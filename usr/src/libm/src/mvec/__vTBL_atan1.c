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

#pragma ident	"@(#)__vTBL_atan1.c	1.3	06/01/31 SMI"

const double __vlibm_TBL_atan1[] __attribute__((aligned(32))) = {

/* i=  -2 conup conlo = 0.0      */                    0.0 ,                     0.0 ,
/* i=  -1 PI/2 upper, lower      */ 1.570796326794896558E+00, 6.123233995736765886e-17,
                                 /*        3ff921fb54442d18,         3c91a62633145c07, */


/* i=       0 atan(3F900000...) */  1.56237286204768313E-02, -4.91360013656630395E-19,
/* i=       0 atan(3F900000...)            3F8FFF555BBB729B,         BC2220C39D4DFF50, */

/* i=       1 atan(3F910000...) */  1.66000375562312640E-02,  1.12189118956867269E-18,
/* i=       1 atan(3F910000...)            3F90FF99A9AA60D7,         3C34B1FB39D277D8, */

/* i=       2 atan(3F920000...) */  1.75763148444955872E-02,  6.59519250301009539E-19,
/* i=       2 atan(3F920000...)            3F91FF8685C3E636,         3C2854FBB35044B1, */

/* i=       3 atan(3F930000...) */  1.85525586258889763E-02,  1.39203477545012197E-19,
/* i=       3 atan(3F930000...)            3F92FF712238A4B8,         3C048AF56CEBE552, */

/* i=       4 atan(3F940000...) */  1.95287670414137082E-02, -9.79999553454266918E-19,
/* i=       4 atan(3F940000...)            3F93FF595F18A700,         BC3213EAC36CFB2C, */

/* i=       5 atan(3F950000...) */  2.05049382324763683E-02, -8.40094761552091156E-19,
/* i=       5 atan(3F950000...)            3F94FF3F1C75BEE7,         BC2EFE787F0F4330, */

/* i=       6 atan(3F960000...) */  2.14810703409090559E-02, -4.19450646799657488E-20,
/* i=       6 atan(3F960000...)            3F95FF223A639D5C,         BBE8C28F1824574A, */

/* i=       7 atan(3F970000...) */  2.24571615089905717E-02, -1.30959312135654387E-18,
/* i=       7 atan(3F970000...)            3F96FF0298F7EA3F,         BC382860F0066622, */

/* i=       8 atan(3F980000...) */  2.34332098794675855E-02, -1.09469246421805015E-18,
/* i=       8 atan(3F980000...)            3F97FEE0184A5C36,         BC343189FC0A354B, */

/* i=       9 atan(3F990000...) */  2.44092135955758099E-02, -1.47897509599299710E-18,
/* i=       9 atan(3F990000...)            3F98FEBA9874D084,         BC3B48432E1BE204, */

/* i=      10 atan(3F9A0000...) */  2.53851708010611396E-02, -1.34303200040391535E-18,
/* i=      10 atan(3F9A0000...)            3F99FE91F99362D6,         BC38C64A0FD5DBE3, */

/* i=      11 atan(3F9B0000...) */  2.63610796402007873E-02,  1.37267443271608158E-18,
/* i=      11 atan(3F9B0000...)            3F9AFE661BC4850F,         3C395245904A67C3, */

/* i=      12 atan(3F9C0000...) */  2.73369382578244127E-02, -8.16108165671393861E-19,
/* i=      12 atan(3F9C0000...)            3F9BFE36DF291712,         BC2E1BEC7756100E, */

/* i=      13 atan(3F9D0000...) */  2.83127447993351995E-02,  8.59249306270865423E-19,
/* i=      13 atan(3F9D0000...)            3F9CFE0423E47E7D,         3C2FB36157FAFE79, */

/* i=      14 atan(3F9E0000...) */  2.92884974107309737E-02, -7.76024364493026302E-19,
/* i=      14 atan(3F9E0000...)            3F9DFDCDCA1CBE70,         BC2CA157C8222A15, */

/* i=      15 atan(3F9F0000...) */  3.02641942386252458E-02, -1.66574467444210944E-18,
/* i=      15 atan(3F9F0000...)            3F9EFD93B1FA8F3E,         BC3EBA41BEEDF844, */

/* i=      16 atan(3FA00000...) */  3.12398334302682774E-02, -1.18844271158774798E-18,
/* i=      16 atan(3FA00000...)            3F9FFD55BBA97625,         BC35EC431444912C, */

/* i=      17 atan(3FA10000...) */  3.31909314971115949E-02, -9.42939153905567217E-19,
/* i=      17 atan(3FA10000...)            3FA0FE66DA9B94EE,         BC3164E77D4EB175, */

/* i=      18 atan(3FA20000...) */  3.51417768027967800E-02,  2.65885150818196357E-18,
/* i=      18 atan(3FA20000...)            3FA1FE1A5C2EC497,         3C4886091E8FC4CB, */

/* i=      19 atan(3FA30000...) */  3.70923545503918164E-02, -1.94050652720581784E-18,
/* i=      19 atan(3FA30000...)            3FA2FDC4E3737DDD,         BC41E5E438D0BA04, */

/* i=      20 atan(3FA40000...) */  3.90426499551669928E-02,  6.27126337421308897E-19,
/* i=      20 atan(3FA40000...)            3FA3FD65F169C9D9,         3C27230A716461B5, */

/* i=      21 atan(3FA50000...) */  4.09926482452637811E-02,  2.47687641119150859E-18,
/* i=      21 atan(3FA50000...)            3FA4FCFD072DFF79,         3C46D85BEC38D078, */

/* i=      22 atan(3FA60000...) */  4.29423346623621707E-02,  2.03095297887322147E-18,
/* i=      22 atan(3FA60000...)            3FA5FC89A5FA3B2D,         3C42BB73BF4E7F99, */

/* i=      23 atan(3FA70000...) */  4.48916944623464972E-02,  2.31751818996581527E-19,
/* i=      23 atan(3FA70000...)            3FA6FC0B4F27D5BB,         3C1119AB07E9C009, */

/* i=      24 atan(3FA80000...) */  4.68407129159696539E-02, -1.65567744225495210E-19,
/* i=      24 atan(3FA80000...)            3FA7FB818430DA2A,         BC086EF8F794F105, */

/* i=      25 atan(3FA90000...) */  4.87893753095156174E-02,  2.91348767453902927E-18,
/* i=      25 atan(3FA90000...)            3FA8FAEBC6B17ABA,         3C4ADF473CC8D797, */

/* i=      26 atan(3FAA0000...) */  5.07376669454602178E-02,  2.07462271032410652E-18,
/* i=      26 atan(3FAA0000...)            3FA9FA49986984DF,         3C4322907AF0ABC2, */

/* i=      27 atan(3FAB0000...) */  5.26855731431300420E-02,  2.86866232988833092E-18,
/* i=      27 atan(3FAB0000...)            3FAAF99A7B3DD42F,         3C4A756FFAAB786E, */

/* i=      28 atan(3FAC0000...) */  5.46330792393594777E-02, -2.66980035901898370E-18,
/* i=      28 atan(3FAC0000...)            3FABF8DDF139C444,         BC489FE34B2A7FA8, */

/* i=      29 atan(3FAD0000...) */  5.65801705891457105E-02,  3.25489507698250449E-18,
/* i=      29 atan(3FAD0000...)            3FACF8137C90A177,         3C4E0567596F063F, */

/* i=      30 atan(3FAE0000...) */  5.85268325663017702E-02, -2.48271181407783583E-19,
/* i=      30 atan(3FAE0000...)            3FADF73A9F9F1882,         BC1251B5C410BCB4, */

/* i=      31 atan(3FAF0000...) */  6.04730505641073168E-02, -5.66989890333967427E-19,
/* i=      31 atan(3FAF0000...)            3FAEF652DCECA4DC,         BC24EB116F8EA623, */

/* i=      32 atan(3FB00000...) */  6.24188099959573500E-02, -1.54907563082950458E-18,
/* i=      32 atan(3FB00000...)            3FAFF55BB72CFDEA,         BC3C934D86D23F1D, */

/* i=      33 atan(3FB10000...) */  6.63088949198234884E-02, -4.88592398930400059E-19,
/* i=      33 atan(3FB10000...)            3FB0F99EA71D52A7,         BC22069FEEC3624F, */

/* i=      34 atan(3FB20000...) */  7.01969710718705203E-02, -1.79819216032204589E-18,
/* i=      34 atan(3FB20000...)            3FB1F86DBF082D59,         BC4095DC7732EF81, */

/* i=      35 atan(3FB30000...) */  7.40829225490337306E-02,  1.35448289530322996E-19,
/* i=      35 atan(3FB30000...)            3FB2F719318A4A9A,         3C03FD1779B9801F, */

/* i=      36 atan(3FB40000...) */  7.79666338315423008E-02,  5.80455187314335664E-18,
/* i=      36 atan(3FB40000...)            3FB3F59F0E7C559D,         3C5AC4CE285DF847, */

/* i=      37 atan(3FB50000...) */  8.18479898030765457E-02,  1.73846131383378367E-18,
/* i=      37 atan(3FB50000...)            3FB4F3FD677292FB,         3C4008D36264979E, */

/* i=      38 atan(3FB60000...) */  8.57268757707448092E-02,  5.34719414350295085E-18,
/* i=      38 atan(3FB60000...)            3FB5F2324FD2D7B2,         3C58A8DA4401318E, */

/* i=      39 atan(3FB70000...) */  8.96031774848717461E-02, -1.08082588355136405E-18,
/* i=      39 atan(3FB70000...)            3FB6F03BDCEA4B0D,         BC33F00E512FA17D, */

/* i=      40 atan(3FB80000...) */  9.34767811585894698E-02, -6.28447259954209545E-18,
/* i=      40 atan(3FB80000...)            3FB7EE182602F10F,         BC5CFB654C0C3D98, */

/* i=      41 atan(3FB90000...) */  9.73475734872236709E-02,  2.51506589544357698E-18,
/* i=      41 atan(3FB90000...)            3FB8EBC54478FB28,         3C4732880CAD24CC, */

/* i=      42 atan(3FBA0000...) */  1.01215441667466668E-01,  5.68120255862341373E-18,
/* i=      42 atan(3FBA0000...)            3FB9E94153CFDCF1,         3C5A332E1D69C47E, */

/* i=      43 atan(3FBB0000...) */  1.05080273416329528E-01,  3.03631931857741762E-18,
/* i=      43 atan(3FBB0000...)            3FBAE68A71C722B8,         3C4C014E6910B9DB, */

/* i=      44 atan(3FBC0000...) */  1.08941956989865793E-01,  6.82671220724095851E-18,
/* i=      44 atan(3FBC0000...)            3FBBE39EBE6F07C3,         3C5F7B8F29A05987, */

/* i=      45 atan(3FBD0000...) */  1.12800381201659389E-01,  1.86724154759436245E-18,
/* i=      45 atan(3FBD0000...)            3FBCE07C5C3CCA32,         3C4138E6425918A7, */

/* i=      46 atan(3FBE0000...) */  1.16655435441069349E-01,  5.48792581210869929E-18,
/* i=      46 atan(3FBE0000...)            3FBDDD21701EBA6E,         3C594EFFCD76FE58, */

/* i=      47 atan(3FBF0000...) */  1.20507009691224562E-01, -5.32529096262256550E-19,
/* i=      47 atan(3FBF0000...)            3FBED98C2190043B,         BC23A598592C7B13, */

/* i=      48 atan(3FC00000...) */  1.24354994546761438E-01, -3.12532414245393831E-18,
/* i=      48 atan(3FC00000...)            3FBFD5BA9AAC2F6E,         BC4CD37686760C17, */

/* i=      49 atan(3FC10000...) */  1.32039761614638762E-01, -1.27692540070995953E-17,
/* i=      49 atan(3FC10000...)            3FC0E6ADCCF40882,         BC6D71A31BB98D0D, */

/* i=      50 atan(3FC20000...) */  1.39708874289163648E-01, -2.95798642473158131E-18,
/* i=      50 atan(3FC20000...)            3FC1E1FAFB043727,         BC4B485914DACF8C, */

/* i=      51 atan(3FC30000...) */  1.47361481088651630E-01,  5.40959914766629796E-18,
/* i=      51 atan(3FC30000...)            3FC2DCBDB2FBA1FF,         3C58F28705561534, */

/* i=      52 atan(3FC40000...) */  1.54996741923940973E-01,  9.58541559411432383E-18,
/* i=      52 atan(3FC40000...)            3FC3D6EEE8C6626C,         3C661A3B0CE9281B, */

/* i=      53 atan(3FC50000...) */  1.62613828597948568E-01,  7.78447064310625246E-18,
/* i=      53 atan(3FC50000...)            3FC4D087A9DA4F17,         3C61F323F1ADF158, */

/* i=      54 atan(3FC60000...) */  1.70211925285474408E-01, -3.54116407980212514E-18,
/* i=      54 atan(3FC60000...)            3FC5C9811E3EC26A,         BC5054AB2C010F3D, */

/* i=      55 atan(3FC70000...) */  1.77790228992676075E-01, -4.02958210085442233E-18,
/* i=      55 atan(3FC70000...)            3FC6C1D4898933D9,         BC52954A7603C427, */

/* i=      56 atan(3FC80000...) */  1.85347949995694761E-01,  4.18069226884307898E-18,
/* i=      56 atan(3FC80000...)            3FC7B97B4BCE5B02,         3C5347B0B4F881CA, */

/* i=      57 atan(3FC90000...) */  1.92884312257974672E-01, -7.41459017624724575E-18,
/* i=      57 atan(3FC90000...)            3FC8B06EE2879C29,         BC6118CD30308C4F, */

/* i=      58 atan(3FCA0000...) */  2.00398553825878512E-01,  3.13995428718444929E-18,
/* i=      58 atan(3FCA0000...)            3FC9A6A8E96C8626,         3C4CF601E7B4348E, */

/* i=      59 atan(3FCB0000...) */  2.07889927202262986E-01,  7.33316066652089850E-18,
/* i=      59 atan(3FCB0000...)            3FCA9C231B403279,         3C60E8BBE89CCA85, */

/* i=      60 atan(3FCC0000...) */  2.15357699697738048E-01,  4.73816013007873192E-19,
/* i=      60 atan(3FCC0000...)            3FCB90D7529260A2,         3C217B10D2E0E5AA, */

/* i=      61 atan(3FCD0000...) */  2.22801153759394521E-01, -5.49882217244684317E-18,
/* i=      61 atan(3FCD0000...)            3FCC84BF8A742E6E,         BC595BDD0682EA26, */

/* i=      62 atan(3FCE0000...) */  2.30219587276843718E-01,  1.23134045291427032E-17,
/* i=      62 atan(3FCE0000...)            3FCD77D5DF205736,         3C6C648D1534597E, */

/* i=      63 atan(3FCF0000...) */  2.37612313865471242E-01,  1.05823143137111299E-17,
/* i=      63 atan(3FCF0000...)            3FCE6A148E96EC4D,         3C6866B22029F765, */

/* i=      64 atan(3FD00000...) */  2.44978663126864143E-01,  1.06987556187344514E-17,
/* i=      64 atan(3FD00000...)            3FCF5B75F92C80DD,         3C68AB6E3CF7AFBD, */

/* i=      65 atan(3FD10000...) */  2.59629629408257512E-01,  1.92387549246153041E-17,
/* i=      65 atan(3FD10000...)            3FD09DC597D86362,         3C762E47390CB865, */

/* i=      66 atan(3FD20000...) */  2.74167451119658789E-01,  8.26135357516377194E-18,
/* i=      66 atan(3FD20000...)            3FD18BF5A30BF178,         3C630CA4748B1BF8, */

/* i=      67 atan(3FD30000...) */  2.88587361894077410E-01, -1.42836995737725708E-17,
/* i=      67 atan(3FD30000...)            3FD278372057EF46,         BC7077CDD36DFC81, */

/* i=      68 atan(3FD40000...) */  3.02884868374971417E-01, -1.10108279030013690E-17,
/* i=      68 atan(3FD40000...)            3FD362773707EBCC,         BC6963A544B672D8, */

/* i=      69 atan(3FD50000...) */  3.17055753209147029E-01, -1.89392892429264215E-17,
/* i=      69 atan(3FD50000...)            3FD44AA436C2AF0A,         BC75D5E43C55B3BA, */

/* i=      70 atan(3FD60000...) */  3.31096076704132103E-01, -7.95261037579379870E-18,
/* i=      70 atan(3FD60000...)            3FD530AD9951CD4A,         BC62566480884082, */

/* i=      71 atan(3FD70000...) */  3.45002177207105132E-01, -2.29388047555783039E-17,
/* i=      71 atan(3FD70000...)            3FD614840309CFE2,         BC7A725715711F00, */

/* i=      72 atan(3FD80000...) */  3.58770670270572245E-01, -2.46238155826386349E-17,
/* i=      72 atan(3FD80000...)            3FD6F61941E4DEF1,         BC7C63AAE6F6E918, */

/* i=      73 atan(3FD90000...) */  3.72398446676754202E-01,  1.96123115048456534E-17,
/* i=      73 atan(3FD90000...)            3FD7D5604B63B3F7,         3C769C885C2B249A, */

/* i=      74 atan(3FDA0000...) */  3.85882669398073752E-01,  2.37882273249194087E-17,
/* i=      74 atan(3FDA0000...)            3FD8B24D394A1B25,         3C7B6D0BA3748FA8, */

/* i=      75 atan(3FDB0000...) */  3.99220769575252543E-01,  2.24659810561704206E-17,
/* i=      75 atan(3FDB0000...)            3FD98CD5454D6B18,         3C79E6C988FD0A77, */

/* i=      76 atan(3FDC0000...) */  4.12410441597387323E-01, -1.58765222777068909E-17,
/* i=      76 atan(3FDC0000...)            3FDA64EEC3CC23FD,         BC724DEC1B50B7FF, */

/* i=      77 atan(3FDD0000...) */  4.25449637370042266E-01,  2.33155307418928847E-17,
/* i=      77 atan(3FDD0000...)            3FDB3A911DA65C6C,         3C7AE187B1CA5040, */

/* i=      78 atan(3FDE0000...) */  4.38336559857957830E-01, -2.49427703062654091E-17,
/* i=      78 atan(3FDE0000...)            3FDC0DB4C94EC9F0,         BC7CC1CE70934C34, */

/* i=      79 atan(3FDF0000...) */  4.51069655988523499E-01, -2.27037952294204745E-17,
/* i=      79 atan(3FDF0000...)            3FDCDE53432C1351,         BC7A2CFA4418F1AD, */

/* i=      80 atan(3FE00000...) */  4.63647609000806094E-01,  2.26987774529616871E-17,
/* i=      80 atan(3FE00000...)            3FDDAC670561BB4F,         3C7A2B7F222F65E2, */

/* i=      81 atan(3FE10000...) */  4.88333951056405535E-01, -1.13732361893295846E-17,
/* i=      81 atan(3FE10000...)            3FDF40DD0B541418,         BC6A3992DC382A23, */

/* i=      82 atan(3FE20000...) */  5.12389460310737732E-01, -2.54627814728558035E-17,
/* i=      82 atan(3FE20000...)            3FE0657E94DB30D0,         BC7D5B495F6349E6, */

/* i=      83 atan(3FE30000...) */  5.35811237960463704E-01, -4.06379568348255750E-18,
/* i=      83 atan(3FE30000...)            3FE1255D9BFBD2A9,         BC52BDAEE1C0EE35, */

/* i=      84 atan(3FE40000...) */  5.58599315343562441E-01, -5.45563054859162639E-18,
/* i=      84 atan(3FE40000...)            3FE1E00BABDEFEB4,         BC5928DF287A668F, */

/* i=      85 atan(3FE50000...) */  5.80756353567670414E-01, -1.44146437819306691E-17,
/* i=      85 atan(3FE50000...)            3FE2958E59308E31,         BC709E73B0C6C087, */

/* i=      86 atan(3FE60000...) */  6.02287346134964152E-01,  2.95043073722840231E-17,
/* i=      86 atan(3FE60000...)            3FE345F01CCE37BB,         3C81021137C71102, */

/* i=      87 atan(3FE70000...) */  6.23199329934065904E-01,  2.67240388514009508E-17,
/* i=      87 atan(3FE70000...)            3FE3F13FB89E96F4,         3C7ECF8B492644F0, */

/* i=      88 atan(3FE80000...) */  6.43501108793284371E-01,  1.58347850514442862E-17,
/* i=      88 atan(3FE80000...)            3FE4978FA3269EE1,         3C72419A87F2A458, */

/* i=      89 atan(3FE90000...) */  6.63202992706093286E-01, -3.07605486442964900E-17,
/* i=      89 atan(3FE90000...)            3FE538F57B89061F,         BC81BB74ABDA520C, */

/* i=      90 atan(3FEA0000...) */  6.82316554874748071E-01,  6.94322367156000774E-18,
/* i=      90 atan(3FEA0000...)            3FE5D58987169B18,         3C60028E4BC5E7CA, */

/* i=      91 atan(3FEB0000...) */  7.00854407884450192E-01, -1.98762623433581612E-17,
/* i=      91 atan(3FEB0000...)            3FE66D663923E087,         BC76EA6FEBE8BBBA, */

/* i=      92 atan(3FEC0000...) */  7.18829999621624527E-01, -2.14783884444569830E-17,
/* i=      92 atan(3FEC0000...)            3FE700A7C5784634,         BC78C34D25AADEF6, */

/* i=      93 atan(3FED0000...) */  7.36257428981428097E-01,  3.47393764829945672E-17,
/* i=      93 atan(3FED0000...)            3FE78F6BBD5D315E,         3C8406A089803740, */

/* i=      94 atan(3FEE0000...) */  7.53151280962194414E-01, -2.42569346591820681E-17,
/* i=      94 atan(3FEE0000...)            3FE819D0B7158A4D,         BC7BF76229D3B917, */

/* i=      95 atan(3FEF0000...) */  7.69526480405658297E-01, -3.70499190560272129E-17,
/* i=      95 atan(3FEF0000...)            3FE89FF5FF57F1F8,         BC855B9A5E177A1B, */

/* i=      96 atan(3FF00000...) */  7.85398163397448279E-01,  3.06161699786838302E-17,
/* i=      96 atan(3FF00000...)            3FE921FB54442D18,         3C81A62633145C07, */

/* i=      97 atan(3FF10000...) */  8.15691923316223422E-01, -1.07145656277874308E-17,
/* i=      97 atan(3FF10000...)            3FEA1A25F2C82506,         BC68B4C3611182FC, */

/* i=      98 atan(3FF20000...) */  8.44153986113171051E-01, -4.84133701193491676E-17,
/* i=      98 atan(3FF20000...)            3FEB034F38649C88,         BC8BE88D6936F833, */

/* i=      99 atan(3FF30000...) */  8.70903457075652976E-01, -2.26982359074728705E-17,
/* i=      99 atan(3FF30000...)            3FEBDE70ED439FE7,         BC7A2B56372C05EF, */

/* i=     100 atan(3FF40000...) */  8.96055384571343927E-01,  2.92387628577430489E-17,
/* i=     100 atan(3FF40000...)            3FECAC7C57846F9E,         3C80DAE13AD18A6B, */

/* i=     101 atan(3FF50000...) */  9.19719605350416858E-01, -4.05743941285276792E-17,
/* i=     101 atan(3FF50000...)            3FED6E57CF4F0ACA,         BC8763B9456AE66E, */

/* i=     102 atan(3FF60000...) */  9.42000040379463610E-01,  5.46083748584668763E-17,
/* i=     102 atan(3FF60000...)            3FEE24DD44C855D1,         3C8F7AC612AB33D8, */

/* i=     103 atan(3FF70000...) */  9.62994330680936206E-01, -3.98666059521075245E-18,
/* i=     103 atan(3FF70000...)            3FEED0D97C9041C9,         BC52629E3B5DA490, */

/* i=     104 atan(3FF80000...) */  9.82793723247329054E-01,  1.39033110312309985E-17,
/* i=     104 atan(3FF80000...)            3FEF730BD281F69B,         3C7007887AF0CBBD, */

/* i=     105 atan(3FF90000...) */  1.00148313569423464E+00,  9.43830802354539200E-17,
/* i=     105 atan(3FF90000...)            3FF006132E34D617,         3C9B343DFA868D93, */

/* i=     106 atan(3FFA0000...) */  1.01914134426634972E+00,  1.00040188693667989E-17,
/* i=     106 atan(3FFA0000...)            3FF04E67277A01D7,         3C67115496C13EB6, */

/* i=     107 atan(3FFB0000...) */  1.03584125300880014E+00,  3.19431398178450371E-17,
/* i=     107 atan(3FFB0000...)            3FF092CE471853CC,         3C8269F9B3E200C2, */

/* i=     108 atan(3FFC0000...) */  1.05165021254837376E+00, -9.65056473146751351E-17,
/* i=     108 atan(3FFC0000...)            3FF0D38F2C5BA09F,         BC9BD0DC231BFD70, */

/* i=     109 atan(3FFD0000...) */  1.06663036531574362E+00, -5.95658963716037456E-17,
/* i=     109 atan(3FFD0000...)            3FF110EB007F39F7,         BC912B2FF85E5500, */

/* i=     110 atan(3FFE0000...) */  1.08083900054116833E+00, -1.56763225113590725E-17,
/* i=     110 atan(3FFE0000...)            3FF14B1DD5F90CE1,         BC7212D570A63FA2, */

/* i=     111 atan(3FFF0000...) */  1.09432890732118993E+00, -5.49067615502236423E-18,
/* i=     111 atan(3FFF0000...)            3FF1825F074030D9,         BC59523F0AF0D3B5, */

/* i=     112 atan(40000000...) */  1.10714871779409041E+00,  9.40447137356637941E-17,
/* i=     112 atan(40000000...)            3FF1B6E192EBBE44,         3C9B1B466A88828E, */

/* i=     113 atan(40010000...) */  1.13095374397916038E+00,  7.12383380453844630E-17,
/* i=     113 atan(40010000...)            3FF21862F3FADE36,         3C94887628D68748, */

/* i=     114 atan(40020000...) */  1.15257199721566761E+00, -9.15973850890037882E-17,
/* i=     114 atan(40020000...)            3FF270EF55A53A25,         BC9A66B1AF5F84FB, */

/* i=     115 atan(40030000...) */  1.17227388112847630E+00,  8.38518861402867437E-17,
/* i=     115 atan(40030000...)            3FF2C1A241D66DC3,         3C982B2D58B6A8E9, */

/* i=     116 atan(40040000...) */  1.19028994968253166E+00,  7.68333362984206881E-17,
/* i=     116 atan(40040000...)            3FF30B6D796A4DA8,         3C96254CB03BB199, */

/* i=     117 atan(40050000...) */  1.20681737028525249E+00,  4.17246763886143912E-17,
/* i=     117 atan(40050000...)            3FF34F1FBB19EB09,         3C880D79B4CF61D5, */

/* i=     118 atan(40060000...) */  1.22202532321098967E+00, -2.97916286489284927E-17,
/* i=     118 atan(40060000...)            3FF38D6A6CE13353,         BC812C77E8A80F5C, */

/* i=     119 atan(40070000...) */  1.23605948947808186E+00,  7.87975273945942128E-17,
/* i=     119 atan(40070000...)            3FF3C6E650B38047,         3C96B63B358E746D, */

/* i=     120 atan(40080000...) */  1.24904577239825443E+00, -2.19620379961231129E-18,
/* i=     120 atan(40080000...)            3FF3FC176B7A8560,         BC4441A3BD3F1084, */

/* i=     121 atan(40090000...) */  1.26109338225244039E+00,  3.24213962153496050E-17,
/* i=     121 atan(40090000...)            3FF42D70411F9EC1,         3C82B08DB7F10896, */

/* i=     122 atan(400A0000...) */  1.27229739520871732E+00,  2.24587501503450703E-17,
/* i=     122 atan(400A0000...)            3FF45B54837351A0,         3C79E4A72EEDACC4, */

/* i=     123 atan(400B0000...) */  1.28274087974427076E+00, -9.28318875426612948E-18,
/* i=     123 atan(400B0000...)            3FF4861B4CFBE710,         BC6567D3D25932D1, */

/* i=     124 atan(400C0000...) */  1.29249666778978534E+00, -6.83080476892666033E-17,
/* i=     124 atan(400C0000...)            3FF4AE10FC6589A5,         BC93B03E8A27F555, */

/* i=     125 atan(400D0000...) */  1.30162883400919616E+00, -1.23691849982462667E-17,
/* i=     125 atan(400D0000...)            3FF4D378C1999A0D,         BC6C857A639541C8, */

/* i=     126 atan(400E0000...) */  1.31019393504755555E+00,  8.74541373478027883E-17,
/* i=     126 atan(400E0000...)            3FF4F68DEA672617,         3C9934F9F2B0020E, */

/* i=     127 atan(400F0000...) */  1.31824205101683711E+00, -6.31939403114467626E-17,
/* i=     127 atan(400F0000...)            3FF51784FA1544BA,         BC9236E3C857C019, */

/* i=     128 atan(40100000...) */  1.32581766366803255E+00, -8.82442937395113632E-17,
/* i=     128 atan(40100000...)            3FF5368C951E9CFD,         BC996F47948A99F1, */

/* i=     129 atan(40110000...) */  1.33970565959899957E+00, -2.59901186030413438E-17,
/* i=     129 atan(40110000...)            3FF56F6F33A3E6A7,         BC7DF6EDD6F1EC3B, */

/* i=     130 atan(40120000...) */  1.35212738092095464E+00,  2.14767425075115096E-17,
/* i=     130 atan(40120000...)            3FF5A25052114E60,         3C78C2D0C89DE218, */

/* i=     131 atan(40130000...) */  1.36330010035969384E+00,  1.09324617152693622E-16,
/* i=     131 atan(40130000...)            3FF5D013C41ADABD,         3C9F82BBA194DD5D, */

/* i=     132 atan(40140000...) */  1.37340076694501589E+00, -3.30771035576951650E-17,
/* i=     132 atan(40140000...)            3FF5F97315254857,         BC831151A43B51CA, */

/* i=     133 atan(40150000...) */  1.38257482149012589E+00, -3.56149043864823010E-17,
/* i=     133 atan(40150000...)            3FF61F06C6A92B89,         BC8487D50BCEB1A5, */

/* i=     134 atan(40160000...) */  1.39094282700241845E+00, -9.84371213348884259E-17,
/* i=     134 atan(40160000...)            3FF6414D44094C7C,         BC9C5F60A65C7397, */

/* i=     135 atan(40170000...) */  1.39860551227195762E+00, -2.32406118259162798E-17,
/* i=     135 atan(40170000...)            3FF660B02C736A06,         BC7ACB6AFB332A0F, */

/* i=     136 atan(40180000...) */  1.40564764938026987E+00, -8.92263013823449239E-17,
/* i=     136 atan(40180000...)            3FF67D8863BC99BD,         BC99B7BD2E1E8C9C, */

/* i=     137 atan(40190000...) */  1.41214106460849531E+00, -9.57380711055722328E-17,
/* i=     137 atan(40190000...)            3FF698213A9D5053,         BC9B9839085189E3, */

/* i=     138 atan(401A0000...) */  1.41814699839963154E+00, -8.26388378251101363E-17,
/* i=     138 atan(401A0000...)            3FF6B0BAE830C070,         BC97D1AB82FFB70B, */

/* i=     139 atan(401B0000...) */  1.42371797140649403E+00,  8.72187092222396751E-17,
/* i=     139 atan(401B0000...)            3FF6C78C7EDEB195,         3C99239AD620FFE2, */

/* i=     140 atan(401C0000...) */  1.42889927219073276E+00, -6.45713474323875439E-17,
/* i=     140 atan(401C0000...)            3FF6DCC57BB565FD,         BC929C86447928E7, */

/* i=     141 atan(401D0000...) */  1.43373015248470903E+00, -4.39620446676763619E-17,
/* i=     141 atan(401D0000...)            3FF6F08F07435FEC,         BC8957A7170DF016, */

/* i=     142 atan(401E0000...) */  1.43824479449822262E+00, -2.49301991026456555E-17,
/* i=     142 atan(401E0000...)            3FF7030CF9403197,         BC7CBE1896221608, */

/* i=     143 atan(401F0000...) */  1.44247309910910193E+00, -1.10511943543031571E-16,
/* i=     143 atan(401F0000...)            3FF7145EAC2088A4,         BC9FDA5797B32A0B, */

/* i=     144 atan(40200000...) */  1.44644133224813509E+00,  9.21132397154505156E-17,
/* i=     144 atan(40200000...)            3FF7249FAA996A21,         3C9A8CC1E7480C68, */

/* i=     145 atan(40210000...) */  1.45368758222803240E+00, -6.81876925015134676E-17,
/* i=     145 atan(40210000...)            3FF7424DE90454D4,         BC93A75D182E1A5F, */

/* i=     146 atan(40220000...) */  1.46013910562100091E+00,  6.26097470783084416E-17,
/* i=     146 atan(40220000...)            3FF75CBAD2A40BD5,         3C920BC8AF35C4D5, */

/* i=     147 atan(40230000...) */  1.46591938806466282E+00, -9.71125555407483218E-17,
/* i=     147 atan(40230000...)            3FF77467E364F601,         BC9BFDA44F3537B8, */

/* i=     148 atan(40240000...) */  1.47112767430373470E+00, -1.08492227620614239E-16,
/* i=     148 atan(40240000...)            3FF789BD2C160054,         BC9F45503CCAD255, */

/* i=     149 atan(40250000...) */  1.47584462045214027E+00,  3.38755967276631476E-17,
/* i=     149 atan(40250000...)            3FF79D0F3FAD1C92,         3C838727DC4FB7D1, */

/* i=     150 atan(40260000...) */  1.48013643959415142E+00,  8.50262547607966975E-17,
/* i=     150 atan(40260000...)            3FF7AEA38C1ACBD1,         3C9881D48AE6DE92, */

/* i=     151 atan(40270000...) */  1.48405798811891154E+00, -3.44545106786359401E-17,
/* i=     151 atan(40270000...)            3FF7BEB396C5699A,         BC83DC969C7E2365, */

/* i=     152 atan(40280000...) */  1.48765509490645531E+00,  7.84437173946107664E-17,
/* i=     152 atan(40280000...)            3FF7CD6F6DC59DB4,         3C969C1FED612CFC, */

/* i=     153 atan(40290000...) */  1.49096634108265924E+00,  6.22143476002012210E-17,
/* i=     153 atan(40290000...)            3FF7DAFF85A63058,         3C91EE9BCCA84EB2, */

/* i=     154 atan(402A0000...) */  1.49402443552511865E+00, -7.47641750277645943E-17,
/* i=     154 atan(402A0000...)            3FF7E7862AA0157C,         BC958C9F564B028C, */

/* i=     155 atan(402B0000...) */  1.49685728913695626E+00,  1.69600762125511713E-17,
/* i=     155 atan(402B0000...)            3FF7F320A0F9F587,         3C738DBB20936502, */

/* i=     156 atan(402C0000...) */  1.49948886200960629E+00, -8.69233960451104982E-19,
/* i=     156 atan(402C0000...)            3FF7FDE80870C2A0,         BC3008D760C989AB, */

/* i=     157 atan(402D0000...) */  1.50193983749385196E+00,  6.06189958407581368E-17,
/* i=     157 atan(402D0000...)            3FF807F2112987C7,         3C9178E474EC8C66, */

/* i=     158 atan(402E0000...) */  1.50422816301907281E+00,  9.13778153422684716E-18,
/* i=     158 atan(402E0000...)            3FF811518CDE39A6,         3C6511FE80FBB230, */

/* i=     159 atan(402F0000...) */  1.50636948736934317E+00, -1.05533910133197090E-16,
/* i=     159 atan(402F0000...)            3FF81A16E43F190B,         BC9E6B0733383AD4, */

/* i=     160 atan(40300000...) */  1.50837751679893928E+00, -6.60752345087512057E-18,
/* i=     160 atan(40300000...)            3FF82250768AC529,         BC5E78C96D05AFCB, */

/* i=     161 atan(40310000...) */  1.51204050407917401E+00, -8.17827248696306499E-17,
/* i=     161 atan(40310000...)            3FF831516233F561,         BC97927FFEC5F9DC, */

/* i=     162 atan(40320000...) */  1.51529782154917969E+00,  9.27265838320600392E-17,
/* i=     162 atan(40320000...)            3FF83EA8EDB40F72,         3C9ABA03A56FDC09, */

/* i=     163 atan(40330000...) */  1.51821326518395483E+00,  7.14053211560016173E-17,
/* i=     163 atan(40330000...)            3FF84A99FE25186B,         3C9494C8619D0BBC, */

/* i=     164 atan(40340000...) */  1.52083793107295384E+00,  1.64275464789776791E-17,
/* i=     164 atan(40340000...)            3FF8555A2787981F,         3C72F08E51763131, */

/* i=     165 atan(40350000...) */  1.52321322351791322E+00,  6.06514977555146142E-18,
/* i=     165 atan(40350000...)            3FF85F14D43D81BE,         3C5BF8770A76AFAF, */

/* i=     166 atan(40360000...) */  1.52537304737331958E+00,  2.48298338570039438E-17,
/* i=     166 atan(40360000...)            3FF867ED918AB138,         3C7CA07933F18E43, */

/* i=     167 atan(40370000...) */  1.52734543140336587E+00, -9.47004210780093541E-17,
/* i=     167 atan(40370000...)            3FF87001C35928D4,         BC9B4BA860ADA728, */

/* i=     168 atan(40380000...) */  1.52915374769630819E+00,  9.96025861033048094E-18,
/* i=     168 atan(40380000...)            3FF87769EB8E956B,         3C66F77FB9BAEBA6, */

/* i=     169 atan(40390000...) */  1.53081763967160667E+00, -8.91334763349872231E-17,
/* i=     169 atan(40390000...)            3FF87E3AA32878AE,         BC99B0E3C3BBC6CF, */

/* i=     170 atan(403A0000...) */  1.53235373677370856E+00,  7.35876234111923764E-17,
/* i=     170 atan(403A0000...)            3FF884855A158B25,         3C9535CEE7C891BB, */

/* i=     171 atan(403B0000...) */  1.53377621092096650E+00,  9.37735480657284383E-17,
/* i=     171 atan(403B0000...)            3FF88A58EC949D14,         3C9B07443DD06AD8, */

/* i=     172 atan(403C0000...) */  1.53509721411557254E+00,  1.10616555458501787E-16,
/* i=     172 atan(403C0000...)            3FF88FC218ACE9DB,         3C9FE20FA7E1E941, */

/* i=     173 atan(403D0000...) */  1.53632722579538861E+00, -1.73373217093894906E-18,
/* i=     173 atan(403D0000...)            3FF894CBDB6BEDFC,         BC3FFB5195F35C00, */

/* i=     174 atan(403E0000...) */  1.53747533091664934E+00,  8.11685860076124202E-17,
/* i=     174 atan(403E0000...)            3FF8997FBB8B19C0,         3C97652F3D7700A3, */

/* i=     175 atan(403F0000...) */  1.53854944435964280E+00, -1.04663067143013889E-16,
/* i=     175 atan(403F0000...)            3FF89DE605ACDBB3,         BC9E2AC570EAC042, */

/* i=     176 atan(40400000...) */  1.53955649336462841E+00, -6.59487545533283128E-17,
/* i=     176 atan(40400000...)            3FF8A205FD558740,         BC930228C09A91B4, */

/* i=     177 atan(40410000...) */  1.54139303859089161E+00, -1.02574621979876286E-16,
/* i=     177 atan(40410000...)            3FF8A98BBF307AA8,         BC9D90ABD3CB737A, */

/* i=     178 atan(40420000...) */  1.54302569020147562E+00, -3.65410017872781400E-17,
/* i=     178 atan(40420000...)            3FF8B03BB4C4D9C4,         BC851080044823F8, */

/* i=     179 atan(40430000...) */  1.54448660954197448E+00, -4.84886962896552125E-17,
/* i=     179 atan(40430000...)            3FF8B63797517BB5,         BC8BF3AB273B6CE0, */

/* i=     180 atan(40440000...) */  1.54580153317597646E+00, -1.28017749694693433E-18,
/* i=     180 atan(40440000...)            3FF8BB9A63718F45,         BC379D77A1373742, */

/* i=     181 atan(40450000...) */  1.54699130060982659E+00,  8.40387156476469915E-17,
/* i=     181 atan(40450000...)            3FF8C079F3350D26,         3C9838F674C6574D, */

/* i=     182 atan(40460000...) */  1.54807296595325550E+00,  5.63378094641568198E-17,
/* i=     182 atan(40460000...)            3FF8C4E82889748C,         3C903CFF21ED4F81, */

/* i=     183 atan(40470000...) */  1.54906061995310385E+00,  1.07720671947039880E-16,
/* i=     183 atan(40470000...)            3FF8C8F3C9E38564,         3C9F0C61F67DF753, */

/* i=     184 atan(40480000...) */  1.54996600675867957E+00, -3.65867202631610758E-17,
/* i=     184 atan(40480000...)            3FF8CCA927CF0B3D,         BC85173F363FCD3B, */

/* i=     185 atan(40490000...) */  1.55079899282174605E+00,  3.88158322748794045E-17,
/* i=     185 atan(40490000...)            3FF8D0129ACD6D1C,         3C866034AEC68494, */

/* i=     186 atan(404A0000...) */  1.55156792769518947E+00, -6.25939220821526366E-17,
/* i=     186 atan(404A0000...)            3FF8D338E42F92C4,         BC920A9DC23967F4, */

/* i=     187 atan(404B0000...) */  1.55227992472688747E+00,  1.03058038268892371E-16,
/* i=     187 atan(404B0000...)            3FF8D623796F0778,         3C9DB4574D874450, */

/* i=     188 atan(404C0000...) */  1.55294108165534417E+00, -6.37987893547135838E-17,
/* i=     188 atan(404C0000...)            3FF8D8D8BF65316F,         BC9263850ED82243, */

/* i=     189 atan(404D0000...) */  1.55355665560036682E+00,  1.03636378617620221E-16,
/* i=     189 atan(404D0000...)            3FF8DB5E3944965E,         3C9DDF03D7D94A94, */

/* i=     190 atan(404E0000...) */  1.55413120308095598E+00, -1.10032784474653953E-16,
/* i=     190 atan(404E0000...)            3FF8DDB8AE2ED03E,         BC9FB6FC889F3B9F, */

/* i=     191 atan(404F0000...) */  1.55466869295126031E+00,  7.12642375326129392E-17,
/* i=     191 atan(404F0000...)            3FF8DFEC478573A0,         3C948A5F6312C3FA, */

/* i=     192 atan(40500000...) */  1.55517259817441977E+00,  1.48861661196504977E-17,
/* i=     192 atan(40500000...)            3FF8E1FCA98CB633,         3C71299EE93BE016, */

};
