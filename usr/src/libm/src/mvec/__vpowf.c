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


#ifdef __RESTRICT
#define restrict _Restrict
#else
#define restrict
#endif

/* float powf(float x, float y)
 *
 * Method :
 *	1. Special cases:
 *	for (anything) ** 0					=> 1
 *		for (anything) ** NaN				=> QNaN + invalid
 *		for NaN ** (anything)				=> QNaN + invalid
 *		for +-1 ** +-Inf				=> QNaN + invalid
 *		for +-(|x| < 1) ** +Inf				=> +0
 *		for +-(|x| < 1) ** -Inf				=> +Inf
 *		for +-(|x| > 1) ** +Inf				=> +Inf
 *		for +-(|x| > 1) ** -Inf				=> +0
 *		for +Inf ** (negative)				=> +0
 *		for +Inf ** (positive)				=> +Inf
 *		for -Inf ** (negative except odd integer)	=> +0
 *		for -Inf ** (negative odd integer)		=> -0
 *		for -Inf ** (positive except odd integer)	=> +Inf
 *		for -Inf ** (positive odd integer)		=> -Inf
 *		for (negative) ** (non-integer)			=> QNaN + invalid
 *		for +0 ** (negative)				=> +Inf + overflow
 *		for +0 ** (positive)				=> +0
 *		for -0 ** (negative except odd integer)		=> +Inf + overflow
 *		for -0 ** (negative odd integer)		=> -Inf + overflow
 *		for -0 ** (positive except odd integer)		=> +0
 *		for -0 ** (positive odd integer)		=> -0
 *	2. Computes x**y from:
 *		x**y = 2**(y*log2(x)) = 2**(w/256), where w = 256*log2(|x|)*y.
 *	3. Computes w = 256 * log2(|x|) * y from
 *		|x| = m * 2**n => log2(|x|) = n + log2(m).
 *	Let m = m0 + dm, where m0 = 1 + k / 128,
 *		k = [0, 128],
 *		dm = [-1/256, 1/256].
 *	Then 256*log2(m) = 256*log2(m0 + dm) = 256*log2(m0) + 256*log2(1+z),
 *		where z = dm*(1/m0), z = [-1/258, 1/256].
 *	Then
 *		1/m0 is looked up in a table of 1, 1/(1+1/128), ..., 1/(1+128/128).
 *		256*log2(m0) is looked up in a table of 256*log2(1), 256*log2(1+1/128),
 *			..., 256*log2(1+128/128).
 *		256*log2(1+z) is computed using approximation:
 *			256*log2(1+z) = (((a3*z + a2)*z + a1)*z + a0)*z.
 *	3. For w >= 32768
 *		then for (negative) ** (odd integer)		=> -Inf + overflow
 *		else						=> +Inf + overflow
 *	For w <= -38400
 *		then for (negative) ** (odd integer)		=> -0 + underflow
 *		else						=> +0 + underflow
 *	4. Computes 2 ** (w/256) from:
 *		2 ** (w/256) = 2**a  *  2**(k/256)  *  2**(r/256)
 *	Where:
 *		a    =    int  ( w ) >> 8;
 *		k    =    int  ( w ) & 0xFF;
 *		r    =    frac ( w ).
 *	Note that:
 *		k = 0, 1, ..., 255;
 *		r = (-1, 1).
 *	Then:
 *		2**(k/256) is looked up in a table of 2**0, 2**1/256, ...
 *		2**(r/256) is computed using approximation:
 *			2**(r/256) =  a0 + a1 * r + a2 * r**2
 *		Multiplication by 2**a is done by adding "a" to
 *		the biased exponent.
 *	5. For (negative) ** (odd integer)	=> -(2**(w/256))
 *	otherwise				=>   2**(w/256)
 *
 * Accuracy:
 *	Max. relative aproximation error < 2**(-37.35) for 256*log2(1+z).
 *	Max. relative aproximation error < 2**(-29.18) for 2**(r/256).
 *	All calculations are done in double precision.
 *	Maximum error observed: less than 0.528 ulp after 700.000.000
 *	results.
 */

static void __attribute__ ((noinline))
__vpowfx( int n, float * restrict px, float * restrict py,
	int stridey, float * restrict pz, int stridez );

static void __attribute__ ((noinline))
__vpowf_n( int n, float * restrict px, int stridex, float * restrict py,
	int stridey, float * restrict pz, int stridez );

static void __attribute__ ((noinline))
__vpowfx_n( int n, double yy, float * restrict py,
	int stridey, float * restrict pz, int stridez );

