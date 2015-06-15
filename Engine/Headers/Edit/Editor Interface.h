/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
namespace Edit{
/******************************************************************************/
enum ELM_TYPE // Project Element Type
{
   ELM_NONE       , // None
   ELM_FOLDER     , // Folder
   ELM_ENUM       , // Enum
   ELM_IMAGE      , // Image
   ELM_IMAGE_ATLAS, // Image Atlas
   ELM_FONT       , // Font
   ELM_TEXT_STYLE , // Text Style
   ELM_PANEL      , // Panel
   ELM_GUI        , // Gui Objects
   ELM_SHADER     , // Shader
   ELM_MTRL       , //          Material
   ELM_WATER_MTRL , // Water    Material
   ELM_PHYS_MTRL  , // Physical Material
   ELM_OBJ_CLASS  , // Object Class
   ELM_OBJ        , // Object
   ELM_MESH       , // Mesh
   ELM_SKEL       , // Skeleton
   ELM_PHYS       , // Physical Body
   ELM_ANIM       , // Animation
   ELM_PANEL_IMAGE, // Panel Image
   ELM_ICON       , // Icon
   ELM_ENV        , // Environment
   ELM_WORLD      , // World
   ELM_SOUND      , // Sound
   ELM_VIDEO      , // Video
   ELM_FILE       , // Raw File
   ELM_CODE       , // Esenthel Source/Script (ES)
   ELM_LIB        , // Code Library
   ELM_APP        , // Code Application
   ELM_ICON_SETTS , // Icon Settings
   ELM_MINI_MAP   , // World Mini Map
   ELM_GUI_SKIN   , // Gui Skin
   ELM_NUM        , // Number of Element Types
};
/******************************************************************************/
struct Elm // Project Element
{
   Enum1<ELM_TYPE> type   ; // type of the element
   Bool            removed, // if this element is marked   as removed    (this does not include parents state which may affect the final result, see 'final_removed' for final value)
                   publish, // if this element is included in publishing (this does not include parents state which may affect the final result, see 'final_publish' for final value)
             final_removed, // if this element or  its parents are marked   as removed
             final_publish; // if this element and its parents are included in publishing
   UID                  id, //      id   of the element
                 parent_id; //      id   of the element's parent ('UIDZero' means no parent)
   Str                name, //      name of the element
                 full_name, // full name of the element (including its parents)
                  src_file; // source file from which this element was created

   void save(File &f)C {f<<type<<removed<<publish<<id<<parent_id<<name<<src_file;}
   Bool load(File &f)  {f>>type>>removed>>publish>>id>>parent_id>>name>>src_file; return true;}
};
/******************************************************************************/
struct Project // Project
{
   UID id  ; // id   of the project
   Str name; // name of the project

   Project& set(C UID &id, C Str &name) {T.id=id; T.name=name; return T;}

   void save(File &f)C {f<<id<<name;}
   Bool load(File &f)  {f>>id>>name; return true;}
};
/******************************************************************************/
T1(TYPE) struct IDParam // ID with a custom parameter
{
   UID  id;
   TYPE value;

   void save(File &f)C {f<<id<<value;}
   Bool load(File &f)  {f>>id>>value; return true;}

   IDParam(C UID &id=UIDZero       ) : id(id)               {}
   IDParam(C UID &id, C TYPE &value) : id(id), value(value) {}
};
/******************************************************************************/
struct ObjParams // Object parameters
{
   UID    id; // id of ELM_OBJ element in the project
   Matrix matrix; // object matrix (its scale determines the object size)
   Bool   align_to_terrain; // if align vertical position of the object to the terrain at that location (in that case 'matrix.pos.y' will be ignored)
   Flt    align_to_terrain_normal; // factor 0..1 of how much to align the object to the terrain surface normal vector (if this is enabled then the object will be additionally rotated according to the terrain shape)

