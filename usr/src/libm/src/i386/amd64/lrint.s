/*
 * Copyright 2017 John R. Marino <draco@marino.st>
 * Derived from FreeBSD/OpenBSD/OpenLibm (BSD/PD licensed)
 */

	.file "lrint.s"

#include "libm.h"
	.weak __lrint
	.type __lrint,@function

	ENTRY(lrint)
	cvtsd2si %xmm0, %rax
	ret
	SET_SIZE(lrint)
	.section .note.GNU-stack,"",%progbits
