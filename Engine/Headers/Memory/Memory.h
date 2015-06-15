/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'MemStats' to access information about system memory usage.

   Use 'Secure' to handle data encryption.

   Use memory functions to handle:
      -Allocate
      -Free
      -Reallocate
      -Zero
      -Set
      -Copy
      -Swap
      -Compare
      -New
      -Delete

/******************************************************************************/
// MEMORY STATUS
/******************************************************************************/
struct MemStats // System Memory Status
{
   Byte usage                 ; // percentage memory usage, 0..100, 0=no memory usage, 100=full memory usage
   Long avail_phys, total_phys, // available and total physical memory (in bytes)
        avail_page, total_page, // available and total paged    memory (in bytes)
        avail_virt, total_virt; // available and total virtual  memory (in bytes)

   Bool get(); // get values from system information, false on fail
};
/******************************************************************************/
// SECURE MEMORY
/******************************************************************************/
struct Secure // De/Encrypting Memory
{
   Byte key[32]; // custom securing key

   virtual void randomize(); // randomize keys

   virtual void   secure(Ptr dest, CPtr src, Int size, Int offset); // encrypt data, when writing custom   'secure' methods, they should handle the case when "src==NULL" but "size>0", in this case 'src' should be treated as zeroed memory of 'size' length
   virtual void unsecure(Ptr dest, CPtr src, Int size, Int offset); // decrypt data, when writing custom 'unsecure' methods, they should handle the case when "src==NULL" but "size>0", in this case 'src' should be treated as zeroed memory of 'size' length

   Secure();
   Secure(Byte k00, Byte k01, Byte k02, Byte k03, Byte k04, Byte k05, Byte k06, Byte k07, Byte k08, Byte k09,
          Byte k10, Byte k11, Byte k12, Byte k13, Byte k14, Byte k15, Byte k16, Byte k17, Byte k18, Byte k19,
          Byte k20, Byte k21, Byte k22, Byte k23, Byte k24, Byte k25, Byte k26, Byte k27, Byte k28, Byte k29,
          Byte k30, Byte k31);
}extern
   SecureDefault;
/******************************************************************************/
// ALLOCATE RAW MEMORY
/******************************************************************************/
         Ptr    Alloc    (             Int size  );                                                    // allocate          memory                   , Exit on fail, !! combine only with 'Free' !!, sample usage: "           Alloc          (100);" will allocate raw memory of 100        bytes
         Ptr    AllocZero(             Int size  );                                                    // allocate and zero memory                   , Exit on fail, !! combine only with 'Free' !!, sample usage: "           AllocZero      (100);" will allocate raw memory of 100 zeroed bytes
T1(TYPE) TYPE*  Alloc    (             Int elms=1) {return (TYPE*)Alloc          (elms*SIZE(TYPE)  );} // allocate          'elms' elements of 'type', Exit on fail, !! combine only with 'Free' !!, sample usage: "           Alloc    <Int> (100);" will allocate raw memory of 100        Int elements
T1(TYPE) TYPE*  AllocZero(             Int elms=1) {return (TYPE*)AllocZero      (elms*SIZE(TYPE)  );} // allocate and zero 'elms' elements of 'type', Exit on fail, !! combine only with 'Free' !!, sample usage: "           AllocZero<Int> (100);" will allocate raw memory of 100 zeroed Int elements
T1(TYPE) TYPE*& Alloc    (TYPE* &data, Int elms=1) {         data=Alloc    <TYPE>(elms); return data;} // allocate          memory for 'elms' TYPE's , Exit on fail, !! combine only with 'Free' !!, sample usage: "Int *data; Alloc    (data, 100);" will allocate raw memory of 100        Int elements
T1(TYPE) TYPE*& AllocZero(TYPE* &data, Int elms=1) {         data=AllocZero<TYPE>(elms); return data;} // allocate and zero memory for 'elms' TYPE's , Exit on fail, !! combine only with 'Free' !!, sample usage: "Int *data; AllocZero(data, 100);" will allocate raw memory of 100 zeroed Int elements
/******************************************************************************/
// FREE RAW MEMORY
/******************************************************************************/
         void   Free(Ptr   &data);                                   // free memory and set pointer to NULL !! combine only with 'Alloc' !!
T1(TYPE) TYPE*& Free(TYPE* &data) {Free(*(Ptr*)&data); return data;} // free memory and set pointer to NULL !! combine only with 'Alloc' !!
/******************************************************************************/
// REALLOCATE MEMORY
/******************************************************************************/
T1(TYPE) void Realloc    (TYPE* &data, Int elms_new, Int elms_old); // reallocate memory without losing data with 'elms_new' and 'elms_old'                       , Exit on fail !! combine only with 'Alloc' !!
T1(TYPE) void ReallocZero(TYPE* &data, Int elms_new, Int elms_old); // reallocate memory without losing data with 'elms_new' and 'elms_old', and zero new elements, Exit on fail !! combine only with 'Alloc' !!
/******************************************************************************/
// ZERO MEMORY
/******************************************************************************/
         void  Zero (Ptr   data, Int size);                                            // zero                 memory
T1(TYPE) TYPE& Zero (TYPE &elm           ) {Zero(&elm ,      SIZE(TYPE)); return elm;} // zero        element  memory
T1(TYPE) void  ZeroN(TYPE *data, Int elms) {Zero( data, elms*SIZE(TYPE));            } // zero 'elms' elements memory
/******************************************************************************/
// SET MEMORY
/******************************************************************************/
         void  SetMem (Ptr   data, Byte value, Int size);                                                     // set                 memory to Byte value
