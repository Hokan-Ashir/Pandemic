/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum MENU_FLAG // Menu Element Flags
{
   MENU_TOGGLABLE     =0x01, // if togglable
   MENU_NOT_SELECTABLE=0x02, // if can't be selected
   MENU_HIDDEN        =0x04, // if hidden
};
/******************************************************************************/
struct MenuElm // Menu Element
{
   Str  name        , //         name (used for code commands)
        display_name; // display name
   Bool on          , // if on       (checked   ), default=false
        disabled    ; // if disabled (greyed out), default=false

            MenuElm& del   (                                                                            ); // delete
            MenuElm& create(C Str &name, void (*func)(          )=NULL            , Bool immediate=false); // create
            MenuElm& create(C Str &name, void (*func)(Ptr   user), Ptr   user=NULL, Bool immediate=false); // create
   T1(TYPE) MenuElm& create(C Str &name, void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return create(name, (void (*)(Ptr))func,  user, immediate);} // create
   T1(TYPE) MenuElm& create(C Str &name, void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return create(name, (void (*)(Ptr))func, &user, immediate);} // create

   MenuElm& flag   (  Byte  flag   );   Byte  flag ()C {return _flag ;} // set/get MENU_FLAG
   MenuElm& kbsc   (C KbSc &kbsc   );   KbSc  kbsc ()C {return _kbsc ;} // set/get keyboard shortcut
   MenuElm& kbsc2  (C KbSc &kbsc   );   KbSc  kbsc2()C {return _kbsc2;} // set/get keyboard shortcut (alternative)
   MenuElm& desc   (C Str  &desc   ); C Str&  desc ()C {return _desc ;} // set/get description
   MenuElm& setOn  (  Bool  on=true);                                   // set     if on
   MenuElm& display(C Str  &name   );                                   // set     display name, this method makes effect only if 'name' is not empty
                                        Menu* menu ()C {return _menu ;} //     get child menu

            MenuElm& func(void (*func)(          ),                  Bool immediate=false);                                                       // set function called when 'MenuElm' is selected, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
            MenuElm& func(void (*func)(Ptr   user), Ptr   user=NULL, Bool immediate=false);                                                       // set function called when 'MenuElm' is selected, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) MenuElm& func(void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return T.func((void(*)(Ptr))func,  user, immediate);} // set function called when 'MenuElm' is selected, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) MenuElm& func(void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return T.func((void(*)(Ptr))func, &user, immediate);} // set function called when 'MenuElm' is selected, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)

  ~MenuElm() {del();}
   MenuElm();

private:
   Bool   _func_immediate;
   Byte   _flag;
   Ptr    _func_user;
   void (*_func )(        );
   void (*_func2)(Ptr user);
   Str    _desc;
   KbSc   _kbsc, _kbsc2;
   Menu  *_menu;
};
/******************************************************************************/
const_mem_addr STRUCT(Menu , GuiObj) // Gui Menu !! must be stored in constant memory address !!
//{
  _List list; // list

   // manage
   Menu& del   (                                                     );                                                      // delete
   Menu& create(                                                     );                                                      // create empty
   Menu& create(C Node<MenuElm> &node, Bool check_column_hidden=false) {return create().setData(node, check_column_hidden);} // create from node of MenuElm's
   Menu& create(C Menu &src                                          );                                                      // create from 'src'

   // get / set
   void operator()(C Str &command, Bool on, Bool quiet=false) ; // set 'command' 'on' state (checked), sample usage:       ("View/Wireframe", true), 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   Bool operator()(C Str &command                           )C; // if  'command' is on      (checked), sample usage:       ("View/Wireframe")
   Bool exists    (C Str &command                           )C; // if  'command' exists in menu      , sample usage: exists("File/Exit")

            Menu& func(void (*func)(Str path, Ptr   user), Ptr   user=NULL);                                                 // set function called when any sub-element has been pushed, with 'user' as its parameter
   T1(TYPE) Menu& func(void (*func)(Str path, TYPE *user), TYPE *user     ) {return T.func((void(*)(Str, Ptr))func,  user);} // set function called when any sub-element has been pushed, with 'user' as its parameter
   T1(TYPE) Menu& func(void (*func)(Str path, TYPE &user), TYPE &user     ) {return T.func((void(*)(Str, Ptr))func, &user);} // set function called when any sub-element has been pushed, with 'user' as its parameter

   Menu& setData(C Node<MenuElm> &node, Bool check_column_hidden=false); // set data from node of MenuElm's

            Menu& setColumns(ListColumn  *column, Int columns, Bool columns_hidden);                                                                                     // set list columns
   T1(TYPE) Menu& setData   (      TYPE  *data  , Int elms   , C Memp<Bool> &visible=NULL, Bool keep_cur=false) {list.setData(data, elms, visible, keep_cur); return T;} // set data from continuous memory
   T1(TYPE) Menu& setData   ( Mems<TYPE> &mems  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {list.setData(mems,       visible, keep_cur); return T;} // set data from Mems
            Menu& setData   (_Memc       &memc  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {list.setData(memc,       visible, keep_cur); return T;} // set data from Memc
            Menu& setData   (_Memb       &memb  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {list.setData(memb,       visible, keep_cur); return T;} // set data from Memb
            Menu& setData   (_Memx       &memx  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {list.setData(memx,       visible, keep_cur); return T;} // set data from Memx
            Menu& setData   (_Meml       &meml  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {list.setData(meml,       visible, keep_cur); return T;} // set data from Meml

   Int      elms(     )C {return _elms.elms();} // get number of menu elements
   MenuElm& elm (Int i)  {return _elms[i]    ;} // get i-th      menu element
 C MenuElm& elm (Int i)C {return _elms[i]    ;} // get i-th      menu element

   virtual Menu& rect (C Rect &rect );   C Rect& rect ()C {return super::rect ();} // set/get rectangle
   virtual Menu& pos  (C Vec2 &pos  );     Vec2  pos  ()C {return super::pos  ();} // set/get top left  position
   virtual Menu& posRU(C Vec2 &pos  );     Vec2  posRU()C {return super::posRU();} // set/get top right position
   virtual Menu& move (C Vec2 &delta);                                             //         move by delta
   virtual Menu& show (             );                                             //         show

   virtual Menu& posAround(C Rect &rect, Flt align=1); // set position around the 'rect' screen rectangle while trying to avoid occluding it, 'align'=horizontal alignment (-1 .. 1) specifying on which side (left or right) the menu should be located

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~Menu() {del();}
   Menu();

private:
   Bool          _no_child_draw, _mouse_action;
   Rect          _crect;
   GuiObj       *_kb, *_owner;
   Mems<MenuElm> _elms;
   Ptr           _func_user;
   void        (*_func)(Str path, Ptr user);

   NO_COPY_CONSTRUCTOR(Menu);
};
/******************************************************************************/
inline Node<MenuElm>& operator+=(Node<MenuElm> &node, Str name) {Node<MenuElm> &child=node.New(); child.create(name); return child;}

inline Int Elms(C Menu &menu) {return Elms(menu.list);}
/******************************************************************************/
