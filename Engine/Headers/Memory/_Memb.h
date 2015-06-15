/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct _Memb // Block Based Container Base - Do not use this class, use 'Memb' instead
{
   void del  ();
   void clear();

   Int    elms    ()C {return _elms      ;}
   UInt   elmSize ()C {return _elm_size  ;}
   UInt blockElms ()C {return _block_elms;}
   UInt   memUsage()C {return _blocks*blockElms()*elmSize();}

   Ptr addr      (Int i)C {return InRange(i, _elms) ?       _element(i) : NULL;}
   Ptr operator[](Int i)C {  RANGE_ASSERT(i, _elms); return _element(i);}
   Ptr operator()(Int i);
   Ptr first     (     )C {return T[0        ];}
   Ptr last      (     )C {return T[elms()-1 ];}
   Ptr New       (     )  {return T[addNum(1)];}
   Ptr NewAt     (Int i);

   Int  index   (CPtr elm)C;
   Bool contains(CPtr elm)C {return index(elm)!=-1;}

   void removeLast();
   void remove    (Int  i  , Bool keep_order=false);
   void removeData(CPtr elm, Bool keep_order=false);

   void setNum    (Int num);
   void setNumZero(Int num);
   Int  addNum    (Int num);

   void reverseOrder();
   void    swapOrder(Int i, Int j);

   void saveRaw(File &f)C;
   Bool loadRaw(File &f) ;

 ~_Memb() {del();}

private:
   Int    _elms;
   UInt   _elm_size, _block_elms, _blocks, _shr;
   Ptr   *_ptr;
   void (*_new)(Ptr elm),
        (*_del)(Ptr elm);
   Ptr  _element(Int i)C;
         _Memb(Int elm_size, Int block_elms, void (*_new)(Ptr elm), void (*_del)(Ptr elm));
   void _reset(Int elm_size, Int block_elms, void (*_new)(Ptr elm), void (*_del)(Ptr elm));
   NO_COPY_CONSTRUCTOR(_Memb);
   T1(TYPE) friend struct Memb;
   T1(TYPE) friend struct MembAbstract;
};
/******************************************************************************/
