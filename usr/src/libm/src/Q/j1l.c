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
 * floating point Bessel's function of the first and second kinds
 * of order zero: j1(x),y1(x);
 *
 * Special cases:
 *	y0(0)=y1(0)=yn(n,0) = -inf with division by zero signal;
 *	y0(-ve)=y1(-ve)=yn(n,-ve) are NaN with invalid signal.
 */

#pragma weak j1l = __j1l
#pragma weak y1l = __y1l

#include "libm.h"

#define	GENERIC long double
static const GENERIC
zero    = 0.0L,
small	= 1.0e-9L,
tiny 	= 1.0e-38L,
one	= 1.0L,
five   	= 5.0L,
invsqrtpi= 5.641895835477562869480794515607725858441e-0001L,
tpi	= 0.636619772367581343075535053490057448L;

static GENERIC pone(GENERIC);
static GENERIC qone(GENERIC);

static const GENERIC r0[7] = {
  -6.249999999999999999999999999999999627320e-0002L,
   1.940606727194041716205384618494641565464e-0003L,
  -3.005630423155733701856481469986459043883e-0005L,
   2.345586219403918667468341047369572169358e-0007L,
  -9.976809285885253587529010109133336669724e-0010L,
   2.218743258363623946078958783775107473381e-0012L,
  -2.071079656218700604767650924103578046280e-0015L,
};
static const GENERIC s0[7] = {
   1.0e0L,
   1.061695903156199920738051277075003059555e-0002L,
   5.521860513111180371566951179398862692060e-0005L,
   1.824214367413754193524107877084979441407e-0007L,
   4.098957778439576834818838198039029353925e-0010L,
   6.047735079699666389853240090925264056197e-0013L,
   4.679044728878836197247923279512047035041e-0016L,
};

GENERIC
j1l(x) GENERIC x;{
	GENERIC z, d, s,c,ss,cc,r;
	int i, sgn;

	if(!finitel(x)) return one/x;
	sgn = signbitl(x);
	x = fabsl(x);
	if(x > 1.28L){
		s = sinl(x);
		c = cosl(x);
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
		if(x>1.0e2450L) {	/* x+x may overflow */
			ss = -s-c;
			cc =  s-c;
		} else if(signbitl(s)!=signbitl(c)) {
			cc = s - c;
			ss = cosl(x+x)/cc;
		} else {
			ss = -s-c;
			cc = cosl(x+x)/ss;
		}
	/*
	 * j1(x) = 1/sqrt(pi*x) * (P(1,x)*cc - Q(1,x)*ss)
	 * y1(x) = 1/sqrt(pi*x) * (P(1,x)*ss + Q(1,x)*cc)
	 */
                if(x>1.0e120L) return (invsqrtpi*cc)/sqrtl(x);
                d =  invsqrtpi*(pone(x)*cc-qone(x)*ss)/sqrtl(x);
		if(sgn==0) return d; else return -d;
	}
	if(x<=small) {
            if(x<=tiny) d = 0.5L*x;
            else d =  x*(0.5L-x*x*0.125L);
	    if(sgn==0) return d; else return -d;
        }
	z = x*x;
	    r = r0[6];
	    s = s0[6];
	    for(i=5;i>=0;i--) {
		r = r*z + r0[i];
		s = s*z + s0[i];
	    }
	d = x*0.5L+x*(z*(r/s));
	if(sgn==0) return d; else return -d;
}

static const GENERIC u0[7] = {
  -1.960570906462389484060557273467558703503e-0001L,
   5.166389353148318460304315890665450006495e-0002L,
  -2.229699464105910913337190798743451115604e-0003L,
   3.625437034548863342715657067759078267158e-0005L,
  -2.689902826993117212255524537353883987171e-0007L,
   9.304570592456930912969387719010256018466e-0010L,
  -1.234878126794286643318321347997500346131e-0012L,
};
static const GENERIC v0[8] = {
   1.0e0L,
   1.369394302535807332517110204820556695644e-0002L,
   9.508438148097659501433367062605935379588e-0005L,
   4.399007309420092056052714797296467565655e-0007L,
   1.488083087443756398305819693177715000787e-0009L,
   3.751609832625793536245746965768587624922e-0012L,
   6.680926434086257291872903276124244131448e-0015L,
   6.676602383908906988160099057991121446058e-0018L,
};

