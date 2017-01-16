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
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */


#pragma weak expf = __expf

/* INDENT OFF */
/*
 * float expf(float x);
 * Code by K.C. Ng for SUN 5.0 libmopt
 * 11/5/99
 * Method :
 *	1. For |x| >= 2^7, either underflow/overflow.
 *	   More precisely:
 *		x > 88.722839355...(0x42B17218) => overflow;
 *		x < -103.97207642..(0xc2CFF1B4) => underflow.
 *	2. For |x| <  2^-6, use polynomail
 *		exp(x) = 1 + x + p1*x^2 + p2*x^3
 *      3. Otherwise, write |x|=(1+r)*2^n, where 0<=r<1.
 *	   Let t = 2^n * (1+r) .... x > 0;
 *	       t = 2^n * (1-r) .... x < 0. (x= -2**(n+1)+t)
 *	   Since -6 <= n <= 6, we may break t into
 *	   six 6-bits chunks:
 *                    -5     -11     -17     -23     -29
 *         t=j *2+j *2  +j *2   +j *2   +j *2   +j *2
 *            1    2      3       4       5       6
 *
 *	   where 0 <= j  < 64 for i = 1,...,6.
 *		       i
 *	   Note that since t has only 24 significant bits,
 *	   either j  or j  must be 0.
 *		   1     6
 *					       7-6i
 *	   One may define j  by   (int) ( t * 2     ) mod 64
 *			   i
 *	   mathematically. In actual implementation, they can
 *	   be obtained by manipulating the exponent and
 *	   mantissa bits as follow:
 *		Let ix = (HEX(x)&0x007fffff)|0x00800000.
 *		If n>=0, let ix=ix<<n, then j =0 and
 *					     6
 *		    j  = ix>>(30-6i)) mod 64  ...i=1,...,5
 *		     i
 *		Otherwise, let ix=ix<<(j+6), then j = 0 and
 *						   1
 *		    j  = ix>>(36-6i)) mod 64  ...i=2,...,6
 *		     i
 *
 *	4. Compute exp(t) by table look-up method.
 *	   Precompute ET[k] = exp(j*2^(7-6i)), k=j+64*(6-i).
 *	   Then
 *	   exp(t) = ET[j +320]*ET[j +256]*ET[j +192]*
 *		        1          2          3
 *
 *		    ET[j +128]*ET[j +64]*ET[j ]
 *			4          5         6
 *
 *				  n+1
 *	5. If x < 0, return exp(-2   )* exp(t). Note that
 *	   -6 <= n <= 6. Let k = n - 6, then we can
 *	   precompute
 *	                 k-5          n+1
 *         EN[k] = exp(-2   ) = exp(-2   ) for k=0,1,...,12.
 *
 *
 * Special cases:
 *	exp(INF) is INF, exp(NaN) is NaN;
 *	exp(-INF) = 0;
 *	for finite argument, only exp(0) = 1 is exact.
 *
 * Accuracy:
 *      All calculations are done in double precision except for
 *      the case |x| < 2^-6.  When |x| < 2^-6, the error is less
 *      than 0.55 ulp.  When |x| >= 2^-6 and the result is normal,
 *      the error is less than 0.51 ulp.  When FDTOS_TRAPS_... is
 *      defined and the result is subnormal, the error can be as
 *      large as 0.75 ulp.
 */
/* INDENT ON */

#include "libm.h"

/*
 * ET[k] = exp(j*2^(7-6i)) , where j = k mod 64, i = k/64
 */