static const double __TBL_exp2f[] = {
	/* 2^(i/256), i = [0, 255] */
1.000000000000000000e+00, 1.002711275050202522e+00, 1.005429901112802726e+00,
1.008155898118417548e+00, 1.010889286051700475e+00, 1.013630084951489430e+00,
1.016378314910953096e+00, 1.019133996077737914e+00, 1.021897148654116627e+00,
1.024667792897135721e+00, 1.027445949118763746e+00, 1.030231637686040980e+00,
1.033024879021228415e+00, 1.035825693601957198e+00, 1.038634101961378731e+00,
1.041450124688316103e+00, 1.044273782427413755e+00, 1.047105095879289793e+00,
1.049944085800687210e+00, 1.052790773004626423e+00, 1.055645178360557157e+00,
1.058507322794512762e+00, 1.061377227289262093e+00, 1.064254912884464499e+00,
1.067140400676823697e+00, 1.070033711820241873e+00, 1.072934867525975555e+00,
1.075843889062791048e+00, 1.078760797757119860e+00, 1.081685614993215250e+00,
1.084618362213309206e+00, 1.087559060917769660e+00, 1.090507732665257690e+00,
1.093464399072885840e+00, 1.096429081816376883e+00, 1.099401802630221914e+00,
1.102382583307840891e+00, 1.105371445701741173e+00, 1.108368411723678726e+00,
1.111373503344817548e+00, 1.114386742595892432e+00, 1.117408151567369279e+00,
1.120437752409606746e+00, 1.123475567333019898e+00, 1.126521618608241848e+00,
1.129575928566288079e+00, 1.132638519598719196e+00, 1.135709414157805464e+00,
1.138788634756691565e+00, 1.141876203969561576e+00, 1.144972144431804173e+00,
1.148076478840178938e+00, 1.151189229952982673e+00, 1.154310420590215935e+00,
1.157440073633751121e+00, 1.160578212027498779e+00, 1.163724858777577476e+00,
1.166880036952481658e+00, 1.170043769683250190e+00, 1.173216080163637320e+00,
1.176396991650281221e+00, 1.179586527462875845e+00, 1.182784710984341014e+00,
1.185991565660993841e+00, 1.189207115002721027e+00, 1.192431382583151178e+00,
1.195664392039827328e+00, 1.198906167074380580e+00, 1.202156731452703076e+00,
1.205416109005123859e+00, 1.208684323626581625e+00, 1.211961399276801243e+00,
1.215247359980468955e+00, 1.218542229827408452e+00, 1.221846032972757623e+00,
1.225158793637145527e+00, 1.228480536106870025e+00, 1.231811284734075862e+00,
1.235151063936933413e+00, 1.238499898199816540e+00, 1.241857812073484002e+00,
1.245224830175257980e+00, 1.248600977189204819e+00, 1.251986277866316222e+00,
1.255380757024691096e+00, 1.258784439549716527e+00, 1.262197350394250739e+00,
1.265619514578806282e+00, 1.269050957191733220e+00, 1.272491703389402762e+00,
1.275941778396392001e+00, 1.279401207505669325e+00, 1.282870016078778264e+00,
1.286348229546025568e+00, 1.289835873406665723e+00, 1.293332973229089466e+00,
1.296839554651009641e+00, 1.300355643379650594e+00, 1.303881265191935812e+00,
1.307416445934677318e+00, 1.310961211524764414e+00, 1.314515587949354636e+00,
1.318079601266064049e+00, 1.321653277603157539e+00, 1.325236643159741323e+00,
1.328829724205954355e+00, 1.332432547083161500e+00, 1.336045138204145832e+00,
1.339667524053302916e+00, 1.343299731186835322e+00, 1.346941786232945804e+00,
1.350593715892034474e+00, 1.354255546936892651e+00, 1.357927306212901142e+00,
1.361609020638224754e+00, 1.365300717204011915e+00, 1.369002422974590516e+00,
1.372714165087668414e+00, 1.376435970754530169e+00, 1.380167867260237990e+00,
1.383909881963832023e+00, 1.387662042298529075e+00, 1.391424375771926236e+00,
1.395196909966200272e+00, 1.398979672538311236e+00, 1.402772691220204759e+00,
1.406575993819015435e+00, 1.410389608217270663e+00, 1.414213562373095145e+00,
1.418047884320415175e+00, 1.421892602169165576e+00, 1.425747744105494208e+00,
1.429613338391970023e+00, 1.433489413367788901e+00, 1.437375997448982368e+00,
1.441273119128625657e+00, 1.445180806977046650e+00, 1.449099089642035043e+00,
1.453027995849052623e+00, 1.456967554401443765e+00, 1.460917794180647045e+00,
1.464878744146405731e+00, 1.468850433336981842e+00, 1.472832890869367528e+00,
1.476826145939499346e+00, 1.480830227822471867e+00, 1.484845165872752393e+00,
1.488870989524397004e+00, 1.492907728291264835e+00, 1.496955411767235455e+00,
1.501014069626425584e+00, 1.505083731623406473e+00, 1.509164427593422841e+00,
1.513256187452609813e+00, 1.517359041198214742e+00, 1.521473018908814590e+00,
1.525598150744538417e+00, 1.529734466947286986e+00, 1.533881997840955913e+00,
1.538040773831656827e+00, 1.542210825407940744e+00, 1.546392183141021448e+00,
1.550584877684999974e+00, 1.554788939777088652e+00, 1.559004400237836929e+00,
1.563231289971357629e+00, 1.567469639965552997e+00, 1.571719481292341403e+00,
1.575980845107886497e+00, 1.580253762652824578e+00, 1.584538265252493749e+00,
1.588834384317163950e+00, 1.593142151342266999e+00, 1.597461597908627073e+00,
1.601792755682693414e+00, 1.606135656416771029e+00, 1.610490331949254283e+00,
1.614856814204860713e+00, 1.619235135194863728e+00, 1.623625327017328868e+00,
1.628027421857347834e+00, 1.632441451987274972e+00, 1.636867449766964411e+00,
1.641305447644006321e+00, 1.645755478153964946e+00, 1.650217573920617742e+00,
1.654691767656194301e+00, 1.659178092161616158e+00, 1.663676580326736376e+00,
1.668187265130582464e+00, 1.672710179641596628e+00, 1.677245357017878469e+00,
1.681792830507429004e+00, 1.686352633448393368e+00, 1.690924799269305279e+00,
1.695509361489332623e+00, 1.700106353718523478e+00, 1.704715809658051251e+00,
1.709337763100462926e+00, 1.713972247929925974e+00, 1.718619298122477934e+00,
1.723278947746273992e+00, 1.727951230961837670e+00, 1.732636182022311067e+00,
1.737333835273706217e+00, 1.742044225155156445e+00, 1.746767386199169048e+00,
1.751503353031878207e+00, 1.756252160373299454e+00, 1.761013843037583904e+00,
1.765788435933272726e+00, 1.770575974063554714e+00, 1.775376492526521188e+00,
1.780190026515424462e+00, 1.785016611318934965e+00, 1.789856282321401038e+00,
1.794709075003107168e+00, 1.799575024940535117e+00, 1.804454167806623932e+00,
1.809346539371031959e+00, 1.814252175500398856e+00, 1.819171112158608494e+00,
1.824103385407053413e+00, 1.829049031404897274e+00, 1.834008086409342431e+00,
1.838980586775893711e+00, 1.843966568958625984e+00, 1.848966069510450838e+00,
1.853979125083385471e+00, 1.859005772428820480e+00, 1.864046048397788979e+00,
1.869099989941238604e+00, 1.874167634110299963e+00, 1.879249018056560194e+00,
1.884344179032334532e+00, 1.889453154390939194e+00, 1.894575981586965607e+00,
1.899712698176555303e+00, 1.904863341817674138e+00, 1.910027950270389852e+00,
1.915206561397147400e+00, 1.920399213163047403e+00, 1.925605943636125028e+00,
1.930826790987627106e+00, 1.936061793492294347e+00, 1.941310989528640452e+00,
1.946574417579233218e+00, 1.951852116230978318e+00, 1.957144124175400179e+00,
1.962450480208927317e+00, 1.967771223233175881e+00, 1.973106392255234320e+00,
1.978456026387950928e+00, 1.983820164850219392e+00, 1.989198846967266343e+00,
1.994592112170940235e+00
};

