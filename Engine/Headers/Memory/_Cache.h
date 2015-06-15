/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct _Cache // Cache (base) - Do not use this class, use 'Cache' instead
{
   struct Desc
   {
      C Str& file()C {return _file;} // get file name

   private:
      Str  _file;
      UInt _flag, _ptr_num;
      Flt  _delay_remove;
   };
   struct Elm
   {
   };

   Int elms()C {return _elms;}

   void   lock()C;
   void unlock()C;

private:
   Bool       _case_sensitive, _d_cs_lock;
   Int        _elms, _data_offset, _desc_offset, _delay_remove_counter;
   UInt       _mode;
   Flt        _delay_remove_time, _delay_remove_check;
   CChar8    *_debug_name;
   Elm      **_order;
   Memx<Elm>  _memx;
   Memc<Elm*> _delay_remove;
   Memc<Ptr> *_record_dec_ref;
   UIntPtr    _record_dec_ref_thread_id;
   CritSect   _cs;
   Ptr        _user;
   Bool     (*_load          )( Ptr data, C Str &file);
   Bool     (*_load_user     )( Ptr data, C Str &file, Ptr user);
   Bool     (*_can_be_removed)(CPtr data);

   void clear         ();
   void del           ();
   UInt mode          (UInt mode);
   void caseSensitive (Bool sensitive);
   void delayRemove   (Flt  time);
   void delayRemoveNow();
   void delayRemoveInc();
   void delayRemoveDec();
   void update        ();

   Ptr    _find      (CChar *file, CChar *path, Bool counted);
   Ptr    _find      (C UID &id  , CChar *path, Bool counted);
   Ptr    _get       (CChar *file, CChar *path, Bool counted);
   Ptr    _get       (C UID &id  , CChar *path, Bool counted);
   Ptr    _require   (CChar *file, CChar *path, Bool counted);
   Ptr    _require   (C UID &id  , CChar *path, Bool counted);
   Bool   _contains  (CPtr   data                           )C;
   Int    _ptrCount  (CPtr   data                           )C;
   Bool   _dummy     (CPtr   data                           )C;
   void   _dummy     (CPtr   data, Bool   dummy             );
   CChar* _name      (CPtr   data, CChar *path              )C;
   UID    _id        (CPtr   data                           )C;
   void   _removeData(CPtr   data                           );

   void   _incRef(CPtr data);
   void   _decRef(CPtr data);
   void _clearRef(Elm  &elm);

   void _from(C _Cache &src);

   Elm& lockedElm(Int i);

 ~_Cache() {del();}

protected:
  _Cache(CChar8 *name, Int block_elms, Bool (*load)(Ptr data, C Str &file));

   NO_COPY_CONSTRUCTOR(_Cache);

   T1(TYPE)                                    friend struct Cache;
   template<typename TYPE, Cache<TYPE> &CACHE> friend struct CacheElmPtr;
   template<typename TYPE, Cache<TYPE> &CACHE> friend struct CacheCounted;

   struct Dummy { Ptr data; Dummy(Ptr data) {T.data=data;} };
};
/******************************************************************************/
