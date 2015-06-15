/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'File' to handle binary files management.

/******************************************************************************/
enum FILE_PATH // File Path Type
{
   FILE_CUR , // relative to 'CurDir'
   FILE_DATA, // relative to 'DataPath'
};
struct File
{
   // manage
   File& del(); // manually delete the file object (this does not delete the file on the disk, it only closes the handle of the C++ file object and releases used memory)

   File& append     (C Str &name, const_mem_addr Secure *secure=NULL); // append      stdio file, Exit on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& write      (C Str &name, const_mem_addr Secure *secure=NULL); // write to    stdio file, Exit on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& readStd    (C Str &name, const_mem_addr Secure *secure=NULL); // read        stdio file, Exit on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& read       (C Str &name, const_mem_addr Secure *secure=NULL); // read Pak or stdio file, Exit on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& read       (C UID &id  , const_mem_addr Secure *secure=NULL); // read Pak or stdio file, Exit on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& read       (C Str &name, C Pak    &pak                     ); // read Pak          file, Exit on fail
   File& read       (C UID &id  , C Pak    &pak                     ); // read Pak          file, Exit on fail
   File& read       (C Str &name, C PakSet &paks                    ); // read Pak          file, Exit on fail
   File& read       (C UID &id  , C PakSet &paks                    ); // read Pak          file, Exit on fail
   File& read       (             C Pak    &pak , C PakFile &file   ); // read Pak          file, Exit on fail

   Bool appendTry   (C Str &name, const_mem_addr Secure *secure=NULL); // try to append      stdio file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool  writeTry   (C Str &name, const_mem_addr Secure *secure=NULL); // try to write to    stdio file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readStdTry(C Str &name, const_mem_addr Secure *secure=NULL); // try to read        stdio file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readTry   (C Str &name, const_mem_addr Secure *secure=NULL); // try to read Pak or stdio file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readTry   (C UID &id  , const_mem_addr Secure *secure=NULL); // try to read Pak or stdio file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool   readTry   (C Str &name, C Pak    &pak                     ); // try to read Pak          file, false on fail
   Bool   readTry   (C UID &id  , C Pak    &pak                     ); // try to read Pak          file, false on fail
   Bool   readTry   (C Str &name, C PakSet &paks                    ); // try to read Pak          file, false on fail
   Bool   readTry   (C UID &id  , C PakSet &paks                    ); // try to read Pak          file, false on fail
   Bool   readTry   (             C Pak    &pak , C PakFile &file   ); // try to read Pak          file, false on fail

   File& writeMemFixed( Int size              , const_mem_addr Secure *secure=NULL); // start writing to   fixed     memory file    (reading is also allowed in this mode, for example you can write some data to the memory, reset file position, and read what has been written), 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File& writeMem     (UInt block_elms=64*1024, const_mem_addr Secure *secure=NULL); // start writing to   resizable memory file    (reading is also allowed in this mode, for example you can write some data to the memory, reset file position, and read what has been written), 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   File&  readMem     (CPtr data, Int size    , const_mem_addr Secure *secure=NULL); // start reading from fixed     memory address (writing is not  allowed in this mode)                                                                                                        , 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)

   // get / set
   Bool is  (        )C {return _type!=0    ;} // if  file is opened
   Bool pos (Long pos);                        // set position, false on fail
   Long pos (        )C {return _pos        ;} // get position
   Long size(        )C {return _size       ;} // get size
   Long left(        )C {return _size-_pos  ;} // get size left (number of bytes from current position to the end of the file)
   Bool end (        )C {return _pos>=_size ;} // if  current position is at the end of the file
   Bool skip(Long n  )  {return  pos(_pos+n);} // skip 'n' bytes going forward

   // put / get
   Bool get( Ptr data, Int size); // read  from file to 'data' memory, false on fail
   Bool put(CPtr data, Int size); // write from 'data' memory to file, false on fail

   T1(TYPE) void  putN      (C TYPE *t, Int n) {put( t, SIZE(TYPE)*n);          } // write raw array  of 'n' number of 't' elements
   T1(TYPE) void  getN      (  TYPE *t, Int n) {get( t, SIZE(TYPE)*n);          } // read  raw array  to 'n' number of 't' elements
   T1(TYPE) File& operator<<(C TYPE &t       ) {put(&t, SIZE(TYPE)  ); return T;} // write raw memory of 't' object
   T1(TYPE) File& operator>>(  TYPE &t       ) {get(&t, SIZE(TYPE)  ); return T;} // read  raw memory to 't' object
            File& operator<<(C Str8 &s       ) {return putStr(s);               } // write string
            File& operator<<(C Str  &s       ) {return putStr(s);               } // write string
            File& operator>>(  Str8 &s       ) {return getStr(s);               } // read  string
            File& operator>>(  Str  &s       ) {return getStr(s);               } // read  string

