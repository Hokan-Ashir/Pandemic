/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
#define MAX_HM_RES (128+1) // Maximum allowed Heightmap Resolution for the 'Heightmap' class
/******************************************************************************/
struct Heightmap
{
   // get / set
   Bool is        ()C; // if  has any data
   Int  resolution()C; // get heightmap resolution, this is the width and height of heightmap images
   Bool hasColor  ()C; // if  heightmap currently uses color map
   UInt memUsage  ()C; // get approximate memory size usage of the heightmap

   Int          materials(     )C {return _materials.elms();} // get number of materials used by the heightmap
 C MaterialPtr& material (Int i)C {return _materials[i]    ;} // get i-th      material  used by the heightmap

   Int getMaterialIndex(C MaterialPtr &material) {return _materials.getMaterialIndex(material);} // get index of desired 'material' in the material palette, if 'material' is not listed in the palette it will be added, up to 255 materials can be stored, 0 index is always reserved for NULL material, -1 on fail

   Flt  height (Int x, Int y            )C; // get              height at x, y image coordinates, 0 on fail (if coordinates out of range)
   Flt  heightI(Flt x, Flt y            )C; // get interpolated height at x, y image coordinates, 0 on fail (if coordinates out of range)
   void height (Int x, Int y, Flt height) ; // set              height at x, y image coordinates to 'height'

   Color color(Int x, Int y                )C; // get color at x, y image coordinates, WHITE on fail (if coordinates out of range)
   void  color(Int x, Int y, C Color &color) ; // set color at x, y image coordinates to 'color'

   Vec  colorF(Int x, Int y              )C; // get color at x, y image coordinates, Vec(1,1,1) on fail (if coordinates out of range)
   void colorF(Int x, Int y, C Vec &color) ; // set color at x, y image coordinates to 'color'

   Bool getMaterialIndex(Int x, Int y,    Int         &m0, Flt &i0,    Int         &m1, Flt &i1,    Int         &m2, Flt &i2)C; // get material at x, y image coordinates to 'm0 m1 m2' material indexes of 'i0 i1 i2' intensities (sum of intensities will be equal to 1), false on fail (if coordinates are out of range), 'm0 m1 m2' represent the indexes of materials which can be accessed by 'material' function
   Bool getMaterial     (Int x, Int y,    MaterialPtr &m0, Flt &i0,    MaterialPtr &m1, Flt &i1,    MaterialPtr &m2, Flt &i2)C; // get material at x, y image coordinates to 'm0 m1 m2' materials        of 'i0 i1 i2' intensities (sum of intensities will be equal to 1), false on fail (if coordinates are out of range)
   void setMaterialIndex(Int x, Int y,    Int          m0, Flt  i0,    Int          m1, Flt  i1,    Int          m2, Flt  i2) ; // set material at x, y image coordinates to 'm0 m1 m2' material indexes of 'i0 i1 i2' intensities (sum of intensities will be equal to 1),                                                  'm0 m1 m2' represent the indexes of materials which can be accessed by 'material' and 'getMaterialIndex' functions
   void setMaterial     (Int x, Int y,  C MaterialPtr &m0, Flt  i0,  C MaterialPtr &m1, Flt  i1,  C MaterialPtr &m2, Flt  i2) ; // set material at x, y image coordinates to 'm0 m1 m2' materials        of 'i0 i1 i2' intensities (intensities should be in range 0..1)
   void addMaterial     (Int x, Int y,  C MaterialPtr &m , Flt  i                                                           ) ; // add material at x, y image coordinates

 C Image& heightImage()C {return _height;} // get heightmap height image

   // manage
   Heightmap& del   (); // delete manually
   Heightmap& create(Int resolution, Flt height, C MaterialPtr &material, Bool align_height_to_neighbors, C Heightmap *l, C Heightmap *r, C Heightmap *b, C Heightmap *f, C Heightmap *lb, C Heightmap *lf, C Heightmap *rb, C Heightmap *rf); // create heightmap with 'resolution', final resolution of the heightmap may be different than 'resolution', and can be obtained using 'resolution' method, heightmap pointers are optional and represent heightmap neighbors (l-left, r-right, b-back, f-forward), all given heightmaps must be of the same resolution as 'resolution'
   Heightmap& create(C Heightmap &src); // create from 'src' heightmap

   // operations
   void resize(Int resolution); // resize heightmap to a custom resolution, final resolution of the heightmap may be different than 'resolution', and can be obtained using 'resolution' method

   void cleanMaterials(); // cleanup heightmap by removing unused materials

   void build(Mesh &dest_mesh, Int quality, Flt tex_scale, Bool ambient_occlusion, C Heightmap *l, C Heightmap *r, C Heightmap *b, C Heightmap *f, C Heightmap *lb, C Heightmap *lf, C Heightmap *rb, C Heightmap *rf, Bool build_null_mtrl=false); // build heightmap into 'dest_mesh', 'quality'=0-full, 1-half, 2-quarter, 'tex_scale'=texture map coordinates scale, 'ambient_occlusion'=if apply ambient occlusion effect to vertex colors, heightmap pointers are optional and represent heightmap neighbors (l-left, r-right, b-back, f-forward), all given heightmaps must be of the same resolution as this heightmap, 'build_null_mtrl'=if build heightmap parts which have the NULL material

   // io
   void save(File &f, CChar *path=NULL)C; // save to   'f' file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load from 'f' file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

private:
   struct MtrlCombo // Material Combination
   {
      VecB4 mtrl_index;

      // mesh building
      Bool  used        ;
      Int   vtxs        ,
            tris        ,
            quads       ,
            ofs_pos     ,
            ofs_nrm     ,
            ofs_tan     ,
            ofs_color   ,
            ofs_tex0    ,
            ofs_material;
      Byte *vtx         , 
           *ind         ;

      MtrlCombo() {Zero(T);}

      NO_COPY_CONSTRUCTOR(MtrlCombo);
   };

   Image           _height     ,
                   _color      ,
                   _mtrl_index ,
                   _mtrl_blend ;
   MaterialPalette _materials  ;
   Memc<MtrlCombo> _mtrl_combos;
};
/******************************************************************************/
