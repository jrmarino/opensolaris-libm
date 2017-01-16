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


#pragma weak casinf = __casinf

#include "libm.h"
#include "complex_wrapper.h"

fcomplex
casinf(fcomplex z) {
	dcomplex dz, dans;
	fcomplex ans;

	D_RE(dz) = (double) (F_RE(z));
	D_IM(dz) = (double) (F_IM(z));
	dans = casin(dz);
	F_RE(ans) = (float) (D_RE(dans));
	F_IM(ans) = (float) (D_IM(dans));
	return (ans);
}
