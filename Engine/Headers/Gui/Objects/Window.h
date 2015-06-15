/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum WIN_FLAG // Window Flags
{
   WIN_MOVABLE  =0x01, // movable
   WIN_RESIZABLE=0x02, // resizable
};
/******************************************************************************/
const_mem_addr STRUCT(Window , GuiObj) // Gui Window !! must be stored in constant memory address !!
//{
   Byte      flag       , // WIN_FLAG      , default=WIN_MOVABLE
             resize_mask; // specifies which edges of the window can be resized, default=DIRF_RIGHT|DIRF_LEFT|DIRF_DOWN|DIRF_UP (used only if 'flag' has WIN_RESIZABLE enabled)
   Str       text       ; // title bar text, default=""
   Button    button[3]  ; // buttons : 0-minimize, 1-maximize, 2-close
   RippleFx *ripple     ; // ripple effect , default=NULL

   // manage
   Window& del   (                             );                                     // delete
   Window& create(                C Str &text=S);                                     // create
   Window& create(C Rect   &rect, C Str &text=S) {create(text).rect(rect); return T;} // create and set rectangle
   Window& create(C Window &src                );                                     // create from 'src'

   // set / get
           Window& set       (C Str        &text   );                                                                        // set     title bar text
   virtual Window& move      (C Vec2       &delta  );                                                                        //         move by delta
   virtual Window& rect      (C Rect       &rect   ); C Rect&       rect          ()C {return super::rect()               ;} // set/get rectangle
           Window& level     (  Int         level  );   Int         level         ()C {return _level                      ;} // set/get window level (windows with level 1 will always be drawn on top of level 0 windows), default=0
           Window& skin      (C GuiSkinPtr &skin   ); C GuiSkinPtr&    skin       ()C {return _skin                       ;} // set/get skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used), changing this value will automatically change the skin of the window buttons
                                                        GuiSkin*    getSkin       ()C {return _skin ? _skin() : Gui.skin();} //     get actual skin
           Window& barVisible(  Bool        visible);   Bool        barVisible    ()C {return _bar_visible                ;} // set/get title bar visibility, default=true
                                                        Flt         barHeight     ()C;                                       //     get title bar height
                                                        Flt         highlightHover()C {return _lit_hover                  ;} //     get current hover highlight (0..1)
                                                        Flt         highlightFocus()C {return _lit_focus                  ;} //     get current focus highlight (0..1)
           Window& alpha     (  Flt         alpha  );   Flt              alpha    ()C {return _alpha                      ;} // set/get custom  window opacity controlled by the user         (0..1)
                                                        Flt          fadeAlpha    ()C {return _fade_alpha                 ;} //     get current window opacity based on the fade effect       (0..1)
                                                        Flt         finalAlpha    ()C {return _final_alpha                ;} //     get final   window opacity based on custom and fade alpha (0..1), this is "alpha()*fadeAlpha()"
                                                        Flt         clientWidth   ()C {return _crect.w   ()               ;} //     get client width
                                                        Flt         clientHeight  ()C {return _crect.h   ()               ;} //     get client height
                                                        Vec2        clientSize    ()C {return _crect.size()               ;} //     get client size
           Window& clientRect(C Rect       &rect   ); C Rect&       clientRect    ()C {return _crect                      ;} // set/get client rect

   virtual Rect sizeLimit              (               )C {return Rect(0.045f, 0.045f, Max(4, D.w()*2), Max(4, D.h()*2));} // allowed size limits for the Window rectangle, you can override this method and return custom values, they will be used by 'rect' method
   virtual void extendedRect           (Rect &rect     )C; // get extended rectangle (including self and all child elements extending it visually)
           void defaultInnerPadding    (Rect &padding  )C; // get default inner padding
           void defaultInnerPaddingSize(Vec2 &padd_size)C; // get default inner padding size
           Vec2 defaultInnerPaddingSize(               )C; // get default inner padding size
           Flt  defaultBarHeight       (               )C; // get default bar height
           Flt  defaultBarTextWidth    (               )C; // get default bar text width
           Flt  defaultBarFullWidth    (               )C; // get default bar full width including text and visible buttons

   // operations
           Bool    showing   (       )C; // if visible and not fading out
           Bool    hiding    (       )C; // if hidden  or      fading out
   virtual Window& fadeIn    (       ) ; // fade in  window
   virtual Window& fadeOut   (       ) ; // fade out window
   virtual Window& fadeToggle(       ) ; // toggle fading
   virtual Window& fade      (Bool in) ; // set    fading
   virtual Window& show      (       ) ; // show
   virtual Window& hide      (       ) ; // hide

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~Window() {del();}
   Window();

private:
   Bool           _bar_visible;
   Byte           _fade_type, _resize;
   Int            _level;
   Flt            _alpha, _fade_alpha, _final_alpha, _lit_hover, _lit_focus;
   Rect           _crect;
   GuiSkinPtr     _skin;
   GuiObjChildren _children;

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;
   virtual void parentClientRectChanged(C Rect *old_client, C Rect *new_client);

   NO_COPY_CONSTRUCTOR(Window);
};
/******************************************************************************/
STRUCT(ClosableWindow , Window) // Closable Window (automatically hides on Escape or Middle Mouse Button)
//{
   virtual void update(C GuiPC &gpc)
   {
      super::update(gpc);
      if(Gui.window()==this && button[2].func()) // this is the active window and close button has a function assigned
      {
         if(Kb.bp(KB_ESC) || Kb.bp(KB_NAV_BACK) || (Ms.bp(2) && contains(Gui.ms())))
         {
            Kb.eat(KB_ESC); Kb.eat(KB_NAV_BACK); Ms.eat(2); button[2].push(); // use "button.push" to trigger calling custom function assigned to that button
         }
      }
   }
};
/******************************************************************************/
