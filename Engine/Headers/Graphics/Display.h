/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Display' to handle all display related functions.
   Including:
      -setting rendering options
      -handling basic 2D drawing

/******************************************************************************/
enum ASPECT_MODE // Aspect Ratio Mode, controls setting the sizes of screen coordinates - D.w and D.h
{
   ASPECT_Y      , // sets D.h to 1.0, D.w will be proportional to D.h depending on the display aspect and selected resolution
   ASPECT_X      , // sets D.w to 1.0, D.h will be proportional to D.w depending on the display aspect and selected resolution
   ASPECT_SMALLER, // this mode is useful for Mobile devices which can be rotated and changed aspect will not affect the display scale, 1.0 will be set to D.w and D.h will be set proportionally (if width is smaller than height) and 1.0 will be set to D.h and D.w will be set proportionally (if height is smaller than width)
   ASPECT_NUM    , // number of aspect ratio modes
};
enum BUMP_MODE // Bump Mapping Mode
{
   BUMP_FLAT    , // flat
   BUMP_NORMAL  , // normal
   BUMP_PARALLAX, // parallax
   BUMP_RELIEF  , // relief
   BUMP_NUM     , // number of bump mapping modes
};
enum AMBIENT_MODE // Ambient Occlusion Mode
{
   AMBIENT_FLAT , // flat
   AMBIENT_LOW  , // low    quality
   AMBIENT_MED  , // medium quality
   AMBIENT_HIGH , // high   quality
   AMBIENT_ULTRA, // ultra  quality
   AMBIENT_NUM  , // number of ambient modes
};
enum SHADOW_MODE // Shadowing Mode
{
   SHADOW_NONE   , // none
   SHADOW_MAP    , // shadow mapping
   SHADOW_STENCIL, // stencil shadows
   SHADOW_NUM    , // number of shadowing modes
};
enum MOTION_MODE // Motion Blur Mode
{
   MOTION_NONE, // none
   MOTION_LOW , // scene is blurred according to camera velocities only, objects velocities are not taken into account
   MOTION_HIGH, // scene is blurred according to camera and object velocities, available only in RT_DEFERRED renderer
   MOTION_NUM , // number of motion blur modes
};
enum DOF_MODE // Depth of Field Mode
{
   DOF_NONE, // none
   DOF_ON  , // on
   DOF_HIGH, // high
   DOF_NUM , // number of depth of field modes
};
enum EDGE_DETECT_MODE // Edge Detect Mode
{
   EDGE_DETECT_NONE, // disabled
   EDGE_DETECT_THIN, // thin         edges
   EDGE_DETECT_FAT , // fat smoothed edges (slower)
   EDGE_DETECT_NUM , // number of edge detect modes
};
enum EDGE_SOFTEN_MODE // Edge Softening Mode
{
   EDGE_SOFTEN_NONE, // disabled
   EDGE_SOFTEN_FXAA, //     Fast Approximate   Anti Aliasing
   EDGE_SOFTEN_MLAA, //          Morphological Anti Aliasing
   EDGE_SOFTEN_SMAA, // Subpixel Morphological Anti Aliasing
   EDGE_SOFTEN_NUM , // number of edge softening modes
};
enum TEXTURE_USAGE // Information about using additional texture maps in material
{
   TEX_USE_DISABLE, // map is always disabled
   TEX_USE_SINGLE , // map is enabled for single materials only
   TEX_USE_MULTI  , // map is enabled for single materials and multiple materials which are blended together
   TEX_USE_NUM    , // number of texture maps usage modes
};
enum FOV_MODE // Field of View mode, determines calculating actual fov values
{
   FOV_Y , // vertical   fov will be taken from given value, horizontal fov will be calculated proportionally 
   FOV_X , // horizontal fov will be taken from given value, vertical   fov will be calculated proportionally
   FOV_XY, // both horizontal and vertical fov's will be taken from given value
};
enum SHADER_MODEL
{
   SM_UNKNOWN, // unknown
   SM_GL     , //           (OpenGL      )
   SM_2      , // Model 2.0 (DirectX  9  )
   SM_3      , // Model 3.0 (DirectX  9  )
   SM_4      , // Model 4.0 (DirectX 10  )
   SM_4_1    , // Model 4.1 (DirectX 10.1)
   SM_5      , // Model 5.0 (DirectX 11  )
};
/******************************************************************************/
struct Display : DisplayState, DisplayDraw // Display Control
{
   Bool (*lost )(), // pointer to custom function (may be NULL) called when display is lost , it must return true on success and false on fail
        (*reset)(); // pointer to custom function (may be NULL) called when display is reset, it must return true on success and false on fail

   void (*screen_changed)(Flt old_width, Flt old_height); // pointer to custom function (may be NULL) called when screen proportions have changed

   Flt (*shadow_step)(Int i, Int num); // pointer to custom function (may be NULL) which allows to manually specify the fraction range of the i-th out of 'num' shadow map splits

   void (*set_shader)(); // pointer to custom function (may be NULL) called when Mesh shaders need to be updated, when changing some display options during application runtime, meshes require to have their shaders updated, Meshes created by using Cache or those created by Game::World are processed automatically, however manually created meshes need to be processed manually, to do this - create a global function which calls 'Mesh::setShader()' on all manually created meshes and then in 'InitPre' function set 'D.set_shader' to point to that function

   void setGetShaderFunc(ShaderTech* (*get_shader)(RENDER_MODE mode, Material *material[4], UInt mesh_base_flag, Int lod_index, Bool allow_tesselation)); // set pointer to custom function (may be NULL) called when Mesh shaders need to be loaded , this function allows to override the default shaders usage, and specify your own custom versions, inside the function basing on the mesh attributes (materials, mesh flags) you can return your own custom shader for a specified rendering mode, NULL for no shader, or just call and return the result of 'GetDefaultShader' which will return the default shader for given parameters, 'mesh_base_flag'=MESH_BASE_FLAG, 'lod_index'=index of the lod in the mesh (according to this information you can set lower quality shaders for the the lods)

