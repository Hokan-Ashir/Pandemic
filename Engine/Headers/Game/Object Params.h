/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'ObjParams' to create custom object templates in the World Editor.
   They will be used for creation of the actual game objects 'Obj'.

/******************************************************************************/
namespace Game{
/******************************************************************************/
enum OBJ_ACCESS // object access mode
{
   ACCESS_CUSTOM , // object can   be accessed and modified during the game any modifications will be saved in SaveGame, this is suited for all dynamic objects which       require custom class
   ACCESS_TERRAIN, // object can't be accessed, it will be embedded into the terrain and rendered as static mesh       , this is suited for all static  objects which don't require custom class, these objects are managed completely by the engine
   ACCESS_GRASS  , // works like ACCESS_TERRAIN however it is optimized for instanced grass rendering, additionaly objects of this mode can be controlled by D.grass methods
   ACCESS_OVERLAY, // works like ACCESS_TERRAIN however it will generate a mesh overlay on the terrain using objects material
   ACCESS_NUM    , // number of access modes
};
enum OBJ_PATH // object path mesh mode
{
   OBJ_PATH_CREATE, //       create path mesh from this object
   OBJ_PATH_IGNORE, // don't create path mesh from this object
   OBJ_PATH_BLOCK , // fully block  path mesh from this object
   OBJ_PATH_NUM   , // number of path modes
};
/******************************************************************************/
DECLARE_CACHE(ObjParams, Objs, ObjParamsPtr); // 'Objs' cache storing 'ObjParams' objects which can be accessed by 'ObjParamsPtr' pointer
/******************************************************************************/
struct ObjParams // Object Parameters - they're created in the Editor and are used for creating typical Game Objects 'Game::Obj'
{
   // members
   Matrix          matrix  ; // matrix, its scale determines object's scale
   Memc<Param>     params  ; // parameters
   Memc<ObjParams> sub_objs; // sub-objects

   // manage
   ObjParams& del   (                ); // delete manually
   ObjParams& create(C ObjParams &src); // create from 'src'

   // get / set
   Matrix matrixFinal()C; // get final matrix ('matrix' adjusted by 'align'), its scale determines object's scale
   Vec    centerFinal()C; // get final matrix center

   ObjParamsPtr firstStored(); // get first object (starting from self to its all bases) which is stored in the cache (which means that it's a project element) and not dynamically created, this will iterate through object and its all bases and return the first one which is stored in the cache, NULL on fail

   void base           (             C ObjParamsPtr &base                     ); C ObjParamsPtr& base              ()C {return _base             ;} // set/get base object
   void type           (Bool custom, C UID          &type     =UIDZero        ); C UID         & type              ()C {return _type             ;} // set/get object type        (OBJ_TYPE 'ObjType' enum element ID), 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used)
   void access         (Bool custom,   OBJ_ACCESS    access   = ACCESS_TERRAIN);   OBJ_ACCESS    access            ()C {return _access           ;} // set/get object access mode (OBJ_ACCESS                        ), 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used)
   void path           (Bool custom,   OBJ_PATH      path     =OBJ_PATH_CREATE);   OBJ_PATH      path              ()C {return _path             ;} // set/get object path   mode (OBJ_PATH                          ), 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used)
   void mesh           (Bool custom, C MeshPtr      &mesh     =NULL           ); C MeshPtr     & mesh              ()C {return _mesh             ;} // set/get mesh                                                   , 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used)
   void meshVariationID(Bool custom,   UInt          id       =0              );   UInt          meshVariationID   ()C {return _mesh_variation_id;} // set/get mesh variation ID                                      , 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used), based on this value, 'meshVariationIndex' can be obtained
                                                                                    Int          meshVariationIndex()C;                             //     get mesh variation index based on variation ID
   void phys           (Bool custom, C PhysBodyPtr  &phys     =NULL           ); C PhysBodyPtr & phys              ()C {return _phys             ;} // set/get physical body                                          , 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used)
   void constant       (Bool custom,   Bool          on       =false          );   Bool          constant          ()C;                             // set/get object constant mode                                   , 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used), this is special modifier for ACCESS_CUSTOM access specifying that the object is always constant (never changes) and should not be saved in SaveGame, but should always created as new object from its default parameters (this reduces SaveGame size)
   void scale          (Bool custom, C Vec          &scale    =1              );   Flt           scale             ()C;                             // set/get object scale                                           , 'custom'=if override base defaults and set custom value (when set to true custom value will be used, if set to false base value will be used)
                                                                                   Vec           scale3            ()C;                             //     get object scale in 3 dimensions

