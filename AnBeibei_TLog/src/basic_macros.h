/*checks for pragma once support*/
#if (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x5140)) || (defined(__SUNPRO_CC) && (__SUNPRO_CC >= 0x5140))
//Oracle Developer Studio C/C++ (12.5 or later)
#    define _pragma_once_support 1
#elif defined(_MSC_VER) && (_MSC_VER >= 1020)	//MSVC
#    define _pragma_once_support 1
#elif defined(__clang__)		//clang
#    define _pragma_once_support 1
#elif defined(__COMO__)			//comeau
#    define _pragma_once_support 1
#elif defined(__CODEGEARC__) && (__CODEGEARC__ >=650)
//C++Builder (XE3 or greater)
#    define _pragma_once_support 1
#elif defined(__DMC__)			//Digital Mars
#    define _pragma_once_support 1
#elif defined(__GNUC__) && ((__GNUC__ > 3) || (defined(__GNUC_MINOR__) && (__GNUC__ == 3) && (__GNUC_MINOR__ >= 4)))
//GCC
#    define _pragma_once_support 1
#elif defined(__HP_aCC) && (__HP_aCC >= 61200)
//HP aC++ (A.06.12)
#    define _pragma_once_support 1
#elif defined(__xlC__) && ((__xlC__ > 1301) || ((__xlC__ == 1301) && (__xlC_ver__ > 0100)))
//IBM
#    define _pragma_once_support 1
#elif defined(__INTEL_COMPILER) || defined(__ICC) || defined(__ECC) || defined(__ICL)
//intel
#    define _pragma_once_support 1
#elif defined(__POCC__)			//Pelles C
#    define _pragma_once_support 1
#elif defined(__CC_ARM)			//ARM compiler
#    define _pragma_once_support 1
#elif defined(__IAR_SYSTEMS_ICC__)	//IAR C/C++
#    define _pragma_once_support 1
#elif defined(__PGI)			//Portland Group C/C++
#    define _pragma_once_support 0
#else							//Unknown
#    define _pragma_once_support 0
#endif

/*if pragma once support then use it in addition to include guard*/
#if _pragma_once_support
#    pragma once
#endif

// #pragma once is a non-standard pragma
// Standard approach to preventing multiple inclusion of the same header is by using include guards:
#ifndef TLOG_BASIC_MACROS_H
#define TLOG_BASIC_MACROS_H

#if defined(_WIN32)
#   define OS_WIN
#endif

// Annoying stuff for windows -- makes sure clients can import these functions
#ifndef ANBEIBEI_TLOG_DLL_DECL
#   if defined(_WIN32) && !defined(__CYGWIN__) && !defined(_DLL_)
#       define ANBEIBEI_TLOG_DLL_DECL  __declspec(dllimport)
#   elif !defined(_STATIC_)
#       define ANBEIBEI_TLOG_DLL_DECL  __declspec(dllexport)
#	else
#       define ANBEIBEI_TLOG_DLL_DECL
#   endif
#endif

#define DISALLOW_COPY_AND_ASSIGN(class_name)              \
    class_name(const class_name&) = delete;               \
    class_name& operator=(class_name&) = delete;          \
    class_name& operator=(const class_name&) = delete;

#define DISALLOW_MOVE_AND_ASSIGN(class_name)              \
    class_name(const class_name&&) = delete;              \
    class_name& operator=(class_name&&) = delete;         \

#endif /* !TLOG_BASIC_MACROS_H */