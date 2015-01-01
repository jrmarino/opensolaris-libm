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
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

	.ident	"@(#)acosf.s	1.9	06/01/23 SMI"

        .file "acosf.s"

#include "libm.h"
LIBM_ANSI_PRAGMA_WEAK(acosf,function)
#include "libm_synonyms.h"
#include "libm_protos.h"

#undef fabs

	ENTRY(acosf)
	flds	4(%esp)			# push x
	fld1				# push 1
	fld	%st(1)			# x , 1 , x
	fabs				# |x| , 1 , x
	fucomp
	fstsw   %ax
	sahf
	ja	.ERR
	fadd	%st(1),%st		# 1+x,x
	fldz
	fucomp	
	fstsw	%ax
	sahf
	jp	.L1
	jne	.L1
	# x is -1 
	fstp	%st(0)			# x
	fstp	%st(0)			# empty NPX stack
	fldpi
	ret
.L1:
	fxch	%st(1)			# x,1+x
	fld1				# 1,x,1+x
	fsubp	%st,%st(1)		# 1-x,1+x
	fdivp	%st,%st(1)		# (1-x)/(1+x)
	fsqrt
	fld1				# 1,sqrt((1-x)/(1+x))
	fpatan
	fadd	%st(0),%st
	ret

.ERR:
	# |x| > 1
	fstp	%st(0)			# x
	fstp	%st(0)			# empty NPX stack
	fldz
	fdiv	%st(0),%st		# 0/0
	ret
	.align	4
	SET_SIZE(acosf)
