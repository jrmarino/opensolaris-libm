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
 * of order zero: j1(x),y1(x);
 *
 * Special cases:
 *	y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *	y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 */

#pragma weak __j1 = j1
#pragma weak __y1 = y1

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
#define MINISCULE_Y1	0x3C900000	/* 2^-54 == 5.55e-17 */

#define GENERIC double
static const GENERIC
zero    = 0.0,
one	= 1.0,
huge	= 1.0e10,
ginormous= 1.0e300,
invsqrtpi= 5.641895835477562869480794515607725858441e-0001,
tpi	= 0.636619772367581343075535053490057448;

static GENERIC pone(GENERIC), qone(GENERIC);
static const GENERIC r0[4] = {	/* [0, 2.0] */
	-6.25000000000000000000e-02,
	 1.40705666955189706048e-03,
	-1.59955631084035597520e-05,
	 4.96727999609584448412e-08,
};
static const GENERIC s0[6] = {
	 0.0,
	 1.91537599538363460805e-02,
	 1.85946785588630915560e-04,
	 1.17718464042623683263e-06,
	 5.04636257076217042715e-09,
	 1.23542274426137913908e-11,
};

GENERIC
j1(GENERIC x) {
	GENERIC y,z,s,c,ss,cc,r;
	GENERIC z2,z4;
	GENERIC r1,r2,s1,s2,s3;
	int32_t hx;

	if (!finite(x))
		return (one/x);

	GET_HIGH_WORD(hx,x);
	hx &= 0x7fffffff;
	y = fabs(x);

	if (hx >= D2_000) {
		s = sin(y);
		c = cos(y);
	/*
	 * j1(x) = sqrt(2/(pi*x))*(p1(x)*cos(x0)-q1(x)*sin(x0))
	 * where x0 = x-3pi/4
	 * 	Better formula:
	 *		cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
	 *			=  1/sqrt(2) * (sin(x) - cos(x))
	 *		sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
	 *			= -1/sqrt(2) * (cos(x) + sin(x))
	 * To avoid cancellation, use
	 *		sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
	 * to compute the worse one.
	 */
		if (hx >= DOF_LIMIT) { /* x+x may overflow if x >= 8.99e307 */
			ss = -s - c;
			cc =  s - c;
		} else if(signbit(s) != signbit(c)) {
			cc = s - c;
			ss = cos(y+y)/cc;
		} else {
			ss = -s - c;
			cc = cos(y+y)/ss;
		}
	/*
	 * j1(x) = 1/sqrt(pi*x) * (P(1,x)*cc - Q(1,x)*ss)
	 * y1(x) = 1/sqrt(pi*x) * (P(1,x)*ss + Q(1,x)*cc)
	 */
		if(hx > D6_805E38)
		    z = (invsqrtpi*cc)/sqrt(y);
		else
                    z =  invsqrtpi*(pone(y)*cc-qone(y)*ss)/sqrt(y);

                if (x > X_TLOSS) {
			if (hx < 0) {z = -z; y = -y;}
			return (_SVID_libm_err(y, z, 36));
                } else {
			if (hx < 0)
				return (-z);
			else
				return (z);
		}
	}
	if(hx < MINISCULE) {
		if (ginormous + x > one) { /* raise inexact if x != 0 */
			return (0.5*x);
		}
	}
	z  = x*x;
	z2 = z*z;
	z4 = z2*z2;

	r1 = z*r0[0];
	r2 = r0[1] + z*r0[2];

	s1 = one   + z*s0[1];
	s2 = s0[2] + z*s0[3];
	s3 = s0[4] + z*s0[5];

	r = x*(r1 + z2*r2 + z4*r0[3]);
	s = s1 + z2*s2 + z4*s3;

	return (0.5*x + r/s);
}

static const GENERIC u0[5] = {
	-1.96057090646238940668e-01,
	 5.04438716639811282616e-02,
	-1.91256895875763547298e-03,
	 2.35252600561610495928e-05,
	-9.19099158039878874504e-08,
};
static const GENERIC v0[5] = {
	 1.99167318236649903973e-02,
	 2.02552581025135171496e-04,
	 1.35608801097516229404e-06,
	 6.22741452364621501295e-09,
	 1.66559246207992079114e-11,
};

