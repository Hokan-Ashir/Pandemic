/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum COMBOBOX_FLAG // Combobox Flag
{
   COMBOBOX_MOUSE_WHEEL=0x1, // if mouse wheel can change selection
   COMBOBOX_CONST_TEXT =0x2, // if don't change text value
};
/******************************************************************************/
const_mem_addr STRUCT(ComboBox , Button) // Gui ComboBox !! must be stored in constant memory address !!
//{
   Byte flag      ; // COMBOBOX_FLAG, default=COMBOBOX_MOUSE_WHEEL
   Flt  menu_align; // menu horizontal alignment (-1 .. 1), default=1, this value specifies on which side (left or right) the menu should be activated
   Menu menu      ; // menu

   // manage
   ComboBox& del   (                                      );                                                  // delete
   ComboBox& create(                                      );                                                  // create empty
   ComboBox& create(C Rect &rect                          ) {return create().                    rect(rect);} // create empty and set rectangle
   ComboBox& create(              CChar8 *data[], Int elms) {return create().setData(data, elms)           ;} // create from text array
   ComboBox& create(C Rect &rect, CChar8 *data[], Int elms) {return create().setData(data, elms).rect(rect);} // create from text array and set rectangle
   ComboBox& create(              CChar  *data[], Int elms) {return create().setData(data, elms)           ;} // create from text array
   ComboBox& create(C Rect &rect, CChar  *data[], Int elms) {return create().setData(data, elms).rect(rect);} // create from text array and set rectangle
   ComboBox& create(              Node<MenuElm>      &node) {return create().setData(node      )           ;} // create from node of menu elements
   ComboBox& create(C Rect &rect, Node<MenuElm>      &node) {return create().setData(node      ).rect(rect);} // create from node of menu elements and set rectangle
   ComboBox& create(C ComboBox &src                       );                                                  // create from 'src'

   // data
            ComboBox& clear(); // clear data

            ComboBox& setData(CChar8 *data[], Int elms                          ); // set data from text array
            ComboBox& setData(CChar  *data[], Int elms                          ); // set data from text array
            ComboBox& setData(Node<MenuElm> &node, Bool check_column_hidden=true); // set data from node of menu elements

            ComboBox& setColumns(ListColumn  *column, Int columns, Bool columns_hidden=true                       ) {menu.setColumns(column, columns, columns_hidden); return T;} // set list columns
   T1(TYPE) ComboBox& setData   (      TYPE  *data  , Int elms   , C Memp<Bool> &visible=NULL, Bool keep_cur=false) {menu.setData   (data, elms, visible, keep_cur  ); return T;} // set data from continuous memory
   T1(TYPE) ComboBox& setData   ( Mems<TYPE> &mems  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {menu.setData   (mems,       visible, keep_cur  ); return T;} // set data from Mems
            ComboBox& setData   (_Memc       &memc  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {menu.setData   (memc,       visible, keep_cur  ); return T;} // set data from Memc
            ComboBox& setData   (_Memb       &memb  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {menu.setData   (memb,       visible, keep_cur  ); return T;} // set data from Memb
            ComboBox& setData   (_Memx       &memx  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {menu.setData   (memx,       visible, keep_cur  ); return T;} // set data from Memx
            ComboBox& setData   (_Meml       &meml  ,              C Memp<Bool> &visible=NULL, Bool keep_cur=false) {menu.setData   (meml,       visible, keep_cur  ); return T;} // set data from Meml

   // set / get
           ComboBox& set    (  Int   sel             , Bool quiet=false);   Int   operator()()C {return _sel;}    // set/get active selection, -1=none , 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
           ComboBox& setText(C Str  &text, Bool force, Bool quiet=false);                                         // set     active selection from text, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called), if 'text' not found : -1 is set and text is set depending on 'force' (false:set(""), true:set(text))
   virtual ComboBox& rect   (C Rect &rect                              ); C Rect& rect()C {return super::rect();} // set/get rectangle

            ComboBox& func(void (*func)(Ptr   user), Ptr   user=NULL, Bool immediate=false);                                                       // set function called when selection has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) ComboBox& func(void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return T.func((void(*)(Ptr))func,  user, immediate);} // set function called when selection has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) ComboBox& func(void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return T.func((void(*)(Ptr))func, &user, immediate);} // set function called when selection has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object

  ~ComboBox() {del();}
   ComboBox();

private:
   Bool   _func_immediate;
   Int    _sel;
   Ptr    _func_user;
   void (*_func)(Ptr user);

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(ComboBox);
};
/******************************************************************************/
inline Int Elms(C ComboBox &combobox) {return Elms(combobox.menu);}
/******************************************************************************/
