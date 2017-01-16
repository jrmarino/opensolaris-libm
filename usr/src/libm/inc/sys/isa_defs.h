/* Added by J.R. Marino to allow build outside of Solaris */

#ifndef _ISA_DEFS_H
#define	_ISA_DEFS_H

#if defined(__x86_64) || defined(__amd64)

#ifndef _LITTLE_ENDIAN
#define	_LITTLE_ENDIAN
#endif

#ifndef __x86
#define	__x86
#endif

#elif defined(__sparc) || defined(__sparcv9) || defined(__sparc__)

#ifndef _BIG_ENDIAN
#define	_BIG_ENDIAN
#endif

#endif
#endif	/* _ISA_DEFS_H */
