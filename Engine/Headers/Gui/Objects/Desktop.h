/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(Desktop , GuiObj) // Gui Desktop !! must be stored in constant memory address !!
//{
   // manage
   Desktop& del   (              ); // manually delete
   Desktop& create(              ); // create
   Desktop& create(C Desktop &src); // create from 'src'

   // main
   GuiObj* test  (C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   void    update(); // update object
   void    draw  (); // draw   object

  ~Desktop() {del();}
   Desktop();

private:
   GuiObjChildren _children;
   NO_COPY_CONSTRUCTOR(Desktop);
};
/******************************************************************************/