GENERIC
y1l(x) GENERIC x;{
	GENERIC z, s,c,ss,cc,u,v;
	int i;

	if(isnanl(x)) return x+x;
	if(x <= zero){
		if(x==zero)
		    return -one/zero;
		else
		    return zero/zero;
	}
	if(x > 1.28L){
		if(!finitel(x)) return zero;
		s = sinl(x);
		c = cosl(x);
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
		if(x>1.0e2450L) {	/* x+x may overflow */
			ss = -s-c;
			cc =  s-c;
		} else if(signbitl(s)!=signbitl(c)) {
			cc = s - c;
			ss = cosl(x+x)/cc;
		} else {
			ss = -s-c;
			cc = cosl(x+x)/ss;
		}
	/*
	 * j1(x) = 1/sqrt(pi*x) * (P(1,x)*cc - Q(1,x)*ss)
	 * y1(x) = 1/sqrt(pi*x) * (P(1,x)*ss + Q(1,x)*cc)
	 */
		if(x>1.0e91L) return (invsqrtpi*ss)/sqrtl(x);
                return invsqrtpi*(pone(x)*ss+qone(x)*cc)/sqrtl(x);
	}
        if(x<=tiny) {
            return(-tpi/x);
        }
	z = x*x;
	    u = u0[6]; v = v0[6]+z*v0[7];
	    for(i=5;i>=0;i--){
		u = u*z + u0[i];
		v = v*z + v0[i];
	    }
	return(x*(u/v) + tpi*(j1l(x)*logl(x)-one/x));
}

