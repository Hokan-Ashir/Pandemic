/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Map' to quickly access custom data by creating it from specified key.
      Once 'Map' creates a resource, it will keep it in the memory for faster access.

   Objects in 'Map' containers are stored using 'Memx' container,
      which means that the memory address of the elements remains constant as long as the elements exist.

/******************************************************************************/
enum MAP_MODE // Map Mode
{
   MAP_EXIT     , //       load data, Exit  on fail
   MAP_NULL     , //       load data, NULL  on fail
   MAP_DUMMY    , //       load data, dummy on fail       (pointer to empty data, initialized with constructor but without the 'load' method)
   MAP_ALL_NULL , // don't load data, always return NULL
   MAP_ALL_DUMMY, // don't load data, always return dummy (pointer to empty data, initialized with constructor but without the 'load' method)
};
/******************************************************************************/
T2(KEY, DATA) struct Map : _Map // Map - container for dynamically created elements, consisting of unique key's and their corresponding data, Map is multi-threaded safe
{
   struct Elm : _Map::Elm
   {
      DATA data;
      KEY  key ;
      Desc desc;
   };

   // manage
   Map&     clear(); // remove all elements
   Map&     del  (); // remove all elements and free helper memory
   MAP_MODE mode (MAP_MODE mode); // set map mode, returns previous mode

   // get
   Int elms    ()C; // get number of elements in container
   Int dataSize()C; // get size of DATA element

   DATA* find      (C KEY &key); // find element, don't create if not found, NULL on fail
   DATA* get       (C KEY &key); // get  element,       create if not found, NULL on fail
   DATA* operator()(C KEY &key); // get  element,       create if not found, Exit on fail (unless different MAP_MODE selected)

   Bool containsKey (C KEY  &key )C; // check if map contains an element with specified key
   Bool containsData(C DATA *data)C; // check if map contains an element, testing is done by comparing elements memory address only
 C KEY* key         (C DATA *data)C; // get element key, this will return pointer to element's key assuming that the element is stored in this Map, NULL on fail

   // operations
   void    lock      (            )C; //   lock      elements          container, unlock must be called after locking container
 C KEY &   lockedKey (  Int   i   ) ; // access i-th element key  from container, this   can  be used   after locking and before unlocking the container
   DATA&   lockedData(  Int   i   ) ; // access i-th element data from container, this   can  be used   after locking and before unlocking the container
 C DATA&   lockedData(  Int   i   )C; // access i-th element data from container, this   can  be used   after locking and before unlocking the container
   void  unlock      (            )C; // unlock      elements          container, this   must be called after locking the container
   void    remove    (  Int   i   ) ; // remove i-th element      from container
   void    removeKey (C KEY  &key ) ; // remove      element      from container
   void    removeData(C DATA *data) ; // remove      element      from container
   Bool    replaceKey(C KEY  &src, C KEY &dest); // replace existing element 'src' key with 'dest', false on fail

   T1(EXTENDED) Map& replaceClass(); // replace the type of class stored in the container, all elements are automatically removed before changing the type of the class, the new type must be extended from the base 'DATA' (if you're receiving a compilation error pointing to this method this means that the new class isn't extended from the base class)

   Map& operator=(C Map &src); // create from 'src'

   Map(Int compare(C KEY &a, C KEY &b), Bool create(DATA &data, C KEY &key, Ptr user)=NULL, Ptr user=NULL, Int block_elms=64); // 'compare'=function which compares two keys, 'create'=function that creates 'data' on the base of the constant 'key'
};
/******************************************************************************/
struct MapLock // Map Lock (automatically locks and unlocks the map at object creation and destruction)
{
   MapLock(_Map &map) : _map(map) {_map.  lock();}
  ~MapLock(         )             {_map.unlock();}

private:
  _Map &_map;
   NO_COPY_CONSTRUCTOR(MapLock);
};
/******************************************************************************/
