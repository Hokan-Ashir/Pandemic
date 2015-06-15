/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Here is a list of miscellaneous helper functions.

/******************************************************************************/
enum ALIGN_TYPE // Align Type
{
   ALIGN_NONE  , // no align
   ALIGN_MIN   , // align to minimum
   ALIGN_CENTER, // align to center
   ALIGN_MAX   , // align to maximum
};
/******************************************************************************/
template<typename TYPE, Int elms>   inline Int Elms(C TYPE (&Array)[elms]) {return elms;} // get number of elements in array

         inline Bool InRange(Int  i, Byte  elms     ) {return UInt(i)<UInt(elms);} // if 'i' index is in range "0..elms-1"
         inline Bool InRange(Int  i, UInt  elms     ) {return UInt(i)<UInt(elms);} // if 'i' index is in range "0..elms-1"
         inline Bool InRange(Int  i, Int   elms     ) {return UInt(i)<UInt(elms);} // if 'i' index is in range "0..elms-1"
T1(TYPE) inline Bool InRange(Int  i, TYPE &container);                             // if 'i' index is in range of container elements, 'container' can be of many types, for example a C++ array (x[]), memory container ('Memc', 'Memb', ..) or any other type for which 'Elms' function has been defined
T1(TYPE) inline Bool InRange(UInt i, TYPE &container);                             // if 'i' index is in range of container elements, 'container' can be of many types, for example a C++ array (x[]), memory container ('Memc', 'Memb', ..) or any other type for which 'Elms' function has been defined
T1(TYPE) inline Bool InRange(Long i, TYPE &container);                             // if 'i' index is in range of container elements, 'container' can be of many types, for example a C++ array (x[]), memory container ('Memc', 'Memb', ..) or any other type for which 'Elms' function has been defined

Str GetBase    (C Str &name); // get     base name , sample usage: GetBase    ("C:/Folder/file.ext") -> "file.ext"
Str GetExt     (C Str &name); // get     extension , sample usage: GetExt     ("C:/Folder/file.ext") -> "ext"
Str GetExtNot  (C Str &name); // get not extension , sample usage: GetExtNot  ("C:/Folder/file.ext") -> "C:/Folder/file"
Str GetPath    (C Str &name); // get     path      , sample usage: GetPath    ("C:/Folder/file.ext") -> "C:/Folder"
Str GetStart   (C Str &name); // get     path start, sample usage: GetStart   ("C:/Folder/file.ext") -> "C:"
Str GetStartNot(C Str &name); // get not path start, sample usage: GetStartNot("C:/Folder/file.ext") -> "Folder/file.ext"

Str GetRelativePath(Str src, Str dest); // get relative path from 'src' location to 'dest' file, sample usage: GetRelativePath("C:/Folder", "C:/dest.txt") -> "../dest.txt"

Bool  IsDrive (CChar *path);   Bool  IsDrive (CChar8 *path); // if path is a     drive  path, sample usage:  IsDrive ("x:/"     ) -> true,  IsDrive("x:/data/0.bmp") -> false,  IsDrive("data/0.bmp") -> false
Bool HasDrive (CChar *path);   Bool HasDrive (CChar8 *path); // if path contains drive  path, sample usage: HasDrive ("x:/"     ) -> true, HasDrive("x:/data/0.bmp") -> true , HasDrive("data/0.bmp") -> false
Bool HasRemote(CChar *path);   Bool HasRemote(CChar8 *path); // if path contains remote path, sample usage: HasRemote("\\\\comp") -> true
Bool FullPath (CChar *path);   Bool FullPath (CChar8 *path); // if path is a full path (has a drive or is remote)

T3(TA,TB,TC) inline TA&    Clamp(TA  &x, TB  min, TC  max) {if(x<min)x=min;else if(x>max)x=max; return x;      } // clamp 'x' to "min..max" range
             inline Int DivFloor(Int  x, Int y           ) {return (x>=0) ?  x     /y : (x-y+1)/y;             } // integer divide with floor
             inline Int DivCeil (Int  x, Int y           ) {return (x<=0) ?  x     /y : (x+y-1)/y;             } // integer divide with ceil
             inline Int DivRound(Int  x, Int y           ) {return (x>=0) ? (x+y/2)/y : (x-y/2)/y;             } // integer divide with round
             inline Int      Mod(Int  x, Int y           ) {if(!y)return 0; Int z=x%y; return (z>=0) ? z : z+y;} // safe modulo "x%y" , returns always a positive number between "  0..y-1"
                    Int   MidMod(Int  x, Int min, Int max);                                                      // safe middle modulo, returns always a          number between "min..max"

