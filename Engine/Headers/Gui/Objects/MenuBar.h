/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum MENU_BAR_FLAG
{
   MENU_BAR_INHERIT=0x1, // allow keyboard shortcuts to enable elements of not only this MenuBar but also from parent objects which contain other MenuBar objects
};
/******************************************************************************/
const_mem_addr STRUCT(MenuBar , GuiObj) // Gui Menu Bar !! must be stored in constant memory address !!
//{
   struct Elm // Menu Element
   {
      Str  name        , //         name (used for code commands)
           display_name; // display name
      Menu menu        ;

      Elm();

   private:
      Bool hidden;
      Flt  x, w;
   };

   Byte       flag; // MENU_BAR_FLAG, default=0
   GuiSkinPtr skin; // skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)

   // manage
   MenuBar& del   (                     ); // delete manually
   MenuBar& create(C Node<MenuElm> &node); // create, 'node'=menu node
   MenuBar& create(C MenuBar       &src ); // create from 'src'

   // get / set
   Int  elms(     )C {return _elms.elms();} // get number of menu elements
   Elm& elm (Int i)  {return _elms[i]    ;} // get i-th      menu element
 C Elm& elm (Int i)C {return _elms[i]    ;} // get i-th      menu element

   void operator()(C Str &command, Bool on, Bool quiet=false) ; // set 'command' 'on' state (enabled), sample usage:       ("View/Wireframe",true), 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   Bool operator()(C Str &command                           )C; // if  'command' is on      (enabled), sample usage:       ("View/Wireframe")
   Bool exists    (C Str &command                           )C; // if  'command' exists in menu      , sample usage: exists("File/Exit")

   MenuBar& setCommand(C Str &command, Bool visible, Bool enabled);                                            // set 'command' visibility and if not disabled
   MenuBar& setCommand(C Str &command, Bool state                ) {return setCommand(command, state, state);} // set 'command' visibility and if not disabled

   virtual MenuBar& rect(C Rect &rect);   C Rect& rect()C {return super::rect();} // set/get rectangle

   GuiSkin* getSkin()C {return skin ? skin() : Gui.skin();} // get actual skin

   // main
   virtual void update(C GuiPC &gpc); // update object
   virtual void draw  (C GuiPC &gpc); // draw   object

  ~MenuBar() {del();}
   MenuBar();

private:
   Bool      _alt;
   Int       _lit, _push, _menu_prev;
   Mems<Elm> _elms;

protected:
   virtual void parentClientRectChanged(C Rect *old_client, C Rect *new_client);

   NO_COPY_CONSTRUCTOR(MenuBar);
};
/******************************************************************************/
inline Int Elms(C MenuBar &menu) {return menu.elms();}
/******************************************************************************/