static const GENERIC pr0[12] = {
   1.000000000000000000000000000000000000267e+0000L,
   1.060717875045891455602180843276758003035e+0003L,
   4.344347542892127024446687712181105852335e+0005L,
   8.915680220724007016377924252717410457094e+0007L,
   9.969502259938406062809873257569171272819e+0009L,
   6.200290193138613035646510338707386316595e+0011L,
   2.105978548788015119851815854422247330118e+0013L,
   3.696635772784601239371730810311998368948e+0014L,
   3.015913097920694682057958412534134515156e+0015L,
   9.370298471339353098123277427328592725921e+0015L,
   7.190349005196335967340799265074029443057e+0015L,
   2.736097786240689996880391074927552517982e+0014L,
};
static const GENERIC ps0[11] = {
   1.0e0L,
   1.060600687545891455602180843276758095107e+0003L,
   4.343106093416975589147153906505338900961e+0005L,
   8.910605869002176566582072242244353399059e+0007L,
   9.959122058635087888690713917622056540190e+0009L,
   6.188744967234948231792482949171041843894e+0011L,
   2.098863976953783506401759873801990304907e+0013L,
   3.672870357018063196746729751479938908450e+0014L,
   2.975538419246824921049011529574385888420e+0015L,
   9.063657659995043205018686029284479837091e+0015L,
   6.401953344314747916729366441508892711691e+0015L,
};
static const GENERIC pr1[12] = {
   1.000000000000000000000023667524130660984e+0000L,
   6.746154419979618754354803488126452971204e+0002L,
   1.811210781083390154857018330296145970502e+0005L,
   2.533098390379924268038005329095287842244e+0007L,
   2.029683619805342145252338570875424600729e+0009L,
   9.660859662192711465301069401598929980319e+0010L,
   2.743396238644831519934098967716621316316e+0012L,
   4.553097354140854377931023170263455246288e+0013L,
   4.210245069852219757476169864974870720374e+0014L,
   1.987334056229596485076645967176169801727e+0015L,
   4.067120052787096893838970455751338930462e+0015L,
   2.486539606380406398310845264910691398133e+0015L,
};
static const GENERIC ps1[14] = {
   1.0e0L,
   6.744982544979618754355808680196859521782e+0002L,
   1.810421795396966762032155290441364740350e+0005L,
   2.530986460644310651529583759699988435573e+0007L,
   2.026743276048023121360249288818290224145e+0009L,
   9.637461924407405935245269407052641341836e+0010L,
   2.732378628423766417402292797028314160831e+0012L,
   4.522345274960527124354844364012184278488e+0013L,
   4.160650668341743132685335758415469856545e+0014L,
   1.943730242988858208243492424892435901211e+0015L,
   3.880228532692127989901131618598067450001e+0015L,
   2.178020816161154615841000173683302999728e+0015L,
  -8.994062666842225551554346698171600634173e+0013L,
   1.368520368508851253495764806934619574990e+0013L,
};
static const GENERIC pr2[12] = {
   1.000000000000000006938651621840396237282e+0000L,
   3.658416291850404981407101077037948144698e+0002L,
   5.267073772170356547709794670602812447537e+0004L,
   3.912012101226837463014925210735894620442e+0006L,
   1.651295648974103957193874928714180765625e+0008L,
   4.114901144480797609972484998142146783499e+0009L,
   6.092524309766036681542980572526335147672e+0010L,
   5.263913178071282616719249969074134570577e+0011L,
   2.538408581124324223367341020538081330994e+0012L,
   6.288607929360291027895126983015365677648e+0012L,
   6.848330048211148419047055075386525945280e+0012L,
   2.290309646838867941423178163991423244690e+0012L,
};
static const GENERIC ps2[14] = {
   1.0e0L,
   3.657244416850405086459410165762319861856e+0002L,
   5.262802358425023243992387075861237306312e+0004L,
   3.905896813959919648136295861661483848364e+0006L,
   1.646791907791461220742694842108202772763e+0008L,
   4.096132803064256022224954120208201437344e+0009L,
   6.046665195915950447544429445730680236759e+0010L,
   5.198061739781991313414052212328653295168e+0011L,
   2.484233851814333966401527626421254279796e+0012L,
   6.047868806925315879339651539434315255940e+0012L,
   6.333103831254091652501642567294101813354e+0012L,
   1.875143098754284994467609936924685024968e+0012L,
  -5.238330920563392692965412762508813601534e+0010L,
   4.656888609439364725427789198383779259957e+0009L,
};
static const GENERIC pr3[13] = {
   1.000000000000009336887318068056137842897e+0000L,
   2.242719942728459588488051572002835729183e+0002L,
   1.955450611382026550266257737331095691092e+0004L,
   8.707143293993619899395400562409175590739e+0005L,
   2.186267894487004565948324289010954505316e+0007L,
   3.224328510541957792360691585667502864688e+0008L,
   2.821057355151380597331792896882741364897e+0009L,
   1.445371387295422404365584793796028979840e+0010L,
   4.181743160669891357783011002656658107864e+0010L,
   6.387371088767993119325536137794535513922e+0010L,
   4.575619999412716078064070587767416436396e+0010L,
   1.228415651211639160620284441690503550842e+0010L,
   7.242170349875563053436050532153112882072e+0008L,
};
static const GENERIC ps3[13] = {
   1.0e0L,
   2.241548067728529551049804610486061401070e+0002L,
   1.952838216795552145132137932931237181307e+0004L,
   8.684574926493185744628127341069974575526e+0005L,
   2.176357771067037962940853412819852189164e+0007L,
   3.199958682356132977319258783167122100567e+0008L,
   2.786218931525334687844675219914201872570e+0009L,
   1.416283776951741549631417572317916039767e+0010L,
   4.042962659271567948735676834609348842922e+0010L,
   6.028168462646694510083847222968444402161e+0010L,
   4.118410226794641413833887606580085281111e+0010L,
   9.918735736297038430744161253338202230263e+0009L,
   4.092967198238098023219124487437130332038e+0008L,
};
static const GENERIC pr4[13] = {
   1.000000000001509220978157399042059553390e+0000L,
   1.437551868378147851133499996323782607787e+0002L,
   7.911335537418177296041518061404505428004e+0003L,
   2.193710939115317214716518908935756104804e+0005L,
   3.390662495136730962513489796538274984382e+0006L,
   3.048655347929348891006070609293884274789e+0007L,
   1.613781633489496606354045161527450975195e+0008L,
   4.975089835037230277110156150038482159988e+0008L,
   8.636047087015115403880904418339566323264e+0008L,
   7.918202912328366140110671223076949101509e+0008L,
   3.423294665798984733439650311722794853294e+0008L,
   5.621904953441963961040503934782662613621e+0007L,
   2.086303543310240260758670404509484499793e+0006L,
};
static const GENERIC ps4[13] = {
   1.0e0L,
   1.436379993384532371670493319591847362304e+0002L,
   7.894647154785430678061053848847436659499e+0003L,
   2.184659753392097529008981741550878586174e+0005L,
   3.366109083305465176803513738147049499361e+0006L,
   3.011911545968996817697665866587226343186e+0007L,
   1.582262913779689851316760148459414895301e+0008L,
   4.819268809494937919217938589530138201770e+0008L,
   8.201355762990450679702837123432527154830e+0008L,
   7.268232093982510937417446421282341425212e+0008L,
   2.950911909015572933262131323934036480462e+0008L,
   4.242839924305934423010858966540621219396e+0007L,
   1.064387620445090779182117666330405186866e+0006L,
};
static const GENERIC pr5[13] = {
   1.000000000102434805241171427253847353861e+0000L,
   9.129332257083629259060502249025963234821e+0001L,
   3.132238483586953037576119377504557191413e+0003L,
   5.329782528269307971278943122454171107861e+0004L,
   4.988460157184117790692873002103052944145e+0005L,
   2.686602071615786816147010334256047469378e+0006L,
   8.445418526028961197703799808701268301831e+0006L,
   1.536575358646141157475725889907900827390e+0007L,
   1.568405818236523821796862770586544811945e+0007L,
   8.450876239888770102387618667362302173547e+0006L,
   2.154414900139567328424026827163203446077e+0006L,
   2.105656926565043898888460254808062352205e+0005L,
   4.739165011023396507022134303736862812975e+0003L,
};
static const GENERIC ps5[13] = {
   1.0e0L,
   9.117613509595327476509152673394703847793e+0001L,
   3.121697972484015639301279229281770795147e+0003L,
   5.294447222735893568040911873834576440255e+0004L,
   4.930368882192772335798256684110887882807e+0005L,
   2.634854685641165298302167435798357437768e+0006L,
   8.185462775400326393555896157031818280918e+0006L,
   1.462417423080215192609668642663030667086e+0007L,
   1.450624993985851675982860844153954896015e+0007L,
   7.460467647561995283219086567162006113864e+0006L,
   1.754210981405612478869227142579056338965e+0006L,
   1.463286721155271971526264914524746699596e+0005L,
   2.155894725796702015341211116579827039459e+0003L,
};
static const GENERIC pr6[13] = {
   1.000000003564855546741735920315743157129e+0000L,
   5.734003934862540458119423509909510288366e+0001L,
   1.209572491935850486086559692291796887976e+0003L,
   1.243398391422281247933674779163660286838e+0004L,
   6.930996755181437937258220998601708278787e+0004L,
   2.198067659532757598646722249966767620099e+0005L,
   4.033659432712058633933179115820576858455e+0005L,
   4.257759657219008027016047206574574358678e+0005L,
   2.511917395876004349480721277445763916389e+0005L,
   7.813756153070623654178731651381881953552e+0004L,
   1.152069173381127881385588092905864352891e+0004L,
   6.548580782804088553777816037551523398082e+0002L,
   8.668725370116906132327542766127938496880e+0000L,
};
static const GENERIC ps6[13] = {
   1.0e0L,
   5.722285236357114566499221525736286205184e+0001L,
   1.203010842878317935444582950620339570506e+0003L,
   1.230058335378583550155825502172435371208e+0004L,
   6.800998550607861288865300438648089894412e+0004L,
   2.130767829599304262987769347536850885921e+0005L,
   3.840483466643916681759936972992155310026e+0005L,
   3.947432373459225542861819148108081160393e+0005L,
   2.237816239393081111481588434457838526738e+0005L,
   6.545820495124419723398946273790921540774e+0004L,
   8.729563630320892741500726213278834737196e+0003L,
   4.130762660291894753450174794196998813709e+0002L,
   3.480368898672684645130335786015075595598e+0000L,
};
static const GENERIC sixteen = 16.0L;
static const GENERIC eight   = 8.0L;
static const GENERIC huge    = 1.0e30L;