T2(TA,TB) inline Bool FlagTest   (TA  flags, TB f         ) {return (flags&f)!=0;}                                   // check if 'f' flag is enabled                in 'flags', in case 'f' contains multiple options then this will succeed if any of them are enabled
T2(TA,TB) inline Bool FlagAll    (TA  flags, TB f         ) {return (flags&f)==f;}                                   // check if 'f' flag is enabled                in 'flags', in case 'f' contains multiple options then this will succeed if all of them are enabled
T2(TA,TB) inline void FlagEnable (TA &flags, TB f         ) {flags|= f;}                                             // enable   'f' flag                           in 'flags'
T2(TA,TB) inline void FlagDisable(TA &flags, TB f         ) {flags&=~f;}                                             // disable  'f' flag                           in 'flags'
T2(TA,TB) inline void FlagToggle (TA &flags, TB f         ) {flags^= f;}                                             // toggle   'f' flag                           in 'flags'
T2(TA,TB) inline void FlagSet    (TA &flags, TB f, Bool on) {if(on)FlagEnable(flags, f);else FlagDisable(flags, f);} // set      'f' flag to be enabled or disabled in 'flags'

inline UInt IndexToFlag(Int i) {return 1<<i;} // convert index to flag

UInt Ceil2      (UInt x); // rounds 'x' to the nearest multiple of 2  , which is equal or greater than 'x'
UInt Ceil4      (UInt x); // rounds 'x' to the nearest multiple of 4  , which is equal or greater than 'x'
UInt Ceil8      (UInt x); // rounds 'x' to the nearest multiple of 8  , which is equal or greater than 'x'
UInt Ceil16     (UInt x); // rounds 'x' to the nearest multiple of 16 , which is equal or greater than 'x'
UInt Ceil32     (UInt x); // rounds 'x' to the nearest multiple of 32 , which is equal or greater than 'x'
UInt Ceil64     (UInt x); // rounds 'x' to the nearest multiple of 64 , which is equal or greater than 'x'
UInt Ceil128    (UInt x); // rounds 'x' to the nearest multiple of 128, which is equal or greater than 'x'
UInt CeilPow2   (UInt x); // rounds 'x' to the nearest power    of 2  , which is equal or greater than 'x'
UInt FloorPow2  (UInt x); // rounds 'x' to the nearest power    of 2  , which is equal or smaller than 'x'
UInt NearestPow2(UInt x); // rounds 'x' to the nearest power    of 2
Bool IsPow2     (UInt x); // if     'x' is     a       power    of 2
Int  ByteHi     (UInt x); // get index of highest non-zero byte in 'x' (0 if none)

void LogConsole(  Bool on=true);                  // open a console window which will include all messages that were passed to 'Log' and 'LogN' functions, if 'on' is set to false then the console window will be closed instead of opened, this function does not prevent from outputting messages to the log file, if you wish to output only to the console the please open the console using 'LogConsole' and clear the log file name using "LogName(S);" (this function works only on Windows)
void LogName   (C Str &name   );   Str LogName(); // set/get name for the log file, default="log.txt" (NULL on Mobile platforms), specifying an empty file name prevents any writing to the file
void LogDel    (              );                  // delete the           log file
void Log       (C Str &text   );                  // write text              to the log (this will output the message to the log file if 'LogName' is specified, and to the console window if it was opened with 'LogConsole')
void LogN      (C Str &text=S );                  // write text and new-line to the log (this will output the message to the log file if 'LogName' is specified, and to the console window if it was opened with 'LogConsole')
void LogShow   (Bool thread_id, Bool date, Bool time, Bool cur_time); // set which additional information should be displayed during logging, 'thread_id'=ID of the thread which is writing to log, 'date'=year-month-day at the moment of the log, 'time'=hour-minute-second at the moment of the log, 'cur_time'=time in seconds obtained using 'Time.curTime()'

Bool ClipSet(C Str &text, Bool fix_new_line=true); // set system clipboard value to 'text', 'fix_new_line'=if replace "\n" characters with "\r\n" which are required in Windows operating system
Str  ClipGet(             Bool fix_new_line=true); // get system clipboard value          , 'fix_new_line'=if remove  '\r' characters

