/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'InterpolatorTime' to calculate time step fraction between sequentially received data.

   Use 'AngularInterpolator' to calculate linear interpolation between sequentially received angle values.
   Use  'LinearInterpolator' to calculate linear interpolation between sequentially received       values.
   Use  'SplineInterpolator' to calculate spline interpolation between sequentially received       values.

   Use 'Interpolator' to calculate interpolation between manually filled array of data,
      at specified position between array elements.

/******************************************************************************/
struct InterpolatorTime
{
   // get
   Flt  operator()()C {return _frac ;} // get current time fraction (0..1) between received data
   Bool empty     ()C {return _empty;} // if is empty (no data was yet received)

   // operations
   void update(); // call this method at least once per frame before using this object for methods of other classes ('AngularInterpolator', 'LinearInterpolator', 'SplineInterpolator')
   void step  (); // call this method when received new data, however after calling 'step' method  of other classes ('AngularInterpolator', 'LinearInterpolator', 'SplineInterpolator')

   InterpolatorTime& reset(); // reset to initial settings

   InterpolatorTime() {reset();}

private:
   Flt  _frac, _latency, _last_receive_time;
   Bool _empty;
};
/******************************************************************************/
T1(TYPE) struct AngularInterpolator
{
   // get
 C TYPE& operator()()C {return _c;} // get current value

   // operations
   AngularInterpolator& update(               C InterpolatorTime &time); // update current value according to history and current time, call once per frame
   void                 step  (C TYPE &value, C InterpolatorTime &time); // call this method when received new data

   void clearHistory() {_c=_h[0]=_h[1];} // clear value history, you can call this method when new value is drastically different than previous values in order to disable interpolation between old values (for example when interpolating player position which has suddenly teleported to a distant location, interpolator would normally return his position as interpolation between original and new position, however after calling this method new position will be returned immediately without interpolation with old position)

   AngularInterpolator() {_h[0]=_h[1]=_c=0;}

private:
   TYPE _c, _h[2];
};
/******************************************************************************/
T1(TYPE) struct LinearInterpolator
{
   // get
 C TYPE& operator()()C {return _c;} // get current value

   // operations
   LinearInterpolator& update(               C InterpolatorTime &time); // update current value according to history and current time, call once per frame
   void                step  (C TYPE &value, C InterpolatorTime &time); // call this method when received new data

   void clearHistory() {_c=_h[0]=_h[1];} // clear value history, you can call this method when new value is drastically different than previous values in order to disable interpolation between old values (for example when interpolating player position which has suddenly teleported to a distant location, interpolator would normally return his position as interpolation between original and new position, however after calling this method new position will be returned immediately without interpolation with old position)

   LinearInterpolator() {_h[0]=_h[1]=_c=0;}

private:
   TYPE _c, _h[2];
};
/******************************************************************************/
T1(TYPE) struct SplineInterpolator
{
   // get
 C TYPE& operator()()C {return _c;} // get current value

   // operations
   SplineInterpolator& update(               C InterpolatorTime &time); // update current value according to history and current time, call once per frame
   void                step  (C TYPE &value, C InterpolatorTime &time); // call this method when received new data

   void clearHistory() {_c=_h[0]=_h[1]=_h[3]=_h[2];} // clear value history, you can call this method when new value is drastically different than previous values in order to disable interpolation between old values (for example when interpolating player position which has suddenly teleported to a distant location, interpolator would normally return his position as interpolation between original and new position, however after calling this method new position will be returned immediately without interpolation with old position)

   SplineInterpolator() {_h[0]=_h[1]=_h[2]=_h[3]=_c=0;}

private:
   TYPE _c, _h[4];
};
/******************************************************************************/
struct _Interpolator // don't use this class, use 'Interpolator' instead
{
   struct _Elm
   {
      Flt  x;
    //TYPE y;
   };

   Bool loop , // if elements are looped (last interpolates to first)                       , default=false
        clamp; // if clamp value when accessing element out of range and looping is disabled, default=true
   Flt  min_x, max_x; // minimum and maximum possible values of 'x' (used only when looping)

   Int  elms ()C {return _elms.elms();} // get number of elements
   void clear()  {_elms.clear(); min_x=FLT_MAX; max_x=-FLT_MAX;} // clear elements and reset min/max ranges

private:
   Memc<_Elm> _elms;
  _Elm* _add (Flt x                                                         ) ;
   void _get (Flt x,             Int &prev, Int &next,             Flt &frac)C;
   void _get4(Flt x, Int &prev2, Int &prev, Int &next, Int &next2, Flt &frac)C;
  _Interpolator();
   T1(TYPE) friend struct Interpolator;
};
/******************************************************************************/
T1(TYPE) struct Interpolator : _Interpolator
{
   struct Elm : _Elm
   {
      TYPE y;
   };

   Interpolator& add(Flt x, C TYPE &y) ; // create new element at 'x' position
   Elm&   operator[](Int i           )C; // get i-th element
   TYPE   operator()(Flt x           )C; // get linear interpolated value at 'x' position
   TYPE       smooth(Flt x           )C; // get smooth interpolated value at 'x' position (using 4 value, hermite spline interpolation)

   Interpolator& operator=(C Interpolator &src);

   Interpolator();
   Interpolator(C Interpolator &src);
};
/******************************************************************************/
typedef AngularInterpolator<Flt> InterpolatorA;

typedef LinearInterpolator<Flt > Interpolator1;
typedef LinearInterpolator<Vec2> Interpolator2;
typedef LinearInterpolator<Vec > Interpolator3;
typedef LinearInterpolator<Vec4> Interpolator4;

typedef SplineInterpolator<Flt > Interpolator1S;
typedef SplineInterpolator<Vec2> Interpolator2S;
typedef SplineInterpolator<Vec > Interpolator3S;
typedef SplineInterpolator<Vec4> Interpolator4S;
/******************************************************************************/
inline Int Elms(C _Interpolator &interpolator) {return interpolator.elms();}
/******************************************************************************/
