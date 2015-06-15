/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Str' to handle text string management.

      Sample Usage:
         Str s="abc";   // set    's' string to "abc" text
         s+="def";      // append 's' string by "def" text                (now 's' has "abcdef" text)
         s=S+"text "+5; // set    's' string from text appended by number (now 's' has "text 5" text)

   Use 'StrLibrary' to store multiple strings in a file using least possible amount of bytes.

      'StrLibrary' works by creating first a database of common strings which may occur frequently when storing them in files.
      Later when strings are written to files, they are first checked if they're present in the database,
      if they are, then only index is stored (saving index requires less space than saving full string, which saves space).
      If the string is not present in the database then it is stored not as index but as a string.

      For example if string library was created with "abcdef" "zzzz" strings in the database:
         storing "abcdef" string in the file will require storing only index
         storing "qwerty" string in the file will require storing full string.

      Please remember that this implies the requirement that when reading previously written strings,
      you must use a 'StrLibrary' which was initialized with the exact same common strings array database
      as the 'StrLibrary' which was used for writing the strings.

/******************************************************************************/
// STRING
/******************************************************************************/
struct Str // Text String (16-bit per character)
{
   // get
         operator CChar*()C {return _d.data();} // cast to CChar*
  CChar* operator()(     )C {return _d.data();} // get  text data
   Char  operator[](Int i)C;                    // get  i-th character, returns '\0' if 'i' is out of range

   Bool is      ()C {return _length>0                     ;} // if  contains any data
   Int  length  ()C {return _length                       ;} // get current length
   Char first   ()C {return _length ? _d[        0] : '\0';} // get first character present in the string, '\0' if empty
   Char last    ()C {return _length ? _d[_length-1] : '\0';} // get last  character present in the string, '\0' if empty
   UInt memUsage()C {return           _d.memUsage()       ;} // get memory usage

   // operations
   Str& del       (                   ); // clear stored data and free helper memory
   Str& clear     (                   ); // clear stored data
   Str& insert    (Int i, C Str &text ); // insert 'text' at 'i' string position
   Str& remove    (Int i,   Int  num=1); // remove 'num' characters starting from 'i-th'
   Str& removeLast(                   ); // remove  last character in the string
   Str& clip      (Int length         ); // clip current length to 'length'
   Str& reserve   (Int length         ); // allocate enough space for the string to handle 'length' characters, if the parameter is smaller than current string length then no operation is performed
   Str& reverse   (                   ); // reverse the order of characters
   Str& replace   (Char src, Char dest); // replace character 'src' to 'dest'
   Str& tailSlash (Bool on            ); // exclude or include slash after string (if including and string is empty then slash will not be added, if excluding and string consists only of slash then it will not be removed)

   Str& space(Int num=1); // add a space if string isn't empty and does not end with a new line or space, 'num'=number of spaces to insert
   Str& line (Int num=1); // add a line  if string isn't empty and does not end with a new line         , 'num'=number of lines  to insert

