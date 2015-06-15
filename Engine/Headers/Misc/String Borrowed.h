/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct BStr // string which uses text memory allocated externally, and limiting it to custom 'length', 'BStr' has case-sensitive compare operators
{
   Bool          is(     )C {return  _length>0;} // if  string is valid (not empty)
   Int       length(     )C {return  _length  ;} // get string length
   Bool    borrowed(     )C {return !_custom  ;} // if string is borrowed (uses external           text memory), warning: this requires that the external memory is accessible during the lifetime of the string object
   Bool      custom(     )C {return  _custom  ;} // if string is custom   (uses manually allocated text memory)
  CChar* operator()(     )C {return  _d       ;} // warning: for borrowed strings returned pointer may not be null-terminated
   Char  operator[](Int i)C {return InRange(i, T) ? _d[        i] : '\0';} // get i-th character
   Char        last(     )C {return _length       ? _d[_length-1] : '\0';} // get last character

   Str  asStr(      )C; // return as string
 C Str& asStr(Str &s)C; // return as string by copying self to 's' string and returning it

   BStr& set        (C BStr &s               ); // set as exact copy of 's' string
   BStr& setCustom  (C Str  &s               ); // manually allocate new memory for text, and set it from 's' string
   BStr& setBorrowed(CChar  *t, Int length=-1); // do not   allocate new memory for text, instead use directly 't' text memory of custom 'length' (-1=auto-detect the actual 't' text length), warning: if 't' text memory becomes changed after calling this method, then this string will also be changed

   BStr& clear (       ); // clear  string to NULL so it's empty
   BStr& extend(Int l=1); // extend string length by 'l' to use more characters from the borrowed text (for example if the string was set as borrowed from text "abcd" with length=2 then it's equal to "ab", after extending it with "l=1" it's now equal to "abc") warning: please take caution not to extend the string longer than the original text

   Bool operator==(CChar   c)C; // if the string is equal to 'c' character (case-sensitive)
   Bool operator==(CChar8  c)C; // if the string is equal to 'c' character (case-sensitive)
   Bool operator==(CChar  *t)C; // if the string is equal to 't' text      (case-sensitive)
   Bool operator==(CChar8 *t)C; // if the string is equal to 't' text      (case-sensitive)
   Bool operator==(C Str  &s)C; // if the string is equal to 's' string    (case-sensitive)
   Bool operator==(C Str8 &s)C; // if the string is equal to 's' string    (case-sensitive)
   Bool operator==(C BStr &s)C; // if the string is equal to 's' string    (case-sensitive)

   Bool operator!=(CChar   c)C {return !(T==c);} // if the string is not equal to 'c' character (case-sensitive)
   Bool operator!=(CChar8  c)C {return !(T==c);} // if the string is not equal to 'c' character (case-sensitive)
   Bool operator!=(CChar  *t)C {return !(T==t);} // if the string is not equal to 't' text      (case-sensitive)
   Bool operator!=(CChar8 *t)C {return !(T==t);} // if the string is not equal to 't' text      (case-sensitive)
   Bool operator!=(C Str  &s)C {return !(T==s);} // if the string is not equal to 's' string    (case-sensitive)
   Bool operator!=(C Str8 &s)C {return !(T==s);} // if the string is not equal to 's' string    (case-sensitive)
   Bool operator!=(C BStr &s)C {return !(T==s);} // if the string is not equal to 's' string    (case-sensitive)

   BStr& operator=(C BStr &s); // set as exact copy of 's' string

   BStr&   del() {return clear();}
  ~BStr() {del();}
   BStr() {_custom=false; _d=NULL; _length=0;}
   BStr(C BStr &s); // initialize as exact copy of 's' string

private:
   Bool   _custom;
   CChar *_d;
   Int    _length;
};
inline Int Elms(C BStr &s) {return s.length();}
/******************************************************************************/
