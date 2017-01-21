/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright 2011 Nexenta Systems, Inc.  All rights reserved.
 */
/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */
/*
 * Copyright 2017 John R. Marino <draco@marino.st>
 */

#pragma weak __fex_get_log = fex_get_log
#pragma weak __fex_set_log = fex_set_log
#pragma weak __fex_get_log_depth = fex_get_log_depth
#pragma weak __fex_set_log_depth = fex_set_log_depth
#pragma weak __fex_log_entry = fex_log_entry

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ucontext.h>
#include <machine/frame.h>
#include <fenv.h>
#include <sys/ieeefp.h>
#include <pthread.h>
#include "fex_handler.h"

#if defined __DragonFly__ || defined __FreeBSD__
#define REG_PC	mc_rip
#define REG_SP	mc_rsp
#define REG_FP	mc_rbp
#define FRAME_STRUCTURE	struct trapframe
#define FRAMEP(X)	(struct trapframe *)(X)
#define NEXT_FRAME(fp)	(struct trapframe *)fp->tf_rbp
#define NEXT_STACK(fp)	fp->tf_rip
# ifdef __FreeBSD__
#define FPU_STATE	mc_fpstate
#define FPU_STRUCTURE	savefpu
# endif
# ifdef __DragonFly__
#define FPU_STATE	mc_fpregs
#define FPU_STRUCTURE	savexmm64
# endif
#else
#error Fex log not supported on this platform
#endif

#define SUPPORT_STACK_WALKING	0

static FILE *log_fp = NULL;
static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;
static int log_depth = 100;

FILE *fex_get_log(void)
{
	FILE	*fp;

	pthread_mutex_lock(&log_lock);
	fp = log_fp;
	pthread_mutex_unlock(&log_lock);
	return fp;
}

int fex_set_log(FILE *fp)
{
	pthread_mutex_lock(&log_lock);
	log_fp = fp;
	pthread_mutex_unlock(&log_lock);
	__fex_update_te();
	return 1;
}

int fex_get_log_depth(void)
{
	int	d;

	pthread_mutex_lock(&log_lock);
	d = log_depth;
	pthread_mutex_unlock(&log_lock);
	return d;
}

int fex_set_log_depth(int d)
{
	if (d < 0)
		return 0;
	pthread_mutex_lock(&log_lock);
	log_depth = d;
	pthread_mutex_unlock(&log_lock);
	return 1;
}

static struct exc_list {
	struct exc_list		*next;
	char			*addr;
	unsigned long		code;
	int			nstack;
	char			*stack[1]; /* actual length is max(1,nstack) */
} *list = NULL;

// amd64
#define PDIG		"16"

/* look for a matching exc_list; return 1 if one is found,
   otherwise add this one to the list and return 0 */
static int check_exc_list(char *addr, unsigned long code, char *stk,
    FRAME_STRUCTURE *fp)
{
	struct exc_list	*l, *ll = NULL;
	FRAME_STRUCTURE	*f;
	int		i, n;

	if (list) {
		for (l = list; l; ll = l, l = l->next) {
			if (l->addr != addr || l->code != code)
				continue;
			if (log_depth < 1 || l->nstack < 1)
				return 1;
			if (l->stack[0] != stk)
				continue;
			n = 1;
			for (i = 1, f = fp;
			  i < log_depth && i < l->nstack && NEXT_STACK(f);
			  i++, f = NEXT_FRAME(f))
				if (l->stack[i] != (char *)NEXT_STACK(f)) {
					n = 0;
					break;
				}
			if (n)
				return 1;
		}
	}

	/* create a new exc_list structure and tack it on the list */
	for (n = 1, f = fp;
	  n < log_depth && f && NEXT_STACK(f);
	  n++, f = NEXT_FRAME(f));
	if ((l = (struct exc_list *)malloc(sizeof(struct exc_list) +
	    (n - 1) * sizeof(char *))) != NULL) {
		l->next = NULL;
		l->addr = addr;
		l->code = code;
		l->nstack = ((log_depth < 1)? 0 : n);
		l->stack[0] = stk;
		for (i = 1; i < n; i++) {
			l->stack[i] = (char *)NEXT_STACK(fp);
			fp = NEXT_FRAME(f);
		}
		if (list)
			ll->next = l;
		else
			list = l;
	}
	return 0;
}

/*
* Warning: cleverness ahead
*
* In the following code, the use of sprintf+write rather than fprintf
* to send output to the log file is intentional.  The reason is that
* fprintf is not async-signal-safe.  "But," you protest, "SIGFPE is
* not an asynchronous signal!  It's always handled by the same thread
* that executed the fpop that provoked it."  That's true, but a prob-
* lem arises because (i) base conversion in fprintf can cause a fp
* exception and (ii) my signal handler acquires a mutex lock before
* sending output to the log file (so that outputs for entries from
* different threads aren't interspersed).  Therefore, if the code
* were to use fprintf, a deadlock could occur as follows:
*
*	Thread A			Thread B
*
*	Incurs a fp exception,		Calls fprintf,
*	acquires log_lock		acquires file rmutex lock
*
*	Calls fprintf,			Incurs a fp exception,
*	waits for file rmutex lock	waits for log_lock
*
* (I could just verify that fprintf doesn't hold the rmutex lock while
* it's doing the base conversion, but since efficiency is of little
* concern here, I opted for the safe and dumb route.)
*/