   ObjParams& set(C UID &id, C Matrix &matrix, Bool align_to_terrain=false, Flt align_to_terrain_normal=0) {T.id=id; T.matrix=matrix; T.align_to_terrain=align_to_terrain; T.align_to_terrain_normal=align_to_terrain_normal; return T;}

   void save(File &f)C {f<<id<<matrix<<align_to_terrain<<align_to_terrain_normal;}
   Bool load(File &f)  {f>>id>>matrix>>align_to_terrain>>align_to_terrain_normal; return true;}

   ObjParams(C UID &id=UIDZero, C Matrix &matrix=MatrixIdentity, Bool align_to_terrain=false, Flt align_to_terrain_normal=0) {set(id, matrix, align_to_terrain, align_to_terrain_normal);}
};
struct ObjDesc // Basic Description of a World Object
{
   UID  world_obj_id, // id of world object instance (each object in the world has its unique ID)
          elm_obj_id; // id of ELM_OBJ element in the project (this is the project element object on which the world object is based)
   Matrix matrix    ; // matrix of the world object (its scale determines the object size)
   Bool   selected  , // if the object is currently selected
          removed   ; // if the object is currently marked as removed

   void save(File &f)C {f<<world_obj_id<<elm_obj_id<<matrix<<selected<<removed;}
   Bool load(File &f)  {f>>world_obj_id>>elm_obj_id>>matrix>>selected>>removed; return true;}

   ObjDesc() {world_obj_id.zero(); elm_obj_id.zero(); matrix.identity(); selected=removed=false;}
};
struct ObjData : ObjDesc // Full Description of a World Object
{
   struct Param : EE::Param
   {
      UID  id       ; // id of the parameter (each parameter has its unique ID)
      bool removed  , // if this parameter is currently removed
           inherited; // if this parameter is inherited from a base object or object class (if this is true then the parameter does not directly exist in the object itself, but it exists in the base/class of the object)

      void save(File &f)C {   EE::Param::save(f); f<<id<<removed<<inherited;}
      Bool load(File &f)  {if(EE::Param::load(f)){f>>id>>removed>>inherited; return true;} return false;}

      Param() {id.zero(); removed=inherited=false;}
   };

   UID                     elm_obj_class_id; // id of ELM_OBJ_CLASS element in the project (this is the project element object class of the world object)
   Enum1<Game::OBJ_ACCESS> access; // access mode of the object
   Enum1<Game::OBJ_PATH  > path  ; // path   mode of the object
   Memc<Param>             params; // parameters  of the object

   Param* findParam(C Str &name, PARAM_TYPE type=PARAM_NUM, Bool include_removed=false); // find the first parameter from 'params' of 'name' and 'type' (use PARAM_NUM to accept all parameter types), 'include_removed'=if return removed parameters as well, NULL on fail (if not found)

   void save(File &f)C {   ObjDesc::save(f); f<<elm_obj_class_id<<access<<path;        params.save(f);}
   Bool load(File &f)  {if(ObjDesc::load(f)){f>>elm_obj_class_id>>access>>path; return params.load(f);} return false;}

   ObjData() {elm_obj_class_id.zero();}
};
/******************************************************************************/
struct MaterialMap
{
   void create(Int resolution); // create using specified image resolution (the image will be created as square 'resolution x resolution')

   Int resolution()C;

   void set(Int x, Int y,  C UID &m0, Flt  i0,  C UID &m1, Flt  i1,  C UID &m2, Flt  i2); // set 'm0 m1 m2' ids of project ELM_MTRL materials, with their corresponding 'i0 i1 i2' intensities (range of 0..1), at 'x,y' image coordinates
   void get(Int x, Int y,    UID &m0, Flt &i0,    UID &m1, Flt &i1,    UID &m2, Flt &i2); // get 'm0 m1 m2' ids of project ELM_MTRL materials, with their corresponding 'i0 i1 i2' intensities (range of 0..1), at 'x,y' image coordinates

   void resize(Int resolution);

   void save(File &f)C; // save to   file
   Bool load(File &f) ; // load from file, false on fail