enum OS_VER // Operating System Version
{
   OS_UNKNOWN,

   WINDOWS_UNKNOWN,
   WINDOWS_2000,
   WINDOWS_XP,
   WINDOWS_XP_64,
   WINDOWS_VISTA,
   WINDOWS_7,
   WINDOWS_8,
   WINDOWS_SERVER_2003,
   WINDOWS_SERVER_2003_R2,
   WINDOWS_SERVER_2008,
   WINDOWS_SERVER_2008_R2,
   WINDOWS_SERVER_2012,
   WINDOWS_SERVER_2012_R2,

   MAC_UNKNOWN,

   LINUX_UNKNOWN,

   ANDROID_UNKNOWN,
   ANDROID_GINGERBREAD,
   ANDROID_HONEYCOMB,
   ANDROID_ICE_CREAM_SANDWICH,
   ANDROID_JELLY_BEAN,
   ANDROID_KIT_KAT,
   ANDROID_LOLLIPOP,

   IOS_UNKNOWN,
};
OS_VER OSVer     (                  ); // get Operating System version
Str    OSName    (OS_VER ver=OSVer()); // get Operating System name
Bool   OSWindows (OS_VER ver=OSVer()); // if  Operating System is Windows
Bool   OSMac     (OS_VER ver=OSVer()); // if  Operating System is Mac
Bool   OSLinux   (OS_VER ver=OSVer()); // if  Operating System is Linux
Bool   OSAndroid (OS_VER ver=OSVer()); // if  Operating System is Android
Bool   OSiOS     (OS_VER ver=OSVer()); // if  Operating System is iOS

Str OSUserName(Bool short_name=false); // get the user name of currently logged in user in the Operating System (for Android platform this will be the main email address associated with the device, 'GET_ACCOUNTS' permission which is by default enabled, needs to be specified in the "AndroidManifest.xml" file in order to access this value)

Bool OSLaunch(C Str &name, C Str &params=S, Bool hidden=false, Bool as_admin=false); // tell Operating System to launch a program or url address, 'as_admin'=if run as administrator, Sample Usage: OSLaunch("esenthel.exe"), OSLaunch("http://www.esenthel.com"), false on fail

Bool OpenAppSettings(); // open application settings, false on fail, this is used only on iOS, after calling this function the OS will open the Application Settings Screen in the System Settings menu

void    JavaScriptRun (CChar8 *code); // execute custom java script command                                 , valid only for WEB platform
void    JavaScriptRun (CChar  *code); // execute custom java script command                                 , valid only for WEB platform
Int     JavaScriptRunI(CChar8 *code); // execute custom java script command and return its result as integer, valid only for WEB platform
Int     JavaScriptRunI(CChar  *code); // execute custom java script command and return its result as integer, valid only for WEB platform
CChar8* JavaScriptRunS(CChar8 *code); // execute custom java script command and return its result as string , valid only for WEB platform
CChar8* JavaScriptRunS(CChar  *code); // execute custom java script command and return its result as string , valid only for WEB platform

Bool CreateShortcut(C Str &file, C Str &shortcut, C Str &desc=S, C Str &icon=S); // create a shortcut to 'file' program, shortcut will be placed in 'shortcut' location, with 'desc' description, 'icon'=custom icon file path (set empty to use default icon), Sample Usage: CreateShortcut("C:/Games/Esenthel/Esenthel.exe", SystemPath(SP_MENU_PROG)+"/Esenthel/Esenthel", "Esenthel - 3D Action RPG");

Bool AssociateFileType(Str extension, Str application_path, Str application_id, Str extension_desc=S, Str custom_icon=S); // associate file type with specified application, 'extension'=file extension, 'application_path'=path to application, 'application_id'=unique string identyfing the application (recommended format is "CompanyNamy.AppName"), 'extension_desc'=description of the extension (can be left empty), 'custom_icon'=path to icon file which will be used as the icon for the files of specified extension (if left empty, icon will be taken from the application), false on fail, Sample Usage: AssociateFileType("dat", "c:/program.exe", "Company.Program", "Data File")

Str NormalizePath(C Str &path); // return normalized path, Sample Usage: NormalizePath("C:/Folder/../test") -> "C:/test"

Str CleanFileName(C Str &name); // removes all characters which are disallowed in file names, these include \ / : * ? " < > |

