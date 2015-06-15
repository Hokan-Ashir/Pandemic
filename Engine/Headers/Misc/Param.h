/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Param' to store a custom parameter consisting of name and value.

/******************************************************************************/
enum PARAM_TYPE // Parameter Type
{
   PARAM_BOOL , // boolean
   PARAM_INT  , // int
   PARAM_FLT  , // float
   PARAM_STR  , // string
   PARAM_ENUM , // enum
   PARAM_VEC2 , // vector 2D
   PARAM_VEC  , // vector 3D
   PARAM_VEC4 , // vector 4D
   PARAM_COLOR, // color
   PARAM_ID   , // id
   PARAM_NUM  , // number of valid parameter types
};
/******************************************************************************/
struct Param // Parameter
{
   PARAM_TYPE type     ; // parameter type
   Enum      *enum_type; // pointer to 'Enum' object from 'Enums' cache, this is valid when 'type'==PARAM_ENUM
   Str        name     ; // parameter name
   struct
   {
      UNION
      (
         UNION_ELM(Bool  b ;) // bool
         UNION_ELM(Int   i ;) // int
         UNION_ELM(Flt   f ;) // float
         UNION_ELM(Vec2  v2;) // vector 2D
         UNION_ELM(Vec   v ;) // vector 3D
         UNION_ELM(Vec4  v4;) // vector 4D
         UNION_ELM(Color c ;) // color
         UNION_ELM(UID   id;) // id
      )
      Str s; // string
   }value; // parameter value

   // get
            Str   asText (Int precision=-6  )C; // ""        on fail
            Bool  asBool (                  )C; // false     on fail
            Int   asInt  (                  )C; // 0         on fail
            Flt   asFlt  (                  )C; // 0         on fail
            Vec2  asVec2 (                  )C; // (0,0)     on fail
            Vec   asVec  (                  )C; // (0,0,0)   on fail
            Vec4  asVec4 (                  )C; // (0,0,0,0) on fail
            Color asColor(                  )C; // (0,0,0,0) on fail
            UID   asID   (                  )C; // UIDZero   on fail
            Int   asEnum (                  )C; // -1        on fail
   T1(TYPE) TYPE  asEnum (TYPE invalid_value)C {Int e=asEnum(); return (e==-1) ? invalid_value : TYPE(e);} // use this method for custom enum types, 'invalid_value'=enum value to use when desired value was not found

   UInt memUsage()C; // get memory usage

   // set
   Param& fromInt (  Int  v); // change value to 'v' and preserve current parameter type
   Param& fromText(C Str &v); // change value to 'v' and preserve current parameter type

   // operations
   Param& clearValue (                                     ); // clear  value
   Param& changeType (PARAM_TYPE type, Enum *enum_type=NULL); // change type  to 'type' and automatically convert the parameter value
   Param& changeValue(C Param   &src                       ); // change value to 'src'  value and preserve current    parameter type

   // io
   void save(File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   Param();
};
/******************************************************************************/
Int Compare(C Param &p0, C Param &p1);
/******************************************************************************/
