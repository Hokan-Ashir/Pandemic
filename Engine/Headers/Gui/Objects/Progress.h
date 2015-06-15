/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum PROGRESS_MODE // Progress Bar Mode
{
   PROGRESS_NONE   , // don't draw any text
   PROGRESS_PERCENT, // draw text as percentage 0..100
   PROGRESS_REAL   , // draw text as real value 0..1
};
/******************************************************************************/
const_mem_addr STRUCT(Progress , GuiObj) // Gui ProgressBar !! must be stored in constant memory address !!
//{
   PROGRESS_MODE mode; // progress mode
   GuiSkinPtr    skin; // skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used)

   // manage
   Progress& del   (                                                  );                                     // delete
   Progress& create(                  PROGRESS_MODE mode=PROGRESS_NONE);                                     // create
   Progress& create(C Rect     &rect, PROGRESS_MODE mode=PROGRESS_NONE) {create(mode).rect(rect); return T;} // create
   Progress& create(C Progress &src                                   );                                     // create from 'src'

   // set/get
   Progress& clear     (                );                                      // clear progress
   Progress& set       (Int  x, Int  max);                                      // set   progress from integer values "x/max"
   Progress& set       (Long x, Long max);                                      // set   progress from integer values "x/max"
   Progress& set       (Flt  progress   );                                      // set   progress (0..1)
   Flt       operator()(                )C {return _progress                 ;} // get   progress (0..1)
   GuiSkin*  getSkin   (                )C {return skin ? skin() : Gui.skin();} // get   actual skin

   // main
   virtual void draw(C GuiPC &gpc); // draw object

  ~Progress() {del();}
   Progress();

private:
   Flt _progress;

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(Progress);
};
/******************************************************************************/
