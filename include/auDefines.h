/**
 * @file auDefines.h
 * @author Rivaz (idv19c.rrivera@uartesdigitales.edu.mx)
 * @date 7/10/2022
 */

#pragma once
#include <assert.h>

/************************************************************************/
/**
 * Initial platform/compiler-related stuff to set.
*/
/************************************************************************/
#define AU_PLATFORM_WIN32   1                  //Windows Platform
#define AU_PLATFORM_LINUX   2                  //Linux Platform
#define AU_PLATFORM_OSX     3


#define AU_COMPILER_MSVC    1                  //Visual Studio Compiler
#define AU_COMPILER_GNUC    2                  //GCC Compiler
#define AU_COMPILER_INTEL   3                  //Intel Compiler
#define AU_COMPILER_CLANG   4                  //Clang Compiler

#define AU_ARCHITECTURE_X86_32 1               //Intel x86 32 bits
#define AU_ARCHITECTURE_X86_64 2               //Intel x86 64 bits

#define AU_ENDIAN_LITTLE  1
#define AU_ENDIAN_BIG     2

//Define the actual endian type (little endian for Windows, Linux, Apple and PS4)
#define UA_ENDIAN UA_ENDIAN_LITTLE

#define AU_VERSION_MAJOR    0                 //Engine version major
#define AU_VERSION_MINIOR   1
#define AU_VERSION_PATCH    0
#define AU_VERSION_BUILD    1

//Define if on crate a we want to report warnings on unknown symbols
#define AU_DEBUG_DETAILED_SYMBOLS   1

/************************************************************************/
/**
 * Compiler type and version
 */
 /************************************************************************/

#if defined(__clang__)
#   define AU_COMPILER AU_COMPILER_CLANG
#   define AU_COMP_VER __cland_version__
#   define AU_THREADLOCAL __thread
#   define AU_STDCALL __attribute__((stdcall))
#   define AU_CDECL __attribute__((cdecl))
#   define AU_FALLTHROUHG [[clang::fallthrough]];
#elif defined (__GNUC__) //Check after Cland, as Clang defines this too
#   define AU_COMPILER AU_COMPILER_GNUC
#   define AU_COMP_VER (((__GNUC__)*100)+(__GNUC_MINOR__*10)+__GNUC_PATCHLEVEL__)
#   define AU_THREADLOCAL __thread
#   define AU_STDCALL __attribute__((stdcall))
#   define AU_CDECL __attribute__((cdecl))
#   define AU_FALLTHROUHG __attribute__((fallthrough));
#elif defined (__INTEL_COMPILER)
#   define AU_COMPILER AU_COMPILER_INTEL
#   define AU_COMP_VER __INTEL_COMPILER
#   define AU_STDCALL __stdcall
#   define AU_CDECL __cdecl
#   define AU_FALLTHROUHG 

/**
 * OA_THREADLOCAL define is down below because Intel compiler defines it
 * differently based on platform
 */

 //Check after Clang end Intel, we could be building with either with Vs
#elif defined (_MSC_VER)
#   define AU_COMPILER AU_COMPILER_MSVC
#   define AU_COMP_VER _MSC_VER
#   define AU_THREADLOCAL __declspec
#   define AU_STDCALL __stdcall
#   define AU_CDECL __cdecl
#   define AU_FALLTHROUHG
#   undef __PRETTY_FUNCTION__
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#else
//No know compiler found, send the error to the output (if any)
#   pragma error "No known compuler. "
#endif

/************************************************************************/
/**
 * See if we can use __forceinline or if we need to use __inline instead
 */
 /************************************************************************/
#if AU_COMPILER == AU_COMPILER_MSVC
# if AU_COMP_VER >= 1200
#   define FORCEINLINE __forceinline
#   ifndef RESTRICT 
#     define RESTRICT __restrict
#   endif
# endif
#elif defined (__MINGW32__)
# if !defined (FORCEINLINE)
#   define FORCEINLINE __inline
#   ifndef RESTRICT
#     define RESTRICT
#   endif
# endif
#else
# define FORCEINLINE __inline
# ifndef RESTRICT
#   define RESTRICT __restrict
# endif
#endif

/************************************************************************/
/**
 * Finds the current platform
 */
 /************************************************************************/
#if defined (__WIN32__) || defined (_WIN32)
# define AU_PLATFORM AU_PLATFORM_WIN32
#elif defined (__APPLE_CC__ )
# define AU_PLATFORM AU_PLATFORM_OSX
#elif defined (__ORBIS__)
# define AU_PLATFORM AU_PLATFORM_LINUX
#endif

/************************************************************************/
/**
 * Find the architecture type
 */
 /************************************************************************/
