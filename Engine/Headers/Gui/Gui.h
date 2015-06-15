/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct GUI // Graphical User Interface
{
   Bool allow_window_fade    ; // if allow Window fading (smooth transparency), default=true
   Flt  window_fade_in_speed , // speed of Window fading in     , 0..Inf, default=9
        window_fade_out_speed, // speed of Window fading out    , 0..Inf, default=6
        window_fade_scale    , // scale of Window when faded out, 0..2  , default=0.85
        desc_delay           , // time after which gui object descriptions should be displayed, default=0.3
        stereoscopic_scale   , //            scale  applied to GUI for stereoscopic rendering,  0..2, default=1
        stereoscopic_offset  ; // horizontal offset applied to GUI for stereoscopic rendering, -1..1, default=0

   ImagePtr image_shadow       , // shadow            image, default=Images.ptrGet("Gui/shadow.gfx"       )
            image_drag         , // drag              image, default=Images.ptrGet("Gui/drag.gfx"         )
            image_resize_x     , // resize horizontal image, default=Images.ptrGet("Gui/resize_x.gfx"     )
            image_resize_y     , // resize vertical   image, default=Images.ptrGet("Gui/resize_y.gfx"     )
            image_resize_ld    , // resize left  down image, default=Images.ptrGet("Gui/resize_ru.gfx"    )
            image_resize_lu    , // resize left  up   image, default=Images.ptrGet("Gui/resize_rd.gfx"    )
            image_resize_ru    , // resize right up   image, default=Images.ptrGet("Gui/resize_ru.gfx"    )
            image_resize_rd    , // resize right down image, default=Images.ptrGet("Gui/resize_rd.gfx"    )
            image_resize_column; // resize right down image, default=Images.ptrGet("Gui/resize_column.gfx")

   GuiSkinPtr skin        ; // active Gui Skin
   UID        default_skin; // ID of the Gui Skin to be loaded during engine initialization, this can be modified in 'InitPre'

   void (*draw_keyboard_highlight)(GuiObj *obj, C Rect &rect, C GuiSkin *skin       ); // pointer to custom function responsible for drawing keyboard highlight    , 'obj'=pointer to gui object for the highlight , 'rect'=screen rectangle of the object, 'skin'=Gui Skin of the object, default='DrawKeyboardHighlight'
   void (*draw_description       )(GuiObj *obj, C Vec2 &pos, CChar *text, Bool mouse); // pointer to custom function responsible for drawing gui object description, 'obj'=pointer to gui object of the desctiption, 'pos' =screen position where the description should be drawn, 'text'=text of the description, 'mouse'=if description drawing was triggered by mouse, default='DrawDescription'
   void (*draw_imm               )(GuiObj *obj                                      ); // pointer to custom function responsible for drawing the IMM data          , 'obj'=pointer to gui object responsible for IMM text, default='DrawIMM'

   // get
   GuiObj* kb     ()C {return _kb     ;} // current object with  keyboard    focus
   GuiObj* ms     ()C {return _ms     ;} // current object with  mouse       focus (this is not always the object under mouse cursor, for example if you push the mouse button on a gui object, and move the cursor away without releasing the button, this method will still return the object on which the button was pushed)
   GuiObj* msLit  ()C {return _ms_lit ;} // current object under mouse cursor      (this is     always the object under mouse cursor)
   GuiObj* wheel  ()C {return _wheel  ;} // current object with  mouse wheel focus
   GuiObj* desktop()C {return _desktop;} // current desktop
   GuiObj* window ()C {return _window ;} // current window with focus
   GuiObj* menu   ()C {return _menu   ;} // current menu

   GuiObj* objAtPos(C Vec2 &pos)C; // get gui object at 'pos' screen position

   Flt updateTime()C {return _update_time;} // get CPU time needed to perform last 'update' method

   Color backgroundColor()C; // get background color of the current skin, this is 'Gui.skin.background_color'
   Color borderColor    ()C; // get border     color of the current skin, this is 'Gui.skin.border_color'

   // operations
   T1(TYPE) void operator+=(TYPE &child) {if(_desktop)*_desktop+=child;} // add    gui object to   active desktop
   T1(TYPE) void operator-=(TYPE &child) {if(_desktop)*_desktop-=child;} // remove gui object from active desktop

   void msgBox(C Str &title, C Str &text); // create and display a gui based message box

   void passwordChar(Char c); // set character used for TextLine's when in password mode (default='*')

   // dragging
   Bool dragging()C {return _dragging;} // if currently dragging an element
   Vec2 dragPos ()C;                    // get screen position of the input that triggered dragging (this is valid if 'dragging' returns true)

   void dragCancel(); // cancel any current dragging

            void drag(C Str &name                                                              , Touch *touch=NULL                                                           );                                                                                                         // start dragging 'name' element,                                                                          'touch'=touch used to initiate the dragging (NULL for mouse)
            void drag(void finish(Ptr   user, GuiObj *obj, C Vec2 &screen_pos), Ptr   user=NULL, Touch *touch=NULL, void start(Ptr   user)=NULL, void cancel(Ptr   user)=NULL);                                                                                                         // start dragging and call 'finish' function when finished, 'start' when started, 'cancel' when cancelled, 'touch'=touch used to initiate the dragging (NULL for mouse)
   T1(TYPE) void drag(void finish(TYPE *user, GuiObj *obj, C Vec2 &screen_pos), TYPE *user     , Touch *touch=NULL, void start(TYPE *user)=NULL, void cancel(TYPE *user)=NULL) {drag((void(*)(Ptr, GuiObj*, C Vec2&))finish,  user, touch, (void(*)(Ptr))start, (void(*)(Ptr))cancel);} // start dragging and call 'finish' function when finished, 'start' when started, 'cancel' when cancelled, 'touch'=touch used to initiate the dragging (NULL for mouse)
   T1(TYPE) void drag(void finish(TYPE &user, GuiObj *obj, C Vec2 &screen_pos), TYPE &user     , Touch *touch=NULL, void start(TYPE &user)=NULL, void cancel(TYPE &user)=NULL) {drag((void(*)(Ptr, GuiObj*, C Vec2&))finish, &user, touch, (void(*)(Ptr))start, (void(*)(Ptr))cancel);} // start dragging and call 'finish' function when finished, 'start' when started, 'cancel' when cancelled, 'touch'=touch used to initiate the dragging (NULL for mouse)

   // function callbacks
            void addFuncCall(void func(          )            );                                          // add custom function to the gui function callback list to be automatically called at the end of the 'Gui.update'
            void addFuncCall(void func(Ptr   user), Ptr   user);                                          // add custom function to the gui function callback list to be automatically called at the end of the 'Gui.update'
   T1(TYPE) void addFuncCall(void func(TYPE *user), TYPE *user) {addFuncCall((void(*)(Ptr))func,  user);} // add custom function to the gui function callback list to be automatically called at the end of the 'Gui.update'
   T1(TYPE) void addFuncCall(void func(TYPE &user), TYPE &user) {addFuncCall((void(*)(Ptr))func, &user);} // add custom function to the gui function callback list to be automatically called at the end of the 'Gui.update'

   // update / draw
   void update(); // update gui
   void draw  (); // draw   gui !! can't be called between 'D.fxBegin' and 'D.fxEnd' !!

private:
   Bool          _drag_want, _dragging;
   Char          _pass_char;
   GuiObj       *_kb, *_ms, *_ms_lit, *_wheel, *_desktop, *_window, *_window_lit, *_window_menu, *_menu, *_desc, *_touch_desc, *_overlay_textline;
   Flt           _desc_time, _touch_desc_time, _update_time, _time_d_fade_in, _time_d_fade_out;
   UInt          _drag_touch_id;
   Vec2          _drag_pos, _overlay_textline_offset;
   Str           _drag_name, _pass_temp;
   Ptr           _drag_user;
   void        (*_drag_start )(Ptr user),
               (*_drag_cancel)(Ptr user),
               (*_drag_finish)(Ptr user, GuiObj *obj, C Vec2 &screen_pos);
   Callbacks     _callbacks;
   CritSect      _cs;
   Memx<Desktop> _desktops;

   GUI();
}extern
   Gui; // Main GUI
/******************************************************************************/
void DrawKeyboardHighlight(GuiObj *obj, C Rect &rect, C GuiSkin *skin       ); // default Keyboard Highlight                 drawing function
void DrawDescription      (GuiObj *obj, C Vec2 &pos, CChar *text, Bool mouse); // default Gui Object Description             drawing function
void DrawIMM              (GuiObj *obj                                      ); // default IMM (Windows Input Method Manager) drawing function
/******************************************************************************/