static const double __TBL_log2f[] = {
	/* __TBL_log2f[2*i] = 256*log2(1+i/128), i = [0, 128] */
	/* __TBL_log2f[2*i+1] = 2**(-23)/(1+i/128), i = [0, 128] */
0.000000000000000000e+00, 1.192092895507812500e-07, 2.874177388353054585e+00,
1.182851865310077503e-07, 5.726160135284354524e+00, 1.173753004807692373e-07,
8.556288393587271557e+00, 1.164793058206106825e-07, 1.136489455576407970e+01,
1.155968868371212153e-07, 1.415230348830453799e+01, 1.147277373120300688e-07,
1.691883275718974389e+01, 1.138715601679104456e-07, 1.966479284501270897e+01,
1.130280671296296339e-07, 2.239048736008688678e+01, 1.121969784007352926e-07,
2.509621323789484038e+01, 1.113780223540145949e-07, 2.778226093521127638e+01,
1.105709352355072477e-07, 3.044891461721790193e+01, 1.097754608812949697e-07,
3.309645233791141550e+01, 1.089913504464285680e-07, 3.572514621409114710e+01,
1.082183621453900683e-07, 3.833526259319860685e+01, 1.074562610035211292e-07,
4.092706221526768928e+01, 1.067048186188811188e-07, 4.350080036923196758e+01,
1.059638129340277719e-07, 4.605672704382322280e+01, 1.052330280172413778e-07,
4.859508707328441091e+01, 1.045122538527397202e-07, 5.111612027810928538e+01,
1.038012861394557784e-07, 5.362006160101114460e+01, 1.030999260979729787e-07,
5.610714123831336053e+01, 1.024079802852348971e-07, 5.857758476694550609e+01,
1.017252604166666732e-07, 6.103161326722020164e+01, 1.010515831953642383e-07,
6.346944344155788542e+01, 1.003867701480263102e-07, 6.589128772931884725e+01,
9.973064746732026447e-08, 6.829735441789475203e+01, 9.908304586038961692e-08,
7.068784775020480993e+01, 9.844380040322580637e-08, 7.306296802873558249e+01,
9.781275040064102225e-08, 7.542291171625650748e+01, 9.718973925159236158e-08,
7.776787153333835079e+01, 9.657461431962025166e-08, 8.009803655279496581e+01,
9.596722680817610579e-08, 8.241359229116476115e+01, 9.536743164062500529e-08,
8.471472079734193983e+01, 9.477508734472049048e-08, 8.700160073846393516e+01,
9.419005594135801946e-08, 8.927440748315585495e+01, 9.361220283742331508e-08,
9.153331318222942059e+01, 9.304139672256097884e-08, 9.377848684692884262e+01,
9.247750946969696962e-08, 9.601009442481273481e+01, 9.192041603915663129e-08,
9.822829887335737453e+01, 9.136999438622755046e-08, 1.004332602313626381e+02,
9.082612537202380448e-08, 1.026251356882391832e+02, 9.028869267751479078e-08,
1.048040796512516550e+02, 8.975758272058823405e-08, 1.069702438107898530e+02,
8.923268457602338686e-08, 1.091237772037370775e+02, 8.871388989825581272e-08,
1.112648262750015107e+02, 8.820109284682080489e-08, 1.133935349372744383e+02,
8.769419001436781487e-08, 1.155100446290761766e+02, 8.719308035714285707e-08,
1.176144943711480977e+02, 8.669766512784091150e-08, 1.197070208212473403e+02,
8.620784781073446298e-08, 1.217877583273978246e+02, 8.572353405898876167e-08,
1.238568389796496376e+02, 8.524463163407821503e-08, 1.259143926603967287e+02,
8.477105034722222546e-08, 1.279605470933005762e+02, 8.430270200276242743e-08,
1.299954278908662388e+02, 8.383950034340659995e-08, 1.320191586007148601e+02,
8.338136099726775949e-08, 1.340318607505952855e+02, 8.292820142663043248e-08,
1.360336538921758915e+02, 8.247994087837838296e-08, 1.380246556436560468e+02,
8.203650033602151192e-08, 1.400049817312349774e+02, 8.159780247326202734e-08,
1.419747460294751704e+02, 8.116377160904255122e-08, 1.439340606005945915e+02,
8.073433366402115954e-08, 1.458830357327226466e+02, 8.030941611842105082e-08,
1.478217799771516638e+02, 7.988894797120419333e-08, 1.497504001846159838e+02,
7.947285970052082892e-08, 1.516690015406285852e+02, 7.906108322538860398e-08,
1.535776875999046922e+02, 7.865355186855669953e-08, 1.554765603199003294e+02,
7.825020032051282044e-08, 1.573657200934933087e+02, 7.785096460459183052e-08,
1.592452657808323124e+02, 7.745578204314720208e-08, 1.611152947403800511e+02,
7.706459122474748130e-08, 1.629759028591741128e+02, 7.667733197236181018e-08,
1.648271845823295223e+02, 7.629394531250000159e-08, 1.666692329418057170e+02,
7.591437344527363039e-08, 1.685021395844594565e+02, 7.553855971534653557e-08,
1.703259947994051231e+02, 7.516644858374384321e-08, 1.721408875447028777e+02,
7.479798560049019504e-08, 1.739469054733941960e+02, 7.443311737804878042e-08,
1.757441349589039135e+02, 7.407179156553397416e-08, 1.775326611198272531e+02,
7.371395682367149407e-08, 1.793125678441195987e+02, 7.335956280048077330e-08,
1.810839378127059831e+02, 7.300856010765549954e-08, 1.828468525225273993e+02,
7.266090029761905417e-08, 1.846013923090393973e+02, 7.231653584123223301e-08,
1.863476363681789962e+02, 7.197542010613207272e-08, 1.880856627778145764e+02,
7.163750733568075279e-08, 1.898155485186936176e+02, 7.130275262850466758e-08,
1.915373694949018386e+02, 7.097111191860465018e-08, 1.932512005538479514e+02,
7.064254195601851460e-08, 1.949571155057867031e+02, 7.031700028801843312e-08,
1.966551871428931406e+02, 6.999444524082569196e-08, 1.983454872579004018e+02,
6.967483590182648015e-08, 2.000280866623128588e+02, 6.935813210227272390e-08,
2.017030552042064926e+02, 6.904429440045249486e-08, 2.033704617856271284e+02,
6.873328406531531472e-08, 2.050303743795980154e+02, 6.842506306053811558e-08,
2.066828600467466401e+02, 6.811959402901785336e-08, 2.083279849515614899e+02,
6.781684027777777772e-08, 2.099658143782880586e+02, 6.751676576327433535e-08,
2.115964127464742432e+02, 6.721933507709251725e-08, 2.132198436261738550e+02,
6.692451343201754014e-08, 2.148361697528176535e+02, 6.663226664847161225e-08,
2.164454530417600608e+02, 6.634256114130434863e-08, 2.180477546025107358e+02,
6.605536390692640687e-08, 2.196431347526584545e+02, 6.577064251077586116e-08,
2.212316530314957390e+02, 6.548836507510729591e-08, 2.228133682133515663e+02,
6.520850026709402365e-08, 2.243883383206399174e+02, 6.493101728723404362e-08,
2.259566206366313565e+02, 6.465588585805084723e-08, 2.275182717179543204e+02,
6.438307621308016336e-08, 2.290733474068335340e+02, 6.411255908613445100e-08,
2.306219028430716378e+02, 6.384430570083681460e-08, 2.321639924757807307e+02,
6.357828776041666578e-08, 2.336996700748701699e+02, 6.331447743775933615e-08,
2.352289887422961954e+02, 6.305284736570248109e-08, 2.367520009230799189e+02,
6.279337062757202180e-08, 2.382687584160988763e+02, 6.253602074795082293e-08,
2.397793123846580556e+02, 6.228077168367347501e-08, 2.412837133668454044e+02,
6.202759781504065697e-08, 2.427820112856774699e+02, 6.177647393724696421e-08,
2.442742554590400630e+02, 6.152737525201612732e-08, 2.457604946094287186e+02,
6.128027735943774537e-08, 2.472407768734942692e+02, 6.103515625000000127e-08,
2.487151498113976231e+02, 6.079198829681274795e-08, 2.501836604159786077e+02,
6.055075024801586965e-08, 2.516463551217433974e+02, 6.031141921936758485e-08,
2.531032798136744475e+02, 6.007397268700787318e-08, 2.545544798358676246e+02,
5.983838848039215603e-08, 2.560000000000000000e+02, 5.960464477539062500e-08
};

