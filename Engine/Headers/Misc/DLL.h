/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'DLL' class to load a dll/so file.

   'DLL' operates on DLL files on Windows platforms, and SO files on Unix platforms.

/******************************************************************************/
struct DLL // DLL/SO loader
{
   // manage
   Bool createMem (  Ptr  data, Int size); // create DLL from memory, false on fail
   Bool createFile(C Str &file          ); // create DLL from file  , false on fail

   // get
   Bool is     (            )C; // if  DLL is created
   Ptr  getFunc(C Str8 &name)C; // get DLL function from its 'name'

   DLL&   del(); // delete manually
  ~DLL() {del();}
   DLL();

private:
   Ptr _dll_file, _dll_mem;
   NO_COPY_CONSTRUCTOR(DLL);
};
/******************************************************************************/
