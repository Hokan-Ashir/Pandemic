/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
inline Bool Any(C Flt &x                              ) {return FlagTest((U32&)x                              , ~SIGN_BIT);} // faster version of "x!=0"
inline Bool Any(C Flt &x, C Flt &y                    ) {return FlagTest((U32&)x | (U32&)y                    , ~SIGN_BIT);} // faster version of "x!=0 || y!=0"
inline Bool Any(C Flt &x, C Flt &y, C Flt &z          ) {return FlagTest((U32&)x | (U32&)y | (U32&)z          , ~SIGN_BIT);} // faster version of "x!=0 || y!=0 || z!=0"
inline Bool Any(C Flt &x, C Flt &y, C Flt &z, C Flt &w) {return FlagTest((U32&)x | (U32&)y | (U32&)z | (U32&)w, ~SIGN_BIT);} // faster version of "x!=0 || y!=0 || z!=0 || w!=0"
/******************************************************************************/
T1(TYPE) Bool InRange(Int  i, TYPE &container) {return UInt (i)<UInt (Elms(container));}
T1(TYPE) Bool InRange(UInt i, TYPE &container) {return UInt (i)<UInt (Elms(container));}
T1(TYPE) Bool InRange(Long i, TYPE &container) {return ULong(i)<ULong(Elms(container));}
/******************************************************************************/
T1(TYPE) struct ClassFunc // various basic functions used by many classes
{
   static void New     (Ptr elm                        ) {    new(        elm )     TYPE            ;}
   static void Del     (Ptr elm                        ) {       ( (TYPE*)elm )->  ~TYPE(          );}
   static void Copy    (Ptr dest,  CPtr  src           ) {       (*(TYPE*)dest)=*(C TYPE*)src       ;}
   static Bool Load    (Ptr elm , C Str &file          ) {return ( (TYPE*)elm )->   load(file      );}
   static Bool LoadUser(Ptr elm , C Str &file, Ptr user) {return ( (TYPE*)elm )->   load(file, user);}

   static inline Bool EmptyNew() {return New==ClassFunc<Int>::New;}   static inline void (*GetNew())(Ptr elm) {return EmptyNew() ? NULL : New;}
   static inline Bool EmptyDel() {return Del==ClassFunc<Int>::Del;}   static inline void (*GetDel())(Ptr elm) {return EmptyDel() ? NULL : Del;}
};
// force empty new delete in case some compilers don't merge similar functions, this also helps in DEBUG mode which doesn't do merging
#define EMPTY_NEW_DEL(TYPE) \
   template<> inline void (*ClassFunc<TYPE>::GetNew())(Ptr elm) {return NULL;}\
   template<> inline void (*ClassFunc<TYPE>::GetDel())(Ptr elm) {return NULL;}
EMPTY_NEW_DEL(Bool )
EMPTY_NEW_DEL(Char ) EMPTY_NEW_DEL(Char8 )
EMPTY_NEW_DEL(SByte) EMPTY_NEW_DEL(Byte  )
EMPTY_NEW_DEL(Short) EMPTY_NEW_DEL(UShort)
EMPTY_NEW_DEL(Int  ) EMPTY_NEW_DEL(UInt  )
EMPTY_NEW_DEL(Long ) EMPTY_NEW_DEL(ULong )
EMPTY_NEW_DEL(Flt  ) EMPTY_NEW_DEL(Dbl   )
EMPTY_NEW_DEL(Ptr  )
#undef EMPTY_NEW_DEL
/******************************************************************************/
inline GuiObj* MouseTouch::guiObj(Int i) {return InRange(i, Touches) ? Touches[i].guiObj() : Gui.ms();}
/******************************************************************************/
// STRING
/******************************************************************************/
#ifdef HAS_MOVE_CONSTRUCTOR
inline         Str8::Str8     (Str8 &&s           ) {_length=0; Swap(T, s);}
inline         Str ::Str      (Str  &&s           ) {_length=0; Swap(T, s);}
inline   Str8& Str8::operator=(Str8 &&s           ) {           Swap(T, s); return T;}
inline   Str & Str ::operator=(Str  &&s           ) {           Swap(T, s); return T;}

inline Str8 operator+(Str8 &&a,   CChar  *b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   CChar8 *b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C Str    &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C Str8   &b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Char    b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Char8   b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Bool    b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   SByte   b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Int     b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Long    b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Byte    b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   UInt    b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   ULong   b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Flt     b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   Dbl     b) {return a+=b;}
inline Str8 operator+(Str8 &&a,   CPtr    b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C Vec2   &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecD2  &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecI2  &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C Vec    &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecD   &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecI   &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C Vec4   &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecD4  &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecI4  &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C VecB4  &b) {return a+=b;}
inline Str8 operator+(Str8 &&a, C BStr   &b) {return a+=b;}

inline Str operator+(Str &&a,   CChar  *b) {return a+=b;}
inline Str operator+(Str &&a,   CChar8 *b) {return a+=b;}
inline Str operator+(Str &&a, C Str    &b) {return a+=b;}
inline Str operator+(Str &&a, C Str8   &b) {return a+=b;}
inline Str operator+(Str &&a,   Char    b) {return a+=b;}
inline Str operator+(Str &&a,   Char8   b) {return a+=b;}
inline Str operator+(Str &&a,   Bool    b) {return a+=b;}
inline Str operator+(Str &&a,   SByte   b) {return a+=b;}
inline Str operator+(Str &&a,   Int     b) {return a+=b;}
inline Str operator+(Str &&a,   Long    b) {return a+=b;}
inline Str operator+(Str &&a,   Byte    b) {return a+=b;}
inline Str operator+(Str &&a,   UInt    b) {return a+=b;}
inline Str operator+(Str &&a,   ULong   b) {return a+=b;}
inline Str operator+(Str &&a,   Flt     b) {return a+=b;}
inline Str operator+(Str &&a,   Dbl     b) {return a+=b;}
inline Str operator+(Str &&a,   CPtr    b) {return a+=b;}
inline Str operator+(Str &&a, C Vec2   &b) {return a+=b;}
inline Str operator+(Str &&a, C VecD2  &b) {return a+=b;}
inline Str operator+(Str &&a, C VecI2  &b) {return a+=b;}
inline Str operator+(Str &&a, C Vec    &b) {return a+=b;}
inline Str operator+(Str &&a, C VecD   &b) {return a+=b;}
inline Str operator+(Str &&a, C VecI   &b) {return a+=b;}
inline Str operator+(Str &&a, C Vec4   &b) {return a+=b;}
inline Str operator+(Str &&a, C VecD4  &b) {return a+=b;}
inline Str operator+(Str &&a, C VecI4  &b) {return a+=b;}
inline Str operator+(Str &&a, C VecB4  &b) {return a+=b;}
inline Str operator+(Str &&a, C BStr   &b) {return a+=b;}
#endif
/******************************************************************************/
// SORT
/******************************************************************************/
void _Sort( Ptr   data, Int elms, Int elm_size, Int compare(CPtr a, CPtr b));
void _Sort(_Memb &memb,                         Int compare(CPtr a, CPtr b));
void _Sort(_Memx &memx,                         Int compare(CPtr a, CPtr b));
void _Sort(_Meml &meml,                         Int compare(CPtr a, CPtr b));

Bool _BinarySearch(   CPtr  data, Int elms, Int elm_size, CPtr value, Int &index, Int compare(CPtr a, CPtr b));
Bool _BinarySearch(C _Memb &data,                         CPtr value, Int &index, Int compare(CPtr a, CPtr b));
Bool _BinarySearch(C _Memx &data,                         CPtr value, Int &index, Int compare(CPtr a, CPtr b));
Bool _BinarySearch(C _Meml &data,                         CPtr value, Int &index, Int compare(CPtr a, CPtr b));

T1(TYPE) void Sort(TYPE *data, Int elms, Int compare(C TYPE &a, C TYPE &b)) {_Sort(Ptr(data), elms, SIZE(TYPE), (Int(*)(CPtr, CPtr))compare);}

T2(DATA, VALUE)   Bool BinarySearch(C DATA *data, Int elms, C VALUE &value, Int &index, Int compare(C DATA &a, C VALUE &b)) {return _BinarySearch(data, elms, SIZE(DATA), &value, index, (Int(*)(CPtr, CPtr))compare);}
/******************************************************************************/
// MEMORY
/******************************************************************************/
void _Realloc    (Ptr &data, Int size_new, Int size_old); // reallocate memory without losing data                      , Exit on fail !! combine only with 'Alloc' !!
void _ReallocZero(Ptr &data, Int size_new, Int size_old); // reallocate memory without losing data and zero new elements, Exit on fail !! combine only with 'Alloc' !!

T1(TYPE) void Realloc    (TYPE* &data, Int elms_new, Int elms_old) {_Realloc    (*(Ptr*)&data, elms_new*SIZE(TYPE), elms_old*SIZE(TYPE));}
T1(TYPE) void ReallocZero(TYPE* &data, Int elms_new, Int elms_old) {_ReallocZero(*(Ptr*)&data, elms_new*SIZE(TYPE), elms_old*SIZE(TYPE));}

void   _ReverseOrder(Ptr data, Int elms, UInt elm_size                        ); // reverse   order of elements (first<->last)
void _RandomizeOrder(Ptr data, Int elms, UInt elm_size                        ); // randomize order of elements
void    _RotateOrder(Ptr data, Int elms, UInt elm_size, Int offset            ); // rotate    order of elements, changes the order of elements so "new_index=old_index+offset", 'offset'=offset of moving the original indexes into target indexes (-Inf..Inf)
void      _MoveElm  (Ptr data, Int elms, UInt elm_size, Int elm, Int new_index); // move 'elm' element to new position located at 'new_index'

T1(TYPE) void   ReverseOrder(TYPE *data, Int elms                        ) {  _ReverseOrder(data, elms, SIZE(TYPE)                );}
T1(TYPE) void RandomizeOrder(TYPE *data, Int elms                        ) {_RandomizeOrder(data, elms, SIZE(TYPE)                );}
T1(TYPE) void    RotateOrder(TYPE *data, Int elms, Int offset            ) {   _RotateOrder(data, elms, SIZE(TYPE), offset        );}
T1(TYPE) void      MoveElm  (TYPE *data, Int elms, Int elm, Int new_index) {     _MoveElm  (data, elms, SIZE(TYPE), elm, new_index);}
/******************************************************************************/
// REFERENCE
/******************************************************************************/
T1(TYPE) void Reference<TYPE>::save(File &f)C {f<<_object_id;}
T1(TYPE) Bool Reference<TYPE>::load(File &f)  {f>>_object_id; _object=NULL; return true;}
T1(TYPE) void Reference<TYPE>::link(       )  {if(!valid() && _object_id.valid())_object=CAST(TYPE, Game::World.objFindById(_object_id));}
/******************************************************************************/
// FIXED ARRAY
/******************************************************************************/
template<typename TYPE, Int NUM>                                     FixedArray<TYPE, NUM>::FixedArray(                 ) {_elm_size=SIZE(TYPE); _data=NULL;}
template<typename TYPE, Int NUM>                                     FixedArray<TYPE, NUM>::FixedArray(C FixedArray &src) {_elm_size=SIZE(TYPE); _data=NULL; T=src;}
template<typename TYPE, Int NUM>              FixedArray<TYPE, NUM>& FixedArray<TYPE, NUM>::operator= (C FixedArray &src) {FREPAO(T)=src[i]; return T;}
template<typename TYPE, Int NUM>              FixedArray<TYPE, NUM>& FixedArray<TYPE, NUM>::del         () {DeleteN(_data); _elm_size=SIZE(TYPE); return T;}
template<typename TYPE, Int NUM> T1(EXTENDED) FixedArray<TYPE, NUM>& FixedArray<TYPE, NUM>::replaceClass() {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>(); del(); _elm_size=SIZE(EXTENDED); _data=new EXTENDED[NUM]; return T;}

template<typename TYPE>                              FixedElm<TYPE>::FixedElm (               ) {_elm_size=SIZE(TYPE); _data=NULL;}
template<typename TYPE>                              FixedElm<TYPE>::FixedElm (C FixedElm &src) {_elm_size=SIZE(TYPE); _data=NULL; T=src;}
template<typename TYPE>              FixedElm<TYPE>& FixedElm<TYPE>::operator=(C FixedElm &src) {T()=src(); return T;}
template<typename TYPE>              FixedElm<TYPE>& FixedElm<TYPE>::del         () {Delete(_data); _elm_size=SIZE(TYPE); return T;}
template<typename TYPE> T1(EXTENDED) FixedElm<TYPE>& FixedElm<TYPE>::replaceClass() {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>(); del(); _elm_size=SIZE(EXTENDED); _data=new EXTENDED; return T;}
/******************************************************************************/
// MEMS
/******************************************************************************/
T1(TYPE) Mems<TYPE>& Mems<TYPE>::clear()
{
   REPA(T)T[i].~TYPE();
   Free(_data); _elms=0;
   return T;
}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::del() {return clear();}

T1(TYPE) Int  Mems<TYPE>::elms    ()C {return      _elms;}
T1(TYPE) UInt Mems<TYPE>::elmSize ()C {return SIZE(TYPE);}
T1(TYPE) UInt Mems<TYPE>::memUsage()C {return elms()*elmSize();}

T1(TYPE) TYPE* Mems<TYPE>::data      (     ) {                          return _data   ;}
T1(TYPE) TYPE* Mems<TYPE>::addr      (Int i) {return InRange(i, _elms) ?      &_data[i] : NULL;}
T1(TYPE) TYPE& Mems<TYPE>::operator[](Int i) {  RANGE_ASSERT(i, _elms); return _data[i];}
T1(TYPE) TYPE& Mems<TYPE>::first     (     ) {return T[       0];}
T1(TYPE) TYPE& Mems<TYPE>::last      (     ) {return T[elms()-1];}
T1(TYPE) TYPE  Mems<TYPE>::popFirst  (     ) {TYPE temp=first(); remove(0, true); return temp;}
T1(TYPE) TYPE  Mems<TYPE>::pop       (     ) {TYPE temp=last (); removeLast(   ); return temp;}

T1(TYPE) C TYPE* Mems<TYPE>::data      (     )C {return ConstCast(T).data ( );}
T1(TYPE) C TYPE* Mems<TYPE>::addr      (Int i)C {return ConstCast(T).addr (i);}
T1(TYPE) C TYPE& Mems<TYPE>::operator[](Int i)C {return ConstCast(T)      [i];}
T1(TYPE) C TYPE& Mems<TYPE>::first     (     )C {return ConstCast(T).first( );}
T1(TYPE) C TYPE& Mems<TYPE>::last      (     )C {return ConstCast(T).last ( );}

T1(TYPE) TYPE& Mems<TYPE>::operator()(Int i)
{
   if(i< 0     )Exit("i<0 inside Mems::operator()(Int i)");
   if(i>=elms())setNumZero(i+1);
   return T[i];
}
T1(TYPE) TYPE& Mems<TYPE>::New  (     ) {setNum(elms()+1); return last();}
T1(TYPE) TYPE& Mems<TYPE>::NewAt(Int i)
{
   Clamp(i, 0, elms());
   TYPE *temp=Alloc<TYPE>(elms()+1);
   CopyN(temp    , data()  ,        i);
   CopyN(temp+i+1, data()+i, elms()-i);
   Free(_data); _data=temp; _elms++;
   TYPE &elm=T[i]; new(&elm)TYPE; return elm;
}

T1(TYPE) Int Mems<TYPE>::index(C TYPE *elm)C
{
   UIntPtr e=(UIntPtr)elm   ,
           d=(UIntPtr)data();
   if(e>=d && e<d+elms()*elmSize())return (e-d)/elmSize();
   return -1;
}
T1(TYPE) Bool Mems<TYPE>::contains(C TYPE *elm)C {return index(elm)!=-1;}

