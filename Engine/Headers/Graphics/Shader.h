/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct ShaderImage // Shader Image
{
 C Image* get(                   )C {return   _image  ;}
   void   set(C Image      *image)  {T._image= image  ;}
   void   set(C Image      &image)  {T._image=&image  ;}
   void   set(C ImageRTPtr &image)  {T._image= image();}
 //void   set(C ImagePtr   &image)  {T._image= image();} this is not safe, as 'ShaderImage' does not store 'ImagePtr' for performance reasons

   ShaderImage() {_image=NULL; _sampler=NULL;}

private:
   Str8   _name;
 C Image *_image;
   Ptr    _sampler;
};
/******************************************************************************/
struct ShaderParam // Shader Parameter
{
            void set(  Bool     b               ); // set boolean  value
            void set(  Int      i               ); // set integer  value
            void set(  Flt      f               ); // set float    value
            void set(C Vec2    &v               ); // set vector2D value
            void set(C Vec     &v               ); // set vector3D value
            void set(C Vec4    &v               ); // set vector4D value
            void set(C VecI2   &v               ); // set vector2D value
            void set(C VecI    &v               ); // set vector3D value
            void set(C VecI4   &v               ); // set vector4D value
            void set(C Color   &color           ); // set vector4D value
            void set(C Rect    &rect            ); // set vector4D value
            void set(C Matrix3 &matrix          ); // set matrix3  value
            void set(C Matrix  &matrix          ); // set matrix   value
            void set(C Matrix4 &matrix          ); // set matrix4  value
            void set(C Vec     *v     , Int elms); // set vector3D array
            void set(C Vec4    *v     , Int elms); // set vector4D array
            void set(C Matrix  *matrix, Int elms); // set matrix   array
            void set(  CPtr     data  , Int size); // set memory
   T1(TYPE) void set(C TYPE    &data            ) {set((CPtr)&data, SIZE(data));}
};
/******************************************************************************/
struct ShaderParamChange // Shader Parameter Change
{
   ShaderParam *param  ; // parameter to change
   Vec4         value  ; // value     to change to
   Bool         restore; // if the parameter value should be restored afterwards

   ShaderParamChange& set(  Bool  b) {value.x   =b; return T;}
   ShaderParamChange& set(  Int   i) {value.x   =i; return T;}
   ShaderParamChange& set(  Flt   f) {value.x   =f; return T;}
   ShaderParamChange& set(C Vec2 &v) {value.v2()=v; return T;}
   ShaderParamChange& set(C Vec  &v) {value.v3()=v; return T;}
   ShaderParamChange& set(C Vec4 &v) {value     =v; return T;}

   ShaderParamChange& set(ShaderParam *param, Bool restore=false) {T.param=param; T.restore=restore; return T;}

   ShaderParamChange() {param=NULL; value.zero(); restore=false;}
};
/******************************************************************************/
struct ShaderShader
{
};
struct ShaderTech
{
   void draw(C Image      *image=NULL, C Rect *rect=NULL        );                             // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Col' shader image, 'rect'=screen rectangle for the effect (set NULL for full viewport)
   void draw(C Image      &image     , C Rect *rect=NULL        ) {draw(&image  , rect     );} // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Col' shader image, 'rect'=screen rectangle for the effect (set NULL for full viewport)
   void draw(C ImageRTPtr &image     , C Rect *rect=NULL        ) {draw( image(), rect     );} // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Col' shader image, 'rect'=screen rectangle for the effect (set NULL for full viewport)
   void draw(C Image      *image     , C Rect *rect, C Rect &tex);                             // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Col' shader image, 'rect'=screen rectangle for the effect (set NULL for full viewport), 'tex'=source image texture coordinates
   void draw(C Image      &image     , C Rect *rect, C Rect &tex) {draw(&image  , rect, tex);} // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Col' shader image, 'rect'=screen rectangle for the effect (set NULL for full viewport), 'tex'=source image texture coordinates
   void draw(C ImageRTPtr &image     , C Rect *rect, C Rect &tex) {draw( image(), rect, tex);} // apply custom 2D effect on the screen, 'image'=image to automatically set as 'Col' shader image, 'rect'=screen rectangle for the effect (set NULL for full viewport), 'tex'=source image texture coordinates
};
/******************************************************************************/
struct Shader // Shader
{
   // get
   ShaderTech* firstTech(            ); //  get first technique, NULL on fail
   ShaderTech*  findTech(C Str8 &name); // find       technique, NULL on fail
   ShaderTech*   getTech(C Str8 &name); //  get       technique, Exit on fail

