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

#pragma weak __cosh = cosh

/* INDENT OFF */
/*
 * cosh(x)
 * Code originated from 4.3bsd.
 * Modified by K.C. Ng for SUN 4.0 libm.
 * Method :
 *	1. Replace x by |x| (cosh(x) = cosh(-x)).
 *	2.
 *		                                        [ exp(x) - 1 ]^2
 *	    0        <= x <= 0.3465  :  cosh(x) := 1 + -------------------
 *			       			           2*exp(x)
 *
 *		                                   exp(x) +  1/exp(x)
 *	    0.3465   <= x <= 22      :  cosh(x) := -------------------
 *			       			           2
 *	    22       <= x <= lnovft  :  cosh(x) := exp(x)/2
 *	    lnovft   <= x <  INF     :  cosh(x) := scalbn(exp(x-1024*ln2),1023)
 *
 *	Note: .3465 is a number near one half of ln2.
 *
 * Special cases:
 *	cosh(x) is |x| if x is +INF, -INF, or NaN.
 *	only cosh(0)=1 is exact for finite x.
 */
/* INDENT ON */

#include "libm.h"

static const double
	ln2 = 6.93147180559945286227e-01,
	ln2hi = 6.93147180369123816490e-01,
	ln2lo = 1.90821492927058770002e-10,
	lnovft = 7.09782712893383973096e+02;

double
cosh(double x) {
	double t, w;

	w = fabs(x);
	if (!finite(w))
		return (w * w);
	if (w < 0.3465) {
		t = expm1(w);
		w = 1.0 + t;
		if (w != 1.0)
			w = 1.0 + (t * t) / (w + w);
		return (w);
	} else if (w < 22.0) {
		t = exp(w);
		return (0.5 * (t + 1.0 / t));
	} else if (w <= lnovft) {
		return (0.5 * exp(w));
	} else {
		w = (w - 1024 * ln2hi) - 1024 * ln2lo;
		if (w >= ln2)
			return (_SVID_libm_err(x, x, 5));
		else
			return (scalbn(exp(w), 1023));
	}
}