   // get
   Flt          w              ()C {return _w             ;} // get Application Screen     Width  (in screen coordinates, usually something near 1.3, depends on selected resolution and aspect mode)
   Flt          h              ()C {return _h             ;} // get Application Screen     Height (in screen coordinates, usually something near 1.0, depends on selected resolution and aspect mode)
   Int          resW           ()C {return _res.x         ;} // get Application Resolution Width  (in pixels)
   Int          resH           ()C {return _res.y         ;} // get Application Resolution Height (in pixels)
   Int          renderW        ()C {return _dense.x       ;} // get Application Resolution Width  (in pixels) affected by 'density'
   Int          renderH        ()C {return _dense.y       ;} // get Application Resolution Height (in pixels) affected by 'density'
   Int          screenW        ()C;                          // get Display     Screen     Width  (in pixels) at the current moment
   Int          screenH        ()C;                          // get Display     Screen     Height (in pixels) at the current moment
   Int          freq           ()C {return _freq_got      ;} // get Display     Screen     Frequency (refresh rate)
   SHADER_MODEL shaderModel    ()C {return _shader_model  ;} // get available Shader Model
   Str8         shaderModelName()C;                          // get available Shader Model in text format
   Str8         apiName        ()C;                          // get Rendering API          in text format
   Int          maxTexFilter   ()C {return _max_tex_filter;} // get maximum available Anisotropic Filtering
   Int          maxTexSize     ()C {return _max_tex_size  ;} // get maximum available Texture     Size
 C Mems<VecI2>& modes          ()C {return _modes         ;} // get fullscreen display modes, where x=width, y=height (in pixels)
 C Str8&        deviceName     ()C {return _device_name   ;} // get GPU device name
   Bool         canDraw        ()C {return _can_draw      ;} // if  drawing graphics is available (this can be false when APP_ALLOW_NO_GPU was enabled and GPU was not found)
   Bool         smallSize      ()C;                          // if  display device is of a small size (phone size)
   Flt          browserZoom    ()C;                          // get current browser zoom level (1.0=100%, 2.0=200%, etc), this is valid only for the WEB platform (others return 1.0)

   // settings
   Display& mode  (Int w=-1, Int h=-1, Int full=-1  );                // set    Display Resolution  Mode, -1=keep original value, if the method fails then previous mode is restored, if previous mode can't be restored then Exit is called
   Display& toggle(           Bool window_size=false);                // toggle Fullscreen/Windowed Mode, 'window_size'=if when switching to fullscreen want to set resolution from current window size instead of desktop size
   Display& full  (Bool full, Bool window_size=false);                // set    Fullscreen Mode         , 'window_size'=if when switching to fullscreen want to set resolution from current window size instead of desktop size
   Bool     full  (                                 ) {return _full;} // if in  Fullscreen Mode (true/false, default=false)

