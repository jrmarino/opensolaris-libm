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

#pragma weak __jn = jn
#pragma weak __yn = yn

/*
 * floating point Bessel's function of the 1st and 2nd kind
 * of order n: jn(n,x),yn(n,x);
 *
 * Special cases:
 *	y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *	y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 * Note 2. About jn(n,x), yn(n,x)
 *	For n=0, j0(x) is called,
 *	for n=1, j1(x) is called,
 *	for n<x, forward recursion us used starting
 *	from values of j0(x) and j1(x).
 *	for n>x, a continued fraction approximation to
 *	j(n,x)/j(n-1,x) is evaluated and then backward
 *	recursion is used starting from a supposed value
 *	for j(n,x). The resulting value of j(0,x) is
 *	compared with the actual value to correct the
 *	supposed value of j(n,x).
 *
 *	yn(n,x) is similar in all respects, except
 *	that forward recursion is used for all
 *	values of n>1.
 *
 */

#include "libm.h"
#include <float.h>	/* DBL_MIN */
#include <values.h>	/* X_TLOSS */
#include "xpg6.h"	/* __xpg6 */

#define GENERIC double

static const GENERIC
	invsqrtpi = 5.641895835477562869480794515607725858441e-0001,
	two	= 2.0,
	zero	= 0.0,
	one	= 1.0;

GENERIC
jn(int n, GENERIC x) {
	int i, sgn;
	GENERIC a, b, temp = 0;
	GENERIC z, w, ox, on;

	/*
	 * J(-n,x) = (-1)^n * J(n, x), J(n, -x) = (-1)^n * J(n, x)
     * Thus, J(-n,x) = J(n,-x)
     */
	ox = x; on = (GENERIC)n;
	if(n<0){
		n = -n;
		x = -x;
	}
	if (isnan(x))
		return (x*x);	/* + -> * for Cheetah */
	if (!((int) _lib_version == libm_ieee ||
		(__xpg6 & _C99SUSv3_math_errexcept) != 0)) {
	    if (fabs(x) > X_TLOSS)
			return (_SVID_libm_err(on, ox, 38));
	}
	if (n == 0)
		return (j0(x));
	if (n == 1)
		return (j1(x));
	if((n&1)==0)
		sgn=0; 			/* even n */
	else
		sgn = signbit(x);	/* old n  */
	x = fabs(x);
	if(x == zero||!finite(x)) b = zero;
	else if ((GENERIC)n <= x) {
					/*
					 * Safe to use
					 *  J(n+1,x)=2n/x *J(n,x)-J(n-1,x)
					 */
	    if (x > 1.0e91) {
				/*
				 * x >> n**2
				 *    Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
				 *   Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
				 *   Let s=sin(x), c=cos(x),
				 *	xn=x-(2n+1)*pi/4, sqt2 = sqrt(2),then
				 *
				 *	   n	sin(xn)*sqt2	cos(xn)*sqt2
				 *	----------------------------------
				 *	   0	 s-c		 c+s
				 *	   1	-s-c 		-c+s
				 *	   2	-s+c		-c-s
				 *	   3	 s+c		 c-s
				 */
		switch(n&3) {
		    case 0: temp =  cos(x)+sin(x); break;
		    case 1: temp = -cos(x)+sin(x); break;
		    case 2: temp = -cos(x)-sin(x); break;
		    case 3: temp =  cos(x)-sin(x); break;
		}
		b = invsqrtpi*temp/sqrt(x);
	    } else {
	        a = j0(x);
	        b = j1(x);
	        for(i=1;i<n;i++){
		    temp = b;
		    b = b*((GENERIC)(i+i)/x) - a; /* avoid underflow */
		    a = temp;
	        }
	    }
	} else {
	    if(x<1e-9) {	/* use J(n,x) = 1/n!*(x/2)^n */
		b = pow(0.5*x,(GENERIC) n);
		if (b!=zero) {
		    for(a=one,i=1;i<=n;i++) a *= (GENERIC)i;
		    b = b/a;
		}
	    } else {
		/*
		 * use backward recurrence
		 * 			x	  x^2	  x^2
		 *  J(n,x)/J(n-1,x) =  ----   ------   ------   .....
		 *			2n  - 2(n+1) - 2(n+2)
		 *
		 * 			1      1        1
		 *  (for large x)   =  ----  ------   ------   .....
		 *			2n   2(n+1)   2(n+2)
		 *			-- - ------ - ------ -
		 *			 x     x         x
		 *
		 * Let w = 2n/x and h=2/x, then the above quotient
		 * is equal to the continued fraction:
		 *		    1
		 *	= -----------------------
		 *		       1
		 *	   w - -----------------
		 *			  1
		 * 	        w+h - ---------
		 *		       w+2h - ...
		 *
		 * To determine how many terms needed, let
		 * Q(0) = w, Q(1) = w(w+h) - 1,
		 * Q(k) = (w+k*h)*Q(k-1) - Q(k-2),
		 * When Q(k) > 1e4	good for single
		 * When Q(k) > 1e9	good for double
		 * When Q(k) > 1e17	good for quaduple
		 */
	    /* determin k */
		GENERIC t,v;
		double q0,q1,h,tmp; int k,m;
		w  = (n+n)/(double)x; h = 2.0/(double)x;
		q0 = w;  z = w+h; q1 = w*z - 1.0; k=1;
		while(q1<1.0e9) {
			k += 1; z += h;
			tmp = z*q1 - q0;
			q0 = q1;
			q1 = tmp;
		}
		m = n+n;
		for(t=zero, i = 2*(n+k); i>=m; i -= 2) t = one/(i/x-t);
		a = t;
		b = one;
		/*
		 * estimate log((2/x)^n*n!) = n*log(2/x)+n*ln(n)
		 *  hence, if n*(log(2n/x)) > ...
		 *  single 8.8722839355e+01
		 *  double 7.09782712893383973096e+02
		 *  long double 1.1356523406294143949491931077970765006170e+04
		 *  then recurrent value may overflow and the result is
		 *  likely underflow to zero
		 */
		tmp = n;
		v = two/x;
		tmp = tmp*log(fabs(v*tmp));
		if(tmp<7.09782712893383973096e+02) {
	    	    for(i=n-1;i>0;i--){
		        temp = b;
		        b = ((i+i)/x)*b - a;
		        a = temp;
	     	    }
		} else {
	    	    for(i=n-1;i>0;i--){
		        temp = b;
		        b = ((i+i)/x)*b - a;
		        a = temp;
			if(b>1e100) {
			    a /= b;
			    t /= b;
			    b  = 1.0;
			}
	     	    }
		}
	    	b = (t*j0(x)/b);
	    }
	}
	if (sgn == 1)
		return (-b);
	else
		return (b);
}

