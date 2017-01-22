/*
 * Copyright 2017 John R. Marino <draco@marino.st>
 * Derived from FreeBSD/OpenBSD/OpenLibm (BSD/PD licensed)
 */

	.file "lrintl.s"

#include "libm.h"
	.weak __lrintl
	.type __lrintl,@function

	ENTRY(lrintl)
	fldt	8(%rsp)
	subq	$8,%rsp
	fistpll	(%rsp)
	popq	%rax
	ret
	SET_SIZE(lrintl)
	.section .note.GNU-stack,"",%progbits