static GENERIC pone(x)
GENERIC x;
{
	GENERIC s,r,t,z;
	int i;
	if(x>huge) return one;
	t = one/x; z = t*t;
	if(x>sixteen) {
	    r = z*pr0[11]+pr0[10]; s = ps0[10];
	    for(i=9;i>=0;i--) {
		r = z*r + pr0[i];
		s = z*s + ps0[i];
	    }
	} else if(x>eight) {
	    r = pr1[11]; s = ps1[11]+z*(ps1[12]+z*ps1[13]);
	    for(i=10;i>=0;i--) {
		r = z*r + pr1[i];
		s = z*s + ps1[i];
	    }
	} else if(x>five) {
	    r = pr2[11]; s = ps2[11]+z*(ps2[12]+z*ps2[13]);
	    for(i=10;i>=0;i--) {
		r = z*r + pr2[i];
		s = z*s + ps2[i];
	    }
        } else if( x>3.5L) {
            r = pr3[12]; s = ps3[12];
            for(i=11;i>=0;i--) {
                r = z*r + pr3[i];
                s = z*s + ps3[i];
            }
        } else if( x>2.5L) {
            r = pr4[12]; s = ps4[12];
            for(i=11;i>=0;i--) {
                r = z*r + pr4[i];
                s = z*s + ps4[i];
            }
        } else if( x> (1.0L/0.5625L)){
            r = pr5[12]; s = ps5[12];
            for(i=11;i>=0;i--) {
                r = z*r + pr5[i];
                s = z*s + ps5[i];
            }
        } else {        /* assume x > 1.28 */
            r = pr6[12]; s = ps6[12];
            for(i=11;i>=0;i--) {
                r = z*r + pr6[i];
                s = z*s + ps6[i];
            }
        }
	return r/s;
}