   Display& density         (Flt              density     );   Flt              density        ()C;                          // get/set Rendering Pixel Density             (0..2                               , default=               1                             ), density affects the number of pixels used during rendering, density=2 makes the rendering use 2x bigger render targets (super sampling) but slower performance, density=0.5 makes the rendering use 2x smaller render targets making the result more blurry but with faster performance, the change is NOT instant, avoid calling real-time
   Display& densityFilter   (Bool             cubic       );   Bool             densityFilter  ()C {return _density_filter;} // get/set Density Cubic Filtering             (true/false                         , default=            true (false           for Mobile)), density filter affects filtering used when up-scaling the image, true=cubic filtering is used, false=linear filtering is used, the change is instant, you can call it real-time
   Display& samples         (Byte             samples     );   Byte             samples        ()C {return _samples       ;} // set/get Sample Count for Multi Sampling AA  (1..16                              , default=               1                             ), multi-sampling for RT_DEFERRED renderer can be enabled only for ShaderModel>=4.1, enabling multi-sampling for ShaderModel<=4.0 disables all depth-based effects, the change is NOT instant, avoid calling real-time
   Display& scale           (Flt              scale       );   Flt              scale          ()C {return _scale         ;} // get/set Draw Scale                          (0..Inf                             , default=               1                             ), changing display scale affects display screen sizes D.w and D.h, the change is NOT instant, avoid calling real-time
   Display& aspectMode      (ASPECT_MODE      mode        );   ASPECT_MODE      aspectMode     ()C {return _aspect_mode   ;} // set/get Aspect Mode                         (ASPECT_MODE                        , default=        ASPECT_Y (ASPECT_SMALLER  for Mobile))
   Display& aspectRatio     (Flt              aspect_ratio);   Flt              aspectRatio    ()C {return _aspect_ratio  ;} // set/get Display Aspect Ratio                (0=autodetect, 4/3, 5/4, 16/9, 16/10, default=               0                             )
   Display& bumpMode        (BUMP_MODE        mode        );   BUMP_MODE        bumpMode       ()C {return _bump_mode     ;} // set/get Bump Mapping Mode                   (BUMP_MODE                          , default=   BUMP_PARALLAX (BUMP_FLAT       for Mobile)), using this method during application runtime requires setting 'D.set_shader' (please check comments on 'D.set_shader' for more info), the change is NOT instant, avoid calling real-time
   Display& gamma           (Flt              gamma       );   Flt              gamma          ()C {return _gamma         ;} // set/get Gamma value                         (-Inf..Inf                          , default=               0                             ), using gamma modifies hardware color processing and does not reduce rendering performance
   Display& highPrecColRT   (Bool             on          );   Bool             highPrecColRT  ()C {return _hp_col_rt     ;} // set/get High Precision Color  Render Target (true/false                         , default=           false                             ), enabling high precision render targets     gives higher quality graphics at the cost of slower performance, high precision means that Render Targets are created with 16-bit floating point precision instead of 8-bit unsigned byte, Color  Render Target is used for storing colors                                 , this affects the entire rendering chain, the biggest difference you can notice is the Sky gradients being more smooth, the change is NOT instant, avoid calling real-time
   Display& highPrecNrmRT   (Bool             on          );   Bool             highPrecNrmRT  ()C {return _hp_nrm_rt     ;} // set/get High Precision Normal Render Target (true/false                         , default=           false                             ), enabling high precision render targets     gives higher quality graphics at the cost of slower performance, high precision means that Render Targets are created with 16-bit floating point precision instead of 8-bit unsigned byte, Normal Render Target is used for storing normal vectors   in Deferred Renderer  , this affects lighting calculations (especially specular) to be more precise, an alternative option to increase the light precision is to use 'highPrecNrmCalc' instead, the change is NOT instant, avoid calling real-time
   Display& highPrecLumRT   (Bool             on          );   Bool             highPrecLumRT  ()C {return _hp_lum_rt     ;} // set/get High Precision Light  Render Target (true/false                         , default=           false                             ), enabling high precision render targets     gives higher quality graphics at the cost of slower performance, high precision means that Render Targets are created with 16-bit floating point precision instead of 8-bit unsigned byte, Light  Render Target is used for storing light  intensity in Deferred Renderer  , most importantly it allows to store light intensities with values higher than 1.0 (which is the limit for low precision render targets), the change is NOT instant, avoid calling real-time
   Display& highPrecNrmCalc (Bool             on          );   Bool             highPrecNrmCalc()C {return _hp_nrm_calc   ;} // set/get High Precision Normal Calculation   (true/false                         , default=           false                             ), enabling high precision normal calculation gives higher quality graphics at the cost of slower performance, high precision means that the Normal Vector from the Normal Render Target in Deferred Renderer will be reconstructed using more complex calculation, giving more precision but slightly slower performance, this affects lighting calculations (especially specular) to be more precise, this is ignored when 'highPrecNrmRT' is enabled as it's not needed in that case, the change is instant, you can call it real-time
   Display& dither          (Bool             on          );   Bool             dither         ()C {return _dither        ;} // set/get Color Dithering                     (true/false                         , default=            true                             ), the change is instant, you can call it real-time
   Display& sync            (Bool             sync        );   Bool             sync           ()C {return _sync          ;} // set/get Screen Synchronization              (true/false                         , default=            true                             ), the change is NOT instant, avoid calling real-time
   Display& maxLights       (Byte             max_lights  );   Byte             maxLights      ()C {return _max_lights    ;} // set/get Maximum Number of Lights            (0=unlimited, 1..255                , default=               0                             ), this will automatically limit the number of lights on the scene, the change is instant, you can call it real-time
   Display& texFilter       (Byte             filter      );   Byte             texFilter      ()C {return _tex_filter    ;} // set/get Texture Filtering Quality           (0..maxTexFilter()                  , default=               8 (2               for Mobile)), 0=no filtering, 1=linear filtering, 2 and more=anisotropic filtering, the change is NOT instant, avoid calling real-time
   Display& texMipFilter    (Bool             on          );   Bool             texMipFilter   ()C {return _tex_mip_filter;} // set/get Texture MipMap Filtering            (true/false                         , default=            true (false           for Mobile)), enables or disables filtering between different mip map levels, the change is NOT instant, avoid calling real-time
   Display& texLod          (Byte             lod         );   Byte             texLod         ()C {return _tex_lod       ;} // set/get Texture Lod Level Quality           (0..16                              , default=               0                             ), values bigger than zero indicate lower texture quality (smaller mip maps will be used), but faster rendering, the change is NOT instant, avoid calling real-time
   Display& texMacro        (Bool             use         );   Bool             texMacro       ()C {return _tex_macro     ;} // set/get Macro      Textures usage           (true/false                         , default=            true                             ), determines usage of additional Macro      Textures in Materials, using this method during application runtime requires setting 'D.set_shader' (please check comments on 'D.set_shader' for more info), the change is NOT instant, avoid calling real-time
   Display& texDetail       (TEXTURE_USAGE    usage       );   TEXTURE_USAGE    texDetail      ()C {return _tex_detail    ;} // set/get Detail     Textures usage           (TEXTURE_USAGE                      , default=   TEX_USE_MULTI (TEX_USE_DISABLE for Mobile)), determines usage of additional Detail     Textures in Materials, using this method during application runtime requires setting 'D.set_shader' (please check comments on 'D.set_shader' for more info), the change is NOT instant, avoid calling real-time
   Display& texReflection   (TEXTURE_USAGE    usage       );   TEXTURE_USAGE    texReflection  ()C {return _tex_reflect   ;} // set/get Reflection Textures usage           (TEXTURE_USAGE                      , default=   TEX_USE_MULTI                             ), determines usage of additional Reflection Textures in Materials, using this method during application runtime requires setting 'D.set_shader' (please check comments on 'D.set_shader' for more info), currently reflection textures do not support 'TEX_USE_MULTI' mode, the change is NOT instant, avoid calling real-time
   Display& fontSharpness   (Flt              value       );   Flt              fontSharpness  ()C {return _font_sharpness;} // set/get Font Sharpness                      (-Inf..Inf                          , default=            0.75                             ), specifies Mip Map Texture Bias for the Font Images, value <0 decreases sharpness, value==0 doesn't change sharpness, value>0 increases sharpness, the change is NOT instant, avoid calling real-time
   Display& bendLeafs       (Bool             on          );   Bool             bendLeafs      ()C {return _bend_leafs    ;} // set/get Leafs Bending animation             (true/false                         , default=            true                             ), using this method during application runtime requires setting 'D.set_shader' (please check comments on 'D.set_shader' for more info), the change is NOT instant, avoid calling real-time
   Display& outlineAffectSky(Bool             on          );   Bool          outlineAffectSky  ()C {return _outline_sky   ;} // set/get Mesh Outline Sky Affect             (true/false                         , default=           false                             ), if this is enabled then outline will be visible on sky pixels in EDGE_DETECT_FAT mode, enabling this option makes outline effect run slower, the change is instant, you can call it real-time
   Display& outlineMode     (EDGE_DETECT_MODE mode        );   EDGE_DETECT_MODE outlineMode    ()C {return _outline_mode  ;} // set/get Mesh Outline   Mode                 (EDGE_DETECT_MODE                   , default=EDGE_DETECT_THIN                             ), the change is instant, you can call it real-time
   Display& edgeDetect      (EDGE_DETECT_MODE mode        );   EDGE_DETECT_MODE edgeDetect     ()C {return _edge_detect   ;} // set/get Edge Detect    Mode                 (EDGE_DETECT_MODE                   , default=EDGE_DETECT_NONE                             ), the change is instant, you can call it real-time
   Display& edgeSoften      (EDGE_SOFTEN_MODE mode        );   EDGE_SOFTEN_MODE edgeSoften     ()C {return _edge_soften   ;} // set/get Edge Softening Mode                 (EDGE_SOFTEN_MODE                   , default=EDGE_SOFTEN_NONE                             ), this is fake Anti-Aliasing, it is not used when Multi Sampling is enabled, the change is instant, you can call it real-time
   Display& stereoscopic    (Bool             on          );   Bool             stereoscopic   ()C {return _stereoscopic  ;} // set/get stereoscopic rendering              (true/false                         , default=           false                             ), the change is NOT instant, avoid calling real-time
   Display& stereoScale     (Flt              scale       );   Flt              stereoScale    ()C {return _stereo_scale  ;} // set/get stereoscopic scaling                (0..2                               , default=               1                             ), the change is instant, you can call it real-time
   Display& eyeDistance     (Flt              dist        );   Flt              eyeDistance    ()C {return _eye_dist      ;} // set/get distance between the eyes           (-Inf..Inf                          , default=           0.064                             ), interpupillary distance (distance between the eye pupils) used for stereoscopic rendering, the change is instant, you can call it real-time
   Display& secondaryOpenGLContexts(Byte      contexts    );   Int         secondaryOpenGLContexts()C;                       // set/get number of secondary OpenGL contexts to create during application initialization (this does not include the main context for the main thread which is always created), each secondary context allows 1 secondary thread to perform operations on the GPU data, for more information please check the 'ThreadMayUseGPUData' global function, this should be called only in 'InitPre', after that, calls to this method are ignored, this value is used only for OpenGL renderer, for DirectX it is ignored, default=1
                                                               Bool canUseGPUDataOnSecondaryThread()C;                       //     get if display supports operating on GPU data on a secondary thread, this is always true for DirectX, for OpenGL it will be true only if secondary OpenGL contexts were successfully created during the display initialization

