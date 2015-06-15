/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
STRUCT_PRIVATE(MaterialPalette , Memc<MaterialPtr>)
//{
   // get
   Int          elms      (     )C {return super::elms      ( );} // get number of elements
 C MaterialPtr& operator[](Int i)C {return super::operator[](i);} // get i-th material
   UInt         memUsage  (     )C {return super::memUsage  ( );} // get memory usage

   Int getMaterialIndex(C MaterialPtr &material); // get index of desired 'material' in the palette, if 'material' is not listed in the palette it will be added, up to 255 materials can be stored, 0 index is always reserved for NULL material, -1 on fail

   // manage
   void del  () {super::del  ();} // delete manually
   void clear() {super::clear();} // clear

   // operations
   void remove(Int  i                       ); // remove i-th   material , 0-th material can't be removed because it's always reserved for NULL material
   Bool clean (Bool is[256], Byte remap[256]); // remove unused materials, 'is'=array of 256 possible values (true if used, false otherwise), 'remap'=material index remap obtained after function return to be used in followig way: "remap[src]=dest"

   // io
   void save(File &f, CChar *path=NULL)C; // save to   'f' file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load from 'f' file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   void   compress(File &f, C StrLibrary &materials_library)C;
   void decompress(File &f, C StrLibrary &materials_library) ;

private:
   Int _last;
};
/******************************************************************************/
STRUCT_PRIVATE(IDPalette , Memc<UID>)
//{
   // get
   Int  elms      (     )C {return super::elms      ( );} // get number of elements
 C UID& operator[](Int i)C {return super::operator[](i);} // get i-th ID
   UInt memUsage  (     )C {return super::memUsage  ( );} // get memory usage

   Int getIDIndex(C UID &id); // get index of desired 'id' in the palette, if 'id' is not listed in the palette it will be added, up to 255 ids can be stored, 0 index is always reserved for 'UIDZero' id, -1 on fail

   // manage
   void del  () {super::del  ();} // delete manually
   void clear() {super::clear();} // clear

   // io
   void save(File &f)C; // save to   'f' file
   Bool load(File &f) ; // load from 'f' file, false on fail

private:
   Int _last;
};
/******************************************************************************/
inline Int Elms(C MaterialPalette &mp) {return mp.elms();}
inline Int Elms(C       IDPalette &ip) {return ip.elms();}
/******************************************************************************/
