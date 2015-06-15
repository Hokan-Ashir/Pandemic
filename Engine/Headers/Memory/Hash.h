/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct CRC32 // Cyclic Redundancy Check
{
   void reset     (                   ) ; // reset status
   void update    (CPtr data, Int size) ; // update with next portion of data
   UInt operator()(                   )C; // get current hash value

   CRC32() {reset();}

private:
   UInt _crc;
};
/******************************************************************************/
struct xxHash32 // xxHash 32-bit
{
   void reset     (                   ); // reset status
   void update    (CPtr data, Int size); // update with next portion of data
   UInt operator()(                   ); // finalize and get hash result

   xxHash32() {reset();}

private:
   ULong _buffer[6];
   Bool  _finalized;
   UInt  _hash;
};
/******************************************************************************/
struct xxHash64 // xxHash 64-bit
{
   void  reset     (                   ); // reset status
   void  update    (CPtr data, Int size); // update with next portion of data
   ULong operator()(                   ); // finalize and get hash result

   xxHash64() {reset();}

private:
   ULong _buffer[11];
   Bool  _finalized;
   ULong _hash;
};
/******************************************************************************/
struct MD5 // Message-Digest Algorithm
{
   void reset     (                   ); // reset status
   void update    (CPtr data, Int size); // update with next portion of data
 C UID& operator()(                   ); // finalize and get hash result

   MD5() {reset();}

private:
   Byte _buffer[64];
   UInt _count [2];
   Bool _finalized;
   UID  _hash;
};
/******************************************************************************/
struct SHA1 // Secure Hash Algorithm-1, with 160-bits
{
   union Hash
   {
      struct{Byte b[20];};
      struct{UInt i[ 5];};
   };

   void  reset     (                   ); // reset status
   void  update    (CPtr data, Int size); // update with next portion of data
 C Hash& operator()(                   ); // finalize and get hash result

   SHA1() {reset();}

private:
   Byte _buffer[64];
   UInt _count [2];
   Bool _finalized;
   Hash _hash;
};
/******************************************************************************/
struct SHA2 // Secure Hash Algorithm-2, with 256-bits
{
   union Hash
   {
      struct{Byte  b[32];};
      struct{UInt  i[ 8];};
      struct{ULong l[ 4];};
   };

   void  reset     (                   ); // reset status
   void  update    (CPtr data, Int size); // update with next portion of data
 C Hash& operator()(                   ); // finalize and get hash result

   SHA2() {reset();}

private:
   Byte _buffer[64];
   UInt _count [2];
   Bool _finalized;
   Hash _hash;
};
/******************************************************************************/
UInt      CRC32Mem(CPtr data, Int size); // calculate CRC32    for given memory
UInt   xxHash32Mem(CPtr data, Int size); // calculate xxHash32 for given memory
ULong  xxHash64Mem(CPtr data, Int size); // calculate xxHash64 for given memory
UID         MD5Mem(CPtr data, Int size); // calculate MD5      for given memory
SHA1::Hash SHA1Mem(CPtr data, Int size); // calculate SHA1     for given memory
SHA2::Hash SHA2Mem(CPtr data, Int size); // calculate SHA2     for given memory
/******************************************************************************/
