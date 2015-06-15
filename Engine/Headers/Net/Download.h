/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Download' to download a single file from the internet.

   'Download' can be also used to upload files when 'File post' parameter is specified,
      in that case, POST command will be used instead of GET.
   You can use following PHP code on the server to process the file:

      <?php
      function LogN($text) {error_log($text."\n", 3, "log.txt");}

      $error    =$_FILES["file"]["error"   ]; // if error occured during file receiving
      $file_size=$_FILES["file"]["size"    ]; // file size
      $temp_name=$_FILES["file"]["tmp_name"]; // temporary file name
      $file_name="Uploads/file";              // desired   file name

      if($error>0) // if any error occured
      {
         LogN('Error:'.$error);
      }else
      {
         LogN("File Size: ".$file_size);
         LogN("Temp Name: ".$temp_name);

         if(file_exists($file_name)) // check if such file already exists
         {
	         LogN($file_name." already exists"); // don't store it
         }else
         {
	         move_uploaded_file($temp_name, $file_name); // store the file
         }
      }
      ?>

/******************************************************************************/
enum DWNL_STATE // Download States
{
   DWNL_NONE      , // nothing
   DWNL_CONNECTING, // waiting for connection
   DWNL_SENDING   , // sending request and 'post' data if specified
   DWNL_DOWNLOAD  , // downloading
   DWNL_DONE      , // done
   DWNL_ERROR     , // error encountered
};
/******************************************************************************/
STRUCT(URLParam , TextParam) // optional parameter that can be passed to the 'Download'
//{
   Bool get; // if this is "GET" or "POST" parameter

   URLParam& set(C Str &name, C Str &value, Bool get=true) {super::set(name, value); T.get=get; return T;}

   URLParam() {get=true;}
};
/******************************************************************************/
const_mem_addr struct Download // File Downloader !! must be stored in constant memory address !!
{
   // manage
   Download& del   (  Int  milliseconds=-1                                                                                                       ); // wait 'milliseconds' time for thread to exit and delete (<0 = infinite wait)
   Download& create(C Str &url, C Memp<URLParam> &params=NULL, const_mem_addr File *post=NULL, Long max_post_size=-1, Long offset=0, Long size=-1); // download 'url' file, 'params'=optional parameters that you can pass if the 'url' is a php script, 'post'=data to be sent to the specified address (if this is NULL then HTTP GET is used, otherwise HTTP POST is used, 'post' File must point to a constant memory address as that pointer will be used until the data has been fully sent), 'offset'=offset position of the file data to download, use this for example if you wish to resume previous download by starting from 'offset' position, 'size'=number of bytes to download (-1=all remaining), warning: some servers don't support manual specifying 'offset' and 'size', 'max_post_size'=number of bytes to send (-1=all remaining)

   // operations
   Download&  pause        (                   );                       // pause  downloading
   Download&  resume       (                   );                       // resume downloading
   Download&  stop         (                   );                       // request the download to be stopped and return immediately after that, without waiting for the thread to exit
   Download&  wait         (Int milliseconds=-1);                       // wait for the download thread to exit (<0 = infinite wait)
   Bool       error        (                   );                       // set DWNL_ERROR state, you can signal that an error has encountered for example when invalid data downloaded, always returns false
   DWNL_STATE state        (                   )C {return _state     ;} // get download   state
   Ptr        data         (                   )C {return _data      ;} // get downloaded data            , this will be valid only in DWNL_DONE state
   Long       offset       (                   )C {return _offset    ;} // get offset of file
   Long       done         (                   )C {return _done      ;} // get number of downloaded bytes
   Long       size         (                   )C {return _size      ;} // get number of bytes to download, this will be valid only in DWNL_DONE state, in DWNL_DOWNLOAD state the value will be either valid or equal to -1 if the size is still unknown
   Long       totalSize    (                   )C {return _total_size;} // get total file size            , this will be valid only in DWNL_DONE state, in DWNL_DOWNLOAD state the value will be either valid or equal to -1 if the size is still unknown
   Long       sent         (                   )C {return _sent      ;} // get number of sent bytes 
   Long       toSend       (                   )C {return _to_send   ;} // get number of bytes to send
 C Str&       url          (                   )C {return _url       ;} // get url address
 C DateTime&  modifyTimeUTC(                   )C {return _modif_time;} // get modification time in UTC time zone of the downloaded file, if value is provided then it will be available starting from DWNL_DOWNLOAD state

  ~Download() {del();}
   Download();
   Download(C Str &url, C Memp<URLParam> &params=NULL, const_mem_addr File *post=NULL, Long max_post_size=-1, Long offset=0, Long size=-1);

private:
   Bool              _chunked, _has_header;
   Byte              _parsing;
   Enum1<DWNL_STATE> _state;
   Int               _expected_size, _pre_send, _pos_send;
   Long              _offset, _done, _size, _total_size, _sent, _to_send;
   Ptr               _data;
   File             *_post_file;
   DateTime          _modif_time;
   Str8              _url_full, _header;
   Str               _url;
   Thread            _thread;
   Socket            _socket;
   Memb<Byte>        _memb;
   Mems<Byte>        _message;
   NO_COPY_CONSTRUCTOR(Download);
};
/******************************************************************************/
