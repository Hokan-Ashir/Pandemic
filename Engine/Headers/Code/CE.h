/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
namespace Edit{
/******************************************************************************/
enum EXE_TYPE // Executable Type
{
   EXE_EXE  , // Windows Executable
   EXE_DLL  , // Windows Dynamically Linked Library
   EXE_LIB  , // Windows Statically  Linked Library (currently not supported, reserved for future use)
   EXE_APK  , // Android Application Package
   EXE_MAC  , // Mac     Application
   EXE_IOS  , // iOS     Application
   EXE_LINUX, // Linux
   EXE_JS   , // Web     JavaScript
};
enum EXPORT_MODE // Export Mode
{
   EXPORT_EXE           , // Export to project according to current Executable Type
   EXPORT_TXT           , // Export to text files
   EXPORT_CPP           , // Export to C++  files
   EXPORT_VS            , // Export to Visual Studio version that is currently selected in the Editor
   EXPORT_VS2008        , // Export to Visual Studio 2008 project
   EXPORT_VS2010        , // Export to Visual Studio 2010 project
   EXPORT_VS2012        , // Export to Visual Studio 2012 project
   EXPORT_VS2013        , // Export to Visual Studio 2013 project
   EXPORT_ANDROID       , // Export to Android            project
   EXPORT_XCODE         , // Export to Xcode              project
   EXPORT_LINUX_MAKE    , // Export to Linux              project to be compiled using 'make'
   EXPORT_LINUX_NETBEANS, // Export to Linux              project to be compiled using NetBeans
};
enum BUILD_MODE
{
   BUILD_BUILD  ,
   BUILD_PUBLISH,
   BUILD_PLAY   ,
   BUILD_DEBUG  ,
};
enum STORAGE_MODE
{
   STORAGE_INTERNAL,
   STORAGE_EXTERNAL,
   STORAGE_AUTO    ,
};
struct CodeEditorInterface
{
   void del        ();
   void clear      ();
   void create     (GuiObj &parent, Bool menu_on_top);
   void update     (Bool active);
   void draw       ();
   void resize     ();
   void skinChanged();
   Bool initialized();
   Str  title      ();
   Str  appPath    (C Str &app_name);
   Str  androidProjectPakPath();
   Str      iOSProjectPakPath();
   void saveChanges(Memc<Edit::SaveChanges::Elm> &elms);
   void saveChanges(Memc<Edit::SaveChanges::Elm> &elms, void (*after_save_close)(Bool all_saved, Ptr user), Ptr user=NULL);
   void sourceRename     (C UID &id  ); // call this when source code file was renamed in the project
   Bool sourceCur        (C Str &name); // set current source
   Bool sourceCur        (C UID &id  ); // set current source
   Bool sourceCurIs      (           ); // if there is a current source
   Str  sourceCurName    (           ); // get current source
   UID  sourceCurId      (           ); // get current source
   Bool sourceCurModified(           ); // get current source modified state
   Bool sourceCurConst   (           ); // get current source const    state
   void sourceDrawPreview(C Str &name); // draw preview of source
   void sourceDrawPreview(C UID &id  ); // draw preview of source
   void sourceAuto       (C Str &data); // set data of the automatically generated source
   void sourceRemove     (C UID &id  ); // remove selected source
   void sourceOverwrite  (C UID &id  ); // overwrite any changes of selected source
   Bool sourceDataGet    (C UID &id,   Str &data); // get source data, false if source is not loaded
   Bool sourceDataSet    (C UID &id, C Str &data); // set source data, false if source is not loaded
   void projectsBuildPath(C Str &path); // set build path of all projects
   void menuEnabled         (Bool on);
   void kbSet               ();
   void close               ();
   void closeAll            ();
   void  hideAll            ();
   Bool visibleOptions      ();
   void visibleOptions      (Bool on);
   Bool visibleOpenedFiles  ();
   void visibleOpenedFiles  (Bool on);
   Bool visibleOutput       ();
   void visibleOutput       (Bool on);
   Bool visibleAndroidDevLog();
   void visibleAndroidDevLog(Bool on);

   void saveSettings(TextNode &code);
   void loadSettings(TextNode &code);

   void clearActiveSources(); // set all sources to be inactive (this must be called when changing app)
   void activateSource(C UID &id   ); // make project based source active
   void activateSource(C Str &name ); // make file    based source active
   void activateApp   (Bool rebuild); // finalize changing app

   void paste(C Memp<UID> &elms, GuiObj *obj, C Vec2 &screen_pos); // paste project elements at specified position
   void paste(C Str &text      , GuiObj *obj, C Vec2 &screen_pos); // paste text             at specified position
   void paste(C Str &text                                       ); // paste text             at current   position

   C Memx<Item>& items(); // get Esenthel Engine items

   void        play();
   void       debug();
   void runToCursor();
   void     publish(C UID &project_id);
   void       build();
   void     rebuild();
   void     rebuildSymbols();
   void       clean();
   void    cleanAll();
   void        stop();
   void     openIDE();
   void exportPaths(Bool    relative);
   Bool      Export(EXPORT_MODE mode);