   File& putBool  (  Bool  b) {T<<b; return T;}   Bool  getBool  () {Bool   b; T>>b; return b;} // write/read  Bool
   File& putByte  (  Byte  b) {T<<b; return T;}   Byte  getByte  () {Byte   b; T>>b; return b;} // write/read  Byte
   File& putShort (  Short i) {T<<i; return T;}   Short getShort () {Short  i; T>>i; return i;} // write/read  Short
   File& putUShort( UShort u) {T<<u; return T;}  UShort getUShort() {UShort u; T>>u; return u;} // write/read UShort
   File& putInt   (  Int   i) {T<<i; return T;}   Int   getInt   () {Int    i; T>>i; return i;} // write/read  Int
   File& putUInt  ( UInt   u) {T<<u; return T;}  UInt   getUInt  () {UInt   u; T>>u; return u;} // write/read UInt
   File& putLong  (  Long  i) {T<<i; return T;}   Long  getLong  () {Long   i; T>>i; return i;} // write/read  Long
   File& putULong ( ULong  u) {T<<u; return T;}  ULong  getULong () {ULong  u; T>>u; return u;} // write/read ULong
   File& putFlt   (  Flt   f) {T<<f; return T;}   Flt   getFlt   () {Flt    f; T>>f; return f;} // write/read  Float
   File& putDbl   (  Dbl   d) {T<<d; return T;}   Dbl   getDbl   () {Dbl    d; T>>d; return d;} // write/read  Double
   File& putUID   (C UID  &i) {T<<i; return T;}   UID   getUID   () {UID    i; T>>i; return i;} // write/read  UID

   File& putStr(CChar8 *t); // write string
   File& putStr(CChar  *t); // write string
   File& putStr(C Str8 &s); // write string
   File& putStr(C Str  &s); // write string
   Str   getStr(         ); // read  string, this method can be used to read previously written strings using all 'putStr' methods
   File& getStr(  Str8 &s); // read  string, this method can be used to read previously written strings using all 'putStr' methods
   File& getStr(  Str  &s); // read  string, this method can be used to read previously written strings using all 'putStr' methods

   File& putAsset(CChar *name); // write asset location, this method is optimized for saving asset locations, typically assets are stored with file name based on UID, in such case this method can detect that and save the location using fewer bytes
   File& putAsset(C UID &id  ); // write asset location, this method is optimized for saving asset locations, typically assets are stored with file name based on UID, in such case this method can detect that and save the location using fewer bytes
   Str   getAsset(           ); // read  asset location, this method can be used to read previously written asset location using all 'putAsset' method

   // compress / decompress
   File& cmpIntV   (  Int      i);                                                              //   compress any Int to   variable number of bytes (1..5) depending on the value of the Int (values -63..64 will require only 1 byte, -8191..8192 will require 2 bytes, -1048575..1048576 will require 3 bytes, bigger values will require more bytes)
   File& decIntV   (  Int     &i);   Int     decIntV   () {Int     i; decIntV   (i); return i;} // decompress any Int from variable number of bytes (1..5)

   File& cmpUIntV  ( UInt      u);                                                              //   compress any UInt to   variable number of bytes (1..5) depending on the value of the UInt (values 0..127 will require only 1 byte, 128..16383 will require 2 bytes, 16384..2097151 will require 3 bytes, bigger values will require more bytes)
   File& decUIntV  ( UInt     &u);   UInt    decUIntV  () {UInt    u; decUIntV  (u); return u;} // decompress any UInt from variable number of bytes (1..5)

   File& cmpLongV  (  Long     l);                                                              //   compress any Long to   variable number of bytes (1..9) depending on the value of the Long (values -64..63 will require only 1 byte, -8192..8191 will require 2 bytes, -1048576..1048575 will require 3 bytes, bigger values will require more bytes)
   File& decLongV  (  Long    &l);   Long    decLongV  () {Long    l; decLongV  (l); return l;} // decompress any Long from variable number of bytes (1..9)

   File& cmpULongV ( ULong     u);                                                              //   compress any ULong to   variable number of bytes (1..9) depending on the value of the ULong (values 0..127 will require only 1 byte, 128..16383 will require 2 bytes, 16384..2097151 will require 3 bytes, bigger values will require more bytes)
   File& decULongV ( ULong    &u);   ULong   decULongV () {ULong   u; decULongV (u); return u;} // decompress any ULong from variable number of bytes (1..9)

   File& cmpFlt3cm (C Flt     &r);                                                              //   compress Float in range -83,800 .. 83,800 to   3 bytes with precision of 0.01 (this covers range of -83..83 kilometers with 1 centimeter precision)
   File& decFlt3cm (  Flt     &r);   Flt     decFlt3cm () {Flt     r; decFlt3cm (r); return r;} // decompress Float in range -83,800 .. 83,800 from 3 bytes with precision of 0.01 (this covers range of -83..83 kilometers with 1 centimeter precision)