static void print_stack(int fd, char *addr, FRAME_STRUCTURE *fp)
{
	int	i;
	char	buf[30];
	char	*line;

	for (i = 0; i < log_depth && addr != NULL; i++) {
		line = convert_address_to_symbol (addr);
		write(fd, buf, sprintf(buf, "  0x%0" PDIG "lx  ", (long)addr));
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
/* temp -- figure out how to detect main
			if (!strcmp(name, "main"))
				break;
*/
		if (fp == NULL)
			break;
		addr = (char *)NEXT_STACK(fp);
		fp = NEXT_FRAME(fp);
	}
}

static void
print_previous_two_stack_addresses (int fd, char *addr, FRAME_STRUCTURE *fp) {
	char	buf[30];
	char	*line;
	char	*next_addr;
	const char	*crtstuff = "_start ";

	line = convert_address_to_symbol (addr);
	write(fd, buf, sprintf(buf, "  0x%0" PDIG "lx  ", (long)addr));
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
	/* Don't print previous frame if it starts with "_start" symbol */
	next_addr = (char *)fp->tf_rsi;
	line = convert_address_to_symbol (next_addr);
	if (strncmp(line, crtstuff, 7) == 0) {
		return;
	}
	write(fd, buf, sprintf(buf, "  0x%0" PDIG "lx  ", (long)next_addr));
	write(fd, line, strlen(line));
	write(fd, "\n", 1);
}

void fex_log_entry(const char *msg)
{
	ucontext_t	uc;
	FRAME_STRUCTURE	*fp;
	char		*stk;
	int		fd;

	/* if logging is disabled, just return */
	pthread_mutex_lock(&log_lock);
	if (log_fp == NULL) {
		pthread_mutex_unlock(&log_lock);
		return;
	}

	/* get the frame pointer from the current context and
	   pop our own frame */
	getcontext(&uc);
	fp = FRAMEP(uc.uc_mcontext.REG_SP);

	if (fp == NULL) {
		pthread_mutex_unlock(&log_lock);
		return;
	}
	stk = (char *)NEXT_STACK(fp);
	fp = NEXT_FRAME(fp);

	/* if we've already logged this message here, don't make an entry */
	if (check_exc_list(stk, (unsigned long)msg, stk, fp)) {
		pthread_mutex_unlock(&log_lock);
		return;
	}

	/* make an entry */
	fd = fileno(log_fp);
	write(fd, "fex_log_entry: ", 15);
	write(fd, msg, strlen(msg));
	write(fd, "\n", 1);
	print_stack(fd, stk, fp);
	pthread_mutex_unlock(&log_lock);
}

static const char *exception[FEX_NUM_EXC] = {
	"inexact result",
	"division by zero",
	"underflow",
	"overflow",
	"invalid operation (0/0)",
	"invalid operation (inf/inf)",
	"invalid operation (inf-inf)",
	"invalid operation (0*inf)",
	"invalid operation (sqrt)",
	"invalid operation (snan)",
	"invalid operation (int)",
	"invalid operation (cmp)"
};

void
__fex_mklog(ucontext_t *uap, char *addr, int f, enum fex_exception e,
    int m, void *p)
{
	FRAME_STRUCTURE	*fp;
	char		*stk;
	int		fd;
	char		*line;

	/* if logging is disabled, just return */
	pthread_mutex_lock(&log_lock);
	if (log_fp == NULL) {
		pthread_mutex_unlock(&log_lock);
		return;
	}

	/* get stack info */
	stk = (char*)uap->uc_mcontext.REG_PC;
	fp = FRAMEP(uap->uc_mcontext.REG_FP);


	/* if the handling mode is the default and this exception's
	   flag is already raised, don't make an entry */
	if (m == FEX_NONSTOP) {
		switch (e) {
		case fex_inexact:
			if (f & FE_INEXACT) {
				pthread_mutex_unlock(&log_lock);
				return;
			}
			break;
		case fex_underflow:
			if (f & FE_UNDERFLOW) {
				pthread_mutex_unlock(&log_lock);
				return;
			}
			break;
		case fex_overflow:
			if (f & FE_OVERFLOW) {
				pthread_mutex_unlock(&log_lock);
				return;
			}
			break;
		case fex_division:
			if (f & FE_DIVBYZERO) {
				pthread_mutex_unlock(&log_lock);
				return;
			}
			break;
		default:
			if (f & FE_INVALID) {
				pthread_mutex_unlock(&log_lock);
				return;
			}
			break;
		}
	}

#if SUPPORT_STACK_WALKING
	/* if we've already logged this exception at this address,
	   don't make an entry */
	if (check_exc_list(addr, (unsigned long)e, stk, fp)) {
		pthread_mutex_unlock(&log_lock);
		return;
	}
#endif

	/* make an entry */
	line = convert_address_to_symbol (addr);
	fd = fileno(log_fp);
	write(fd, "Floating point ", 15);
	write(fd, exception[e], strlen(exception[e]));
	write(fd, " at ", 4);
	write(fd, line, strlen(line));
	switch (m) {
	case FEX_NONSTOP:
		write(fd, ", nonstop mode\n", 15);
		break;

	case FEX_ABORT:
		write(fd, ", abort\n", 8);
		break;

	case FEX_NOHANDLER:
		if (p == (void *)SIG_DFL) {
			write(fd, ", handler: SIG_DFL\n", 19);
			break;
		}
		else if (p == (void *)SIG_IGN) {
			write(fd, ", handler: SIG_IGN\n", 19);
			break;
		}
		/* fall through*/
	default:
		write(fd, ", handler: ", 11);
		line = convert_address_to_symbol (p);
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		break;
	}
#if SUPPORT_STACK_WALKING
	print_stack(fd, stk, fp);
#else
	print_previous_two_stack_addresses(fd, stk, fp);
#endif
	pthread_mutex_unlock(&log_lock);
}
