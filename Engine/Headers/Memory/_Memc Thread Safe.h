/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct _ThreadSafeMemc // Thread-Safe Continuous Memory Based Container Base - Do not use this class, use 'ThreadSafeMemc' instead
{
   void clear();
   void del  ();

   // get / set
   Int  elms    ()C {return _memc.elms    ();}
   UInt elmSize ()C {return _memc.elmSize ();}
   UInt memUsage()C {return _memc.memUsage();}

   Ptr lockedData (     )C {return _memc.data ( );}
   Ptr lockedAddr (Int i)C {return _memc.addr (i);}
   Ptr lockedElm  (Int i)C {return _memc      [i];}
   Ptr lockedFirst(     )C {return _memc.first( );}
   Ptr lockedLast (     )C {return _memc.last ( );}
   Ptr lockedNew  (     )  {return _memc.New  ( );}
   Ptr lockedNewAt(Int i)  {return _memc.NewAt(i);}

   Int  index   (CPtr elm)C;
   Bool contains(CPtr elm)C {return index(elm)!=-1;}

   void removeLast();
   void remove    (Int  i  , Bool keep_order=false);
   void removeData(CPtr elm, Bool keep_order=false);

   void setNum    (Int num);
   void setNumZero(Int num);
   Int  addNum    (Int num);

   Bool binarySearch(CPtr value, Int &index, Int compare(CPtr a, CPtr b))C;

   void           sort(Int compare(CPtr a, CPtr b));
   void   reverseOrder();
   void randomizeOrder();
   void    rotateOrder(Int offset);
   void      swapOrder(Int i, Int j);
   void      moveElm  (Int elm, Int new_index);

   // operations
   void   lock()C {_cs.on ();}
   void unlock()C {_cs.off();}

private:
  _Memc     _memc;
   CritSect _cs;

  _ThreadSafeMemc(Int elm_size, void (*_new)(Ptr elm), void (*_del)(Ptr elm));
   T1(TYPE) friend struct ThreadSafeMemc;
};
/******************************************************************************/
