/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Following defines are available:
      WINDOWS - Windows             applications
      MAC     - Mac OS X            applications
      LINUX   - Linux               applications
      ANDROID - Android             applications
      IOS     - iOS                 applications
      WEB     - Web                 applications
      DESKTOP - Windows, Mac, Linux applications
      MOBILE  - Android, iOS        applications
      APPLE   - Mac, iOS            applications
      X64     - 64-bit              applications

   Sample Usage:
   
      #ifdef WINDOWS
         This line will compile only on Windows platform!
      #endif

/******************************************************************************/
// detect platform
#ifdef _WIN32 // Windows
   #define PLATFORM(windows, unix) windows
   #define WINDOWS
#elif defined __APPLE__ // Apple - Mac or iOS
   #define  PLATFORM(windows, unix) unix
   #define  APPLE
   #include <TargetConditionals.h>
   #if      TARGET_OS_IPHONE
      #define IOS // iOS
   #else
      #define MAC // Mac
   #endif
#elif defined ANDROID // Android
   #define PLATFORM(windows, unix) unix
 //#define ANDROID this is already defined on Android
#elif defined __linux__ // Linux (check this after Apple and Android)
   #define PLATFORM(windows, unix) unix
   #define LINUX
#elif defined EMSCRIPTEN
   #define PLATFORM(windows, unix) unix
   #define WEB
#else
   #error Unsupported platform detected
#endif

#if defined WINDOWS || defined MAC || defined LINUX
   #define DESKTOP
#endif

#if defined ANDROID || defined IOS
   #define MOBILE
#endif

#if defined _WIN64 || defined __LP64__
   #define X64 // this is a 64-bit platform
#endif

#if !defined WINDOWS || _MSC_VER>=1600 // not Windows or Visual Studio 2010 available
   #define HAS_MOVE_CONSTRUCTOR // C++11 move constructor is available
#endif

#ifdef WINDOWS
   #ifndef __PLACEMENT_NEW_INLINE
      #define __PLACEMENT_NEW_INLINE
      inline void* __cdecl operator new   (size_t, void *where) {return where;}
      inline void  __cdecl operator delete(void *, void *     )throw() {}
   #endif
   #undef KF_UP
   #undef TRANSPARENT
   #undef ERROR
   #undef INPUT_MOUSE
   #undef INPUT_KEYBOARD
   #undef min
   #undef max
#else
   #include <new>
   #include <typeinfo>
   #include <stdint.h>
   #include <stddef.h>
   #undef   NULL
#endif
/******************************************************************************/
