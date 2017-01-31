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
 * Floating point Bessel's function of the first and second kinds
 * of order zero: j0(x),y0(x);
 *
 * Special cases:
 *	y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *	y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 */

#pragma weak __j0 = j0
#pragma weak __y0 = y0

#include "libm.h"
#include "libm_protos.h"
#include <math.h>
#include <values.h>

#define D8_000		0x40200000
#define D4_545		0x40122E8B
#define D2_857		0x4006DB6D
#define D2_000		0x40000000
#define D1_000		0x3FF00000
#define D6_805E38	0x48000000
#define DOF_LIMIT	0x7FE00000	/* 8.988e307 */
#define SMALL		0x3F200000	/* 2^-13 == 1.22e-4 */
#define MINISCULE	0x3E400000	/* 2^-27 == 7.45e-9 */ 

#define GENERIC double
static const GENERIC
zero    = 0.0,
one	= 1.0,
huge	= 1.0e10,
ginormous= 1.0e300,
invsqrtpi= 5.641895835477562869480794515607725858441e-0001,
tpi	= 0.636619772367581343075535053490057448;

static GENERIC pzero(GENERIC), qzero(GENERIC);
static const GENERIC r0[6] = {	/* [0, 2.0] */
	 0.0,
	 0.0,
	 1.56249999999999947958e-02,
	-1.89979294238854721751e-04,
	 1.82954049532700665670e-06,
	-4.61832688532103189199e-09,
};
static const GENERIC s0[5] = {
	 0.0,
	 1.56191029464890010492e-02,
	 1.16926784663337450260e-04,
	 5.13546550207318111446e-07,
	 1.16614003333790000205e-09,
};

GENERIC
j0(GENERIC x) {
	GENERIC z,s,c,ss,cc,r,u,ox;
	GENERIC z2,z4;
	GENERIC r1,r2,s1,s2;
	int32_t hx;

	if (isnan(x))
		return (x*x);	/* + -> * for Cheetah */

	GET_HIGH_WORD(hx,x);
	hx &= 0x7fffffff;
	ox = x;
	x = fabs(x);

	if (hx >= D2_000) {
		if (!finite(x))
			return (zero);
		s = sin(x);
		c = cos(x);
	/*
	 * j0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)-q0(x)*sin(x0))
	 * where x0 = x-pi/4
	 * 	Better formula:
	 *		cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
	 *			= 1/sqrt(2) * (cos(x) + sin(x))
	 *		sin(x0) = sin(x)cos(pi/4)-cos(x)sin(pi/4)
	 *			= 1/sqrt(2) * (sin(x) - cos(x))
	 * To avoid cancellation, use
	 *		sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
	 * to compute the worse one.
	 */
		if (hx >= DOF_LIMIT) { /* x+x may overflow if x >= 8.99e307 */
			ss = s - c;
			cc = s + c;
		} else if (signbit(s) != signbit(c)) {
			ss = s - c;
			cc = -cos(x+x)/ss;
		} else {
			cc = s + c;
			ss = -cos(x+x)/cc;
		}
	/*
	 * j0(x) = 1/sqrt(pi) * (P(0,x)*cc - Q(0,x)*ss) / sqrt(x)
	 * y0(x) = 1/sqrt(pi) * (P(0,x)*ss + Q(0,x)*cc) / sqrt(x)
	 */
		if(hx > D6_805E38)
		    z= (invsqrtpi*cc)/sqrt(x);
		else
		    z = invsqrtpi*(pzero(x)*cc-qzero(x)*ss)/sqrt(x);
	/* force to pass SVR4 even the result is wrong (sign) */
		if (x > X_TLOSS)
		    return (_SVID_libm_err(ox, z, 34));
		else
		    return (z);
	}
	if(hx < SMALL) {
		if (ginormous + x > one) { /* raise inexact if x != 0 */
			if (hx < MINISCULE)
				return (one);
			else
				return (one - 0.25*x*x);
		}
	}
	z  = x*x;
	z2 = z*z;
	z4 = z2*z2;

	r1 = z*r0[2];
	r2 = r0[3] + z*r0[4];

	s1 = one + z*s0[1];
	s2 = s0[2] + z*s0[3];

	r = r1 + z2*r2 + z4*r0[5];
	s = s1 + z2*s2 + z4*s0[4];

	if (hx < D1_000) {
		return (one + z*(-0.25 + (r/s)));
	} else {
		u = 0.5*x;
		return ((one + u)*(one - u) + z*(r/s));
	}
}

