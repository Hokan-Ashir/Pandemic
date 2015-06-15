/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
const_mem_addr STRUCT(TextLine , GuiObj) // Gui TextLine !! must be stored in constant memory address !!
//{
   Bool             kb_catch , // if can catch          keyboard focus by pressing Tab key, default=true
                    kb_lit   , // if highlight when has keyboard focus                    , default=true
                    show_find; // if show find image when there's no text entered         , default=false
   Str              hint     ; // hint displayed     when there's no text entered         , default=""
   GuiSkinPtr       skin     ; // skin override                                           , default=NULL (if set to NULL then current value of 'Gui.skin' is used)
   FixedElm<Button> reset    ; // reset/clear button                                      , default=created but hidden

   // manage
   TextLine& del   (                               );                                     // delete
   TextLine& create(                  C Str &text=S);                                     // create
   TextLine& create(C Rect     &rect, C Str &text=S) {create(text).rect(rect); return T;} // create
   TextLine& create(C TextLine &src                );                                     // create from 'src'

   // get / set
   Bool   password  ()C;                        TextLine& password (  Bool on                    ); // get/set if in password mode (in password mode text characters will be displayed as '*', and you will not be able to copy it using keyboard shortcuts)
   Int    maxLength ()C {return _max_length;}   TextLine& maxLength(  Int  max_length            ); // get/set maximum allowed text length (-1=no limit)
   Int    cursor    ()C {return _edit.cur  ;}   TextLine& cursor   (  Int  position              ); // get/set cursor position
   C Str& operator()()C {return _text      ;}   TextLine& set      (C Str &text, Bool quiet=false); // get/set text, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
                                                TextLine& clear    (             Bool quiet=false); // clear   text, 'quiet'=if apply the value in quiet mode (if set to true then 'func' will not be called)
   GuiSkin*  getSkin()C {return skin ? skin() : Gui.skin();}                                        // get     actual skin

            TextLine& func(void (*func)(Ptr   user), Ptr   user=NULL, Bool immediate=false);                                                       // set function called when text has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) TextLine& func(void (*func)(TYPE *user), TYPE *user     , Bool immediate=false) {return T.func((void(*)(Ptr))func,  user, immediate);} // set function called when text has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)
   T1(TYPE) TextLine& func(void (*func)(TYPE &user), TYPE &user     , Bool immediate=false) {return T.func((void(*)(Ptr))func, &user, immediate);} // set function called when text has changed, with 'user' as its parameter, 'immediate'=if call the function immediately when a change occurs (this will happen inside object update function where you cannot delete any objects) if set to false then the function will get called after all objects finished updating (there you can delete objects)

   virtual TextLine& rect(C Rect &rect );   C Rect& rect()C {return super::rect();} // set/get rectangle
   virtual TextLine& move(C Vec2 &delta);                                           // move by delta

   // operations
   TextLine& selectNone  (); // select no  text
   TextLine& selectAll   (); // select all text
   TextLine& selectExtNot(); // select all but extension

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~TextLine() {del();}
   TextLine();

private:
   Bool     _can_select, _func_immediate;
   Int      _max_length;
   Flt      _offset;
   Str      _text;
   TextEdit _edit;
   Ptr      _func_user;
   void   (*_func)(Ptr user);

protected:
   virtual void save(File &f, CChar *path=NULL)C;
   virtual Bool load(File &f, CChar *path=NULL) ;

   NO_COPY_CONSTRUCTOR(TextLine);
};
/******************************************************************************/
