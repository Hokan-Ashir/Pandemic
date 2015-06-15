/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'App' to setup initial application parameters inside 'InitPre' function.

/******************************************************************************/
enum APP_FLAG // Application Flags
{
   APP_NO_TITLE_BAR                    =1<< 0, // application window will have no title bar [Supported Platforms: Windows, Linux]
   APP_NO_CLOSE                        =1<< 1, // application won't be closed by Alt+F4 or when received one of the following messages in window loop : WM_QUIT WM_CLOSE WM_DESTROY
   APP_MINIMIZABLE                     =1<< 2, // apllication will have minimize box on the window
   APP_MAXIMIZABLE                     =1<< 3, // apllication will have maximize box on the window
   APP_RESIZABLE                       =1<< 4, // application window can be resized by dragging the window edges/corners
   APP_HIDDEN                          =1<< 5, // application window will be initially hidden
   APP_FULL_TOGGLE                     =1<< 6, // display can be altered with Alt+Enter keys (windowed/fullscreen toggle), Alt+Shift+Enter can also be used to switch into fullscreen with resolution taken from the window size
   APP_WORK_IN_BACKGROUND              =1<< 7, // application will work also in background (when not focused)
   APP_ON_RUN_EXIT                     =1<< 8, // if the application is already running in another instance, then new instance will not be created, but instead the existing instance window will be activated
   APP_ON_RUN_WAIT                     =1<< 9, // if the application is already running in another instance, then wait until it exits and then continue
   APP_KB_EXCLUSIVE                    =1<<10, // initialize keyboard in exclusive mode (which disables windows key) [Supported Platforms: Windows]
   APP_MS_EXCLUSIVE                    =1<<11, // initialize mouse    in exclusive mode (which hides cursor and clips it to the application window)
   APP_MEM_LEAKS                       =1<<12, // error will be shown at program exit if memory leaks were found, use this only for debugging as it may slow down the application [Supported Platforms: Windows]
   APP_NO_PAUSE_ON_WINDOW_MOVE_SIZE    =1<<13, // application will not pause when the main window is being moved or resized [Supported Platforms: Windows, other platforms don't need this]
   APP_DX_FAKE_FULLSCREEN              =1<<14, // use this option to force DirectX to use fake fullscreen mode, this will enable overlay windows drawn on top of the Application, however this will also slow down the performance of fullscreen mode [Supported Platforms: Windows]
   APP_DX_MANAGEMENT                   =1<<15, // this flag specifies that DirectX should handle data management instead of the Graphics Driver [Supported Platforms: Windows DirectX 9]
   APP_DX_THREAD_SAFE                  =1<<16, // this flag specifies that DirectX should be multi-threaded safe, this slows down all DirectX calls and makes rendering slower, the engine is already multi-thread safe when it comes to managing GPU resources, which means that this flag is not needed when performing operations on different GPU resources on multiple threads, use this only for debugging if you suspect DirectX/Driver error [Supported Platforms: Windows]
   APP_AUTO_FREE_IMAGE_OPEN_GL_ES_DATA =1<<17, // this flag is used only for OpenGL ES, it specifies that all Images will automatically call 'freeOpenGLESData' after loading their data, the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file), you can enable this option for release version of your game to reduce its memory usage
   APP_AUTO_FREE_MESH_OPEN_GL_ES_DATA  =1<<18, // this flag is used only for OpenGL ES, it specifies that all Meshes will automatically call 'freeOpenGLESData' after loading their data, the method frees the software copy of the GPU data which increases available memory, however after calling this method the data can no longer be accessed on the CPU (can no longer be locked or saved to file), you can enable this option for release version of your game to reduce its memory usage
   APP_AUTO_FREE_PHYS_BODY_HELPER_DATA =1<<19, // 'PhysBody'  objects will automatically call their 'freeHelperData'          method after loading from file, this will free up some memory, however it will disable saving the 'PhysBody' to file, or converting it to 'MeshBase', you can enable this option for release version of your game to reduce its memory usage
   APP_AUTO_MATERIAL_CONVERT_ALPHA_TEST=1<<20, // 'Material'  objects will automatically call their 'convertAlphaTest(false)' method after loading from file, this can be used for mobile platforms to increase rendering performance
   APP_ALLOW_NO_GPU                    =1<<21, // allow application to run if the graphics driver does not meet the minimum requirements, this mode is recommended for server applications where GPU can be limited or not available. This flag works differently for different API's : if in DX9 the graphics failed to initialize then application will run but with graphics disabled, if in DX10+ the graphics failed to initialize then application will run and will display graphics but using "WARP - Windows Advanced Rasterization Platform" which uses CPU for graphics, in order to ensure maximum CPU performance on servers you may want to create the application window small - less pixels to draw = smaller CPU usage, or minimize the application window at startup = completely disables any drawing/rendering, in OpenGL graphics will always be disabled when using this flag
   APP_EXIT_IMMEDIATELY                =1<<22, // if this flag is specified then the application will exit immediately after 'InitPre' function
   APP_BREAKPOINT_ON_ERROR             =1<<23, // if program encounters an error and 'Exit' function is called, then breakpoint will be forced by calling the 'Break' during the 'Exit' function, allowing you to enter debug mode, use this option only for debugging
   APP_CALLSTACK_ON_ERROR              =1<<24, // if program encounters an error and 'Exit' function is called, then current call stack will be included in the error message [Supported Platforms: Windows]
   APP_NO_OCULUS_RIFT                  =1<<25, // disable usage of Oculus Rift SDK as it may cause crashes for apps loaded from DLL files from memory using DLL.createMem

