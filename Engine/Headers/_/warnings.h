/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
ASSERT(SIZE(Bool)==1); // if you receive compiler error pointing to this line it means you need to change your XCode Project Settings "GCC Language \ Use One Byte Bool = YES"
ASSERT(SIZE(Char)==2); // if you receive compiler error pointing to this line it means you need to change your XCode Project Settings "GCC Language \ Other C Flags     = -fshort-wchar"
/******************************************************************************/
#ifdef WINDOWS
   #pragma warning(disable:4018) // signed/unsigned mismatch
   #pragma warning(disable:4244) // conversion from 'TYPE_A' to 'TYPE_B', possible loss of data
   #pragma warning(disable:4258) // definition from the for loop is ignored; the definition from the enclosing scope is used
   #pragma warning(disable:4355) // 'this' : used in base member initializer list
   #pragma warning(disable:4521) // multiple copy constructors specified

#endif
/******************************************************************************/