static const double __TBL_expfb[] = {
7.006492321624085355e-46, 1.401298464324817071e-45, 2.802596928649634142e-45,
5.605193857299268284e-45, 1.121038771459853657e-44, 2.242077542919707313e-44,
4.484155085839414627e-44, 8.968310171678829254e-44, 1.793662034335765851e-43,
3.587324068671531702e-43, 7.174648137343063403e-43, 1.434929627468612681e-42,
2.869859254937225361e-42, 5.739718509874450723e-42, 1.147943701974890145e-41,
2.295887403949780289e-41, 4.591774807899560578e-41, 9.183549615799121156e-41,
1.836709923159824231e-40, 3.673419846319648462e-40, 7.346839692639296925e-40,
1.469367938527859385e-39, 2.938735877055718770e-39, 5.877471754111437540e-39,
1.175494350822287508e-38, 2.350988701644575016e-38, 4.701977403289150032e-38,
9.403954806578300064e-38, 1.880790961315660013e-37, 3.761581922631320025e-37,
7.523163845262640051e-37, 1.504632769052528010e-36, 3.009265538105056020e-36,
6.018531076210112041e-36, 1.203706215242022408e-35, 2.407412430484044816e-35,
4.814824860968089633e-35, 9.629649721936179265e-35, 1.925929944387235853e-34,
3.851859888774471706e-34, 7.703719777548943412e-34, 1.540743955509788682e-33,
3.081487911019577365e-33, 6.162975822039154730e-33, 1.232595164407830946e-32,
2.465190328815661892e-32, 4.930380657631323784e-32, 9.860761315262647568e-32,
1.972152263052529514e-31, 3.944304526105059027e-31, 7.888609052210118054e-31,
1.577721810442023611e-30, 3.155443620884047222e-30, 6.310887241768094443e-30,
1.262177448353618889e-29, 2.524354896707237777e-29, 5.048709793414475555e-29,
1.009741958682895111e-28, 2.019483917365790222e-28, 4.038967834731580444e-28,
8.077935669463160887e-28, 1.615587133892632177e-27, 3.231174267785264355e-27,
6.462348535570528710e-27, 1.292469707114105742e-26, 2.584939414228211484e-26,
5.169878828456422968e-26, 1.033975765691284594e-25, 2.067951531382569187e-25,
4.135903062765138374e-25, 8.271806125530276749e-25, 1.654361225106055350e-24,
3.308722450212110699e-24, 6.617444900424221399e-24, 1.323488980084844280e-23,
2.646977960169688560e-23, 5.293955920339377119e-23, 1.058791184067875424e-22,
2.117582368135750848e-22, 4.235164736271501695e-22, 8.470329472543003391e-22,
1.694065894508600678e-21, 3.388131789017201356e-21, 6.776263578034402713e-21,
1.355252715606880543e-20, 2.710505431213761085e-20, 5.421010862427522170e-20,
1.084202172485504434e-19, 2.168404344971008868e-19, 4.336808689942017736e-19,
8.673617379884035472e-19, 1.734723475976807094e-18, 3.469446951953614189e-18,
6.938893903907228378e-18, 1.387778780781445676e-17, 2.775557561562891351e-17,
5.551115123125782702e-17, 1.110223024625156540e-16, 2.220446049250313081e-16,
4.440892098500626162e-16, 8.881784197001252323e-16, 1.776356839400250465e-15,
3.552713678800500929e-15, 7.105427357601001859e-15, 1.421085471520200372e-14,
2.842170943040400743e-14, 5.684341886080801487e-14, 1.136868377216160297e-13,
2.273736754432320595e-13, 4.547473508864641190e-13, 9.094947017729282379e-13,
1.818989403545856476e-12, 3.637978807091712952e-12, 7.275957614183425903e-12,
1.455191522836685181e-11, 2.910383045673370361e-11, 5.820766091346740723e-11,
1.164153218269348145e-10, 2.328306436538696289e-10, 4.656612873077392578e-10,
9.313225746154785156e-10, 1.862645149230957031e-09, 3.725290298461914062e-09,
7.450580596923828125e-09, 1.490116119384765625e-08, 2.980232238769531250e-08,
5.960464477539062500e-08, 1.192092895507812500e-07, 2.384185791015625000e-07,
4.768371582031250000e-07, 9.536743164062500000e-07, 1.907348632812500000e-06,
3.814697265625000000e-06, 7.629394531250000000e-06, 1.525878906250000000e-05,
3.051757812500000000e-05, 6.103515625000000000e-05, 1.220703125000000000e-04,
2.441406250000000000e-04, 4.882812500000000000e-04, 9.765625000000000000e-04,
1.953125000000000000e-03, 3.906250000000000000e-03, 7.812500000000000000e-03,
1.562500000000000000e-02, 3.125000000000000000e-02, 6.250000000000000000e-02,
1.250000000000000000e-01, 2.500000000000000000e-01, 5.000000000000000000e-01,
1.000000000000000000e+00, 2.000000000000000000e+00, 4.000000000000000000e+00,
8.000000000000000000e+00, 1.600000000000000000e+01, 3.200000000000000000e+01,
6.400000000000000000e+01, 1.280000000000000000e+02, 2.560000000000000000e+02,
5.120000000000000000e+02, 1.024000000000000000e+03, 2.048000000000000000e+03,
4.096000000000000000e+03, 8.192000000000000000e+03, 1.638400000000000000e+04,
3.276800000000000000e+04, 6.553600000000000000e+04, 1.310720000000000000e+05,
2.621440000000000000e+05, 5.242880000000000000e+05, 1.048576000000000000e+06,
2.097152000000000000e+06, 4.194304000000000000e+06, 8.388608000000000000e+06,
1.677721600000000000e+07, 3.355443200000000000e+07, 6.710886400000000000e+07,
1.342177280000000000e+08, 2.684354560000000000e+08, 5.368709120000000000e+08,
1.073741824000000000e+09, 2.147483648000000000e+09, 4.294967296000000000e+09,
8.589934592000000000e+09, 1.717986918400000000e+10, 3.435973836800000000e+10,
6.871947673600000000e+10, 1.374389534720000000e+11, 2.748779069440000000e+11,
5.497558138880000000e+11, 1.099511627776000000e+12, 2.199023255552000000e+12,
4.398046511104000000e+12, 8.796093022208000000e+12, 1.759218604441600000e+13,
3.518437208883200000e+13, 7.036874417766400000e+13, 1.407374883553280000e+14,
2.814749767106560000e+14, 5.629499534213120000e+14, 1.125899906842624000e+15,
2.251799813685248000e+15, 4.503599627370496000e+15, 9.007199254740992000e+15,
1.801439850948198400e+16, 3.602879701896396800e+16, 7.205759403792793600e+16,
1.441151880758558720e+17, 2.882303761517117440e+17, 5.764607523034234880e+17,
1.152921504606846976e+18, 2.305843009213693952e+18, 4.611686018427387904e+18,
9.223372036854775808e+18, 1.844674407370955162e+19, 3.689348814741910323e+19,
7.378697629483820646e+19, 1.475739525896764129e+20, 2.951479051793528259e+20,
5.902958103587056517e+20, 1.180591620717411303e+21, 2.361183241434822607e+21,
4.722366482869645214e+21, 9.444732965739290427e+21, 1.888946593147858085e+22,
3.777893186295716171e+22, 7.555786372591432342e+22, 1.511157274518286468e+23,
3.022314549036572937e+23, 6.044629098073145874e+23, 1.208925819614629175e+24,
2.417851639229258349e+24, 4.835703278458516699e+24, 9.671406556917033398e+24,
1.934281311383406680e+25, 3.868562622766813359e+25, 7.737125245533626718e+25,
1.547425049106725344e+26, 3.094850098213450687e+26, 6.189700196426901374e+26,
1.237940039285380275e+27, 2.475880078570760550e+27, 4.951760157141521100e+27,
9.903520314283042199e+27, 1.980704062856608440e+28, 3.961408125713216880e+28,
7.922816251426433759e+28, 1.584563250285286752e+29, 3.169126500570573504e+29,
6.338253001141147007e+29, 1.267650600228229401e+30, 2.535301200456458803e+30,
5.070602400912917606e+30, 1.014120480182583521e+31, 2.028240960365167042e+31,
4.056481920730334085e+31, 8.112963841460668170e+31, 1.622592768292133634e+32,
3.245185536584267268e+32, 6.490371073168534536e+32, 1.298074214633706907e+33,
2.596148429267413814e+33, 5.192296858534827629e+33, 1.038459371706965526e+34,
2.076918743413931051e+34, 4.153837486827862103e+34, 8.307674973655724206e+34,
1.661534994731144841e+35, 3.323069989462289682e+35, 6.646139978924579365e+35,
1.329227995784915873e+36, 2.658455991569831746e+36, 5.316911983139663492e+36,
1.063382396627932698e+37, 2.126764793255865397e+37, 4.253529586511730793e+37,
8.507059173023461587e+37, 1.701411834604692317e+38, 3.402823669209384635e+38
};

