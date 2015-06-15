/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'States' to handle different application states, for which you can specify custom functions for:
      -Initialize
      -Shut Down
      -Update
      -Draw

/******************************************************************************/
struct State // Application State
{
   // get
   Flt time()C {return _time;} // get time in seconds since the state was started

   // set
   void set(                                             ); // set as active state (this sets current State to the StateNext, and in the next frame it will be set also as StateActive)
   void set(Flt fade_time, Bool fade_previous_frame=false); // set as active state and use screen fade effect between states, that lasts 'fade_time' number of seconds, 'fade_previous_frame'=if use result of previous frame instead of the next frame for fading

   State(Bool (*update)(), void (*draw)(), Bool (*init)()=NULL, void (*shut)()=NULL); // 'init' and 'shut' may be set to NULL

private:
   Flt   _time;
   Bool (*update)();
   void (*draw  )();
   Bool (*init  )();
   void (*shut  )();
}extern
   StateExit  , //        state which always exits application (NULL, NULL, NULL, NULL)
   StateMain  , // main   state                                (Main, Draw, NULL, NULL)
  *StateActive, // active state
  *StateNext  ; // next   state that will be activated in the next frame, default=&StateMain
/******************************************************************************/
