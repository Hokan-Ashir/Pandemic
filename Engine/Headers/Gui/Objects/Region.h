/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(Region , GuiObj) // Gui Region !! must be stored in constant memory address !!
//{
   Bool                    kb_lit       ; // if highlight when has keyboard focus, default=true
   Flt                     slidebar_size; // slidebar size                       , default=0.05
   FixedElm  <Button     > view         ; // view button
   FixedArray<SlideBar, 2> slidebar     ; // 2 slidebars (0=horizontal, 1=vertical)

   // manage
   Region& del   (              );                                 // delete
   Region& create(              );                                 // create
   Region& create(C Rect   &rect) {create().rect(rect); return T;} // create
   Region& create(C Region &src );                                 // create from 'src'

   // operations
   Region& scrollX   (Flt delta       , Bool immediate=false) {slidebar[0].scroll   (delta   , immediate); return T;} // horizontal scroll by delta
   Region& scrollToX (Flt pos         , Bool immediate=false) {slidebar[0].scrollTo (pos     , immediate); return T;} // horizontal scroll to pos
   Region& scrollFitX(Flt min, Flt max, Bool immediate=false) {slidebar[0].scrollFit(min, max, immediate); return T;} // horizontal scroll to fit min..max range

   Region& scrollY   (Flt delta       , Bool immediate=false) {slidebar[1].scroll   (delta   , immediate); return T;} // vertical scroll by delta
   Region& scrollToY (Flt pos         , Bool immediate=false) {slidebar[1].scrollTo (pos     , immediate); return T;} // vertical scroll to pos
   Region& scrollFitY(Flt min, Flt max, Bool immediate=false) {slidebar[1].scrollFit(min, max, immediate); return T;} // vertical scroll to fit min..max range

   Region& removeSlideBars(); // remove slide bars

   // set / get
   virtual Region& rect       (C Rect &rect                             ); C Rect& rect        ()C {return super::rect()                        ;} // set/get rectangle
   virtual Region& move       (C Vec2 &delta                            );                                                                         // move by delta
                                                                             Flt   clientWidth ()C {return      _crect.w          ()            ;} //     get client  width
                                                                             Flt   clientHeight()C {return      _crect.h          ()            ;} //     get client  height
                                                                             Vec2  clientSize  ()C {return      _crect.size       ()            ;} //     get client  size
                                                                           C Rect& clientRect  ()C {return      _crect                          ;} //     get client  rectangle
                                                                             Flt  virtualWidth ()C {return slidebar[0].lengthTotal()            ;} //     get virtual width
                                                                             Flt  virtualHeight()C {return slidebar[1].lengthTotal()            ;} //     get virtual height
           Region& virtualSize(C Vec2       *size                       );   Vec2 virtualSize  ()C {return Vec2(virtualWidth(), virtualHeight());} // set/get virtual size, pass NULL to automatically calculate according to children
           Region& skin       (C GuiSkinPtr &skin, Bool sub_objects=true); C GuiSkinPtr&   skin()C {return _skin                                ;} // set/get skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used), 'sub_objects'=if additionally change the skin of the region slidebars and view button
                                                                             GuiSkin*   getSkin()C {return _skin ? _skin() : Gui.skin()         ;} //     get actual  skin

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~Region() {del();}
   Region();

private:
   Rect           _crect;
   GuiSkinPtr     _skin;
   GuiObjChildren _children;

protected:
   virtual void childRectChanged(C Rect *old_rect, C Rect *new_rect, GuiObj &child);

   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(Region);
};
/******************************************************************************/
