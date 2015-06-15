/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(CheckBox , GuiObj) // Gui CheckBox !! must be stored in constant memory address !!
//{
   GuiSkinPtr skin; // skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)

   // manage
   CheckBox& del   (                               );                                   // delete
   CheckBox& create(                  Bool on=false);                                   // create
   CheckBox& create(C Rect     &rect, Bool on=false) {create(on).rect(rect); return T;} // create and set rectangle
   CheckBox& create(C CheckBox &src                );                                   // create from 'src'

   // get / set
   CheckBox& set      (Bool on, Bool quiet=false);   Bool operator()()C {return _on;}                        // set/get if on, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   CheckBox& toggle   (         Bool quiet=false);                                                           // toggle  if on, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   CheckBox& setMulti (                         );                                                           // set     visuals as both true and false, this modifies only visuals and does not modify the current value of the checkbox
   CheckBox& focusable(Bool on                  );   Bool  focusable()C {return _focusable;}                 // set/get if can catch keyboard focus, default=false
                                                  GuiSkin*   getSkin()C {return skin ? skin() : Gui.skin();} // get actual skin

            CheckBox& func(void (*func)(Ptr       ), Ptr   user=NULL, Bool immediate=false);                                                       // set function called when checkbox state has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) CheckBox& func(void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return T.func((void(*)(Ptr))func,  user, immediate);} // set function called when checkbox state has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) CheckBox& func(void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return T.func((void(*)(Ptr))func, &user, immediate);} // set function called when checkbox state has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)

   // main
   virtual void update(C GuiPC &gpc); // update object
   virtual void draw  (C GuiPC &gpc); // draw   object

  ~CheckBox() {del();}
   CheckBox();

private:
   Bool   _on, _multi, _func_immediate, _focusable;
   Flt    _lit;
   Ptr    _func_user;
   void (*_func)(Ptr user);

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(CheckBox);
};
/******************************************************************************/
