/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Pak' for archiving multiple data files into one "*.pak" file.

/******************************************************************************/
struct PakNode // Pak File Node, used for creating Pak's from custom files
{
   Bool          exists         , // if the file exists, if it's set to false then file will be created with PF_REMOVED flag enabled (see comments for PF_REMOVED flag to get more information)
                 compressed     , // if 'file' data is already compressed
                 compressable   ; // if 'file' should be compressed when creating a compressed pak (this is ignored if file is already compressed or creating pak without compression), this can be used to manually disable compression for some files
   FSTD_TYPE     type           ; // type of the file, can be set to FSTD_FILE, FSTD_DIR or FSTD_LINK
   Str           name           ; // target name in the destination Pak, for example "image.gfx" (can't include folders)
   File         *file           ; // pointer to file   data which will be used for storing the node file data (please specify 'file' or 'file2', but not both)
   Str           file2          ; // path    to source file which will be used for storing the node file data (please specify 'file' or 'file2', but not both)
   UInt          crc32          ; // file crc32, if you know it already then you can set it manually to save processing time, in other case you can leave it to 0
   DateTime      modify_time_utc; // file modification time (UTC time zone)
   Memb<PakNode> children       ; // sub-elements

   PakNode& set(C Str &name, const_mem_addr File  *file=NULL, C DateTime *modify_time_utc=NULL, Bool exists=true, UInt crc32=0, FSTD_TYPE type=FSTD_FILE, Bool compressed=false, Bool compressable=true) {T.name=name; T.file= file; T.file2.clear(); if(modify_time_utc)T.modify_time_utc=*modify_time_utc; T.exists=exists; T.crc32=crc32; T.type=type; T.compressed=compressed; T.compressable=compressable; return T;}
   PakNode& set(C Str &name, const_mem_addr File  &file     , C DateTime *modify_time_utc=NULL, Bool exists=true, UInt crc32=0, FSTD_TYPE type=FSTD_FILE, Bool compressed=false, Bool compressable=true) {T.name=name; T.file=&file; T.file2.clear(); if(modify_time_utc)T.modify_time_utc=*modify_time_utc; T.exists=exists; T.crc32=crc32; T.type=type; T.compressed=compressed; T.compressable=compressable; return T;}
   PakNode& set(C Str &name,              C Str   &file     , C DateTime *modify_time_utc=NULL, Bool exists=true, UInt crc32=0, FSTD_TYPE type=FSTD_FILE, Bool compressed=false, Bool compressable=true) {T.name=name; T.file= NULL; T.file2=file   ; if(modify_time_utc)T.modify_time_utc=*modify_time_utc; T.exists=exists; T.crc32=crc32; T.type=type; T.compressed=compressed; T.compressable=compressable; return T;}

   PakNode() {exists=true; compressed=false; compressable=true; type=FSTD_FILE; file=NULL; crc32=0; modify_time_utc.zero();}
};
struct PakFileData // Pak File Data, used for creating or updating Pak's from custom files
{
   enum MODE
   {
      REPLACE     , // remove any previous information about this file in Pak,       include     new information about this file specifying that it    now exists, with new data taken from 'file' member    , use this mode for creating new files or updating previous files
      REMOVE      , // remove any previous information about this file in Pak, don't include any new information about this file                                                                             , use this mode for completely removing any information about previous file
      MARK_REMOVED, // remove any previous information about this file in Pak,       include     new information about this file specifying that it is now removed, by enabling PF_REMOVED flag for this file, use this mode for removing previous file and leaving information that it now is removed (see comments for PF_REMOVED flag to get more information)
   };

