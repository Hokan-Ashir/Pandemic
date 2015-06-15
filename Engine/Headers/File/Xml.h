/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'TextData' to handle automatic text-base data saving and loading.
   Use  'XmlData' to handle automatic       xml data saving and loading.

/******************************************************************************/
// TEXT
/******************************************************************************/
struct TextParam
{
   Str name , // parameter name
       value; // parameter value

   // set / get
   TextParam& setName(C Str &name=S) {T.name=name; return T;}

   TextParam& setValue(C Str  &value=S) {T.value=         value           ; return T;}
   TextParam& setValue(  Int   value  ) {T.value=         value           ; return T;}
   TextParam& setValue(  Flt   value  ) {T.value=TextReal(value      , -6); return T;}
   TextParam& setValue(C Vec2 &value  ) {T.value=         value.asText(-6); return T;}
   TextParam& setValue(C Vec  &value  ) {T.value=         value.asText(-6); return T;}
   TextParam& setValue(C Vec4 &value  ) {T.value=         value.asText(-6); return T;}

   TextParam& set(C Str &name, C Str  &value=S) {return setName(name).setValue(value);}
   TextParam& set(C Str &name,   Int   value  ) {return setName(name).setValue(value);}
   TextParam& set(C Str &name,   Flt   value  ) {return setName(name).setValue(value);}
   TextParam& set(C Str &name, C Vec2 &value  ) {return setName(name).setValue(value);}
   TextParam& set(C Str &name, C Vec  &value  ) {return setName(name).setValue(value);}
   TextParam& set(C Str &name, C Vec4 &value  ) {return setName(name).setValue(value);}

 C Str&  asText ()C {return           value ;}
   Bool  asBool ()C {return TextBool (value);}
   Int   asInt  ()C {return TextInt  (value);}
   UInt  asUInt ()C {return TextUInt (value);}
   Long  asLong ()C {return TextLong (value);}
   ULong asULong()C {return TextULong(value);}
   Flt   asFlt  ()C {return TextFlt  (value);}
   Dbl   asDbl  ()C {return TextDbl  (value);}
   Vec2  asVec2 ()C {return TextVec2 (value);}
   Vec   asVec  ()C {return TextVec  (value);}
   Vec4  asVec4 ()C {return TextVec4 (value);}
   Color asColor()C {return TextColor(value);}

   TextParam& clear() {name.clear(); value.clear(); return T;}
   TextParam& del  () {name.del  (); value.del  (); return T;}
   
   TextParam() {}
   TextParam(C Str &name, C Str &value=S) {set(name, value);}
};
/******************************************************************************/
STRUCT(TextNode , TextParam)
//{
   Memc<TextNode> nodes;

   // get / set
   TextNode* findNode(C Str &name, Int i=0); // find i-th node which name is equal to 'name', NULL on fail (if not found)
   TextNode&  getNode(C Str &name         ); // get       node which name is equal to 'name', New  on fail (if not found)

   TextNode& setName(C Str &name=S) {super::setName(name); return T;}

   // manage
   TextNode& clear() {super::clear(); nodes.clear(); return T;} // clear
   TextNode& del  () {super::del  (); nodes.del  (); return T;} // delete manually

   TextNode() {}
   TextNode(C XmlNode &xml); // create from 'XmlNode'
};
/******************************************************************************/
struct TextData
{
   Memc<TextNode> nodes;

   // get
   TextNode* findNode(C Str &name, Int i=0); // find i-th node which name is equal to 'name', NULL on fail (if not found)
   TextNode&  getNode(C Str &name         ); // get       node which name is equal to 'name', New  on fail (if not found)

   // manage
   TextData& clear() {nodes.clear(); return T;} // clear
   TextData& del  () {nodes.del  (); return T;} // delete manually

   // io
   Bool save(C Str    &name, ENCODING encoding=UTF_8, INDENT indent=INDENT_TABS, const_mem_addr Secure *secure=NULL)C; // save to file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   void save(FileText &f                                                                                           )C; // save to file, 'f' file must be already opened for writing

