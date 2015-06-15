/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum SLIDEBAR_BACK_CLICK_MODE // action occured when clicking on the background of the SlideBar
{
   SBC_OFF    , // nothing happens
   SBC_STEP   , // one time scroll   will be performed by a single step
   SBC_SMOOTH , // smooth scrolling  will be performed as long as the click is hold
   SBC_SET_POS, // slidebar position will be immediately set to the click position
};
const_mem_addr STRUCT(SlideBar , GuiObj) // Gui SlideBar !! must be stored in constant memory address !!
//{
   FixedArray<Button, 3>    button; // 3 buttons (0=middle, 1=left/up, 2=right/down)
   SLIDEBAR_BACK_CLICK_MODE sbc   ; // default=SBC_STEP

   // manage
   SlideBar& del   (                );                              // delete
   SlideBar& create(                );                              // create
   SlideBar& create(C Rect     &rect) {return create().rect(rect);} // create and set rectangle
   SlideBar& create(C SlideBar &src );                              // create from 'src'

   // set / get
   SlideBar&   setLengths   (Flt length, Flt length_total);                         // set, 'length'=covered length, 'length_total'=total length
   SlideBar&   set          (Flt step  , Bool quiet=false);                         // set slidebar step                 (0..1)                  , 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   Flt         operator()   (                            )C;                        // get slidebar step                 (0..1)
   Flt         offsetDesired(                            )C;                        // get slidebar offset desired       (0..length_total-length)
   Flt         offset       (                            )C {return _offset      ;} // get slidebar offset at the moment (0..length_total-length)
   SlideBar&   offset       (Flt offset, Bool quiet=false);                         // set slidebar offset               (0..length_total-length), 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   Flt         length       (                            )C {return _length      ;} // get slidebar length
   Flt         lengthTotal  (                            )C {return _length_total;} // get slidebar length total
   SlideBar&      skin      (C GuiSkinPtr &skin          );                         // set skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used), changing this value will automatically change the skin of the SlideBar buttons
 C GuiSkinPtr&    skin      (                            )C {return _skin        ;} // get skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)
   GuiSkin*    getSkin      (                            )C {return _skin ? _skin() : Gui.skin();} // get actual skin

            SlideBar& func(void (*func)(Ptr   user), Ptr   user=NULL);                                            // set function called when value has changed, with 'user' as its parameter
   T1(TYPE) SlideBar& func(void (*func)(TYPE *user), TYPE *user     ) {return T.func((void(*)(Ptr))func,  user);} // set function called when value has changed, with 'user' as its parameter
   T1(TYPE) SlideBar& func(void (*func)(TYPE &user), TYPE &user     ) {return T.func((void(*)(Ptr))func, &user);} // set function called when value has changed, with 'user' as its parameter

   virtual SlideBar& desc(C Str &desc);   C Str& desc()C {return super::desc();} // set/get description

   SlideBar& focusable(Bool on);   Bool focusable()C {return _focusable;} // set/get if can catch keyboard focus, default=true

   // operations
   virtual SlideBar& rect(C Rect &rect );   C Rect& rect()C {return super::rect();} // set/get rectangle
   virtual SlideBar& move(C Vec2 &delta);                                           // move by delta

   SlideBar& scroll   (Flt delta       , Bool immediate=false); // scroll by delta
   SlideBar& scrollTo (Flt pos         , Bool immediate=false); // scroll to pos
   SlideBar& scrollFit(Flt min, Flt max, Bool immediate=false); // scroll to fit min..max range

   SlideBar& scrollOptions(Flt relative=0.5f, Flt base=0, Bool immediate=false, Flt button_speed=1.5f); // set scrolling options, 'relative'=amount of scrolling using the mouse wheel relative to slidebar 'length' (0..Inf, default=1), 'base'=constant amount of scrolling using mouse wheel (0..Inf, default=0), 'immediate'=if mouse wheel scrolling is immediate or smooth, 'button_speed'=speed of scrolling upon pressing the left/up/right/down buttons

   SlideBar& removeSideButtons(); // remove side buttons (left/up and right/down) leaving only the middle button

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~SlideBar() {del();}
   SlideBar();

private:
   Bool       _scroll_immediate, _scroll, _vertical, _usable, _focusable;
   Flt        _scroll_to, _offset, _length, _length_total, _scroll_mul, _scroll_add, _scroll_button, _button_size;
   Ptr        _func_user;
   void     (*_func)(Ptr user);
   GuiSkinPtr _skin;

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(SlideBar);
};
/******************************************************************************/