static const GENERIC qr0[12] = {
   3.749999999999999999999999999999999971033e-0001L,
   4.256726035237050601607682277433094262226e+0002L,
   1.875976490812878489192409978945401066066e+0005L,
   4.170314268048041914273603680317745592790e+0007L,
   5.092750132543855817293451118974555746551e+0009L,
   3.494749676278488654103505795794139483404e+0011L,
   1.327062148257437316997667817096694173709e+0013L,
   2.648993138273427226907503742066551150490e+0014L,
   2.511695665909547412222430494473998127684e+0015L,
   9.274694506662289043224310499164702306096e+0015L,
   8.150904170663663829331320302911792892002e+0015L,
  -5.001918733707662355772037829620388765122e+0014L,
};
static const GENERIC qs0[11] = {
   1.0e0L,
   1.135400380229880160428715273982155760093e+0003L,
   5.005701183877126164326765545516590744360e+0005L,
   1.113444200113712167984337603933040102987e+0008L,
   1.361074819925223062778717565699039471124e+0010L,
   9.355750985802849484438933905325982809653e+0011L,
   3.563462786008988825003965543857998084828e+0013L,
   7.155145113900094163648726863803802910454e+0014L,
   6.871266835834472758055559013851843654113e+0015L,
   2.622030899226736712644974988157345234092e+0016L,
   2.602912729172876330650077021706139707746e+0016L,
};
static const GENERIC qr1[12] = {
   3.749999999999999999997762458207284405806e-0001L,
   2.697883998881706839929255517498189980485e+0002L,
   7.755195925781028489386938870473834411019e+0004L,
   1.166777762104017777198211072895528968355e+0007L,
   1.011504772984321168320010084520261069362e+0009L,
   5.246007703574156853577754571720205550010e+0010L,
   1.637692549885592683166116551691266537647e+0012L,
   3.022303623698185669912990310925039382495e+0013L,
   3.154769927290655684846107030265909987946e+0014L,
   1.715819913441554770089730934808123360921e+0015L,
   4.165044355759732622273534445131736188510e+0015L,
   3.151381420874174705643100381708086287596e+0015L,
};
static const GENERIC qs1[14] = {
   1.0e0L,
   7.197091705351218239785633172408276982828e+0002L,
   2.070012799599548685544883041297609861055e+0005L,
   3.117014815317656221871840152778458754516e+0007L,
   2.705719678902554974863325877025902971727e+0009L,
   1.406113614727345726925060648750867264098e+0011L,
   4.403777536067131320363005978631674817359e+0012L,
   8.170725690209322283061499386703167242894e+0013L,
   8.609458844975495289227794126964431210566e+0014L,
   4.766766367015473481257280600694952920204e+0015L,
   1.202286587943342194863557940888115641650e+0016L,
   1.012474328306200909525063936061756024120e+0016L,
   6.183552022678917858273222879615824070703e+0014L,
  -9.756731548558226997573737400988225722740e+0013L,
};
static const GENERIC qr2[12] = {
   3.749999999999999481245647262226994293189e-0001L,
   1.471366807289771354491181140167359026735e+0002L,
   2.279432486768448220142080962843526951250e+0004L,
   1.828943048523771225163804043356958285893e+0006L,
   8.379828388647823135832220596417725010837e+0007L,
   2.279814029335044024585393671278378022053e+0009L,
   3.711653952257118120832817785271466441420e+0010L,
   3.557650914518554549916730572553105048068e+0011L,
   1.924583483146095896259774329498934160650e+0012L,
   5.424386256063736390759567088291887140278e+0012L,
   6.839325621241776786206509704671746841737e+0012L,
   2.702169563144001166291686452305436313971e+0012L,
};
static const GENERIC qs2[14] = {
   1.0e0L,
   3.926379194439388135703211933895203191089e+0002L,
   6.089148804106598297488336063007609312276e+0004L,
   4.893546162973278583711376356041614150645e+0006L,
   2.247571119114497845046388801813832219404e+0008L,
   6.137635663350177751290469334200757872645e+0009L,
   1.005115019784102856424493519524998953678e+0011L,
   9.725664462014503832860151384604677240620e+0011L,
   5.345525100485511116148634192844434636072e+0012L,
   1.549944007398946691720862738173956994779e+0013L,
   2.067148441178952625710302124163264760362e+0013L,
   9.401565402641963611295119487242595462301e+0012L,
   3.548217088622398274748837287769709374385e+0011L,
  -2.934470341719047120076509938432417352365e+0010L,
};
static const GENERIC qr3[13] = {
   3.749999999999412724084579833297451472091e-0001L,
   9.058478580291706212422978492938435582527e+0001L,
   8.524056033161038750461083666711724381171e+0003L,
   4.105967158629109427753434569223631014730e+0005L,
   1.118326603378531348259783091972623333657e+0007L,
   1.794636683403578918528064904714132329343e+0008L,
   1.714314157463635959556133236004368896724e+0009L,
   9.622092032236084846572067257267661456030e+0009L,
   3.057759524485859159957762858780768355020e+0010L,
   5.129306780754798531609621454415938890020e+0010L,
   3.999122002794961070680636194346316041352e+0010L,
   1.122298454643493485989721564358100345388e+0010L,
   5.603981987645989709668830968522362582221e+0008L,
};
static const GENERIC qs3[13] = {
   1.0e0L,
   2.418328663076578169836155170053634419922e+0002L,
   2.279620205900121042587523541281272875520e+0004L,
   1.100984222585729521470129014992217092794e+0006L,
   3.010743223679247091004262516286654516282e+0007L,
   4.860925542827367817289619265215599433996e+0008L,
   4.686668111035348691982715864307839581243e+0009L,
   2.668701788405102017427214705946730894074e+0010L,
   8.677395746106802640390580944836650584903e+0010L,
   1.511936455574951790658498795945106643036e+0011L,
   1.260845604432623478002018696873608353093e+0011L,
   4.052692278419853853911440231600864589805e+0010L,
   2.965516519212226064983267822243329694729e+0009L,
};
static const GENERIC qr4[13] = {
   3.749999999919234164154669754440123072618e-0001L,
   5.844218580776819864791168253485055101858e+0001L,
   3.489273514092912982675669411371435670220e+0003L,
   1.050523637774575684509663430018995479594e+0005L,
   1.764549172059701565500717319792780115289e+0006L,
   1.725532438844133795028063102681497371154e+0007L,
   9.938114847359778539965140247590176334874e+0007L,
   3.331710808184595545396883770200772842314e+0008L,
   6.271970557641881511609560444872797282698e+0008L,
   6.188529798677357075020774923903737913285e+0008L,
   2.821905302742849974509982167877885011629e+0008L,
   4.615467358646911976773290256984329814896e+0007L,
   1.348140608731546467396685802693380693275e+0006L,
};
static const GENERIC qs4[13] = {
   1.0e0L,
   1.561192663112345185261418296389902133372e+0002L,
   9.346678031144098270547225423124213083072e+0003L,
   2.825851246482293547838023847601704751590e+0005L,
   4.776572711622156091710902891124911556293e+0006L,
   4.715106953717135402977938048006267859302e+0007L,
   2.753962350894311316439652227611209035193e+0008L,
   9.428501434615463207768964787500411575223e+0008L,
   1.832650858775206787088236896454141572617e+0009L,
   1.901697378939743226948920874296595242257e+0009L,
   9.433322226854293780627188599226380812725e+0008L,
   1.808520540608671608680284520798858587370e+0008L,
   7.983342331736662753157217446919462398008e+0006L,
};
static const GENERIC qr5[13] = {
      3.749999995331364437028988850515190446719e-0001L,
      3.739356381766559882677514593041627547911e+0001L,
      1.399562500629413529355265462912819802551e+0003L,
      2.594154053098947925345332218062210111753e+0004L,
      2.640149879297408640394163979394594318371e+0005L,
      1.542471854873199142031889093591449397995e+0006L,
      5.242272868972053374067572098992335425895e+0006L,
      1.025834487769410221329633071426044839935e+0007L,
      1.116553924239448940142230579060124209622e+0007L,
      6.318076065595910176374916303525884653514e+0006L,
      1.641218086168640408527639735915512881785e+0006L,
      1.522369793529178644168813882912134706444e+0005L,
      2.526530541062297200914180060208669584055e+0003L,
};
static const GENERIC qs5[13] = {
      1.0e0L,
      9.998960735935075380397545659016287506660e+0001L,
      3.758767417842043742686475060540416737562e+0003L,
      7.013652806952306520121959742519780781653e+0004L,
      7.208949808818615099246529616211730446850e+0005L,
      4.272753927109614455417836186072202009252e+0006L,
      1.482524411356470699336129814111025434703e+0007L,
      2.988750366665678233425279237627700803473e+0007L,
      3.396957890261080492694709150553619185065e+0007L,
      2.050652487738593004111578091156304540386e+0007L,
      5.900504120811732547616511555946279451316e+0006L,
      6.563391409260160897024498082273183468347e+0005L,
      1.692629845012790205348966731477187041419e+0004L,
};
static const GENERIC qr6[13] = {
    3.749999861516664133157566870858975421296e-0001L,
    2.367863756747764863120797431599473468918e+0001L,
    5.476715802114976248882067325630793143777e+0002L,
    6.143190357869842894025012945444096170251e+0003L,
    3.716250534677997850513733595140463851730e+0004L,
    1.270883463823876752138326905022875657430e+0005L,
    2.495301449636814481646371665429083801388e+0005L,
    2.789578988212952248340486296254398601942e+0005L,
    1.718247946911109055931819087137397324634e+0005L,
    5.458973214011665714330326732204106364229e+0004L,
    7.912102686687948786048943339759596652813e+0003L,
    4.077961006160866935722030715149087938091e+0002L,
    3.765206972770245085551057237882528510428e+0000L,
};
static const GENERIC qs6[13] = {
    1.0e0L,
    6.341646532940517305641893852673926809601e+0001L,
    1.477058277414040790932597537920671025359e+0003L,
    1.674406564031044491436044253393536487604e+0004L,
    1.028516501369755949895050806908994650768e+0005L,
    3.593620042532885295087463507733285434207e+0005L,
    7.267924991381020915185873399453724799625e+0005L,
    8.462277510768818399961191426205006083088e+0005L,
    5.514399892230892163373611895645500250514e+0005L,
    1.898084241009259353540620272932188102299e+0005L,
    3.102941242117739015721984123081026253068e+0004L,
    1.958971184431466907681440650181421086143e+0003L,
    2.878853357310495087181721613889455121867e+0001L,
};
static GENERIC qone(x)
GENERIC x;
{
	GENERIC s,r,t,z;
	int i;
	if(x>huge) return 0.375L/x;
	t = one/x; z = t*t;
	if(x>sixteen) {
	    r = z*qr0[11]+qr0[10]; s = qs0[10];
	    for(i=9;i>=0;i--) {
		r = z*r + qr0[i];
		s = z*s + qs0[i];
	    }
	} else if(x>eight) {
	    r = qr1[11]; s = qs1[11]+z*(qs1[12]+z*qs1[13]);
	    for(i=10;i>=0;i--) {
		r = z*r + qr1[i];
		s = z*s + qs1[i];
	    }
	} else if (x>five) {	/* x > 5.0 */
	    r = qr2[11]; s = qs2[11]+z*(qs2[12]+z*qs2[13]);
	    for(i=10;i>=0;i--) {
		r = z*r + qr2[i];
		s = z*s + qs2[i];
	    }
        } else if(x>3.5L) {
            r = qr3[12]; s = qs3[12];
            for(i=11;i>=0;i--) {
                r = z*r + qr3[i];
                s = z*s + qs3[i];
            }
        } else if(x>2.5L) {
            r = qr4[12]; s = qs4[12];
            for(i=11;i>=0;i--) {
                r = z*r + qr4[i];
                s = z*s + qs4[i];
            }
        } else if(x> (1.0L/0.5625L)) {
            r = qr5[12]; s = qs5[12];
            for(i=11;i>=0;i--) {
                r = z*r + qr5[i];
                s = z*s + qs5[i];
            }
        } else {        /* assume x > 1.28 */
            r = qr6[12]; s = qs6[12];
            for(i=11;i>=0;i--) {
                r = z*r + qr6[i];
                s = z*s + qs6[i];
            }
        }
	return t*(r/s);
}