   MODE      mode           ; // mode specifying how this file should be treated (whether it should be replaced, removed completely, or marked as removed)
   Str       name           ; // target name in the destination Pak (can include folders), for example "Folder/file.ext"
   UInt      crc32          ; // file crc32, if you know it already then you can set it manually to save processing time, in other case you can leave it to 0
   DateTime  modify_time_utc; // file modification time (UTC time zone)
   File      file           ; // new file data                                                   , used only if "mode==REPLACE" (please specify 'file' or 'file2', but not both)
   Str       file2          ; // path to source file                                             , used only if "mode==REPLACE" (please specify 'file' or 'file2', but not both)
   FSTD_TYPE type           ; // type of the file, can be set to FSTD_FILE, FSTD_DIR or FSTD_LINK, used only if "mode==REPLACE" or "mode==MARK_REMOVED"
   Bool      compressed     , // if 'file' data is already compressed                            , used only if "mode==REPLACE"
             compressable   ; // if 'file' should be compressed when creating a compressed pak   , used only if "mode==REPLACE" (this is ignored if file is already compressed or creating pak without compression), this can be used to manually disable compression for some files

   PakFileData() {mode=REPLACE; crc32=0; modify_time_utc.zero(); compressed=false; compressable=true; type=FSTD_FILE;}
};
struct PakProgress // class that can be optionally passed to Pak creation functions to get extra control over that process (for example on one thread you can call Pak create function with this class object as the parameter, then on secondary thread you can access that object and read the 'progress' or enable 'stop' to break pak creation)
{
   Bool stop    ; // set this to 'true' on secondary thread to break pak creation, default=false
   Flt  progress; // current progress of pak creation, 0..1, pak creation functions will modify this value according to the progress, default=0

   PakProgress&   reset() {stop=false; progress=0; return T;} // reset members to initial values
   PakProgress() {reset();}
};
/******************************************************************************/
// PAK
/******************************************************************************/
enum PAK_FILE_FLAG
{
   PF_COMPRESSED =1<<0, // this file is stored as compressed, accessing this file will cause the engine to decompress it first
   PF_REMOVED    =1<<1, // this file is marked as removed   , this flag is useful if you're using multiple paks and you want to specify that a file which was in one pak should now no longer exist (for example: having "data.pak" - base pak of data, "patch.pak" - pak storing updated files, "data.pak" has "file.txt", in the "patch.pak" we want to specify that "file.txt" should no longer exist, to do that, we include a dummy "file.txt" PakFile in the "patch.pak" with PF_REMOVED enabled, now when loading "data.pak" followed by "patch.pak", "file.txt" from "patch.pak" with PF_REMOVED flag will replace "file.txt" from "data.pak" making it no longer accessible)
   PF_STD_DIR    =1<<2, // this file was originally created from a standard directory (not a file or memory-based node)
   PF_NO_COMPRESS=1<<3, // this file was created with "compressable==false" (it wanted to disable any possible compression)
   PF_STD_LINK   =1<<4, // this file was originally created from a symbolic link
};
struct PakFile // Single File stored in Pak
{
   CChar   *name                ; // file name  (this does not include the path, if you want the full name you need to use Pak.fullName)
   Byte     flag                ; // file flags (PAK_FILE_FLAG)
   Int      parent              , // parent index       in Pak.file, -1=none
            children_offset     , // offset of children in Pak.file (this is the index of the first child in Pak.file array)
            children_num        ; // number of children
   ULong    data_offset         ; // offset of data     in Pak
   UInt     data_size           , // size   of data
            data_size_compressed, // size   of data after compression (if this file is not compressed, then this member is equal to 'data_size')
            data_crc32          ; // crc32  of data, this member is set to 0 if PAK_SET_CRC32 was not enabled during pak creation
   DateTime modify_time_utc     ; // file modification time (UTC time zone)

   FSTD_TYPE type()C {return (flag&PF_STD_DIR) ? FSTD_DIR : (flag&PF_STD_LINK) ? FSTD_LINK : FSTD_FILE;} // get type of the file
};
/******************************************************************************/
enum PAK_FLAG // Pak Creation Flags
{
   PAK_SHORTEN  =1<<0, // when packing only one directory "xxx", files inside it won't be stored in "xxx\*.*" but in root "*.*"
   PAK_NO_DATA  =1<<1, // store only file names without their data
   PAK_NO_FILE  =1<<2, // don't create output pak file, but only set Pak class members
   PAK_SET_CRC32=1<<3, // calculate the crc32 member for each pak file, if not enabled then the crc32 will be set to zero (crc32 calculation requires additional processing and slows down creation of paks)
};
struct Pak // Set of Pak Files !! do not add secured files to Pak, secure whole Pak instead !!
{
   // load
   void operator=(              C Str &name                                                                 ); // load pak from file  , Exit  on fail
   Bool load     (              C Str &name          , const_mem_addr Secure *secure=NULL, Long pak_offset=0); // load pak from file  , false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'pak_offset'=offset of PAK data inside the file
   Bool loadMem  (const_mem_addr CPtr  data, Int size, const_mem_addr Secure *secure=NULL                   ); // load pak from memory, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'data' must point to a constant memory address (only pointer is stored through which the data can be later accessed)