GENERIC
y1(GENERIC x) {
	GENERIC z,s,c,ss,cc,u,v;
	int32_t hx;

	if (isnan(x))
		return (x*x);	/* + -> * for Cheetah */
	if(x <= zero){
		if(x==zero)
		    /* return -one/zero;  */
		    return (_SVID_libm_err(x, x, 10));
		else
		    /* return zero/zero; */
		    return (_SVID_libm_err(x, x, 11));
	}

	GET_HIGH_WORD(hx,x);
	hx &= 0x7fffffff;

	if (hx >= D2_000) {
		if (!finite(x))
			return (zero);
		s = sin(x);
		c = cos(x);
	/*
	 * j1(x) = sqrt(2/(pi*x))*(p1(x)*cos(x0)-q1(x)*sin(x0))
	 * where x0 = x-3pi/4
	 * 	Better formula:
	 *		cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
	 *			=  1/sqrt(2) * (sin(x) - cos(x))
	 *		sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
	 *			= -1/sqrt(2) * (cos(x) + sin(x))
	 * To avoid cancellation, use
	 *		sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
	 * to compute the worse one.
	 */
		if (hx >= DOF_LIMIT) { /* x+x may overflow if x >= 8.99e307 */
			ss = -s - c;
			cc =  s - c;
		} else if(signbit(s) != signbit(c)) {
			cc = s - c;
			ss = cos(x+x)/cc;
		} else {
			ss = -s - c;
			cc = cos(x+x)/ss;
		}
	/*
	 * j1(x) = 1/sqrt(pi*x) * (P(1,x)*cc - Q(1,x)*ss)
	 * y1(x) = 1/sqrt(pi*x) * (P(1,x)*ss + Q(1,x)*cc)
	 */
		if (hx > D6_805E38)
		    z =  (invsqrtpi*ss)/sqrt(x);
		else
                    z = invsqrtpi*(pone(x)*ss+qone(x)*cc)/sqrt(x);

                if (x > X_TLOSS)
			return (_SVID_libm_err(x, z, 37));
                else
			return (z);
	}
        if(hx <= MINISCULE_Y1) {
            return(-tpi/x);
        }
	z  = x*x;
	u = u0[0] + z*(u0[1] + z*(u0[2] + z*(u0[3] + z*u0[4])));
	v = one + z*(v0[0] + z*(v0[1] + z*(v0[2] + z*(v0[3] + z*v0[4]))));
	return (x*(u/v) + tpi*(j1(x)*log(x) - one/x));
}

/* For x >= 8, the asymptotic expansions of pone is
 *	1 + 15/128 s^2 - 4725/2^15 s^4 - ...,	where s = 1/x.
 * We approximate pone by
 *	pone(x) = 1 + (R/S)
 * where  R = pr0 + pr1*s^2 + pr2*s^4 + ... + pr5*s^10
 *	  S = 1 + ps0*s^2 + ... + ps4*s^10
 * and
 *	| pone(x)-1-R/S | <= 2  ** ( -60.06)
 */

static const GENERIC pR8_000[6] = { /* [inf, 8] = 1/[0,0.125] */
	 0.00000000000000000000e+00,
	 1.17187499999988647970e-01,
	 1.32394806593073575129e+01,
	 4.12051854307378562225e+02,
	 3.87474538913960532227e+03,
	 7.91447954031891731574e+03,
};
static const GENERIC pS8_000[5] = {
	 1.14207370375678408436e+02, 
	 3.65093083420853463394e+03,
	 3.69562060269033463555e+04,
	 9.76027935934950801311e+04,
	 3.08042720627888811578e+04,
};

static const GENERIC pR4_545[6] = { /*  [8,4.5454] = 1/[0.125,0.22001] */
	 1.31990519556243522749e-11,
	 1.17187493190614097638e-01,
	 6.80275127868432871736e+00,
	 1.08308182990189109773e+02,
	 5.17636139533199752805e+02,
	 5.28715201363337541807e+02,
};
static const GENERIC pS4_545[5] = {
	 5.92805987221131331921e+01,
	 9.91401418733614377743e+02,
	 5.35326695291487976647e+03,
	 7.84469031749551231769e+03,
	 1.50404688810361062679e+03,
};

static const GENERIC pR2_857[6] = {/* [4.547,2.8571] = 1/[0.2199,0.35001] */
	 3.02503916137373618024e-09,
	 1.17186865567253592491e-01,
	 3.93297750033315640650e+00,
	 3.51194035591636932736e+01,
	 9.10550110750781271918e+01,
	 4.85590685197364919645e+01,
};
static const GENERIC pS2_857[5] = {
	 3.47913095001251519989e+01,
	 3.36762458747825746741e+02,
	 1.04687139975775130551e+03,
	 8.90811346398256432622e+02,
	 1.03787932439639277504e+02,
};

