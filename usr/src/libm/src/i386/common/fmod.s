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

        .file "fmod.s"

#include "libm.h"
	.weak __fmod
	.type __fmod,@function
#include "libm_protos.h"

	ENTRY(fmod)
	movl	16(%esp),%eax		# eax <-- hi_32(y)
	andl	$0x7fffffff,%eax	# eax <-- hi_32(|y|)
	orl	12(%esp),%eax		# eax <-- lo_32(y)|hi_32(|y|)
	je	.zero

	fldl	12(%esp)		# load arg y
	fldl	4(%esp)			# load arg x
.mod_loop:
	fprem				# partial fmod
	fstsw	%ax			# store status word
	andw	$0x400,%ax		# check for incomplete reduction
	jne	.mod_loop		# while incomplete, do fprem again
	fstp	%st(1)
	ret
.zero:
	pushl	%ebp
	movl	%esp,%ebp
#ifdef PIC	/* PIC-SETUP macro */
	pushl	%ebx
	call	.1
.1:	popl	%ebx
	addl	$_GLOBAL_OFFSET_TABLE_+[.-.1],%ebx
#endif
	pushl	$27			# case 27 in _SVID_libm_err
	pushl	20(%ebp)		# pass x
	pushl	16(%ebp)
	pushl	12(%ebp)		# pass y
	pushl	8(%ebp)
#ifdef PIC	/* PIC-F macro */
	call	_SVID_libm_err@PLT
#else
	call	_SVID_libm_err
#endif
	addl	$20,%esp
#ifdef PIC	/* PIC-WRAPUP macro */
	popl	%ebx
#endif
	leave
	ret
	.align	4
	SET_SIZE(fmod)
