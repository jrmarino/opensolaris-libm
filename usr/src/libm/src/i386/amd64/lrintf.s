/*
 * Copyright 2017 John R. Marino <draco@marino.st>
 * Derived from FreeBSD/OpenBSD/OpenLibm (BSD/PD licensed)
 */

	.file "lrintf.s"

#include "libm.h"
	.weak __lrintf
	.type __lrintf,@function

	ENTRY(lrintf)
	cvtss2si %xmm0, %rax
	ret
	SET_SIZE(lrintf)
	.section .note.GNU-stack,"",%progbits
