/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Material' to specify custom mesh material parameters.
   'Materials' are usually created in the 'Material Editor' tool, and used by 'Meshes'.

/******************************************************************************/
enum MATERIAL_TECHNIQUE // Material Techniques
{
   MTECH_DEFAULT               , // standard rendering of solid (opaque) materials
   MTECH_ALPHA_TEST            , // indicates that textures alpha channel will be used as models transparency (this is slightly slower than Default as alpha testing may disable some hardware-level optimizations)
   MTECH_FUR                   , // mesh will be rendered with fur effect, the mesh will be wrapped with additional fur imitating textures, in this technique "detail scale" specifies fur intensity, "detail power" specifies fur length, supported only in Deferred Renderer
   MTECH_GRASS                 , // mesh vertexes will bend on the wind like grass, bending intensity is determined by mesh vertex source Y position, which should be in the range from 0 to 1
   MTECH_LEAF                  , // mesh vertexes will bend on the wind like tree leafs, to use this technique mesh must also contain leaf attachment positions, which can be generated in the Model Editor tool through menu options
   MTECH_BLEND                 , // mesh will be smoothly blended on the screen using alpha values, mesh will not be affected by lighting or shadowing
   MTECH_BLEND_LIGHT           , // works like Blend technique except that mesh will be affected by lighting or shadowing, however only the most significant directional light will be used (all other lights are ignored), due to additional lighting calculations this is slower than Blend technique
   MTECH_BLEND_LIGHT_GRASS     , // combination of Blend Light and Grass techniques
   MTECH_BLEND_LIGHT_LEAF      , // combination of Blend Light and Leaf  techniques
   MTECH_TEST_BLEND_LIGHT      , // works like MTECH_BLEND_LIGHT       with additional Alpha-Testing and Depth-Writing which enables correct Depth-Sorting
   MTECH_TEST_BLEND_LIGHT_GRASS, // works like MTECH_BLEND_LIGHT_GRASS with additional Alpha-Testing and Depth-Writing which enables correct Depth-Sorting
   MTECH_TEST_BLEND_LIGHT_LEAF , // works like MTECH_BLEND_LIGHT_LEAF  with additional Alpha-Testing and Depth-Writing which enables correct Depth-Sorting
};
/******************************************************************************/
struct MaterialParams // Material Parameters
{
   Vec4 color    ; // color                 (0,0,0,0) .. (1,1,1,1), default=(1,1,1,1)
   Vec  ambient  ; // ambient                 (0,0,0) .. (1,1,1)  , default=(0,0,0)
   Flt  specular , // specular                      0 .. 1        , default=0
        sss      , // sub-surface scattering        0 .. 1        , default=0
        glow     , // glow amount                   0 .. 1        , default=0
        rough    , // roughness                     0 .. 1        , default=0.5
        bump     , // bumpiness                     0 .. 0.09     , default=0.03
        tex_scale, // texture scale                 0 .. Inf      , default=1, this is used mainly for World Editor terrain textures scaling, not supported on Shader Model 2.0
        det_scale, // detail  scale                 0 .. Inf      , default=4
        det_power, // detail  power                 0 .. 1        , default=0.3
        reflect  ; // reflection                    0 .. 1        , default=0.2
};
STRUCT(Material , MaterialParams) // Mesh Rendering Material - contains render parameters and textures
//{
   Bool               cull            ; // if face culling enabled       , default=true
   MATERIAL_TECHNIQUE technique       ; // material   technique          , default=MTECH_DEFAULT
   ImagePtr           base_0          , // base       texture #0         , default=NULL, this texture contains data packed in following channel order: RGB, Alpha/Bump
                      base_1          , // base       texture #1         , default=NULL, this texture contains data packed in following channel order: Specular, NormalY, Alpha/Glow, NormalX
                          detail_map  , // detail     texture            , default=NULL
                           macro_map  , // macro      texture            , default=NULL
                      reflection_map  , // reflection texture            , default=NULL
                           light_map  ; // light map  texture            , default=NULL
   Int                user_shader     , // user shader enum element index, default=0
                      user_type       ; // user type   enum element index, default=0
   Str8               user_shader_name, // user shader enum element name , default=""
                      user_type_name  ; // user type   enum element name , default=""

   // operations
   Material& validate        (); // this needs to be called after manually changing the parameters/textures
   Material& reset           (); // reset to default values (automatically calls 'validate')
   Bool      convertAlphaTest(Bool blend); // if material 'technique' uses alpha testing then it will be converted to another "alpha test" technique with blending enabled/disabled depending on 'blend' value, you can use this method in the game to adjust quality of the material (blended techniques are more attractive but also slower to display, you can disable blending for slow devices), automatically calls 'validate', returns true if any change was made to this material, see also 'APP_AUTO_MATERIAL_CONVERT_ALPHA_TEST'

   // io
   Bool save(C Str &name)C; // save, false on fail
   Bool load(C Str &name) ; // load, false on fail

   void save(File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   Material();
  ~Material();

private:
   Bool  _coverage, _depth_write;
   Color _alpha_factor;
   struct Multi
   {
      Vec4 color, normal_mul, normal_add;
      Flt  tex_scale, det_scale, det_mul, det_add, bump, macro;
   }_multi;
   struct Instance
   {
      Int num, solid, ambient, grass, shadow;
      Instance() {num=0; solid=ambient=grass=shadow=-1;}
   }_instance;
public:
   void _adjustParams(UInt old_base_tex, UInt new_base_tex);
};
/******************************************************************************/
DECLARE_CACHE(Material, Materials, MaterialPtr); // 'Materials' cache storing 'Material' objects which can be accessed by 'MaterialPtr' pointer
extern Enum  *MaterialUserShader               , //  Material's User Shader enum, default=Enums.get("Enum/material_user_shader.enum")
             *MaterialUserType                 ; //  Material's User Type   enum, default=Enums.get("Enum/material_user_type.enum"  )
