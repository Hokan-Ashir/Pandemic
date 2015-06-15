/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum BUTTON_MODE // Button Mode
{
   BUTTON_DEFAULT   , // callback function gets called when                  pointer is released on the button
   BUTTON_CONTINUOUS, // callback function gets called every frame while the pointer is enabled  on the button
   BUTTON_TOGGLE    , // callback function gets called when                  pointer is pushed   on the button which toggles its state (enabled <-> disabled)
   BUTTON_IMMEDIATE , // callback function gets called when                  pointer is pushed   on the button
};
/******************************************************************************/
const_mem_addr STRUCT(Button , GuiObj) // Gui Button !! must be stored in constant memory address !!
//{
   BUTTON_MODE mode       ; // button mode  , default=BUTTON_DEFAULT
   Color       image_color; // image color  , default=WHITE (this is multiplied by 'GuiSkin.button.image_color')
   Flt         text_align , // text aligning, default=0.0
               text_size  ; // text size    , default=1.0 (this is multiplied by button height and 'GuiSkin.button.text_size')
   Str         text       ; // text         , default=""
   ImagePtr    image      ; // image        , default=NULL
   GuiSkinPtr  skin       ; // skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)

   // manage
   Button& del   (                             );                                     // delete
   Button& create(                C Str &text=S);                                     // create
   Button& create(C Rect   &rect, C Str &text=S) {create(text).rect(rect); return T;} // create and set rectangle
   Button& create(C Button &src                );                                     // create from 'src'

   // get / set
           Bool    operator()(                         )C {return _on ;} // get button state (if it's visually pushed)
           Flt     lit       (                         )C {return _lit;} // get highlight factor (0..1)
           Flt     textWidth (C Flt *height=NULL       )C;               // calculate button text width, 'height'=if calculate based on custom button height (if NULL then current button height is used)
           Button& set       (Bool on, Bool quiet=false);                // set if on, this method is valid only for BUTTON_TOGGLE mode, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
           Button& push      (                         );                // push manually
           Button& setText   (C Str      &text         );                // set text
           Button& setImage  (C ImagePtr &image        );                // set image
   virtual Button&  enabled  (Bool  enabled            );   Bool  enabled ()C {return          super:: enabled();} // set/get if  enabled
   virtual Button& disabled  (Bool disabled            );   Bool disabled ()C {return          super::disabled();} // set/get if disabled
           Button& focusable (Bool on                  );   Bool focusable()C {return                 _focusable;} // set/get if can catch keyboard focus, default=true
                                                        GuiSkin* getSkin  ()C {return skin ? skin() : Gui.skin();} //     get actual skin

            Button& func(void (*func)(Ptr   user), Ptr   user=NULL, Bool immediate=false);                                                       // set function called when button state has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) Button& func(void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return T.func((void(*)(Ptr))func,  user, immediate);} // set function called when button state has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) Button& func(void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return T.func((void(*)(Ptr))func, &user, immediate);} // set function called when button state has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)

            void  (*func()) (Ptr user) {return _func;} // get function called when button state has changed, this returns a pointer to "void func(Ptr user)" function

   // main
   virtual Button& hide  (            ); // hide
   virtual Button& show  (            ); // show
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~Button() {del();}
   Button();

private:
   Bool   _push_button, _on, _vertical, _focusable, _pixel_align, _func_immediate;
   Byte   _sub_type;
   Flt    _lit;
   Ptr    _func_user;
   void (*_func)(Ptr user);

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(Button);
};
/******************************************************************************/
