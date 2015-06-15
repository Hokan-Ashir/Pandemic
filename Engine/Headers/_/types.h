/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
typedef                       bool               Bool       ; // Boolean Value (8-bit) false/true

typedef                       char               Char8      ; // Character ( 8-bit)
typedef                       wchar_t            Char       ; // Character (16-bit)

typedef   PLATFORM(  signed __int8 ,   int8_t)   I8 ,  SByte; //   Signed Int ( 8-bit)                        -128 .. 127
typedef   PLATFORM(unsigned __int8 ,  uint8_t)   U8 ,   Byte; // Unsigned Int ( 8-bit)                           0 .. 255
typedef   PLATFORM(  signed __int16,  int16_t)   I16,  Short; //   Signed Int (16-bit)                     -32 768 .. 32 767
typedef   PLATFORM(unsigned __int16, uint16_t)   U16, UShort; // Unsigned Int (16-bit)                           0 .. 65 535
typedef   PLATFORM(  signed __int32,  int32_t)   I32,    Int; //   Signed Int (32-bit)              -2 147 483 648 .. 2 147 483 647
typedef   PLATFORM(unsigned __int32, uint32_t)   U32,   UInt; // Unsigned Int (32-bit)                           0 .. 4 294 967 295
typedef   PLATFORM(  signed __int64,  int64_t)   I64,   Long; //   Signed Int (64-bit)  -9 223 372 036 854 775 808 ..  9 223 372 036 854 775 807
typedef   PLATFORM(unsigned __int64, uint64_t)   U64,  ULong; // Unsigned Int (64-bit)                           0 .. 18 446 744 073 709 551 615

typedef                       float              F32, Flt   ; //  Float (32-bit)  1-bit sign +  8-bit exponent + 23-bit mantissa
typedef                       double             F64, Dbl   ; // Double (64-bit)  1-bit sign + 11-bit exponent + 52-bit mantissa

typedef                       void              *Ptr        ; // General Pointer               (32-bit or 64-bit)
typedef                 const void              *CPtr       ; // General Pointer to const data (32-bit or 64-bit)
/******************************************************************************/
typedef   const Char8   CChar8; // Const Char8
typedef   const Char    CChar ; // Const Char
/******************************************************************************/
#ifdef X64
   typedef I64  IntPtr; //   Signed Int capable of storing full memory address (needs to be 64-bit on 64-bit platforms)
   typedef U64 UIntPtr; // Unsigned Int capable of storing full memory address (needs to be 64-bit on 64-bit platforms)
#else
   typedef I32  IntPtr; //   Signed Int capable of storing full memory address (needs to be 32-bit on 32-bit platforms)
   typedef U32 UIntPtr; // Unsigned Int capable of storing full memory address (needs to be 32-bit on 32-bit platforms)
#endif
/******************************************************************************/