static const GENERIC u0[7] = {
	-7.38042951086872317523e-02,
	 1.76666452509181115538e-01,
	-1.38185671945596898896e-02,
	 3.47453432093683650238e-04,
	-3.81407053724364161125e-06,
	 1.95590137035022920206e-08,
	-3.98205194132103398453e-11,
};
static const GENERIC v0[4] = {
	 1.27304834834123699328e-02,
	 7.60068627350353253702e-05,
	 2.59150851840457805467e-07,
	 4.41110311332675467403e-10,
};

GENERIC
y0(GENERIC x) {
	GENERIC z,s,c,ss,cc,u,v;
	int32_t hx;

	if (isnan(x))
		return (x*x);	/* + -> * for Cheetah */
	if(x <= zero){
		if(x == zero)
		    /* return -one/(x-x); */
		    return (_SVID_libm_err(x, x, 8));
		else
		    /* return zero/(x-x); */
		    return (_SVID_libm_err(x, x, 9));
	}

	GET_HIGH_WORD(hx,x);
	hx &= 0x7fffffff;

	if (hx >= D2_000) {
		if (!finite(x))
			return (zero);
		s = sin(x);
		c = cos(x);
	/*
	 * j0(x) = sqrt(2/(pi*x))*(p0(x)*cos(x0)-q0(x)*sin(x0))
	 * where x0 = x-pi/4
	 * 	Better formula:
	 *		cos(x0) = cos(x)cos(pi/4)+sin(x)sin(pi/4)
	 *			= 1/sqrt(2) * (cos(x) + sin(x))
	 *		sin(x0) = sin(x)cos(pi/4)-cos(x)sin(pi/4)
	 *			= 1/sqrt(2) * (sin(x) - cos(x))
	 * To avoid cancellation, use
	 *		sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
	 * to compute the worse one.
	 */
		if (hx >= DOF_LIMIT) { /* x+x may overflow if x >= 8.99e307 */
			ss = s - c;
			cc = s + c;
		} else if (signbit(s) != signbit(c)) {
			ss = s - c;
			cc = -cos(x+x)/ss;
		} else {
			cc = s + c;
			ss = -cos(x+x)/cc;
		}
	/*
	 * j0(x) = 1/sqrt(pi*x) * (P(0,x)*cc - Q(0,x)*ss)
	 * y0(x) = 1/sqrt(pi*x) * (P(0,x)*ss + Q(0,x)*cc)
	 */
		if (hx > D6_805E38)
		    z = (invsqrtpi*ss)/sqrt(x);
		else
		    z = invsqrtpi*(pzero(x)*ss+qzero(x)*cc)/sqrt(x);

		if (x > X_TLOSS)
		    return (_SVID_libm_err(x, z, 35));
		else
		    return (z);
	}
	if(hx <= MINISCULE) {
	    return(u0[0] + tpi*log(x));
	}
	z = x*x;
	u = u0[0] + z*(u0[1] + z*(u0[2] + z*(u0[3] + z*(u0[4] + z*(u0[5] + z*u0[6])))));
	v = one+z*(v0[0] + z*(v0[1] + z*(v0[2] + z*v0[3])));
	return(u/v + tpi*(j0(x)*log(x)));
}

/* The asymptotic expansions of pzero is
 *	1 - 9/128 s^2 + 11025/98304 s^4 - ...,	where s = 1/x.
 * For x >= 2, We approximate pzero by
 * 	pzero(x) = 1 + (R/S)
 * where  R = pR0 + pR1*s^2 + pR2*s^4 + ... + pR5*s^10
 * 	  S = 1 + pS0*s^2 + ... + pS4*s^10
 * and
 *	| pzero(x)-1-R/S | <= 2  ** ( -60.26)
 */

