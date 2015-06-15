/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Cache' to quickly access custom data by loading it from specified file.
      Once 'Cache' loads a resource, it will keep it in the memory for faster access.
      You can also use 'Cache' to access file name of already loaded element.

   Objects in 'Cache' containers are stored using 'Memx' container,
      which means that the memory address of the elements remains constant as long as the elements exist.

   'Cache' loads the data and stores it forever (as long as the cache lives),
      in order to load the data for as long as it is needed, you must use 'CacheElmPtr'.

   'CacheElmPtr' can be treated like a typical pointer, with the exception that when copied or destroyed,
      it automatically increases/decreses the reference count of an element inside a cache.
      Once the reference count of an element drops to zero, it means that there are no more 'CacheElmPtr'
      pointers referencing the data, and the data is released.

   Engine uses the 'Cache' class to store many types of data, for example:
      'Images'    - cache for images   , with 'ImagePtr'    typedef for the 'CacheElmPtr' template pointer
      'Materials' - cache for materials, with 'MaterialPtr' typedef for the 'CacheElmPtr' template pointer
      'Meshes'    - cache for meshes   , with 'MeshPtr'     typedef for the 'CacheElmPtr' template pointer
      ..

/******************************************************************************/
enum CACHE_MODE // Cache Mode
{
   CACHE_EXIT      , //       load data, Exit  on fail
   CACHE_NULL      , //       load data, NULL  on fail
   CACHE_DUMMY     , //       load data, dummy on fail       (pointer to empty data with correct path, initialized with constructor but without the 'load' method)
   CACHE_ALL_NULL  , // don't load data, always return NULL
   CACHE_ALL_DUMMY , // don't load data, always return dummy (pointer to empty data with correct path, initialized with constructor but without the 'load' method)
   CACHE_DUMMY_NULL, // don't load data,        return dummy (pointer to empty data with correct path, initialized with constructor but without the 'load' method) if a file exists at specified path, if a file does not exist then NULL is returned
};
/******************************************************************************/
// CACHE
/******************************************************************************/
T1(TYPE) struct Cache : _Cache // Cache - container for dynamically loaded data, used for fast accessing data through file name, 'Cache' is multi-threaded safe
{
   struct Elm : _Cache::Elm
   {
      TYPE data;
      Desc desc;
   };

   // manage
   CACHE_MODE mode         (CACHE_MODE mode); // set cache mode, returns previous mode
   Cache&     caseSensitive(Bool  sensitive); // set if cache should use case sensitive paths for accessing resources, default=false

   // get object and store it forever (as long as the Cache lives)
   TYPE* find      (C Str &file, CChar *path=NULL); // find    object by its file name   , don't load if not found, NULL on fail
   TYPE* find      (C UID &id  , CChar *path=NULL); // find    object by its file name id, don't load if not found, NULL on fail
   TYPE* get       (C Str &file, CChar *path=NULL); // get     object by its file name   ,       load if not found, NULL on fail
   TYPE* get       (C UID &id  , CChar *path=NULL); // get     object by its file name id,       load if not found, NULL on fail
   TYPE* operator()(C Str &file, CChar *path=NULL); // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected)
   TYPE* operator()(C UID &id  , CChar *path=NULL); // require object by its file name id,       load if not found, Exit on fail (unless different CACHE_MODE selected)

   // get object file name (this will return pointer to internally stored file name assuming that the object is stored in this Cache)
   CChar* name(C TYPE *data, CChar *path=NULL)C; // get object file name, NULL on fail

   // get object file name id (this will return ID of the object file name assuming that the object is stored in the cache and its file name was created using 'EncodeFileName')
   UID id(C TYPE *data)C; // get object file name id, 'UIDZero' on fail

   // get
   Int elms()C; // get number of elements in container

   Bool contains(C TYPE *data            )C; // check if cache contains this object
   Bool dummy   (C TYPE *data            )C; // check if cache contains this object and it's a dummy (it was not loaded but created as empty)
   void dummy   (C TYPE *data, Bool dummy) ; //       if cache contains this object then set its dummy state (this can be used for example if object was first loaded as a dummy, but then you've downloaded/generated/saved its data, and now need to update the dummy state)

   // operations
   void   lock     (     )C; //   lock      elements      container, unlock must be called after locking container
   Elm&   lockedElm(Int i) ; // access i-th element  from container, this   can  be used   after locking and before unlocking the container
   void unlock     (     )C; // unlock      elements      container, this   must be called after locking the container

   void removeData(C TYPE *data); // manually remove object from cache, this is ignored for objects which still are accessed by some CacheElmPtr's

   void update(); // update cache to process all delay removed elements

   T1(EXTENDED) Cache& replaceClass(); // replace the type of class stored in the container, all elements are automatically removed before changing the type of the class, the new type must be extended from the base 'TYPE' (if you're receiving a compilation error pointing to this method this means that the new class isn't extended from the base class)

   Cache& operator=(C Cache &src); // create from 'src'

   Cache& clear(); // remove all elements
   Cache& del  (); // remove all elements and free helper memory
   Cache(CChar8 *name=NULL, Int block_elms=64); // 'name'=cache name (this value is optional, it will be used when displaying an error message when cache element failed to load)
};
/******************************************************************************/
// COUNTED CACHE
/******************************************************************************/
template<typename TYPE, Cache<TYPE> &CACHE>   struct CacheCounted // Provides additional functionality of counted accessing the elements, 'CacheCounted' is multi-threaded safe
{
   // manage
   CACHE_MODE    mode          (CACHE_MODE mode); // set cache mode, returns previous mode
   CacheCounted& caseSensitive (Bool  sensitive); // set if cache should use case sensitive paths for accessing resources, default=false
   CacheCounted& delayRemove   (Flt   time     ); // set amount of time (in seconds) after which unused elements are removed from cache (<=0 value specifies immediate unloading), default=0
   CacheCounted& delayRemoveNow(               ); // immediately remove all elements marked for delay removal at a later time to free as much memory as possible
   CacheCounted& delayRemoveInc(               ); // increase the cache "delay remove" counter thanks to which elements will not be immediately removed when they're no longer referenced, 'delayRemoveDec' should be called after this method
   CacheCounted& delayRemoveDec(               ); // decrease the cache "delay remove" counter thanks to which elements will not be immediately removed when they're no longer referenced, this should be called after 'delayRemoveInc', once the counter goes back to zero then all non referenced elements will be removed

   // get object and store it forever (as long as the Cache lives)
   TYPE* find      (C Str &file, CChar *path=NULL)C; // find    object by its file name   , don't load if not found, NULL on fail
   TYPE* find      (C UID &id  , CChar *path=NULL)C; // find    object by its file name id, don't load if not found, NULL on fail
   TYPE* get       (C Str &file, CChar *path=NULL) ; // get     object by its file name   ,       load if not found, NULL on fail
   TYPE* get       (C UID &id  , CChar *path=NULL) ; // get     object by its file name id,       load if not found, NULL on fail
   TYPE* operator()(C Str &file, CChar *path=NULL) ; // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected)
   TYPE* operator()(C UID &id  , CChar *path=NULL) ; // require object by its file name id,       load if not found, Exit on fail (unless different CACHE_MODE selected)

   // get object and store it temporarily (as long as it is referenced by at least one 'CacheElmPtr')
   CacheElmPtr<TYPE,CACHE> ptrFind   (C Str &file, CChar *path=NULL)C; // find    object by its file name   , don't load if not found, NULL on fail
   CacheElmPtr<TYPE,CACHE> ptrFind   (C UID &id  , CChar *path=NULL)C; // find    object by its file name id, don't load if not found, NULL on fail
   CacheElmPtr<TYPE,CACHE> ptrGet    (C Str &file, CChar *path=NULL) ; // get     object by its file name   ,       load if not found, NULL on fail
   CacheElmPtr<TYPE,CACHE> ptrGet    (C UID &id  , CChar *path=NULL) ; // get     object by its file name id,       load if not found, NULL on fail
   CacheElmPtr<TYPE,CACHE> ptrRequire(C Str &file, CChar *path=NULL) ; // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr<TYPE,CACHE> ptrRequire(C UID &id  , CChar *path=NULL) ; // require object by its file name id,       load if not found, Exit on fail (unless different CACHE_MODE selected)

   // get object file name (this will return pointer to internally stored file name assuming that the object is stored in the cache)
   CChar* name(C TYPE                    *data, CChar *path=NULL)C; // get object file name, NULL on fail
   CChar* name(C CacheElmPtr<TYPE,CACHE> &data, CChar *path=NULL)C; // get object file name, NULL on fail

   // get object file name id (this will return ID of the object file name assuming that the object is stored in the cache and its file name was created using 'EncodeFileName')
   UID id(C TYPE                    *data)C; // get object file name id, 'UIDZero' on fail
   UID id(C CacheElmPtr<TYPE,CACHE> &data)C; // get object file name id, 'UIDZero' on fail

   // get
   Bool contains(C TYPE                    *data            )C; // check if cache contains this object
   Bool contains(C CacheElmPtr<TYPE,CACHE> &data            )C; // check if cache contains this object
   Int  ptrCount(C TYPE                    *data            )C; // check if cache contains this object and return current number of active pointer references to it, -1 is returned if object is not stored in this cache
   Int  ptrCount(C CacheElmPtr<TYPE,CACHE> &data            )C; // check if cache contains this object and return current number of active pointer references to it, -1 is returned if object is not stored in this cache
   Bool dummy   (C TYPE                    *data            )C; // check if cache contains this object and it's a dummy (it was not loaded but created as empty)
   Bool dummy   (C CacheElmPtr<TYPE,CACHE> &data            )C; // check if cache contains this object and it's a dummy (it was not loaded but created as empty)
   void dummy   (C TYPE                    *data, Bool dummy) ; //       if cache contains this object then set its dummy state (this can be used for example if object was first loaded as a dummy, but then you've downloaded/generated/saved its data, and now need to update the dummy state)
   void dummy   (C CacheElmPtr<TYPE,CACHE> &data, Bool dummy) ; //       if cache contains this object then set its dummy state (this can be used for example if object was first loaded as a dummy, but then you've downloaded/generated/saved its data, and now need to update the dummy state)

   // operations
   Int                          elms     (     )C; // get number of elements in   container
   void                         lock     (     )C; //   lock        elements      container, unlock must be called after locking container
   typename Cache<TYPE>::Elm&   lockedElm(Int i) ; // access i-th   element  from container, this   can  be used   after locking and before unlocking the container
   void                       unlock     (     )C; // unlock        elements      container, this   must be called after locking the container

   void remove(C TYPE *data); // manually remove object from cache, this is ignored for objects accessed using CacheElmPtr (reference counted)

   void update(); // update cache to process all delay removed elements

   T1(EXTENDED) CacheCounted& replaceClass(); // replace the type of class stored in the container, all elements are automatically removed before changing the type of the class, the new type must be extended from the base 'TYPE' (if you're receiving a compilation error pointing to this method this means that the new class isn't extended from the base class)

   CacheCounted& clear(); // remove all elements
   CacheCounted& del  (); // remove all elements and free helper memory
   operator _Cache&() {return CACHE;} // auto-casting to enable Elms function work (without this, function Elms doesn't work for 'CacheCounted', C++ doesn't detect templates)
};
/******************************************************************************/
// CACHE ELEMENT POINTER
/******************************************************************************/
template<typename TYPE, Cache<TYPE> &CACHE>   struct CacheElmPtr // Cache Element Pointer - can hold a reference to a TYPE based object in the CACHE cache, number of active references for a given object is stored in the cache
{
   // operators
   TYPE* operator ()  (                   )C {return  T._data            ;} // access the data, you can use the returned pointer   as long as this 'CacheElmPtr' object exists and not modified
   TYPE* operator ->  (                   )C {return  T._data            ;} // access the data, you can use the returned pointer   as long as this 'CacheElmPtr' object exists and not modified
   TYPE& operator *   (                   )C {return *T._data            ;} // access the data, you can use the returned reference as long as this 'CacheElmPtr' object exists and not modified
   Bool  operator ==  (  int              )C {return  T._data==NULL      ;} // if pointers are equal     (this simulates "T==NULL")
   Bool  operator !=  (  int              )C {return  T._data!=NULL      ;} // if pointers are different (this simulates "T!=NULL")
   Bool  operator ==  (C TYPE        *data)C {return  T._data==data      ;} // if pointers are equal
   Bool  operator !=  (C TYPE        *data)C {return  T._data!=data      ;} // if pointers are different
   Bool  operator ==  (C CacheElmPtr &eptr)C {return  T._data==eptr._data;} // if pointers are equal
   Bool  operator !=  (C CacheElmPtr &eptr)C {return  T._data!=eptr._data;} // if pointers are different
         operator Bool(                   )C {return  T._data!=NULL      ;} // if pointer  is  valid

   // get object file name (this will return pointer to internally stored file name assuming that the object is stored in the cache)
   CChar* name(CChar *path=NULL)C; // get object file name, NULL on fail

   // get object file name id (this will return ID of the object file name assuming that the object is stored in the cache and its file name was created using 'EncodeFileName')
   UID id()C; // get object file name id, 'UIDZero' on fail

   // get
   Bool dummy(          )C; // check if this object is a dummy (it was not loaded but created as empty)
   void dummy(Bool dummy) ; // set dummy state for this object (this can be used for example if object was first loaded as a dummy, but then you've downloaded/generated/saved its data, and now need to update the dummy state)

   // operations
   CacheElmPtr& operator=(  TYPE        *data); // set       pointer to 'data', this automatically decreases the reference count of current data and increases the reference count of the new data
   CacheElmPtr& operator=(C CacheElmPtr &eptr); // set       pointer to 'eptr', this automatically decreases the reference count of current data and increases the reference count of the new data
   CacheElmPtr& clear    (                   ); // clear the pointer to  NULL , this automatically decreases the reference count of current data
   CacheElmPtr& operator=(int                ); // clear the pointer to  NULL , this automatically decreases the reference count of current data, this simulates "T=NULL"

   // get object and store it temporarily (as long as it is referenced by at least one 'CacheElmPtr')
   CacheElmPtr& find     (C Str  &file, CChar *path=NULL); // find    object by its file name   , don't load if not found, NULL on fail
   CacheElmPtr& find     (C UID  &id  , CChar *path=NULL); // find    object by its file name id, don't load if not found, NULL on fail
   CacheElmPtr& get      (C Str  &file, CChar *path=NULL); // get     object by its file name   ,       load if not found, NULL on fail
   CacheElmPtr& get      (C UID  &id  , CChar *path=NULL); // get     object by its file name id,       load if not found, NULL on fail
   CacheElmPtr& require  (C Str  &file, CChar *path=NULL); // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr& require  (C UID  &id  , CChar *path=NULL); // require object by its file name id,       load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr& operator=(C Str  &file                  ); // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected), works exactly the same as 'require' method, however without the option of specifying additional 'path'
   CacheElmPtr& operator=(C Str8 &file                  ); // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected), works exactly the same as 'require' method, however without the option of specifying additional 'path'
   CacheElmPtr& operator=(CChar  *file                  ); // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected), works exactly the same as 'require' method, however without the option of specifying additional 'path'
   CacheElmPtr& operator=(CChar8 *file                  ); // require object by its file name   ,       load if not found, Exit on fail (unless different CACHE_MODE selected), works exactly the same as 'require' method, however without the option of specifying additional 'path'
   CacheElmPtr& operator=(C UID  &id                    ); // require object by its file name id,       load if not found, Exit on fail (unless different CACHE_MODE selected), works exactly the same as 'require' method, however without the option of specifying additional 'path'

   // constructors / destructors
   CacheElmPtr(  int=0            ); // initialize the pointer with  NULL
   CacheElmPtr(  TYPE        *data); // initialize the pointer with 'data', this automatically increases the reference count of the    'data'
   CacheElmPtr(C CacheElmPtr &eptr); // initialize the pointer with 'eptr', this automatically increases the reference count of the    'eptr'
   CacheElmPtr(C Str         &file); // initialize the pointer with 'file', this automatically increases the reference count of the    'file', works exactly the same as 'operator=(C Str  &file)', require object, load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr(C Str8        &file); // initialize the pointer with 'file', this automatically increases the reference count of the    'file', works exactly the same as 'operator=(C Str8 &file)', require object, load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr(  CChar       *file); // initialize the pointer with 'file', this automatically increases the reference count of the    'file', works exactly the same as 'operator=(CChar  *file)', require object, load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr(  CChar8      *file); // initialize the pointer with 'file', this automatically increases the reference count of the    'file', works exactly the same as 'operator=(CChar8 *file)', require object, load if not found, Exit on fail (unless different CACHE_MODE selected)
   CacheElmPtr(C UID         &id  ); // initialize the pointer with 'id'  , this automatically increases the reference count of the    'file', works exactly the same as 'operator=(C UID  &id  )', require object, load if not found, Exit on fail (unless different CACHE_MODE selected)
  ~CacheElmPtr(                   ); // release    the pointer            , this automatically decreases the reference count of current data

private:
   TYPE *_data;
   CacheElmPtr(C _Cache::Dummy &dummy) {T._data=(TYPE*)dummy.data;}
   friend struct CacheCounted<TYPE,CACHE>;
};
/******************************************************************************/
struct CacheLock // Cache Lock (automatically locks and unlocks the cache at object creation and destruction)
{
   CacheLock(C _Cache &cache) : _cache(cache) {_cache.  lock();}
  ~CacheLock(               )                 {_cache.unlock();}

private:
C _Cache &_cache;
   NO_COPY_CONSTRUCTOR(CacheLock);
};
/******************************************************************************/
#define DECLARE_CACHE(type, cache_name, ptr_name            )   extern Cache<type> _##cache_name            ;   extern CacheCounted<type, _##cache_name> cache_name;   typedef CacheElmPtr<type, _##cache_name> ptr_name; // this declares a counted cache in a header, the cache stores 'type' data, the cache name is 'cache_name' and the name for the pointer to elements is 'ptr_name'
#define  DEFINE_CACHE(type, cache_name, ptr_name, debug_name)          Cache<type> _##cache_name(debug_name);          CacheCounted<type, _##cache_name> cache_name;   typedef CacheElmPtr<type, _##cache_name> ptr_name; // this defines  a counted cache in C++ file
/******************************************************************************/