   void           del(); // delete manually
  ~MaterialMap() {del();}

private:
   Image _m, _i;
   IDPalette _ip;
};
/******************************************************************************/
struct EditorInterface
{
   static Str ElmFileName(C UID &elm_id, C Str &data_path=S) {return elm_id.valid() ? Str(data_path).tailSlash(true)+EncodeFileName(elm_id) : S;} // get path to the element file, you can use it to access resources in read-only mode, do not write to the files under no condition

   // connection
   Bool    connected(                            )C; // if connected
   void disconnect  (                            ) ; // disconnect
   Bool    connect  (Str &message, Int timeout=-1) ; //    connect to a running instance of Esenthel Editor, 'timeout'=time in milliseconds (-1=default) to wait for a connection, false on fail

   // projects
   Str  projectsPath(           ); // get path where your projects are located
   Bool projectsPath(C Str &path); // set path where your projects are located

   Bool  getProjects(Memp<Project> projects); // get list of projects, false on fail
   UID   curProject (                      ); // get ID of currently opened project, 'UIDZero' is returned if no project is opened
   Bool openProject (C UID &proj_id=UIDZero); // change active project to the one specified by its id, if 'UIDZero' is passed then editor will open the project list menu, false on fail

   // following methods operate on currently opened project
      // settings
      Str dataPath(); // get project game data path, you can use it to access resources in read-only mode, do not write data to the path under no condition, "" on fail

      // elements
      Bool      getElms (Memp<Elm> elms); // get list of          elements     (elements will be sorted by their ID), false on fail
      Bool selectedElms (Memp<UID> elms); // get list of selected element ID's (ID's     will be sorted            ), false on fail
      UID       newElm  (ELM_TYPE type, C Str &name,                                       C UID &parent_id=UIDZero); // create a new element in the project of 'type', 'name' and assigned to 'parent_id' parent (use 'UIDZero' for no parent), this method does not support following types: ELM_MESH, ELM_SKEL, ELM_PHYS, ELM_WORLD (for creating worlds please use 'newWorld' method)      , ID of the newly created element will be returned or 'UIDZero' if failed
      UID       newWorld(               C Str &name, Int area_size=64, Int terrain_res=64, C UID &parent_id=UIDZero); // create a new world   in the project            'name' and assigned to 'parent_id' parent (use 'UIDZero' for no parent), 'area_size'=size of a single area (in meters, valid values are: 32, 64, 128), 'terrain_res'=terrain resolution (valid values are: 32, 64, 128), ID of the newly created element will be returned or 'UIDZero' if failed

      Bool setElmName   (C Memp< IDParam<Str > > &elms); // set 'name'          for elements, where 'IDParam.id'=element id, 'IDParam.value'=element name
      Bool setElmRemoved(C Memp< IDParam<Bool> > &elms); // set 'removed' state for elements, where 'IDParam.id'=element id, 'IDParam.value'=element removed state
      Bool setElmPublish(C Memp< IDParam<Bool> > &elms); // set 'publish' state for elements, where 'IDParam.id'=element id, 'IDParam.value'=element publish state
      Bool setElmParent (C Memp< IDParam<UID > > &elms); // set 'parent'        for elements, where 'IDParam.id'=element id, 'IDParam.value'=parent id (use 'UIDZero' for no parent)
      Bool setElmSrcFile(C Memp< IDParam<Str > > &elms); // set 'src_file'      for elements, where 'IDParam.id'=element id, 'IDParam.value'=element source file (this does not reload the element, it only adjusts the source file for it)

      // world
      UID   curWorld(                       ); // get ID of currently opened ELM_WORLD element, 'UIDZero' is returned if no world is opened
      Bool openWorld(C UID &world_id=UIDZero); // open world in the world editor, 'world_id'=id of ELM_WORLD element in the project, if 'UIDZero' is passed then editor will close the world editor, false on fail

      Int worldAreaSize(C UID &world_id); // get size (in meters) of a single area in specified world, 'world_id'=id of ELM_WORLD element in the project, 0 on fail

