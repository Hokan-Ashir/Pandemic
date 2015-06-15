/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Memp' to operate on any kind of memory container.

   'Memp' is a pointer to one of all supported memory container types:
      'Mems', 'Memc', 'Memt', 'Memb', 'Memx', 'Meml' or regular continuous memory.

   'Memp' allows to write one function which can operate on all memory container types.

      For example, instead of writing multiple functions which accept different containers:
         Int Sum(C Memc<Int> &values) {Int sum=0; REPA(values)sum+=values[i]; return sum;}
         Int Sum(C Memb<Int> &values) {Int sum=0; REPA(values)sum+=values[i]; return sum;}
         ..

      You can write just one function:
         Int Sum(C Memp<Int> &values) {Int sum=0; REPA(values)sum+=values[i]; return sum;}

         This function will accept all memory container types, so you can do the following:
            Memc<Int> memc_values; Sum(memc_values);
            Memb<Int> memb_values; Sum(memb_values);
            ..

/******************************************************************************/
template<typename TYPE, Int Memt_size> struct Memp // Memory Container Pointer, 'Memt_size'=size of the 'Memt' helper stack memory
{
   // manage
   Memp& clear(); // remove all elements
   Memp& del  (); // remove all elements and free helper memory

   // get / set
   Int  elms    ()C; // number of elements
   UInt elmSize ()C; // size   of element
   UInt memUsage()C; // memory usage

   TYPE* data      (     ) ; // get    pointer to the start of the elements
 C TYPE* data      (     )C; // get    pointer to the start of the elements
   TYPE* addr      (Int i) ; // get    i-th  element address, NULL is returned if index is out of range
 C TYPE* addr      (Int i)C; // get    i-th  element address, NULL is returned if index is out of range
   TYPE& operator[](Int i) ; // get    i-th  element, accessing element out of range is an invalid operation and may cause undefined behavior
 C TYPE& operator[](Int i)C; // get    i-th  element, accessing element out of range is an invalid operation and may cause undefined behavior
   TYPE& operator()(Int i) ; // get    i-th  element, accessing element out of range will cause creation of all elements before it, memory of those elements will be first zeroed before calling their constructor
   TYPE& first     (     ) ; // get    first element
 C TYPE& first     (     )C; // get    first element
   TYPE& last      (     ) ; // get    last  element
 C TYPE& last      (     )C; // get    last  element
   TYPE& New       (     ) ; // create new   element at the  end                                                                              , this method changes the memory address of all elements
   TYPE& NewAt     (Int i) ; // create new   element at i-th position, all old elements starting from i-th position will be moved to the right, this method changes the memory address of all elements

   Int  index   (C TYPE *elm)C; // get index of element in container, -1 on fail      , testing is done by comparing elements memory address only
   Bool contains(C TYPE *elm)C; // check if memory container actually contains element, testing is done by comparing elements memory address only

   operator  Bool()C; // if points to something (not NULL)
   Bool resizable()C; // if supports adding/removing elements

   // remove
   Memp& removeLast(                                  ); // remove last element                                                                                                                                                                        , this method does not change the memory address of any of the remaining elements
   Memp& remove    (  Int   i  , Bool keep_order=false); // remove i-th element                        , if 'keep_order'=false then moves the last element to i-th, if 'keep_order'=true then moves all elements after i-th to the left (keeping order), this method may      change the memory address of some elements
   Memp& removeData(C TYPE *elm, Bool keep_order=false); // remove element by giving its memory address, if 'keep_order'=false then moves the last element to i-th, if 'keep_order'=true then moves all elements after i-th to the left (keeping order), this method may      change the memory address of some elements

   Memp& setNum    (Int num); // set number of elements to 'num'                                                                              , this method changes the memory address of all elements
   Memp& setNumZero(Int num); // set number of elements to 'num', memory of new elements will be first zeroed before calling their constructor, this method changes the memory address of all elements
   Int   addNum    (Int num); // add 'num' elements, return index of first added element                                                      , this method changes the memory address of all elements

   // values
   T1(VALUE) Int   find   (C VALUE &value                       )C {REPA(T)if(T[i]==value)return i; return -1;                                                  } // check if 'value' is present in container and return its index, -1 if not found
   T1(VALUE) Bool  has    (C VALUE &value                       )C {return find(value)!=-1;                                                                     } // check if 'value' is present in container
   T1(VALUE) Memp& add    (C VALUE &value                       )  {New()=value; return T;                                                                      } // add      'value' to container                                                                                       , this method changes the memory address of all elements
   T1(VALUE) Bool  include(C VALUE &value                       )  {if(!has(value)){add(value); return true;} return false;                                     } // include  'value' if it's not already present in container, returns true if value wasn't present and has been added  , this method changes the memory address of all elements
   T1(VALUE) Bool  exclude(C VALUE &value, Bool keep_order=false)  {Int i=find(value); if(i!=-1){remove(i, keep_order); return true ;}             return false;} // exclude  'value' if present  in container                , returns true if value was    present and has been removed, this method changes the memory address of all elements
   T1(VALUE) Bool  toggle (C VALUE &value, Bool keep_order=false)  {Int i=find(value); if(i!=-1){remove(i, keep_order); return false;} add(value); return true ;} // toggle   'value'    presence in container                , returns true if value is now present in container        , this method changes the memory address of all elements

   T1(VALUE)   Bool  binarySearch (C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C; // search sorted container for presence of 'value' and return if it was found in the container, 'index'=if the function returned true then this index points to the location where the 'value' is located in the container, if the function returned false then it means that 'value' was not found in the container however the 'index' points to the place where it should be added in the container while preserving sorted data
   T1(VALUE)   Bool  binaryHas    (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))C {Int i; return binarySearch(value, i, compare);                                                              } // check if 'value' (using binary search) is present in container
   T1(VALUE)   TYPE* binaryFind   (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; return binarySearch(value, i, compare) ? &T[i] : NULL;                                               } // check if 'value' (using binary search) is present in container and return it, NULL on fail
   T1(VALUE) C TYPE* binaryFind   (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))C {return ConstCast(T).binaryFind(value, compare);                                                             } // check if 'value' (using binary search) is present in container and return it, NULL on fail
   T1(VALUE)   Memp& binaryAdd    (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i;        binarySearch(value, i, compare); NewAt (i)=value;                                return     T;} // add      'value' (using binary search)                                                                                                    , this method changes the memory address of all elements
   T1(VALUE)   Bool  binaryInclude(C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; if(   !binarySearch(value, i, compare)){NewAt (i)=value; return true;}                  return false;} // include  'value' (using binary search) if it's not already present in container, returns true if value wasn't present and has been added  , this method changes the memory address of all elements
   T1(VALUE)   Bool  binaryExclude(C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; if(    binarySearch(value, i, compare)){remove(i, true); return true;}                  return false;} // exclude  'value' (using binary search) if present  in container                , returns true if value was    present and has been removed, this method changes the memory address of all elements
   T1(VALUE)   Bool  binaryToggle (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; if(   !binarySearch(value, i, compare)){NewAt (i)=value; return true;} remove(i, true); return false;} // toggle   'value' (using binary search)    presence in container                , returns true if value is now present in container        , this method changes the memory address of all elements

   // order
   Memp&         sort(Int compare(C TYPE &a, C TYPE &b)); // sort elements with custom comparing function
   Memp& reverseOrder(                                 ); // reverse order of elements
   Memp&    swapOrder(Int i, Int j                     ); // swap order of 'i' and 'j' valid elements

   // misc
                      Memp& operator=(C Mems<TYPE      > &src); // copy elements using assignment operator
                      Memp& operator=(C Memc<TYPE      > &src); // copy elements using assignment operator
   template<Int size> Memp& operator=(C Memt<TYPE, size> &src); // copy elements using assignment operator
                      Memp& operator=(C Memb<TYPE      > &src); // copy elements using assignment operator
                      Memp& operator=(C Memx<TYPE      > &src); // copy elements using assignment operator
                      Memp& operator=(C Meml<TYPE      > &src); // copy elements using assignment operator
   template<Int size> Memp& operator=(C Memp<TYPE, size> &src); // copy elements using assignment operator
                      Memp& operator=(C Memp<TYPE      > &src); // copy elements using assignment operator (this must be specified even though func above should do the same, because without it compiler will try to use constructor instead, which just sets pointers instead of copying elements)

   // io
   void save(File &f);   void save(File &f)C; // save elements with their own 'save' method, this method first saves number of current elements, and then for each element calls its 'save' method
   Bool load(File &f);                        // load elements with their own 'load' method, this method removes all currently stored  elements, and then sequentially     calls     'load' method for each element stored in the file, false on fail

   void saveRaw(File &f)C; // save raw memory of elements (number of elements + elements raw memory)
   Bool loadRaw(File &f) ; // load raw memory of elements (number of elements + elements raw memory)

   // initialize 'Memp' to point to source
                      Memp& point(     int=NULL                        ); // this simulates initializing from NULL
                      Memp& point(     TYPE             &src           );
                      Memp& point(     TYPE             *src, Int elms );
   template<Int size> Memp& point(     TYPE            (&src)    [size]);
                      Memp& point(Mems<TYPE           > &src           );
                      Memp& point(Memc<TYPE           > &src           );
                      Memp& point(Memt<TYPE, Memt_size> &src           );
                      Memp& point(Memb<TYPE           > &src           );
                      Memp& point(Memx<TYPE           > &src           );
                      Memp& point(Meml<TYPE           > &src           );
                   #ifdef WINDOWS // only Microsoft compiler can handle following line which prevents initializing from 'const Memp'
                      Memp& point(Memp<TYPE, Memt_size> &src           );
                   #endif

                      Memp(     int=NULL                        ) {point(NULL     );} // this simulates initializing from NULL
                      Memp(     TYPE             &src           ) {point(src      );}
                      Memp(     TYPE             *src, Int elms ) {point(src, elms);}
   template<Int size> Memp(     TYPE            (&src)    [size]) {point(src      );}
                      Memp(Mems<TYPE           > &src           ) {point(src      );}
                      Memp(Memc<TYPE           > &src           ) {point(src      );}
                      Memp(Memt<TYPE, Memt_size> &src           ) {point(src      );}
                      Memp(Memb<TYPE           > &src           ) {point(src      );}
                      Memp(Memx<TYPE           > &src           ) {point(src      );}
                      Memp(Meml<TYPE           > &src           ) {point(src      );}
                   #ifdef WINDOWS // only Microsoft compiler can handle following line which prevents initializing from 'const Memp'
                      Memp(Memp<TYPE, Memt_size> &src           ) {point(src      );}
                   #endif

   enum MODE
   {
      PTR ,
      MEMS,
      MEMC,
      MEMT,
      MEMB,
      MEMX,
      MEML,
   };

   MODE mode()C {return _mode;} // get type of container from which 'Memp' was created

   Mems<TYPE>* mems() {return (_mode==MEMS) ? _mems : NULL;}
   Memc<TYPE>* memc() {return (_mode==MEMC) ? _memc : NULL;}
   Memb<TYPE>* memb() {return (_mode==MEMB) ? _memb : NULL;}
   Memx<TYPE>* memx() {return (_mode==MEMX) ? _memx : NULL;}

private:
   union
   {
      TYPE                  *_ptr ;
      Mems<TYPE           > *_mems;
      Memc<TYPE           > *_memc;
      Memt<TYPE, Memt_size> *_memt;
      Memb<TYPE           > *_memb;
      Memx<TYPE           > *_memx;
      Meml<TYPE           > *_meml;
   };
   MODE _mode;
   Int  _elms;
   Memp& operator=(int  );
   Memp& operator=(TYPE&);

   friend struct Mems<TYPE>;
   friend struct Memc<TYPE>;
   friend struct Memt<TYPE, Memt_size>;
   friend struct Memb<TYPE>;
   friend struct Memx<TYPE>;
   friend struct Meml<TYPE>;
};
/******************************************************************************/
template<typename TYPE, Int size>   inline Int Elms(C Memp<TYPE, size> &memp) {return memp.elms();}
/******************************************************************************/