   // screen fading
   Bool      fading()C;                                      // if    fading is currently enabled
   void   setFade  (Flt seconds, Bool previous_frame=false); // start fading the nearest screen result for the following 'seconds', 'previous_frame'=if use result of previous frame instead of the next frame
   void clearFade  (                                      ); // clear any active fading, the change is instant, you can call it real-time

   // Color Palette
   Display& colorPaletteAllow(  Bool      on     );   Bool      colorPaletteAllow()C {return _color_palette_allow;} // set/get if RM_PALETTE/RM_PALETTE1 rendering modes are allowed, disabling them increases rendering performance, default=true (false for Mobile)
   Display& colorPalette     (C ImagePtr &palette); C ImagePtr& colorPalette     ()C {return _color_palette[0]   ;} // set/get color palette image that is used during RM_PALETTE  rendering mode, palette textures need to have a height of 4 pixels (width can be set freely), where each row represents an intensity color palette for respectively (red, green, blue, alpha) components when rendering in RM_PALETTE  mode, default=Images.ptrGet("Gfx/Fx/color palette.gfx")
   Display& colorPalette1    (C ImagePtr &palette); C ImagePtr& colorPalette1    ()C {return _color_palette[1]   ;} // set/get color palette image that is used during RM_PALETTE1 rendering mode, palette textures need to have a height of 4 pixels (width can be set freely), where each row represents an intensity color palette for respectively (red, green, blue, alpha) components when rendering in RM_PALETTE1 mode, default=NULL

   // Particles
   Display& particlesSoft      (Bool on);   Bool particlesSoft      ()C {return _particles_soft  ;} // set/get Particles Softing          (true/false, default=true                   ), the change is instant, you can call it real-time
   Display& particlesSmoothAnim(Bool on);   Bool particlesSmoothAnim()C {return _particles_smooth;} // set/get Particles Smooth Animation (true/false, default=true (false for Mobile)), if enabled then particles with animated images will be displayed with better quality by smooth blending between animation frames, the change is instant, you can call it real-time

   // Eye Adaptation
   Display& eyeAdaptation         (Bool on          );   Bool eyeAdaptation         ()C {return _eye_adapt           ;} // set/get Eye Adaptation usage                (                true/false                  , default=false), enables automatic screen brightness adjustment, the change is instant, you can call it real-time
   Display& eyeAdaptationWeighted (Bool on          );   Bool eyeAdaptationWeighted ()C {return _eye_adapt_weighted  ;} // set/get Eye Adaptation weighted luminance   (                true/false                  , default=true ), if true then uses (0.2125, 0.7154, 0.0721) weights for RGB components in luminance calculation, if false calculates luminance based on maximum of RGB components, the change is instant, you can call it real-time
   Display& eyeAdaptationExposure (Flt  exposure    );   Flt  eyeAdaptationExposure ()C {return _eye_adapt_exposure  ;} // set/get Eye Adaptation exposure             (                   0..Inf                   , default= 0.75), total scale of lighting, the change is instant, you can call it real-time
   Display& eyeAdaptationContrast (Flt  contrast    );   Flt  eyeAdaptationContrast ()C {return _eye_adapt_contrast  ;} // set/get Eye Adaptation contrast             (                   0..Inf                   , default= 0.2 ), determines how much to darken bright scenes and how much to brighten dark scenes, the change is instant, you can call it real-time
   Display& eyeAdaptationMaxDark  (Flt  max_dark    );   Flt  eyeAdaptationMaxDark  ()C {return _eye_adapt_max_dark  ;} // set/get Eye Adaptation maximum   darkening  (                   0..eyeAdaptationMaxBright, default= 0.1 ), the change is instant, you can call it real-time
   Display& eyeAdaptationMaxBright(Flt  max_bright  );   Flt  eyeAdaptationMaxBright()C {return _eye_adapt_max_bright;} // set/get Eye Adaptation maximum brightening  (eyeAdaptationMaxDark..Inf                   , default= 2.0 ), the change is instant, you can call it real-time
   Display& eyeAdaptationSpeed    (Flt  speed       );   Flt  eyeAdaptationSpeed    ()C {return _eye_adapt_speed     ;} // set/get Eye Adaptation speed                (                   1..Inf                   , default= 6.5 ), the change is instant, you can call it real-time
   Display& resetEyeAdaptation    (Flt  brightness=1);                                                                  // reset   Eye Adaptation value, eye adaptation changes over time according to screen colors, this method resets the adaptation to its original state, 'brightness'=initial brightness (0..Inf), the change is NOT instant, avoid calling real-time