T1(TYPE) Mems<TYPE>& Mems<TYPE>::remove(Int i, Bool /*keep_order*/)
{
   if(InRange(i, T))
   {
      T[i].~TYPE();
      TYPE *temp=Alloc<TYPE>(elms()-1);
      CopyN(temp  , data()    ,        i  );
      CopyN(temp+i, data()+i+1, elms()-i-1);
      Free(_data); _data=temp; _elms--;
   }
   return T;
}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::removeLast(                            ) {return remove(elms()-1              );}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::removeData(C TYPE *elm, Bool keep_order) {return remove(index(elm), keep_order);}

T1(TYPE) Mems<TYPE>& Mems<TYPE>::setNum(Int num)
{
   MAX(num, 0);
   if (num>elms()) // add new elements
   {
      Int old_elms=elms();
      TYPE *temp=Alloc<TYPE>(num);
      CopyN(temp, data(), elms());
      Free (_data); _data=temp; _elms=num;
      for(Int i=old_elms; i<elms(); i++)new(&T[i])TYPE;
   }else
   if(num<elms()) // remove elements
   {
      for(Int i=num; i<elms(); i++)T[i].~TYPE();
      TYPE *temp=Alloc<TYPE>(num);
      CopyN(temp, data(), num);
      Free (_data); _data=temp; _elms=num;
   }
   return T;
}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::setNumZero(Int num)
{
   MAX(num, 0);
   if (num>elms()) // add new elements
   {
      Int old_elms=elms();
      TYPE *temp=Alloc<TYPE>(num);
      CopyN(temp       , data(),     elms());
      ZeroN(temp+elms(),         num-elms());
      Free (_data); _data=temp; _elms=num;
      for(Int i=old_elms; i<elms(); i++)new(&T[i])TYPE;
   }else
   if(num<elms()) // remove elements
   {
      for(Int i=num; i<elms(); i++)T[i].~TYPE();
      TYPE *temp=Alloc<TYPE>(num);
      CopyN(temp, data(), num);
      Free (_data); _data=temp; _elms=num;
   }
   return T;
}
T1(TYPE) Int Mems<TYPE>::addNum(Int num) {Int index=elms(); if(num>0)setNum(elms()+num); return index;}

T1(TYPE) T1(VALUE)   Bool Mems<TYPE>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _BinarySearch(data(), elms(), elmSize(), &value, index, (Int(*)(CPtr, CPtr))compare);}

T1(TYPE) Mems<TYPE>& Mems<TYPE>::sort(Int compare(C TYPE &a, C TYPE &b)) {_Sort(data(), elms(), elmSize(), (Int(*)(CPtr, CPtr))compare); return T;}

T1(TYPE) Mems<TYPE>& Mems<TYPE>::  reverseOrder(                      ) {  _ReverseOrder(data(), elms(), elmSize()                ); return T;}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::randomizeOrder(                      ) {_RandomizeOrder(data(), elms(), elmSize()                ); return T;}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::   rotateOrder(Int offset            ) {   _RotateOrder(data(), elms(), elmSize(), offset        ); return T;}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::     moveElm  (Int elm, Int new_index) {     _MoveElm  (data(), elms(), elmSize(), elm, new_index); return T;}
T1(TYPE) Mems<TYPE>& Mems<TYPE>::     swapOrder(Int i, Int j          ) {if(InRange(i, T) && InRange(j, T))Swap(_data[i], _data[j]); return T;}

