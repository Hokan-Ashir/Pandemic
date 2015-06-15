/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum TABS_LAYOUT
{
   TABS_AUTO      , // tabs will be set using auto-detection
   TABS_HORIZONTAL, // tabs will be set horizontally
   TABS_VERTICAL  , // tabs will be set vertically
   TABS_NUM       , // number of TABS_LAYOUT modes
};
/******************************************************************************/
STRUCT(Tab , Button) // single Tab
//{
   Tab&    del(           );
   Tab& create(C Str &text);
   Tab& create(C Tab &src ); // create from 'src'

   Tab& setCornerTab(Bool right, Bool top);

private:
   GuiObjChildren _children;
protected:
   virtual void parentClientRectChanged(C Rect *old_client, C Rect *new_client);
   virtual Bool load(File &f, CChar *path=NULL);
};
/******************************************************************************/
const_mem_addr STRUCT(Tabs , GuiObj) // Gui Tabs !! must be stored in constant memory address !!
//{
   // manage
   Tabs& del   (                                                                     );                                                         // delete
   Tabs& create(                         CChar8 **text, Int num, Bool auto_size=false);                                                         // create
   Tabs& create(                         CChar  **text, Int num, Bool auto_size=false);                                                         // create
   Tabs& create(C Rect &rect, Flt space, CChar8 **text, Int num, Bool auto_size=false) {return create(text, num).rect(rect, space, auto_size);} // create and set rectangle and space between tabs, 'auto_size'=if set tab sizes according to their name length
   Tabs& create(C Rect &rect, Flt space, CChar  **text, Int num, Bool auto_size=false) {return create(text, num).rect(rect, space, auto_size);} // create and set rectangle and space between tabs, 'auto_size'=if set tab sizes according to their name length
   Tabs& create(C Tabs &src                                                          ); // create from 'src'

   // get / set
                                                    Int         tabs      (     )C {return _tabs.elms(                );} //     get number of tabs
                                                    Tab&        tab       (Int i)  {return _tabs[i]                    ;} //     get i-th      tab
                                                  C Tab&        tab       (Int i)C {return _tabs[i]                    ;} //     get i-th      tab
           Tabs& set   (Int i, Bool quiet=false);   Int         operator()(     )C {return _sel                        ;} // set/get active    tab, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
           Tabs& toggle(Int i, Bool quiet=false);                                                                         // toggle  i-th      tab, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
           Tabs& valid (Bool        on         );   Bool        valid     (     )C {return _valid                      ;} // set/get if one    tab must be selected, if false then no tab can be selected as well, default=false
           Tabs& layout(TABS_LAYOUT layout     );   TABS_LAYOUT layout    (     )C {return _layout                     ;} // set/get tabs layout mode, default=TABS_AUTO
   virtual Tabs& desc  (C Str      &desc       ); C Str&        desc      (     )C {return super::desc()               ;} // set/get tabs description
                                                    Flt         space     (     )C {return _space                      ;} //     get tabs spacing
                                                    Bool        autoSize  (     )C {return _auto_size                  ;} //     get tabs auto size
           Tabs& skin  (C GuiSkinPtr &skin     ); C GuiSkinPtr&       skin(     )C {return _skin                       ;} // set/get skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used), changing this value will automatically change the skin of each tab
                                                    GuiSkin*       getSkin(     )C {return _skin ? _skin() : Gui.skin();} //     get actual  skin

            Tabs& func(void (*func)(Ptr   user), Ptr   user=NULL, Bool immediate=false);                                                       // set function called when tab has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) Tabs& func(void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return T.func((void(*)(Ptr))func,  user, immediate);} // set function called when tab has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) Tabs& func(void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return T.func((void(*)(Ptr))func, &user, immediate);} // set function called when tab has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)

   // operations
   T1(TYPE) Tabs& replaceClass() {_tabs.replaceClass<TYPE>(); return T;} // replace class of 'Tab'

           Tabs& rect(C Rect &rect, Flt space, Bool auto_size=false);                                           // set     rectangle and spacing between buttons, 'auto_size'=if set tab sizes according to their name length
   virtual Tabs& rect(C Rect &rect                                 );   C Rect& rect()C {return super::rect();} // set/get rectangle
   virtual Tabs& move(C Vec2 &delta                                );                                           //         move by delta

   Tab & New   (C Str &text, Int i=-1); // add    new  tab at i-th position (-1=last)
   Tabs& remove(             Int i   ); // remove i-th tab

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~Tabs() {del();}
   Tabs();

private:
   Bool        _valid, _auto_size, _func_immediate;
   Int         _sel;
   Flt         _space;
   TABS_LAYOUT _layout, _actual_layout;
   Ptr         _func_user;
   void      (*_func)(Ptr user);
   GuiSkinPtr  _skin;
   Memx<Tab>   _tabs;

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;
   virtual void parentClientRectChanged(C Rect *old_client, C Rect *new_client);

   NO_COPY_CONSTRUCTOR(Tabs);
};
/******************************************************************************/
inline Int Elms(C Tabs &tabs) {return tabs.tabs();}
/******************************************************************************/