   // Bloom, setting 'original' value to 1, 'scale' to 0 and 'contrast' to 1 disables bloom and increases rendering performance, optionally you can disable it with "bloomAllow(false)"
   Display&  glowAllow     (Bool allow     );   Bool  glowAllow     ()C {return  _glow_allow     ;} // set/get Allow Glow Effect     (true/false, default=true  (false for Mobile)), this can work only if 'bloomAllow' is enabled, the change is instant, you can call it real-time
   Display& bloomAllow     (Bool allow     );   Bool bloomAllow     ()C {return _bloom_allow     ;} // set/get Allow Bloom           (true/false, default=true  (false for Mobile)), the change is instant, you can call it real-time
   Display& bloomOriginal  (Flt  original  );   Flt  bloomOriginal  ()C {return _bloom_original  ;} // set/get Bloom Original Color  (   0..Inf , default=1.0                     ), the change is instant, you can call it real-time
   Display& bloomScale     (Flt  scale     );   Flt  bloomScale     ()C {return _bloom_scale     ;} // set/get Bloom Scale           (   0..Inf , default=0.6                     ), the change is instant, you can call it real-time
   Display& bloomCut       (Flt  cut       );   Flt  bloomCut       ()C {return _bloom_cut       ;} // set/get Bloom Cutoff          (   0..Inf , default=0.3                     ), the change is instant, you can call it real-time
   Display& bloomContrast  (Flt  contrast  );   Flt  bloomContrast  ()C {return _bloom_contrast  ;} // set/get Bloom Contrast        (   0..Inf , default=1.0                     ), the change is instant, you can call it real-time
   Display& bloomOverbright(Bool overbright);   Bool bloomOverbright()C {return _bloom_overbright;} // set/get Bloom Overbright      (true/false, default=false                   ), the change is instant, you can call it real-time
   Display& bloomHalf      (Bool half      );   Bool bloomHalf      ()C {return _bloom_half      ;} // set/get Bloom Half/Quarter    (true/false, default=true  (false for Mobile)), this specifies whether bloom should be calculated using half or quarter sized render targets (half is more precise but slower, quarter is more blurred), the change is instant, you can call it real-time
   Display& bloomBlurs     (Byte blurs     );   Byte bloomBlurs     ()C {return _bloom_blurs     ;} // set/get Bloom Number of Blurs (   1..4   , default=2     (1     for Mobile)), the change is instant, you can call it real-time
   Display& bloomSamples   (Bool high      );   Bool bloomSamples   ()C {return _bloom_samples   ;} // set/get Bloom Sample Count    (true/false, default=true  (false for Mobile)), if set to true then 6 texture reads are performed in the shader, if set to false then 3 texture reads are performed, the change is instant, you can call it real-time

   // Ambient Light
   Display& ambientMode    (AMBIENT_MODE mode    );   AMBIENT_MODE ambientMode    ()C {return _amb_mode       ;} // set/get Ambient Mode            (AMBIENT_MODE, default=AMBIENT_FLAT), the change is instant, you can call it real-time
   Display& ambientSoft    (  Byte       soft    );   Byte         ambientSoft    ()C {return _amb_soft       ;} // set/get Ambient Softing         (  0..3      , default=           1), if soften the AO result, the change is instant, you can call it real-time
   Display& ambientJitter  (  Bool       jitter  );   Bool         ambientJitter  ()C {return _amb_jitter     ;} // set/get Ambient Jittering       (true/false  , default=        true), jittering enables per pixel randomization of the AO samples, the change is instant, you can call it real-time
   Display& ambientNormal  (  Bool       normal  );   Bool         ambientNormal  ()C {return _amb_normal     ;} // set/get Ambient Normal Map Use  (true/false  , default=        true), if include per pixel normal vectors from the render target, the change is instant, you can call it real-time
   Display& ambientRes     (  Int        res     );   Int          ambientRes     ()C {return _amb_res        ;} // set/get Ambient Resolution      (  0..2      , default=           1), this determines the size of the buffers used for calculating the Ambient Occlusion effect, 0=full size, 1=half size, 2=quarter size, smaller sizes offer faster performance but worse quality, the change is instant, you can call it real-time
   Display& ambientPower   (  Flt        power   );   Flt          ambientPower   ()C {return _amb_color.max();} // set/get Ambient Power           (  0..2      , default=         0.4), this is equivalent to using 'ambientColor' with RGB components set to the same value, the change is instant, you can call it real-time
   Display& ambientColor   (C Vec       &color   );   Vec          ambientColor   ()C {return _amb_color      ;} // set/get Ambient Color           (  0..2      , default=         0.4), the change is instant, you can call it real-time
   Display& ambientContrast(  Flt        contrast);   Flt          ambientContrast()C {return _amb_contrast   ;} // set/get Ambient Contrast        (  0..Inf    , default=         1.2), the change is instant, you can call it real-time
   Display& ambientRange   (C Vec2      &range   );   Vec2         ambientRange   ()C {return _amb_range      ;} // set/get Ambient 2D Range        (  0..Inf    , default=         0.3), the change is instant, you can call it real-time
   Display& ambientScale   (  Flt        scale   );   Flt          ambientScale   ()C {return _amb_scale      ;} // set/get Ambient 3D Scale        (  0..Inf    , default=         2.5), the change is instant, you can call it real-time
   Display& ambientBias    (  Flt        bias    );   Flt          ambientBias    ()C {return _amb_bias       ;} // set/get Ambient Bias            (  0..1      , default=         0.3), the change is instant, you can call it real-time

   // Shadowing
   Display& shadowMode         (SHADOW_MODE mode    );   SHADOW_MODE shadowMode         ()C {return _shd_mode      ;} // set/get Shadow Mode                                  (SHADOW_MODE, default=SHADOW_MAP (SHADOW_NONE for Mobile)), the change is instant, you can call it real-time
   Display& shadowSoft         (Byte        soft    );   Byte        shadowSoft         ()C {return _shd_soft      ;} // set/get Shadow Softing                               (  0..2     , default=         0                         ), available only in RT_DEFERRED renderer, the change is instant, you can call it real-time
   Display& shadowJitter       (Bool        jitter  );   Bool        shadowJitter       ()C {return _shd_jitter    ;} // set/get Shadow Jittering                             (true/false , default=     false                         ), works best when combined with shadow softing, the change is instant, you can call it real-time
   Display& shadowReduceFlicker(Bool        on      );   Bool        shadowReduceFlicker()C {return _shd_reduce    ;} // set/get Shadow Flickering Decreasing                 (true/false , default=     false                         ), this option reduces directional light shadow map flickering when rotating the camera, however at the expense of slightly increasing the shadow map blockiness, enable only when the flickering is really disturbing, the change is instant, you can call it real-time
   Display& shadowFrac         (Flt         frac    );   Flt         shadowFrac         ()C {return _shd_frac      ;} // set/get Shadow Range Fraction for Directional Lights (  0..1     , default=         1                         ), this option can limit shadowing range to a fraction of the viewport range, the change is instant, you can call it real-time
   Display& shadowFade         (Flt         fade    );   Flt         shadowFade         ()C {return _shd_fade      ;} // set/get Shadow Fade  Fraction for Directional Lights (  0..1     , default=         1                         ), this option specifies at which part of the shadowing range, shadow fading occurs, the change is instant, you can call it real-time
   Display& shadowMapSize      (Int         map_size);   Int         shadowMapSize      ()C {return _shd_map_size  ;} // set/get Shadow Map Size                              (  1..Inf   , default=      1024                         ), this option specifies the size of a single shadow map (in pixels), bigger size results in more precise shadows but smaller performance, the change is NOT instant, avoid calling real-time
   Display& shadowMapSizeLocal (Flt         frac    );   Flt         shadowMapSizeLocal ()C {return _shd_map_size_l;} // set/get Shadow Map Size Fraction for    Local Lights (  0..1     , default=         1                         ), this option specifies global size factor for computing the size of shadow maps for local lights (point/cone), final size of shadow maps for local lights is calculated using following formula: "shadowMapSize()*shadowMapSizeLocal()"                    , this means that for shadowMapSizeLocal()==1 full shadowMapSize() is used, for shadowMapSizeLocal()==0.5 half of shadowMapSize() is used, and so on, the change is instant, you can call it real-time
   Display& shadowMapSizeCone  (Flt         factor  );   Flt         shadowMapSizeCone  ()C {return _shd_map_size_c;} // set/get Shadow Map Size Factor   for    Cone  Lights (  0..2     , default=         1                         ), this option specifies global size factor for computing the size of shadow maps for cone  lights             , final size of shadow maps for cone  lights is calculated using following formula: "shadowMapSize()*shadowMapSizeLocal()*shadowMapSizeCone()", this means that for shadowMapSizeCone ()==1 full shadowMapSize() is used, for shadowMapSizeCone ()==0.5 half of shadowMapSize() is used, for shadowMapSizeCone()==2 double of shadowMapSize() is used, the range for shadowMapSizeCone is 0..2, which means that if set to 2, it can double the default shadow quality for all cone lights, the change is instant, you can call it real-time
   Display& shadowMapNum       (Byte        map_num );   Byte        shadowMapNum       ()C {return _shd_map_num   ;} // set/get Number of Shadow Maps for Directional Lights (  1..6     , default=         6                         ), this option specifies the number of shadow maps used when rendering directional lights, the more shadow maps are used the better quality but smaller performance, RT_FORWARD renderer supports only even numbers of maps, the change is instant, you can call it real-time
   Display& cloudsMapSize      (Int         map_size);   Int         cloudsMapSize      ()C {return _cld_map_size  ;} // set/get Clouds Shadow Map Size                       (  1..Inf   , default=        80                         ), the change is NOT instant, avoid calling real-time