/******************************************************************************/
enum BASE_TEX
{
   BT_COLOR   =1<<0, // base texture contains color
   BT_ALPHA   =1<<1, // base texture contains alpha
   BT_BUMP    =1<<2, // base texture contains bump
   BT_NORMAL  =1<<3, // base texture contains normal
   BT_SPECULAR=1<<4, // base texture contains specular
   BT_GLOW    =1<<5, // base texture contains glow
};
UInt CreateBaseTextures (Image &base_0, Image &base_1, C Image &col, C Image &alpha, C Image &bump, C Image &normal, C Image &specular, C Image &glow, Bool resize_to_pow2=true, Bool flip_normal_y=false, FILTER_TYPE filter=FILTER_BEST); // create 'base_0' and 'base_1' base material textures from given images, textures will be created as IMAGE_B8G8R8A8 IMAGE_SOFT, 'flip_normal_y'=if flip normal map Y channel, returns bit combination of BASE_TEX enums of what the base textures have
void CreateDetailTexture(Image &detail,                C Image &col,                 C Image &bump, C Image &normal,                                   Bool resize_to_pow2=true, Bool flip_normal_y=false, FILTER_TYPE filter=FILTER_BEST); // create 'detail'                   material texture  from given images, texture  will be created as IMAGE_B8G8R8A8 IMAGE_SOFT, 'flip_normal_y'=if flip normal map Y channel
void CreateBumpFromColor(Image &bump  ,                C Image &col                                                                                                                                                                      ); // create 'bump'                              texture  from color image , texture  will be created as IMAGE_L8       IMAGE_SOFT
Bool  MergeBaseTextures (Image &base_0,                C Material &material, Int image_type=-1, Int max_image_size=-1, C Vec *light_dir=&NoTemp(!Vec(1, -1, 1)), Flt light_power=0.77f, Flt ambient=0.57f, FILTER_TYPE filter=FILTER_BEST); // create 'base_0'   simplified base material texture out of existing 'material' textures, this works by merging the two base textures into one (thus removing bump, normal, specular and glow maps, and keeping only color and alpha maps), 'image_type'=new desired IMAGE_TYPE for texture (-1=don't modify and use existing type), 'max_image_size'=limit maximum texture resolution (value of <=0 does not apply any limit), 'light_dir'=specify direction of the light for baking the normal map onto the color map (use NULL for no baking), 'light_power'=intensity of light (0..1) used during baking the normal map on the color map (ignored if 'light_dir' is set to NULL), 'ambient'=amount of ambient light (0..1) used during baking the normal map on the color map (ignored if 'light_dir' is set to NULL), returns true if base textures were merged and the new image was created, returns false if the material does not use two base textures (in such case the 'base_0' is left unmodified)
/******************************************************************************/