static const GENERIC pR2_000[6] = {/* [2.8570,2]=1/[0.3499,0.5] */
	 1.07710830106873743082e-07,
	 1.17176219462683348094e-01,
	 2.36851496667608785174e+00,
	 1.22426109148261232917e+01,
	 1.76939711271687727390e+01,
	 5.07352312588818499250e+00,
};
static const GENERIC pS2_000[5] = {
	 2.14364859363821409488e+01,
	 1.25290227168402751090e+02,
	 2.32276469057162813669e+02,
	 1.17679373287147100768e+02,
	 8.36463893371618283368e+00,
};

/* x must range between 2 (inclusive) and infinity */
static GENERIC
pone(GENERIC x) {
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

/* For x >= 8, the asymptotic expansions of qone is
 *	3/8 s - 105/1024 s^3 - ..., where s = 1/x.
 * We approximate pone by
 *	qone(x) = s*(0.375 + (R/S))
 * where  R = qr1*s^2 + qr2*s^4 + ... + qr5*s^10
 *	  S = 1 + qs1*s^2 + ... + qs6*s^12
 * and
 *	| qone(x)/s -0.375-R/S | <= 2  ** ( -61.13)
 */

static const GENERIC qR8_000[6] = { /* [inf, 8] = 1/[0,0.125] */
	 0.00000000000000000000e+00,
	-1.02539062499992714161e-01,
	-1.62717534544589987888e+01,
	-7.59601722513950107896e+02,
	-1.18498066702429587167e+04,
	-4.84385124285750353010e+04,
};
static const GENERIC qS8_000[6] = {
	 1.61395369700722909556e+02,
	 7.82538599923348465381e+03,
	 1.33875336287249578163e+05,
	 7.19657723683240939863e+05,
	 6.66601232617776375264e+05,
	-2.94490264303834643215e+05,
};

static const GENERIC qR4_545[6] = { /* [8,4.5454] = 1/[0.125,0.22001] */
	-2.08979931141764104297e-11,
	-1.02539050241375426231e-01,
	-8.05644828123936029840e+00,
	-1.83669607474888380239e+02,
	-1.37319376065508163265e+03,
	-2.61244440453215656817e+03,
};
static const GENERIC qS4_545[6] = {
	 8.12765501384335777857e+01,
	 1.99179873460485964642e+03,
	 1.74684851924908907677e+04,
	 4.98514270910352279316e+04,
	 2.79480751638918118260e+04, 
	-4.71918354795128470869e+03,
};

static const GENERIC qR2_857[6] = {/* [4.547,2.8571] = 1/[0.2199,0.35001] */
	-5.07831226461766561369e-09, 
	-1.02537829820837089745e-01, 
	-4.61011581139473403113e+00,
	-5.78472216562783643212e+01,
	-2.28244540737631695038e+02,
	-2.19210128478909325622e+02,
};
static const GENERIC qS2_857[6] = {
	 4.76651550323729509273e+01,
	 6.73865112676699709482e+02, 
	 3.38015286679526343505e+03,
	 5.54772909720722782367e+03,
	 1.90311919338810798763e+03,
	-1.35201191444307340817e+02,
};

static const GENERIC qR2_000[6] = {/* [2.8570,2] = 1/[0.3499,0.5] */
	-1.78381727510958865572e-07,
	-1.02517042607985553460e-01,
	-2.75220568278187460720e+00,
	-1.96636162643703720221e+01,
	-4.23253133372830490089e+01,
	-2.13719211703704061733e+01,
};
static const GENERIC qS2_000[6] = {
	 2.95333629060523854548e+01,
	 2.52981549982190529136e+02,
	 7.57502834868645436472e+02,
	 7.39393205320467245656e+02,
	 1.55949003336666123687e+02,
	-4.95949898822628210127e+00,
};

/* x must range between 2 (inclusive) and infinity */
static GENERIC
qone(GENERIC x) {
	GENERIC s,r,z;
	GENERIC z2,z4,z6;
	GENERIC r1,r2,r3,s1,s2,s3;
	const GENERIC *qr,*qs; 
	int32_t hx;

	if (x > huge)
		return (0.375/x);

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

	return ((0.375 + r/s)/x);
}
