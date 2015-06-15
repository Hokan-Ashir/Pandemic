/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(GuiCustom , GuiObj) // Gui Custom Object !! must be stored in constant memory address !!
//{
   // manage
   GuiCustom& del   (                                );                                     // delete
   GuiCustom& create(                   Ptr user=NULL);                                     // create
   GuiCustom& create(C Rect      &rect, Ptr user=NULL) {create(user).rect(rect); return T;} // create
   GuiCustom& create(C GuiCustom &src                );                                     // create from 'src'

   // set / get
   GuiCustom& focusable(Bool on);   Bool focusable()C {return _focusable;} // set/get if can catch keyboard focus, default=false

  ~GuiCustom() {del();}
   GuiCustom();

private:
   Bool _focusable;

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(GuiCustom);
};
/******************************************************************************/