Str8 EncodeFileName(            CPtr src , Int size); // encode 'src' binary data of 'size' size, into string which can be used as a file name
Bool DecodeFileName(C Str8 &src, Ptr dest, Int size); // decode       binary data                 from string, false on fail

T1(TYPE) Str8 EncodeFileName(           C TYPE &elm) {return EncodeFileName(     &elm, SIZE(elm));}
T1(TYPE) Bool DecodeFileName(C Str8 &src, TYPE &elm) {return DecodeFileName(src, &elm, SIZE(elm));}
         Bool DecodeFileName(CChar  *src, UID  &id );

UID FileNameID(C Str &name); // convert base of 'name' (obtained using 'GetBase') to ID using 'DecodeFileName', 'UIDZero' on fail

VecI4 FileVersion(C Str &name); // get exe/dll file version, (-1, -1, -1, -1) on fail

Str8 RandomPassword(Int length, Bool chars, Bool digits, Bool symbols=false); // generate a random password, 'length'=length of the password, 'chars'=if use characters in the password, 'digits'=if use digits in the password, 'symbols'=if use symbols in the password

Bool ValidEmail     (C Str &email); // test if 'email' is in correct email       format - "user@domain.com"
Bool ValidURL       (C Str &url  ); // test if 'url'   is in correct url         format - "http://domain.com"
Bool ValidLicenseKey(C Str &key  ); // test if 'key'   is in correct license key format - "XXXXX-XXXXX-XXXXX-XXXXX-XXXXX"

Str         CString(C Str &str); // get string as if it would be stored for the C++ language (preceeding '\' and '"' characters with '\'                           ), for example:         CString("abc"def\ghi"     ) -> ("abc\"def\\ghi")
Str       XmlString(C Str &str); // get string as if it would be stored for the XML text     (replacing  & -> &amp;  < -> &lt;  > -> &gt;  ' -> &apos;  " -> &quot;), for example:       XmlString("abc"def\ghi"     ) -> ("abc&quot;def\ghi")
Str DecodeXmlString(C Str &str); // decode string back from the                 XML text     (replacing  &amp; -> &  &lt; -> <  &gt; -> >  &apos; -> '  &quot; -> "), for example: DecodeXmlString("abc&quot;def\ghi") -> ("abc"def\ghi")

UID ComputerID(Bool per_user); // get a unique ID of this computer, 'per_user'=if generate a different ID depending on which user is logged in

void Break(           ); // calling this function will force breakpoint exception, use for debugging
void Exit (Str error=S); // immediately exit the application with 'error' message
/******************************************************************************/
enum SYSTEM_PATH // System Path Type
{
   SP_NONE             , // none
   SP_DESKTOP          , // desktop             (typically "C:/Users/*/Desktop")
   SP_PROG_FILES       , // program files       (typically "C:/Program Files")
   SP_MENU             , // start menu          (typically "C:/Users/*/AppData/Roaming/Microsoft/Windows/Start Menu")
   SP_MENU_PROG        , // start menu/programs (typically "C:/Users/*/AppData/Roaming/Microsoft/Windows/Start Menu/Programs")
   SP_STARTUP          , // start menu/startup  (typically "C:/Users/*/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/Startup")
   SP_FAVORITES        , // user/favorites      (typically "C:/Users/*/Favorites")
   SP_DOCUMENTS        , // user/documents      (typically "C:/Users/*/Documents"      , on Mobile platforms this is the path where the application can write files on local    storage)
   SP_APP_DATA         , // user/app data       (typically "C:/Users/*/AppData/Roaming", on Mobile platforms this is the path where the application can write files on local    storage)
   SP_APP_DATA_EXTERNAL, // user/app data       (typically "C:/Users/*/AppData/Roaming", on Mobile platforms this is the path where the application can write files on external SD Card)
   SP_ALL_APP_DATA     , // all users/app data  (typically "C:/ProgramData")
   SP_SD_CARD          , // for Android this is the path to mounted SD card
};
Str SystemPath(SYSTEM_PATH type); // get system path, Sample Usage: SystemPath(SP_PROG_FILES) -> "C:/Program Files"

Str AppDataPath(); // return application path on desktop systems and SP_APP_DATA on mobile
/******************************************************************************/
enum EXTENSION_TYPE // Extension Type
{
   EXT_NONE    , // none
   EXT_TEXT    , // text
   EXT_IMAGE   , // image
   EXT_SOUND   , // sound
   EXT_MATERIAL, // material
   EXT_MESH    , // mesh
   EXT_PHYS    , // physics
   EXT_VIDEO   , // video
};
EXTENSION_TYPE ExtType(C Str &ext); // get extension type from given extension name, Sample Usage : ExtType("bmp") -> EXT_IMAGE

