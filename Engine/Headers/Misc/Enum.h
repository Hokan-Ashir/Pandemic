/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Enum' to handle operating on C++ style enums.

/******************************************************************************/
struct Enum // Enum helper class !! Enum doesn't support manual value assigning, for example "enum SAMPLE_ENUM{ CUSTOM_VALUE=128 };" !!
{
   struct Elm // Enum Element
   {
      Char8 name[64]; // element name
      UID   id      ; // element unique id

      Elm& set(C Str8 &name, C UID &id) {Set(T.name, name); T.id=id; return T;}
   };

   Char8 name[64]; // enum name

   // get
 C Mems<Elm>& elms      (     )C {return _elms   ;} // get      enum elements
 C      Elm & operator[](Int i)C {return _elms[i];} // get i-th enum element

   CChar8* elmName(Int i)C; // get i-th enum element name, NULL      on fail (if index is out of range)
 C UID   & elmID  (Int i)C; // get i-th enum element ID  , 'UIDZero' on fail (if index is out of range)

   Int find      (CChar8 *name)C; // get index of enum element by specifying its 'name', -1   on fail (if element was not found)
   Int find      (CChar  *name)C; // get index of enum element by specifying its 'name', -1   on fail (if element was not found)
   Int find      (C UID  &id  )C; // get index of enum element by specifying its 'id'  , -1   on fail (if element was not found)
   Int operator()(CChar8 *name)C; // get index of enum element by specifying its 'name', Exit on fail (if element was not found)
   Int operator()(CChar  *name)C; // get index of enum element by specifying its 'name', Exit on fail (if element was not found)
   Int operator()(C UID  &id  )C; // get index of enum element by specifying its 'id'  , Exit on fail (if element was not found)

 C UID   & findID  (CChar8 *name)C {return elmID  (find(name));} // get ID   of enum element by specifying its 'name', 'UIDZero' on fail (if element was not found)
 C UID   & findID  (CChar  *name)C {return elmID  (find(name));} // get ID   of enum element by specifying its 'name', 'UIDZero' on fail (if element was not found)
   CChar8* findName(C UID  &id  )C {return elmName(find(id  ));} // get name of enum element by specifying its 'id'  , NULL      on fail (if element was not found)
 C UID   &  getID  (CChar8 *name)C {return elmID  (T   (name));} // get ID   of enum element by specifying its 'name', Exit      on fail (if element was not found)
 C UID   &  getID  (CChar  *name)C {return elmID  (T   (name));} // get ID   of enum element by specifying its 'name', Exit      on fail (if element was not found)
   CChar8*  getName(C UID  &id  )C {return elmName(T   (id  ));} // get name of enum element by specifying its 'id'  , Exit      on fail (if element was not found)

   // manage
   Enum& create(C Str &name, C Memp<Elm> &elms); // create from custom elements

   Enum& operator=(C Enum &src); // create enum from 'src'

   // io
   void operator=(C Str  &name) ; // load binary                 , Exit  on fail
   void save     (  File &f   )C; // save binary
   Bool load     (  File &f   ) ; // load binary                 , false on fail
   Bool save     (C Str  &name)C; // save binary                 , false on fail
   Bool load     (C Str  &name) ; // load binary                 , false on fail
   Bool saveH    (C Str  &name)C; // save text (C++ header style), false on fail

   Enum&   del ( );
  ~Enum() {del ( );}
   Enum() {Zero(T);}

private:
   UInt     *_order;
   Mems<Elm> _elms ;
   Enum(C Enum&);
};
/******************************************************************************/
extern Cache<Enum> Enums; // Enum Cache
/******************************************************************************/
inline Int Elms(C Enum &e) {return e.elms().elms();}
/******************************************************************************/