   // get
   Int        rootFiles(     )C {return _root_files  ;} // get number of files in root directory, they are stored first in the 'files' array
   Int       totalFiles(     )C {return _files.elms();} // get number of all files
 C Mems<PakFile>& files(     )C {return _files       ;} // get files array
 C      PakFile & file (Int i)C {return _files[i]    ;} // get i-th file

   Long     totalSize(C PakFile &file, Bool compressed=false    )C; // get      file          total size (size of the file and all of its children), 'compressed'=if return the compressed size 'PakFile.data_size_compressed' instead of 'PakFile.data_size'
   Long     totalSize(  Int      i   , Bool compressed=false    )C; // get i-th file          total size (size of the file and all of its children), 'compressed'=if return the compressed size 'PakFile.data_size_compressed' instead of 'PakFile.data_size'
   Str      fullName (C PakFile &file                           )C; // get      file          full  name (path + name)
   Str      fullName (  Int      i                              )C; // get i-th file          full  name (path + name)
 C PakFile* find     (CChar     *name, Bool include_removed=true)C; // find     file from its full  name (path + name), 'include_removed'=return also files which are marked as removed (have PF_REMOVED flag enabled), NULL on fail
 C PakFile* find     (C UID     &id  , Bool include_removed=true)C; // find     file from its ID                      , 'include_removed'=return also files which are marked as removed (have PF_REMOVED flag enabled), NULL on fail

 C Str& actualFileName()C {return _file_name;} // get name of the actual file where the pak is located. If this PAK is stored inside another file, then this method will return the file name of the top most parent.

   // create from files and save to disk
   Bool create(C Str               &file , C Str &pak_name=S, UInt flag=PAK_SHORTEN, Secure *dest_secure=NULL, Secure *src_secure=NULL, COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9, Bool (*filter)(C Str &name)=NULL, Str *error_message=NULL, PakProgress *progress=NULL); // create pak, 'file '=single  file/directory      , 'pak_name'=pak file name to save to, 'flag'=PAK_FLAG                                                                 , 'compression_level'=(0..9) (0=fastest/worst, 9=slowest/best), false on fail, 'filter'=optional pointer to custom callback function which will receive information about encountered files and folders (their name) for which it should return true if the element should be included in the Pak and false if not included (if 'filter' is NULL then all encountered files/folders will be included), 'error_message'=will contain a message what went wrong upon error, 'progress'=optional parameter allowing to control creation from secondary thread
   Bool create(C Memp<Str        > &files, C Str &pak_name=S, UInt flag=PAK_SHORTEN, Secure *dest_secure=NULL, Secure *src_secure=NULL, COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9, Bool (*filter)(C Str &name)=NULL, Str *error_message=NULL, PakProgress *progress=NULL); // create pak, 'files'=list of file/directories    , 'pak_name'=pak file name to save to, 'flag'=PAK_FLAG, all elements listed in 'files' must be located in the same path, 'compression_level'=(0..9) (0=fastest/worst, 9=slowest/best), false on fail, 'filter'=optional pointer to custom callback function which will receive information about encountered files and folders (their name) for which it should return true if the element should be included in the Pak and false if not included (if 'filter' is NULL then all encountered files/folders will be included), 'error_message'=will contain a message what went wrong upon error, 'progress'=optional parameter allowing to control creation from secondary thread
   Bool create(C Memp<PakNode    > &files, C Str &pak_name  , UInt flag=          0, Secure *dest_secure=NULL                         , COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9                                  , Str *error_message=NULL, PakProgress *progress=NULL); // create pak, 'files'=list of file/directory nodes, 'pak_name'=pak file name to save to, 'flag'=PAK_FLAG                                                                 , 'compression_level'=(0..9) (0=fastest/worst, 9=slowest/best), false on fail                                                                                                                                                                                                                                                                                                                        , 'error_message'=will contain a message what went wrong upon error, 'progress'=optional parameter allowing to control creation from secondary thread
   Bool create(C Memp<PakFileData> &files, C Str &pak_name  , UInt flag=          0, Secure *dest_secure=NULL                         , COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9                                  , Str *error_message=NULL, PakProgress *progress=NULL); // create pak, 'files'=list of file/directory data , 'pak_name'=pak file name to save to, 'flag'=PAK_FLAG                                                                 , 'compression_level'=(0..9) (0=fastest/worst, 9=slowest/best), false on fail                                                                                                                                                                                                                                                                                                                        , 'error_message'=will contain a message what went wrong upon error, 'progress'=optional parameter allowing to control creation from secondary thread