   Str& operator=(  CChar  *t);   Str& operator+=(  CChar  *t);   Str operator+(  CChar  *t)C;
   Str& operator=(  CChar8 *t);   Str& operator+=(  CChar8 *t);   Str operator+(  CChar8 *t)C;
   Str& operator=(C Str    &s);   Str& operator+=(C Str    &s);   Str operator+(C Str    &s)C;
   Str& operator=(C Str8   &s);   Str& operator+=(C Str8   &s);   Str operator+(C Str8   &s)C;
   Str& operator=(  Char    c);   Str& operator+=(  Char    c);   Str operator+(  Char    c)C;
   Str& operator=(  Char8   c);   Str& operator+=(  Char8   c);   Str operator+(  Char8   c)C;
   Str& operator=(  Bool    b);   Str& operator+=(  Bool    b);   Str operator+(  Bool    b)C;
   Str& operator=(  SByte   i);   Str& operator+=(  SByte   i);   Str operator+(  SByte   i)C;
   Str& operator=(  Int     i);   Str& operator+=(  Int     i);   Str operator+(  Int     i)C;
   Str& operator=(  Long    i);   Str& operator+=(  Long    i);   Str operator+(  Long    i)C;
   Str& operator=(  Byte    u);   Str& operator+=(  Byte    u);   Str operator+(  Byte    u)C;
   Str& operator=(  UInt    u);   Str& operator+=(  UInt    u);   Str operator+(  UInt    u)C;
   Str& operator=(  ULong   u);   Str& operator+=(  ULong   u);   Str operator+(  ULong   u)C;
   Str& operator=(  Flt     f);   Str& operator+=(  Flt     f);   Str operator+(  Flt     f)C;
   Str& operator=(  Dbl     d);   Str& operator+=(  Dbl     d);   Str operator+(  Dbl     d)C;
   Str& operator=(  CPtr    p);   Str& operator+=(  CPtr    p);   Str operator+(  CPtr    p)C;
   Str& operator=(C Vec2   &v);   Str& operator+=(C Vec2   &v);   Str operator+(C Vec2   &v)C;
   Str& operator=(C VecD2  &v);   Str& operator+=(C VecD2  &v);   Str operator+(C VecD2  &v)C;
   Str& operator=(C VecI2  &v);   Str& operator+=(C VecI2  &v);   Str operator+(C VecI2  &v)C;
   Str& operator=(C Vec    &v);   Str& operator+=(C Vec    &v);   Str operator+(C Vec    &v)C;
   Str& operator=(C VecD   &v);   Str& operator+=(C VecD   &v);   Str operator+(C VecD   &v)C;
   Str& operator=(C VecI   &v);   Str& operator+=(C VecI   &v);   Str operator+(C VecI   &v)C;
   Str& operator=(C Vec4   &v);   Str& operator+=(C Vec4   &v);   Str operator+(C Vec4   &v)C;
   Str& operator=(C VecD4  &v);   Str& operator+=(C VecD4  &v);   Str operator+(C VecD4  &v)C;
   Str& operator=(C VecI4  &v);   Str& operator+=(C VecI4  &v);   Str operator+(C VecI4  &v)C;
   Str& operator=(C VecB4  &v);   Str& operator+=(C VecB4  &v);   Str operator+(C VecB4  &v)C;
   Str& operator=(C BStr   &s);   Str& operator+=(C BStr   &s);   Str operator+(C BStr   &s)C;
#ifdef HAS_MOVE_CONSTRUCTOR
   Str& operator=(  Str   &&s);
#endif

   // io
   void save(File &f)C; // save string using f.putStr(T)
   Bool load(File &f) ; // load string using f.getStr(T), false on fail

   Str(         );
   Str(Char    c);
   Str(Char8   c);
   Str(CChar  *t);
   Str(CChar8 *t);
   Str(C Str  &s);
   Str(C Str8 &s);
#ifdef HAS_MOVE_CONSTRUCTOR
   Str(  Str &&s);
#endif

private:
   Mems<Char> _d;
   Int        _length;

   friend struct _List;
};extern
   const Str S; // Constant Empty String
/******************************************************************************/
// STRING LIBRARY
/******************************************************************************/
struct StrLibrary // String Library, efficient solution for storing multiple strings in a file using least possible amount of bytes
{
   // manage
   void del   (                                                     ); // delete manually
   void create(C Memp<Str> &strings, Bool case_sensitive, Bool paths); // create library database from 'strings' array of strings, 'paths'=if treat strings as paths (they can have '/' replaced with '\')

   // get / set
   Int elms(     )C {return _elms;} // get number of strings stored in this library
   Str elm (Int i)C;                // get i-th      string  stored in this library, NULL on fail

   void putStr(File &f, C Str &str)C;                                                         // put 'str' string into 'f' file
   void getStr(File &f,   Str &str)C;   Str getStr(File &f)C {Str s; getStr(f, s); return s;} // get 'str' string from 'f' file

   // io
   void save(File &f)C; // save
   Bool load(File &f) ; // load, false on fail

  ~StrLibrary() {del();}
   StrLibrary();
   StrLibrary(C Memp<Str> &strings, Bool case_sensitive, Bool paths);

private:
   Bool  _case_sensitive, _paths;
   Int   _elms, _size, *_index;
   Byte *_data;
   NO_COPY_CONSTRUCTOR(StrLibrary);
};
/******************************************************************************/
// MAIN
/******************************************************************************/
inline Int Elms(C Str &str) {return str.length();}
/******************************************************************************/
