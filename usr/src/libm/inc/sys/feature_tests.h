#ifndef _SYS_FEATURE_TESTS_H
#define	_SYS_FEATURE_TESTS_H

#ifdef	__cplusplus
extern "C" {
#endif

#if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#define	_POSIX_C_SOURCE 1
#endif

#if defined(_XOPEN_SOURCE) || defined(_POSIX_C_SOURCE)
#define	__XOPEN_OR_POSIX
#endif

#define	_STDC_C11
#define	_STDC_C99

#define	_ISO_CPP_14882_1998
#define	_ISO_C_9899_1999
#define	_ISO_C_9899_2011

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_FEATURE_TESTS_H */