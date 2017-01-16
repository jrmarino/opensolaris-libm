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
 * For i = 0L, ..., 75 let x(i) be the extended precision number
 * whose exponent is given by 0x3ffc + ((i + 8) >> 5) and whose
 * five most significant fraction bits are given by (i + 8) & 0x1f.
 * (The remaining fraction bits are zero and the integer bit is 1.)
 * Then _TBL_sinl_hi[i] := sin(x(i)) rounded to extended precisionL,
 * and _TBL_sinl_lo[i] ~ sin(x(i)) - _TBL_sinl_hi[i].
 */

#include "libm.h"

const long double _TBL_sinl_hi[] = {
	 1.5561499277355604121432509e-01L,
	 1.5947245893184341994353297e-01L,
	 1.6332749173661285085207024e-01L,
	 1.6718003236480673437500555e-01L,
	 1.7103002203139501927501524e-01L,
	 1.7487740199027218989302670e-01L,
	 1.7872211353515365937804412e-01L,
	 1.8256409800047155539783929e-01L,
	 1.8640329676226988454758749e-01L,
	 1.9023965123909906176839606e-01L,
	 1.9407310289290979115543571e-01L,
	 1.9790359322994628465735775e-01L,
	 2.0173106380163880472144652e-01L,
	 2.0555545620549551765724079e-01L,
	 2.0937671208599364370531084e-01L,
	 2.1319477313546989061102989e-01L,
	 2.1700958109501015675778940e-01L,
	 2.2082107775533849055107655e-01L,
	 2.2462920495770529235180901e-01L,
	 2.2843390459477474541995223e-01L,
	 2.3223511861151146241076006e-01L,
	 2.3603278900606633373558587e-01L,
	 2.3982685783066156443802536e-01L,
	 2.4361726719247488600575847e-01L,
	 2.4740395925452292959266856e-01L,
	 2.5496596041587846749013231e-01L,
	 2.6251239976915328146124702e-01L,
	 2.7004281671858503154006088e-01L,
	 2.7755675164633632592044860e-01L,
	 2.8505374594054742458945975e-01L,
	 2.9253334202332754361585744e-01L,
	 2.9999508337868305117438275e-01L,
	 3.0743851458038085066887951e-01L,
	 3.1486318131974525087106269e-01L,
	 3.2226863043338662567511427e-01L,
	 3.2965440993086017192298214e-01L,
	 3.3702006902225307624892253e-01L,
	 3.4436515814569840820730424e-01L,
	 3.5168922899481405922451731e-01L,
	 3.5899183454606505366498749e-01L,
	 3.6627252908604756136416898e-01L,
	 3.7353086823869294642950362e-01L,
	 3.8076640899239019207055991e-01L,
	 3.8797870972702504604426484e-01L,
	 3.9516733024093423623426119e-01L,
	 4.0233183177777311122311904e-01L,
	 4.0947177705329506611003562e-01L,
	 4.1658673028204111924766885e-01L,
	 4.2367625720393801036934428e-01L,
	 4.3073992511080319721861361e-01L,
	 4.3777730287275513286178799e-01L,
	 4.4478796096452721142060563e-01L,
	 4.5177147149168377657582618e-01L,
	 4.5872740821673659236961014e-01L,
	 4.6565534658516018269211988e-01L,
	 4.7255486375130445115036980e-01L,
	 4.7942553860420300028150759e-01L,
	 4.9307868575392305727079882e-01L,
	 5.0661145481425736764773474e-01L,
	 5.2002054195372700474845132e-01L,
	 5.3330267353602017331871271e-01L,
	 5.4645460691920356440616155e-01L,
	 5.5947313124736687740433047e-01L,
	 5.7235506823450724037203458e-01L,
	 5.8509727294046215482874185e-01L,
	 5.9769663453870153121657086e-01L,
	 6.1015007707579137127265265e-01L,
	 6.2245456022234368301943030e-01L,
	 6.3460708001526929683284300e-01L,
	 6.4660466959115237050095826e-01L,
	 6.5844439991056754159573505e-01L,
	 6.7012338047316289465094724e-01L,
	 6.8163876002333416675559724e-01L,
	 6.9298772724631791026551897e-01L,
	 7.0416751145453367277888060e-01L,
};

