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
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _LIBM_MACROS_H
#define	_LIBM_MACROS_H

#include <sys/isa_defs.h>

#if defined(__sparc)

#define	HIWORD		0
#define	LOWORD		1
#define	HIXWORD		0		/* index of int containing exponent */
#define	XSGNMSK		0x80000000	/* exponent bit mask within the int */
#define	XBIASED_EXP(x)	((((int *)&x)[HIXWORD] & ~0x80000000) >> 16)
#define	ISZEROL(x)	(((((int *)&x)[0] & ~XSGNMSK) | ((int *)&x)[1] | \
				((int *)&x)[2] | ((int *)&x)[3]) == 0)

#include <stdint.h>

typedef union
{
  double value;
  struct
  {
    uint32_t msw;
    uint32_t lsw;
  } parts;
} ieee_double_shape_type;

#elif defined(__x86)

#define	HIWORD		1
#define	LOWORD		0
#define	HIXWORD		2
#define	XSGNMSK		0x8000
#define	XBIASED_EXP(x)	(((int *)&x)[HIXWORD] & 0x7fff)
#define	ISZEROL(x)	(x == 0.0L)

#include <stdint.h>

typedef union
{
  double value;
  struct
  {
    uint32_t lsw;
    uint32_t msw;
  } parts;
} ieee_double_shape_type;

#define	HANDLE_UNSUPPORTED

/*
 * "convert" the high-order 32 bits of a SPARC quad precision
 * value ("I") to the sign, exponent, and high-order bits of an
 * x86 extended double precision value ("E"); the low-order bits
 * in the 12-byte quantity are left intact
 */
#define	ITOX(I, E)       \
		E[2] = 0xffff & ((I) >> 16); \
		E[1] = (((I) & 0x7fff0000) == 0)? \
		    (E[1] & 0x7fff) | (0x7fff8000 & ((I) << 15)) :\
		    0x80000000 | (E[1] & 0x7fff) | (0x7fff8000 & ((I) << 15))

/*
 * "convert" the sign, exponent, and high-order bits of an x86
 * extended double precision value ("E") to the high-order 32 bits
 * of a SPARC quad precision value ("I")
 */
#define	XTOI(E, I)	\
		I = ((E[2]<<16) | (0xffff & (E[1]>>15)))

#else
#error Unknown architecture
#endif

#define EXTRACT_WORDS(ix0,ix1,d) \
{ \
  ieee_double_shape_type ew_u; \
  ew_u.value = (d); \
  (ix0) = ew_u.parts.msw; \
  (ix1) = ew_u.parts.lsw; \
}

#define GET_HIGH_WORD(i,d) \
{ \
  ieee_double_shape_type gh_u; \
  gh_u.value = (d); \
  (i) = gh_u.parts.msw; \
}

#define SET_HIGH_WORD(d,v) \
{ \
  ieee_double_shape_type sh_u; \
  sh_u.value = (d); \
  sh_u.parts.msw = (v); \
  (d) = sh_u.value; \
}

#define INSERT_WORDS(d,ix0,ix1) \
{ \
  ieee_double_shape_type iw_u; \
  iw_u.parts.msw = (ix0); \
  iw_u.parts.lsw = (ix1); \
  (d) = iw_u.value; \
}

#endif	/* _LIBM_MACROS_H */
