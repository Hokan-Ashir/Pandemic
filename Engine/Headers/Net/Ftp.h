/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Ftp' to handle FTP connections.

/******************************************************************************/
struct FtpFile : FileInfo
{
   Str name;
};
struct Ftp // File Transfer Protocol, Ftp supports only one command/transfer at a time
{
   // manage
   Bool login (C Str8 &host, C Str8 &user, C Str8 &password, Int port=21); //    connect to   FTP, false on fail
   void logout(                                                         ); // disconnect from FTP

   // get / set
   Bool is        (                              )C {return _socket.is();} // if  connected to the FTP
   Long progress  (                              )C {return _progress   ;} // get transfer progress (in bytes)
   Long total     (                              )C {return _total      ;} // get transfer total    (in bytes, -1=unknown)
   Bool noop      (                              ); // send empty message to keep up the connection, false on fail
   Long fileSize  (C Str8 &file                  ); // get file size                               , -1    on fail
   Bool fileTime  (C Str8 &file,   DateTime &dt  ); // get file modification time                  , false on fail
   Bool rename    (C Str8 &src , C Str8     &dest); // rename file/directory                       , false on fail
   Bool removeFile(C Str8 &file                  ); // remove file                                 , false on fail
   Bool removeDir (C Str8 &dir                   ); // remove empty   directory                    , false on fail
   Bool createDir (C Str8 &dir                   ); // create empty   directory                    , false on fail
   Bool changeDir (C Str8 &dir                   ); // change current directory                    , false on fail

   // io, if following functions will be called in a secondary thread, then you may not perform any operations on the given 'File', until the methods return
   Bool  download(C Str8 &src ,   File &dest, Long offset=0, Bool passive=true, Secure * src_secure=NULL); // download 'src' file from FTP to 'dest' file       , 'passive'=transfer mode, false on fail, 'dest' file should be already opened for writing mode (either to   disk or memory)
   Bool    upload(  File &src , C Str8 &dest               , Bool passive=true, Secure *dest_secure=NULL); //   upload 'src' file to   FTP    'dest' location   , 'passive'=transfer mode, false on fail, 'src'  file should be already opened for reading mode (either from disk or memory), data is uploaded from current position of 'src' file (not from start)
   Bool    append(  File &src , C Str8 &dest               , Bool passive=true                          ); //   append 'src' file to   FTP    'dest' location   , 'passive'=transfer mode, false on fail, 'src'  file should be already opened for reading mode (either from disk or memory), data is uploaded from current position of 'src' file (not from start)
   Bool listFiles(C Str8 &path, Memp<FtpFile> files        , Bool passive=true                          ); // retrieve a list of all files in the specified path, 'passive'=transfer mode, false on fail, warning: not all fields in the 'FtpFile' may be valid, this is because hosts don't necessarily provide all the info
   Bool listNames(C Str8 &path, Memp<Str    > names        , Bool passive=true                          ); // retrieve a list of all names in the specified path, 'passive'=transfer mode, false on fail
   void     abort(                                                                                      ); // notify that the current transfer operation should be aborted, this can be called in a secondary thread to cancel any active transfer

  ~Ftp() {logout();}
   Ftp();

private:
   Bool   _binary  , _abort, _timeout, _timeouts;
   Int    _port;
   Long   _progress, _total;
   Socket _socket;
   Str8   _response, _host, _user, _password;
};
/******************************************************************************/
