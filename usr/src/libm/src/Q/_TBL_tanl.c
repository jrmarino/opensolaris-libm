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


/*
 * table of tanl(x) where x is 0.15625 + i*0.03125, i=0,1,...,74.
 * {0x3ffc4000,0,0,0} --> (inc 0x800) -->  {0x3ffe9000,0,0,0}
 *    0.15625	           0.03125	     0.78125  (pi/4 = 0.785395663...)
 */

#include "libm.h"

const long double _TBL_tanl_hi[] = {
	+1.575341073252716106852257741724104864870e-0001L,
	+1.615397840495214763092752400110463977418e-0001L,
	+1.655505192739339762139309125850523900470e-0001L,
	+1.695664452197665101509706065437500194264e-0001L,
	+1.735876947679815208446734114353616329985e-0001L,
	+1.776144014774467276317429269586882243819e-0001L,
	+1.816466996033214276582758961743535864882e-0001L,
	+1.856847241156344116266612278649865067149e-0001L,
	+1.897286107180591328910833700730338069829e-0001L,
	+1.937784958668918635160223977682694780440e-0001L,
	+1.978345167902386688084063751239797409303e-0001L,
	+2.018968115074171328840689933657666757769e-0001L,
	+2.059655188485788721087393288030358608878e-0001L,
	+2.100407784745589808415175232245911862545e-0001L,
	+2.141227308969586648860666814158624683863e-0001L,
	+2.182115174984674325058820481495796084382e-0001L,
	+2.223072805534313308722888175879995829692e-0001L,
	+2.264101632486738374776714045035595099974e-0001L,
	+2.305203097045761414554475155379181753938e-0001L,
	+2.346378649964236789993677105610770268268e-0001L,
	+2.387629751760259202681510637409399276566e-0001L,
	+2.428957872936165424010859430156609881174e-0001L,
	+2.470364494200412646634947325158035272170e-0001L,
	+2.511851106692407673991038906774344215246e-0001L,
	+2.553419212210362665044822364904736907938e-0001L,
	+2.636805964199967998548259948794679989658e-0001L,
	+2.720536986587708834265643667712727220498e-0001L,
	+2.804624701452514031696042891852650256007e-0001L,
	+2.889081724405147260015884454642448163630e-0001L,
	+2.973920872690245894671940160246554900716e-0001L,
	+3.059155173530592641072389231969929579942e-0001L,
	+3.144797872725715161734382202256272257022e-0001L,
	+3.230862443517455201183006557179619867007e-0001L,
	+3.317362595735727673394297030105334375685e-0001L,
	+3.404312285238303874282274418902587687499e-0001L,
	+3.491725723659103522547129636843912210518e-0001L,
	+3.579617388480169983883959631794471179752e-0001L,
	+3.668002033443234227206048185537661359712e-0001L,
	+3.756894699317548404092457756875977254806e-0001L,
	+3.846310725041492230408562796582816506283e-0001L,
	+3.936265759256327582294137871012180779893e-0001L,
	+4.026775772251402117785937359900067250949e-0001L,
	+4.117857068341084757888498763848712415895e-0001L,
	+4.209526298694758220747941414506739471850e-0001L,
	+4.301800474642300490203296054472752443302e-0001L,
	+4.394696981478662404836631484799309510327e-0001L,
	+4.488233592792397088405555239245740331672e-0001L,
	+4.582428485344323669591891965241567184790e-0001L,
	+4.677300254523917999213427069619926229670e-0001L,
	+4.772867930412522617224042590104237355391e-0001L,
	+4.869150994484063244987175035683195875449e-0001L,
	+4.966169396975656257105605790725693200164e-0001L,
	+5.063943574962298120708227547071771601970e-0001L,
	+5.162494471171751444917753379369286911420e-0001L,
	+5.261843553577791441706134379510093677744e-0001L,
	+5.362012835812160313475789292393083126826e-0001L,
	+5.463024898437905132551794657802853544147e-0001L,
	+5.667670655805864456801779441354759990792e-0001L,
	+5.875973675914432213941588631578976895206e-0001L,
	+6.088137403243807214124939743963768234939e-0001L,
	+6.304376738358847668526114292997751740101e-0001L,
	+6.524918979288079927238977365516267472227e-0001L,
	+6.750004851442429076631779494777228720541e-0001L,
	+6.979889636235992551497657233900136516119e-0001L,
	+7.214844409909044199895178832795946639042e-0001L,
	+7.455157405593919951361301646778137804617e-0001L,
	+7.701135513442087050059836600527731975210e-0001L,
	+7.953105935686741856456016917474183548089e-0001L,
	+8.211418015898941219114239653747117425236e-0001L,
	+8.476445264465526540907883088076187235513e-0001L,
	+8.748587605544823495396719079321555572147e-0001L,
	+9.028273874526735021961743652539763208464e-0001L,
	+9.315964599440724611652027565739364074620e-0001L,
	+9.612155104943704161853006259468735267385e-0001L,
	+9.917378983632686802568573899299023560595e-0001L,
};