T1(TYPE) TYPE& SetMem (TYPE &elm , Byte value          ) {SetMem(&elm , value,      SIZE(TYPE)); return elm;} // set 'elm'           memory to Byte value
T1(TYPE) void  SetMemN(TYPE *data, Byte value, Int elms) {SetMem( data, value, elms*SIZE(TYPE));            } // set 'elms' elements memory to Byte value
/******************************************************************************/
// COPY MEMORY
/******************************************************************************/
         void Copy (Ptr   dest,   CPtr  src, Int size);                                            // copy 'src'  memory  to 'dest', if 'src' is NULL then 'dest' will be set to zeros
T1(TYPE) void Copy (TYPE &dest, C TYPE &src          ) {Copy(&dest, (CPtr)&src,      SIZE(TYPE));} // copy 'src'  element to 'dest'
T1(TYPE) void CopyN(TYPE *dest, C TYPE *src, Int elms) {Copy( dest, (CPtr) src, elms*SIZE(TYPE));} // copy 'elms' elements
/******************************************************************************/
// SWAP MEMORY
/******************************************************************************/
         void Swap(Ptr     a, Ptr     b, Int size);                              // swap memories
  inline void Swap(Char   &a, Char   &b          ) {Char   temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Char8  &a, Char8  &b          ) {Char8  temp=a; a=b; b=temp;} // swap elements
  inline void Swap(SByte  &a, SByte  &b          ) {SByte  temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Short  &a, Short  &b          ) {Short  temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Int    &a, Int    &b          ) {Int    temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Long   &a, Long   &b          ) {Long   temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Byte   &a, Byte   &b          ) {Byte   temp=a; a=b; b=temp;} // swap elements
  inline void Swap(UShort &a, UShort &b          ) {UShort temp=a; a=b; b=temp;} // swap elements
  inline void Swap(UInt   &a, UInt   &b          ) {UInt   temp=a; a=b; b=temp;} // swap elements
  inline void Swap(ULong  &a, ULong  &b          ) {ULong  temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Flt    &a, Flt    &b          ) {Flt    temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Dbl    &a, Dbl    &b          ) {Dbl    temp=a; a=b; b=temp;} // swap elements
  inline void Swap(Ptr    &a, Ptr    &b          ) {Ptr    temp=a; a=b; b=temp;} // swap elements
T1(TYPE) void Swap(TYPE*  &a, TYPE*  &b          ) {TYPE  *temp=a; a=b; b=temp;} // swap elements
T1(TYPE) void Swap(TYPE   &a, TYPE   &b          ) {  Swap(&a, &b, SIZE(TYPE));} // swap elements
/******************************************************************************/
// CHANGE ORDER OF ELEMENTS IN MEMORY
/******************************************************************************/
T1(TYPE) void   ReverseOrder(TYPE *data, Int elms            ); // reverse   order of elements (first<->last)
T1(TYPE) void RandomizeOrder(TYPE *data, Int elms            ); // randomize order of elements
T1(TYPE) void    RotateOrder(TYPE *data, Int elms, Int offset); // rotate    order of elements, changes the order of elements so "new_index=old_index+offset", 'offset'=offset of moving the original indexes into target indexes (-Inf..Inf)
/******************************************************************************/
// COMPARE MEMORY
/******************************************************************************/
         Bool EqualMem(  CPtr  a,   CPtr  b, Int size);                                                   // if equal memories
T1(TYPE) Bool EqualMem(C TYPE &a, C TYPE &b          ) {return EqualMem((CPtr)&a, (CPtr)&b, SIZE(TYPE));} // if equal elements (in memory)
/******************************************************************************/
} // close EE namespace to define following functions in global namespace
/******************************************************************************/
   // OVERRIDE NEW AND DELETE
   /******************************************************************************/
#if defined MAC || defined IOS
   Ptr  operator new   (size_t size)throw(std::bad_alloc); // override default new    to use custom allocation with detection of memory leaks
   void operator delete(Ptr    data)throw(              ); // override default delete to use custom freeing    with detection of memory leaks
#else
   inline Ptr  operator new   (size_t size)        {return EE::Alloc((Int)size);} // override default new    to use custom allocation with detection of memory leaks
   inline void operator delete(Ptr    data)throw() {       EE::Free (     data);} // override default delete to use custom allocation with detection of memory leaks
#endif
/******************************************************************************/
namespace EE // restore EE namespace
{
/******************************************************************************/
// ALLOCATE MEMORY AND CALL CONSTRUCTOR
/******************************************************************************/
T1(TYPE) TYPE*& New(TYPE* &data          ) {data=            new TYPE              ; return data;} // create        object  !! combine only with 'Delete'  or 'delete'   !!
T1(TYPE) TYPE*& New(TYPE* &data, Int elms) {data=((elms>0) ? new TYPE[elms] : NULL); return data;} // create 'elms' objects !! combine only with 'DeleteN' or 'delete[]' !!
/******************************************************************************/
// CALL DESTRUCTOR AND FREE MEMORY
/******************************************************************************/
T1(TYPE) TYPE*& Delete (TYPE* &data) {delete   data; data=NULL; return data;} // delete object  and set pointer to NULL !! combine only with "New(data      )" or 'new'   !!
T1(TYPE) TYPE*& DeleteN(TYPE* &data) {delete[] data; data=NULL; return data;} // delete objects and set pointer to NULL !! combine only with "New(data, elms)" or 'new[]' !!
/******************************************************************************/
Str8 Base64(CPtr data, Int size); // calculate Base64 for given memory
/******************************************************************************/
