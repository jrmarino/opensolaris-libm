/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License, Version 1.0 only
 * (the "License").  You may not use this file except in compliance
 * with the License.
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
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*
 * Copyright 2017 John R. Marino <draco@marino.st>
 *
 * This was not part of the original libm release. The fpclass function
 * has been reconstructed from Illumos sources as it is required for
 * proper libm functionality (x86 only)
 */

/* double precision */
typedef  union {
	struct {
		unsigned  lo	:32;
		unsigned  hi	:20;
		unsigned  exp	:11;
		unsigned  sign	:1;
	} fparts;
	struct {
		unsigned  lo	:32;
		unsigned  hi	:19;
		unsigned  qnan_bit	:1;
		unsigned  exp	:11;
		unsigned  sign	:1;
	} nparts;
	struct {
		unsigned  lo	:32;
		unsigned  hi	:32;
	} fwords;
	double	d;
} _dval;

/* single precision */
typedef  union {
	struct {
		unsigned fract	:23;
		unsigned exp	:8;
		unsigned sign	:1;
	} fparts;
	struct {
		unsigned fract	:22;
		unsigned qnan_bit	:1;
		unsigned exp	:8;
		unsigned sign	:1;
	} nparts;
	unsigned long	fword;
	float	f;
} _fval;

#define	SIGNBIT(X)	(((_dval *)&(X))->fparts.sign)
#define	EXPONENT(X)	(((_dval *)&(X))->fparts.exp)

#define	HIFRACTION(X)	(((_dval *)&(X))->fparts.hi)
#define	LOFRACTION(X)	(((_dval *)&(X))->fparts.lo)
#define	QNANBIT(X)	(((_dval *)&(X))->nparts.qnan_bit)

#define	MAXEXP	0x7ff /* maximum exponent of double */

#include <sys/ieeefp.h>

/*
 * FPCLASS(X)
 * fpclass(x) returns the floating point class x belongs to
 */

enum fp_class_type
fpclass(double x)
{
/* #### original function ####
 * The original function distinguished between positive and negative
 * versions of infinity, normal, denormal, and zero, but the
 * fp_class_type enumeration doesn't make this distinguishment.

	int	sign, exp;

	exp = EXPONENT(x);
	sign = SIGNBIT(x);
	if (exp == 0) { * de-normal or zero *
		if (HIFRACTION(x) || LOFRACTION(x)) * de-normal *
			return (sign ? FP_NDENORM : FP_PDENORM);
		else
			return (sign ? FP_NZERO : FP_PZERO);
	}
	if (exp == MAXEXP) { * infinity or NaN *
		if ((HIFRACTION(x) == 0) && (LOFRACTION(x) == 0)) * infinity *
			return (sign ? FP_NINF : FP_PINF);
		else
			if (QNANBIT(x))
			* hi-bit of mantissa set - quiet nan *
				return (FP_QNAN);
			else	return (FP_SNAN);
	}
	* if we reach here we have non-zero normalized number *
	return (sign ? FP_NNORM : FP_PNORM);
*/
	int	exp;
	exp = EXPONENT(x);
	if (exp == 0) {
		if (HIFRACTION(x) || LOFRACTION(x))
			return fp_subnormal;
		else
			return fp_zero;
	}
	if (exp == MAXEXP) {
		/* infinity or NaN */
		if ((HIFRACTION(x) == 0) && (LOFRACTION(x) == 0))
			return fp_infinity;
		else {
			if (QNANBIT(x))
				return fp_quiet;
			else
				return fp_signaling;
		}
	}
	/* if we reach here we have non-zero normalized number */
	return fp_normal;
}