static const double ET[] = {
	1.00000000000000000000e+00, 1.00000000186264514923e+00,
	1.00000000372529029846e+00, 1.00000000558793544769e+00,
	1.00000000745058059692e+00, 1.00000000931322574615e+00,
	1.00000001117587089539e+00, 1.00000001303851604462e+00,
	1.00000001490116119385e+00, 1.00000001676380656512e+00,
	1.00000001862645171435e+00, 1.00000002048909686359e+00,
	1.00000002235174201282e+00, 1.00000002421438716205e+00,
	1.00000002607703253332e+00, 1.00000002793967768255e+00,
	1.00000002980232283178e+00, 1.00000003166496798102e+00,
	1.00000003352761335229e+00, 1.00000003539025850152e+00,
	1.00000003725290365075e+00, 1.00000003911554879998e+00,
	1.00000004097819417126e+00, 1.00000004284083932049e+00,
	1.00000004470348446972e+00, 1.00000004656612984100e+00,
	1.00000004842877499023e+00, 1.00000005029142036150e+00,
	1.00000005215406551073e+00, 1.00000005401671088201e+00,
	1.00000005587935603124e+00, 1.00000005774200140252e+00,
	1.00000005960464655175e+00, 1.00000006146729192302e+00,
	1.00000006332993707225e+00, 1.00000006519258244353e+00,
	1.00000006705522759276e+00, 1.00000006891787296404e+00,
	1.00000007078051811327e+00, 1.00000007264316348454e+00,
	1.00000007450580863377e+00, 1.00000007636845400505e+00,
	1.00000007823109937632e+00, 1.00000008009374452556e+00,
	1.00000008195638989683e+00, 1.00000008381903526811e+00,
	1.00000008568168063938e+00, 1.00000008754432578861e+00,
	1.00000008940697115989e+00, 1.00000009126961653116e+00,
	1.00000009313226190244e+00, 1.00000009499490705167e+00,
	1.00000009685755242295e+00, 1.00000009872019779422e+00,
	1.00000010058284316550e+00, 1.00000010244548853677e+00,
	1.00000010430813368600e+00, 1.00000010617077905728e+00,
	1.00000010803342442856e+00, 1.00000010989606979983e+00,
	1.00000011175871517111e+00, 1.00000011362136054238e+00,
	1.00000011548400591366e+00, 1.00000011734665128493e+00,
	1.00000000000000000000e+00, 1.00000011920929665621e+00,
	1.00000023841860752327e+00, 1.00000035762793260119e+00,
	1.00000047683727188996e+00, 1.00000059604662538959e+00,
	1.00000071525599310007e+00, 1.00000083446537502141e+00,
	1.00000095367477115360e+00, 1.00000107288418149665e+00,
	1.00000119209360605055e+00, 1.00000131130304481530e+00,
	1.00000143051249779091e+00, 1.00000154972196497738e+00,
	1.00000166893144637470e+00, 1.00000178814094198287e+00,
	1.00000190735045180190e+00, 1.00000202655997583179e+00,
	1.00000214576951407253e+00, 1.00000226497906652412e+00,
	1.00000238418863318657e+00, 1.00000250339821405987e+00,
	1.00000262260780914403e+00, 1.00000274181741843904e+00,
	1.00000286102704194491e+00, 1.00000298023667966163e+00,
	1.00000309944633158921e+00, 1.00000321865599772764e+00,
	1.00000333786567807692e+00, 1.00000345707537263706e+00,
	1.00000357628508140806e+00, 1.00000369549480438991e+00,
	1.00000381470454158261e+00, 1.00000393391429298617e+00,
	1.00000405312405860059e+00, 1.00000417233383842586e+00,
	1.00000429154363246198e+00, 1.00000441075344070896e+00,
	1.00000452996326316679e+00, 1.00000464917309983548e+00,
	1.00000476838295071502e+00, 1.00000488759281580542e+00,
	1.00000500680269510667e+00, 1.00000512601258861878e+00,
	1.00000524522249634174e+00, 1.00000536443241827556e+00,
	1.00000548364235442023e+00, 1.00000560285230477575e+00,
	1.00000572206226934213e+00, 1.00000584127224811937e+00,
	1.00000596048224110746e+00, 1.00000607969224830640e+00,
	1.00000619890226971620e+00, 1.00000631811230533685e+00,
	1.00000643732235516836e+00, 1.00000655653241921073e+00,
	1.00000667574249746394e+00, 1.00000679495258992802e+00,
	1.00000691416269660294e+00, 1.00000703337281748873e+00,
	1.00000715258295258536e+00, 1.00000727179310189285e+00,
	1.00000739100326541120e+00, 1.00000751021344314040e+00,
	1.00000000000000000000e+00, 1.00000762942363508046e+00,
	1.00001525890547848796e+00, 1.00002288844553022251e+00,
	1.00003051804379095024e+00, 1.00003814770026133729e+00,
	1.00004577741494138365e+00, 1.00005340718783175546e+00,
	1.00006103701893311886e+00, 1.00006866690824547383e+00,
	1.00007629685576948653e+00, 1.00008392686150582307e+00,
	1.00009155692545448346e+00, 1.00009918704761613384e+00,
	1.00010681722799144033e+00, 1.00011444746658040295e+00,
	1.00012207776338368781e+00, 1.00012970811840196106e+00,
	1.00013733853163522269e+00, 1.00014496900308413885e+00,
	1.00015259953274937565e+00, 1.00016023012063093311e+00,
	1.00016786076672947736e+00, 1.00017549147104567453e+00,
	1.00018312223357952462e+00, 1.00019075305433191581e+00,
	1.00019838393330284809e+00, 1.00020601487049298761e+00,
	1.00021364586590300050e+00, 1.00022127691953288675e+00,
	1.00022890803138353455e+00, 1.00023653920145494389e+00,
	1.00024417042974778091e+00, 1.00025180171626271175e+00,
	1.00025943306099973640e+00, 1.00026706446395974304e+00,
	1.00027469592514273167e+00, 1.00028232744454959047e+00,
	1.00028995902218031944e+00, 1.00029759065803558471e+00,
	1.00030522235211605242e+00, 1.00031285410442172257e+00,
	1.00032048591495348333e+00, 1.00032811778371155675e+00,
	1.00033574971069616488e+00, 1.00034338169590819589e+00,
	1.00035101373934764979e+00, 1.00035864584101541475e+00,
	1.00036627800091149076e+00, 1.00037391021903676602e+00,
	1.00038154249539146257e+00, 1.00038917482997580244e+00,
	1.00039680722279067382e+00, 1.00040443967383629875e+00,
	1.00041207218311289928e+00, 1.00041970475062136359e+00,
	1.00042733737636191371e+00, 1.00043497006033499375e+00,
	1.00044260280254104778e+00, 1.00045023560298029786e+00,
	1.00045786846165363215e+00, 1.00046550137856127272e+00,
	1.00047313435370366363e+00, 1.00048076738708124900e+00,
	1.00000000000000000000e+00, 1.00048840047869447289e+00,
	1.00097703949241645383e+00, 1.00146591715766675179e+00,
	1.00195503359100279717e+00, 1.00244438890903908579e+00,
	1.00293398322844673487e+00, 1.00342381666595459322e+00,
	1.00391388933834746489e+00, 1.00440420136246855165e+00,
	1.00489475285521656645e+00, 1.00538554393354861993e+00,
	1.00587657471447822211e+00, 1.00636784531507639251e+00,
	1.00685935585247099411e+00, 1.00735110644384739942e+00,
	1.00784309720644804642e+00, 1.00833532825757243856e+00,
	1.00882779971457803292e+00, 1.00932051169487890796e+00,
	1.00981346431594687374e+00, 1.01030665769531102782e+00,
	1.01080009195055753324e+00, 1.01129376719933050666e+00,
	1.01178768355933157430e+00, 1.01228184114831898377e+00,
	1.01277624008410960244e+00, 1.01327088048457714109e+00,
	1.01376576246765282008e+00, 1.01426088615132625748e+00,
	1.01475625165364347069e+00, 1.01525185909270931894e+00,
	1.01574770858668572693e+00, 1.01624380025379235093e+00,
	1.01674013421230657883e+00, 1.01723671058056375216e+00,
	1.01773352947695694404e+00, 1.01823059101993673714e+00,
	1.01872789532801233392e+00, 1.01922544251975000229e+00,
	1.01972323271377418585e+00, 1.02022126602876750390e+00,
	1.02071954258347008526e+00, 1.02121806249668067856e+00,
	1.02171682588725554197e+00, 1.02221583287410910934e+00,
	1.02271508357621376817e+00, 1.02321457811260052573e+00,
	1.02371431660235789884e+00, 1.02421429916463280207e+00,
	1.02471452591863054771e+00, 1.02521499698361440167e+00,
	1.02571571247890602763e+00, 1.02621667252388526492e+00,
	1.02671787723799012859e+00, 1.02721932674071725344e+00,
	1.02772102115162167202e+00, 1.02822296059031659254e+00,
	1.02872514517647339893e+00, 1.02922757502982276101e+00,
	1.02973025027015285815e+00, 1.03023317101731093359e+00,
	1.03073633739120262831e+00, 1.03123974951179242510e+00,
	1.00000000000000000000e+00, 1.03174340749910276038e+00,
	1.06449445891785954288e+00, 1.09828514030782575794e+00,
	1.13314845306682632220e+00, 1.16911844616950433284e+00,
	1.20623024942098067136e+00, 1.24452010776609522935e+00,
	1.28402541668774139438e+00, 1.32478475872886569675e+00,
	1.36683794117379631139e+00, 1.41022603492571074746e+00,
	1.45499141461820125087e+00, 1.50117780000012279729e+00,
	1.54883029863413312910e+00, 1.59799544995063325104e+00,
	1.64872127070012819416e+00, 1.70105730184840076014e+00,
	1.75505465696029849809e+00, 1.81076607211938722664e+00,
	1.86824595743222232613e+00, 1.92755045016754467113e+00,
	1.98873746958229191684e+00, 2.05186677348797674725e+00,
	2.11700001661267478426e+00, 2.18420081081561789915e+00,
	2.25353478721320854561e+00, 2.32506966027712103084e+00,
	2.39887529396709808793e+00, 2.47502376996302508871e+00,
	2.55358945806292680913e+00, 2.63464908881563086851e+00,
	2.71828182845904553488e+00, 2.80456935623722669604e+00,
	2.89359594417176113623e+00, 2.98544853936535581340e+00,
	3.08021684891803104733e+00, 3.17799342753883840018e+00,
	3.27887376793867346692e+00, 3.38295639409246895468e+00,
	3.49034295746184142217e+00, 3.60113833627217561073e+00,
	3.71545073794110392029e+00, 3.83339180475841034834e+00,
	3.95507672292057721464e+00, 4.08062433502646015882e+00,
	4.21015725614395996956e+00, 4.34380199356104235164e+00,
	4.48168907033806451778e+00, 4.62395315278208052234e+00,
	4.77073318196760265408e+00, 4.92217250943229078786e+00,
	5.07841903718008147450e+00, 5.23962536212848917216e+00,
	5.40594892514116676097e+00, 5.57755216479125959239e+00,
	5.75460267600573072144e+00, 5.93727337374560715233e+00,
	6.12574266188198635064e+00, 6.32019460743274397174e+00,
	6.52081912033011246166e+00, 6.72781213889469142941e+00,
	6.94137582119703555605e+00, 7.16171874249371143151e+00,
	1.00000000000000000000e+00, 7.38905609893065040694e+00,
	5.45981500331442362040e+01, 4.03428793492735110249e+02,
	2.98095798704172830185e+03, 2.20264657948067178950e+04,
	1.62754791419003915507e+05, 1.20260428416477679275e+06,
	8.88611052050787210464e+06, 6.56599691373305097222e+07,
	4.85165195409790277481e+08, 3.58491284613159179688e+09,
	2.64891221298434715271e+10, 1.95729609428838775635e+11,
	1.44625706429147509766e+12, 1.06864745815244628906e+13,
	7.89629601826806875000e+13, 5.83461742527454875000e+14,
	4.31123154711519500000e+15, 3.18559317571137560000e+16,
	2.35385266837020000000e+17, 1.73927494152050099200e+18,
	1.28516001143593082880e+19, 9.49611942060244828160e+19,
	7.01673591209763143680e+20, 5.18470552858707204506e+21,
	3.83100800071657691546e+22, 2.83075330327469394756e+23,
	2.09165949601299610311e+24, 1.54553893559010391826e+25,
	1.14200738981568423454e+26, 8.43835666874145383188e+26,
	6.23514908081161674391e+27, 4.60718663433129178064e+28,
	3.40427604993174075827e+29, 2.51543867091916687979e+30,
	1.85867174528412788702e+31, 1.37338297954017610775e+32,
	1.01480038811388874615e+33, 7.49841699699012090701e+33,
	5.54062238439350983445e+34, 4.09399696212745451138e+35,
	3.02507732220114256223e+36, 2.23524660373471497416e+37,
	1.65163625499400180987e+38, 1.22040329431784083418e+39,
	9.01762840503429851945e+39, 6.66317621641089618500e+40,
	4.92345828601205826106e+41, 3.63797094760880474988e+42,
	2.68811714181613560943e+43, 1.98626483613765434356e+44,
	1.46766223015544238535e+45, 1.08446385529002313207e+46,
	8.01316426400059069850e+46, 5.92097202766466993617e+47,
	4.37503944726134096988e+48, 3.23274119108485947460e+49,
	2.38869060142499127023e+50, 1.76501688569176554670e+51,
	1.30418087839363225614e+52, 9.63666567360320166416e+52,
	7.12058632688933793173e+53, 5.26144118266638596909e+54,
};