#define SUPPORTED_IMAGE_EXT "gfx|bmp|png|jpg|jpeg|webp|tga|tif|tiff|dds|psd|ico|cur"
#define SUPPORTED_MESH_EXT  "mesh|dae|fbx|x|ase|obj|3ds|b3d|ms3d|psk|wrl"
#define SUPPORTED_TEXT_EXT  "es|c|cpp|h|cs|cc|cxx|m|mm|java|txt|xml|htm|html|php|mk"
/******************************************************************************/
enum REG_KEY_GROUP // registry key group
{
   RKG_CLASSES_ROOT , // this will be translated to HKEY_CLASSES_ROOT
   RKG_CURRENT_USER , // this will be translated to HKEY_CURRENT_USER
   RKG_LOCAL_MACHINE, // this will be translated to HKEY_LOCAL_MACHINE
   RKG_USERS        , // this will be translated to HKEY_USERS
};
enum REG_KEY_TYPE // registry key type
{
   REG_KEY_NONE  ,
   REG_KEY_STRING,
   REG_KEY_U32   ,
   REG_KEY_U64   ,
   REG_KEY_DATA  ,
};
REG_KEY_TYPE GetReg    (REG_KEY_GROUP reg_key_group, C Str &name, Memc<Byte> *data   =NULL  ); // get registry key type and optionally data, REG_KEY_NONE on fail
Str          GetRegStr (REG_KEY_GROUP reg_key_group, C Str &name, Bool       *success=NULL  ); // get registry key value as String         , ""           on fail, 'success'=optional parameter which will be set to true if the key exists
UInt         GetRegUInt(REG_KEY_GROUP reg_key_group, C Str &name, Bool       *success=NULL  ); // get registry key value as UInt           , 0            on fail, 'success'=optional parameter which will be set to true if the key exists
Bool         SetRegStr (REG_KEY_GROUP reg_key_group, C Str &name, C Str      &value         ); // set registry key value as String         , false        on fail
Bool         SetRegUInt(REG_KEY_GROUP reg_key_group, C Str &name, UInt        value         ); // set registry key value as UInt           , false        on fail
Bool         SetRegData(REG_KEY_GROUP reg_key_group, C Str &name, CPtr        data, Int size); // set registry key value as binary data    , false        on fail
/******************************************************************************/
T1(ENUM) struct Enum1 // Custum enum stored as 1 byte
{
     operator ENUM()C {return ENUM(_value);} // automatic cast to 'ENUM'
   ENUM operator()()C {return ENUM(_value);} // manual    cast to 'ENUM'

   Enum1(          ) {}
   Enum1(ENUM value) {T._value=value;}

private:
   Byte _value;
};
/******************************************************************************/
enum SMOOTH_VALUE_MODE // SmoothValue Mode
{
   SV_NONE, // no smoothing occurs

   SV_AVERAGE2, // sets result equal to 2 previous values average
   SV_AVERAGE4, // sets result equal to 4 previous values average
   SV_AVERAGE8, // sets result equal to 8 previous values average

   SV_WEIGHT2, // sets result equal to 2 previous values weighted average
   SV_WEIGHT4, // sets result equal to 4 previous values weighted average
   SV_WEIGHT8, // sets result equal to 8 previous values weighted average

   SV_NUM, // number of smoothing modes
};
struct SmoothValue
{
   void              mode  (SMOOTH_VALUE_MODE mode) ; // set SMOOTH_VALUE_MODE
   SMOOTH_VALUE_MODE mode  (                      )C; // get SMOOTH_VALUE_MODE
   void              init  (Flt        start_value) ; // init with starting value
   Flt               update(Flt      current_value) ; // update by giving current raw value, returns smooth result based on SMOOTH_VALUE_MODE and previous values

   SmoothValue(SMOOTH_VALUE_MODE mode=SV_WEIGHT4);

private:
   Byte _mode, _pos;
   Flt  _history[8];
};
struct SmoothVel
{
   Flt updatePosDelta(Flt pos_delta, Flt dt); // update by giving position delta, returns smooth velocity result, 'dt'=time delta
   Flt updateVel     (Flt vel      , Flt dt); // update by giving velocity      , returns smooth velocity result, 'dt'=time delta

