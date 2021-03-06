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

extern void __vz_exp( int, double *, int, double *, int, double * );
extern void __vz_log( int, double *, int, double *, int );

void
__vz_pow( int n, double * restrict x, int stridex, double * restrict y,
	int stridey, double * restrict z, int stridez, double * restrict tmp )
{
	double	r;
	int		i, j, k;

	__vz_log( n, x, stridex, tmp, 1 );
	stridey <<= 1;
	for ( i = j = 0; i < n; i++, j += stridey )
	{
		k = i << 1;
		r = y[j] * tmp[k] - y[j+1] * tmp[k+1];
		tmp[k+1] = y[j+1] * tmp[k] + y[j] * tmp[k+1];
		tmp[k] = r;
	}
	__vz_exp( n, tmp, 1, z, stridez, tmp + n + n );
}
