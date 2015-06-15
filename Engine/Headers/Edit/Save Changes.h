/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
namespace Edit{
/******************************************************************************/
STRUCT(SaveChanges , ClosableWindow)
//{
   struct Elm
   {
      Str name, display;
      UID id;
      Ptr user;

      // set
      Elm& set  (C Str &name, C Str &display, C UID &id=UIDZero, Ptr user=NULL) {T.name=name; T.display=display; T.id=id; T.user=user; return T;}
      Elm& save (Bool (*func)(Elm &elm)=NULL                                  ) {T._save =func;                                        return T;}
      Elm& close(void (*func)(Elm &elm)=NULL                                  ) {T._close=func;                                        return T;}

      // operations
      Bool doSaveClose();
      void doClose    ();

      Elm() {id.zero(); user=NULL; _save=NULL; _close=NULL;}

   private:
      Bool (*_save )(Elm &elm);
      void (*_close)(Elm &elm);
   };

   Memc<Elm> elms;
   List<Elm> list;
   Region    region;
   Button    save, close, cancel;

   // statics
   static void Save  (SaveChanges &sc) {sc.doSave ();}
   static void Close (SaveChanges &sc) {sc.doClose();}
   static void Cancel(SaveChanges &sc) {sc.hide   ();}

   // manage
   void create();

   // set
            void set(C Memp<Elm> &elms, void (*after_save_close)(Bool all_saved, Ptr   user)=NULL, Ptr   user=NULL);
   T1(TYPE) void set(C Memp<Elm> &elms, void (*after_save_close)(Bool all_saved, TYPE *user)     , TYPE *user     ) {set(elms, (void(*)(Bool, Ptr))after_save_close,  user);}
   T1(TYPE) void set(C Memp<Elm> &elms, void (*after_save_close)(Bool all_saved, TYPE &user)     , TYPE &user     ) {set(elms, (void(*)(Bool, Ptr))after_save_close, &user);}

   // operations
   void clear  ();
   void doSave ();
   void doClose();

   virtual Rect    sizeLimit(            )C;
   virtual Window& rect     (C Rect &rect) ;

   SaveChanges() {_after_save_close=NULL; _user=NULL;}

private:
   void (*_after_save_close)(Bool all_saved, Ptr user);
   Ptr    _user;
};
/******************************************************************************/
} // namespace
/******************************************************************************/