#if defined (__x86_x64__) || defined(_M_X64)    //If this is a x64 compile
# define AU_ARCH_TYPE AU_ARCHITECTURE_X86_64
#else
#  define AU_ARCH_TYPE AU_ARCHITECTURE_X86_32
#endif

/************************************************************************/
/**
 * Memory Alignment macros
 */
 /************************************************************************/
#if AU_COMPILER == AU_COMPILER_MSVC
# define MS_ALIGN(n) __declspec(align(n))
# ifndef GCC_PACK
#   define GCC_PACK(n)
# endif
# ifndef GCC_ALIGN
#   define GCC_ALIGN(n)
# endif
#elif (AU_COMPILER == AU_COMPILER_GNUC)
# define MS_ALIGN(n)
# define GCC_PACK(n)
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#else
# define MS_ALIGN(n)
# define GCC_PACK(n) __attribute__((packed, aligned(n)))
# define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#endif

/************************************************************************/
/**
 * For throw override (deprecated on c++11 but VS does not have handle )
 */
 /************************************************************************/
#if AU_COMPILER == AU_COMPILER_MSVC
# define _NOEXCEPT noexcept
#elif AU_COMPILER == AU_COMPILER_INTEL
# define _NOEXCEPT noexcept
#elif AU_COMPILER == AU_COMPILER_GNUC
# define _NOEXCEPT noexcept
#else
# define _NOEXCEPT
#endif

/************************************************************************/
/**
 * Library export specifics
 */
 /************************************************************************/
#if AU_PLATFORM == AU_PLATFORM_WIN32
# if AU_COMPILER == AU_COMPILER_MSVC
#   if defined( AU_STATIC_lib )
#     define AU_UTILITY_EXPORT
#   else
#     if defined ( AU_UTILITY_EXPORTS )
#       define AU_UTILITY_EXPORT __declspec( dllexport )
#     else
#       define AU_UTILITY_EXPORT __declspec( dllimport )
#     endif
#   endif
# else //Any other compiler
#   if defined( AU_STATIC_LIB )
#     define AU_UTILITY_EXPORT
#   else
#     if defined( AU_UTILITY_EXPORTS )
#       define AU_UTILITY_EXPORT __attribute__ ((dllexport))
#     else
#       define AU_UTILITY_EXPORT __attribute__ ((dllimport))
#     endif
#   endif
# endif
# define AU_UTILITY_HIDDEN
#else
# define AU_UTILITY_EXPORT __attribute__ ((visibility ("default")))
# define AU_UTILITY_HIDDEN __attribute__ ((visibility ("hidden")))
#endif

 //DLL export plug ins
#if AU_PLATFORM == AU_PLATFORM_WIN32
# if AU_COMPILER == AU_COMPILER_MSVC
#   define AU_PLUGIN_EXPORT __declspec(dllexport)
# else
#   define AU_PLUGIN_EXPORT __attribute__ ((dllexport))
# endif
#else
#  define AU_PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

/************************************************************************/
/**
 * Window specific Settings
 */
 /************************************************************************/
 //Win32
#if AU_PLATFORM == AU_PLATFORM_WIN32
# if defined(_DEBUG) || defined(DEBUG)
#   define AU_DEBUG_MODE 1
# else
#   define AU_DEBUG_MODE 0
# endif
# if AU_COMPILER == AU_COMPILER_INTEL
#   define AU_THREADLOCAL __declspec(thread)
# endif
#endif //OA_PLATFORM

/************************************************************************/
/**
 * LINUX-Apple specific Settings
 */
 /************************************************************************/

 //
#if AU_PLATFORM == AU_PLATFORM_LINUX || OA_PLATFORM == OA_PLATFORM_OSX

//if we're on debug mode
# if defined(_DEBUG) || defined(DEBUG)
#   define AU_DEBUG_MODE 1
# else
#   define AU_DEBUG_MODE 0
# endif
# if AU_COMPILER == AU_COMPILER_INTEL
#   define AU_THREADLOCAL thread
# endif
#endif //OA_PLATFORM

/************************************************************************/
/**
 * DEfinition of DEbug macros
 */
 /************************************************************************/
#if AU_DEBUG_MODE
# define AU_DEBUG_ONLY(x) x
# define AU_ASSERT(x) assert(x)
#else
# define AU_DEBUG_ONLY(x)
# define AU_ASSERT(x)
#endif

/************************************************************************/
/**
 * Disable some compiler warnings
 */
 /************************************************************************/

 //If we are compiling with VS
#if AU_COMPILER == AU_COMPILER_MSVC

# define _CRT_SECURE_NO_WARNINGS

# pragma warning(disable : 4201)

# pragma warning(disable : 4996)

# pragma warning(disable : 4251)

# pragma warning(disable : 4503)

#endif

#define OA_EXTERN extern "C"