   // Motion Blur
   Display& motionMode  (MOTION_MODE mode  );   MOTION_MODE motionMode  ()C {return _mtn_mode     ;} // set/get Motion Blur Mode                 (MOTION_MODE, default=MOTION_NONE), the change is instant, you can call it real-time
   Display& motionSmooth(Bool        smooth);   Bool        motionSmooth()C {return _mtn_smooth   ;} // set/get Motion Blur Smooth Blurring      (true/false , default=      false), if set to true then 15 samples will be used when blurring, if false only 7 will be used, the change is instant, you can call it real-time
   Display& motionLeaks (Byte        remove);   Byte        motionLeaks ()C {return _mtn_leaks_rem;} // set/get Motion Blur Leaks  Removal       ( 0..3      , default=          2), remove leaking of blurred background objects into not blurred foreground objects, the change is instant, you can call it real-time
   Display& motionScale (Flt         scale );   Flt         motionScale ()C {return _mtn_scale    ;} // set/get Motion Blur Velocity Scale       ( 0..Inf    , default=       0.04), the change is instant, you can call it real-time
   Display& motionSkyVel(Bool        on    );   Bool        motionSkyVel()C {return _mtn_sky_vel  ;} // set/get Motion Blur Correct Sky Velocity (true/false , default=       true), the change is instant, you can call it real-time

   // Depth of Field
   Display& dofMode (DOF_MODE mode );   DOF_MODE dofMode ()C {return _dof_mode ;} // set/get Depth of Field Mode            ( DOF_MODE , default=DOF_NONE), the change is instant, you can call it real-time
   Display& dofHalf (Bool     half );   Bool     dofHalf ()C {return _dof_half ;} // set/get Depth of Field Half/Quarter    (true/false, default=    true), this specifies whether depth of field should be calculated using half or quarter sized render targets (half is more precise but slower, quarter is more blurred), the change is instant, you can call it real-time
   Display& dofBlurs(Byte     blurs);   Byte     dofBlurs()C {return _dof_blurs;} // set/get Depth of Field Number of Blurs (   1..4   , default=       1), the change is instant, you can call it real-time
   Display& dofPower(Flt      power);   Flt      dofPower()C {return _dof_power;} // set/get Depth of Field Power           (   0..1   , default=       1), intensity of the depth of field effect, the change is instant, you can call it real-time
   Display& dofZ    (Flt      z    );   Flt      dofZ    ()C {return _dof_z    ;} // set/get Depth of Field Focus Position  (   0..Inf , default=       0), this is the distance from camera which shouldn't be blurred, the change is instant, you can call it real-time
   Display& dofRange(Flt      range);   Flt      dofRange()C {return _dof_range;} // set/get Depth of Field Focus Range     (   0..Inf , default=      30), this is the distance from Focus Position where blurring should be set to maximum, the change is instant, you can call it real-time

   // Level of Detail
   Display& lod            (Flt general, Flt shadow, Flt mirror);                              // set     Level of Detail factors, the change is instant, you can call it real-time
   Display& lodFactor      (Flt factor);   Flt lodFactor      ()C {return _lod_factor       ;} // set/get Level of Detail general factor which determines                                    Lod selection, 0..Inf, default=1, it's a scaling factor: values from 0..1 increase details and values from 1..Inf decrease details, the change is instant, you can call it real-time
   Display& lodFactorShadow(Flt factor);   Flt lodFactorShadow()C {return _lod_factor_shadow;} // set/get Level of Detail shadows factor which is also applied to shadows                    Lod selection, 0..Inf, defailt=2, it's a scaling factor: values from 0..1 increase details and values from 1..Inf decrease details, the change is instant, you can call it real-time
   Display& lodFactorMirror(Flt factor);   Flt lodFactorMirror()C {return _lod_factor_mirror;} // set/get Level of Detail mirror  factor which is also applied to meshes rendered in mirrors Lod selection, 0..Inf, defailt=2, it's a scaling factor: values from 0..1 increase details and values from 1..Inf decrease details, the change is instant, you can call it real-time

   // Tesselation
   Display& tesselation         (Bool on     );   Bool tesselation         ()C {return _tesselation          ;} // set/get Tesselation               (true/false, default=false), Tesselation smoothes the mesh polygons, it is available only on Shader Model>=5.0, the change is instant, you can call it real-time
   Display& tesselationHeightmap(Bool on     );   Bool tesselationHeightmap()C {return _tesselation_heightmap;} // set/get Tesselation of Heightmaps (true/false, default=false), the change is NOT instant, avoid calling real-time
   Display& tesselationDensity  (Flt  density);   Flt  tesselationDensity  ()C {return _tesselation_density  ;} // set/get Tesselation Density       (  0..Inf  , default=60   ), the change is instant, you can call it real-time

