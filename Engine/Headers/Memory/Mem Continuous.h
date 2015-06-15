/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Memc' for continuous memory based dynamic array container.

   'Memc' stores elements in continuous memory, for example:
      [ABCDE...]

   'Memc' container reserves some extra memory for adding new elements.
      If creating a new element when there is no extra memory available,
      the container will reallocate the whole array into a new bigger one,
      thus changing the address of all elements.

/******************************************************************************/
T1(const_mem_addr TYPE) struct Memc : _Memc // Continuous Memory Based Container
{
   // manage
   Memc& clear(); // remove all elements
   Memc& del  (); // remove all elements and free helper memory

   // get / set
   Int  elms    ()C; // number of elements
   UInt elmSize ()C; // size   of element
   UInt memUsage()C; // memory usage

   TYPE* data      (     ) ; // get    pointer to the start of the elements
 C TYPE* data      (     )C; // get    pointer to the start of the elements
   TYPE* addr      (Int i) ; // get    i-th  element address, NULL is returned if index is out of range
 C TYPE* addr      (Int i)C; // get    i-th  element address, NULL is returned if index is out of range
   TYPE* addrFirst (     ) ; // get    first element address, NULL is returned if element doesn't exist
 C TYPE* addrFirst (     )C; // get    first element address, NULL is returned if element doesn't exist
   TYPE* addrLast  (     ) ; // get    last  element address, NULL is returned if element doesn't exist
 C TYPE* addrLast  (     )C; // get    last  element address, NULL is returned if element doesn't exist
   TYPE& operator[](Int i) ; // get    i-th  element, accessing element out of range is an invalid operation and may cause undefined behavior
 C TYPE& operator[](Int i)C; // get    i-th  element, accessing element out of range is an invalid operation and may cause undefined behavior
   TYPE& operator()(Int i) ; // get    i-th  element, accessing element out of range will cause creation of all elements before it, memory of those elements will be first zeroed before calling their constructor
   TYPE& first     (     ) ; // get    first element
 C TYPE& first     (     )C; // get    first element
   TYPE& last      (     ) ; // get    last  element
 C TYPE& last      (     )C; // get    last  element
   TYPE  popFirst  (     ) ; // get    first element and remove it from the container
   TYPE  pop       (     ) ; // get    last  element and remove it from the container
   TYPE& New       (     ) ; // create new   element at the  end                                                                              , this method may change the memory address of all elements
   TYPE& NewAt     (Int i) ; // create new   element at i-th position, all old elements starting from i-th position will be moved to the right, this method may change the memory address of all elements

   Int  index   (C TYPE *elm)C; // get index of element in container, -1 on fail      , testing is done by comparing elements memory address only
   Bool contains(C TYPE *elm)C; // check if memory container actually contains element, testing is done by comparing elements memory address only

   // remove
   Memc& removeLast(                                  ); // remove last element                                                                                                                                                                        , this method does not change the memory address of any of the remaining elements
   Memc& remove    (  Int   i  , Bool keep_order=false); // remove i-th element                        , if 'keep_order'=false then moves the last element to i-th, if 'keep_order'=true then moves all elements after i-th to the left (keeping order), this method may      change the memory address of some elements
   Memc& removeData(C TYPE *elm, Bool keep_order=false); // remove element by giving its memory address, if 'keep_order'=false then moves the last element to i-th, if 'keep_order'=true then moves all elements after i-th to the left (keeping order), this method may      change the memory address of some elements

   Memc& setNum    (Int num); // set number of elements to 'num'                                                                              , this method may change the memory address of all elements
   Memc& setNumZero(Int num); // set number of elements to 'num', memory of new elements will be first zeroed before calling their constructor, this method may change the memory address of all elements
   Int   addNum    (Int num); // add 'num' elements, return index of first added element                                                      , this method may change the memory address of all elements

   // values
   T1(VALUE) Int   find   (C VALUE &value                       )C {REPA(T)if(T[i]==value)return i; return -1;                                                  } // check if 'value' is present in container and return its index, -1 if not found
   T1(VALUE) Bool  has    (C VALUE &value                       )C {return find(value)!=-1;                                                                     } // check if 'value' is present in container
   T1(VALUE) Memc& add    (C VALUE &value                       )  {New()=value; return T;                                                                      } // add      'value' to container                                                                                       , this method may change the memory address of all elements
   T1(VALUE) Bool  include(C VALUE &value                       )  {if(!has(value)){add(value); return true;} return false;                                     } // include  'value' if it's not already present in container, returns true if value wasn't present and has been added  , this method may change the memory address of all elements
   T1(VALUE) Bool  exclude(C VALUE &value, Bool keep_order=false)  {Int i=find(value); if(i!=-1){remove(i, keep_order); return true ;}             return false;} // exclude  'value' if present  in container                , returns true if value was    present and has been removed, this method may change the memory address of all elements
   T1(VALUE) Bool  toggle (C VALUE &value, Bool keep_order=false)  {Int i=find(value); if(i!=-1){remove(i, keep_order); return false;} add(value); return true ;} // toggle   'value'    presence in container                , returns true if value is now present in container        , this method may change the memory address of all elements

   T1(VALUE)   Bool  binarySearch (C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C; // search sorted container for presence of 'value' and return if it was found in the container, 'index'=if the function returned true then this index points to the location where the 'value' is located in the container, if the function returned false then it means that 'value' was not found in the container however the 'index' points to the place where it should be added in the container while preserving sorted data
   T1(VALUE)   Bool  binaryHas    (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))C {Int i; return binarySearch(value, i, compare);                                                              } // check if 'value' (using binary search) is present in container
   T1(VALUE)   TYPE* binaryFind   (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; return binarySearch(value, i, compare) ? &T[i] : NULL;                                               } // check if 'value' (using binary search) is present in container and return it, NULL on fail
   T1(VALUE) C TYPE* binaryFind   (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))C {return ConstCast(T).binaryFind(value, compare);                                                             } // check if 'value' (using binary search) is present in container and return it, NULL on fail
   T1(VALUE)   Memc& binaryAdd    (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i;        binarySearch(value, i, compare); NewAt (i)=value;                                return     T;} // add      'value' (using binary search)                                                                                                    , this method may change the memory address of all elements
   T1(VALUE)   Bool  binaryInclude(C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; if(   !binarySearch(value, i, compare)){NewAt (i)=value; return true;}                  return false;} // include  'value' (using binary search) if it's not already present in container, returns true if value wasn't present and has been added  , this method may change the memory address of all elements
   T1(VALUE)   Bool  binaryExclude(C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; if(    binarySearch(value, i, compare)){remove(i, true); return true;}                  return false;} // exclude  'value' (using binary search) if present  in container                , returns true if value was    present and has been removed, this method may change the memory address of all elements
   T1(VALUE)   Bool  binaryToggle (C VALUE &value,             Int compare(C TYPE &a, C VALUE &b))  {Int i; if(   !binarySearch(value, i, compare)){NewAt (i)=value; return true;} remove(i, true); return false;} // toggle   'value' (using binary search)    presence in container                , returns true if value is now present in container        , this method may change the memory address of all elements

   // order
   Memc&           sort(Int compare(C TYPE &a, C TYPE &b)); // sort elements with custom comparing function, this method may change the memory address of all elements
   Memc&   reverseOrder(                                 ); // reverse   order of elements, this method     changes the memory address of all elements
   Memc& randomizeOrder(                                 ); // randomize order of elements, this method may change  the memory address of all elements
   Memc&    rotateOrder(Int offset                       ); // rotate    order of elements, changes the order of elements so "new_index=old_index+offset", 'offset'=offset of moving the original indexes into target indexes (-Inf..Inf)
   Memc&      swapOrder(Int i, Int j                     ); // swap      order of 'i' and 'j' elements
   Memc&      moveElm  (Int elm, Int new_index           ); // move 'elm' element to new position located at 'new_index'

   // misc
                      Memc& operator=(C Mems<TYPE      > &src); // copy elements using assignment operator
                      Memc& operator=(C Memc<TYPE      > &src); // copy elements using assignment operator
   template<Int size> Memc& operator=(C Memt<TYPE, size> &src); // copy elements using assignment operator
                      Memc& operator=(C Memb<TYPE      > &src); // copy elements using assignment operator
                      Memc& operator=(C Memx<TYPE      > &src); // copy elements using assignment operator
                      Memc& operator=(C Meml<TYPE      > &src); // copy elements using assignment operator
   template<Int size> Memc& operator=(C Memp<TYPE, size> &src); // copy elements using assignment operator