static const double
	KA3 = -3.60659926599003171364e-01*256.0,
	KA2 =  4.80902715189356683026e-01*256.0,
	KA1 = -7.21347520569871841065e-01*256.0,
	KA0 =  1.44269504088069658645e+00*256.0,
	KB2 =  3.66556671660783833261e-06,
	KB1 =  2.70760782821392980564e-03,
	DONE = 1.0,
	HTHRESH = 32768.0,
	LTHRESH = -38400.0;

#define RETURN(ret)						\
{								\
	*pz = (ret);						\
	px += stridex;						\
	py += stridey;						\
	pz += stridez;						\
	if ( n_n == 0 )						\
	{							\
		spx = px; spy = py; spz = pz;			\
		continue;					\
	}							\
	n--;							\
	break;							\
}

void
__vpowf( int n, float * restrict px, int stridex, float * restrict py,
	int stridey, float * restrict pz, int stridez )
{
	float		*spx, *spy, *spz;
	double		y0, yy0;
	long long	di0;
	unsigned	ux, sx, uy, ay, ax0;
	int		exp, i0, ind0, exp0, yisint0, n_n;

#ifndef NOPOWFIX
	if ( stridex == 0 )
	{
		unsigned	hx = *(unsigned*)px;

		if ( (hx >= 0x00800000) &&	/* x not zero or subnormal		*/
		(hx < 0x7f800000) &&		/* x not inf, nan or negative sign bit	*/
		(hx != 0x3f800000) )		/* x not 1				*/
		{
			__vpowfx( n, px, py, stridey, pz, stridez );
			return;
		}
	}
#endif

	while ( n > 0 )
	{
		n_n = 0;
		spx = px;
		spy = py;
		spz = pz;
		for ( ; n > 0 ; n-- )
		{
			uy = *(unsigned int*)py;
			ux = *(unsigned int*)px;
			ay = uy & 0x7fffffff;
			ax0 = ux & 0x7fffffff;
			sx = ux >> 31;
			yisint0 = 0;	/* Y - non-integer */

			/* |X| or |Y| = Inf,Nan */
			if ( ax0 >= 0x7f800000 || ay >= 0x7f800000 )
			{
				if ( ay == 0 )
					RETURN( 1.0f )	/* pow(X,0) */
				/* |X| or |Y| = Nan */
				if ( ax0 > 0x7f800000 || ay > 0x7f800000 )
					RETURN ( *px + *py )
				if ( ay == 0x7f800000 )		/* |Y| = Inf */
				{
					float fy;
					if ( ax0 == 0x3f800000 )
						fy = *py - *py;		/* +-1 ** +-Inf = NaN */
					else
						fy = ( (ax0 < 0x3f800000) != (uy >> 31) ) ? 0.0f : *(float*) &ay;
					RETURN( fy )
				}
				if ( sx )	/* X = -Inf */
				{
					exp = ay >> 23;
					if ( exp >= 0x97 )	/* |Y| >= 2^24 */
						yisint0 = 2;	/* Y - even */
					else if ( exp >= 0x7f )	/* |Y| >= 1 */
					{
						i0 = ay >> ((0x7f + 23) - exp);
						if ( (i0 << ((0x7f + 23) - exp)) == ay )
							yisint0 = 2 - (i0 & 1);
					}
				}
				if ( uy >> 31 )
					ax0 = 0;
				ax0 += yisint0 << 31;
				RETURN( *(float*)&ax0 )
			}

			if ( (int)ux < 0x00800000 )	/* X = denormal or negative */
			{
				if ( ay == 0 )
					RETURN( 1.0f )	/* pow(X,0) */
				exp0 = (ax0 >> 23) - 127;

				if ( (int)ax0 < 0x00800000 )	/* X = denormal */
				{
					*((float*) &ax0) = (float) (int)ax0;
					exp0 = (ax0 >> 23) - (127 + 149);
				}

				if ( (int)ux <= 0 )	/* X <= 0 */
				{
					exp = ay >> 23;
					if ( exp >= 0x97 )	/* |Y| >= 2^24 */
						yisint0 = 2;	/* Y - even */
					else if ( exp >= 0x7f )	/* |Y| >= 1 */
					{
						i0 = ay >> ((0x7f + 23) - exp);
						if ( (i0 << ((0x7f + 23) - exp)) == ay )
							yisint0 = 2 - (i0 & 1);
					}

					if ( ax0 == 0 )		/* pow(0,Y) */
					{
						float fy;
						fy = (uy >> 31) ? 1.0f / 0.0f : 0.0f;
						if ( sx & yisint0 )
							fy = -fy;
						RETURN( fy )
					}

					if ( yisint0 == 0 )	/* pow(neg,non-integer) */
						RETURN( 0.0f / 0.0f )	/* NaN */
				}

				/* perform yy0 = 256*log2(xi)*yi */
				ax0 &= 0x007fffff;
				i0 = (ax0 + 0x8000) & 0xffff0000;
				ind0 = i0 >> 15;
				i0 = ax0 - i0;
				y0 = (double) i0 * __TBL_log2f[ind0 + 1];
				yy0 = __TBL_log2f[ind0] + (double) (exp0 << 8);
				yy0 += (((KA3 * y0 + KA2) * y0 + KA1) * y0 + KA0) * y0;
				yy0 = (double)py[0] * yy0;

				/* perform 2 ** (yy0/256) */
				if ( yy0 >= HTHRESH )
					yy0 = HTHRESH;
				if ( yy0 <= LTHRESH )
					yy0 = LTHRESH;
				ind0 = (int) yy0;
				y0 = yy0 - (double)ind0;
				yy0 = (KB2 * y0 + KB1) * y0 + DONE;
				di0 = ((long long)((ind0 >> 8) + (yisint0 << 11))) << 52;
				di0 += ((long long*)__TBL_exp2f)[ind0 & 255];
				RETURN( (float) (yy0 * *(double*)&di0) )
			}
			px += stridex;
			py += stridey;
			pz += stridez;
			n_n++;
		}
		if ( n_n > 0 )
			__vpowf_n( n_n, spx, stridex, spy, stridey, spz, stridez );
	}
}


