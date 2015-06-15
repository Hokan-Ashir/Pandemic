/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
namespace Edit{
/******************************************************************************/
struct Item
{
   enum TYPE
   {
      UNKNOWN,
      LIB    ,
      APP    ,
      FOLDER ,
      FILE   ,
   };
   Enum1<TYPE> type;
   Str         base_name, full_name;
   Memx<Item>  children;

   Item() {type=UNKNOWN;}
};
/******************************************************************************/
} // namespace
/******************************************************************************/
