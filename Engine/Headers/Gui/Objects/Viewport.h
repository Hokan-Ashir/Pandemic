/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(Viewport , GuiObj) // Viewport !! must be stored in constant memory address !!
//{
   // saved
   Color rect_color; // rectangle color, default=Gui.borderColor

   // following members are not saved in the 'save' method
   FOV_MODE fov_mode             ; // field of view mode      , default=D.viewFovMode()
   Flt      fov                  , // field of view           , default=D.viewFov    ()
            from                 , // viewport near clip plane, default=D.viewFrom   ()
            range                ; // viewport far  clip plane, default=D.viewRange  ()
   void   (*draw_func)(Viewport&); // pointer to drawing function

   // manage
   Viewport& del   (                                                             );                                           // delete
   Viewport& create(                  void (*draw)(Viewport&)=NULL, Ptr user=NULL);                                           // create
   Viewport& create(C Rect     &rect, void (*draw)(Viewport&)=NULL, Ptr user=NULL) {create(draw, user).rect(rect); return T;} // create
   Viewport& create(C Viewport &src                                              );                                           // create from 'src'

   // operations
   void setDisplayView()C; // activate display viewport settings from current viewport parameters

   // main
   virtual GuiObj* test(C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    draw(C GuiPC &gpc); // draw object

  ~Viewport() {del();}
   Viewport();

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(Viewport);
};
/******************************************************************************/