static const GENERIC pR8_000[6] = { /* [inf, 8] = 1/[0,0.125] */
	 0.00000000000000000000e+00,
	-7.03124999999900357484e-02,
	-8.08167041275349795626e+00,
	-2.57063105679704847262e+02,
	-2.48521641009428822144e+03,
	-5.25304380490729545272e+03,
};
static const GENERIC pS8_000[5] = {
	 1.16534364619668181717e+02,
	 3.83374475364121826715e+03,
	 4.05978572648472545552e+04,
	 1.16752972564375915681e+05,
	 4.76277284146730962675e+04,
};

static const GENERIC pR4_545[6] = { /*  [8,4.5454] = 1/[0.125,0.22001] */
	-1.14125464691894502584e-11,
	-7.03124940873599280078e-02,
	-4.15961064470587782438e+00,
	-6.76747652265167261021e+01,
	-3.31231299649172967747e+02,
	-3.46433388365604912451e+02,
};
static const GENERIC pS4_545[5] = {
	 6.07539382692300335975e+01,
	 1.05125230595704579173e+03,
	 5.97897094333855784498e+03,
	 9.62544514357774460223e+03,
	 2.40605815922939109441e+03,
};

static const GENERIC pR2_857[6] = {/* [4.547,2.8571] = 1/[0.2199,0.35001] */
	-2.54704601771951915620e-09,
	-7.03119616381481654654e-02,
	-2.40903221549529611423e+00,
	-2.19659774734883086467e+01,
	-5.80791704701737572236e+01,
	-3.14479470594888503854e+01,
};
static const GENERIC pS2_857[5] = {
	 3.58560338055209726349e+01,
	 3.61513983050303863820e+02,
	 1.19360783792111533330e+03,
	 1.12799679856907414432e+03,
	 1.73580930813335754692e+02,
};

static const GENERIC pR2_000[6] = {/* [2.8570,2]=1/[0.3499,0.5] */
	-8.87534333032526411254e-08,
	-7.03030995483624743247e-02,
	-1.45073846780952986357e+00,
	-7.63569613823527770791e+00,
	-1.11931668860356747786e+01,
	-3.23364579351335335033e+00,
};
static const GENERIC pS2_000[5] = {
	 2.22202997532088808441e+01,
	 1.36206794218215208048e+02,
	 2.70470278658083486789e+02,
	 1.53875394208320329881e+02,
	 1.46576176948256193810e+01,
};

/* x must range between 2 (inclusive) and infinity */
static GENERIC
pzero(GENERIC x) {
	GENERIC s,r,z;
	GENERIC z2,z4;
	GENERIC r1,r2,r3,s1,s2,s3;
	const GENERIC *pr,*ps; 
	int32_t hx;

	if (x > huge)
		return (one);

	GET_HIGH_WORD(hx,x);
	hx &= 0x7fffffff;
	     if (hx >= D8_000) {pr = pR8_000; ps = pS8_000;}
	else if (hx >= D4_545) {pr = pR4_545; ps = pS4_545;}
	else if (hx >= D2_857) {pr = pR2_857; ps = pS2_857;}
	else                   {pr = pR2_000; ps = pS2_000;}

	z  = one/(x*x);
	z2 = z*z;
	z4 = z2*z2;

	r1 = pr[0] + z*pr[1];
	r2 = pr[2] + z*pr[3]; 
	r3 = pr[4] + z*pr[5];

	s1 = one   + z*ps[0];
	s2 = ps[1] + z*ps[2];
	s3 = ps[3] + z*ps[4];

	r = r1 + z2*r2 + z4*r3;
	s = s1 + z2*s2 + z4*s3;
	
	return (one + r/s);
}

/* For x >= 8, the asymptotic expansions of qzero is
 *	-1/8 s + 75/1024 s^3 - ..., where s = 1/x.
 * We approximate pzero by
 * 	qzero(x) = s*(-1.25 + (R/S))
 * where  R = qR0 + qR1*s^2 + qR2*s^4 + ... + qR5*s^10
 * 	  S = 1 + qS0*s^2 + ... + qS5*s^12
 * and
 *	| qzero(x)/s +1.25-R/S | <= 2  ** ( -61.22)
 */

