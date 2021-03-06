/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Sort' functions to sort custom data.

   Use 'BinarySearch' functions to perform binary search on custom data.

/******************************************************************************/
// Basic Compare Functions
inline Int Compare(C Byte  &a, C Byte  &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C Int   &a, C Int   &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C UInt  &a, C UInt  &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C Long  &a, C Long  &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C ULong &a, C ULong &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C Flt   &a, C Flt   &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C Dbl   &a, C Dbl   &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1
inline Int Compare(C Ptr   &a, C Ptr   &b) {if(a<b)return -1; if(a>b)return +1; return 0;} // compare 'a' 'b' values and return -1, 0, +1

// Sort Data
         void Sort(Int  *data, Int elms                                   ); // sort Int    array
         void Sort(Flt  *data, Int elms                                   ); // sort Flt    array
         void Sort(Dbl  *data, Int elms                                   ); // sort Dbl    array
T1(TYPE) void Sort(TYPE *data, Int elms, Int compare(C TYPE &a, C TYPE &b)); // sort custom array using custom comparing function

// Binary Search, search sorted 'data' array for presence of 'value' and return if it was found in the array, 'index'=if the function returned true then this index points to the location where the 'value' is located in the array, if the function returned false then it means that 'value' was not found in the array however the 'index' points to the place where it should be added in the array while preserving sorted data
T2(DATA, VALUE)   Bool  BinarySearch(C DATA *data, Int elms, C VALUE &value, Int &index, Int compare(C DATA &a, C VALUE &b));
T2(DATA, VALUE)   Bool  BinaryHas   (C DATA *data, Int elms, C VALUE &value,             Int compare(C DATA &a, C VALUE &b)) {Int i; return BinarySearch(data, elms, value, i, compare);                  } // check if 'value' is present in array
T2(DATA, VALUE)   DATA* BinaryFind  (  DATA *data, Int elms, C VALUE &value,             Int compare(C DATA &a, C VALUE &b)) {Int i; return BinarySearch(data, elms, value, i, compare) ? &data[i] : NULL;} // check if 'value' is present in array and return it, NULL on fail
/******************************************************************************/
