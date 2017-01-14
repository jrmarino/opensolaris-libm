/* Added by J.R. Marino to allow build outside of Solaris */

#if defined(__x86_64) || defined(__amd64)

#define	_LITTLE_ENDIAN

#elif defined(__sparc) || defined(__sparcv9) || defined(__sparc__)

#define	_BIG_ENDIAN

#endif
