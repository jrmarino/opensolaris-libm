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

#ifndef _ISO_MATH_C99_H
#define	_ISO_MATH_C99_H

#include <sys/feature_tests.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __P
#ifdef __STDC__
#define	__P(p)	p
#else
#define	__P(p)	()
#endif
#endif	/* !defined(__P) */

#if defined(_STDC_C99) || _XOPEN_SOURCE - 0 >= 600 || defined(__C99FEATURES__)
#if defined(__GNUC__)
#undef	HUGE_VAL
#define	HUGE_VAL	(__builtin_huge_val())
#undef	HUGE_VALF
#define	HUGE_VALF	(__builtin_huge_valf())
#undef	HUGE_VALL
#define	HUGE_VALL	(__builtin_huge_vall())
#undef	INFINITY
#define	INFINITY	(__builtin_inff())
#undef	NAN
#define	NAN		(__builtin_nanf(""))

/*
 * C99 7.12.3 classification macros
 */
#undef	isnan
#if __GNUC__ >= 4
#define	isnan(x)	__builtin_isnan(x)
#else
#define	isnan(x)	__extension__( \
			{ __typeof(x) __x_n = (x); \
			__builtin_isunordered(__x_n, __x_n); })
#endif
#undef	isinf
#define	isinf(x)	__extension__( \
			{ __typeof(x) __x_i = (x); \
			__x_i == (__typeof(__x_i)) INFINITY || \
			__x_i == (__typeof(__x_i)) (-INFINITY); })
#undef	isfinite
#define	isfinite(x)	__extension__( \
			{ __typeof(x) __x_f = (x); \
			!isnan(__x_f) && !isinf(__x_f); })
#undef	isnormal
#define	isnormal(x)	__extension__( \
			{ __typeof(x) __x_r = (x); isfinite(__x_r) && \
			(sizeof (__x_r) == sizeof (float) ? \
			__builtin_fabsf(__x_r) >= __FLT_MIN__ : \
			sizeof (__x_r) == sizeof (double) ? \
			__builtin_fabs(__x_r) >= __DBL_MIN__ : \
			__builtin_fabsl(__x_r) >= __LDBL_MIN__); })
#undef	fpclassify
#define	fpclassify(x)	__extension__( \
			{ __typeof(x) __x_c = (x); \
			isnan(__x_c) ? FP_NAN : \
			isinf(__x_c) ? FP_INFINITE : \
			isnormal(__x_c) ? FP_NORMAL : \
			__x_c == (__typeof(__x_c)) 0 ? FP_ZERO : \
			FP_SUBNORMAL; })
#undef	signbit
#if defined(__sparc)
#define	signbit(x)	__extension__( \
			{ __typeof(x) __x_s = (x); \
			(int) (*(unsigned *) &__x_s >> 31); })
#elif defined(__i386) || defined(__amd64)
#define	signbit(x)	__extension__( \
			{ __typeof(x) __x_s = (x); \
			(sizeof (__x_s) == sizeof (float) ? \
			(int) (*(unsigned *) &__x_s >> 31) : \
			sizeof (__x_s) == sizeof (double) ? \
			(int) (((unsigned *) &__x_s)[1] >> 31) : \
			(int) (((unsigned short *) &__x_s)[4] >> 15)); })
#endif

/*
 * C99 7.12.14 comparison macros
 */
#undef	isgreater
#define	isgreater(x, y)		__builtin_isgreater(x, y)
#undef	isgreaterequal
#define	isgreaterequal(x, y)	__builtin_isgreaterequal(x, y)
#undef	isless
#define	isless(x, y)		__builtin_isless(x, y)
#undef	islessequal
#define	islessequal(x, y)	__builtin_islessequal(x, y)
#undef	islessgreater
#define	islessgreater(x, y)	__builtin_islessgreater(x, y)
#undef	isunordered
#define	isunordered(x, y)	__builtin_isunordered(x, y)
#else	/* defined(__GNUC__) */
#undef	HUGE_VAL
#define	HUGE_VAL	__builtin_huge_val
#undef	HUGE_VALF
#define	HUGE_VALF	__builtin_huge_valf
#undef	HUGE_VALL
#define	HUGE_VALL	__builtin_huge_vall
#undef	INFINITY
#define	INFINITY	__builtin_infinity
#undef	NAN
#define	NAN		__builtin_nan