   APP_AUTO_FREE_OPEN_GL_ES_DATA=APP_AUTO_FREE_IMAGE_OPEN_GL_ES_DATA|APP_AUTO_FREE_MESH_OPEN_GL_ES_DATA,
};
/******************************************************************************/
enum AWAKE_MODE
{
   AWAKE_OFF   , // the system and screen can go to sleep
   AWAKE_SYSTEM, // prevent the system from going to sleep, however the screen can go to sleep
   AWAKE_SCREEN, // prevent the system and screen from going to sleep, as long as the App is active or has APP_WORK_IN_BACKGROUND enabled
};
/******************************************************************************/
struct Application // Application Settings
{
   Int       x, y                                                                  ; // initial position (-1..1) used to specify window position on the desktop at the creation of application, default=(-1, 1)
   UInt      flag                                                                  ; // APP_FLAG
   LANG_TYPE language                                                              ; // application language, this is a custom value which may be changed freely, some engine messages rely on this value, default=EN
   void    (*receive_data)(CPtr data, Int size, Ptr hwnd_sender                   ); // pointer to custom function called whan the application has received binary data sent using 'WindowSendData' function, the application may not access 'data' memory after the callback function returns, 'hwnd_sender'=hwnd window identifier of the sender, default=NULL
   void    (*save_state  )(                                                       ); // pointer to custom function called when application is being put into background or will be terminated, in this function you should save current state of data which you may want to restore at next application startup, this function is used only on mobile platforms where the operating system may close the application for any reason, default=NULL
   void    (*paused      )(                                                       ); // pointer to custom function called when application is being  paused (lost   focus), default=NULL
   void    (*resumed     )(                                                       ); // pointer to custom function called when application is being resumed (gained focus), default=NULL
   void    (*drop        )(Memc<Str> &names, GuiObj *focus_obj, C Vec2 &screen_pos); // pointer to custom function called when a file is Drag and Dropped on the application window, 'names'=list of file names being drag and dropped, 'focus_obj'=gui object at which elements are being dropped, 'screen_pos'=screen position at which dropping occurs, default=NULL
   void    (*quit        )(                                                       ); // pointer to custom function called when the application has been requested to quit (for example by pressing Alt+F4 or clicking on the "x-close" window button), if this member is different than NULL, then the application will not exit automatically, manual exiting can be called inside custom 'quit' function (for example by activating 'StateExit' State), this member is ignored when the application was created with APP_NO_CLOSE flag, default=NULL
   void    (*exit        )(CChar *error                                           ); // pointer to custom function called when the application has encountered an error and is about to force terminating the application, typically this occurs inside 'Exit' function, default=NULL

