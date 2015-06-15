/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
// DEFINITIONS
/******************************************************************************/
#define C     const
#define T     (*this)
#define super __super
#define NULL  0
/******************************************************************************/
// TEMPLATE MACROS
/******************************************************************************/
#define T1(a      )   template<typename a                        > // 1 type  template
#define T2(a, b   )   template<typename a, typename b            > // 2 types template
#define T3(a, b, c)   template<typename a, typename b, typename c> // 3 types template
/******************************************************************************/
// HELPER MACROS
/******************************************************************************/
#define SIZE                                     sizeof               // get raw size of C++ element in bytes
#define MEMBER(     Class, member)         (((Class*)NULL)-> member)  // NULL based Class::member, this macro is used to obtain member information by many other macros/functions
#define OFFSET(     Class, member)   UIntPtr(&MEMBER(Class,  member)) // get offset   of member in class
#define MEMBER_SIZE(Class, member)      SIZE( MEMBER(Class,  member)) // get size     of member in class
#define MEMBER_ELMS(Class, member)      Elms( MEMBER(Class,  member)) // get elements of member in class
#define  CAST(      Class, object)      dynamic_cast<Class*>(object)  // perform a dynamic cast of 'object' to 'Class' class
#define SCAST(      Class, object)       static_cast<Class&>(object)  // perform a  static cast of 'object' to 'Class' class
#define ELMS(       Array        )       (SIZE(Array)/SIZE(Array[0])) // get number of elements in array (this is the compile-time version, use 'Elms' instead of 'ELMS' whenever possible)

T1(TYPE) TYPE& ConstCast(C TYPE &x) {return const_cast<TYPE&>(x);} // remove the const modifier
T1(TYPE) TYPE* ConstCast(C TYPE *x) {return const_cast<TYPE*>(x);} // remove the const modifier
/******************************************************************************/
// ITERATION MACROS
/******************************************************************************/
#define    REP(    n)   for(Int i=(n); --i>= 0 ;    ) //         repeat                : n-1 .. 0
#define    REPD(i, n)   for(Int i=(n); --i>= 0 ;    ) //         repeat with definition: n-1 .. 0
#define   FREP(    n)   for(Int i= 0 ;   i< (n); i++) // forward repeat                :   0 .. n-1
#define   FREPD(i, n)   for(Int i= 0 ;   i< (n); i++) // forward repeat with definition:   0 .. n-1

#define   REPA(    a)   for(Int i=Elms(a); --i>=     0 ;    ) //         repeat all                : Elms(a)-1 .. 0
#define   REPAD(i, a)   for(Int i=Elms(a); --i>=     0 ;    ) //         repeat all with definition: Elms(a)-1 .. 0
#define  FREPA(    a)   for(Int i=     0 ;   i< Elms(a); i++) // forward repeat all                :         0 .. Elms(a)-1
#define  FREPAD(i, a)   for(Int i=     0 ;   i< Elms(a); i++) // forward repeat all with definition:         0 .. Elms(a)-1

#define  REPAO(    a)   for(Int i=Elms(a); --i>=     0 ;    ) (a)[i] //         repeat all                 and operate: Elms(a)-1 .. 0
#define  REPAOD(i, a)   for(Int i=Elms(a); --i>=     0 ;    ) (a)[i] //         repeat all with definition and operate: Elms(a)-1 .. 0
#define FREPAO(    a)   for(Int i=     0 ;   i< Elms(a); i++) (a)[i] // forward repeat all                 and operate:         0 .. Elms(a)-1
#define FREPAOD(i, a)   for(Int i=     0 ;   i< Elms(a); i++) (a)[i] // forward repeat all with definition and operate:         0 .. Elms(a)-1

#define   REPS( i, n)   for((i)=    (n); --(i)>=0; ) // repeat     with i specified:      n -1 .. 0
#define   REPAS(i, a)   for((i)=Elms(a); --(i)>=0; ) // repeat all with i specified: Elms(a)-1 .. 0
/******************************************************************************/
// ASSERTIONS
/******************************************************************************/
#define ASSERT_CONCAT2(a, b) a##b                 // don't use this
#define ASSERT_CONCAT( a, b) ASSERT_CONCAT2(a, b) // don't use this

#define          ASSERT(value       )   typedef int ASSERT_CONCAT(_AssertDummyName, __LINE__)[(value) ? 1 : -1]    // compile time assertion
#define  DYNAMIC_ASSERT(value, error)   {if(!(value))Exit(S+(error)+"\nFile: \""+__FILE__+"\"\nLine: "+__LINE__);} // dynamic      assertion
#ifdef DEBUG
   #define DEBUG_ASSERT(value, error)   DYNAMIC_ASSERT(value, error)                                               // debug        assertion   available only in debug   mode
#else
   #define DEBUG_ASSERT(value, error)   {}                                                                         // debug        assertion unavailable      in release mode
#endif
#define    RANGE_ASSERT(index, elms )   DEBUG_ASSERT(InRange(index, elms), "Element out of range")                 // out of range assertion, asserts that 'index' is in range "0..elms-1"
/******************************************************************************/
// STRUCT DECLARATION
/******************************************************************************/
#define const_mem_addr // custom keyword specifying that the struct/class must be stored in constant memory address, if you see this keyword next to a struct/class declaration you must ensure that when defining objects of that struct/class you will store them in constant memory address (this can be either global namespace or inside 'Memx' 'Meml' containers)

#define STRUCT(        Extended, Base)   struct Extended :         Base { PLATFORM(, typedef Base super;) // macro for declaring an 'Extended' class from 'Base' version, and declaring 'super' keyword at the same time (this is needed for non Windows platforms which don't declare 'super' automatically)
#define STRUCT_PRIVATE(Extended, Base)   struct Extended : private Base { PLATFORM(, typedef Base super;) // macro for declaring an 'Extended' class from 'Base' version, and declaring 'super' keyword at the same time (this is needed for non Windows platforms which don't declare 'super' automatically)

#define UNION(    x)   PLATFORM(union {x}; , x) //                                  uses union     on Windows Platform, and no union     for non-Windows platforms
#define UNION_ELM(x)   PLATFORM(struct{x}; , x) // encapsulates element into a non-named structure on Windows Platform, and no structure for non-Windows platforms

#define NO_COPY_CONSTRUCTOR(Class)             \
    T1(UNUSED)   void operator=(C Class &src); \
    T1(UNUSED)            Class(C Class &src); // when declared inside a class this macro disables the use of copy constructors
/******************************************************************************/