         // world terrain
         Int  worldTerrainRes  (C UID &world_id              ); // get terrain resolution of a single area in specified world, 'world_id'=id of ELM_WORLD element in the project, 0 on fail
         Bool worldTerrainAreas(C UID &world_id, RectI &areas); // get coverage of all areas in the world which have terrain, coordinates are from 'areas.min' to 'areas.max' inclusive, if no areas in the world have terrain then 'RectI(0, 0, -1, -1)' will be returned, 'world_id'=id of ELM_WORLD element in the project, false on fail

         Bool worldTerrainDel        (C UID &world_id, C VecI2 &area_xy                                                                                       ); // delete          terrain          at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail
         Bool worldTerrainExists     (C UID &world_id, C VecI2 &area_xy                                                                                       ); // test if there's terrain          at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail
         Bool worldTerrainGetHeight  (C UID &world_id, C VecI2 &area_xy,   Image &height                                                                      ); // get             terrain height   at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, 'height'   =height   map (its         resolution will be "worldTerrainRes(world_id)", IMAGE_F32    type, IMAGE_SOFT mode)
         Bool worldTerrainSetHeight  (C UID &world_id, C VecI2 &area_xy, C Image &height,                                           C UID &material_id=UIDZero); // set             terrain height   at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, 'height'   =height   map (recommended resolution      is "worldTerrainRes(world_id)" however it will be automatically resized if different, recommended format is IMAGE_F32   ), each terrain must have a material set, if there is already a terrain at that location, then its material will not be modified, if there is no terrain yet, then 'material_id' will be used (which is id of ELM_MTRL element in the project), if the material was not found or it was set to 'UIDZero', then default material from the editor terrain material slot will be used, if that material was not set, then the method will fail and the terrain will not be created
         Bool worldTerrainGetColor   (C UID &world_id, C VecI2 &area_xy,                                             Image &color                             ); // get             terrain color    at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, 'color'    =color    map (its         resolution will be "worldTerrainRes(world_id)", IMAGE_R8G8B8 type, IMAGE_SOFT mode)
         Bool worldTerrainSetColor   (C UID &world_id, C VecI2 &area_xy,                                           C Image &color , C UID &material_id=UIDZero); // set             terrain color    at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, 'color'    =color    map (recommended resolution      is "worldTerrainRes(world_id)" however it will be automatically resized if different, recommended format is IMAGE_R8G8B8), each terrain must have a material set, if there is already a terrain at that location, then its material will not be modified, if there is no terrain yet, then 'material_id' will be used (which is id of ELM_MTRL element in the project), if the material was not found or it was set to 'UIDZero', then default material from the editor terrain material slot will be used, if that material was not set, then the method will fail and the terrain will not be created
         Bool worldTerrainGetMaterial(C UID &world_id, C VecI2 &area_xy,                    MaterialMap &material                                             ); // get             terrain material at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, 'material' =material map (its         resolution will be "worldTerrainRes(world_id)")
         Bool worldTerrainSetMaterial(C UID &world_id, C VecI2 &area_xy,                  C MaterialMap &material                                             ); // set             terrain material at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, 'material' =material map (recommended resolution      is "worldTerrainRes(world_id)" however it will be automatically resized if different)
         Bool worldTerrainGet        (C UID &world_id, C VecI2 &area_xy,   Image &height,   MaterialMap &material,   Image *color=NULL                        ); // get             terrain          at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, this method gets terrain height, material and color all at the same time
         Bool worldTerrainSet        (C UID &world_id, C VecI2 &area_xy, C Image &height, C MaterialMap &material, C Image *color=NULL                        ); // set             terrain          at 'area_xy' area coordinates in specified world, 'world_id'=id of ELM_WORLD element in the project, false on fail, this method sets terrain height, material and color all at the same time, if 'color' is NULL then it will be set as fully white, each terrain must have a material specified