#ifdef HAS_MOVE_CONSTRUCTOR
                      Memc& operator=(  Memc<TYPE      >&&src); // copy elements using assignment operator
#endif

   T1(EXTENDED) Memc& replaceClass(); // replace the type of class stored in the container, all elements are automatically removed before changing the type of the class, the new type must be extended from the base 'TYPE' (if you're receiving a compilation error pointing to this method this means that the new class isn't extended from the base class)

   T1(BASE) operator   Memc<BASE>&() ; // casting to container of 'BASE' elements, 'TYPE' must be extended from BASE
   T1(BASE) operator C Memc<BASE>&()C; // casting to container of 'BASE' elements, 'TYPE' must be extended from BASE

   // io
   void save(File &f);   void save(File &f)C; // save elements with their own 'save' method, this method first saves number of current elements, and then for each element calls its 'save' method
   Bool load(File &f);                        // load elements with their own 'load' method, this method removes all currently stored  elements, and then sequentially     calls     'load' method for each element stored in the file, false on fail

   T1(USER) void save(File &f, C USER &user)C; // save elements with their own 'save' method and 'user' parameter, this method first saves number of current elements, and then for each element calls its 'save' method
   T1(USER) Bool load(File &f, C USER &user) ; // load elements with their own 'load' method and 'user' parameter, this method removes all currently stored  elements, and then sequentially     calls     'load' method for each element stored in the file, false on fail

   void saveRaw(File &f)C; // save raw memory of elements (number of elements + elements raw memory)
   Bool loadRaw(File &f) ; // load raw memory of elements (number of elements + elements raw memory)

   Memc(           );
   Memc(C Memc &src);
