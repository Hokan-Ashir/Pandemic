/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use following functions to handle data compression.

/******************************************************************************/
enum COMPRESS_TYPE // Compression Library Type
{
   COMPRESS_NONE  , // don't use               compression, best      performance (60x), biggest  size (100%), data is stored in original format
   COMPRESS_ZLIB  , // use ZLib                compression, medium    performance ( 5x), small    size (~60%)
   COMPRESS_LZMA  , // use LZMA                compression, slowest   performance ( 1x), smallest size (~51%), memory required for decompressing depends on 'compression_level', each level requires following amount of memory: 0->16KB, 1->64KB, 2->256KB, 3->1MB, 4->4MB, 5->16MB, 6->32MB, 7..9->64MB, while memory required for compression is: 0->1.5MB, 1->1.8MB, 2->3MB, 3->8MB, 4->32MB, 5->185MB, 6->370MB, 7..9->675MB
   COMPRESS_SNAPPY, // use Google Snappy       compression, good      performance (11x), big      size (~72%), the library was designed to achieve fastest compression/decompression speed at the cost of lower compression when compared to ZLib
   COMPRESS_RLE   , // use Run-Length Encoding compression, very good performance (23x), big      size (   ?), compression can be good only for memory in which can be found continuous chunks of bytes of the same value
   COMPRESS_LZ4_HC, // use LZ4 High            compression, very good performance (25x), medium   size (~63%), the library was designed to achieve fastest compression/decompression speed at the cost of lower compression when compared to ZLib, compression is slower than Snappy, however decompression is faster and the file sizes are smaller
   COMPRESS_LZ4   , // use LZ4 Low             compression, very good performance (25x), medium   size (~70%), the library was designed to achieve fastest compression/decompression speed at the cost of lower compression when compared to ZLib, compression is faster than Snappy,         decompression is faster and the file sizes are smaller
   COMPRESS_LZHAM , // use LZHAM               compression, slow      performance ( 2x), small    size (~53%), compression is slower than LZMA and it achieves slightly worse compression rates than LZMA, however decompression speeds are 1.5-8x higher
   COMPRESS_NUM   , // number of compression types
};
/******************************************************************************/
Bool Compressable(C Str &file_extension); // if 'file_extension' is compressable (compressing most likely would reduce the file size, this returns false for file types already compressed like "jpg", "mp3", "avi", "rar", .. and true for all other file types)

CChar8* CompressionName  (COMPRESS_TYPE type); // get compression type name in text format
VecI2   CompressionLevels(COMPRESS_TYPE type); // get range of compression levels for specified type, 'VecI2.x' will contain the minimum level, 'VecI2.y' will contain the maximum level, if both values are the same, then it means that this type does not support different compression levels

// perform file->file (de)compression
Bool   Compress    (File &src, File &dest, COMPRESS_TYPE type, Int compression_level=9, Bool multi_threaded=true); //   compress data from 'src' file into 'dest' file, 'src' should be already opened for reading, 'dest' should be already opened for writing, 'compression_level'=(0..9) (0=fastest/worst, 9=slowest/best), compression occurs from the current position of 'src' to the end of the file, false on fail
Bool Decompress    (File &src, File &dest, Bool memory=false                                                    ); // decompress data from 'src' file into 'dest' file, 'src' should be already opened for reading, 'dest' should be already opened for writing if 'memory' is set to false, if 'memory' is set to true then decompression will be faster, however 'dest' will be first reinitialized with 'writeMemFixed' before decompressing, which means that decompression result will not be stored into original 'dest' target, but instead into a dynamically allocated memory, false on fail
Int  DecompressSize(File &src                                                                                   ); // get decompressed size of 'src' without decompressing it, if 'src' file contains compressed data then this function will return the size of decompressed data without doing any decompression, -1 will be returned on fail (if the file does not contain compressed data), this function restores 'src' position to the place before the call
/******************************************************************************/
