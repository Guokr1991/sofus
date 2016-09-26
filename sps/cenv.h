/**
 * @file   cenv.h
 * @author Jens Munk Hansen <jens.munk.hansen@gmail.com>
 * @date   Sat Nov 29 17:48:45 2014
 *
 * @brief  Environment macros introduced for portability
 *         This file must be kept C compliant
 *
 *
 */
#pragma once

//TODO:
#if 0
#if __cplusplus <= 199711L
#error This library needs at least a C++11 compliant compiler
#endif
// 201103L is C++11
#endif


#include <cstdarg>

// TODO: Add other OS'es
#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
# define SPS_OS_WIN
#endif

#ifndef SPS_UNREFERENCED_PARAMETER
# define SPS_UNREFERENCED_PARAMETER(x) ((void)(x))
#endif

#ifdef __GNUC__
# include <features.h>
#endif

#if defined(__STDC__)
# define C89
# if defined(__STDC_VERSION__)
#  define C90
#  if (__STDC_VERSION__ >= 199409L)
#   define C94
#  endif
#  if (__STDC_VERSION__ >= 199901L)
#   define C99
#  endif
#  if (__STDC_VERSION__ >= 201112L)
#   define C11
#  endif
# elif defined(__cplusplus)
#  ifdef __USE_ISOC99
#   define C99
#  endif
# endif
#endif

// Alignment, TODO: Use alignas if present
#if (defined(_MSC_VER) && defined(_WIN32))
# define ALIGN16_BEGIN __declspec(align(16))
# define ALIGN16_END
#elif defined(__GNUC__)
# define ALIGN16_BEGIN
# define ALIGN16_END __attribute__((aligned(16)))
#endif

// Static inlines
#if (defined(_MSC_VER) && defined(_WIN32))
// Note when used inside a namespace, the static is superfluous
# define STATIC_INLINE_BEGIN static inline //__forceinline
# define STATIC_INLINE_END
#elif (defined(__GNUC__))
# define STATIC_INLINE_BEGIN static inline
# if defined(__CYGWIN__)
#  define STATIC_INLINE_END
# else
#  define STATIC_INLINE_END /* Work on this */ //__attribute__ ((always_inline))
# endif
#endif

#define __BEGIN__       {
#define __END__         goto exit; exit: ; }

// Thread-local storage
#if defined(_WIN32) && defined(_MSC_VER)
# define __THREAD __declspec(thread)
#elif defined(__GNUC__)
# define __THREAD __thread
#endif

#ifdef __GNUG__
# define GCC_VERSION (__GNUC__ * 10000 \
              + __GNUC_MINOR__ * 100        \
              + __GNUC_PATCHLEVEL__)
#endif

// TODO: Make file with helper macros
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/* count arguments */
#define NUMARGS(...) \
  SELECT_5TH(__VA_ARGS__, 4, 3, 2, 1, 0, throwaway, throwaway)
#define SELECT_5TH(a1,a2,a3,a4,a5, ...) a5

/* expands to the first arguments */
#define RETURN_FIRST(...) RETURN_FIRST_HELPER(__VA_ARGS__, throwaway)
#define RETURN_FIRST_HELPER(first, ...) return first;

#define FIRST(...) FIRST_HELPER(__VA_ARGS__, throwaway)
#define FIRST_HELPER(first, ...) first

/*
 * if there's only one argument, expands to nothing.  if there is more
 * than one argument, expands to a comma followed by everything but
 * the first argument.  only supports up to 9 arguments but can be
 * trivially expanded.
 */
#define REST(...) REST_HELPER(NNUM(__VA_ARGS__), __VA_ARGS__)
#define REST_HELPER(qty, ...) REST_HELPER2(qty, __VA_ARGS__)
#define REST_HELPER2(qty, ...) REST_HELPER_##qty(__VA_ARGS__)
#define REST_HELPER_ONE(first)
#define REST_HELPER_TWOORMORE(first, ...) , __VA_ARGS__
#define NNUM(...) \
    SELECT_10TH(__VA_ARGS__, TWOORMORE, TWOORMORE, TWOORMORE, TWOORMORE,\
                TWOORMORE, TWOORMORE, TWOORMORE, TWOORMORE, ONE, throwaway)
#define SELECT_10TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, ...) a10

/* Local variables: */
/* indent-tabs-mode: nil */
/* tab-width: 2 */
/* c-basic-offset: 2 */
/* End: */
