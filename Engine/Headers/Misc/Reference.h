/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
T1(TYPE) struct Reference // Reference, this is a pointer to an object which may be deleted but its memory is still valid and possibly occupied by another object of similar class
{
   // get / set
   void  clear     ()  {_object=NULL; _object_id.zero ();            } // clear reference to NULL
   Bool  empty     ()C {return       !_object_id.valid();            } // perform a check if the reference is empty (doesn't want to point to any object at all)
   Bool  valid     ()C {return  _object && _object->id()==_object_id;} // perform a check if the reference is valid (points to an existing object with matching id)
   TYPE* validPtr  ()C {return   valid() ? _object : NULL           ;} // return  a pointer   to object that is valid
 C UID & objectID  ()C {return  _object_id                          ;} // return  a              object ID
   TYPE& operator()()C {return *_object                             ;} // return  a reference to object, usage of this method must be preceded by performing a reference validation using 'valid' method
   TYPE* operator->()C {return  _object                             ;} // return  a reference to object, usage of this method must be preceded by performing a reference validation using 'valid' method

   // compare
   T1(OBJECT)   Bool operator==(OBJECT           *object)C {return T._object==     object && (object ? T._object_id==     object->id() : true );} // if reference points to 'object'
   T1(OBJECT)   Bool operator==(OBJECT           &object)C {return T._object==    &object &&           T._object_id==     object .id()         ;} // if reference points to 'object'
   T1(TYPE2 )   Bool operator==(Reference<TYPE2> &ref   )C {return T._object==ref._object &&           T._object_id==ref._object_id            ;} // if references are equal

   T1(OBJECT)   Bool operator!=(OBJECT           *object)C {return T._object!=     object || (object ? T._object_id!=     object->id() : false);} // if reference doesn't point to 'object'
   T1(OBJECT)   Bool operator!=(OBJECT           &object)C {return T._object!=    &object ||           T._object_id!=     object .id()         ;} // if reference doesn't point to 'object'
   T1(TYPE2 )   Bool operator!=(Reference<TYPE2> &ref   )C {return T._object!=ref._object ||           T._object_id!=ref._object_id            ;} // if references are not equal

   // io
   void save(File &f)C; // save 'object_id'
   Bool load(File &f) ; // load 'object_id' and set 'object' pointer to NULL, actual linking pointer to the object should be performed later using 'link' method

   // link
   void link(); // link the reference with existing World object, this method should be called only inside 'Game::Obj::linkReferences' or 'Game::World.link_references'

   // construct
   Reference(         ) {T._object=NULL;                                    T._object_id.zero();}
   Reference(TYPE &obj) {T._object=&obj;        T._object_id=obj .id();                         }
   Reference(TYPE *obj) {T._object= obj; if(obj)T._object_id=obj->id();else T._object_id.zero();}

private:
   TYPE *_object;
   UID   _object_id;
};
/******************************************************************************/