static void
__vpowf_n( int n, float * restrict px, int stridex, float * restrict py,
	int stridey, float * restrict pz, int stridez )
{
	double		y0, yy0;
	double		di0;
	int		ind0, i0, exp0;
	unsigned	ax0;
	double		y1, yy1;
	double		di1;
	int		ind1, i1, exp1;
	unsigned	ax1;
	double		y2, yy2;
	double		di2;
	int		ind2, i2, exp2;
	unsigned	ax2;

	for ( ; n > 2 ; n -= 3 )
	{
		/* perform yy0 = 256*log2(xi)*yi */
		ax0 = ((int*)px)[0];
		px += stridex;
		ax1 = ((int*)px)[0];
		px += stridex;
		ax2 = ((int*)px)[0];
		px += stridex;
		exp0 = ((ax0 & 0x7fffffff) >> 23) - 127;
		exp1 = ((ax1 & 0x7fffffff) >> 23) - 127;
		exp2 = ((ax2 & 0x7fffffff) >> 23) - 127;
		ax0 &= 0x007fffff;
		ax1 &= 0x007fffff;
		ax2 &= 0x007fffff;
		i0 = (ax0 + 0x8000) & 0xffff0000;
		i1 = (ax1 + 0x8000) & 0xffff0000;
		i2 = (ax2 + 0x8000) & 0xffff0000;
		ind0 = i0 >> 15;
		ind1 = i1 >> 15;
		ind2 = i2 >> 15;
		i0 = ax0 - i0;
		i1 = ax1 - i1;
		i2 = ax2 - i2;
		y0 = (double) i0 * __TBL_log2f[ind0 + 1];
		y1 = (double) i1 * __TBL_log2f[ind1 + 1];
		y2 = (double) i2 * __TBL_log2f[ind2 + 1];
		yy0 = __TBL_log2f[ind0] + (double) (exp0 << 8);
		yy1 = __TBL_log2f[ind1] + (double) (exp1 << 8);
		yy2 = __TBL_log2f[ind2] + (double) (exp2 << 8);
		yy0 += (((KA3 * y0 + KA2) * y0 + KA1) * y0 + KA0) * y0;
		yy1 += (((KA3 * y1 + KA2) * y1 + KA1) * y1 + KA0) * y1;
		yy2 += (((KA3 * y2 + KA2) * y2 + KA1) * y2 + KA0) * y2;
		yy0 = (double)py[0] * yy0;
		py += stridey;
		yy1 = (double)py[0] * yy1;
		py += stridey;
		yy2 = (double)py[0] * yy2;
		py += stridey;

		/* perform 2 ** (yy0/256) */
		if ( yy0 >= HTHRESH )
			yy0 = HTHRESH;
		if ( yy0 <= LTHRESH )
			yy0 = LTHRESH;
		if ( yy1 >= HTHRESH )
			yy1 = HTHRESH;
		if ( yy1 <= LTHRESH )
			yy1 = LTHRESH;
		if ( yy2 >= HTHRESH )
			yy2 = HTHRESH;
		if ( yy2 <= LTHRESH )
			yy2 = LTHRESH;

		ind0 = (int) yy0;
		ind1 = (int) yy1;
		ind2 = (int) yy2;
		y0 = yy0 - (double)ind0;
		y1 = yy1 - (double)ind1;
		y2 = yy2 - (double)ind2;
		yy0 = (KB2 * y0 + KB1) * y0 + DONE;
		yy1 = (KB2 * y1 + KB1) * y1 + DONE;
		yy2 = (KB2 * y2 + KB1) * y2 + DONE;
		di0 = (__TBL_expfb + 150)[ind0 >> 8];
		di1 = (__TBL_expfb + 150)[ind1 >> 8];
		di2 = (__TBL_expfb + 150)[ind2 >> 8];
		di0 *= __TBL_exp2f[ind0 & 255];
		di1 *= __TBL_exp2f[ind1 & 255];
		di2 *= __TBL_exp2f[ind2 & 255];
		pz[0] = (float) (yy0 * di0);
		pz += stridez;
		pz[0] = (float) (yy1 * di1);
		pz += stridez;
		pz[0] = (float) (yy2 * di2);
		pz += stridez;
	}

	for ( ; n > 0 ; n-- )
	{
		/* perform yy0 = 256*log2(xi)*yi */
		ax0 = ((int*)px)[0];
		exp0 = ((ax0 & 0x7fffffff) >> 23) - 127;
		ax0 &= 0x007fffff;
		i0 = (ax0 + 0x8000) & 0xffff0000;
		ind0 = i0 >> 15;
		i0 = ax0 - i0;
		y0 = (double) i0 * __TBL_log2f[ind0 + 1];
		yy0 = __TBL_log2f[ind0] + (double) (exp0 << 8);
		yy0 += (((KA3 * y0 + KA2) * y0 + KA1) * y0 + KA0) * y0;
		yy0 = (double)py[0] * yy0;

		/* perform 2 ** (yy0/256) */
		if ( yy0 >= HTHRESH )
			yy0 = HTHRESH;
		if ( yy0 <= LTHRESH )
			yy0 = LTHRESH;
		ind0 = (int) yy0;
		y0 = yy0 - (double)ind0;
		yy0 = (KB2 * y0 + KB1) * y0 + DONE;
		di0 = (__TBL_expfb + 150)[ind0 >> 8];
		di0 *= __TBL_exp2f[ind0 & 255];
		pz[0] = (float) (yy0 * di0);
		px += stridex;
		py += stridey;
		pz += stridez;
	}
}