/*
 * EN[k] = exp(-2^(k-5))
 */
static const double EN[] = {
	9.69233234476344129860e-01, 9.39413062813475807644e-01,
	8.82496902584595455110e-01, 7.78800783071404878477e-01,
	6.06530659712633424263e-01, 3.67879441171442334024e-01,
	1.35335283236612702318e-01, 1.83156388887341786686e-02,
	3.35462627902511853224e-04, 1.12535174719259116458e-07,
	1.26641655490941755372e-14, 1.60381089054863792659e-28,
#if defined(FDTOS_TRAPS_INCOMPLETE_IN_FNS_MODE)
	2.96555550007072683578e-38,	/* exp(-128) scaled up by 2^60 */
#else
	2.57220937264241481170e-56,
#endif
};

static const float F[] = {
	0.0f,
	1.0f,
	5.0000000951292138e-01F,
	1.6666518897347284e-01F,
	3.4028234663852885981170E+38F,
	1.1754943508222875079688E-38F,
#if defined(FDTOS_TRAPS_INCOMPLETE_IN_FNS_MODE)
	8.67361737988403547205962240695953369140625e-19F
#endif
};

#define	zero	F[0]
#define	one	F[1]
#define	p1	F[2]
#define	p2	F[3]
#define	big	F[4]
#define	tiny	F[5]
#if defined(FDTOS_TRAPS_INCOMPLETE_IN_FNS_MODE)
#define	twom60	F[6]
#endif

