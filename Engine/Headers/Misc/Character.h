/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum CHAR_FLAG // Character Flag
{
   CHARF_DIG2 =0x01, // if binary  digit       01
   CHARF_DIG10=0x02, // if decimal digit       0123456789
   CHARF_DIG16=0x04, // if hex     digit       0123456789ABCDEFabcdef
   CHARF_SIGN =0x08, // if standard sign       `~!@#$%^&-+*=()[]{}<>;:'",./|\?
   CHARF_CHAR =0x10, // if letter or underline
   CHARF_UP   =0x20, // if letter with case up
   CHARF_SPACE=0x40, // if space character

   CHARF_DIG=CHARF_DIG10,
};

UInt CharFlag(Char  c); // get CHAR_FLAG
UInt CharFlag(Char8 c); // get CHAR_FLAG
/******************************************************************************/
enum CHAR_TYPE // Character Type
{
   CHART_NONE , // none/unknown
   CHART_CHAR , // letter or digit
   CHART_SPACE, // space
   CHART_SIGN , // standard sign
};

CHAR_TYPE CharType(Char  c); // get character type
CHAR_TYPE CharType(Char8 c); // get character type
/******************************************************************************/
Bool WhiteChar(Char c); // if char is a white char - ' ', '\t', '\n', '\r'

Char8 Char16To8(Char  c); // convert 16-bit to  8-bit character
Char  Char8To16(Char8 c); // convert  8-bit to 16-bit character

Char  CaseDown(Char  c); // return case down
Char8 CaseDown(Char8 c); // return case down
Char  CaseUp  (Char  c); // return case up
Char8 CaseUp  (Char8 c); // return case up

Int Compare(Char  a, Char  b); // compare characters, case insensitive, returns -1, 0, +1
Int Compare(Char  a, Char8 b); // compare characters, case insensitive, returns -1, 0, +1
Int Compare(Char8 a, Char  b); // compare characters, case insensitive, returns -1, 0, +1
Int Compare(Char8 a, Char8 b); // compare characters, case insensitive, returns -1, 0, +1

Bool EqualCS(Char  a, Char  b); // if equal characters, case sensitive
Bool EqualCS(Char  a, Char8 b); // if equal characters, case sensitive
Bool EqualCS(Char8 a, Char  b); // if equal characters, case sensitive
Bool EqualCS(Char8 a, Char8 b); // if equal characters, case sensitive
/******************************************************************************/