T1(TYPE)                    Mems<TYPE>& Mems<TYPE>::operator=(C Mems<TYPE      > &src) {if(this!=&src     ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
T1(TYPE)                    Mems<TYPE>& Mems<TYPE>::operator=(C Memc<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Mems<TYPE>& Mems<TYPE>::operator=(C Memt<TYPE, size> &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Mems<TYPE>& Mems<TYPE>::operator=(C Memb<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Mems<TYPE>& Mems<TYPE>::operator=(C Memx<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Mems<TYPE>& Mems<TYPE>::operator=(C Meml<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Mems<TYPE>& Mems<TYPE>::operator=(C Memp<TYPE, size> &src) {if(this!=src._mems){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

T1(TYPE) void Mems<TYPE>::save(File &f)C {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
T1(TYPE) void Mems<TYPE>::save(File &f)  {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
T1(TYPE) Bool Mems<TYPE>::load(File &f)  {clear().setNum(f.decUIntV(     )); FREPA(T)if(!T[i].load(f))return false; return true;}

T1(TYPE) T1(USER) void Mems<TYPE>::save(File &f, C USER &user)C {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f, user)                          ;}
T1(TYPE) T1(USER) Bool Mems<TYPE>::load(File &f, C USER &user)  {clear().setNum(f.decUIntV(     )); FREPA(T)if(!T[i].load(f, user))return false; return true;}

T1(TYPE) void Mems<TYPE>::saveRaw(File &f)C {       f.cmpUIntV(elms()); f.putN(data(), elms());}
T1(TYPE) Bool Mems<TYPE>::loadRaw(File &f)  {setNum(f.decUIntV(     )); f.getN(data(), elms()); return true;}

T1(TYPE) Mems<TYPE>::~Mems(           ) {del();}
T1(TYPE) Mems<TYPE>:: Mems(           ) {_data=NULL; _elms=0;}
T1(TYPE) Mems<TYPE>:: Mems(C Mems &src) {_data=NULL; _elms=0; T=src;}
/******************************************************************************/
// MEMC
/******************************************************************************/
T1(TYPE) Memc<TYPE>& Memc<TYPE>::clear() {_Memc::clear(); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::del  () {_Memc::del  (); return T;}

T1(TYPE) Int  Memc<TYPE>::elms    ()C {return _Memc::elms    ();}
T1(TYPE) UInt Memc<TYPE>::elmSize ()C {return _Memc::elmSize ();}
T1(TYPE) UInt Memc<TYPE>::memUsage()C {return _Memc::memUsage();}

T1(TYPE) TYPE* Memc<TYPE>::data      (     ) {DEBUG_ASSERT(elmSize()==SIZE(TYPE) || elms()<=1, "Memc::data() Can't cast to C++ pointer after using replaceClass."); return (TYPE*)_Memc::data();}
T1(TYPE) TYPE* Memc<TYPE>::addr      (Int i) {return  (TYPE*)_Memc::addr      (i);}
T1(TYPE) TYPE* Memc<TYPE>::addrFirst (     ) {return  (TYPE*)_Memc::addrFirst ( );}
T1(TYPE) TYPE* Memc<TYPE>::addrLast  (     ) {return  (TYPE*)_Memc::addrLast  ( );}
T1(TYPE) TYPE& Memc<TYPE>::operator[](Int i) {return *(TYPE*)_Memc::operator[](i);}
T1(TYPE) TYPE& Memc<TYPE>::operator()(Int i) {return *(TYPE*)_Memc::operator()(i);}
T1(TYPE) TYPE& Memc<TYPE>::first     (     ) {return *(TYPE*)_Memc::first     ( );}
T1(TYPE) TYPE& Memc<TYPE>::last      (     ) {return *(TYPE*)_Memc::last      ( );}
T1(TYPE) TYPE  Memc<TYPE>::popFirst  (     ) {TYPE temp=first(); remove(0, true); return temp;}
T1(TYPE) TYPE  Memc<TYPE>::pop       (     ) {TYPE temp=last (); removeLast(   ); return temp;}
T1(TYPE) TYPE& Memc<TYPE>::New       (     ) {return *(TYPE*)_Memc::New       ( );}
T1(TYPE) TYPE& Memc<TYPE>::NewAt     (Int i) {return *(TYPE*)_Memc::NewAt     (i);}

T1(TYPE) C TYPE* Memc<TYPE>::data      (     )C {return ConstCast(T).data     ( );}
T1(TYPE) C TYPE* Memc<TYPE>::addr      (Int i)C {return ConstCast(T).addr     (i);}
T1(TYPE) C TYPE* Memc<TYPE>::addrFirst (     )C {return ConstCast(T).addrFirst( );}
T1(TYPE) C TYPE* Memc<TYPE>::addrLast  (     )C {return ConstCast(T).addrLast ( );}
T1(TYPE) C TYPE& Memc<TYPE>::operator[](Int i)C {return ConstCast(T)          [i];}
T1(TYPE) C TYPE& Memc<TYPE>::first     (     )C {return ConstCast(T).first    ( );}
T1(TYPE) C TYPE& Memc<TYPE>::last      (     )C {return ConstCast(T).last     ( );}

T1(TYPE) Int  Memc<TYPE>::index   (C TYPE *elm)C {return _Memc::index   (elm);}
T1(TYPE) Bool Memc<TYPE>::contains(C TYPE *elm)C {return _Memc::contains(elm);}

T1(TYPE) Memc<TYPE>& Memc<TYPE>::removeLast(                            ) {_Memc::removeLast(               ); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::remove    (  Int   i  , Bool keep_order) {_Memc::remove    (i  , keep_order); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::removeData(C TYPE *elm, Bool keep_order) {_Memc::removeData(elm, keep_order); return T;}

T1(TYPE) Memc<TYPE>& Memc<TYPE>::setNum    (Int num) {       _Memc::setNum    (num); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::setNumZero(Int num) {       _Memc::setNumZero(num); return T;}
T1(TYPE) Int         Memc<TYPE>::addNum    (Int num) {return _Memc::addNum    (num);          }

T1(TYPE) T1(VALUE)   Bool Memc<TYPE>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _Memc::binarySearch(&value, index, (Int(*)(CPtr, CPtr))compare);}

T1(TYPE) Memc<TYPE>& Memc<TYPE>::          sort(Int compare(C TYPE &a, C TYPE &b)) {_Memc::          sort((Int(*)(CPtr, CPtr))compare); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::  reverseOrder(                                 ) {_Memc::  reverseOrder(                           ); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::randomizeOrder(                                 ) {_Memc::randomizeOrder(                           ); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::   rotateOrder(Int offset                       ) {_Memc::   rotateOrder(offset                     ); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::     swapOrder(Int i, Int j                     ) {_Memc::     swapOrder(i, j                       ); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::     moveElm  (Int elm, Int new_index           ) {_Memc::     moveElm  (elm, new_index             ); return T;}

T1(TYPE)                    Memc<TYPE>& Memc<TYPE>::operator=(C Mems<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memc<TYPE>& Memc<TYPE>::operator=(C Memc<TYPE      > &src) {if(this!=&src     ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
T1(TYPE) template<Int size> Memc<TYPE>& Memc<TYPE>::operator=(C Memt<TYPE, size> &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memc<TYPE>& Memc<TYPE>::operator=(C Memb<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memc<TYPE>& Memc<TYPE>::operator=(C Memx<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memc<TYPE>& Memc<TYPE>::operator=(C Meml<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Memc<TYPE>& Memc<TYPE>::operator=(C Memp<TYPE, size> &src) {if(this!=src._memc){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

T1(TYPE) T1(EXTENDED)   Memc<TYPE>& Memc<TYPE>::replaceClass          ()  {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>();           _Memc::_reset(SIZE(EXTENDED), ClassFunc<EXTENDED>::GetNew(), ClassFunc<EXTENDED>::GetDel()); return T;}
T1(TYPE) T1(BASE    )               Memc<TYPE>::operator   Memc<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(  Memc<BASE>*)this;}
T1(TYPE) T1(BASE    )               Memc<TYPE>::operator C Memc<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(C Memc<BASE>*)this;}

T1(TYPE) void Memc<TYPE>::save(File &f)C {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
T1(TYPE) void Memc<TYPE>::save(File &f)  {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
T1(TYPE) Bool Memc<TYPE>::load(File &f)  {clear().setNum(f.decUIntV(     )); FREPA(T)if(!T[i].load(f))return false; return true;}

T1(TYPE) T1(USER) void Memc<TYPE>::save(File &f, C USER &user)C {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f, user)                          ;}
T1(TYPE) T1(USER) Bool Memc<TYPE>::load(File &f, C USER &user)  {clear().setNum(f.decUIntV(     )); FREPA(T)if(!T[i].load(f, user))return false; return true;}

T1(TYPE) void Memc<TYPE>::saveRaw(File &f)C {       _Memc::saveRaw(f);}
T1(TYPE) Bool Memc<TYPE>::loadRaw(File &f)  {return _Memc::loadRaw(f);}

T1(TYPE) Memc<TYPE>::Memc(           ) : _Memc(SIZE(TYPE), ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {}
T1(TYPE) Memc<TYPE>::Memc(C Memc &src) : _Memc(SIZE(TYPE), ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {T=src;}

// MemcAbstract
T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::clear() {_Memc::clear(); return T;}
T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::del  () {_Memc::del  (); return T;}

T1(TYPE) Int  MemcAbstract<TYPE>::elms    ()C {return _Memc::elms    ();}
T1(TYPE) UInt MemcAbstract<TYPE>::elmSize ()C {return _Memc::elmSize ();}
T1(TYPE) UInt MemcAbstract<TYPE>::memUsage()C {return _Memc::memUsage();}

T1(TYPE) TYPE* MemcAbstract<TYPE>::data      (     ) {DEBUG_ASSERT(elmSize()==SIZE(TYPE) || elms()<=1, "MemcAbstract::data() Can't cast to C++ pointer after using replaceClass."); return (TYPE*)_Memc::data();}
T1(TYPE) TYPE* MemcAbstract<TYPE>::addr      (Int i) {return  (TYPE*)_Memc::addr      (i);}
T1(TYPE) TYPE& MemcAbstract<TYPE>::operator[](Int i) {return *(TYPE*)_Memc::operator[](i);}
T1(TYPE) TYPE& MemcAbstract<TYPE>::operator()(Int i) {return *(TYPE*)_Memc::operator()(i);}
T1(TYPE) TYPE& MemcAbstract<TYPE>::first     (     ) {return *(TYPE*)_Memc::first     ( );}
T1(TYPE) TYPE& MemcAbstract<TYPE>::last      (     ) {return *(TYPE*)_Memc::last      ( );}
T1(TYPE) TYPE& MemcAbstract<TYPE>::New       (     ) {return *(TYPE*)_Memc::New       ( );}
T1(TYPE) TYPE& MemcAbstract<TYPE>::NewAt     (Int i) {return *(TYPE*)_Memc::NewAt     (i);}

T1(TYPE) C TYPE* MemcAbstract<TYPE>::data      (     )C {return ConstCast(T).data ( );}
T1(TYPE) C TYPE* MemcAbstract<TYPE>::addr      (Int i)C {return ConstCast(T).addr (i);}
T1(TYPE) C TYPE& MemcAbstract<TYPE>::operator[](Int i)C {return ConstCast(T)      [i];}
T1(TYPE) C TYPE& MemcAbstract<TYPE>::first     (     )C {return ConstCast(T).first( );}
T1(TYPE) C TYPE& MemcAbstract<TYPE>::last      (     )C {return ConstCast(T).last ( );}

T1(TYPE) Int  MemcAbstract<TYPE>::index   (C TYPE *elm)C {return _Memc::index   (elm);}
T1(TYPE) Bool MemcAbstract<TYPE>::contains(C TYPE *elm)C {return _Memc::contains(elm);}

T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::removeLast(                            ) {_Memc::removeLast(               ); return T;}
T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::remove    (  Int   i  , Bool keep_order) {_Memc::remove    (i  , keep_order); return T;}
T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::removeData(C TYPE *elm, Bool keep_order) {_Memc::removeData(elm, keep_order); return T;}

T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::setNum    (Int num) {       _Memc::setNum    (num); return T;}
T1(TYPE) MemcAbstract<TYPE>& MemcAbstract<TYPE>::setNumZero(Int num) {       _Memc::setNumZero(num); return T;}
T1(TYPE) Int                 MemcAbstract<TYPE>::addNum    (Int num) {return _Memc::addNum    (num);          }

T1(TYPE) T1(EXTENDED)   MemcAbstract<TYPE>& MemcAbstract<TYPE>::replaceClass          ()  {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>();           _Memc::_reset(SIZE(EXTENDED), ClassFunc<EXTENDED>::GetNew(), ClassFunc<EXTENDED>::GetDel()); return T;}
T1(TYPE) T1(BASE    )                       MemcAbstract<TYPE>::operator   Memc<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(  Memc<BASE>*)this;}
T1(TYPE) T1(BASE    )                       MemcAbstract<TYPE>::operator C Memc<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(C Memc<BASE>*)this;}

T1(TYPE) MemcAbstract<TYPE>::MemcAbstract() : _Memc(0, NULL, NULL) {}
/******************************************************************************/
// THREAD SAFE MEMC
/******************************************************************************/
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::clear() {_ThreadSafeMemc::clear(); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::del  () {_ThreadSafeMemc::del  (); return T;}

T1(TYPE) Int  ThreadSafeMemc<TYPE>::elms    ()C {return _ThreadSafeMemc::elms    ();}
T1(TYPE) UInt ThreadSafeMemc<TYPE>::elmSize ()C {return _ThreadSafeMemc::elmSize ();}
T1(TYPE) UInt ThreadSafeMemc<TYPE>::memUsage()C {return _ThreadSafeMemc::memUsage();}

T1(TYPE) TYPE* ThreadSafeMemc<TYPE>::lockedData (     ) {DEBUG_ASSERT(elmSize()==SIZE(TYPE) || elms()<=1, "ThreadSafeMemc::data() Can't cast to C++ pointer after using replaceClass."); return (TYPE*)_ThreadSafeMemc::lockedData();}
T1(TYPE) TYPE* ThreadSafeMemc<TYPE>::lockedAddr (Int i) {return  (TYPE*)_ThreadSafeMemc::lockedAddr (i);}
T1(TYPE) TYPE& ThreadSafeMemc<TYPE>::lockedElm  (Int i) {return *(TYPE*)_ThreadSafeMemc::lockedElm  (i);}
T1(TYPE) TYPE& ThreadSafeMemc<TYPE>::lockedFirst(     ) {return *(TYPE*)_ThreadSafeMemc::lockedFirst( );}
T1(TYPE) TYPE& ThreadSafeMemc<TYPE>::lockedLast (     ) {return *(TYPE*)_ThreadSafeMemc::lockedLast ( );}
T1(TYPE) TYPE  ThreadSafeMemc<TYPE>::popFirst   (     ) {CritSectLock csl(_cs); TYPE temp=lockedFirst(); remove(0, true); return temp;}
T1(TYPE) TYPE  ThreadSafeMemc<TYPE>::pop        (     ) {CritSectLock csl(_cs); TYPE temp=lockedLast (); removeLast(   ); return temp;}
T1(TYPE) TYPE& ThreadSafeMemc<TYPE>::lockedNew  (     ) {return *(TYPE*)_ThreadSafeMemc::lockedNew  ( );}
T1(TYPE) TYPE& ThreadSafeMemc<TYPE>::lockedNewAt(Int i) {return *(TYPE*)_ThreadSafeMemc::lockedNewAt(i);}

T1(TYPE) C TYPE* ThreadSafeMemc<TYPE>::lockedData (     )C {return ConstCast(T).lockedData ( );}
T1(TYPE) C TYPE* ThreadSafeMemc<TYPE>::lockedAddr (Int i)C {return ConstCast(T).lockedAddr (i);}
T1(TYPE) C TYPE& ThreadSafeMemc<TYPE>::lockedElm  (Int i)C {return ConstCast(T).lockedElm  (i);}
T1(TYPE) C TYPE& ThreadSafeMemc<TYPE>::lockedFirst(     )C {return ConstCast(T).lockedFirst( );}
T1(TYPE) C TYPE& ThreadSafeMemc<TYPE>::lockedLast (     )C {return ConstCast(T).lockedLast ( );}

T1(TYPE) Int  ThreadSafeMemc<TYPE>::index   (C TYPE *elm)C {return _ThreadSafeMemc::index   (elm);}
T1(TYPE) Bool ThreadSafeMemc<TYPE>::contains(C TYPE *elm)C {return _ThreadSafeMemc::contains(elm);}

T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::removeLast(                            ) {_ThreadSafeMemc::removeLast(               ); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::remove    (  Int   i  , Bool keep_order) {_ThreadSafeMemc::remove    (i  , keep_order); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::removeData(C TYPE *elm, Bool keep_order) {_ThreadSafeMemc::removeData(elm, keep_order); return T;}

T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::setNum    (Int num) {       _ThreadSafeMemc::setNum    (num); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::setNumZero(Int num) {       _ThreadSafeMemc::setNumZero(num); return T;}
T1(TYPE) Int                   ThreadSafeMemc<TYPE>::addNum    (Int num) {return _ThreadSafeMemc::addNum    (num);          }

T1(TYPE) T1(VALUE)   Bool ThreadSafeMemc<TYPE>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _ThreadSafeMemc::binarySearch(&value, index, (Int(*)(CPtr, CPtr))compare);}

T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::          sort(Int compare(C TYPE &a, C TYPE &b)) {_ThreadSafeMemc::          sort((Int(*)(CPtr, CPtr))compare); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::  reverseOrder(                                 ) {_ThreadSafeMemc::  reverseOrder(                           ); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::randomizeOrder(                                 ) {_ThreadSafeMemc::randomizeOrder(                           ); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::   rotateOrder(Int offset                       ) {_ThreadSafeMemc::   rotateOrder(offset                     ); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::     swapOrder(Int i, Int j                     ) {_ThreadSafeMemc::     swapOrder(i, j                       ); return T;}
T1(TYPE) ThreadSafeMemc<TYPE>& ThreadSafeMemc<TYPE>::     moveElm  (Int elm, Int new_index           ) {_ThreadSafeMemc::     moveElm  (elm, new_index             ); return T;}

T1(TYPE) void ThreadSafeMemc<TYPE>::  lock()C {_ThreadSafeMemc::  lock();}
T1(TYPE) void ThreadSafeMemc<TYPE>::unlock()C {_ThreadSafeMemc::unlock();}

T1(TYPE) ThreadSafeMemc<TYPE>::ThreadSafeMemc() : _ThreadSafeMemc(SIZE(TYPE), ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {}
/******************************************************************************/
// MEMT
/******************************************************************************/
template<typename TYPE, Int size>   Memt<TYPE, size>& Memt<TYPE, size>::clear()
{
   REPA(T)T[i].~TYPE(); _elms=0;
   return T;
}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::del()
{
   clear();
   if(_data!=(TYPE*)_temp){Free(_data); _max_elms=SIZE(_temp)/elmSize();}
   return T;
}

template<typename TYPE, Int size>   Int    Memt<TYPE, size>::elms    ()C {return      _elms;}
template<typename TYPE, Int size>   UInt   Memt<TYPE, size>::elmSize ()C {return SIZE(TYPE);}
template<typename TYPE, Int size>   UInt   Memt<TYPE, size>::memUsage()C {return SIZE(T) + (_data ? elmSize()*_max_elms : 0);}

template<typename TYPE, Int size>   TYPE*   Memt<TYPE, size>::data      (     ) {                          return _data ? _data    :  (TYPE*)_temp    ;}
template<typename TYPE, Int size>   TYPE&   Memt<TYPE, size>::operator[](Int i) {  RANGE_ASSERT(i, _elms); return _data ? _data[i] : ((TYPE*)_temp)[i];}
template<typename TYPE, Int size>   TYPE*   Memt<TYPE, size>::addr      (Int i) {return InRange(i, _elms) ? &T[i] : NULL;}
template<typename TYPE, Int size>   TYPE&   Memt<TYPE, size>::first     (     ) {return T[       0];}
template<typename TYPE, Int size>   TYPE&   Memt<TYPE, size>::last      (     ) {return T[elms()-1];}
template<typename TYPE, Int size>   TYPE    Memt<TYPE, size>::popFirst  (     ) {TYPE temp=first(); remove(0, true); return temp;}
template<typename TYPE, Int size>   TYPE    Memt<TYPE, size>::pop       (     ) {TYPE temp=last (); removeLast(   ); return temp;}

template<typename TYPE, Int size>   C TYPE*   Memt<TYPE, size>::data      (     )C {return ConstCast(T).data ( );}
template<typename TYPE, Int size>   C TYPE*   Memt<TYPE, size>::addr      (Int i)C {return ConstCast(T).addr (i);}
template<typename TYPE, Int size>   C TYPE&   Memt<TYPE, size>::operator[](Int i)C {return ConstCast(T)      [i];}
template<typename TYPE, Int size>   C TYPE&   Memt<TYPE, size>::first     (     )C {return ConstCast(T).first( );}
template<typename TYPE, Int size>   C TYPE&   Memt<TYPE, size>::last      (     )C {return ConstCast(T).last ( );}

template<typename TYPE, Int size>   TYPE&   Memt<TYPE, size>::operator()(Int i)
{
   if(i< 0     )Exit("i<0 inside Memt::operator()(Int i)");
   if(i>=elms())setNumZero(i+1);
   return T[i];
}
template<typename TYPE, Int size>   TYPE&   Memt<TYPE, size>::New  (     ) {setNum(elms()+1); return last();}
template<typename TYPE, Int size>   TYPE&   Memt<TYPE, size>::NewAt(Int i)
{
   Clamp(i, 0, elms());
   Int old_elms=elms(); _elms++;
   if(elms()>_max_elms)
   {
     _max_elms=CeilPow2(elms());
      Ptr next=Alloc(_max_elms*elmSize());
      Copy((Byte*)next                , &T[0],           i *elmSize());
      Copy((Byte*)next+(i+1)*elmSize(), &T[i], (old_elms-i)*elmSize());
      if(_data!=(TYPE*)_temp)Free(_data); _data=(TYPE*)next;
   }else
   if(i<old_elms)
   {
      Copy(&T[i+1], &T[i], (old_elms-i)*elmSize());
   }
   TYPE &elm=T[i]; new(&elm)TYPE; return elm;
}

template<typename TYPE, Int size>   Int   Memt<TYPE, size>::index(C TYPE *elm)C
{
   UIntPtr e=(UIntPtr)elm   ,
           d=(UIntPtr)data();
   if(e>=d && e<d+elms()*elmSize())return (e-d)/elmSize();
   return -1;
}
template<typename TYPE, Int size>   Bool   Memt<TYPE, size>::contains(C TYPE *elm)C {return index(elm)!=-1;}

template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::remove(Int i, Bool keep_order)
{
   if(InRange(i, T))
   {
      T[i].~TYPE();
      if(elms()-1>i)
      {
         if(keep_order)Copy(&T[i], &T[     i+1], elmSize()*(elms()-i-1));
         else          Copy(&T[i], &T[elms()-1], elmSize());
      }
     _elms--;
   }
   return T;
}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::removeLast(                            ) {return remove(elms()-1              );}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::removeData(C TYPE *elm, Bool keep_order) {return remove(index(elm), keep_order);}

template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::setNum(Int num)
{
   MAX(num, 0);
   if( num>elms()) // add elements
   {
      Int old_elms=elms(); _elms=num;
      if(elms()>_max_elms)
      {
        _max_elms=CeilPow2(elms());
         Ptr next=Alloc(_max_elms*elmSize());
         Copy(next, data(), old_elms*elmSize());
         if(_data!=(TYPE*)_temp)Free(_data); _data=(TYPE*)next;
      }
      for(Int i=old_elms; i<elms(); i++)new(&T[i])TYPE;
   }else
   if(num<elms()) // remove elements
   {
      for(Int i=num; i<elms(); i++)T[i].~TYPE();
     _elms=num;
   }
   return T;
}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::setNumZero(Int num)
{
   MAX(num, 0);
   if( num>elms()) // add elements
   {
      Int old_elms=elms(); _elms=num;
      if(elms()>_max_elms)
      {
        _max_elms=CeilPow2(elms());
         Ptr next=Alloc(_max_elms*elmSize());
         Copy(next, data(), old_elms*elmSize());
         if(_data!=(TYPE*)_temp)Free(_data); _data=(TYPE*)next;
      }
      Zero(&T[old_elms], elmSize()*(elms()-old_elms));
      for(Int i=old_elms; i<elms(); i++)new(&T[i])TYPE;
   }else
   if(num<elms()) // remove elements
   {
      for(Int i=num; i<elms(); i++)T[i].~TYPE();
     _elms=num;
   }
   return T;
}
template<typename TYPE, Int size>   Int   Memt<TYPE, size>::addNum(Int num) {Int index=elms(); if(num>0)setNum(elms()+num); return index;}

template<typename TYPE, Int size>   T1(VALUE)   Bool   Memt<TYPE, size>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _BinarySearch(data(), elms(), elmSize(), &value, index, (Int(*)(CPtr, CPtr))compare);}

template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::sort(Int compare(C TYPE &a, C TYPE &b)) {_Sort(data(), elms(), elmSize(), (Int(*)(CPtr, CPtr))compare); return T;}

template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::  reverseOrder(                      ) {  _ReverseOrder(data(), elms(), elmSize()                ); return T;}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::randomizeOrder(                      ) {_RandomizeOrder(data(), elms(), elmSize()                ); return T;}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::   rotateOrder(Int offset            ) {   _RotateOrder(data(), elms(), elmSize(), offset        ); return T;}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::     moveElm  (Int elm, Int new_index) {     _MoveElm  (data(), elms(), elmSize(), elm, new_index); return T;}
template<typename TYPE, Int size>   Memt<TYPE, size>&   Memt<TYPE, size>::     swapOrder(Int i, Int j          ) {if(InRange(i, T) && InRange(j, T))        Swap(T[i], T[j]); return T;}

template<typename TYPE, Int size>                       Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Mems<TYPE       > &src) {                         setNum(src.elms()); FREPAO(T)=src[i];  return T;}
template<typename TYPE, Int size>                       Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Memc<TYPE       > &src) {                         setNum(src.elms()); FREPAO(T)=src[i];  return T;}
template<typename TYPE, Int size> template<Int size2>   Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Memt<TYPE, size2> &src) {if(this!=Ptr(&src     )){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int size>                       Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Memt<TYPE       > &src) {if(this!=Ptr(&src     )){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int size>                       Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Memb<TYPE       > &src) {                         setNum(src.elms()); FREPAO(T)=src[i];  return T;}
template<typename TYPE, Int size>                       Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Memx<TYPE       > &src) {                         setNum(src.elms()); FREPAO(T)=src[i];  return T;}
template<typename TYPE, Int size>                       Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Meml<TYPE       > &src) {                         setNum(src.elms()); FREPAO(T)=src[i];  return T;}
template<typename TYPE, Int size> template<Int size2>   Memt<TYPE, size>&   Memt<TYPE, size>::operator=(C Memp<TYPE, size2> &src) {if(this!=Ptr(src._memt)){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

template<typename TYPE, Int size>   void   Memt<TYPE, size>::save(File &f)C {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
template<typename TYPE, Int size>   void   Memt<TYPE, size>::save(File &f)  {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
template<typename TYPE, Int size>   Bool   Memt<TYPE, size>::load(File &f)  {clear().setNum(f.decUIntV(     )); FREPA(T)if(!T[i].load(f))return false; return true;}

template<typename TYPE, Int size>   void   Memt<TYPE, size>::saveRaw(File &f)C {       f.cmpUIntV(elms()) ; f.putN(data(), elms());}
template<typename TYPE, Int size>   Bool   Memt<TYPE, size>::loadRaw(File &f)  {setNum(f.decUIntV(      )); f.getN(data(), elms()); return true;}

template<typename TYPE, Int size>   Memt<TYPE, size>::~Memt(           ) {del();}
template<typename TYPE, Int size>   Memt<TYPE, size>:: Memt(           ) {_data=NULL; _elms=0; _max_elms=SIZE(_temp)/elmSize();}
template<typename TYPE, Int size>   Memt<TYPE, size>:: Memt(C Memt &src) {_data=NULL; _elms=0; _max_elms=SIZE(_temp)/elmSize(); T=src;}
/******************************************************************************/
// MEMB
/******************************************************************************/
T1(TYPE) Memb<TYPE>& Memb<TYPE>::clear() {_Memb::clear(); return T;}
T1(TYPE) Memb<TYPE>& Memb<TYPE>::del  () {_Memb::del  (); return T;}

T1(TYPE) Int  Memb<TYPE>::  elms    ()C {return _Memb::  elms    ();}
T1(TYPE) UInt Memb<TYPE>::  elmSize ()C {return _Memb::  elmSize ();}
T1(TYPE) UInt Memb<TYPE>::blockElms ()C {return _Memb::blockElms ();}
T1(TYPE) UInt Memb<TYPE>::  memUsage()C {return _Memb::  memUsage();}

T1(TYPE) TYPE* Memb<TYPE>::addr      (Int i) {return  (TYPE*)_Memb::addr      (i);}
T1(TYPE) TYPE& Memb<TYPE>::operator[](Int i) {return *(TYPE*)_Memb::operator[](i);}
T1(TYPE) TYPE& Memb<TYPE>::operator()(Int i) {return *(TYPE*)_Memb::operator()(i);}
T1(TYPE) TYPE& Memb<TYPE>::first     (     ) {return *(TYPE*)_Memb::first     ( );}
T1(TYPE) TYPE& Memb<TYPE>::last      (     ) {return *(TYPE*)_Memb::last      ( );}
T1(TYPE) TYPE  Memb<TYPE>::popFirst  (     ) {TYPE temp=first(); remove(0, true); return temp;}
T1(TYPE) TYPE  Memb<TYPE>::pop       (     ) {TYPE temp=last (); removeLast(   ); return temp;}
T1(TYPE) TYPE& Memb<TYPE>::New       (     ) {return *(TYPE*)_Memb::New       ( );}
T1(TYPE) TYPE& Memb<TYPE>::NewAt     (Int i) {return *(TYPE*)_Memb::NewAt     (i);}

T1(TYPE) C TYPE* Memb<TYPE>::addr      (Int i)C {return ConstCast(T).addr (i);}
T1(TYPE) C TYPE& Memb<TYPE>::operator[](Int i)C {return ConstCast(T)      [i];}
T1(TYPE) C TYPE& Memb<TYPE>::first     (     )C {return ConstCast(T).first( );}
T1(TYPE) C TYPE& Memb<TYPE>::last      (     )C {return ConstCast(T).last ( );}

T1(TYPE) Int  Memb<TYPE>::index   (C TYPE *elm)C {return _Memb::index   (elm);}
T1(TYPE) Bool Memb<TYPE>::contains(C TYPE *elm)C {return _Memb::contains(elm);}

T1(TYPE) Memb<TYPE>& Memb<TYPE>::removeLast(                            ) {_Memb::removeLast(               ); return T;}
T1(TYPE) Memb<TYPE>& Memb<TYPE>::remove    (  Int   i  , Bool keep_order) {_Memb::remove    (i  , keep_order); return T;}
T1(TYPE) Memb<TYPE>& Memb<TYPE>::removeData(C TYPE *elm, Bool keep_order) {_Memb::removeData(elm, keep_order); return T;}

T1(TYPE) Memb<TYPE>& Memb<TYPE>::setNum    (Int num) {       _Memb::setNum    (num); return T;}
T1(TYPE) Memb<TYPE>& Memb<TYPE>::setNumZero(Int num) {       _Memb::setNumZero(num); return T;}
T1(TYPE) Int         Memb<TYPE>::addNum    (Int num) {return _Memb::addNum    (num);          }

T1(TYPE) T1(VALUE)   Bool Memb<TYPE>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _BinarySearch(T, &value, index, (Int(*)(CPtr, CPtr))compare);}

T1(TYPE) Memb<TYPE>& Memb<TYPE>::sort(Int compare(C TYPE &a, C TYPE &b)) {_Sort(T, (Int(*)(CPtr, CPtr))compare); return T;}

T1(TYPE) Memb<TYPE>& Memb<TYPE>::reverseOrder(            ) {_Memb::reverseOrder(    ); return T;}
T1(TYPE) Memb<TYPE>& Memb<TYPE>::   swapOrder(Int i, Int j) {_Memb::   swapOrder(i, j); return T;}

T1(TYPE)                    Memb<TYPE>& Memb<TYPE>::operator=(C Mems<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memb<TYPE>& Memb<TYPE>::operator=(C Memc<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Memb<TYPE>& Memb<TYPE>::operator=(C Memt<TYPE, size> &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memb<TYPE>& Memb<TYPE>::operator=(C Memb<TYPE      > &src) {if(this!=&src     ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
T1(TYPE)                    Memb<TYPE>& Memb<TYPE>::operator=(C Memx<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memb<TYPE>& Memb<TYPE>::operator=(C Meml<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Memb<TYPE>& Memb<TYPE>::operator=(C Memp<TYPE, size> &src) {if(this!=src._memb){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

T1(TYPE) T1(EXTENDED) Memb<TYPE>& Memb<TYPE>::replaceClass          ()  {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>();           _Memb::_reset(SIZE(EXTENDED), _block_elms, ClassFunc<EXTENDED>::GetNew(), ClassFunc<EXTENDED>::GetDel()); return T;}
T1(TYPE) T1(BASE    )             Memb<TYPE>::operator   Memb<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(  Memb<BASE>*)this;}
T1(TYPE) T1(BASE    )             Memb<TYPE>::operator C Memb<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(C Memb<BASE>*)this;}

T1(TYPE) void Memb<TYPE>::save(File &f)C {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
T1(TYPE) void Memb<TYPE>::save(File &f)  {               f.cmpUIntV(elms()); FREPA(T)    T[i].save(f)                          ;}
T1(TYPE) Bool Memb<TYPE>::load(File &f)  {clear().setNum(f.decUIntV(     )); FREPA(T)if(!T[i].load(f))return false; return true;}

T1(TYPE) void Memb<TYPE>::saveRaw(File &f)C {       _Memb::saveRaw(f);}
T1(TYPE) Bool Memb<TYPE>::loadRaw(File &f)  {return _Memb::loadRaw(f);}

T1(TYPE) Memb<TYPE>::Memb(Int block_elms) : _Memb(SIZE(TYPE),      block_elms, ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {}
T1(TYPE) Memb<TYPE>::Memb(C Memb &src   ) : _Memb(SIZE(TYPE), src._block_elms, ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {T=src;}

// MembAbstract
T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::clear() {_Memb::clear(); return T;}
T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::del  () {_Memb::del  (); return T;}

T1(TYPE) Int  MembAbstract<TYPE>::  elms   ()C {return _Memb::  elms   ();}
T1(TYPE) UInt MembAbstract<TYPE>::  elmSize()C {return _Memb::  elmSize();}
T1(TYPE) UInt MembAbstract<TYPE>::blockElms()C {return _Memb::blockElms();}

T1(TYPE) TYPE* MembAbstract<TYPE>::addr      (Int i) {return  (TYPE*)_Memb::addr      (i);}
T1(TYPE) TYPE& MembAbstract<TYPE>::operator[](Int i) {return *(TYPE*)_Memb::operator[](i);}
T1(TYPE) TYPE& MembAbstract<TYPE>::operator()(Int i) {return *(TYPE*)_Memb::operator()(i);}
T1(TYPE) TYPE& MembAbstract<TYPE>::first     (     ) {return *(TYPE*)_Memb::first     ( );}
T1(TYPE) TYPE& MembAbstract<TYPE>::last      (     ) {return *(TYPE*)_Memb::last      ( );}
T1(TYPE) TYPE& MembAbstract<TYPE>::New       (     ) {return *(TYPE*)_Memb::New       ( );}
T1(TYPE) TYPE& MembAbstract<TYPE>::NewAt     (Int i) {return *(TYPE*)_Memb::NewAt     (i);}

T1(TYPE) C TYPE* MembAbstract<TYPE>::addr      (Int i)C {return ConstCast(T).addr (i);}
T1(TYPE) C TYPE& MembAbstract<TYPE>::operator[](Int i)C {return ConstCast(T)      [i];}
T1(TYPE) C TYPE& MembAbstract<TYPE>::first     (     )C {return ConstCast(T).first( );}
T1(TYPE) C TYPE& MembAbstract<TYPE>::last      (     )C {return ConstCast(T).last ( );}

T1(TYPE) Int  MembAbstract<TYPE>::index   (C TYPE *elm)C {return _Memb::index   (elm);}
T1(TYPE) Bool MembAbstract<TYPE>::contains(C TYPE *elm)C {return _Memb::contains(elm);}

T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::removeLast(                            ) {_Memb::removeLast(               ); return T;}
T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::remove    (  Int   i  , Bool keep_order) {_Memb::remove    (i  , keep_order); return T;}
T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::removeData(C TYPE *elm, Bool keep_order) {_Memb::removeData(elm, keep_order); return T;}

T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::setNum    (Int num) {       _Memb::setNum    (num); return T;}
T1(TYPE) MembAbstract<TYPE>& MembAbstract<TYPE>::setNumZero(Int num) {       _Memb::setNumZero(num); return T;}
T1(TYPE) Int                 MembAbstract<TYPE>::addNum    (Int num) {return _Memb::addNum    (num);          }

T1(TYPE) T1(EXTENDED) MembAbstract<TYPE>& MembAbstract<TYPE>::replaceClass          ()  {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>();           _Memb::_reset(SIZE(EXTENDED), _block_elms, ClassFunc<EXTENDED>::GetNew(), ClassFunc<EXTENDED>::GetDel()); return T;}
T1(TYPE) T1(BASE    )                     MembAbstract<TYPE>::operator   Memb<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(  Memb<BASE>*)this;}
T1(TYPE) T1(BASE    )                     MembAbstract<TYPE>::operator C Memb<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(C Memb<BASE>*)this;}

T1(TYPE) MembAbstract<TYPE>::MembAbstract(Int block_elms) : _Memb(0, block_elms, NULL, NULL) {}

// MembConst
T1(TYPE) TYPE* MembConst<TYPE>::addr      (Int i)C {return ConstCast(T).Memb<TYPE>::addr      (i);}
T1(TYPE) TYPE& MembConst<TYPE>::operator[](Int i)C {return ConstCast(T).Memb<TYPE>::operator[](i);}
T1(TYPE) TYPE& MembConst<TYPE>::first     (     )C {return ConstCast(T).Memb<TYPE>::first     ( );}
T1(TYPE) TYPE& MembConst<TYPE>::last      (     )C {return ConstCast(T).Memb<TYPE>::last      ( );}

T1(TYPE) T1(BASE) MembConst<TYPE>::operator   MembConst<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE>(); return *(  MembConst<BASE>*)this;}
T1(TYPE) T1(BASE) MembConst<TYPE>::operator C MembConst<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE>(); return *(C MembConst<BASE>*)this;}
/******************************************************************************/
// MEMX
/******************************************************************************/
T1(TYPE) Memx<TYPE>& Memx<TYPE>::clear() {_Memx::clear(); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::del  () {_Memx::del  (); return T;}

T1(TYPE) Int  Memx<TYPE>::  absElms ()C {return _Memx::  absElms ();}
T1(TYPE) Int  Memx<TYPE>::validElms ()C {return _Memx::validElms ();}
T1(TYPE) Int  Memx<TYPE>::     elms ()C {return _Memx::     elms ();}
T1(TYPE) UInt Memx<TYPE>::  elmSize ()C {return _Memx::  elmSize ();}
T1(TYPE) UInt Memx<TYPE>::  memUsage()C {return _Memx::  memUsage();}

T1(TYPE) TYPE& Memx<TYPE>::    absElm(Int i) {return *(TYPE*)_Memx::    absElm(i);}
T1(TYPE) TYPE& Memx<TYPE>::  validElm(Int i) {return *(TYPE*)_Memx::  validElm(i);}
T1(TYPE) TYPE* Memx<TYPE>::      addr(Int i) {return  (TYPE*)_Memx::      addr(i);}
T1(TYPE) TYPE& Memx<TYPE>::operator[](Int i) {return *(TYPE*)_Memx::operator[](i);}
T1(TYPE) TYPE& Memx<TYPE>::     first(     ) {return *(TYPE*)_Memx::     first( );}
T1(TYPE) TYPE& Memx<TYPE>::      last(     ) {return *(TYPE*)_Memx::      last( );}
T1(TYPE) TYPE& Memx<TYPE>::     New  (     ) {return *(TYPE*)_Memx::     New  ( );}
T1(TYPE) TYPE& Memx<TYPE>::     NewAt(Int i) {return *(TYPE*)_Memx::     NewAt(i);}

T1(TYPE) C TYPE& Memx<TYPE>::    absElm(Int i)C {return ConstCast(T).  absElm(i);}
T1(TYPE) C TYPE& Memx<TYPE>::  validElm(Int i)C {return ConstCast(T).validElm(i);}
T1(TYPE) C TYPE* Memx<TYPE>::      addr(Int i)C {return ConstCast(T).    addr(i);}
T1(TYPE) C TYPE& Memx<TYPE>::operator[](Int i)C {return ConstCast(T)         [i];}
T1(TYPE) C TYPE& Memx<TYPE>::     first(     )C {return ConstCast(T).   first( );}
T1(TYPE) C TYPE& Memx<TYPE>::      last(     )C {return ConstCast(T).    last( );}

T1(TYPE) Int  Memx<TYPE>::validToAbsIndex(  Int valid)C {return _Memx::validToAbsIndex(valid);}
T1(TYPE) Int  Memx<TYPE>::absToValidIndex(  Int   abs)C {return _Memx::absToValidIndex(abs  );}
T1(TYPE) Int  Memx<TYPE>::validIndex     (C TYPE *elm)C {return _Memx::validIndex     (elm  );}
T1(TYPE) Int  Memx<TYPE>::  absIndex     (C TYPE *elm)C {return _Memx::  absIndex     (elm  );}
T1(TYPE) Bool Memx<TYPE>::  contains     (C TYPE *elm)C {return _Memx::  contains     (elm  );}

T1(TYPE) Memx<TYPE>& Memx<TYPE>::removeAbs  (  Int   i  , Bool keep_order) {_Memx::removeAbs  (i  , keep_order); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::removeValid(  Int   i  , Bool keep_order) {_Memx::removeValid(i  , keep_order); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::removeData (C TYPE *elm, Bool keep_order) {_Memx::removeData (elm, keep_order); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::removeLast (                            ) {_Memx::removeLast (               ); return T;}

T1(TYPE) T1(VALUE)   Bool Memx<TYPE>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _BinarySearch(T, &value, index, (Int(*)(CPtr, CPtr))compare);}

T1(TYPE) Memx<TYPE>& Memx<TYPE>::sort(Int compare(C TYPE &a, C TYPE &b)) {_Sort(T, (Int(*)(CPtr, CPtr))compare); return T;}

T1(TYPE) Memx<TYPE>& Memx<TYPE>::reverseOrder(                      ) {_Memx::reverseOrder(              ); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::   swapOrder(Int i  , Int j        ) {_Memx::   swapOrder(i  , j        ); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::moveElm     (Int elm, Int new_index) {_Memx::moveElm     (elm, new_index); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::moveToStart (Int elm               ) {_Memx::moveToStart (elm           ); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::moveToEnd   (Int elm               ) {_Memx::moveToEnd   (elm           ); return T;}

T1(TYPE)                    Memx<TYPE>& Memx<TYPE>::operator=(C Mems<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memx<TYPE>& Memx<TYPE>::operator=(C Memc<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Memx<TYPE>& Memx<TYPE>::operator=(C Memt<TYPE, size> &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memx<TYPE>& Memx<TYPE>::operator=(C Memb<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Memx<TYPE>& Memx<TYPE>::operator=(C Memx<TYPE      > &src) {if(this!=&src     ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
T1(TYPE)                    Memx<TYPE>& Memx<TYPE>::operator=(C Meml<TYPE      > &src) {                    setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Memx<TYPE>& Memx<TYPE>::operator=(C Memp<TYPE, size> &src) {if(this!=src._memx){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

T1(TYPE) T1(EXTENDED) Memx<TYPE>& Memx<TYPE>::replaceClass          ()  {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>();           _Memx::_reset(SIZE(EXTENDED), _abs.blockElms(), ClassFunc<EXTENDED>::GetNew(), ClassFunc<EXTENDED>::GetDel()); return T;}
T1(TYPE) T1(BASE    )             Memx<TYPE>::operator   Memx<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(  Memx<BASE>*)this;}
T1(TYPE) T1(BASE    )             Memx<TYPE>::operator C Memx<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE    >(); return *(C Memx<BASE>*)this;}

T1(TYPE) void Memx<TYPE>::save(File &f)C {             f.cmpUIntV(elms()); FREPA(T)T[i].save(f);}
T1(TYPE) void Memx<TYPE>::save(File &f)  {             f.cmpUIntV(elms()); FREPA(T)T[i].save(f);}
T1(TYPE) Bool Memx<TYPE>::load(File &f)  {clear(); REP(f.decUIntV(      ))    if(!New().load(f))return false; return true;}

T1(TYPE) Memx<TYPE>::Memx(Int block_elms) : _Memx(SIZE(TYPE),          block_elms , ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {}
T1(TYPE) Memx<TYPE>::Memx(C Memx &src   ) : _Memx(SIZE(TYPE), src._abs.blockElms(), ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {T=src;}

T1(TYPE) Memx<TYPE>::Memx(Abstract, Int block_elms) : _Memx(0, block_elms, NULL, NULL) {}
/******************************************************************************/
// MEML
/******************************************************************************/
T1(TYPE) Meml<TYPE>& Meml<TYPE>::del  () {_Meml::del  (); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::clear() {_Meml::clear(); return T;}

T1(TYPE) Int  Meml<TYPE>::elms    ()C {return _Meml::elms    ();}
T1(TYPE) UInt Meml<TYPE>::elmSize ()C {return _Meml::elmSize ();}
T1(TYPE) UInt Meml<TYPE>::memUsage()C {return _Meml::memUsage();}

T1(TYPE) TYPE* Meml<TYPE>::addr      (Int       i   ) {return  (TYPE*)_Meml::addr      (i);}
T1(TYPE) TYPE& Meml<TYPE>::operator[](Int       i   ) {return *(TYPE*)_Meml::operator[](i);}
T1(TYPE) TYPE& Meml<TYPE>::operator()(Int       i   ) {return *(TYPE*)_Meml::operator()(i);}
T1(TYPE) TYPE& Meml<TYPE>::operator[](MemlNode *node) {return *(TYPE*) node->data      ( );}
T1(TYPE) TYPE& Meml<TYPE>::New       (              ) {return *(TYPE*)_Meml::New       ( );}
T1(TYPE) TYPE& Meml<TYPE>::NewAt     (Int       i   ) {return *(TYPE*)_Meml::NewAt     (i);}

T1(TYPE) C TYPE* Meml<TYPE>::addr      (Int       i   )C {return ConstCast(T).addr(i   );}
T1(TYPE) C TYPE& Meml<TYPE>::operator[](Int       i   )C {return ConstCast(T)     [i   ];}
T1(TYPE) C TYPE& Meml<TYPE>::operator[](MemlNode *node)C {return ConstCast(T)     [node];}

T1(TYPE) MemlNode* Meml<TYPE>::add      (              ) {return _Meml::add      (    );}
T1(TYPE) MemlNode* Meml<TYPE>::addBefore(MemlNode *node) {return _Meml::addBefore(node);}
T1(TYPE) MemlNode* Meml<TYPE>::addAfter (MemlNode *node) {return _Meml::addAfter (node);}

T1(TYPE) MemlNode* Meml<TYPE>::first()C {return _Meml::first();}
T1(TYPE) MemlNode* Meml<TYPE>::last ()C {return _Meml::last ();}

T1(TYPE) Int  Meml<TYPE>::index   (C TYPE *elm)C {return _Meml::index   (elm);}
T1(TYPE) Bool Meml<TYPE>::contains(C TYPE *elm)C {return _Meml::contains(elm);}

T1(TYPE) Meml<TYPE>& Meml<TYPE>::removeFirst(                Bool keep_order) {_Meml::removeFirst(      keep_order); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::removeLast (                               ) {_Meml::removeLast (                ); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::remove     (MemlNode *node, Bool keep_order) {_Meml::remove     (node, keep_order); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::removeData (C TYPE   *elm , Bool keep_order) {_Meml::removeData (elm , keep_order); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::removeIndex(Int       i   , Bool keep_order) {_Meml::removeIndex(i   , keep_order); return T;}

T1(TYPE) Meml<TYPE>& Meml<TYPE>::setNum    (Int num) {_Meml::setNum    (num); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::setNumZero(Int num) {_Meml::setNumZero(num); return T;}

T1(TYPE) T1(VALUE)   Bool Meml<TYPE>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C {return _BinarySearch(T, &value, index, (Int(*)(CPtr, CPtr))compare);}

T1(TYPE) Meml<TYPE>& Meml<TYPE>::sort(Int compare(C TYPE &a, C TYPE &b)) {_Sort(T, (Int(*)(CPtr, CPtr))compare); return T;}

T1(TYPE) Meml<TYPE>& Meml<TYPE>::reverseOrder(            ) {_Meml::reverseOrder(    ); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::   swapOrder(Int i, Int j) {_Meml::   swapOrder(i, j); return T;}

T1(TYPE)                    Meml<TYPE>& Meml<TYPE>::operator=(C Mems<TYPE      > &src) {                     setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Meml<TYPE>& Meml<TYPE>::operator=(C Memc<TYPE      > &src) {                     setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE) template<Int size> Meml<TYPE>& Meml<TYPE>::operator=(C Memt<TYPE, size> &src) {                     setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Meml<TYPE>& Meml<TYPE>::operator=(C Memb<TYPE      > &src) {                     setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Meml<TYPE>& Meml<TYPE>::operator=(C Memx<TYPE      > &src) {                     setNum(src.elms()); FREPAO(T)=src[i];  return T;}
T1(TYPE)                    Meml<TYPE>& Meml<TYPE>::operator=(C Meml<TYPE      > &src) {if(this!=&src      ){setNum(src.elms()); for(MemlNode *d=first(), *s=src.first(); d && s; d=d->next(), s=s->next())T[d]=src[s];} return T;}
T1(TYPE) template<Int size> Meml<TYPE>& Meml<TYPE>::operator=(C Memp<TYPE, size> &src) {if(this!= src._meml){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

T1(TYPE) void Meml<TYPE>::save(File &f)C {             f.cmpUIntV(elms()); MFREP(T)T[i].save(f);}
T1(TYPE) void Meml<TYPE>::save(File &f)  {             f.cmpUIntV(elms()); MFREP(T)T[i].save(f);}
T1(TYPE) Bool Meml<TYPE>::load(File &f)  {clear(); REP(f.decUIntV(      ))    if(!New().load(f))return false; return true;}

T1(TYPE) Meml<TYPE>::Meml(           ) : _Meml(SIZE(TYPE), ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {}
T1(TYPE) Meml<TYPE>::Meml(C Meml &src) : _Meml(SIZE(TYPE), ClassFunc<TYPE>::GetNew(), ClassFunc<TYPE>::GetDel()) {T=src;}
/******************************************************************************/
// MEMP
/******************************************************************************/
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(     int                             ) {_mode=PTR ; _ptr =NULL; _elms=   0; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(     TYPE             &src           ) {_mode=PTR ; _ptr =&src; _elms=   1; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(     TYPE             *src, Int elms ) {_mode=PTR ; _ptr = src; _elms=elms; return T;}
template<typename TYPE, Int Memt_size> template<Int size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(     TYPE            (&src)    [size]) {_mode=PTR ; _ptr = src; _elms=size; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Mems<TYPE           > &src           ) {_mode=MEMS; _mems=&src; _elms=   0; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Memc<TYPE           > &src           ) {_mode=MEMC; _memc=&src; _elms=   0; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Memt<TYPE, Memt_size> &src           ) {_mode=MEMT; _memt=&src; _elms=   0; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Memb<TYPE           > &src           ) {_mode=MEMB; _memb=&src; _elms=   0; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Memx<TYPE           > &src           ) {_mode=MEMX; _memx=&src; _elms=   0; return T;}
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Meml<TYPE           > &src           ) {_mode=MEML; _meml=&src; _elms=   0; return T;}
#ifdef WINDOWS
template<typename TYPE, Int Memt_size>                      Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::point(Memp<TYPE, Memt_size> &src           ) {_mode=src._mode; _ptr=src._ptr; _elms=src._elms; return T;}
#endif

template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::clear()
{
   switch(_mode)
   {
      case PTR : if(_elms)Exit("Memp.clear does not support PTR mode"); break;
      case MEMS: _mems->clear(); break;
      case MEMC: _memc->clear(); break;
      case MEMT: _memt->clear(); break;
      case MEMB: _memb->clear(); break;
      case MEMX: _memx->clear(); break;
      case MEML: _meml->clear(); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::del()
{
   switch(_mode)
   {
      case PTR : if(_elms)Exit("Memp.del does not support PTR mode"); break;
      case MEMS: _mems->del(); break;
      case MEMC: _memc->del(); break;
      case MEMT: _memt->del(); break;
      case MEMB: _memb->del(); break;
      case MEMX: _memx->del(); break;
      case MEML: _meml->del(); break;
   }
   return T;
}

template<typename TYPE, Int Memt_size>   Int Memp<TYPE, Memt_size>::elms()C
{
   switch(_mode)
   {
      default  : return _elms; // PTR
      case MEMS: return _mems->elms();
      case MEMC: return _memc->elms();
      case MEMT: return _memt->elms();
      case MEMB: return _memb->elms();
      case MEMX: return _memx->elms();
      case MEML: return _meml->elms();
   }
}
template<typename TYPE, Int Memt_size>   UInt Memp<TYPE, Memt_size>::elmSize()C
{
   switch(_mode)
   {
      default  : return SIZE(TYPE); // PTR
      case MEMS: return _mems->elmSize();
      case MEMC: return _memc->elmSize();
      case MEMT: return _memt->elmSize();
      case MEMB: return _memb->elmSize();
      case MEMX: return _memx->elmSize();
      case MEML: return _meml->elmSize();
   }
}
template<typename TYPE, Int Memt_size>   UInt Memp<TYPE, Memt_size>::memUsage()C
{
   switch(_mode)
   {
      default  : return elms()*elmSize(); // PTR
      case MEMS: return _mems->memUsage();
      case MEMC: return _memc->memUsage();
      case MEMT: return _memt->memUsage();
      case MEMB: return _memb->memUsage();
      case MEMX: return _memx->memUsage();
      case MEML: return _meml->memUsage();
   }
}
template<typename TYPE, Int Memt_size>   TYPE* Memp<TYPE, Memt_size>::data()
{
   switch(_mode)
   {
      default  : return _ptr; // PTR
      case MEMS: return _mems->data();
      case MEMC: return _memc->data();
      case MEMT: return _memt->data();
      case MEMB: Exit("Memp.data does not support MEMB mode"); return NULL;
      case MEMX: Exit("Memp.data does not support MEMX mode"); return NULL;
      case MEML: Exit("Memp.data does not support MEML mode"); return NULL;
   }
}
template<typename TYPE, Int Memt_size>   TYPE* Memp<TYPE, Memt_size>::addr(Int i)
{
   switch(_mode)
   {
      default  : return InRange(i, _elms) ? &_ptr[i] : NULL; // PTR
      case MEMS: return _mems->addr(i);
      case MEMC: return _memc->addr(i);
      case MEMT: return _memt->addr(i);
      case MEMB: return _memb->addr(i);
      case MEMX: return _memx->addr(i);
      case MEML: return _meml->addr(i);
   }
}
template<typename TYPE, Int Memt_size>   TYPE& Memp<TYPE, Memt_size>::operator[](Int i)
{
   switch(_mode)
   {
      default  : RANGE_ASSERT(i, _elms); return _ptr[i]; // PTR
      case MEMS: return (*_mems)[i];
      case MEMC: return (*_memc)[i];
      case MEMT: return (*_memt)[i];
      case MEMB: return (*_memb)[i];
      case MEMX: return (*_memx)[i];
      case MEML: return (*_meml)[i];
   }
}
template<typename TYPE, Int Memt_size>   TYPE& Memp<TYPE, Memt_size>::operator()(Int i)
{
   switch(_mode)
   {
      default  : if(!InRange(i, _elms))Exit("Memp.operator(Int) PTR mode out of range"); return _ptr[i]; // PTR
      case MEMS: return (*_mems)(i);
      case MEMC: return (*_memc)(i);
      case MEMT: return (*_memt)(i);
      case MEMB: return (*_memb)(i);
      case MEMX: Exit("Memp.operator(Int) does not support MEMX mode"); return *(TYPE*)NULL;
      case MEML: return (*_meml)(i);
   }
}
template<typename TYPE, Int Memt_size>   TYPE& Memp<TYPE, Memt_size>::first() {return T[0       ];}
template<typename TYPE, Int Memt_size>   TYPE& Memp<TYPE, Memt_size>::last () {return T[elms()-1];}

template<typename TYPE, Int Memt_size>   C TYPE* Memp<TYPE, Memt_size>::data      (     )C {return ConstCast(T).data ( );}
template<typename TYPE, Int Memt_size>   C TYPE* Memp<TYPE, Memt_size>::addr      (Int i)C {return ConstCast(T).addr (i);}
template<typename TYPE, Int Memt_size>   C TYPE& Memp<TYPE, Memt_size>::operator[](Int i)C {return ConstCast(T)      [i];}
template<typename TYPE, Int Memt_size>   C TYPE& Memp<TYPE, Memt_size>::first     (     )C {return ConstCast(T).first( );}
template<typename TYPE, Int Memt_size>   C TYPE& Memp<TYPE, Memt_size>::last      (     )C {return ConstCast(T).last ( );}

template<typename TYPE, Int Memt_size>   TYPE& Memp<TYPE, Memt_size>::New()
{
   switch(_mode)
   {
      default  : Exit("Memp.New does not support PTR mode"); return *(TYPE*)NULL; // PTR
      case MEMS: return _mems->New();
      case MEMC: return _memc->New();
      case MEMT: return _memt->New();
      case MEMB: return _memb->New();
      case MEMX: return _memx->New();
      case MEML: return _meml->New();
   }
}
template<typename TYPE, Int Memt_size>   TYPE& Memp<TYPE, Memt_size>::NewAt(Int i)
{
   switch(_mode)
   {
      default  : Exit("Memp.NewAt does not support PTR mode"); return *(TYPE*)NULL; // PTR
      case MEMS: return _mems->NewAt(i);
      case MEMC: return _memc->NewAt(i);
      case MEMT: return _memt->NewAt(i);
      case MEMB: return _memb->NewAt(i);
      case MEMX: return _memx->NewAt(i);
      case MEML: return _meml->NewAt(i);
   }
}
template<typename TYPE, Int Memt_size>   Int Memp<TYPE, Memt_size>::index(C TYPE *elm)C
{
   switch(_mode)
   {
      case PTR : {Int i=elm-_ptr; if(InRange(i, _elms))return i;} break;
      case MEMS: return _mems->index(elm);
      case MEMC: return _memc->index(elm);
      case MEMT: return _memt->index(elm);
      case MEMB: return _memb->index(elm);
      case MEMX: return _memx->validIndex(elm);
      case MEML: return _meml->index(elm);
   }
   return -1;
}
template<typename TYPE, Int Memt_size>   Bool Memp<TYPE, Memt_size>::contains(C TYPE *elm)C {return index(elm)>=0;}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::removeLast()
{
   switch(_mode)
   {
      case PTR : if(_elms)Exit("Memp.removeLast does not support PTR mode"); break;
      case MEMS: _mems->removeLast(); break;
      case MEMC: _memc->removeLast(); break;
      case MEMT: _memt->removeLast(); break;
      case MEMB: _memb->removeLast(); break;
      case MEMX: _memx->removeLast(); break;
      case MEML: _meml->removeLast(); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::remove(Int i, Bool keep_order)
{
   switch(_mode)
   {
      case PTR : if(InRange(i, _elms))Exit("Memp.remove does not support PTR mode"); break;
      case MEMS: _mems->remove     (i, keep_order); break;
      case MEMC: _memc->remove     (i, keep_order); break;
      case MEMT: _memt->remove     (i, keep_order); break;
      case MEMB: _memb->remove     (i, keep_order); break;
      case MEMX: _memx->removeValid(i, keep_order); break;
      case MEML: _meml->removeIndex(i            ); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::removeData(C TYPE *elm, Bool keep_order)
{
   switch(_mode)
   {
      case PTR : if(InRange(index(elm), _elms))Exit("Memp.removeData does not support PTR mode"); break;
      case MEMS: _mems->removeData(elm            ); break;
      case MEMC: _memc->removeData(elm, keep_order); break;
      case MEMT: _memt->removeData(elm, keep_order); break;
      case MEMB: _memb->removeData(elm, keep_order); break;
      case MEMX: _memx->removeData(elm, keep_order); break;
      case MEML: _meml->removeData(elm            ); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::setNum(Int num)
{
   switch(_mode)
   {
      case PTR : if(_elms!=num)Exit("Memp.setNum does not support PTR mode"); break;
      case MEMS: _mems->setNum(num); break;
      case MEMC: _memc->setNum(num); break;
      case MEMT: _memt->setNum(num); break;
      case MEMB: _memb->setNum(num); break;
      case MEMX: _memx->setNum(num); break;
      case MEML: _meml->setNum(num); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>& Memp<TYPE, Memt_size>::setNumZero(Int num)
{
   switch(_mode)
   {
      case PTR : if(_elms!=num)Exit("Memp.setNumZero does not support PTR mode"); break;
      case MEMS: _mems->setNumZero(num); break;
      case MEMC: _memc->setNumZero(num); break;
      case MEMT: _memt->setNumZero(num); break;
      case MEMB: _memb->setNumZero(num); break;
      case MEMX:  Exit("Memp.setNumZero does not support MEMX mode"); break;
      case MEML: _meml->setNumZero(num); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Int Memp<TYPE, Memt_size>::addNum(Int num)
{
   switch(_mode)
   {
      default  : if(num>0)Exit("Memp.addNum does not support PTR mode"); return _elms; // PTR
      case MEMS: return _mems->addNum(num);
      case MEMC: return _memc->addNum(num);
      case MEMT: return _memt->addNum(num);
      case MEMB: return _memb->addNum(num);
      case MEMX: return _memx->addNum(num);
      case MEML: return _meml->addNum(num);
   }
}

template<typename TYPE, Int Memt_size> T1(VALUE)   Bool Memp<TYPE, Memt_size>::binarySearch(C VALUE &value, Int &index, Int compare(C TYPE &a, C VALUE &b))C
{
   switch(_mode)
   {
      default  : return        BinarySearch(_ptr, _elms, value, index, compare); // PTR
      case MEMS: return _mems->binarySearch(             value, index, compare);
      case MEMC: return _memc->binarySearch(             value, index, compare);
      case MEMT: return _memt->binarySearch(             value, index, compare);
      case MEMB: return _memb->binarySearch(             value, index, compare);
      case MEMX: return _memx->binarySearch(             value, index, compare);
      case MEML: return _meml->binarySearch(             value, index, compare);
   }
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::sort(Int compare(C TYPE &a, C TYPE &b))
{
   switch(_mode)
   {
      case PTR :        Sort(_ptr, _elms, compare); break;
      case MEMS: _mems->sort(             compare); break;
      case MEMC: _memc->sort(             compare); break;
      case MEMT: _memt->sort(             compare); break;
      case MEMB: _memb->sort(             compare); break;
      case MEMX: _memx->sort(             compare); break;
      case MEML: _meml->sort(             compare); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::reverseOrder()
{
   switch(_mode)
   {
      case PTR :        ReverseOrder(_ptr, _elms); break;
      case MEMS: _mems->reverseOrder(           ); break;
      case MEMC: _memc->reverseOrder(           ); break;
      case MEMT: _memt->reverseOrder(           ); break;
      case MEMB: _memb->reverseOrder(           ); break;
      case MEMX: _memx->reverseOrder(           ); break;
      case MEML: _meml->reverseOrder(           ); break;
   }
   return T;
}
template<typename TYPE, Int Memt_size>   Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::swapOrder(Int i, Int j)
{
   switch(_mode)
   {
      case PTR : if(InRange(i, _elms) && InRange(j, _elms))Swap(&T[i], &T[j], elmSize()); break;
      case MEMS: _mems->swapOrder(i, j); break;
      case MEMC: _memc->swapOrder(i, j); break;
      case MEMT: _memt->swapOrder(i, j); break;
      case MEMB: _memb->swapOrder(i, j); break;
      case MEMX: _memx->swapOrder(i, j); break;
      case MEML: _meml->swapOrder(i, j); break;
   }
   return T;
}

template<typename TYPE, Int Memt_size>                        Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Mems<TYPE      > &src) {if(    _mems !=    &src              ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>                        Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Memc<TYPE      > &src) {if(    _memc !=    &src              ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>   template<Int size>   Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Memt<TYPE, size> &src) {if(Ptr(_memt)!=Ptr(&src)             ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>                        Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Memb<TYPE      > &src) {if(    _memb !=    &src              ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>                        Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Memx<TYPE      > &src) {if(    _memx !=    &src              ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>                        Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Meml<TYPE      > &src) {if(    _meml !=    &src              ){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>                        Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Memp<TYPE      > &src) {if(_ptr!=src._ptr || _elms!=src._elms){setNum(src.elms()); FREPAO(T)=src[i];} return T;}
template<typename TYPE, Int Memt_size>   template<Int size>   Memp<TYPE, Memt_size>&   Memp<TYPE, Memt_size>::operator=(C Memp<TYPE, size> &src) {if(_ptr!=src._ptr || _elms!=src._elms){setNum(src.elms()); FREPAO(T)=src[i];} return T;}

template<typename TYPE, Int Memt_size>        Memp<TYPE, Memt_size>::operator Bool()C {return _mode!=PTR || elms();}
template<typename TYPE, Int Memt_size>   Bool Memp<TYPE, Memt_size>::resizable    ()C {return _mode!=PTR;}

template<typename TYPE, Int Memt_size>   void Memp<TYPE, Memt_size>::save(File &f)C
{
   switch(_mode)
   {
      default  : f.cmpUIntV(elms()); FREPA(T)T[i].save(f); break; // PTR
      case MEMS: _mems->save(f); break;
      case MEMC: _memc->save(f); break;
      case MEMT: _memt->save(f); break;
      case MEMB: _memb->save(f); break;
      case MEMX: _memx->save(f); break;
      case MEML: _meml->save(f); break;
   }
}
template<typename TYPE, Int Memt_size>   void Memp<TYPE, Memt_size>::save(File &f)
{
   switch(_mode)
   {
      default  : f.cmpUIntV(elms()); FREPA(T)T[i].save(f); break; // PTR
      case MEMS: _mems->save(f); break;
      case MEMC: _memc->save(f); break;
      case MEMT: _memt->save(f); break;
      case MEMB: _memb->save(f); break;
      case MEMX: _memx->save(f); break;
      case MEML: _meml->save(f); break;
   }
}
template<typename TYPE, Int Memt_size>   Bool Memp<TYPE, Memt_size>::load(File &f)
{
   switch(_mode)
   {
      default  : if(f.decUIntV()!=elms())return false; FREPA(T)if(!T[i].load(f))return false; return true; // PTR
      case MEMS: return _mems->load(f);
      case MEMC: return _memc->load(f);
      case MEMT: return _memt->load(f);
      case MEMB: return _memb->load(f);
      case MEMX: return _memx->load(f);
      case MEML: return _meml->load(f);
   }
}

template<typename TYPE, Int Memt_size>   void Memp<TYPE, Memt_size>::saveRaw(File &f)C
{
   switch(_mode)
   {
      default  : f.cmpUIntV(elms()); f.putN(_ptr, elms()); break; // PTR
      case MEMS: _mems->saveRaw(f); break;
      case MEMC: _memc->saveRaw(f); break;
      case MEMT: _memt->saveRaw(f); break;
      case MEMB: _memb->saveRaw(f); break;
      case MEMX: _memx->saveRaw(f); break;
      case MEML: _meml->saveRaw(f); break;
   }
}
template<typename TYPE, Int Memt_size>   Bool Memp<TYPE, Memt_size>::loadRaw(File &f)
{
   switch(_mode)
   {
      default  : if(f.decUIntV()!=elms())return false; f.getN(_ptr, elms()); return true; // PTR
      case MEMS: return _mems->loadRaw(f);
      case MEMC: return _memc->loadRaw(f);
      case MEMT: return _memt->loadRaw(f);
      case MEMB: return _memb->loadRaw(f);
      case MEMX: return _memx->loadRaw(f);
      case MEML: return _meml->loadRaw(f);
   }
}

#ifdef HAS_MOVE_CONSTRUCTOR
T1(TYPE) Mems<TYPE>& Mems<TYPE>::operator=(Mems<TYPE> &&src)                           {Swap(T, src); return T;}
T1(TYPE) Memc<TYPE>& Memc<TYPE>::operator=(Memc<TYPE> &&src)                           {Swap(T, src); return T;}
T1(TYPE) Memb<TYPE>& Memb<TYPE>::operator=(Memb<TYPE> &&src)                           {Swap(T, src); return T;}
T1(TYPE) Memx<TYPE>& Memx<TYPE>::operator=(Memx<TYPE> &&src)                           {Swap(T, src); return T;}
T1(TYPE) Meml<TYPE>& Meml<TYPE>::operator=(Meml<TYPE> &&src)                           {Swap(T, src); return T;}
T1(TYPE)             Mems<TYPE>::Mems     (Mems       &&src) : _data(NULL), _elms(0)   {Swap(T, src);}
T1(TYPE)             Memc<TYPE>::Memc     (Memc       &&src) : _Memc(0,    NULL, NULL) {Swap(T, src);}
T1(TYPE)             Memb<TYPE>::Memb     (Memb       &&src) : _Memb(0, 0, NULL, NULL) {Swap(T, src);}
T1(TYPE)             Memx<TYPE>::Memx     (Memx       &&src) : _Memx(0, 0, NULL, NULL) {Swap(T, src);}
T1(TYPE)             Meml<TYPE>::Meml     (Meml       &&src) : _Meml(0,    NULL, NULL) {Swap(T, src);}
#endif
/******************************************************************************/
// CACHE
/******************************************************************************/
T1(TYPE)  Cache<TYPE>&  Cache<TYPE>::clear        (               ) {                   _Cache::clear        (         ); return T;}
T1(TYPE)  Cache<TYPE>&  Cache<TYPE>::del          (               ) {                   _Cache::del          (         ); return T;}
T1(TYPE)  CACHE_MODE    Cache<TYPE>::mode         (CACHE_MODE mode) {return (CACHE_MODE)_Cache::mode         (mode     );          }
T1(TYPE)  Cache<TYPE>&  Cache<TYPE>::caseSensitive(Bool  sensitive) {                   _Cache::caseSensitive(sensitive); return T;}

T1(TYPE)  TYPE*  Cache<TYPE>::find      (C Str &file, CChar *path) {return (TYPE*)_Cache::_find   (file, path, false);}
T1(TYPE)  TYPE*  Cache<TYPE>::find      (C UID &id  , CChar *path) {return (TYPE*)_Cache::_find   (id  , path, false);}
T1(TYPE)  TYPE*  Cache<TYPE>::get       (C Str &file, CChar *path) {return (TYPE*)_Cache::_get    (file, path, false);}
T1(TYPE)  TYPE*  Cache<TYPE>::get       (C UID &id  , CChar *path) {return (TYPE*)_Cache::_get    (id  , path, false);}
T1(TYPE)  TYPE*  Cache<TYPE>::operator()(C Str &file, CChar *path) {return (TYPE*)_Cache::_require(file, path, false);}
T1(TYPE)  TYPE*  Cache<TYPE>::operator()(C UID &id  , CChar *path) {return (TYPE*)_Cache::_require(id  , path, false);}

T1(TYPE)  CChar*  Cache<TYPE>::name    (C TYPE *data, CChar *path )C {return _Cache::_name    (data, path );}
T1(TYPE)  UID     Cache<TYPE>::id      (C TYPE *data              )C {return _Cache::_id      (data       );}
T1(TYPE)  Bool    Cache<TYPE>::contains(C TYPE *data              )C {return _Cache::_contains(data       );}
T1(TYPE)  Bool    Cache<TYPE>::dummy   (C TYPE *data              )C {return _Cache::_dummy   (data       );}
T1(TYPE)  void    Cache<TYPE>::dummy   (C TYPE *data, Bool   dummy)  {       _Cache::_dummy   (data, dummy);}

T1(TYPE)  Int                         Cache<TYPE>::  elms     (     )C {return                             _Cache::  elms     ( );}
T1(TYPE)  void                        Cache<TYPE>::  lock     (     )C {                                   _Cache::  lock     ( );}
T1(TYPE)  typename Cache<TYPE>::Elm&  Cache<TYPE>::  lockedElm(Int i)  {return (typename Cache<TYPE>::Elm&)_Cache::  lockedElm(i);}
T1(TYPE)  void                        Cache<TYPE>::unlock     (     )C {                                   _Cache::unlock     ( );}

T1(TYPE)  void  Cache<TYPE>::removeData(C TYPE *data) {return _Cache::_removeData(data);}

T1(TYPE)  void  Cache<TYPE>::update() {return _Cache::update();}

T1(TYPE) T1(EXTENDED)  Cache<TYPE>&  Cache<TYPE>::replaceClass() {ASSERT_BASE_EXTENDED<TYPE, EXTENDED>(); lock(); del(); _data_offset=OFFSET(typename Cache<EXTENDED>::Elm, data); _desc_offset=OFFSET(typename Cache<EXTENDED>::Elm, desc); _memx.replaceClass<typename Cache<EXTENDED>::Elm>(); unlock(); return T;}

T1(TYPE)  Cache<TYPE>&  Cache<TYPE>::operator=(C Cache<TYPE> &src) {if(this!=&src){lock(); src.lock(); _from(src); FREPA(_memx)_clearRef((Elm&)_memx[i]=(C Elm&)src._memx[i]); src.unlock(); unlock();} return T;}

T1(TYPE) Cache<TYPE>::Cache(CChar8 *name, Int block_elms) : _Cache(name, block_elms, ClassFunc<TYPE>::Load) {replaceClass<TYPE>();}
/******************************************************************************/
// CACHE COUNTED
/******************************************************************************/
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::clear         (               ) {       CACHE.clear         (         ); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::del           (               ) {       CACHE.del           (         ); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CACHE_MODE                  CacheCounted<TYPE,CACHE>::mode          (CACHE_MODE mode) {return CACHE.mode          (mode     );          }
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::caseSensitive (Bool  sensitive) {       CACHE.caseSensitive (sensitive); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::delayRemove   (Flt   time     ) {       CACHE.delayRemove   (time     ); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::delayRemoveNow(               ) {       CACHE.delayRemoveNow(         ); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::delayRemoveInc(               ) {       CACHE.delayRemoveInc(         ); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheCounted<TYPE,CACHE>&   CacheCounted<TYPE,CACHE>::delayRemoveDec(               ) {       CACHE.delayRemoveDec(         ); return T;}

template<typename TYPE, Cache<TYPE> &CACHE>   TYPE*   CacheCounted<TYPE,CACHE>::find      (C Str &file, CChar *path)C {return (TYPE*)CACHE._find   (file, path, false);}
template<typename TYPE, Cache<TYPE> &CACHE>   TYPE*   CacheCounted<TYPE,CACHE>::find      (C UID &id  , CChar *path)C {return (TYPE*)CACHE._find   (id  , path, false);}
template<typename TYPE, Cache<TYPE> &CACHE>   TYPE*   CacheCounted<TYPE,CACHE>::get       (C Str &file, CChar *path)  {return (TYPE*)CACHE._get    (file, path, false);}
template<typename TYPE, Cache<TYPE> &CACHE>   TYPE*   CacheCounted<TYPE,CACHE>::get       (C UID &id  , CChar *path)  {return (TYPE*)CACHE._get    (id  , path, false);}
template<typename TYPE, Cache<TYPE> &CACHE>   TYPE*   CacheCounted<TYPE,CACHE>::operator()(C Str &file, CChar *path)  {return (TYPE*)CACHE._require(file, path, false);}
template<typename TYPE, Cache<TYPE> &CACHE>   TYPE*   CacheCounted<TYPE,CACHE>::operator()(C UID &id  , CChar *path)  {return (TYPE*)CACHE._require(id  , path, false);}

template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>   CacheCounted<TYPE,CACHE>::ptrFind   (C Str &file, CChar *path)C {return _Cache::Dummy(CACHE._find   (file, path, true));}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>   CacheCounted<TYPE,CACHE>::ptrFind   (C UID &id  , CChar *path)C {return _Cache::Dummy(CACHE._find   (id  , path, true));}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>   CacheCounted<TYPE,CACHE>::ptrGet    (C Str &file, CChar *path)  {return _Cache::Dummy(CACHE._get    (file, path, true));}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>   CacheCounted<TYPE,CACHE>::ptrGet    (C UID &id  , CChar *path)  {return _Cache::Dummy(CACHE._get    (id  , path, true));}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>   CacheCounted<TYPE,CACHE>::ptrRequire(C Str &file, CChar *path)  {return _Cache::Dummy(CACHE._require(file, path, true));}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>   CacheCounted<TYPE,CACHE>::ptrRequire(C UID &id  , CChar *path)  {return _Cache::Dummy(CACHE._require(id  , path, true));}

template<typename TYPE, Cache<TYPE> &CACHE>   CChar*   CacheCounted<TYPE,CACHE>::name    (C TYPE                    *data, CChar *path)C {return CACHE._name    (data  , path );}
template<typename TYPE, Cache<TYPE> &CACHE>   CChar*   CacheCounted<TYPE,CACHE>::name    (C CacheElmPtr<TYPE,CACHE> &data, CChar *path)C {return CACHE._name    (data(), path );}
template<typename TYPE, Cache<TYPE> &CACHE>   UID      CacheCounted<TYPE,CACHE>::id      (C TYPE                    *data             )C {return CACHE._id      (data         );}
template<typename TYPE, Cache<TYPE> &CACHE>   UID      CacheCounted<TYPE,CACHE>::id      (C CacheElmPtr<TYPE,CACHE> &data             )C {return CACHE._id      (data()       );}
template<typename TYPE, Cache<TYPE> &CACHE>   Bool     CacheCounted<TYPE,CACHE>::contains(C TYPE                    *data             )C {return CACHE._contains(data         );}
template<typename TYPE, Cache<TYPE> &CACHE>   Bool     CacheCounted<TYPE,CACHE>::contains(C CacheElmPtr<TYPE,CACHE> &data             )C {return CACHE._contains(data()       );}
template<typename TYPE, Cache<TYPE> &CACHE>   Int      CacheCounted<TYPE,CACHE>::ptrCount(C TYPE                    *data             )C {return CACHE._ptrCount(data         );}
template<typename TYPE, Cache<TYPE> &CACHE>   Int      CacheCounted<TYPE,CACHE>::ptrCount(C CacheElmPtr<TYPE,CACHE> &data             )C {return CACHE._ptrCount(data()       );}
template<typename TYPE, Cache<TYPE> &CACHE>   Bool     CacheCounted<TYPE,CACHE>::dummy   (C TYPE                    *data             )C {return CACHE._dummy   (data         );}
template<typename TYPE, Cache<TYPE> &CACHE>   Bool     CacheCounted<TYPE,CACHE>::dummy   (C CacheElmPtr<TYPE,CACHE> &data             )C {return CACHE._dummy   (data()       );}
template<typename TYPE, Cache<TYPE> &CACHE>   void     CacheCounted<TYPE,CACHE>::dummy   (C TYPE                    *data, Bool  dummy)  {       CACHE._dummy   (data  , dummy);}
template<typename TYPE, Cache<TYPE> &CACHE>   void     CacheCounted<TYPE,CACHE>::dummy   (C CacheElmPtr<TYPE,CACHE> &data, Bool  dummy)  {       CACHE._dummy   (data(), dummy);}

template<typename TYPE, Cache<TYPE> &CACHE>   Int                          CacheCounted<TYPE,CACHE>::  elms     (     )C {return                             CACHE.  elms     ( );}
template<typename TYPE, Cache<TYPE> &CACHE>   void                         CacheCounted<TYPE,CACHE>::  lock     (     )C {                                   CACHE.  lock     ( );}
template<typename TYPE, Cache<TYPE> &CACHE>   typename Cache<TYPE>::Elm&   CacheCounted<TYPE,CACHE>::  lockedElm(Int i)  {return (typename Cache<TYPE>::Elm&)CACHE.  lockedElm(i);}
template<typename TYPE, Cache<TYPE> &CACHE>   void                         CacheCounted<TYPE,CACHE>::unlock     (     )C {                                   CACHE.unlock     ( );}

template<typename TYPE, Cache<TYPE> &CACHE>   void   CacheCounted<TYPE,CACHE>::remove(C TYPE *data) {return CACHE._remove(data);}

template<typename TYPE, Cache<TYPE> &CACHE>   void   CacheCounted<TYPE,CACHE>::update() {return CACHE.update();}

template<typename TYPE, Cache<TYPE> &CACHE> T1(EXTENDED)   CacheCounted<TYPE,CACHE>&    CacheCounted<TYPE,CACHE>::replaceClass() {CACHE.template replaceClass<EXTENDED>(); return T;}

                                              inline Int Elms(C _Cache                     &cache) {return cache.elms();}
T1(TYPE)                                      inline Int Elms(C  Cache        <TYPE      > &cache) {return cache.elms();}
template<typename TYPE, Cache<TYPE> &CACHE>   inline Int Elms(C  CacheCounted <TYPE,CACHE> &cache) {return cache.elms();}
/******************************************************************************/
// CACHE ELEMENT POINTER
/******************************************************************************/
template<typename TYPE, Cache<TYPE> &CACHE>   CChar*   CacheElmPtr<TYPE,CACHE>::name (CChar *path )C {return CACHE._name (_data, path );}
template<typename TYPE, Cache<TYPE> &CACHE>   UID      CacheElmPtr<TYPE,CACHE>::id   (            )C {return CACHE._id   (_data       );}
template<typename TYPE, Cache<TYPE> &CACHE>   Bool     CacheElmPtr<TYPE,CACHE>::dummy(            )C {return CACHE._dummy(_data       );}
template<typename TYPE, Cache<TYPE> &CACHE>   void     CacheElmPtr<TYPE,CACHE>::dummy(Bool   dummy)  {       CACHE._dummy(_data, dummy);}

template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::clear    (                   ) {            CACHE._decRef(T._data);               T._data=      NULL ;  return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(  TYPE        *data) {if(T!=data){CACHE._decRef(T._data); CACHE._incRef(T._data=      data);} return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(C CacheElmPtr &eptr) {if(T!=eptr){CACHE._decRef(T._data); CACHE._incRef(T._data=eptr._data);} return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(  int              ) {clear();                                                                return T;}

template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::find     (C Str  &file, CChar *path) {TYPE *old=T._data; T._data=(TYPE*)CACHE._find   (    file , path, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::find     (C UID  &id  , CChar *path) {TYPE *old=T._data; T._data=(TYPE*)CACHE._find   (    id   , path, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::get      (C Str  &file, CChar *path) {TYPE *old=T._data; T._data=(TYPE*)CACHE._get    (    file , path, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::get      (C UID  &id  , CChar *path) {TYPE *old=T._data; T._data=(TYPE*)CACHE._get    (    id   , path, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::require  (C Str  &file, CChar *path) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(    file , path, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::require  (C UID  &id  , CChar *path) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(    id   , path, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(C Str  &file             ) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(    file , NULL, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(C Str8 &file             ) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(Str(file), NULL, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(CChar  *file             ) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(    file , NULL, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(CChar8 *file             ) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(Str(file), NULL, true); CACHE._decRef(old); return T;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>&   CacheElmPtr<TYPE,CACHE>::operator=(C UID  &id               ) {TYPE *old=T._data; T._data=(TYPE*)CACHE._require(    id   , NULL, true); CACHE._decRef(old); return T;}

template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(  int              ) {              T._data=      NULL ;}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(  TYPE        *data) {CACHE._incRef(T._data=      data);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(C CacheElmPtr &eptr) {CACHE._incRef(T._data=eptr._data);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(C Str         &file) {              T._data=(TYPE*)CACHE._require(    file , NULL, true);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(C Str8        &file) {              T._data=(TYPE*)CACHE._require(Str(file), NULL, true);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(  CChar       *file) {              T._data=(TYPE*)CACHE._require(    file , NULL, true);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(  CChar8      *file) {              T._data=(TYPE*)CACHE._require(Str(file), NULL, true);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>:: CacheElmPtr(C UID         &id  ) {              T._data=(TYPE*)CACHE._require(    id   , NULL, true);}
template<typename TYPE, Cache<TYPE> &CACHE>   CacheElmPtr<TYPE,CACHE>::~CacheElmPtr(                   ) {clear();}
/******************************************************************************/
// MAP
/******************************************************************************/
T2(KEY, DATA)  Map<KEY, DATA>&  Map<KEY, DATA>::del  (             ) {                 _Map::del  (    ); return T;}
T2(KEY, DATA)  Map<KEY, DATA>&  Map<KEY, DATA>::clear(             ) {                 _Map::clear(    ); return T;}
T2(KEY, DATA)  MAP_MODE         Map<KEY, DATA>::mode (MAP_MODE mode) {return (MAP_MODE)_Map::mode (mode);          }

T2(KEY, DATA)  Int  Map<KEY, DATA>::elms    ()C {return _Map::elms    ();}
T2(KEY, DATA)  Int  Map<KEY, DATA>::dataSize()C {return _Map::dataSize();}

T2(KEY, DATA)    DATA*  Map<KEY, DATA>::find        (C KEY  &key )  {return (DATA*)_Map::find        (&key );}
T2(KEY, DATA)    DATA*  Map<KEY, DATA>::get         (C KEY  &key )  {return (DATA*)_Map::get         (&key );}
T2(KEY, DATA)    DATA*  Map<KEY, DATA>::operator()  (C KEY  &key )  {return (DATA*)_Map::operator()  (&key );}
T2(KEY, DATA)    Bool   Map<KEY, DATA>::containsKey (C KEY  &key )C {return        _Map::containsKey (&key );}
T2(KEY, DATA)    Bool   Map<KEY, DATA>::containsData(C DATA *data)C {return        _Map::containsData( data);}
T2(KEY, DATA)  C KEY *  Map<KEY, DATA>::key         (C DATA *data)C {return (KEY *)_Map::key         ( data);}

T2(KEY, DATA)    void   Map<KEY, DATA>::  lock      (                        )C {               _Map::  lock      (     );}
T2(KEY, DATA)  C KEY &  Map<KEY, DATA>::  lockedKey (  Int   i               )  {return *(KEY *)_Map::  lockedKey ( i   );}
T2(KEY, DATA)    DATA&  Map<KEY, DATA>::  lockedData(  Int   i               )  {return *(DATA*)_Map::  lockedData( i   );}
T2(KEY, DATA)  C DATA&  Map<KEY, DATA>::  lockedData(  Int   i               )C {return  ConstCast(T).  lockedData( i   );}
T2(KEY, DATA)    void   Map<KEY, DATA>::unlock      (                        )C {               _Map::unlock      (     );}
T2(KEY, DATA)    void   Map<KEY, DATA>::  remove    (  Int   i               )  {               _Map::  remove    ( i   );}
T2(KEY, DATA)    void   Map<KEY, DATA>::  removeKey (C KEY  &key             )  {               _Map::  removeKey (&key );}
T2(KEY, DATA)    void   Map<KEY, DATA>::  removeData(C DATA *data            )  {               _Map::  removeData( data);}
T2(KEY, DATA)    Bool   Map<KEY, DATA>::  replaceKey(C KEY  &src, C KEY &dest)  {return         _Map::  replaceKey(&src, &dest);}

T2(KEY, DATA) T1(EXTENDED)  Map<KEY, DATA>&  Map<KEY, DATA>::replaceClass() {ASSERT_BASE_EXTENDED<DATA, EXTENDED>(); lock(); del(); _key_offset=UIntPtr(&((typename Map<KEY, EXTENDED>::Elm*)NULL)->key); _data_offset=UIntPtr(&((typename Map<KEY, EXTENDED>::Elm*)NULL)->data); _desc_offset=UIntPtr(&((typename Map<KEY, EXTENDED>::Elm*)NULL)->desc); _data_size=SIZE(EXTENDED); _memx.replaceClass<typename Map<KEY, EXTENDED>::Elm>(); unlock(); return T;}

T2(KEY, DATA)  Map<KEY, DATA>&  Map<KEY, DATA>::operator=(C Map<KEY, DATA> &src) {if(this!=&src){lock(); src.lock(); _from(src); FREPA(_memx)(Elm&)_memx[i]=(C Elm&)src._memx[i]; src.unlock(); unlock();} return T;}

T2(KEY, DATA)  Map<KEY, DATA>::Map(Int compare(C KEY &a, C KEY &b), Bool create(DATA &data, C KEY &key, Ptr user), Ptr user, Int block_elms) : _Map(block_elms, (Int(*)(CPtr, CPtr))compare, (Bool(*)(Ptr, CPtr, Ptr))create, user, ClassFunc<KEY>::Copy) {replaceClass<DATA>();}

T2(KEY, DATA)  Int  Elms(C Map<KEY, DATA> &map) {return map.elms();}
/******************************************************************************/
// GRID
/******************************************************************************/
T1(TYPE)   void          Grid<TYPE>:: del(                )  {                    _Grid::del (            );} // delete all      cells
T1(TYPE)   void          Grid<TYPE>:: del(Cell<TYPE> *cell)  {                    _Grid::del ((_Cell*)cell);} // delete selected cell
T1(TYPE)   Cell<TYPE>*   Grid<TYPE>:: get(C VecI2 &xy     )  {return (Cell<TYPE>*)_Grid::get (xy          );} // get 'xy' cell, create it   if not found
T1(TYPE)   Cell<TYPE>*   Grid<TYPE>::find(C VecI2 &xy     )C {return (Cell<TYPE>*)_Grid::find(xy          );} // get 'xy' cell, return NULL if not found
T1(TYPE)   Bool          Grid<TYPE>::size(  RectI &rect   )C {return              _Grid::size(rect        );} // get rectangle covering all grid cells, false on fail (if no grid cells are present)

T1(TYPE)                Grid<TYPE>&   Grid<TYPE>::fastAccess  (C RectI *rect) {_Grid::fastAccess                  (rect); return T;} // optimize accessing cells (via 'find/get' methods) within 'rect' rectangle, normally cells are accessed recursively, however after calling this method all cells within the rectangle will be available instantly, if NULL is provided then the optimization is disabled
T1(TYPE) T1(EXTENDED)   Grid<TYPE>&   Grid<TYPE>::replaceClass(             ) {_Grid::replaceClass<TYPE, EXTENDED>(    ); return T;} // replace the type of class stored in the grid, all grid cells are automatically removed before changing the type of the class, the new type must be extended from the base 'TYPE' (if you're receiving a compilation error pointing to this method this means that the new class isn't extended from the base class)

// call custom function on grid cells
T1(TYPE)                 void   Grid<TYPE>::func      (               void func(Cell<TYPE> &cell, Ptr        user)                 ) {_Grid::func      (      (void (*)(_Cell &cell, Ptr user))func,  NULL);} // call 'func' on all existing grid cells
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::func      (               void func(Cell<TYPE> &cell, USER_DATA *user), USER_DATA *user) {_Grid::func      (      (void (*)(_Cell &cell, Ptr user))func,  user);} // call 'func' on all existing grid cells
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::func      (               void func(Cell<TYPE> &cell, USER_DATA &user), USER_DATA &user) {_Grid::func      (      (void (*)(_Cell &cell, Ptr user))func, &user);} // call 'func' on all existing grid cells
T1(TYPE)                 void   Grid<TYPE>::func      (C RectI &rect, void func(Cell<TYPE> &cell, Ptr        user)                 ) {_Grid::func      (rect, (void (*)(_Cell &cell, Ptr user))func,  NULL);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::func      (C RectI &rect, void func(Cell<TYPE> &cell, USER_DATA *user), USER_DATA *user) {_Grid::func      (rect, (void (*)(_Cell &cell, Ptr user))func,  user);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::func      (C RectI &rect, void func(Cell<TYPE> &cell, USER_DATA &user), USER_DATA &user) {_Grid::func      (rect, (void (*)(_Cell &cell, Ptr user))func, &user);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE)                 void   Grid<TYPE>::funcCreate(C RectI &rect, void func(Cell<TYPE> &cell, Ptr        user)                 ) {_Grid::funcCreate(rect, (void (*)(_Cell &cell, Ptr user))func,  NULL);} // call 'func' on all          grid cells in specified rectangle (this method creates grid cells if they don't exist yet)
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::funcCreate(C RectI &rect, void func(Cell<TYPE> &cell, USER_DATA *user), USER_DATA *user) {_Grid::funcCreate(rect, (void (*)(_Cell &cell, Ptr user))func,  user);} // call 'func' on all          grid cells in specified rectangle (this method creates grid cells if they don't exist yet)
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::funcCreate(C RectI &rect, void func(Cell<TYPE> &cell, USER_DATA &user), USER_DATA &user) {_Grid::funcCreate(rect, (void (*)(_Cell &cell, Ptr user))func, &user);} // call 'func' on all          grid cells in specified rectangle (this method creates grid cells if they don't exist yet)

// call custom function on grid cells (multi-threaded version)
T1(TYPE)                 void   Grid<TYPE>::mtFunc(               void func(Cell<TYPE> &cell, Ptr        user)                 , Int threads) {_Grid::mtFunc(      (void (*)(_Cell &cell, Ptr user))func,  NULL, threads);} // call 'func' on all existing grid cells
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::mtFunc(               void func(Cell<TYPE> &cell, USER_DATA *user), USER_DATA *user, Int threads) {_Grid::mtFunc(      (void (*)(_Cell &cell, Ptr user))func,  user, threads);} // call 'func' on all existing grid cells
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::mtFunc(               void func(Cell<TYPE> &cell, USER_DATA &user), USER_DATA &user, Int threads) {_Grid::mtFunc(      (void (*)(_Cell &cell, Ptr user))func, &user, threads);} // call 'func' on all existing grid cells
T1(TYPE)                 void   Grid<TYPE>::mtFunc(C RectI &rect, void func(Cell<TYPE> &cell, Ptr        user)                 , Int threads) {_Grid::mtFunc(rect, (void (*)(_Cell &cell, Ptr user))func,  NULL, threads);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::mtFunc(C RectI &rect, void func(Cell<TYPE> &cell, USER_DATA *user), USER_DATA *user, Int threads) {_Grid::mtFunc(rect, (void (*)(_Cell &cell, Ptr user))func,  user, threads);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE) T1(USER_DATA)   void   Grid<TYPE>::mtFunc(C RectI &rect, void func(Cell<TYPE> &cell, USER_DATA &user), USER_DATA &user, Int threads) {_Grid::mtFunc(rect, (void (*)(_Cell &cell, Ptr user))func, &user, threads);} // call 'func' on all existing grid cells in specified rectangle

// call custom function on grid cells (multi-threaded version with per thread data)
T1(TYPE) T1(PER_THREAD_DATA           )   void   Grid<TYPE>::mtFuncWithPerThreadData(               void func(Cell<TYPE> &cell, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user)                 , Int threads) {Memc<PER_THREAD_DATA> ptd; _Grid::mtFuncWithPerThreadData(      (void (*)(_Cell &cell, Int thread_index, Ptr per_thread_data, Ptr user))func,  NULL, threads, ptd);} // call 'func' on all existing grid cells
T1(TYPE) T2(PER_THREAD_DATA, USER_DATA)   void   Grid<TYPE>::mtFuncWithPerThreadData(               void func(Cell<TYPE> &cell, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA *user), USER_DATA *user, Int threads) {Memc<PER_THREAD_DATA> ptd; _Grid::mtFuncWithPerThreadData(      (void (*)(_Cell &cell, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd);} // call 'func' on all existing grid cells
T1(TYPE) T2(PER_THREAD_DATA, USER_DATA)   void   Grid<TYPE>::mtFuncWithPerThreadData(               void func(Cell<TYPE> &cell, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA &user), USER_DATA &user, Int threads) {Memc<PER_THREAD_DATA> ptd; _Grid::mtFuncWithPerThreadData(      (void (*)(_Cell &cell, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd);} // call 'func' on all existing grid cells
T1(TYPE) T1(PER_THREAD_DATA           )   void   Grid<TYPE>::mtFuncWithPerThreadData(C RectI &rect, void func(Cell<TYPE> &cell, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user)                 , Int threads) {Memc<PER_THREAD_DATA> ptd; _Grid::mtFuncWithPerThreadData(rect, (void (*)(_Cell &cell, Int thread_index, Ptr per_thread_data, Ptr user))func,  NULL, threads, ptd);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE) T2(PER_THREAD_DATA, USER_DATA)   void   Grid<TYPE>::mtFuncWithPerThreadData(C RectI &rect, void func(Cell<TYPE> &cell, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA *user), USER_DATA *user, Int threads) {Memc<PER_THREAD_DATA> ptd; _Grid::mtFuncWithPerThreadData(rect, (void (*)(_Cell &cell, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd);} // call 'func' on all existing grid cells in specified rectangle
T1(TYPE) T2(PER_THREAD_DATA, USER_DATA)   void   Grid<TYPE>::mtFuncWithPerThreadData(C RectI &rect, void func(Cell<TYPE> &cell, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA &user), USER_DATA &user, Int threads) {Memc<PER_THREAD_DATA> ptd; _Grid::mtFuncWithPerThreadData(rect, (void (*)(_Cell &cell, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd);} // call 'func' on all existing grid cells in specified rectangle
/******************************************************************************/
// GAME::OBJ_MEMX
/******************************************************************************/
namespace Game
{
   T1(TYPE)  ObjMap<TYPE>&  ObjMap<TYPE>::clear() {_map.clear(); return T;}

   T1(TYPE)  Int  ObjMap<TYPE>::elms   ()C {return _map.elms    ();}
   T1(TYPE)  Int  ObjMap<TYPE>::elmSize()C {return _map.dataSize();}

   T1(TYPE)    TYPE&  ObjMap<TYPE>::operator[](Int i)  {return _map.lockedData(i);}
   T1(TYPE)  C TYPE&  ObjMap<TYPE>::operator[](Int i)C {return _map.lockedData(i);}

   T1(TYPE)  Bool  ObjMap<TYPE>::containsId (C UID  &obj_id)C {return obj_id.valid() ? _map.containsKey (obj_id) : false;}
   T1(TYPE)  Bool  ObjMap<TYPE>::containsObj(C TYPE *obj   )C {return                  _map.containsData(obj   )        ;}

   T1(TYPE)  TYPE*  ObjMap<TYPE>::find(C UID &obj_id) {return obj_id.valid() ? _map.find(obj_id) : NULL;}

   T1(TYPE)  ObjMap<TYPE>&  ObjMap<TYPE>::remove   (  Int   i     ) {                  _map.remove    (i     ); return T;}
   T1(TYPE)  ObjMap<TYPE>&  ObjMap<TYPE>::removeId (C UID  &obj_id) {if(obj_id.valid())_map.removeKey (obj_id); return T;}
   T1(TYPE)  ObjMap<TYPE>&  ObjMap<TYPE>::removeObj(C TYPE *data  ) {                  _map.removeData(data  ); return T;}

   T1(TYPE)  T1(BASE)  ObjMap<TYPE>::operator    ObjMap<BASE>&()  {ASSERT_BASE_EXTENDED<BASE, TYPE>(); return *(  ObjMap<BASE>*)this;}
   T1(TYPE)  T1(BASE)  ObjMap<TYPE>::operator  C ObjMap<BASE>&()C {ASSERT_BASE_EXTENDED<BASE, TYPE>(); return *(C ObjMap<BASE>*)this;}

   T1(TYPE)  ObjMap<TYPE>::ObjMap(Int block_elms) : _map(Compare, NULL, NULL, block_elms) {}
}
T1(TYPE)  Int  Elms(C Game::ObjMap<TYPE> &obj_map) {return obj_map.elms();}
/******************************************************************************/
// LIST
/******************************************************************************/
T1(TYPE) _List& _List::setData    (TYPE       *data, Int elms, C Memp<Bool> &visible, Bool keep_cur) {return _setData(     data  ,      elms  ,     SIZE(TYPE), visible, keep_cur);}
T1(TYPE) _List& _List::setData    (Mems<TYPE> &mems,           C Memp<Bool> &visible, Bool keep_cur) {return _setData(mems.data(), mems.elms(), mems.elmSize(), visible, keep_cur);}
T1(TYPE) _List& _List::setDataNode(Memx<TYPE> &memx,           C Memp<Bool> &visible, Bool keep_cur) {return _setData(memx       ,      OFFSET(TYPE, children), visible, keep_cur); Memx<TYPE> &temp=MEMBER(TYPE, children);}
/******************************************************************************/
// INTERPOLATOR
/******************************************************************************/
T1(TYPE)  AngularInterpolator<TYPE>&  AngularInterpolator<TYPE>::update(               C InterpolatorTime &time) {_c=Lerp(_h[0], _h[1], time()); return T;}
T1(TYPE)  void                        AngularInterpolator<TYPE>::step  (C TYPE &value, C InterpolatorTime &time) {if(time.empty())_c=_h[0]=_h[1]=value;else{update(time); _h[0]=_c; _h[1]=_h[0]+AngleDelta(_h[0], value);}}

T1(TYPE)  LinearInterpolator<TYPE>&  LinearInterpolator<TYPE>::update(               C InterpolatorTime &time) {_c=Lerp(_h[0], _h[1], time()); return T;}
T1(TYPE)  void                       LinearInterpolator<TYPE>::step  (C TYPE &value, C InterpolatorTime &time) {if(time.empty())_c=_h[0]=_h[1]=value;else{update(time); _h[0]=_c; _h[1]=value;}}

T1(TYPE)  SplineInterpolator<TYPE>&  SplineInterpolator<TYPE>::update(               C InterpolatorTime &time) {_c=Lerp4(_h[0], _h[1], _h[2], _h[3], time()); return T;}
T1(TYPE)  void                       SplineInterpolator<TYPE>::step  (C TYPE &value, C InterpolatorTime &time) {if(time.empty())_c=_h[0]=_h[1]=_h[2]=_h[3]=value;else{update(time); _h[3]=value+(value-_h[2]); _h[0]=_h[1]; _h[1]=_c; _h[2]=value;}}

T1(TYPE)           Interpolator<TYPE>     &  Interpolator<TYPE>::add       (Flt x, C TYPE &y)  {if(typename Interpolator<TYPE>::Elm *elm=(typename Interpolator<TYPE>::Elm*)_add(x))elm->y=y; return T;}
T1(TYPE)  typename Interpolator<TYPE>::Elm&  Interpolator<TYPE>::operator[](Int i           )C {return (typename Interpolator<TYPE>::Elm&)_elms[i];}
T1(TYPE)                        TYPE         Interpolator<TYPE>::operator()(Flt x           )C
{
   Int prev, next; Flt frac; _get(x, prev, next, frac);
   if( prev==next)
   {
      if(prev<0)return 0;
      return T[prev].y;
   }
   return Lerp(T[prev].y, T[next].y, frac);
}
T1(TYPE)  TYPE  Interpolator<TYPE>::smooth(Flt x)C
{
   Int prev2, prev, next, next2; Flt frac; _get4(x, prev2, prev, next, next2, frac);
   if( prev==next)
   {
      if(prev<0)return 0;
      return T[prev].y;
   }
   return Lerp4((prev2<0) ? T[prev].y*2-T[next].y : T[prev2].y, T[prev].y, T[next].y, (next2<0) ? T[next].y*2-T[prev].y : T[next2].y, frac);
}
T1(TYPE)  Interpolator<TYPE>&  Interpolator<TYPE>::operator=(C Interpolator &src)
{
   loop =src.loop;
   clamp=src.clamp;
   min_x=src.min_x;
   max_x=src.max_x;
  _elms.setNum(src.elms());
   FREPAO(T)=src[i];
   return T;
}
T1(TYPE)  Interpolator<TYPE>::Interpolator(                   ) {_elms.replaceClass<Elm>();}
T1(TYPE)  Interpolator<TYPE>::Interpolator(C Interpolator &src) {_elms.replaceClass<Elm>(); T=src;}
/******************************************************************************/
// IO
/******************************************************************************/
T1(TYPE) void FList(C Str &path, FILE_LIST_MODE func(C FileFind &ff, TYPE *user), TYPE *user) {FList(path, (FILE_LIST_MODE (*)(C FileFind &ff, Ptr user))func,  user);}
T1(TYPE) void FList(C Str &path, FILE_LIST_MODE func(C FileFind &ff, TYPE &user), TYPE &user) {FList(path, (FILE_LIST_MODE (*)(C FileFind &ff, Ptr user))func, &user);}
/******************************************************************************/
// PVRTC
/******************************************************************************/
extern Bool   CompressPVRTC     (Int x, Int y, Ptr data, Int type, Int quality, Ptr &compressed_data, Int &compressed_size);
extern Bool (*CompressPVRTCFunc)(Int x, Int y, Ptr data, Int type, Int quality, Ptr &compressed_data, Int &compressed_size);
inline void    SupportPVRTC()
{
#if defined WINDOWS || defined MAC || defined LINUX
   CompressPVRTCFunc=CompressPVRTC;
#endif
}
/******************************************************************************/
// EDIT
/******************************************************************************/
namespace Edit
{
/******************************************************************************/
// UNDO
/******************************************************************************/
T1(TYPE) Undo<TYPE>::Undo(Bool full, Ptr user, Flt time) : _Undo(full, user, time) {replaceClass<TYPE>();}

T1(TYPE) T1(CHANGE) Undo<TYPE>& Undo<TYPE>::replaceClass() {ASSERT_BASE_EXTENDED<TYPE, CHANGE>(); _changes.replaceClass<CHANGE>(); return T;}

T1(TYPE) TYPE* Undo<TYPE>::set(CPtr change_type, Bool force_create, Flt extra_time) {return (TYPE*)_Undo::set(change_type, force_create, extra_time);}
T1(TYPE) TYPE* Undo<TYPE>::set( Int change_type, Bool force_create, Flt extra_time) {return (TYPE*)_Undo::set(change_type, force_create, extra_time);}
}
/******************************************************************************/