   void     configDebug(Bool     debug);
   Bool     configDebug(              );
   void     config32Bit(Bool     bit32);
   Bool     config32Bit(              );
   void     configDX9  (Bool     dx9  );
   Bool     configDX9  (              );
   void     configEXE  (EXE_TYPE exe  );
   EXE_TYPE configEXE  (              );

   virtual void visibleChangedOptions      () {}
   virtual void visibleChangedOpenedFiles  () {}
   virtual void visibleChangedOutput       () {}
   virtual void visibleChangedAndroidDevLog() {}

   virtual void configChangedDebug() {}
   virtual void configChanged32Bit() {}
   virtual void configChangedDX9  () {}
   virtual void configChangedEXE  () {}

   virtual Str          appName                 () {return                S;} // get name                    of current app
   virtual Str          appDirsWindows          () {return                S;} // get all directories         of current app
   virtual Str          appDirsNonWindows       () {return                S;} // get all directories         of current app
   virtual Str          appHeadersWindows       () {return                S;} // get all headers             of current app
   virtual Str          appHeadersNonWindows    () {return                S;} // get all headers             of current app
   virtual Str          appLibsWindows          () {return                S;} // get all libraries           of current app
   virtual Str          appLibsMac              () {return                S;} // get all libraries           of current app
   virtual Str          appLibsLinux            () {return                S;} // get all libraries           of current app
   virtual Str          appLibsAndroid          () {return                S;} // get all libraries           of current app
   virtual Str          appLibsiOS              () {return                S;} // get all libraries           of current app
   virtual Str          appPackage              () {return                S;} // get package name            of current app
   virtual Str          appLocationUsageReason  () {return                S;} // get location usage reason   of current app
   virtual Int          appBuild                () {return                1;} // get build number            of current app
   virtual ULong        appFacebookAppID        () {return                0;} // get Facebook App ID         of current app
   virtual STORAGE_MODE appPreferredStorage     () {return STORAGE_INTERNAL;} // get preferred storage       of current app
   virtual UInt         appSupportedOrientations() {return                0;} // get supported orientations  of current app (DIR_FLAG)
   virtual UID          appGuiSkin              () {return          UIDZero;} // get default Gui Skin        of current app
   virtual ImagePtr     appIcon                 () {return             NULL;} // get icon                    of current app
   virtual ImagePtr     appImagePortrait        () {return             NULL;} // get portrait  splash screen of current app
   virtual ImagePtr     appImageLandscape       () {return             NULL;} // get landscape splash screen of current app
   virtual Bool         appEmbedEngineData      () {return            false;} // get if embed   engine  data of current app
   virtual Bool         appPublishProjData      () {return             true;} // get if publish project data of current app
   virtual Bool         appPublishPhysxDll      () {return             true;} // get if copy physx dll's     of current app
   virtual Bool         appPublishDataAsPak     () {return             true;} // get if publish data as paks of current app
   virtual Bool         appWindowsCodeSign      () {return            false;} // get if code sign exe        of current app
   virtual void         appSpecificFiles        (Memp<PakFileData> files)  {} // get specific files          of current app
   virtual void         appPackageInvalid       (C Str &msg             )  {} // called when package name was detected as invalid

   virtual Rect         menuRect    (                      ) {return Rect(-D.w(), -D.h(), D.w(), D.h());}
   virtual Rect       sourceRect    (                      ) {return Rect(-D.w(), -D.h(), D.w(), D.h());}
   virtual Str        sourceProjPath(C UID &id             ) {return S;}
   virtual ERROR_TYPE sourceDataLoad(C UID &id,   Str &data) {return EE_ERR_ELM_NOT_FOUND;}
   virtual Bool       sourceDataSave(C UID &id, C Str &data) {return false;}
   virtual void       sourceChanged () {} // called on change of current source

   virtual void publishSuccess(C Str &exe_name, EXE_TYPE exe_type, BUILD_MODE build_mode, C UID &project_id) {}

   virtual void validateActiveSources() {} // called when sources need to have their activation reset

   virtual Bool elmValid    (C UID &id              ) {return false;} // if element of this ID exists in the project
   virtual Str  elmBaseName (C UID &id              ) {return     S;} // get base name of element
   virtual Str  elmFullName (C UID &id              ) {return     S;} // get full name of element
   virtual void elmHighlight(C UID &id, C Str  &name) {             } // highlight element
   virtual void elmOpen     (C UID &id              ) {             } // open      element
   virtual void elmLocate   (C UID &id              ) {             } // locate    element
   virtual void elmPreview  (C UID &id, C Vec2 &pos, Bool mouse, C Rect &clip) {} // draw element preview at 'pos' position, 'mouse'=if triggered by mouse

   virtual Str idToText(C UID &id, Bool *valid=NULL) {if(valid)*valid=false; return S;} // return ID in text format (this can be element/object/waypoint/.. ID)

   struct ElmLink
   {
      UID      id;
      Str      full_name;
      ImagePtr icon;

      void set(C UID &id, C Str &full_name, C ImagePtr &icon) {T.id=id; T.full_name=full_name; T.icon=icon;}
   };
   virtual void getProjPublishElms(Memc<ElmLink> &elms) {} // get list of project elements for publishing
};
} // namespace
/******************************************************************************/
