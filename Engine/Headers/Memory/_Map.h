/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct _Map // Map (base) - Do not use this class, use 'Map' instead
{
   struct Desc
   {
   private:
      UInt _flag;
   };
   struct Elm
   {
   };

   Int elms    ()C {return _elms;}
   Int dataSize()C {return _data_size;} // get size of DATA element

   void   lock()C;
   void unlock()C;

private:
   Bool       _d_cs_lock;
   Int        _elms, _key_offset, _data_offset, _desc_offset, _data_size;
   UInt       _mode;
   Elm      **_order;
   Memx<Elm>  _memx;
   CritSect   _cs;
   Ptr        _user;
   Int      (*_compare )(CPtr key_a, CPtr key_b);
   Bool     (*_create  )( Ptr elm  , CPtr key  , Ptr user);
   void     (*_copy_key)( Ptr dest , CPtr src  );

   void clear();
   void del  ();
   UInt mode (UInt mode);

    Ptr  find        (CPtr key );
    Ptr  get         (CPtr key );
    Ptr  operator()  (CPtr key );
    Bool containsKey (CPtr key )C;
    Bool containsData(CPtr data)C;
   CPtr  key         (CPtr data)C;

   CPtr lockedKey (Int  i   );
    Ptr lockedData(Int  i   );
   void remove    (Int  i   );
   void removeKey (CPtr key );
   void removeData(CPtr data);
   Bool replaceKey(CPtr src, CPtr dest);

   void _from(C _Map &src);

 ~_Map() {del();}

protected:
   T2(KEY,DATA) friend struct Map;
  _Map(Int block_elms, Int compare(CPtr key_a, CPtr key_b), Bool create(Ptr data, CPtr key, Ptr user), Ptr user, void (&copy_key)(Ptr dest, CPtr src));
   NO_COPY_CONSTRUCTOR(_Map);
};
/******************************************************************************/
