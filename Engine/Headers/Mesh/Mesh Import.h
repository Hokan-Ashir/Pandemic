/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Import' functions to import data from external file formats.

/******************************************************************************/
struct XMaterial // Material stored in external formats
{
   Bool               cull     , // enable face culling
                  flip_normal_y; // if flip normal map Y channel
   MATERIAL_TECHNIQUE tech     ; // material technique
   Vec4               color    ; // color                 (0,0,0,0) .. (1,1,1,1), default=(1,1,1,1)
   Vec                ambient  , // ambient                 (0,0,0) .. (1,1,1)  , default=(0,0,0)
                      specular ; // specular                (0,0,0) .. (1,1,1)  , default=(0,0,0)
   Flt                sss      , // sub-surface scattering        0 .. 1        , default=0
                      glow     , // glow amount                   0 .. 1        , default=0
                      rough    , // roughness                     0 .. 1        , default=0.5
                      bump     , // bumpiness                     0 .. 0.09     , default=0.03
                      tex_scale, // texture scale                 0 .. Inf      , default=1, this is used mainly for World Editor terrain textures scaling, not supported on Shader Model 2.0
                      det_scale, // detail  scale                 0 .. Inf      , default=4
                      det_power, // detail  power                 0 .. 1        , default=0.3
                     reflection; // reflection                    0 .. 1        , default=0.2
   Str                color_map, // color           texture file name
                      alpha_map, // alpha           texture file name
                       bump_map, // bump            texture file name
                       glow_map, // glow            texture file name
                      light_map, // light           texture file name
                     normal_map, // normal          texture file name
                   specular_map, // specular        texture file name
                 reflection_map, // reflection      texture file name
               detail_color_map, // detail color    texture file name
                detail_bump_map, // detail bump     texture file name
              detail_normal_map, // detail normal   texture file name
            detail_specular_map, // detail specular texture file name
                           name; // material name

   void createFrom  (C Material &src ) ; // create        from 'src'  material
   void copyParamsTo(  Material &mtrl)C; // copy parameters to 'mtrl' material (this does not copy textures)

   XMaterial();
};
/******************************************************************************/
struct XAnimation // Animation stored in external formats
{
   Flt       fps ; // animation frames per second (0 if unknown)
   Str       name; // animation name
   Animation anim; // animation data

   XAnimation() {fps=0;}
};
/******************************************************************************/
// Collada - DAE
Bool ImportDAE(C Str &name, Mesh *mesh, Skeleton *skeleton, XAnimation *animation, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from Collada .dae 'name' file, false on fail

// Autodesk FilmBox - FBX
void SetFbxDllPath(C Str &dll_32, C Str &dll_64); // set custom path to FBX DLL files (including path and file name) for 32-bit and 64-bit dll versions (default="FBX.dll" and "FBX 64.dll"), this function is used only on Windows platform
Bool ImportFBX(C Str &name, Mesh *mesh, Skeleton *skeleton, Memp<XAnimation> animations, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from FBX .fbx 'name' file, false on fail

// Microsoft DirectX - X
Bool ImportX(C Str &name, Mesh *mesh, Skeleton *skeleton, Memp<XAnimation> animations, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from DirectX .x 'name' file, false on fail

// 3D Studio Max Ascii Scene Export - ASE
Bool ImportASE(C Str &name, Mesh *mesh, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from Ascii Scene Export 'name' file, false on fail

// Wavefront - OBJ
Bool ImportOBJ(C Str &name, Mesh    *mesh, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from Wavefront Obj 'name' file, false on fail
Bool ExportOBJ(C Str &name, MeshLod &mesh); // export to Wavefront Obj 'name' file

// 3D Studio - 3DS
Bool Import3DS(C Str &name, Mesh *mesh, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from 3D Studio 'name' file, false on fail

// Blitz3D - B3D
Bool ImportB3D(C Str &name, Mesh *mesh, Skeleton *skeleton, XAnimation *animation, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from Blitz3D 'name' file, false on fail

// Biovision Motion Capture - BVH
Bool ImportBVH(C Str &name, Skeleton *skeleton, XAnimation *animation); // import data from BVH 'name' file, false on fail

// MilkShape 3D - MS3D
Bool ImportMS3D(C Str &name, Mesh *mesh, Skeleton *skeleton, XAnimation *animation, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from MS3D 'name' file, false on fail

// Unreal Engine Mesh - PSK
Bool ImportPSK(C Str &name, Mesh *mesh, Skeleton *skeleton, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from PSK 'name' file, false on fail

// Unreal Engine Animation - PSA
Bool ImportPSA(C Str &name, Skeleton *skeleton, Memp<XAnimation> animations); // import data from PSA 'name' file, false on fail

// VRML97 - WRL
Bool ImportWRL(C Str &name, Mesh *mesh); // import data from Vrml97 wrl 'name' file, false on fail

// Ogre Scene - SCENE
Bool ImportOgre(C Str &name, Mesh *mesh, Skeleton *skeleton, Memp<XAnimation> animations, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data from Ogre 'name' file, false on fail

Bool Import(C Str &name, Mesh *mesh, Skeleton *skeleton, Memp<XAnimation> animations, Memp<XMaterial> materials, Memp<Int> part_material_index); // import data according to file extension, false on fail
/******************************************************************************/