   File& cmpSatFlt1(C Flt     &r);                                                              //   compress Saturated Float in range 0..1 to   1 byte  (having   256 possible values, and precision of ~0.00400)
   File& cmpSatFlt2(C Flt     &r);                                                              //   compress Saturated Float in range 0..1 to   2 bytes (having 65536 possible values, and precision of ~0.00001)
   File& decSatFlt1(  Flt     &r);   Flt     decSatFlt1() {Flt     r; decSatFlt1(r); return r;} // decompress Saturated Float in range 0..1 from 1 byte
   File& decSatFlt2(  Flt     &r);   Flt     decSatFlt2() {Flt     r; decSatFlt2(r); return r;} // decompress Saturated Float in range 0..1 from 2 bytes

   File& cmpAngle1 (C Flt     &r);                                                              //   compress Angle Float (0..PI2) to   1 byte  (having   256 possible values, and precision of ~0.02000)
   File& cmpAngle2 (C Flt     &r);                                                              //   compress Angle Float (0..PI2) to   2 bytes (having 65536 possible values, and precision of ~0.00009)
   File& decAngle1 (  Flt     &r);   Flt     decAngle1 () {Flt     r; decAngle1 (r); return r;} // decompress Angle Float          from 1 byte
   File& decAngle2 (  Flt     &r);   Flt     decAngle2 () {Flt     r; decAngle2 (r); return r;} // decompress Angle Float          from 2 bytes

   File& cmpDir2   (C Vec     &v);                                                              //   compress Normalized Direction Vector to   2 bytes
   File& cmpDir3   (C Vec     &v);                                                              //   compress Normalized Direction Vector to   3 bytes
   File& decDir2   (  Vec     &v);   Vec     decDir2   () {Vec     v; decDir2   (v); return v;} // decompress Normalized Direction Vector from 2 bytes
   File& decDir3   (  Vec     &v);   Vec     decDir3   () {Vec     v; decDir3   (v); return v;} // decompress Normalized Direction Vector from 3 bytes

   File& cmpOrient2(C Matrix3 &m);                                                              //   compress Orientation to   2 bytes (its scale is ignored, only rotation is saved)
   File& cmpOrient3(C Matrix3 &m);                                                              //   compress Orientation to   3 bytes (its scale is ignored, only rotation is saved)
   File& cmpOrient4(C Matrix3 &m);                                                              //   compress Orientation to   4 bytes (its scale is ignored, only rotation is saved)
   File& decOrient2(  Matrix3 &m);   Matrix3 decOrient2() {Matrix3 m; decOrient2(m); return m;} // decompress Orientation from 2 bytes
   File& decOrient3(  Matrix3 &m);   Matrix3 decOrient3() {Matrix3 m; decOrient3(m); return m;} // decompress Orientation from 3 bytes
   File& decOrient4(  Matrix3 &m);   Matrix3 decOrient4() {Matrix3 m; decOrient4(m); return m;} // decompress Orientation from 4 bytes

   // operations
   File&      reset   (                                             ); // reset all written  data to the memory, this method affects only files which have been created using 'writeMem', this method sets file position and size to zero, but keeps the file in mode available for writing new data
   Bool       flush   (                                             ); // flush all buffered data to the disk  , false on fail
   Bool       equal   (File &f   , Long max_size=-1                 ); // if has the same data as 'f' file   (only data from the current positions to the end are compared, and not from the start to the end), 'max_size'=number of bytes to compare (-1=all remaining)
   Bool       copy    (File &dest, Long max_size=-1, Bool flush=true); // copy file to 'dest', false on fail (only data from the current position  to the end are copied  , and not from the start to the end), 'max_size'=number of bytes to copy    (-1=all remaining), 'flush'=if flush the 'dest' file at the end of the copy and verify that it has succeeded
   UInt       crc32   (                                             ); // get file CRC32    from current position to the end of the file, this reads the data and modifies file position
   UInt       xxHash32(                                             ); // get file xxHash32 from current position to the end of the file, this reads the data and modifies file position
   ULong      xxHash64(                                             ); // get file xxHash64 from current position to the end of the file, this reads the data and modifies file position
   UID        md5     (                                             ); // get file MD5      from current position to the end of the file, this reads the data and modifies file position
   SHA2::Hash sha2    (                                             ); // get file SHA2     from current position to the end of the file, this reads the data and modifies file position

           ~File() {del();}
            File();
   explicit File(             C Pak &pak , C PakFile &file                   ); // read Pak          file, Exit on fail
   explicit File(C Str &name, C Pak &pak                                     ); // read Pak          file, Exit on fail
   explicit File(C Str &name             , const_mem_addr Secure *secure=NULL); // read Pak or stdio file, Exit on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   explicit File( CPtr  data,   Int  size, const_mem_addr Secure *secure=NULL); // start reading from memory address (writing is not allowed in this mode), 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)

private:
   Byte       _type  , _mode, _path;
   ULong      _offset, _pos , _size, _apk_offset;
 C Pak       *_pak   ;
   Secure    *_secure;
   Memb<Byte> _memb  ;
   Ptr        _buf   ; Int _buf_pos, _buf_len, _buf_size, _handle; // Std
   Ptr        _mem   ; // Mem
   NO_COPY_CONSTRUCTOR(File);
};
/******************************************************************************/