   // manage
   void del();

   // io
   Bool load(C Str &name); // load, false on fail

   Shader();
  ~Shader() {del();}

private:
   Mems<ShaderShader> _vs, _hs, _ds, _ps;
   Mems<ShaderTech  > _techs;
   NO_COPY_CONSTRUCTOR(Shader);
};
/******************************************************************************/
extern Cache<Shader> Shaders; // Shader Cache
/******************************************************************************/
struct ShaderMacro // macro used for shader compilation
{
   Str8 name      ,
        definition;

   void set(C Str8 &name, C Str8 &definition) {T.name=name; T.definition=definition;}
};
/******************************************************************************/
// shader image
ShaderImage* FindShaderImage(CChar8 *name); // find shader image, NULL on fail (shader image can be returned only after loading a shader which contains the image)
ShaderImage*  GetShaderImage(CChar8 *name); // find shader image, Exit on fail (shader image can be returned only after loading a shader which contains the image)

// shader parameter
ShaderParam* FindShaderParam(CChar8 *name); // find shader parameter, NULL on fail (shader parameter can be returned only after loading a shader which contains the parameter)
ShaderParam*  GetShaderParam(CChar8 *name); // find shader parameter, Exit on fail (shader parameter can be returned only after loading a shader which contains the parameter)

         inline void SPSet(CChar8 *name,   Bool     b               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(b           );} // set boolean  value
         inline void SPSet(CChar8 *name,   Int      i               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(i           );} // set integer  value
         inline void SPSet(CChar8 *name,   Flt      f               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(f           );} // set float    value
         inline void SPSet(CChar8 *name, C Vec2    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector2D value
         inline void SPSet(CChar8 *name, C Vec     &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector3D value
         inline void SPSet(CChar8 *name, C Vec4    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector4D value
         inline void SPSet(CChar8 *name, C VecI2   &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector2D value
         inline void SPSet(CChar8 *name, C VecI    &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector3D value
         inline void SPSet(CChar8 *name, C VecI4   &v               ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v           );} // set vector4D value
         inline void SPSet(CChar8 *name, C Color   &color           ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(color       );} // set vector4D value
         inline void SPSet(CChar8 *name, C Rect    &rect            ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(rect        );} // set vector4D value
         inline void SPSet(CChar8 *name, C Matrix3 &matrix          ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix      );} // set matrix   value
         inline void SPSet(CChar8 *name, C Matrix  &matrix          ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix      );} // set matrix   value
         inline void SPSet(CChar8 *name, C Matrix4 &matrix          ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix      );} // set matrix4  value
         inline void SPSet(CChar8 *name, C Vec     *v     , Int elms) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v     , elms);} // set vector3D array
         inline void SPSet(CChar8 *name, C Vec4    *v     , Int elms) {if(ShaderParam *sp=FindShaderParam(name))sp->set(v     , elms);} // set vector4D array
         inline void SPSet(CChar8 *name, C Matrix  *matrix, Int elms) {if(ShaderParam *sp=FindShaderParam(name))sp->set(matrix, elms);} // set matrix   array
         inline void SPSet(CChar8 *name,   CPtr     data  , Int size) {if(ShaderParam *sp=FindShaderParam(name))sp->set(data  , size);} // set memory
T1(TYPE) inline void SPSet(CChar8 *name, C TYPE    &data            ) {if(ShaderParam *sp=FindShaderParam(name))sp->set(data        );} // set memory

// shader
ShaderTech* GetDefaultShader(RENDER_MODE mode, Material *material[4], UInt mesh_base_flag, Int lod_index, Bool allow_tesselation); // this function returns a default shader for a mesh with given parameters, 'mesh_base_flag'=MESH_BASE_FLAG, 'lod_index'=index of the lod in the mesh (required in order to set appropriate quality of the shader)

// compile
Bool ShaderCompileTry(Str src, Str dest, SHADER_MODEL model, C Memp<ShaderMacro> &macros=NULL, Str *messages=NULL); // compile shader from 'src' file to 'dest' using additional 'macros', false on fail, 'messages'=optional parameter which will receive any messages that occured during compilation
void ShaderCompile   (Str src, Str dest, SHADER_MODEL model, C Memp<ShaderMacro> &macros=NULL                    ); // compile shader from 'src' file to 'dest' using additional 'macros', Exit  on fail
/******************************************************************************/