   // Grass
   Display& grassRange  (Flt  range  );   Flt  grassRange  ()C {return _grass_range  ;} // set/get Grass Range             (  0..Inf  , default=50                ), grass objects above specified range will not be rendered, the change is instant, you can call it real-time
   Display& grassDensity(Flt  density);   Flt  grassDensity()C {return _grass_density;} // set/get Grass Density           (  0..1    , default=1 (0.5 for Mobile)), controls the amount of grass objects rendered, the change is instant, you can call it real-time
   Display& grassShadow (Bool on     );   Bool grassShadow ()C {return _grass_shadow ;} // set/get Grass Shadow Casting    (true/false, default=false             ), if grass objects should cast shadows, the change is instant, you can call it real-time
   Display& grassMirror (Bool on     );   Bool grassMirror ()C {return _grass_mirror ;} // set/get Grass Drawing in Mirror (true/false, default=false             ), if grass objects should be drawn in mirrors, the change is instant, you can call it real-time
   Display& grassUpdate (            );                                                 // update  Grass and Leafs bending animation, call this each frame to update the animation, the change is instant, you can call it real-time

   // Fur
   Display& furStaticGravity (Flt gravity  );   Flt furStaticGravity ()C {return _fur_gravity  ;} //                     gravity affecting fur on non-animated meshes which aren't controlled by AnimatedSkeleton (AnimatedSkeleton.fur_* parameters), -Inf..Inf, default=-1   , the change is instant, you can call it real-time
   Display& furStaticVelScale(Flt vel_scale);   Flt furStaticVelScale()C {return _fur_vel_scale;} // how much does mesh movement affect    fur on non-animated meshes which aren't controlled by AnimatedSkeleton (AnimatedSkeleton.fur_* parameters), -Inf..Inf, default=-0.75, the change is instant, you can call it real-time

   // Volumetric Lighting
   Display& volLight(Bool on );   Bool volLight()C {return _vol_light;} // set/get Volumetric Lighting       (true/false, default=false), supported only in SHADOW_MAP shadow mode and Shader Model>=3.0, the change is instant, you can call it real-time
   Display& volAdd  (Bool on );   Bool volAdd  ()C {return _vol_add  ;} // set/get Volumetric Apply Mode     (true/false, default=false), when true is set, Volumetric Light will be added to the scene, if false is set, Lerp to 1 will be performed, the change is instant, you can call it real-time
   Display& volMax  (Flt  max);   Flt  volMax  ()C {return _vol_max  ;} // set/get Volumetric Global Maximum (   0..Inf , default=1.0  ), the change is instant, you can call it real-time

   // Viewport Settings
   Display& viewRect (C RectI *rect               );   C RectI& viewRectI  ()C {return _view_main.recti   ;} // set/get viewport rectangle (NULL for fullscreen), custom viewport rectangle is reset at start of each frame to fullscreen, that's why when used it must be set manually in each frame
   Display& viewRect (C Rect  &rect               );   C Rect & viewRect   ()C {return _view_rect         ;} // set/get viewport rectangle                      , custom viewport rectangle is reset at start of each frame to fullscreen, that's why when used it must be set manually in each frame
   Display& viewFrom (Flt from                    );   Flt      viewFrom   ()C {return _view_main.from    ;} // set/get viewport near clip plane       , default=0.05
   Display& viewRange(Flt range                   );   Flt      viewRange  ()C {return _view_main.range   ;} // set/get viewport far  clip plane       , default=100
   Display& viewFov  (Flt fov, FOV_MODE mode=FOV_Y);   Flt      viewFov    ()C {return _view_fov          ;} // set/get viewport          field of view, default={DegToRad(75), FOV_Y}
                                                       Flt      viewFovX   ()C {return _view_main.fov.x   ;} //     get actual horizontal field of view
                                                       Flt      viewFovY   ()C {return _view_main.fov.y   ;} //     get actual vertical   field of view
                                                       FOV_MODE viewFovMode()C {return _view_main.fov_mode;} //     get viewport          field of view mode, default=FOV_Y
   Display& viewForceSquarePixel(Bool square=false);                                                         //   force pixel aspect ratio to 1, this may be needed for rendering to textures, default rendering should have this disabled, default=false

   // Convert Coordinates                                                          src.X           src.Y                          dest.X          dest.Y
   static Vec2  screenToUV              (C Vec2  &screen); // from screen      (-D.w .. D.w   , -D.h .. D.h   ) to UV          (   0 .. 1     ,    0 .. 1     )
   static Rect  screenToUV              (C Rect  &screen); // from screen      (-D.w .. D.w   , -D.h .. D.h   ) to UV          (   0 .. 1     ,    0 .. 1     )
   static Vec2  screenToPixel           (C Vec2  &screen); // from screen      (-D.w .. D.w   , -D.h .. D.h   ) to pixel       (   0 .. D.resW,    0 .. D.resH)
   static VecI2 screenToPixelI          (C Vec2  &screen); // from screen      (-D.w .. D.w   , -D.h .. D.h   ) to pixel       (   0 .. D.resW,    0 .. D.resH)
   static Rect  screenToPixel           (C Rect  &screen); // from screen      (-D.w .. D.w   , -D.h .. D.h   ) to pixel       (   0 .. D.resW,    0 .. D.resH)
   static RectI screenToPixelI          (C Rect  &screen); // from screen      (-D.w .. D.w   , -D.h .. D.h   ) to pixel       (   0 .. D.resW,    0 .. D.resH)
   static Vec2  screenToPixelSize       (C Vec2  &screen); // from screen size (   0 .. D.w*2 ,    0 .. D.h*2 ) to pixel  size (   0 .. D.resW,    0 .. D.resH), use this function for widths and heights
   static Vec2  UVToScreen              (C Vec2  &uv    ); // from UV          (   0 .. 1     ,    0 .. 1     ) to screen      (-D.w .. D.w   , -D.h .. D.h   )
   static Vec2  pixelToScreen           (C Vec2  &pixel ); // from pixel       (   0 .. D.resW,    0 .. D.resH) to screen      (-D.w .. D.w   , -D.h .. D.h   )
   static Vec2  pixelToScreen           (C VecI2 &pixel ); // from pixel       (   0 .. D.resW,    0 .. D.resH) to screen      (-D.w .. D.w   , -D.h .. D.h   )
   static Rect  pixelToScreen           (C Rect  &pixel ); // from pixel       (   0 .. D.resW,    0 .. D.resH) to screen      (-D.w .. D.w   , -D.h .. D.h   )
   static Rect  pixelToScreen           (C RectI &pixel ); // from pixel       (   0 .. D.resW,    0 .. D.resH) to screen      (-D.w .. D.w   , -D.h .. D.h   )
   static Vec2  pixelToScreenSize       (C Vec2  &pixel ); // from pixel  size (   0 .. D.resW,    0 .. D.resH) to screen size (   0 .. D.w*2 ,    0 .. D.h*2 ), use this function for widths and heights
   static Vec2  pixelToScreenSize       (C VecI2 &pixel ); // from pixel  size (   0 .. D.resW,    0 .. D.resH) to screen size (   0 .. D.w*2 ,    0 .. D.h*2 ), use this function for widths and heights
   static Vec2  screenAlignedToPixel    (C Vec2  &screen); // get   screen space position  aligned to nearest pixel
   static Vec2  alignScreenToPixelOffset(C Vec2  &screen); // get   offset needed for aligning screen space position to nearest pixel
   static void  alignScreenToPixel      (  Vec2  &screen); // align screen space position  to nearest pixel
   static void  alignScreenToPixel      (  Rect  &screen); // align screen space rectangle so its top-left corner will be aligned to nearest pixel while preserving the rectangle size
        C Vec2& pixelToScreenSize       (               )C {return _pixel_size;} // get screen size of a single pixel