   // get / set
   Application& name        (C Str &name    );                          // set Application Name
 C Str&         name        (               ) {return _name          ;} // get Application Name
 C Str&         exe         (               ) {return _exe           ;} // get Executable Path and Name
 C Str&         cmdLine     (               ) {return _cmd_line      ;} // get Command Line Parameters
   Bool         elevated    (               ) {return _elevated      ;} // get Application Process     Elevation (true if has administrator rights)
   UInt         processID   (               ) {return _process_id    ;} // get Application Process     ID
   UIntPtr       threadID   (               ) {return _thread_id     ;} // get Application Main Thread ID
   Ptr          hwnd        (               ) {return _hwnd          ;} // get Application Window Handle in the OS (this can be casted to HWND object)
 C RectI&       desktopArea (               ) {return _desktop_area  ;} // get Available Desktop Area (not covered by windows taskbar or other desktop toolbars)
   Int          desktopW    (               ) {return _desktop_size.x;} // get screen width  at the moment of application start (desktop width )
   Int          desktopH    (               ) {return _desktop_size.y;} // get screen height at the moment of application start (desktop height)
   Bool         active      (               ) {return _active        ;} // if  Application is Active    (its window is focused)
   Bool         minimized   (               );                          // if  Application is Minimized
   Bool         maximized   (               );                          // if  Application is Maximized
   Bool         movingSizing(               ) {return _paused        ;} // if  Application window is currently being moved or resized
   DIR_ENUM     orientation (               );                          // get device orientation, this is valid for mobile devices which support accelerometers, for those devices the method will return one of the following orientation: DIRE_UP (default), DIRE_DOWN (rotated down), DIRE_LEFT (rotated left), DIRE_RIGHT (rotated right), if the device doesn't support accelerometers then DIRE_UP is returned
   Application& icon        (C Image   &icon);                          // set custom application icon
   Application& stayAwake   (AWAKE_MODE mode);                          // set preventing the operating system from going to sleep

   // operations
   Bool renameSelf      (Str dest); // rename application executable file to 'dest' location, false on fail
   void deleteSelfAtExit(        ); // notify that the exe should delete itself at application exit (this works by creating a temporary .bat file which deletes the exe and itself)
   void close           (        ); // request application to be closed, if 'App.quit' was specified then it will be called instead

   // advanced
   void coInitialize(UInt dwCoInit); // this method is for Windows only, it allows to change initialization of the Windows COM library. By default the engine already initializes the COM library using "CoInitialize(NULL)" system function (which is called before 'InitPre' function), however if you require to initialize the COM library using 'CoInitializeEx' system function with custom settings, then you must call this method ('coInitialize') with 'dwCoInit' parameter which you would normally use for 'CoInitializeEx'. The engine will reinitialize the COM library and any interfaces it previously obtained. You should not attempt to manually uninitialize the COM library by using 'CoUninitialize' on the main thread, as the engine already manages initialization and uninitialization of the library. 'CoUninitialize' will be automatically called by the engine at the end of the application, after 'Shut' function.

private:
   Bool              _active, _initialized, _was_active, _paused, _minimized, _maximized, _close, _closed, _del_self_at_exit, _elevated, _updating;
   Enum1<AWAKE_MODE> _stay_awake;
   Int               _mem_leaks;
   UInt              _style_window, _style_window_max, _style_full, _process_id;
   UIntPtr           _thread_id, _timer_id;
   Ptr               _hwnd, _hinstance;
   VecI2             _window_pos, _window_size, _window_resized, _desktop_size;
   RectI             _desktop_area, _bound, _bound_max;
   Str               _exe, _name, _cmd_line;
#ifdef WINDOWS
   Ptr               _icon;
#else
   Image             _icon;
#endif
   ThreadSafeCallbacks _callbacks;
   Application();
}extern
   App; // Application Settings
