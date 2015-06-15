/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Calc' functions to calculate string expressions and convert them to values.

   Sample Usage:

      Flt result=CalcR("2*3");

/******************************************************************************/
enum CVAL_TYPE // Calculator Value Type
{
   CVAL_NONE  , // none
   CVAL_INT   , // integer
   CVAL_LONG  , // long
   CVAL_REAL  , // real
   CVAL_VEC2  , // vector 2D
   CVAL_VEC   , // vector 3D
   CVAL_VEC4  , // vector 4D
   CVAL_MATRIX, // matrix
};
/******************************************************************************/
struct CalcValue // Calculator Value
{
   CVAL_TYPE type; // value type
   UNION
   (
      UNION_ELM(Int    i ;) // integer
      UNION_ELM(Long   l ;) // long
      UNION_ELM(Dbl    r ;) // real
      UNION_ELM(VecD2  v2;) // vector 2D
      UNION_ELM(VecD   v ;) // vector 3D
      UNION_ELM(VecD4  v4;) // vector 4D
      UNION_ELM(Matrix m ;) // matrix
   )

   // get
   CChar* typeName(                     )C; // get CVAL_TYPE type name in text format
   Str    asText  (Int precision=INT_MAX)C; // get value as text
   Int    asInt   (                     )C; // get value as Int   , 0 on fail
   UInt   asUInt  (                     )C; // get value as UInt  , 0 on fail
   Long   asLong  (                     )C; // get value as Long  , 0 on fail
   ULong  asULong (                     )C; // get value as ULong , 0 on fail
   Flt    asFlt   (                     )C; // get value as Flt   , 0 on fail
   Dbl    asDbl   (                     )C; // get value as Dbl   , 0 on fail
   Vec2   asVec2  (                     )C; // get value as Vec2  , (0,0) on fail
   VecD2  asVecD2 (                     )C; // get value as VecD2 , (0,0) on fail
   VecI2  asVecI2 (                     )C; // get value as VecI2 , (0,0) on fail
   Vec    asVec   (                     )C; // get value as Vec   , (0,0,0) on fail
   VecD   asVecD  (                     )C; // get value as VecD  , (0,0,0) on fail
   VecI   asVecI  (                     )C; // get value as VecI  , (0,0,0) on fail
   Vec4   asVec4  (                     )C; // get value as Vec4  , (0,0,0,0) on fail
   VecD4  asVecD4 (                     )C; // get value as VecD4 , (0,0,0,0) on fail
   VecI4  asVecI4 (                     )C; // get value as VecI4 , (0,0,0,0) on fail
   Matrix asMatrix(                     )C; // get value as Matrix, MatrixIdentity on fail
};
/******************************************************************************/
struct CalcVar // Calculator Variable
{
   Str       name ;
   CalcValue value;

   CalcVar& set(C Str &name, CVAL_TYPE type=CVAL_REAL) {T.name=name; T.value.type=type; return T;}

   CalcVar(                                     ) {value.type=CVAL_REAL;}
   CalcVar(C Str &name, CVAL_TYPE type=CVAL_REAL) {set(name, type);}
};
/******************************************************************************/
extern Char CalcError[]; // contains error on failed Calc()
/******************************************************************************/
// Calculate 'expression', with 'var' array of 'vars' variables
Bool  Calculate  (CalcValue &value, C Str &expression, CalcVar *var=NULL, Int vars=0); // put    result value to 'value' and return if ok
Int   CalculateI (                  C Str &expression, CalcVar *var=NULL, Int vars=0); // return result value as Int
Dbl   CalculateR (                  C Str &expression, CalcVar *var=NULL, Int vars=0); // return result value as Real
VecD2 CalculateV2(                  C Str &expression, CalcVar *var=NULL, Int vars=0); // return result value as Vec2
VecD  CalculateV (                  C Str &expression, CalcVar *var=NULL, Int vars=0); // return result value as Vec
VecD4 CalculateV4(                  C Str &expression, CalcVar *var=NULL, Int vars=0); // return result value as Vec4
/******************************************************************************/