GENERIC
yn(int n, GENERIC x) {
	int i;
	int sign;
	GENERIC a, b, temp = 0, ox, on;

	ox = x; on = (GENERIC)n;
	if (isnan(x))
		return (x*x);	/* + -> * for Cheetah */
	if (x <= zero) {
		if (x == zero) {
			/* return -one/zero; */
			return (_SVID_libm_err((GENERIC)n, x, 12));
		} else {
			/* return zero/zero; */
			return (_SVID_libm_err((GENERIC)n, x, 13));
		}
	}
	if (!((int) _lib_version == libm_ieee ||
		(__xpg6 & _C99SUSv3_math_errexcept) != 0)) {
	    if (x > X_TLOSS)
			return (_SVID_libm_err(on, ox, 39));
	}
	sign = 1;
	if(n<0){
		n = -n;
		if((n&1) == 1) sign = -1;
	}
	if (n == 0)
		return (y0(x));
	if (n == 1)
		return (sign*y1(x));
	if (!finite(x))
		return (zero);

	if (x > 1.0e91) {
				/*
				 * x >> n**2
				 *  Jn(x) = cos(x-(2n+1)*pi/4)*sqrt(2/x*pi)
				 *  Yn(x) = sin(x-(2n+1)*pi/4)*sqrt(2/x*pi)
				 *  Let s = sin(x), c = cos(x),
				 *  xn = x-(2n+1)*pi/4, sqt2 = sqrt(2), then
				 *
				 *    n	sin(xn)*sqt2	cos(xn)*sqt2
				 *	----------------------------------
				 *	 0	 s-c		 c+s
				 *	 1	-s-c 		-c+s
				 *	 2	-s+c		-c-s
				 *	 3	 s+c		 c-s
				 */
		switch(n&3) {
		    case 0: temp =  sin(x)-cos(x); break;
		    case 1: temp = -sin(x)-cos(x); break;
		    case 2: temp = -sin(x)+cos(x); break;
		    case 3: temp =  sin(x)+cos(x); break;
		}
		b = invsqrtpi*temp/sqrt(x);
	} else {
		a = y0(x);
		b = y1(x);
		/*
		 * fix 1262058 and take care of non-default rounding
		 */
		for (i = 1; i < n; i++) {
			temp = b;
			b *= (GENERIC) (i + i) / x;
			if (b <= -DBL_MAX)
				break;
			b -= a;
			a = temp;
		}
	}
	if (sign > 0)
		return (b);
	else
		return (-b);
}