   Bool customType         ()C; // if uses custom type           (if 'custom' was set to true when setting the value)
   Bool customAccess       ()C; // if uses custom access         (if 'custom' was set to true when setting the value)
   Bool customPath         ()C; // if uses custom path           (if 'custom' was set to true when setting the value)
   Bool customMesh         ()C; // if uses custom mesh           (if 'custom' was set to true when setting the value)
   Bool customMeshVariation()C; // if uses custom mesh variation (if 'custom' was set to true when setting the value)
   Bool customPhys         ()C; // if uses custom phys           (if 'custom' was set to true when setting the value)
   Bool customConstant     ()C; // if uses custom constant       (if 'custom' was set to true when setting the value)
   Bool customScale        ()C; // if uses custom scale          (if 'custom' was set to true when setting the value)
   Bool customAlign        ()C; // if uses custom align          (if 'custom' was set to true when setting the value)

   // params
   Param    * findParam (C Str &name) ; // find parameter by name, first local parameters are searched, if not found then bases are searched recursively, NULL on fail !! each objects parameters are required to be sorted according to their name !!
 C Param    * findParam (C Str &name)C; // find parameter by name, first local parameters are searched, if not found then bases are searched recursively, NULL on fail !! each objects parameters are required to be sorted according to their name !!
   Param    &  getParam (C Str &name) ; // get  parameter by name, first local parameters are searched, if not found then bases are searched recursively, Exit on fail !! each objects parameters are required to be sorted according to their name !!
 C Param    &  getParam (C Str &name)C; // get  parameter by name, first local parameters are searched, if not found then bases are searched recursively, Exit on fail !! each objects parameters are required to be sorted according to their name !!
   ObjParams& sortParams(           ) ; // sort parameters according to their names, this needs to be called after manual adding/removing custom parameters (this is needed for using 'findParam getParam' methods which assume that parameters are sorted)

   // aligning
   ALIGN_TYPE alignX()C; // get x aligning
   ALIGN_TYPE alignY()C; // get y aligning
   ALIGN_TYPE alignZ()C; // get z aligning
   void       align (Bool custom, ALIGN_TYPE x=ALIGN_NONE, ALIGN_TYPE y=ALIGN_NONE, ALIGN_TYPE z=ALIGN_NONE); // set aligning

   // operations
   ObjParams& updateBase(); // update members according to base (you should call this if base members were changed)

   // io
   Bool save(C Str &name)C; // save, false on fail
   Bool load(C Str &name) ; // load, false on fail
   void save(File &f, CChar *path=NULL)C; // save, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   // compare
   Bool operator==(C ObjParams &obj)C;                    // if     equal
   Bool operator!=(C ObjParams &obj)C {return !(T==obj);} // if not equal

   ObjParams();

private:
   UShort            _flag;
   Byte              _align;
   Enum1<OBJ_ACCESS> _access;
   Enum1<OBJ_PATH  > _path;
   UID               _type;
   ObjParamsPtr      _base;
   MeshPtr           _mesh;
   UInt              _mesh_variation_id;
   PhysBodyPtr       _phys;
};
/******************************************************************************/
extern Enum ObjType; // OBJ_TYPE enum responsible for game object type management
/******************************************************************************/
} // namespace
/******************************************************************************/