const long double _TBL_tanl_lo[] = {
	+4.179214385976688849250979202972663542033e-0036L,
	+1.201528446191025246839024650298397902579e-0035L,
	+1.129323489449537738080901788756231977300e-0035L,
	+2.140135278964936125815581758267649033136e-0037L,
	+4.432205749300185001040819456988862684951e-0036L,
	+6.136100978120132271332684207100740679906e-0036L,
	-1.032553059579180849987395832156976613765e-0035L,
	-3.160024259922437001215851404196652376871e-0037L,
	+9.288062528988428190963791818336024913881e-0036L,
	-7.446971695790644707546943119354167721612e-0036L,
	-3.194115406765633171232961214385101074252e-0036L,
	+8.636824101000271295925487212833770093090e-0036L,
	+3.102272236726159152985822088441358430350e-0036L,
	-5.851906473589368694487202441718008909753e-0036L,
	+4.010022070137306925338504597897336002613e-0036L,
	+1.037727706884673933875970874373462194321e-0035L,
	-7.373234860421060505099033319601658081963e-0037L,
	+1.012564187615243178899324943342662908733e-0035L,
	-1.409372712725876553601555574139438939044e-0036L,
	+8.378827024922767151362882309834645448153e-0036L,
	+2.973824478467770877677465646013477493211e-0037L,
	+5.400099398783906370270919848839276575083e-0036L,
	-6.462512242458415498262723324973388658384e-0036L,
	-2.322762023061318925750503642571013465985e-0035L,
	-1.258955887171193954556521579215259847692e-0035L,
	-2.320447955805179154521333495999564905899e-0035L,
	-1.149012552345329193834437558081484346041e-0035L,
	+1.452751817871169833623945031311944393871e-0035L,
	+1.233520419884672519188849688498814953115e-0035L,
	-2.801716058919562991500189219464456618491e-0036L,
	-8.652310551710608096633992612270187537921e-0036L,
	+1.247172716748407772564831128401880847054e-0035L,
	-1.239704249638930213583929247314024560861e-0035L,
	+5.184462988068616168233816296529150644737e-0036L,
	-6.856476723415391305857531095744442523549e-0039L,
	-9.739553531295433673398454344315039002245e-0036L,
	+2.266233016492660661638292126777401538348e-0035L,
	+2.301502770052376628347923621704562121797e-0035L,
	+1.948845747336057051538318007442114995744e-0035L,
	-1.940750389335608259363326370556914475278e-0035L,
	+2.019644660873458215118483163076314703163e-0035L,
	+1.602015812156905914821208807083062984550e-0035L,
	-3.292416392515743374743236507806546284438e-0036L,
	+8.663813942351672490328381271391704283086e-0036L,
	+2.366609581506599084093910217277994736871e-0035L,
	-1.408950063101056644039900854057776596620e-0035L,
	-1.514769920962849077013113923603803573445e-0035L,
	-2.261973795598615105449462443044330073903e-0035L,
	-2.553211882172402068866429390071980923144e-0036L,
	+1.416627029437126089675998257335033382140e-0035L,
	+2.342724931714249133589230079809850869266e-0035L,
	+1.710557978782419482731492281155256146438e-0036L,
	-2.148837714938406737587489024152464642738e-0035L,
	-4.273007541330408144086077695573950943351e-0035L,
	-1.187512317830147119742251549090183099823e-0035L,
	+4.828271743385077560204615670566277021463e-0036L,
	+2.888285131340709127656514948635349311805e-0035L,
	-4.505233085580329558684272075904471228864e-0035L,
	+2.931630895327838681946984510160883959332e-0036L,
	+2.647698485118630114484469975939947791390e-0035L,
	+3.589320320845381187254017736531618320153e-0035L,
	+3.109409548262590459351847474032415851843e-0035L,
	+4.083234910839125531016836269706248922707e-0035L,
	+2.617081426185972174278972738311427223003e-0035L,
	+1.685638883876736468625598871602567025329e-0035L,
	+3.340709007044122362174996515517070074049e-0035L,
	+4.272448967674769643335827331513513914893e-0035L,
	-1.016337077502454982949287784426587554312e-0035L,
	-4.164820472415940877265629374001265181061e-0035L,
	-1.266702907529482683855413412028523879313e-0035L,
	-2.498295523749676738976415773050309926889e-0035L,
	-2.240244888035701528565322302010524216607e-0035L,
	+2.072673676633052237512344957839713494538e-0035L,
	-5.635620575073849011607547314084511148918e-0036L,
	+1.289773398786324444403985925780591709915e-0035L,
};