/******************************************************************************/
void StartEEManually(Ptr dll_module_instance); // this function imitates "WinMain" function, and should be called only in a DLL based application to start the engine manually

void SupportPVRTC(); // call this inside 'InitPre' function to add support for compressing IMAGE_PVRTC formats on Desktop platforms, using this will however make your executable file bigger
/******************************************************************************/
// Multi Language Text, returns one of the few translations provided depending on current application language
inline Str MLT(C Str &english                                                                                                                             ) {return english;}
inline Str MLT(C Str &english, LANG_TYPE l0, C Str &t0                                                                                                    ) {if(App.language==l0)return t0; return english;}
inline Str MLT(C Str &english, LANG_TYPE l0, C Str &t0, LANG_TYPE l1, C Str &t1                                                                           ) {if(App.language==l0)return t0; if(App.language==l1)return t1; return english;}
inline Str MLT(C Str &english, LANG_TYPE l0, C Str &t0, LANG_TYPE l1, C Str &t1, LANG_TYPE l2, C Str &t2                                                  ) {if(App.language==l0)return t0; if(App.language==l1)return t1; if(App.language==l2)return t2; return english;}
inline Str MLT(C Str &english, LANG_TYPE l0, C Str &t0, LANG_TYPE l1, C Str &t1, LANG_TYPE l2, C Str &t2, LANG_TYPE l3, C Str &t3                         ) {if(App.language==l0)return t0; if(App.language==l1)return t1; if(App.language==l2)return t2; if(App.language==l3)return t3; return english;}
inline Str MLT(C Str &english, LANG_TYPE l0, C Str &t0, LANG_TYPE l1, C Str &t1, LANG_TYPE l2, C Str &t2, LANG_TYPE l3, C Str &t3, LANG_TYPE l4, C Str &t4) {if(App.language==l0)return t0; if(App.language==l1)return t1; if(App.language==l2)return t2; if(App.language==l3)return t3; if(App.language==l4)return t4; return english;}

// Multi Language Text Constant, returns one of the few translations provided depending on current application language
inline CChar* MLTC(CChar* english                                                                                                                             ) {return english;}
inline CChar* MLTC(CChar* english, LANG_TYPE l0, CChar* t0                                                                                                    ) {if(App.language==l0)return t0; return english;}
inline CChar* MLTC(CChar* english, LANG_TYPE l0, CChar* t0, LANG_TYPE l1, CChar* t1                                                                           ) {if(App.language==l0)return t0; if(App.language==l1)return t1; return english;}
inline CChar* MLTC(CChar* english, LANG_TYPE l0, CChar* t0, LANG_TYPE l1, CChar* t1, LANG_TYPE l2, CChar* t2                                                  ) {if(App.language==l0)return t0; if(App.language==l1)return t1; if(App.language==l2)return t2; return english;}
inline CChar* MLTC(CChar* english, LANG_TYPE l0, CChar* t0, LANG_TYPE l1, CChar* t1, LANG_TYPE l2, CChar* t2, LANG_TYPE l3, CChar* t3                         ) {if(App.language==l0)return t0; if(App.language==l1)return t1; if(App.language==l2)return t2; if(App.language==l3)return t3; return english;}
inline CChar* MLTC(CChar* english, LANG_TYPE l0, CChar* t0, LANG_TYPE l1, CChar* t1, LANG_TYPE l2, CChar* t2, LANG_TYPE l3, CChar* t3, LANG_TYPE l4, CChar* t4) {if(App.language==l0)return t0; if(App.language==l1)return t1; if(App.language==l2)return t2; if(App.language==l3)return t3; if(App.language==l4)return t4; return english;}
/******************************************************************************/