#ifdef HAS_MOVE_CONSTRUCTOR
   Memc(  Memc&&src);
#endif
};
/******************************************************************************/
T1(TYPE) struct MemcAbstract : _Memc // Continuous Memory Based Container which allows storage of abstract classes, 'replaceClass' should be called before creating new elements in it
{
   // manage
   MemcAbstract& clear(); // remove all elements
   MemcAbstract& del  (); // remove all elements and free helper memory

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
   TYPE& New       (     ) ; // create new   element at the  end                                                                              , this method does not change the memory address of any of the elements
   TYPE& NewAt     (Int i) ; // create new   element at i-th position, all old elements starting from i-th position will be moved to the right, this method may      change the memory address of all        elements

   Int  index   (C TYPE *elm)C; // get index of element in container, -1 on fail      , testing is done by comparing elements memory address only
   Bool contains(C TYPE *elm)C; // check if memory container actually contains element, testing is done by comparing elements memory address only

   // remove
   MemcAbstract& removeLast(                                  ); // remove last element                                                                                                                                                                        , this method does not change the memory address of any of the remaining elements
   MemcAbstract& remove    (  Int   i  , Bool keep_order=false); // remove i-th element                        , if 'keep_order'=false then moves the last element to i-th, if 'keep_order'=true then moves all elements after i-th to the left (keeping order), this method may      change the memory address of some elements
   MemcAbstract& removeData(C TYPE *elm, Bool keep_order=false); // remove element by giving its memory address, if 'keep_order'=false then moves the last element to i-th, if 'keep_order'=true then moves all elements after i-th to the left (keeping order), this method may      change the memory address of some elements

   MemcAbstract& setNum    (Int num); // set number of elements to 'num'                                                                              , this method does not change the memory address of any of the elements
   MemcAbstract& setNumZero(Int num); // set number of elements to 'num', memory of new elements will be first zeroed before calling their constructor, this method does not change the memory address of any of the elements
   Int           addNum    (Int num); // add 'num' elements, return index of first added element                                                      , this method does not change the memory address of any of the elements

   T1(EXTENDED) MemcAbstract& replaceClass(); // replace the type of class stored in the container, all elements are automatically removed before changing the type of the class, the new type must be extended from the base 'TYPE' (if you're receiving a compilation error pointing to this method this means that the new class isn't extended from the base class)

   T1(BASE) operator   Memc<BASE>&() ; // casting to container of 'BASE' elements, 'TYPE' must be extended from BASE
   T1(BASE) operator C Memc<BASE>&()C; // casting to container of 'BASE' elements, 'TYPE' must be extended from BASE

   MemcAbstract();

private:
   NO_COPY_CONSTRUCTOR(MemcAbstract);
};
/******************************************************************************/
inline Int Elms(C _Memc &memc) {return memc.elms();}
/******************************************************************************/