   // Clear Screen
   static void clear     (C Color &color=TRANSPARENT); // clear screen viewport to 'color' and clear depth buffer
   static void clearCol  (C Color &color=TRANSPARENT); // clear screen viewport to 'color'
   static void clearDepth(                          ); // clear                                      depth buffer

   // operations
   void setShader(Material *material=NULL); // manually trigger resetting shaders for all meshes, 'material'=if reset shaders only for meshes having specified material (use NULL for all meshes)

private:
   struct ViewportSettings
   {
      FOV_MODE fov_mode;
      Flt      from, range, fov;
      Rect     rect;

      void get() ; // get viewport settings from current display settings "T=D"
      void set()C; // set viewport settings as   current display settings "D=T"
   };
   struct Viewport
   {
      // 2D
      Bool     full;
      RectI    recti;

      // 3D
      Flt      from, range;
      Vec2     fov, fov_sin, fov_cos, fov_tan;
      FOV_MODE fov_mode;
   };

   ASPECT_MODE      _aspect_mode;
   BUMP_MODE        _bump_mode;
   AMBIENT_MODE     _amb_mode;
   SHADOW_MODE      _shd_mode;
   MOTION_MODE      _mtn_mode;
   DOF_MODE         _dof_mode;
   EDGE_DETECT_MODE _edge_detect, _outline_mode;
   EDGE_SOFTEN_MODE _edge_soften;
   TEXTURE_USAGE    _tex_detail, _tex_reflect;
   SHADER_MODEL     _shader_model;
   Str8             _device_name;
   Bool             _full, _sync, _density_filter, _hp_col_rt, _hp_nrm_rt, _hp_lum_rt, _hp_nrm_calc, _dither, _bend_leafs, _particles_soft, _particles_smooth, _tex_mip_filter, _tex_macro, _eye_adapt, _eye_adapt_weighted, _bloom_overbright, _bloom_half, _bloom_samples, _dof_half,
                    _tesselation, _tesselation_heightmap,
                    _bloom_allow, _glow_allow, _amb_jitter, _amb_normal, _shd_jitter, _shd_reduce, _grass_shadow, _grass_mirror, _vol_light, _vol_add, _mtn_smooth, _mtn_sky_vel, _outline_sky, _color_palette_allow,
                    _gamma_use, _tex_pow2, _tex_pow2_mip, _tex_pow2_3d, _tex_pow2_cube, _mrt_const_bit_size, _mrt_post_process, _view_square_pixel, _resetting, _began, _no_gpu, _can_draw, _stereoscopic, _fade_get, _fade_flipped;
   Byte             _density, _samples, _max_tex_filter, _max_vtx_attribs, _bloom_blurs, _max_rt,
                    _amb_soft, _amb_res,
                    _shd_soft, _shd_map_num,
                    _mtn_leaks_rem,
                    _dof_blurs,
                    _max_lights,
                    _tex_filter, _tex_lod, _stereo_num;
   UShort           _gamma_array[3][256];
   Int              _shd_map_size, _shd_map_size_actual, _cld_map_size, _freq_want, _freq_got, _max_tex_size;
   VecI2            _res, _dense;
   Flt              _aspect, _aspect_ratio, _aspect_ratio_want, _aspect_pixel, _gamma, _uw, _uh, _w, _h, _w2, _h2, _font_sharpness, _scale,
                    _amb_contrast, _amb_scale, _amb_bias,
                    _eye_adapt_exposure, _eye_adapt_contrast, _eye_adapt_max_dark, _eye_adapt_max_bright, _eye_adapt_speed,
                    _shd_frac, _shd_fade, _shd_map_size_l, _shd_map_size_c,
                    _bloom_original, _bloom_scale, _bloom_cut, _bloom_contrast,
                    _mtn_scale,
                    _dof_power, _dof_z, _dof_range,
                    _vol_max,
                    _grass_range, _grass_range_sqr, _grass_density,
                    _lod_factor, _lod_factor_shadow, _lod_factor_mirror, _lod_factors[2][2], _lod_factors_fov[2][2], _lod_fov, _lod_current_factor,
                    _tesselation_density,
                    _fur_gravity, _fur_vel_scale,
                    _stereo_scale, _eye_dist,
                    _view_fov,
                    _fade_len, _fade_step;
   Vec2             _draw_offset, _pixel_size, _pixel_size_2, _pixel_size_inv,
                    _amb_range;
   Vec              _amb_color;
   Vec2             _view_center, _view_helper;
   Rect             _view_rect, _view_eye_rect[2];
   Viewport         _view_main, _view_active;
   ImagePtr         _color_palette[2];
   Image            _color_palette_soft[2];
   Mems<VecI2>      _modes;
   CritSect         _cs, _cs_func;
   Material*        _set_shader_material;
   Ptr              _get_shader, _get_shader_f, _get_shader_b;

   Display();
};extern Display
   D; // Main Display Control
/******************************************************************************/