const long double _TBL_sinl_lo[] = {
	-4.4044420388485708604352042e-21L,
	-9.3658505779466794663857779e-22L,
	-5.2040678607071393508410817e-21L,
	-4.0395267481940078256007650e-21L,
	 6.3327332576496468315469778e-21L,
	 2.6586707822142093837984364e-21L,
	-2.6878787450050744237345282e-21L,
	 1.7063635662305595250654237e-21L,
	 4.7924921282538555045455343e-21L,
	-4.4101691066939302183010470e-21L,
	 6.1948600915447822830980496e-22L,
	-4.9638413649749502251618971e-21L,
	 3.5916271597651546227926473e-21L,
	-4.0777150323673712797756569e-22L,
	 6.5799136599779898603647660e-21L,
	 5.0431441802236271279596547e-21L,
	 2.7886967636804383702412094e-21L,
	 1.7797941915507094664564119e-21L,
	-1.3804554392939635583829251e-21L,
	 4.7855981187615466625152631e-21L,
	 3.1708211390406997503004900e-21L,
	-1.5157834044725652569873263e-22L,
	 3.3438946731684019204631903e-21L,
	 6.4724798056855877111175401e-21L,
	 4.1801428671953314697839700e-21L,
	-2.5757365367012227482016023e-21L,
	-1.0297394515771810295074032e-20L,
	 1.2694179637735656722464528e-20L,
	 1.5748512781011179565308673e-21L,
	-1.6967184859202905792705521e-21L,
	 8.8448858652331336251731737e-21L,
	-1.1134468969040340293241825e-20L,
	 1.6234471791025321420471804e-21L,
	-6.0263738196054484651751291e-21L,
	 1.2631652295822646843414172e-20L,
	-8.6644101687582762853694906e-21L,
	 1.2359222174923859397271358e-20L,
	-1.3219821587241831508027981e-22L,
	-1.9324110998995296922101291e-21L,
	 1.2722808830089214240915385e-20L,
	 8.7403704479785940299212466e-21L,
	-1.2663863629342751015966219e-20L,
	-1.3359206065200525634208487e-20L,
	 6.8148547822187652382727319e-21L,
	 1.0571450573402892191582257e-20L,
	-6.0134413552023063129130024e-21L,
	 1.2658405457632407447211937e-20L,
	 1.1443598275137284797608912e-20L,
	-7.6602922503647693246330011e-21L,
	-2.2920876394624080624512678e-21L,
	-1.6901640257671788285214336e-22L,
	 1.2450383440926973698285013e-20L,
	 5.8625687909310643361252782e-21L,
	 7.6848891207540014891539434e-21L,
	-1.0920363727912466924531705e-20L,
	-3.8184802762435242280438906e-21L,
	-8.2196498741416868399433703e-21L,
	-5.6622687407305065056015130e-21L,
	-5.4387357437209102117877930e-21L,
	 1.1762381857741709383097597e-20L,
	 1.0418391756080576218864700e-20L,
	-2.8119958331524728369894697e-21L,
	-1.9486464776808433575964276e-20L,
	 1.2919131320458122775352322e-20L,
	-2.3342533395278737494836457e-20L,
	 2.2076763147253802020227787e-20L,
	 1.0897468372542621634126622e-21L,
	 2.2496400209117994020651730e-20L,
	 1.7466909662624346932394383e-20L,
	 2.3083902445127091336067492e-20L,
	-6.1510978111621596519832919e-21L,
	 3.5843424075843715436394953e-21L,
	-2.2355288181001597796661994e-20L,
	 1.6296521874464521140945741e-20L,
	 1.1789113655896899561477559e-21L,
};