float
expf(float xf) {
	double	w, p, q;
	int	hx, ix, n;

	hx = *(int *)&xf;
	ix = hx & ~0x80000000;

	if (ix < 0x3c800000) {	/* |x| < 2**-6 */
		if (ix < 0x38800000)	/* |x| < 2**-14 */
			return (one + xf);
		return (one + (xf + (xf * xf) * (p1 + xf * p2)));
	}

	n = ix >> 23;		/* biased exponent */

	if (n >= 0x86) {	/* |x| >= 2^7 */
		if (n >= 0xff) {	/* x is nan of +-inf */
			if (hx == 0xff800000)
				return (zero);	/* exp(-inf)=0 */
			return (xf * xf);	/* exp(nan/inf) is nan or inf */
		}
		if (hx > 0)
			return (big * big);	/* overflow */
		else
			return (tiny * tiny);	/* underflow */
	}

	ix -= n << 23;
	if (hx > 0)
		ix += 0x800000;
	else
		ix = 0x800000 - ix;
	if (n >= 0x7f) {	/* n >= 0 */
		ix <<= n - 0x7f;
		w = ET[(ix & 0x3f) + 64] * ET[((ix >> 6) & 0x3f) + 128];
		p = ET[((ix >> 12) & 0x3f) + 192] *
		    ET[((ix >> 18) & 0x3f) + 256];
		q = ET[((ix >> 24) & 0x3f) + 320];
	} else {
		ix <<= n - 0x79;
		w = ET[ix & 0x3f] * ET[((ix >> 6) & 0x3f) + 64];
		p = ET[((ix >> 12) & 0x3f) + 128] *
		    ET[((ix >> 18) & 0x3f) + 192];
		q = ET[((ix >> 24) & 0x3f) + 256];
	}
	xf = (float)((w * p) * (hx < 0 ? q * EN[n - 0x79] : q));
#if defined(FDTOS_TRAPS_INCOMPLETE_IN_FNS_MODE)
	if ((unsigned)hx >= 0xc2800000u) {
		if ((unsigned)hx >= 0xc2aeac50) { /* force underflow */
			volatile float	t = tiny;
			t *= t;
		}
		return (xf * twom60);
	}
#endif
	return (xf);
}
