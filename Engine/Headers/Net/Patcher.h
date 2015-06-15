/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Patcher' for patching files on local computer,
      according to server files uploaded using "Uploader" tool.

/******************************************************************************/
const_mem_addr struct Patcher // class for automatic downloading file updates from a http server !! must be stored in constant memory address !!
{
   struct LocalFile // use this class to describe an element stored on local computer
   {
      enum TYPE
      {
         PAK_FILE   , // PakFile          (       file   inside Pak  archive)
         SYSTEM_FILE, // system file      (normal file   on     your drive  )
         SYSTEM_DIR , // system directory (normal folder on     your drive  )
      };

      TYPE     type           ; // specifies how the file is stored on the local computer
      Str      full_name      ; // full name of file (path+name) relative to your data storage folder (don't include the drive here, instead, use path relative to the folder which has been used for uploading your files)
      Long     file_size      ; // size  of file in bytes (leave 0 for folders)
      UInt     crc32          ; // crc32 of file (this is optional, it can be left at 0 which will disable checking for crc differences, however when enabled, it can provide more reliable detecting differences between file versions)
      DateTime modify_time_utc; // file modification time in UTC time zone

      LocalFile& set(C Str &full_name, C FileInfo &fi); // set from 'full_name' and 'FileInfo'

      LocalFile() {type=PAK_FILE; file_size=0; crc32=0; modify_time_utc.zero();}
   };

   struct Downloaded
   {
      Bool      success        ; // file downloaded successfully, if this is equal to false it means that the file was not found or it was different than expected
      Int       index          ; // file index in 'Patcher.index' Pak
      UInt      crc32          ; // crc32 of file data  (can be 0 if not calculated)
      FSTD_TYPE type           ; // type of the element, can be FSTD_FILE, FSTD_DIR or FSTD_LINK
      DateTime  modify_time_utc; // file modification time in UTC time zone
      Str       full_name      ; // full name of downloaded file
      File      data           ; // file data

      Downloaded() {success=false; index=-1; crc32=0; type=FSTD_NONE; modify_time_utc.zero();}
   };

   struct InstallerInfo
   {
      Int      size           ; // file size
      UInt     crc32          ; // crc32 of file data
      DateTime modify_time_utc; // file modification time in UTC time zone

      InstallerInfo();
   };

   // local file list
   static void SetList(Memp<LocalFile> local_files, C Str    &dir ); // automatically create 'local_files' list from 'dir'  folder on your local computer (this will process all system files and folders inside 'dir'  and list them in 'local_files' container)
   static void SetList(Memp<LocalFile> local_files, C PakSet &paks); // automatically create 'local_files' list from 'paks' set of paks                   (this will process all pak files                inside 'paks' and list them in 'local_files' container)

   // manage
   Patcher& create(C Str &http_dir, C Str &upload_name, Secure *secure=NULL); // create the patcher according to provided internet address, 'http_dir'=case-sensitive http address of the directory where files were uploaded (for example: "http://www.domain.com/download"), 'upload_name'=case-sensitive name of the upload (for example: "GameName"), 'secure'=secure keys used during upload, these parameters must match the ones you have provided in the Uploader tool

   // get
      // installer information
      Patcher& downloadInstallerInfo     (); // initialize downloading of the installer information, downloading will begin on secondary thread
      DWNL_STATE       installerInfoState(); // get state  of installer information download, once it's equal to DWNL_DONE you can access it
    C InstallerInfo*   installerInfo     (); // get access to installer information (this will return a valid pointer only if 'installerInfoState' is equal to DWNL_DONE), NULL on fail

      // installer
      Patcher& downloadInstaller        (); // initialize downloading of the installer, downloading will begin on secondary thread (this automatically initiates downloading of installer information if it wasn't previously downloaded)
      DWNL_STATE       installerState   (); // get state  of installer download, once it's equal to DWNL_DONE you can access it
      Int              installerProgress(); // get number of downloaded bytes for the installer
    C Mems<Byte>*      installer        (); // get access to raw bytes of installer .exe file which you can write on disk, quit current installer and run the updated version (this will return a valid pointer only if 'installerState' is equal to DWNL_DONE), NULL on fail

      // index
      Patcher& downloadIndex     (); // initialize downloading of the index (list of all current files on the server), downloading will begin on secondary thread
      DWNL_STATE       indexState(); // get state  of index download, once it's equal to DWNL_DONE you can access its information
    C Pak*             index     (); // get access to the index of files on the server (this will return a valid pointer only if 'indexState' is equal to DWNL_DONE), NULL on fail

      // file
      Patcher& downloadFile(Int         i         ); // initialize downloading of i-th file in index from server, downloading will begin on secondary thread, this method should be called after downloading the index
      Bool  getNextDownload(Downloaded &downloaded); // get next downloaded file, this method checks if there is a file fully downloaded, if there is one, it sets information about it into 'downloaded' parameter and returns true, if there is no file downloaded at this moment, then false is returned and given parameter is unmodified

   // stats
   Long progress ()C; // get number of bytes that have been already downloaded (this includes only files, this does not include installer info, installer, index and overhead)
   Long filesSize()C; // get number of bytes of all files requested to be downloaded (this includes files that have been downloaded and those that still need to be downloaded)
   Int  filesLeft()C; // get number of files that are still waiting to be downloaded

   // compare
   Bool compare(C Memp<LocalFile> &local_files, Memp<Int> local_remove, Memp<Int> server_download); // compare list of files from server (index) with list of files on local computer (local_files), 'local_remove'=list of indexes from 'local_files' that need to be removed (those files are not present in the server, therefore we should remove them), 'server_download'=list of indexes from "index->file" that need to be downloaded from the server (those files aren't present in the local computer or are of different version, therefore we should download latest version and replace existing one if any), this method relies on 'index', so you should call it only after downloading the index using 'downloadIndex' method with 'indexState' returning DWNL_DONE, false on fail ('index' not yet available)

   static void Compare(C Memp<LocalFile> &src_files, C Memp<LocalFile> &dest_files, Memp<Int> dest_remove, Memp<Int> src_copy); // compare list of files from source ('src_files') with list of files from destination ('dest_files'), 'dest_remove'=list of indexes from 'dest_files' that need to be removed (those files are not present in the source, therefore we should remove them), 'src_copy'=list of indexes from 'src_files' that need to be copied from the source to the destination (those files aren't present in destination or are of different version, therefore we should copy latest version from the source and replace existing one in the destination, if any)

   Patcher&   del(); // delete manually
  ~Patcher() {del();}
   Patcher();

private:
   struct FileDownload : Download
   {
      Int index;
   };
   Str              _http, _name;
   Secure          *_secure;
   Bool             _pak_available, _inst_info_available, _inst_available;
   Download         _pak_download , _inst_info_download , _inst_download ;
   FileDownload     _file_download[6];
   Int              _files_left;
   Long             _bytes_downloaded;
   Pak              _pak;
   InstallerInfo    _inst_info;
   Mems<Byte>       _inst;
   Memc<Int >       _to_download;
   Memc<Downloaded> _downloaded;
   CritSect         _cs;
   Thread           _thread;
};
/******************************************************************************/
