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

        .file "nextafterf.s"

#include "libm.h"
	.weak __nextafterf
	.type __nextafterf,@function

	.data
	.align	4
Fmaxf:	.long	0x7f7fffff
Fminf:	.long	0x1
ftmpf:	.long	0


	ENTRY(nextafterf)
	pushl	%ebp
	movl	%esp,%ebp
	movl	$0,%eax		# upper half of %eax must be initialized
	flds	12(%ebp)	# y
	subl	$4,%esp
	flds	8(%ebp)		# x, y
	fucom			# x : y
	fstsw	%ax
	sahf
	jp	.NaN
	je	.equal
	fstp	%st(1)		# x
	ja	.bigger
	# x < y
	ftst			# x : 0
	movl	$0x1,-4(%ebp)		# -4(%ebp) contains Fminf
	fnstsw	%ax
	sahf
	je	.final
	ja	.addulp
	jb	.subulp
.bigger:
	# x > y
	ftst			# x : 0
	movl	$0x80000001,-4(%ebp)	# -4(%ebp) contains -Fminf
	fnstsw	%ax
	sahf
	je	.final
	jb	.addulp
.subulp:
	movl	8(%ebp),%eax	# x
	subl	$1,%eax		# x - ulp
	movl	%eax,-4(%ebp)
	jmp	.final
.addulp:
	movl	8(%ebp),%eax	# x
	addl	$1,%eax		# x + ulp
	movl	%eax,-4(%ebp)

.final:
	fstp	%st(0)		# empty
	flds	-4(%ebp)	# z
	andl	$0x7f800000,%eax
	jz	.underflow
	cmpl	$0x7f800000,%eax
	je	.overflow
	jmp	.return
.overflow:
#ifdef PIC	/* PIC-SETUP macro */
	pushl	%ebx
	call	.1
.1:	popl	%ebx
	addl	$_GLOBAL_OFFSET_TABLE_+[.-.1],%ebx
#endif
#ifdef PIC	/* PIC-L macro */
	flds	Fmaxf@GOTOFF(%ebx)	# Fmaxf, z
#else
	flds	Fmaxf			# Fmaxf, z
#endif
	fmul	%st(0),%st		# overflow-to-Inf, z
#ifdef PIC	/* PIC-L macro */
	fstps	ftmpf@GOTOFF(%ebx)	# z & create overflow signal
#else
	fstps	ftmpf			# z & create overflow signal
#endif
#ifdef PIC	/* PIC-WRAPUP macro */
	popl	%ebx
#endif
	jmp	.return
.underflow:
#ifdef PIC	/* PIC-SETUP macro */
	pushl	%ebx
	call	.2
.2:	popl	%ebx
	addl	$_GLOBAL_OFFSET_TABLE_+[.-.2],%ebx
#endif
#ifdef PIC	/* PIC-L macro */
	flds	Fminf@GOTOFF(%ebx)	# Fminf, z
#else
	flds	Fminf			# Fminf, z
#endif
	fmul	%st(0),%st		# underflow-to-0, z
#ifdef PIC	/* PIC-L macro */
	fstps	ftmpf@GOTOFF(%ebx)	# z & create underflow signal
#else
	fstps	ftmpf			# z & create underflow signal
#endif
#ifdef PIC	/* PIC-WRAPUP macro */
	popl	%ebx
#endif
	jmp	.return
.equal:
	fstp	%st(0)		# C99 says to return y when x == y
	jmp	.return
.NaN:
	faddp	%st,%st(1)	# x+y
.return:
	fwait
	leave
	ret
	.align	4
	SET_SIZE(nextafterf)