static void
__vpowfx( int n, float * restrict px, float * restrict py,
	int stridey, float * restrict pz, int stridez )
{
	float		*spy, *spz;
	double		yy, y0;
	int		ind0, exp0, i0, n_n;
	unsigned	ux, ax, ax0, uy, ay;

	/* perform yy = 256*log2(xi)*yi */
	ux = *(unsigned int*)px;
	ax = ux & 0x7fffffff;
	exp0 = (ax >> 23) - 127;
	ax0 = ux & 0x007fffff;
	i0 = (ax0 + 0x8000) & 0xffff0000;
	ind0 = i0 >> 15;
	i0 = ax0 - i0;
	y0 = (double) i0 * __TBL_log2f[ind0 + 1];
	yy = __TBL_log2f[ind0] + (double) (exp0 << 8);
	yy += (((KA3 * y0 + KA2) * y0 + KA1) * y0 + KA0) * y0;

	while ( n > 0 )
	{
		n_n = 0;
		spy = py;
		spz = pz;
		for ( ; n > 0 ; n-- )
		{
			uy = *(unsigned int*)py;
			ay = uy & 0x7fffffff;

			if ( ay >= 0x7f800000 )		/* |Y| = Inf or Nan */
			{
				float fy;
				if ( ay > 0x7f800000 )
					fy = *py + *py;	/* |Y| = Nan */
				else
					fy = ( (ax < 0x3f800000) != (uy >> 31) ) ? 0.0f : *(float*)&ay;
				*pz = fy;
				py += stridey;
				pz += stridez;
				if ( n_n == 0 )
				{
					spy = py;
					spz = pz;
					continue;
				}
				n--;
				break;
			}
			py += stridey;
			pz += stridez;
			n_n++;
		}
		if ( n_n > 0 )
			__vpowfx_n( n_n, yy, spy, stridey, spz, stridez );
	}
}