static const GENERIC qR8_000[6] = { /* [inf, 8] = 1/[0,0.125] */
	 0.00000000000000000000e+00,
	 7.32421874999935051953e-02,
	 1.17682064682252693899e+01,
	 5.57673380256401856059e+02,
	 8.85919720756468632317e+03,
	 3.70146267776887834771e+04,
};
static const GENERIC qS8_000[6] = {
	 1.63776026895689824414e+02,
	 8.09834494656449805916e+03,
	 1.42538291419120476348e+05, 
	 8.03309257119514397345e+05,
	 8.40501579819060512818e+05, 
	-3.43899293537866615225e+05,
};

static const GENERIC qR4_545[6] = { /* [8,4.5454] = 1/[0.125,0.22001] */
	 1.84085963594515531381e-11,
	 7.32421766612684765896e-02,
	 5.83563508962056953777e+00,
	 1.35111577286449829671e+02,
	 1.02724376596164097464e+03,
	 1.98997785864605384631e+03,
};
static const GENERIC qS4_545[6] = {
	 8.27766102236537761883e+01,
	 2.07781416421392987104e+03,
	 1.88472887785718085070e+04,
	 5.67511122894947329769e+04,
	 3.59767538425114471465e+04,
	-5.35434275601944773371e+03,
};

static const GENERIC qR2_857[6] = {/* [4.547,2.8571] = 1/[0.2199,0.35001] */
	 4.37741014089738620906e-09,
	 7.32411180042911447163e-02,
	 3.34423137516170720929e+00,
	 4.26218440745412650017e+01,
	 1.70808091340565596283e+02,
	 1.66733948696651168575e+02,
};
static const GENERIC qS2_857[6] = {
	 4.87588729724587182091e+01,
	 7.09689221056606015736e+02,
	 3.70414822620111362994e+03,
	 6.46042516752568917582e+03,
	 2.51633368920368957333e+03,
	-1.49247451836156386662e+02,
};

static const GENERIC qR2_000[6] = {/* [2.8570,2] = 1/[0.3499,0.5] */
	 1.50444444886983272379e-07, 
	 7.32234265963079278272e-02, 
	 1.99819174093815998816e+00, 
	 1.44956029347885735348e+01, 
	 3.16662317504781540833e+01, 
	 1.62527075710929267416e+01, 
};
static const GENERIC qS2_000[6] = {
	 3.03655848355219184498e+01, 
	 2.69348118608049844624e+02, 
	 8.44783757595320139444e+02, 
	 8.82935845112488550512e+02, 
	 2.12666388511798828631e+02, 
	-5.31095493882666946917e+00,
};

/* x must range between 2 (inclusive) and infinity */
static GENERIC
qzero(GENERIC x) {
	GENERIC s,r,z;
	GENERIC z2,z4,z6;
	GENERIC r1,r2,r3,s1,s2,s3;
	const GENERIC *qr,*qs; 
	int32_t hx;

	if (x > huge)
		return (-0.125/x);

	GET_HIGH_WORD(hx,x);
	hx &= 0x7fffffff;
	     if (hx >= D8_000) {qr = qR8_000; qs = qS8_000;}
	else if (hx >= D4_545) {qr = qR4_545; qs = qS4_545;}
	else if (hx >= D2_857) {qr = qR2_857; qs = qS2_857;}
	else                   {qr = qR2_000; qs = qS2_000;}

	z  = one/(x*x);
	z2 = z*z;
	z4 = z2*z2;
	z6 = z4*z2;

	r1 = qr[0] + z*qr[1];
	r2 = qr[2] + z*qr[3]; 
	r3 = qr[4] + z*qr[5]; 

	s1 = one   + z*qs[0];
	s2 = qs[1] + z*qs[2];
	s3 = qs[3] + z*qs[4];

	r = r1 + z2*r2 + z4*r3;
	s = s1 + z2*s2 + z4*s3 + z6*qs[5];

	return ((-.125 + r/s)/x);
}