   SmoothVel(Flt history_time=4.0f/60); // 'history_time'=how long keep the values in history

private:
   Byte _pos, _done;
   Flt  _history[8], _history_time, _time;
};
/******************************************************************************/
struct TextPatch
{
   enum MODE
   {
      ADD  ,
      DEL  ,
      EQUAL,
   };

   struct Diff
   {
      MODE mode;
      Str  text;
   };

   Bool       ok; // if patch succeeded
   Int        base_offset, a_offset,
              base_length, a_length;
   Mems<Diff> diffs;
};
Str Merge(C Str &base, C Str &a, C Str &b, Memc<TextPatch> *patches=NULL, Int timeout=-1); // merge 3 texts, 'base'=original text, 'a'=modification of original text, 'b'=another modification of original text, 'patches'=optional paramter that will receive information about patches applied, 'timeout'=approximatelly how long to search for best merge (-1=unlimited), returns merged text
/******************************************************************************/
T2(BASE, EXTENDED)   void ASSERT_BASE_EXTENDED_EX(BASE&, EXTENDED&)   {EXTENDED *e=((EXTENDED*)256); BASE *b=e; DYNAMIC_ASSERT(Ptr(b)==Ptr(e), "Selected class is not the base class of extended one");}
T2(BASE, EXTENDED)   void ASSERT_BASE_EXTENDED_EX(BASE*, EXTENDED*)   {EXTENDED *e=((EXTENDED*)256); BASE *b=e; DYNAMIC_ASSERT(Ptr(b)==Ptr(e), "Selected class is not the base class of extended one");}

T2(BASE, EXTENDED)   void ASSERT_BASE_EXTENDED   (                )   {int i=0; ASSERT_BASE_EXTENDED_EX((BASE&)i, (EXTENDED&)i);} // asserts that 'BASE' class is the main base class of 'EXTENDED', this also works for pointers

T1(TYPE) CPtr CType(       ) {return (CPtr)&typeid(TYPE);} // convert C++ type into pointer
T1(TYPE) CPtr CType(TYPE &x) {return (CPtr)&typeid(x   );} // convert C++ type into pointer

T1(TYPE)   TYPE& NoTemp(  TYPE &x) {return x;}
T1(TYPE) C TYPE& NoTemp(C TYPE &x) {return x;}
/******************************************************************************/
enum LANG_TYPE
{
#ifndef _WINNT_
   LANG_NEUTRAL      =0x00,
   LANG_INVARIANT    =0x7F,