   Bool load(C Str    &name, const_mem_addr Secure *secure=NULL); // load from file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool load(C UID    &id  , const_mem_addr Secure *secure=NULL); // load from file, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool load(FileText &f                                       ); // load from file, false on fail, 'f' file must be already opened for reading

   Bool loadJSON(C Str    &name, const_mem_addr Secure *secure=NULL); // load from file in JSON format, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool loadJSON(FileText &f                                       ); // load from file in JSON format, false on fail, 'f' file must be already opened for reading

   Bool loadYAML(C Str    &name, const_mem_addr Secure *secure=NULL); // load from file in YAML format, false on fail, 'secure' must point to object in constant memory address (only pointer is stored through which the object can be later accessed)
   Bool loadYAML(FileText &f                                       ); // load from file in YAML format, false on fail, 'f' file must be already opened for reading

   TextData() {}
   TextData(C XmlData &xml); // create from 'XmlData'
};
/******************************************************************************/
// XML
/******************************************************************************/
typedef TextParam XmlParam; // Xml Node Parameter
/******************************************************************************/
struct XmlNode // Xml Node
{
   Str            name  ; // node name
   Memc<XmlParam> params; // node parameters
   Memc<Str     > data  ; // node data
   Memc<XmlNode > nodes ; // node children

   XmlNode& setName(C Str &name) {T.name=name; return T;}

   // get
   XmlParam* findParam(C Str &name, Int i=0); // find i-th parameter which name is equal to 'name', NULL on fail (if not found)
   XmlParam&  getParam(C Str &name         ); // get       parameter which name is equal to 'name', New  on fail (if not found)
   XmlNode * findNode (C Str &name, Int i=0); // find i-th node      which name is equal to 'name', NULL on fail (if not found)
   XmlNode &  getNode (C Str &name         ); // get       node      which name is equal to 'name', New  on fail (if not found)

   // manage
   XmlNode& clear() {name.clear(); params.clear(); data.clear(); nodes.clear(); return T;} // clear
   XmlNode& del  () {name.del  (); params.del  (); data.del  (); nodes.del  (); return T;} // delete manually

   XmlNode() {}
   XmlNode(C TextNode &text); // create from 'TextNode'
};
/******************************************************************************/
struct XmlData // Xml Data
{
   Memc<XmlNode> nodes;

   // get
   XmlNode* findNode(C Str &name, Int i=0); // find i-th node which name is equal to 'name', NULL on fail (if not found)
   XmlNode&  getNode(C Str &name         ); // get       node which name is equal to 'name', New  on fail (if not found)

   // manage
   XmlData& clear() {nodes.clear(); return T;} // clear
   XmlData& del  () {nodes.del  (); return T;} // delete manually

   // io
   Bool save(C Str    &name, Bool params_in_separate_lines=false, ENCODING encoding=UTF_8)C; // save to file, false on fail
   void save(FileText &f   , Bool params_in_separate_lines=false                         )C; // save to file, 'f' file must be already opened for writing

   Bool load(C Str    &name); // load from file, false on fail
   Bool load(C UID    &id  ); // load from file, false on fail
   Bool load(FileText &f   ); // load from file, false on fail, 'f' file must be already opened for reading

   XmlData() {}
   XmlData(C TextData &text); // create from 'TextData'
};
/******************************************************************************/
TextNode* FindNode(Memp<TextNode> nodes, C Str &name, Int i=0); // find i-th node which name is equal to 'name', NULL on fail (if not found)
TextNode&  GetNode(Memp<TextNode> nodes, C Str &name         ); // get       node which name is equal to 'name', New  on fail (if not found)

XmlNode* FindNode(Memp<XmlNode> nodes, C Str &name, Int i=0); // find i-th node which name is equal to 'name', NULL on fail (if not found)
XmlNode&  GetNode(Memp<XmlNode> nodes, C Str &name         ); // get       node which name is equal to 'name', New  on fail (if not found)
/******************************************************************************/
