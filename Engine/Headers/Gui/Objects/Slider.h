/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(Slider , GuiObj) // Gui Slider !! must be stored in constant memory address !!
//{
   GuiSkinPtr skin; // skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)

   // manage
   Slider& del   (                         );                                            // delete
   Slider& create(                         );                                            // create
   Slider& create(C Rect   &rect           ) {create()           .rect(rect); return T;} // create and set initial values
   Slider& create(C Rect   &rect, Flt value) {create().set(value).rect(rect); return T;} // create and set initial values
   Slider& create(C Slider &src            );                                            // create from 'src'

   // get / set
   Flt      operator()(                           )C {return _value;} // get value (0..1)
   Slider & set       (Flt value, Bool quiet=false);                  // set value (0..1), 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   GuiSkin* getSkin   (                           )C {return skin ? skin() : Gui.skin();} // get actual skin

            Slider& func(void (*func)(Ptr   user), Ptr   user=NULL);                                            // set function called when value has changed, with 'user' as its parameter
   T1(TYPE) Slider& func(void (*func)(TYPE *user), TYPE *user     ) {return T.func((void(*)(Ptr))func,  user);} // set function called when value has changed, with 'user' as its parameter
   T1(TYPE) Slider& func(void (*func)(TYPE &user), TYPE &user     ) {return T.func((void(*)(Ptr))func, &user);} // set function called when value has changed, with 'user' as its parameter

   Slider& focusable(Bool on);   Bool focusable()C {return _focusable;} // set/get if can catch keyboard focus, default=false

   // operations
   virtual Slider& rect(C Rect &rect);   C Rect& rect()C {return super::rect();} // set/get rectangle

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~Slider() {del();}
   Slider();

private:
   Bool   _vertical, _focusable;
   Flt    _value, _lit;
   Ptr    _func_user;
   void (*_func)(Ptr user);

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(Slider);
};
/******************************************************************************/