   // io
   void saveHeader(File &f)C; // save pak header (information about files, without their data)

   Pak&   del(); // delete manually
  ~Pak() {del();}
   Pak();

private:
   UInt          _root_files;
   ULong         _data_offset, _file_apk_offset;
   Mems<Byte   > _data_decompressed;
   Mems<Char   > _names;
   Mems<PakFile> _files;
   Byte          _file_type;
   Secure       *_file_secure;
   Str           _file_name;
   CPtr          _data;
   NO_COPY_CONSTRUCTOR(Pak);
};
/******************************************************************************/
// PAK SET
/******************************************************************************/
struct PaksFile // Single file stored in PakSet
{
   Pak     *pak            ; // Pak to which file belongs to
 C PakFile *file           ; // pointer to pak file
   Int      children_offset, // offset of children in PakSet.file
            children_num   ; // number of children

   Str fullName()C; // get file full name (path + name)

   PaksFile() {Zero(T);}
};
/******************************************************************************/
struct PakSet // set of Pak's combined together with all their PakFile's combined in one database (PakFile's with PF_REMOVED aren't included in PakSet)
{
   // get
   Int         rootFiles(     )C {return _root_files  ;} // get number of files in root directory, they are stored first in the 'file' array
   Int        totalFiles(     )C {return _files.elms();} // get number of all files
 C Memc<PaksFile>& files(     )C {return _files       ;} // get files array
 C      PaksFile & file (Int i)C {return _files[i]    ;} // get i-th file

   Long     totalSize(C PaksFile &file, Bool compressed=false)C; // get      file          total size (size of the file and all of its children), 'compressed'=if return the compressed size 'PakFile.data_size_compressed' instead of 'PakFile.data_size'
   Long     totalSize(  Int       i   , Bool compressed=false)C; // get i-th file          total size (size of the file and all of its children), 'compressed'=if return the compressed size 'PakFile.data_size_compressed' instead of 'PakFile.data_size'
   Str       fullName(C PaksFile &file                       )C; // get      file          full  name (path + name)
   Str       fullName(  Int       i                          )C; // get i-th file          full  name (path + name)
 C PaksFile* find    (CChar      *name                       )C; // get      file from its full  name (path + name)
 C PaksFile* find    (C UID      &id                         )C; // get      file from its ID