/*
 * C99 7.12.3 classification macros
 */
#undef	fpclassify
#define	fpclassify(x)	__builtin_fpclassify(x)
#undef	isfinite
#define	isfinite(x)	__builtin_isfinite(x)
#undef	isinf
#define	isinf(x)	__builtin_isinf(x)
#undef	isnan
#define	isnan(x)	__builtin_isnan(x)
#undef	isnormal
#define	isnormal(x)	__builtin_isnormal(x)
#undef	signbit
#define	signbit(x)	__builtin_signbit(x)

/*
 * C99 7.12.14 comparison macros
 */
#undef	isgreater
#define	isgreater(x, y)		((x) __builtin_isgreater(y))
#undef	isgreaterequal
#define	isgreaterequal(x, y)	((x) __builtin_isgreaterequal(y))
#undef	isless
#define	isless(x, y)		((x) __builtin_isless(y))
#undef	islessequal
#define	islessequal(x, y)	((x) __builtin_islessequal(y))
#undef	islessgreater
#define	islessgreater(x, y)	((x) __builtin_islessgreater(y))
#undef	isunordered
#define	isunordered(x, y)	((x) __builtin_isunordered(y))
#endif	/* defined(__GNUC__) */
#endif	/* defined(_STDC_C99) || _XOPEN_SOURCE - 0 >= 600 || ... */

#if defined(__EXTENSIONS__) || defined(_STDC_C99) || \
	(!defined(_STRICT_STDC) && !defined(__XOPEN_OR_POSIX)) || \
	defined(__C99FEATURES__)
#if defined(__FLT_EVAL_METHOD__) && __FLT_EVAL_METHOD__ - 0 == 0
typedef float float_t;
typedef double double_t;
#elif __FLT_EVAL_METHOD__ - 0 == 1
typedef double float_t;
typedef double double_t;
#elif __FLT_EVAL_METHOD__ - 0 == 2
typedef long double float_t;
typedef long double double_t;
#elif defined(__sparc) || defined(__amd64)
typedef float float_t;
typedef double double_t;
#elif defined(__i386)
typedef long double float_t;
typedef long double double_t;
#endif

#undef	FP_ZERO
#define	FP_ZERO		0
#undef	FP_SUBNORMAL
#define	FP_SUBNORMAL	1
#undef	FP_NORMAL
#define	FP_NORMAL	2
#undef	FP_INFINITE
#define	FP_INFINITE	3
#undef	FP_NAN
#define	FP_NAN		4

#undef	FP_ILOGB0
#define	FP_ILOGB0	(-2147483647)
#undef	FP_ILOGBNAN
#define	FP_ILOGBNAN	2147483647

#undef	MATH_ERRNO
#define	MATH_ERRNO	1
#undef	MATH_ERREXCEPT
#define	MATH_ERREXCEPT	2
#undef	math_errhandling
#define	math_errhandling	MATH_ERREXCEPT

extern double acosh __P((double));
extern double asinh __P((double));
extern double atanh __P((double));

extern double exp2 __P((double));
extern double expm1 __P((double));
extern int ilogb __P((double));
extern double log1p __P((double));
extern double log2 __P((double));
extern double logb __P((double));
extern double scalbn __P((double, int));
extern double scalbln __P((double, long int));

extern double cbrt __P((double));
extern double hypot __P((double, double));

extern double erf __P((double));
extern double erfc __P((double));
extern double lgamma __P((double));
extern double tgamma __P((double));

extern double nearbyint __P((double));
extern double rint __P((double));
extern long int lrint __P((double));
extern double round __P((double));
extern long int lround __P((double));
extern double trunc __P((double));

extern double remainder __P((double, double));
extern double remquo __P((double, double, int *));

extern double copysign __P((double, double));
extern double nan __P((const char *));
extern double nextafter __P((double, double));
extern double nexttoward __P((double, long double));

extern double fdim __P((double, double));
extern double fmax __P((double, double));
extern double fmin __P((double, double));

extern double fma __P((double, double, double));

extern float acosf __P((float));
extern float asinf __P((float));
extern float atanf __P((float));
extern float atan2f __P((float, float));
extern float cosf __P((float));
extern float sinf __P((float));
extern float tanf __P((float));

extern float acoshf __P((float));
extern float asinhf __P((float));
extern float atanhf __P((float));
extern float coshf __P((float));
extern float sinhf __P((float));
extern float tanhf __P((float));

