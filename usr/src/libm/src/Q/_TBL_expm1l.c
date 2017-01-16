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
 * Table of constants for expm1l.
 * By K.C. Ng, June 30, 1995
 */

#include "libm.h"

const long double _TBL_expm1lx[] = {
	+7.8124999999999999999999999999995004619e-03L,
	+2.3437499999999999999999999999998790275e-02L,
	+3.9062499999999999999999999999981095794e-02L,
	+5.4687500000000000000000000000007637516e-02L,
	+7.0312500000000000000000000000001673152e-02L,
	+8.5937500000000000000000000000004285194e-02L,
	+1.0156249999999999999999999999997969348e-01L,
	+1.1718749999999999999999999999998630182e-01L,
	+1.3281249999999999999999999999999246480e-01L,
	+1.4843750000000000000000000000000096296e-01L,
	+1.6406249999999999999999999999999947037e-01L,
	+1.7968750000000000000000000000007190941e-01L,
	+1.9531249999999999999999999999999874815e-01L,
	+2.1093749999999999999999999999999877222e-01L,
	+2.2656250000000000000000000000000019259e-01L,
	+2.4218749999999999999999999999999800185e-01L,
	+2.5781249999999999999999999999996335918e-01L,
	+2.7343749999999999999999999999999903704e-01L,
	+2.8906249999999999999999999999998362960e-01L,
	+3.0468750000000000000000000000000240741e-01L,
	+3.2031249999999999999999999999999542592e-01L,
	+3.3593749999999999999999999999999619629e-01L,
	+3.5156250000000000000000000000001040002e-01L,
	+3.6718749999999999999999999999999316295e-01L,
	+3.8281250000000000000000000000000871483e-01L,
	+3.9843750000000000000000000000000385186e-01L,
	+4.1406249999999999999999999999999975926e-01L,
	+4.2968750000000000000000000000000385186e-01L,
	+4.4531250000000000000000000000032119697e-01L,
	+4.6093749999999999999999999999999956667e-01L,
	+4.7656250000000000000000000000000134815e-01L,
	+4.9218749999999999999999999999999388517e-01L,
	+5.0781249999999999999999999999999778518e-01L,
	+5.2343749999999999999999999999999325925e-01L,
	+5.3906249999999999999999999999990649610e-01L,
	+5.5468750000000000000000000000000452594e-01L,
	+5.7031250000000000000000000000000645187e-01L,
	+5.8593749999999999999999999999999807407e-01L,
	+6.0156250000000000000000000000000182963e-01L,
	+6.1718750000000000000000000000000048148e-01L,
	+6.3281250000000000000000000000000943706e-01L,
	+6.4843749999999999999999999999999470369e-01L,
	+6.6406250000000000000000000000000192593e-01L,
	+6.7968750000000000000000000000000693335e-01L,
	+6.9531250000000000000000000000001482966e-01L,
	+7.1093750000000000000000000000000154074e-01L,
	+7.2656250000000000000000000000000385186e-01L,
	+7.4218750000000000000000000000000115556e-01L,
	+7.5781250000000000000000000000000048148e-01L,
	+7.7343749999999999999999999999999942222e-01L,
	+7.8906249999999999999999999999999720740e-01L,
	+8.0468749999999999999999999999999634073e-01L,
	+8.2031249999999999999999999999999797777e-01L,
	+8.3593750000000000000000000000000828150e-01L,
	+8.5156249999999999999999999999999865185e-01L,
	+8.6718749999999999999999999999999682222e-01L,
	+8.8281249999999999999999999999999749629e-01L,
	+8.9843749999999999999999999999999836296e-01L,
	+9.1406249999999999999999999999999229628e-01L,
	+9.2968750000000000000000000000000462223e-01L,
	+9.4531249999999999999999999999999499258e-01L,
	+9.6093749999999999999999999999999894074e-01L,
	+9.7656249999999999999999999999999855555e-01L,
	+9.9218750000000000000000000000000028889e-01L,
	+1.0078124999999999999999999999999870963e+00L,
	+1.0234375000000000000000000000000003852e+00L,
	+1.0390624999999999999999999999999998074e+00L,
	+1.0546874999999999999999999999999801629e+00L,
	+1.0703125000000000000000000000000182963e+00L,
	+1.0859375000000000000000000000000021185e+00L,
	+1.1015624999999999999999999999999978815e+00L,
	+1.1171874999999999999999999999999986518e+00L,
	+1.1328124999999999999999999999999984593e+00L,
	+1.1484374999999999999999999999999980741e+00L,
	+1.1640625000000000000000000000000000000e+00L,
	+1.1796874999999999999999999999999998074e+00L,
	+1.1953125000000000000000000000000196445e+00L,
	+1.2109374999999999999999999999999976889e+00L,
	+1.2265625000000000000000000000000017333e+00L,
	+1.2421874999999999999999999999999976889e+00L,
	+1.2578124999999999999999999999999980741e+00L,
	+1.2734374999999999999999999999999951852e+00L,
	-7.8125000000000000000000000000074012886e-03L,
	-2.3437499999999999999999999999997418050e-02L,
	-3.9062499999999999999999999999998134255e-02L,
	-5.4687500000000000000000000000006361587e-02L,
	-7.0312500000000000000000000000006271309e-02L,
	-8.5937500000000000000000000000001721300e-02L,
	-1.0156250000000000000000000000000020463e-01L,
	-1.1718750000000000000000000000000290093e-01L,
	-1.3281249999999999999999999999999987963e-01L,
	-1.4843749999999999999999999999999942222e-01L,
	-1.6406250000000000000000000000000026482e-01L,
	-1.7968750000000000000000000000000052963e-01L,
	-1.9531249999999999999999999999999867592e-01L,
	-2.1093750000000000000000000000000081852e-01L,
	-2.2656250000000000000000000000000250371e-01L,
	-2.4218749999999999999999999999999718333e-01L,
	-2.5781250000000000000000000000001059261e-01L,
	-2.7343749999999999999999999999999557036e-01L,
	-2.8906250000000000000000000000000520001e-01L,
	-3.0468749999999999999999999999999792963e-01L,
	-3.2031250000000000000000000000000231112e-01L,
	-3.3593749999999999999999999999999383702e-01L,
	-3.5156249999999999999999999999999903704e-01L,
	-3.6718749999999999999999999999999634073e-01L,
	-3.8281249999999999999999999999999956667e-01L,
	-3.9843750000000000000000000000000004815e-01L,
	-4.1406249999999999999999999999999870000e-01L,
	-4.2968750000000000000000000000000216667e-01L,
	-4.4531250000000000000000000000000072222e-01L,
	-4.6093749999999999999999999999999513703e-01L,
	-4.7656250000000000000000000000000539260e-01L,
	-4.9218749999999999999999999999999759259e-01L,
	-5.0781250000000000000000000000000067408e-01L,
	-5.2343750000000000000000000000001386670e-01L,
	-5.3906249999999999999999999999996427400e-01L,
	-5.5468750000000000000000000000000404445e-01L,
	-5.7031249999999999999999999999998536293e-01L,
	-5.8593749999999999999999999999999634073e-01L,
	-6.0156250000000000000000000000000028889e-01L,
	-6.1718749999999999999999999999998468886e-01L,
	-6.3281249999999999999999999999999335554e-01L,
	-6.4843750000000000000000000000000356297e-01L,
	-6.6406250000000000000000000000000019259e-01L,
	-6.7968750000000000000000000000000067408e-01L,
	-6.9531249999999999999999999999998439997e-01L,
	-7.1093750000000000000000000000000009630e-01L,
	-7.2656250000000000000000000000000414075e-01L,
	-7.4218749999999999999999999999998738516e-01L,
	-7.5781250000000000000000000000000019259e-01L,
	-7.7343750000000000000000000000000808891e-01L,
	-7.8906250000000000000000000000000028889e-01L,
	-8.0468750000000000000000000000000096296e-01L,
	-8.2031249999999999999999999999999634073e-01L,
	-8.3593750000000000000000000000000086667e-01L,
	-8.5156250000000000000000000000000115556e-01L,
	-8.6718750000000000000000000000000028889e-01L,
	-8.8281250000000000000000000000000577779e-01L,
	-8.9843750000000000000000000000000587409e-01L,
	-9.1406250000000000000000000000000654816e-01L,
	-9.2968749999999999999999999999999210369e-01L,
	-9.4531250000000000000000000000000115556e-01L,
	-9.6093749999999999999999999999999682222e-01L,
	-9.7656250000000000000000000000000298519e-01L,
	-9.9218749999999999999999999999999711111e-01L,
	-1.0078124999999999999999999999999953778e+00L,
	-1.0234375000000000000000000000000279260e+00L,
	-1.0390625000000000000000000000000000000e+00L,
	-1.0546875000000000000000000000000042370e+00L,
	-1.0703124999999999999999999999999969185e+00L,
	-1.0859374999999999999999999999999965333e+00L,
	-1.1015625000000000000000000000000144445e+00L,
	-1.1171875000000000000000000000000007704e+00L,
	-1.1328125000000000000000000000000052000e+00L,
	-1.1484375000000000000000000000000021185e+00L,
	-1.1640625000000000000000000000000188741e+00L,
	-1.1796874999999999999999999999999915259e+00L,
	-1.1953125000000000000000000000000196445e+00L,
	-1.2109374999999999999999999999999965333e+00L,
	-1.2265624999999999999999999999999940296e+00L,
	-1.2421874999999999999999999999999955704e+00L,
	-1.2578125000000000000000000000000036593e+00L,
	-1.2734375000000000000000000000000005778e+00L,
};
const long double _TBL_expm1l[] = {
	+7.8430972064479776934535597601230757455e-03L,
	+2.3714316602357916968850532165767719684e-02L,
	+3.9835471336230000576622009875172135295e-02L,
	+5.6210497316931971181336703768137839969e-02L,
	+7.2843392434877444411300095010815562014e-02L,
	+8.9738217538093231018282025418516874073e-02L,
	+1.0689909742365748278760239374175648642e-01L,
	+1.2433022184475071745173290544494115241e-01L,
	+1.4203584653356558967616143134879189360e-01L,
	+1.6002029424032514702921521389409692713e-01L,
	+1.7828795578866324266314330819585528511e-01L,
	+1.9684329114762477118219685277015441058e-01L,
	+2.1569083052054745183001825454039531082e-01L,
	+2.3483517545109100468401611087600122614e-01L,
	+2.5428099994668375200482125309068587301e-01L,
	+2.7403305161966092927649653871633746915e-01L,
	+2.9409615284637330982611062681002354822e-01L,
	+3.1447520194454913428413492197987169290e-01L,
	+3.3517517436919679261104091066359163835e-01L,
	+3.5620112392734023305848825938576026618e-01L,
	+3.7755818401188367036076223788924855083e-01L,
	+3.9925156885490683578620594549518425777e-01L,
	+4.2128657480069675555953993770759156716e-01L,
	+4.4366858159882686275236684344276542291e-01L,
	+4.6640305371759914220725806222619001343e-01L,
	+4.8949554167816997960557644740137111180e-01L,
	+5.1295168340968543562438375411433268970e-01L,
	+5.3677720562575679548630956319776281677e-01L,
	+5.6097792522261245434042965895343734385e-01L,
	+5.8555975069926749109404773234379454282e-01L,
	+6.1052868360005765883685767151390117210e-01L,
	+6.3589081997988998017269448860547030419e-01L,
	+6.6165235189256768193303746403901387346e-01L,
	+6.8781956890255283724467962874956344875e-01L,
	+7.1439885962053580513691701731111144172e-01L,
	+7.4139671326318637019829227657113109938e-01L,
	+7.6881972123746738864840365608134114398e-01L,
	+7.9667457874989774401796242919906293119e-01L,
	+8.2496808644115750689424843988747369733e-01L,
	+8.5370715204643438037652998773947217833e-01L,
	+8.8289879208191679750745518776052322714e-01L,
	+9.1255013355784542053624989476899678486e-01L,
	+9.4266841571854127598629758313676072782e-01L,
	+9.7326099180983534572639774176307759762e-01L,
	+1.0043353308743311241896996041635484486e+00L,
	+1.0358990195749384471803078942778539846e+00L,
	+1.0679597640471238000138982954032239149e+00L,
	+1.1005253917803293237405302109843095228e+00L,
	+1.1336038535290198596069082796475886372e+00L,
	+1.1672032252538246054702826653026856058e+00L,
	+1.2013317100932473053430319197695098859e+00L,
	+1.2359976403664263564195928556324051853e+00L,
	+1.2712094796074337986378900692396989892e+00L,
	+1.3069758246316098519065681271390426992e+00L,
	+1.3433054076344374874670823571053750423e+00L,
	+1.3802070983234694643656048039370676504e+00L,
	+1.4176899060838283316233663173665695732e+00L,
	+1.4557629821778080933856445408266366139e+00L,
	+1.4944356219791145601003068865880283870e+00L,
	+1.5337172672422898656593276319684411587e+00L,
	+1.5736175084078752204957296405891018055e+00L,
	+1.6141460869438746959611789503655886752e+00L,
	+1.6553128977240916980462361132966809382e+00L,
	+1.6971279914439187908098398388318058200e+00L,
	+1.7396015770741706739548391625061335312e+00L,
	+1.7827440243535594070547844776995992896e+00L,
	+1.8265658663204204072713762882878497127e+00L,
	+1.8710778018843073303053045700866748054e+00L,
	+1.9162906984380836781353147778063807290e+00L,
	+1.9622155945111488641976761209920359164e+00L,
	+2.0088637024644465094546949911966296733e+00L,
	+2.0562464112279129437484158431835361592e+00L,
	+2.1043752890810342484246997824723919209e+00L,
	+2.1532620864771907009732038831535016010e+00L,
	+2.2029187389124781729299756967091584890e+00L,
	+2.2533573698397068911414662577557965622e+00L,
	+2.3045902936282890023428920188543322512e+00L,
	+2.3566300185707375845529318204056188573e+00L,
	+2.4094892499365111287660263409108200844e+00L,
	+2.4631808930739490736114262571853290077e+00L,
	+2.5177180565610557168667363422785819682e+00L,
	+2.5731140554059017538295927080989585090e+00L,
	-7.7820617397564878940627738863895136168e-03L,
	-2.3164975049937966141654020345517900132e-02L,
	-3.8309398394574704340244721980137502162e-02L,
	-5.3219029217871103345945692892173875140e-02L,
	-6.7897507640472422098597150880870814431e-02L,
	-8.2348417348184187852664478898998721220e-02L,
	-9.6575286466913289047103004903893595054e-02L,
	-1.1058158842404436382535801893754083366e-01L,
	-1.2437074279646178545389116639858446817e-01L,
	-1.3794611614542428546897208319214646321e-01L,
	-1.5131102283849604551092782942638950286e-01L,
	-1.6446872585873492869892658849405193342e-01L,
	-1.7742243760133541028616024893906020644e-01L,
	-1.9017532065792070445541830028432254804e-01L,
	-2.0273048858867556872072433107848955384e-01L,
	-2.1509100668250829875574108587424583890e-01L,
	-2.2725989270542750384925893490015094814e-01L,
	-2.3924011763731637587872084997993792064e-01L,
	-2.5103460639728433199192216502316397159e-01L,
	-2.6264623855777312240316411149867979990e-01L,
	-2.7407784904759174916236707216223561007e-01L,
	-2.8533222884405183877364930326430409924e-01L,
	-2.9641212565437245046372839566093886675e-01L,
	-3.0732024458652068208051596680746383072e-01L,
	-3.1805924880965185639883349668276001738e-01L,
	-3.2863176020431053139357768964876694788e-01L,
	-3.3904036000255107819096872094974754682e-01L,
	-3.4928758941813410931539692705947339063e-01L,
	-3.5937595026695261691197788694876862518e-01L,
	-3.6930790557783929525168292907013160482e-01L,
	-3.7908588019390417343445352368401927192e-01L,
	-3.8871226136454937222268435896035706784e-01L,
	-3.9818939932830552279841068785563696096e-01L,
	-4.0751960788663214438675145523141552015e-01L,
	-4.1670516496882207157854692957232201487e-01L,
	-4.2574831318814785027807613334156070311e-01L,
	-4.3465126038938588296698375694570623290e-01L,
	-4.4341618018785199889104786302733041801e-01L,
	-4.5204521250008005232823143909224611574e-01L,
	-4.6054046406627311177860364731167719334e-01L,
	-4.6890400896465479423105583940253757841e-01L,
	-4.7713788911784632111786130180348641941e-01L,
	-4.8524411479139292568322765140558720714e-01L,
	-4.9322466508456132479074344820321183415e-01L,
	-5.0108148841352808120907176750144850100e-01L,
	-5.0881650298707682468469397665961648404e-01L,
	-5.1643159727492047118140006480748942245e-01L,
	-5.2392863046876277909203259884139061144e-01L,
	-5.3130943293621180856911747373956708600e-01L,
	-5.3857580666765610494466923948125161529e-01L,
	-5.4572952571621270908956480845806990458e-01L,
	-5.5277233663085440607996537742519552762e-01L,
	-5.5970595888282195827936433920573211501e-01L,
	-5.6653208528542542950338319090135722295e-01L,
	-5.7325238240733709291016556235278458118e-01L,
	-5.7986849097947682625807457952262425338e-01L,
	-5.8638202629558933380643321697780798620e-01L,
	-5.9279457860661099402232802681583606392e-01L,
	-5.9910771350892261602101192647121362362e-01L,
	-6.0532297232658289493900937468812013977e-01L,
	-6.1144187248763588685320419660027392238e-01L,
	-6.1746590789458437705718363441235796711e-01L,
	-6.2339654928911959113469156706514092208e-01L,
	-6.2923524461119629598145525663487507890e-01L,
	-6.3498341935254095737853086332102468069e-01L,
	-6.4064247690467926157560858675744165996e-01L,
	-6.4621379890156797026959945044832806294e-01L,
	-6.5169874555691476103560779451668832748e-01L,
	-6.5709865599626840836245660190447925603e-01L,
	-6.6241484858396038364664323096343822726e-01L,
	-6.6764862124497769549523628863318702845e-01L,
	-6.7280125178184555417288842186006604551e-01L,
	-6.7787399818659722569870081614203949644e-01L,
	-6.8286809894790724165768340684449330930e-01L,
	-6.8778477335346294994617200009875163606e-01L,
	-6.9262522178764822913249147051072428209e-01L,
	-6.9739062602461204459956440664519817754e-01L,
	-7.0208214951679339786562882012396622127e-01L,
	-7.0670093767897311117765076057926938575e-01L,
	-7.1124811816792179736856679611852620191e-01L,
	-7.1572480115771228979753508374143873445e-01L,
	-7.2013207961076374868941367244540733250e-01L,
};