   // operations
   Bool    addTry   (              C Str &name,           const_mem_addr Secure *secure=NULL, Bool auto_rebuild=true, Long pak_offset=0); // add Pak from file  , 'auto_rebuild'=if automatically call the 'rebuild' method, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'pak_offset'=offset of PAK data inside the file
   PakSet& add      (              C Str &name,           const_mem_addr Secure *secure=NULL, Bool auto_rebuild=true, Long pak_offset=0); // add Pak from file  , 'auto_rebuild'=if automatically call the 'rebuild' method, Exit  on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'pak_offset'=offset of PAK data inside the file
   Bool    addMemTry(const_mem_addr CPtr  data, Int size, const_mem_addr Secure *secure=NULL, Bool auto_rebuild=true                   ); // add Pak from memory, 'auto_rebuild'=if automatically call the 'rebuild' method, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'data' must point to a constant memory address (only pointer is stored through which the data can be later accessed)
   PakSet& addMem   (const_mem_addr CPtr  data, Int size, const_mem_addr Secure *secure=NULL, Bool auto_rebuild=true                   ); // add Pak from memory, 'auto_rebuild'=if automatically call the 'rebuild' method, Exit  on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed), 'data' must point to a constant memory address (only pointer is stored through which the data can be later accessed)
   Bool    remove   (              C Str &name,                                                                       Long pak_offset=0); // remove previously added "Pak from file"  , true is returned if Pak was found and removed, false if it was not found, this method always calls 'rebuild' upon success
   Bool    removeMem(               CPtr  data                                                                                         ); // remove previously added "Pak from memory", true is returned if Pak was found and removed, false if it was not found, this method always calls 'rebuild' upon success
   void    rebuild  (                                                                                                                  ); // rebuild pak files database from loaded Pak's, this needs to be called once after adding new Pak's

   PakSet& del(); // delete manually
   PakSet();

private:
   struct Src : Pak
   {
      Str  name;
      Long pak_offset;
   };
   UInt           _root_files;
   CritSect       _cs;
   Meml<Src>      _paks;
   Memc<PaksFile> _files;
}extern
   Paks; // this is the global pak set which is automatically used when opening files
/******************************************************************************/
// MAIN
/******************************************************************************/
// Create Pak
inline Bool PakCreate(C Str               &file , C Str &pak_name=S, UInt flag=PAK_SHORTEN, Secure *dest_secure=NULL, Secure *src_secure=NULL, COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9, Bool (*filter)(C Str &name)=NULL, Str *error_message=NULL, PakProgress *progress=NULL) {return Pak().create(file , pak_name, flag, dest_secure, src_secure, compress, compression_level, filter, error_message, progress);}
inline Bool PakCreate(C Memp<Str        > &files, C Str &pak_name=S, UInt flag=PAK_SHORTEN, Secure *dest_secure=NULL, Secure *src_secure=NULL, COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9, Bool (*filter)(C Str &name)=NULL, Str *error_message=NULL, PakProgress *progress=NULL) {return Pak().create(files, pak_name, flag, dest_secure, src_secure, compress, compression_level, filter, error_message, progress);}
inline Bool PakCreate(C Memp<PakNode    > &files, C Str &pak_name  , UInt flag=          0, Secure *dest_secure=NULL                         , COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9                                  , Str *error_message=NULL, PakProgress *progress=NULL) {return Pak().create(files, pak_name, flag, dest_secure            , compress, compression_level        , error_message, progress);}
inline Bool PakCreate(C Memp<PakFileData> &files, C Str &pak_name  , UInt flag=          0, Secure *dest_secure=NULL                         , COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9                                  , Str *error_message=NULL, PakProgress *progress=NULL) {return Pak().create(files, pak_name, flag, dest_secure            , compress, compression_level        , error_message, progress);}

// Update Pak
Bool PakUpdate(Pak &src_pak, C Memp<PakFileData> &update_files, C Str &pak_name, Secure *dest_secure=NULL, COMPRESS_TYPE compress=COMPRESS_NONE, Int compression_level=9, Str *error_message=NULL); // update 'src_pak' by adding 'update_files' and saving the new Pak into 'pak_name', 'compression_level'=(0..9) (0=fastest/worst, 9=slowest/best), if compression is enabled then all files will be compressed (including uncompressed files from 'src_pak')

// Compare Pak
Bool PakEqual(C Memp<PakFileData> &files, C Pak &pak); // if 'files' are the same as the ones in 'pak' (this will verify if all files from 'files' are of the same size and modification time as those from 'pak', warning: folders may get ignored)
Bool PakEqual(C Memp<PakFileData> &files, C Str &pak_name, Secure *pak_secure=NULL);

inline Int Elms(C Pak    &pak ) {return pak .totalFiles();}
inline Int Elms(C PakSet &paks) {return paks.totalFiles();}
/******************************************************************************/
