/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Time' to access:
      -current time
      -current frame time
      -current frame number
      -modify game time speed

/******************************************************************************/
struct TimeClass
{
   UInt     frame ()C {return _frame;} // current frame number
   Flt      fps   ()C {return _fps  ;} // current number of frames per second
   Flt      d     ()C {return _d    ;} // game        time delta (frame time duration,     modified by game 'speed',     affected by 'smooth' 'skipUpdate' and application pauses)
   Flt     ad     ()C {return _ad   ;} // application time delta (frame time duration, NOT modified by game 'speed',     affected by 'smooth' 'skipUpdate' and application pauses)
   Flt     rd     ()C {return _rd   ;} // real        time delta (frame time duration, NOT modified by game 'speed', NOT affected by 'smooth' 'skipUpdate' and application pauses)
   Flt      time  ()C {return _t    ;} // game        time in current frame  (     seconds since application started,     modified by game 'speed',     affected by 'smooth' 'skipUpdate' and application pauses)
   Flt   appTime  ()C {return _at   ;} // application time in current frame  (     seconds since application started, NOT modified by game 'speed',     affected by 'smooth' 'skipUpdate' and application pauses)
   Flt  realTime  ()C {return _rt   ;} // real        time in current frame  (     seconds since application started, NOT modified by game 'speed', NOT affected by 'smooth' 'skipUpdate' and application pauses)
   Flt   curTime  ()C;                 // real        time in current moment (     seconds since application started, NOT modified by game 'speed', NOT affected by 'smooth' 'skipUpdate' and application pauses, this method always calculates the time when called)
   UInt  curTimeMs()C;                 // real        time in current moment (milliseconds since application started, NOT modified by game 'speed', NOT affected by 'smooth' 'skipUpdate' and application pauses, this is a little faster method than 'curTime' but returns time in milliseconds)

   Flt               speed     (                      )C {return _speed;} // get game time speed (<1 slower, 1 default, >1 faster)
   void              speed     (Flt              speed) ;                 // set game time speed (<1 slower, 1 default, >1 faster) and modify sound speeds (except VOLUME_MUSIC and VOLUME_AMBIENT volume groups)
   SMOOTH_VALUE_MODE smooth    (                      )C;                 // get time delta smoothing, default=SV_WEIGHT4
   void              smooth    (SMOOTH_VALUE_MODE mode) ;                 // set time delta smoothing
   void              wait      (Int       milliseconds) ;                 // pause the current thread and wait 'milliseconds' time (this is equal to calling the system 'Sleep' function)
   void              skipUpdate(Byte          frames=1) ;                 // call this method to notify that timer should skip updating frame time for following 'frames', use this method after slow one time methods, like loading data

   Flt stateUpdateTime()C {return _state_update;} // get CPU time needed to process active application State Update in last frame
   Flt stateDrawTime  ()C {return _state_draw  ;} // get CPU time needed to process active application State Draw   in last frame

   TimeClass();

private:
   Bool        _pc;
   Byte        _skip;
   Int         _frames_drawn;
   UInt        _start_time_ms, _frame;
   ULong       _start_time;
   Flt         _fps, _rd_2, _rd_1, _rd, _ad, _d, _rt, _at, _t, _speed, _fps_time, _state_update, _state_draw;
   Dbl         _time_mul;
   SmoothValue _sv_ad;
}extern
   Time; // Application Time Access
/******************************************************************************/
Bool EventOccured(Flt event_time                        , Flt cur_time, Flt dt); // if event has occured , 'event_time     '=position in time       ,                                        'cur_time'=current time, 'dt'=time delta
Bool EventBetween(Flt event_time_from, Flt event_time_to, Flt cur_time, Flt dt); // if event is  occuring, 'event_time_from'=position of event start, 'event_time_to'=position of event end, 'cur_time'=current time, 'dt'=time delta
/******************************************************************************/