         // world objects
         Bool worldObjCreate (C UID &world_id, C Memp<ObjParams> &objs                                                                                                                                               ); // create objects in world, 'world_id'=id of ELM_WORLD element in the project, 'objs'=array of objects to create, false on fail
         Bool worldObjGetDesc(C UID &world_id,   Memp<ObjDesc  >  objs, C Memp<UID> &world_obj_ids=NULL, C RectI *areas=NULL, Bool only_selected=false, Bool include_removed=false                                   ); // get    objects in world, 'world_id'=id of ELM_WORLD element in the project, 'objs'=array of objects to fill with those from the world, 'world_obj_ids'=if get data only from the objects specified in this container (use NULL for all objects), 'areas'=get objects only from the specified world areas (use NULL for all areas), 'only_selected'=if get only objects that are currently selected, 'include_removed'=if include objects that were removed,                                                                          this method is much faster than the one below as it returns only basic data, false on fail
         Bool worldObjGetData(C UID &world_id,   Memp<ObjData  >  objs, C Memp<UID> &world_obj_ids=NULL, C RectI *areas=NULL, Bool only_selected=false, Bool include_removed=false, Bool include_removed_params=false); // get    objects in world, 'world_id'=id of ELM_WORLD element in the project, 'objs'=array of objects to fill with those from the world, 'world_obj_ids'=if get data only from the objects specified in this container (use NULL for all objects), 'areas'=get objects only from the specified world areas (use NULL for all areas), 'only_selected'=if get only objects that are currently selected, 'include_removed'=if include objects that were removed, 'include_removed_params'=if include object parameters that were removed, this method is slower      than the one above as it returns full       data, false on fail

         // world camera
         Bool worldCamGet(  Camera &cam); // get camera settings in the world editor, false on fail
         Bool worldCamSet(C Camera &cam); // set camera settings in the world editor, false on fail

         // world draw
         struct Line
         {
            Color color;
            Edge  edge;

            void save(File &f)C {f<<color<<edge;}
            Bool load(File &f)  {f>>color>>edge; return true;}

            Line& set(C Color &color, C Edge &edge) {T.color=color; T.edge=edge; return T;}

            Line(                            ) {}
            Line(C Color &color, C Edge &edge) {set(color, edge);}
         };
         Bool worldDrawLines(C Memp<Line> &lines); // request the world editor to draw specified lines, after you make this call, the world editor will draw the lines in each frame, if you no longer wish to draw lines, then call this method with empty container, false on fail

      // image
      Bool getImage(C UID &elm_id,   Image &image); // get image of 'elm_id' ELM_IMAGE element in the project, false on fail
      Bool setImage(C UID &elm_id, C Image &image); // set image of 'elm_id' ELM_IMAGE element in the project, false on fail

      // code
      Bool getCode(C UID &elm_id,   Str &code); // get source code of 'elm_id' ELM_CODE element in the project, false on fail
      Bool setCode(C UID &elm_id, C Str &code); // set source code of 'elm_id' ELM_CODE element in the project, false on fail

      // file
      Bool getFile(C UID &elm_id, File &data); // get data of 'elm_id' ELM_FILE ELM_SOUND ELM_VIDEO elements in the project, 'data' must be already opened for writing as the method will write  to it, false on fail
      Bool setFile(C UID &elm_id, File &data); // set data of 'elm_id' ELM_FILE ELM_SOUND ELM_VIDEO elements in the project, 'data' must be already opened for reading as the method will read from it, false on fail

      // mesh
      Bool getMesh(C UID &elm_id,   Mesh &mesh); // get mesh of 'elm_id' ELM_OBJ ELM_MESH elements in the project, false on fail
      Bool setMesh(C UID &elm_id, C Mesh &mesh); // set mesh of 'elm_id' ELM_OBJ ELM_MESH elements in the project, false on fail

      // application
      Bool activeApp(C UID      &elm_id); // set    active application of 'elm_id' ELM_APP element in the project, false on fail
      Bool exportApp(EXPORT_MODE mode  ); // export active application, false on fail