extern float expf __P((float));
extern float exp2f __P((float));
extern float expm1f __P((float));
extern float frexpf __P((float, int *));
extern int ilogbf __P((float));
extern float ldexpf __P((float, int));
extern float logf __P((float));
extern float log10f __P((float));
extern float log1pf __P((float));
extern float log2f __P((float));
extern float logbf __P((float));
extern float modff __P((float, float *));
extern float scalbnf __P((float, int));
extern float scalblnf __P((float, long int));

extern float cbrtf __P((float));
extern float fabsf __P((float));
extern float hypotf __P((float, float));
extern float powf __P((float, float));
extern float sqrtf __P((float));

extern float erff __P((float));
extern float erfcf __P((float));
extern float lgammaf __P((float));
extern float tgammaf __P((float));

extern float ceilf __P((float));
extern float floorf __P((float));
extern float nearbyintf __P((float));
extern float rintf __P((float));
extern long int lrintf __P((float));
extern float roundf __P((float));
extern long int lroundf __P((float));
extern float truncf __P((float));

extern float fmodf __P((float, float));
extern float remainderf __P((float, float));
extern float remquof __P((float, float, int *));

extern float copysignf __P((float, float));
extern float nanf __P((const char *));
extern float nextafterf __P((float, float));
extern float nexttowardf __P((float, long double));

extern float fdimf __P((float, float));
extern float fmaxf __P((float, float));
extern float fminf __P((float, float));

extern float fmaf __P((float, float, float));

extern long double acosl __P((long double));
extern long double asinl __P((long double));
extern long double atanl __P((long double));
extern long double atan2l __P((long double, long double));
extern long double cosl __P((long double));
extern long double sinl __P((long double));
extern long double tanl __P((long double));

extern long double acoshl __P((long double));
extern long double asinhl __P((long double));
extern long double atanhl __P((long double));
extern long double coshl __P((long double));
extern long double sinhl __P((long double));
extern long double tanhl __P((long double));

extern long double expl __P((long double));
extern long double exp2l __P((long double));
extern long double expm1l __P((long double));
extern long double frexpl __P((long double, int *));
extern int ilogbl __P((long double));
extern long double ldexpl __P((long double, int));
extern long double logl __P((long double));
extern long double log10l __P((long double));
extern long double log1pl __P((long double));
extern long double log2l __P((long double));
extern long double logbl __P((long double));
extern long double modfl __P((long double, long double *));
extern long double scalbnl __P((long double, int));
extern long double scalblnl __P((long double, long int));

extern long double cbrtl __P((long double));
extern long double fabsl __P((long double));
extern long double hypotl __P((long double, long double));
extern long double powl __P((long double, long double));
extern long double sqrtl __P((long double));

extern long double erfl __P((long double));
extern long double erfcl __P((long double));
extern long double lgammal __P((long double));
extern long double tgammal __P((long double));

extern long double ceill __P((long double));
extern long double floorl __P((long double));
extern long double nearbyintl __P((long double));
extern long double rintl __P((long double));
extern long int lrintl __P((long double));
extern long double roundl __P((long double));
extern long int lroundl __P((long double));
extern long double truncl __P((long double));

extern long double fmodl __P((long double, long double));
extern long double remainderl __P((long double, long double));
extern long double remquol __P((long double, long double, int *));

extern long double copysignl __P((long double, long double));
extern long double nanl __P((const char *));
extern long double nextafterl __P((long double, long double));
extern long double nexttowardl __P((long double, long double));

extern long double fdiml __P((long double, long double));
extern long double fmaxl __P((long double, long double));
extern long double fminl __P((long double, long double));

extern long double fmal __P((long double, long double, long double));

#if !defined(_STRICT_STDC) && !defined(_NO_LONGLONG) || defined(_STDC_C99) || \
	defined(__C99FEATURES__)
extern long long int llrint __P((double));
extern long long int llround __P((double));

extern long long int llrintf __P((float));
extern long long int llroundf __P((float));

extern long long int llrintl __P((long double));
extern long long int llroundl __P((long double));
#endif

#endif	/* defined(__EXTENSIONS__) || defined(_STDC_C99) || ... */

#ifdef __cplusplus
}
#endif

#endif	/* _ISO_MATH_C99_H */