static void
__vpowfx_n( int n, double yy, float * restrict py,
	int stridey, float * restrict pz, int stridez )
{
	double		y0, yy0, di0;
	double		y1, yy1, di1;
	double		y2, yy2, di2;
	int		ind0, ind1, ind2;

	for ( ; n > 2 ; n-= 3 )
	{
		/* perform 2 ** (yy/256) */
		yy0 = (double)py[0] * yy;
		py += stridey;
		yy1 = (double)py[0] * yy;
		py += stridey;
		yy2 = (double)py[0] * yy;
		py += stridey;
		if ( yy0 >= HTHRESH )
			yy0 = HTHRESH;
		if ( yy0 <= LTHRESH )
			yy0 = LTHRESH;
		if ( yy1 >= HTHRESH )
			yy1 = HTHRESH;
		if ( yy1 <= LTHRESH )
			yy1 = LTHRESH;
		if ( yy2 >= HTHRESH )
			yy2 = HTHRESH;
		if ( yy2 <= LTHRESH )
			yy2 = LTHRESH;
		ind0 = (int) yy0;
		ind1 = (int) yy1;
		ind2 = (int) yy2;
		y0 = yy0 - (double)ind0;
		y1 = yy1 - (double)ind1;
		y2 = yy2 - (double)ind2;
		yy0 = (KB2 * y0 + KB1) * y0 + DONE;
		yy1 = (KB2 * y1 + KB1) * y1 + DONE;
		yy2 = (KB2 * y2 + KB1) * y2 + DONE;
		di0 = (__TBL_expfb + 150)[ind0 >> 8];
		di1 = (__TBL_expfb + 150)[ind1 >> 8];
		di2 = (__TBL_expfb + 150)[ind2 >> 8];
		di0 *= __TBL_exp2f[ind0 & 255];
		di1 *= __TBL_exp2f[ind1 & 255];
		di2 *= __TBL_exp2f[ind2 & 255];
		pz[0] = (float) (yy0 * di0);
		pz += stridez;
		pz[0] = (float) (yy1 * di1);
		pz += stridez;
		pz[0] = (float) (yy2 * di2);
		pz += stridez;
	}
	for ( ; n > 0 ; n-- )
	{
		/* perform 2 ** (yy/256) */
		yy0 = (double)py[0] * yy;
		if ( yy0 >= HTHRESH )
			yy0 = HTHRESH;
		if ( yy0 <= LTHRESH )
			yy0 = LTHRESH;
		ind0 = (int) yy0;
		y0 = yy0 - (double)ind0;
		yy0 = (KB2 * y0 + KB1) * y0 + DONE;
		di0 = (__TBL_expfb + 150)[ind0 >> 8];
		di0 *= __TBL_exp2f[ind0 & 255];
		pz[0] = (float) (yy0 * di0);
		py += stridey;
		pz += stridez;
	}
}