   // build settings
   Bool buildDebug(Bool     debug   ); // set build debug/release    configuration (true=debug   , false=release )
   Bool build32Bit(Bool     bit32   ); // set build    32/64 bit     configuration (true=32      , false=64      )
   Bool buildDX9  (Bool     dx9     ); // set build   DX9/DX10+      configuration (true=DX9     , false=DX10+   )
   Bool buildExe  (EXE_TYPE type    ); // set build executable type  configuration
   Bool buildPaths(Bool     relative); // set build export     paths configuration (true=relative, false=absolute)

private:
   Connection _conn;
};
/******************************************************************************/
Elm* FindElm(Memp<Elm> elms, C UID &elm_id               ); // find element with 'elm_id' ID                    , this function assumes that 'elms' is sorted by element ID's, NULL is returned if element was not found
Elm* FindElm(Memp<Elm> elms, C UID &elm_id, ELM_TYPE type); // find element with 'elm_id' ID and 'type' ELM_TYPE, this function assumes that 'elms' is sorted by element ID's, NULL is returned if element was not found or it had different type than requested
/******************************************************************************/
// SERVER SIDE
/******************************************************************************/
struct EditorServer : ConnectionServer
{
   STRUCT(Client , ConnectionServer::Client)
   //{
      Bool connection_version_ok;

      virtual Bool update();

      Client() {connection_version_ok=false;}
   };

   Client& client(int i) {return (Client&)clients.lockedData(i);}

   EditorServer() {clients.replaceClass<Client>();}
};
/******************************************************************************/
enum EDITOR_INTERFACE_COMMANDS
{
   EI_VERSION_CHECK,

   EI_GET_PROJECTS,
   EI_GET_PROJECT,
   EI_SET_PROJECT,

   EI_GET_DATA_PATH,

   EI_GET_ELMS,
   EI_GET_ELMS_SELECTED,
   EI_NEW_ELM,
   EI_NEW_WORLD,
   EI_SET_ELM_NAME,
   EI_SET_ELM_REMOVED,
   EI_SET_ELM_PUBLISH,
   EI_SET_ELM_PARENT,
   EI_SET_ELM_SRC_FILE,

   EI_GET_WORLD,
   EI_SET_WORLD,
   EI_GET_WORLD_AREA_SIZE,
   EI_GET_WORLD_TERRAIN_RES,
   EI_GET_WORLD_TERRAIN_AREAS,
   EI_DEL_WORLD_TERRAIN,
   EI_GET_WORLD_TERRAIN_IS,
   EI_GET_WORLD_TERRAIN_HEIGHT,
   EI_SET_WORLD_TERRAIN_HEIGHT,
   EI_GET_WORLD_TERRAIN_COLOR,
   EI_SET_WORLD_TERRAIN_COLOR,
   EI_GET_WORLD_TERRAIN_MATERIAL,
   EI_SET_WORLD_TERRAIN_MATERIAL,
   EI_GET_WORLD_TERRAIN,
   EI_SET_WORLD_TERRAIN,

   EI_NEW_WORLD_OBJ,
   EI_GET_WORLD_OBJ_BASIC,
   EI_GET_WORLD_OBJ_FULL,

   EI_GET_WORLD_CAM,
   EI_SET_WORLD_CAM,

   EI_DRAW_WORLD_LINES,

   EI_GET_IMAGE,
   EI_SET_IMAGE,
   EI_GET_CODE,
   EI_SET_CODE,
   EI_GET_FILE,
   EI_SET_FILE,
   EI_GET_MESH,
   EI_SET_MESH,
   EI_SET_ACTIVE_APP,
   EI_EXPORT_APP,

   EI_GET_PROJECTS_PATH,
   EI_SET_PROJECTS_PATH,

   EI_BUILD_DEBUG,
   EI_BUILD_32BIT,
   EI_BUILD_DX9  ,
   EI_BUILD_EXE  ,
   EI_BUILD_PATHS,

   EI_NUM,
};
/******************************************************************************/
} // namespace
/******************************************************************************/