   LANG_AFRIKAANS    =0x36,
   LANG_ALBANIAN     =0x1C,
   LANG_ALSATIAN     =0x84,
   LANG_AMHARIC      =0x5E,
   LANG_ARABIC       =0x01,
   LANG_ARMENIAN     =0x2B,
   LANG_ASSAMESE     =0x4D,
   LANG_AZERI        =0x2C,
   LANG_BASHKIR      =0x6D,
   LANG_BASQUE       =0x2D,
   LANG_BELARUSIAN   =0x23,
   LANG_BENGALI      =0x45,
   LANG_BRETON       =0x7E,
   LANG_BOSNIAN      =0x1A,
   LANG_BULGARIAN    =0x02,
   LANG_CATALAN      =0x03,
   LANG_CHINESE      =0x04,
   LANG_CORSICAN     =0x83,
   LANG_CROATIAN     =0x1A,
   LANG_CZECH        =0x05,
   LANG_DANISH       =0x06,
   LANG_DARI         =0x8C,
   LANG_DIVEHI       =0x65,
   LANG_DUTCH        =0x13,
   LANG_ENGLISH      =0x09,
   LANG_ESTONIAN     =0x25,
   LANG_FAEROESE     =0x38,
   LANG_FILIPINO     =0x64,
   LANG_FINNISH      =0x0B,
   LANG_FRENCH       =0x0C,
   LANG_FRISIAN      =0x62,
   LANG_GALICIAN     =0x56,
   LANG_GEORGIAN     =0x37,
   LANG_GERMAN       =0x07,
   LANG_GREEK        =0x08,
   LANG_GREENLANDIC  =0x6F,
   LANG_GUJARATI     =0x47,
   LANG_HAUSA        =0x68,
   LANG_HEBREW       =0x0D,
   LANG_HINDI        =0x39,
   LANG_HUNGARIAN    =0x0E,
   LANG_ICELANDIC    =0x0F,
   LANG_IGBO         =0x70,
   LANG_INDONESIAN   =0x21,
   LANG_INUKTITUT    =0x5D,
   LANG_IRISH        =0x3C,
   LANG_ITALIAN      =0x10,
   LANG_JAPANESE     =0x11,
   LANG_KANNADA      =0x4B,
   LANG_KASHMIRI     =0x60,
   LANG_KAZAK        =0x3F,
   LANG_KHMER        =0x53,
   LANG_KICHE        =0x86,
   LANG_KINYARWANDA  =0x87,
   LANG_KONKANI      =0x57,
   LANG_KOREAN       =0x12,
   LANG_KYRGYZ       =0x40,
   LANG_LAO          =0x54,
   LANG_LATVIAN      =0x26,
   LANG_LITHUANIAN   =0x27,
   LANG_LOWER_SORBIAN=0x2E,
   LANG_LUXEMBOURGISH=0x6E,
   LANG_MACEDONIAN   =0x2F,
   LANG_MALAY        =0x3E,
   LANG_MALAYALAM    =0x4C,
   LANG_MALTESE      =0x3A,
   LANG_MANIPURI     =0x58,
   LANG_MAORI        =0x81,
   LANG_MAPUDUNGUN   =0x7A,
   LANG_MARATHI      =0x4E,
   LANG_MOHAWK       =0x7C,
   LANG_MONGOLIAN    =0x50,
   LANG_NEPALI       =0x61,
   LANG_NORWEGIAN    =0x14,
   LANG_OCCITAN      =0x82,
   LANG_ORIYA        =0x48,
   LANG_PASHTO       =0x63,
   LANG_PERSIAN      =0x29,
   LANG_POLISH       =0x15,
   LANG_PORTUGUESE   =0x16,
   LANG_PUNJABI      =0x46,
   LANG_QUECHUA      =0x6B,
   LANG_ROMANIAN     =0x18,
   LANG_ROMANSH      =0x17,
   LANG_RUSSIAN      =0x19,
   LANG_SAMI         =0x3B,
   LANG_SANSKRIT     =0x4F,
   LANG_SERBIAN      =0x1A,
   LANG_SINDHI       =0x59,
   LANG_SINHALESE    =0x5B,
   LANG_SLOVAK       =0x1B,
   LANG_SLOVENIAN    =0x24,
   LANG_SOTHO        =0x6C,
   LANG_SPANISH      =0x0A,
   LANG_SWAHILI      =0x41,
   LANG_SWEDISH      =0x1D,
   LANG_SYRIAC       =0x5A,
   LANG_TAJIK        =0x28,
   LANG_TAMAZIGHT    =0x5F,
   LANG_TAMIL        =0x49,
   LANG_TATAR        =0x44,
   LANG_TELUGU       =0x4A,
   LANG_THAI         =0x1E,
   LANG_TIBETAN      =0x51,
   LANG_TIGRIGNA     =0x73,
   LANG_TSWANA       =0x32,
   LANG_TURKISH      =0x1F,
   LANG_TURKMEN      =0x42,
   LANG_UIGHUR       =0x80,
   LANG_UKRAINIAN    =0x22,
   LANG_UPPER_SORBIAN=0x2E,
   LANG_URDU         =0x20,
   LANG_UZBEK        =0x43,
   LANG_VIETNAMESE   =0x2A,
   LANG_WELSH        =0x52,
   LANG_WOLOF        =0x88,
   LANG_XHOSA        =0x34,
   LANG_YAKUT        =0x85,
   LANG_YI           =0x78,
   LANG_YORUBA       =0x6A,
   LANG_ZULU         =0x35,
#endif
   LANG_UNKNOWN=LANG_NEUTRAL,

   EN=LANG_ENGLISH   ,
   CN=LANG_CHINESE   ,
   JP=LANG_JAPANESE  ,
   KO=LANG_KOREAN    ,
   DE=LANG_GERMAN    ,
   FR=LANG_FRENCH    ,
   PL=LANG_POLISH    ,
   RU=LANG_RUSSIAN   ,
   SP=LANG_SPANISH   ,
   PO=LANG_PORTUGUESE,
};
LANG_TYPE OSLanguage        (              ); // get Operating System Language
Str         LanguageSpecific(LANG_TYPE lang); // get specific alphabet characters for the selected language
/******************************************************************************/
