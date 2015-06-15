/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Str8' to handle 8-bit per character text string management.

/******************************************************************************/
struct Str8 // Text String (8-bit per character)
{
   // get
          operator CChar8*()C {return _d.data();} // cast to CChar8*
  CChar8* operator()(      )C {return _d.data();} // get  text data
   Char8  operator[](Int  i)C;                    // get  i-th character, returns '\0' if 'i' is out of range

   Bool  is      ()C {return _length>0                     ;} // if  contains any data
   Int   length  ()C {return _length                       ;} // get current length
   Char8 first   ()C {return _length ? _d[        0] : '\0';} // get first character present in the string, '\0' if empty
   Char8 last    ()C {return _length ? _d[_length-1] : '\0';} // get last  character present in the string, '\0' if empty
   UInt  memUsage()C {return           _d.memUsage()       ;} // get memory usage

   // operations
   Str8& del       (                     ); // clear stored data and free helper memory
   Str8& clear     (                     ); // clear stored data
   Str8& insert    (Int i, C Str8 &text  ); // insert 'text' at 'i' string position
   Str8& remove    (Int i,   Int   num=1 ); // remove 'num' characters starting from 'i-th'
   Str8& removeLast(                     ); // remove  last character in the string
   Str8& clip      (Int length           ); // clip current length to 'length'
   Str8& reserve   (Int length           ); // allocate enough space for the string to handle 'length' characters, if the parameter is smaller than current string length then no operation is performed
   Str8& reverse   (                     ); // reverse the order of characters
   Str8& replace   (Char8 src, Char8 dest); // replace character 'src' to 'dest'
   Str8& tailSlash (Bool on              ); // exclude or include slash after string (if including and string is empty then slash will not be added, if excluding and string consists only of slash then it will not be removed)

   Str8& space(Int num=1); // add a space if string isn't empty and does not end with a new line or space, 'num'=number of spaces to insert
   Str8& line (Int num=1); // add a line  if string isn't empty and does not end with a new line         , 'num'=number of lines  to insert

   Str8& operator=(  CChar  *t);   Str8& operator+=(  CChar  *t);   Str  operator+(  CChar  *t)C;
   Str8& operator=(  CChar8 *t);   Str8& operator+=(  CChar8 *t);   Str8 operator+(  CChar8 *t)C;
   Str8& operator=(C Str    &s);   Str8& operator+=(C Str    &s);   Str  operator+(C Str    &s)C;
   Str8& operator=(C Str8   &s);   Str8& operator+=(C Str8   &s);   Str8 operator+(C Str8   &s)C;
   Str8& operator=(  Char    c);   Str8& operator+=(  Char    c);   Str  operator+(  Char    c)C;
   Str8& operator=(  Char8   c);   Str8& operator+=(  Char8   c);   Str8 operator+(  Char8   c)C;
   Str8& operator=(  Bool    b);   Str8& operator+=(  Bool    b);   Str8 operator+(  Bool    b)C;
   Str8& operator=(  SByte   i);   Str8& operator+=(  SByte   i);   Str8 operator+(  SByte   i)C;
   Str8& operator=(  Int     i);   Str8& operator+=(  Int     i);   Str8 operator+(  Int     i)C;
   Str8& operator=(  Long    i);   Str8& operator+=(  Long    i);   Str8 operator+(  Long    i)C;
   Str8& operator=(  Byte    u);   Str8& operator+=(  Byte    u);   Str8 operator+(  Byte    u)C;
   Str8& operator=(  UInt    u);   Str8& operator+=(  UInt    u);   Str8 operator+(  UInt    u)C;
   Str8& operator=(  ULong   u);   Str8& operator+=(  ULong   u);   Str8 operator+(  ULong   u)C;
   Str8& operator=(  Flt     f);   Str8& operator+=(  Flt     f);   Str8 operator+(  Flt     f)C;
   Str8& operator=(  Dbl     d);   Str8& operator+=(  Dbl     d);   Str8 operator+(  Dbl     d)C;
   Str8& operator=(  CPtr    p);   Str8& operator+=(  CPtr    p);   Str8 operator+(  CPtr    p)C;
   Str8& operator=(C Vec2   &v);   Str8& operator+=(C Vec2   &v);   Str8 operator+(C Vec2   &v)C;
   Str8& operator=(C VecD2  &v);   Str8& operator+=(C VecD2  &v);   Str8 operator+(C VecD2  &v)C;
   Str8& operator=(C VecI2  &v);   Str8& operator+=(C VecI2  &v);   Str8 operator+(C VecI2  &v)C;
   Str8& operator=(C Vec    &v);   Str8& operator+=(C Vec    &v);   Str8 operator+(C Vec    &v)C;
   Str8& operator=(C VecD   &v);   Str8& operator+=(C VecD   &v);   Str8 operator+(C VecD   &v)C;
   Str8& operator=(C VecI   &v);   Str8& operator+=(C VecI   &v);   Str8 operator+(C VecI   &v)C;
   Str8& operator=(C Vec4   &v);   Str8& operator+=(C Vec4   &v);   Str8 operator+(C Vec4   &v)C;
   Str8& operator=(C VecD4  &v);   Str8& operator+=(C VecD4  &v);   Str8 operator+(C VecD4  &v)C;
   Str8& operator=(C VecI4  &v);   Str8& operator+=(C VecI4  &v);   Str8 operator+(C VecI4  &v)C;
   Str8& operator=(C VecB4  &v);   Str8& operator+=(C VecB4  &v);   Str8 operator+(C VecB4  &v)C;
   Str8& operator=(C BStr   &s);   Str8& operator+=(C BStr   &s);   Str  operator+(C BStr   &s)C;
#ifdef HAS_MOVE_CONSTRUCTOR
   Str8& operator=(  Str8  &&s);
#endif

   // io
   void save(File &f)C; // save string using f.putStr(T)
   Bool load(File &f) ; // load string using f.getStr(T), false on fail

   Str8(         );
   Str8(Char    c);
   Str8(Char8   c);
   Str8(CChar  *t);
   Str8(CChar8 *t);
   Str8(C Str  &s);
   Str8(C Str8 &s);
#ifdef HAS_MOVE_CONSTRUCTOR
   Str8(  Str8&&s);
#endif

private:
   Mems<Char8> _d;
   Int         _length;

   friend struct _List;
};
/******************************************************************************/
inline Int Elms(C Str8 &str) {return str.length();}
/******************************************************************************/
