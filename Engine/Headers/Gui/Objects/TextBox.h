/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(TextBox , GuiObj) // Gui TextBox !! must be stored in constant memory address !! TextBox is not yet implemented !!
//{
   GuiSkinPtr skin; // skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)

   // manage
   TextBox& del   (              ); // delete
   TextBox& create(              ); // create
   TextBox& create(C TextBox &src); // create from 'src'

   GuiSkin* getSkin()C {return skin ? skin() : Gui.skin();} // get actual skin

   // main
   virtual void draw(C GuiPC &gpc); // draw object

  ~TextBox() {del();}
   TextBox();

   NO_COPY_CONSTRUCTOR(TextBox);
};
/******************************************************************************/
