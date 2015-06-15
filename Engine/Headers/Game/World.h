/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'World' to automatically manage the game world and game objects.
      It handles:
         -paging
         -updating
         -rendering
         -saving
         -loading

/******************************************************************************/
namespace Game{
/******************************************************************************/
T1(TYPE) struct ObjMap // Container for Game Objects, this is the same thing as 'Map<UID, TYPE>', except without the control of manual adding new elements, which should be handled by 'WorldManager' (through "World.objCreate")
{
   ObjMap& clear(); // remove all objects

   Int elms   ()C; // number of valid objects
   Int elmSize()C; // size   of       object (excluding the UID KEY)

   TYPE& operator[](Int i) ; // get i-th object
 C TYPE& operator[](Int i)C; // get i-th object

   Bool containsId (C UID  &obj_id)C; // if container contains       object with 'obj_id' ID
   Bool containsObj(C TYPE *obj   )C; // if container contains 'obj' object

   TYPE* find(C UID &obj_id); // find object by its ID, NULL on fail

   ObjMap& remove   (  Int   i     ); // remove i-th object from container
   ObjMap& removeId (C UID  &obj_id); // remove      object from container by its ID
   ObjMap& removeObj(C TYPE *data  ); // remove      object from container by its memory address

   // misc
   T1(BASE) operator   ObjMap<BASE>&() ; // casting to container of 'BASE' objects, 'TYPE' must be extended from BASE
   T1(BASE) operator C ObjMap<BASE>&()C; // casting to container of 'BASE' objects, 'TYPE' must be extended from BASE

   explicit ObjMap(Int block_elms=32);

private:
   Map<UID, TYPE> _map;
};
/******************************************************************************/
enum WORLD_MODE // World Mode
{
   WORLD_STREAM, // streamed world (areas are loaded and unloaded depending on their distance to center of action inside "World.update" method, those close to center of action are automatically loaded, those far away are unloaded, recommended for most games)
   WORLD_FULL  , // full     world (at start full world is loaded with all areas, may consume lots of memory, recommended for race games with fast travelling objects, where any loading pauses are unacceptable)
   WORLD_MANUAL, // manual   world (areas are not managed automatically, they can be loaded and unloaded only by manual use of "World.areaSetState" method)
};
/******************************************************************************/
struct WorldSettings // World Settings
{
   EnvironmentPtr environment; // default environment settings for this world, defualt=NULL

   Flt   areaSize()C {return _area_size ;}   WorldSettings&   areaSize(Flt size); // get/set area size           , 0..Inf, default=32
   Int     hmRes ()C {return _hm_res    ;}   WorldSettings&     hmRes (Int res ); // get/set heightmap resolution, 2..129, default=65, setting resolution will automatically align the value to the "(nearest power of 2)+1"
   Int path2DRes ()C {return _path2d_res;}   WorldSettings& path2DRes (Int res ); // get/set 2d paths  resolution, 1..128, default=32

   // operations
   WorldSettings& reset(); // reset to default values

   // io
   void save(File &f, CChar *path=NULL)C; // save to   file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f, CChar *path=NULL) ; // load from file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   Bool save(C Str &name)C; // save to   file, false on fail
   Bool load(C Str &name) ; // load from file, false on fail

   WorldSettings() {reset();}

private:
   Flt _area_size;
   Int _hm_res, _path2d_res;
};
/******************************************************************************/
struct WorldManager // World Manager
{
   Bool update_objects_after_physics, // this specifies which should be updated first - objects or the physics, default=true (setting it to false may occur in lack of synchronization between the character mesh and its controller when using Physics.draw, false is required for synchronization of character physical clothing)
        use_background_loading      , // if enabled then nearby areas will be loaded to memory on a secondary thread, which will allow smooth travelling across big worlds without pauses for loading data, default=true (for Mobile platforms the default value is set to "Cpu.cores()>=2")
        use_early_z_for_terrain     , // if enable early-z rendering technique when drawing terrain, enabling early-z causes the terrain to be rendered additional time (to the depth buffer only), this has the cost of rendering the terrain additional time, however it can be beneficial if rendering will occlude other parts of the screen preventing from performing some pixel shader operations at later stage, whether this option should be enabled or disabled that depends on your world, and should be tested manually
        low_memory_usage            ; // if release resources every time they're not needed, enabling this may decrease memory usage however it will decrease loading times when loading areas/changing worlds, default=false

   MiniMap mini_map; // this is automatically managed by the World Manager, use it to access the maps for certain areas, however do not store references to returned images, because they may get deleted in 'Game::World.update'

   Secure *area_secure; // pointer to custom Secure object (default=NULL) used for encrypting area files in case they are stored as stdio files (if they are stored in paks, then this secure is ignored)

   void (*link_references)(); // pointer to custom function (may be NULL) called when new objects have been loaded, and there is possibility that they should be linked with custom global 'Reference's, you can set this to a custom function and inside it manually call Reference::link for all global 'Reference's (do not use this for 'Reference's stored inside 'Game::Obj' classes, as they should be linked inside 'Game::Obj::linkReferences' method)
   void (*physics_update )(); // pointer to custom function (may be NULL) called when frame physics simulation has ended. 'WorldManager.update' method automatically handles physics simulation updates. If 'physics_update' is not NULL then it will be called after 'Physics.stopSimulation' and before 'Physics.startSimulation'. This function can be useful when physics is being processed in a background thread, and you need to precisely access/modify actor parameters when the simulation is not being processed. For example, if physics simulation is processed in background thread (that processing could occur during entire frame) and on the main thread you wish to adjust actor velocities, then the simulation may not behave the same every time and may not be precise, due to the fact of adjusting actor parameters when the simulation is already running at unknown stage in background thread. To overcome this issue and gain ability of precise adjusting of actor values you can set this callback, which will be called when the simulation is at the moment not running in the background thread.

   // init
   T1(TYPE) WorldManager& setAreaClass(                                   ) { _grid.replaceClass<TYPE>(                                ); return T;} // set class responsible for areas    , TYPE must be extended from Game::Area
   T1(TYPE) WorldManager& setAreaData (                                   ) {return _setAreaData<TYPE>(                                );          } // set class responsible for area data, TYPE must be extended from Game::Area::Data
   T1(TYPE) WorldManager& setObjType  (ObjMap<TYPE> &obj_map, Int obj_type) {return _setObjType       (obj_map, obj_type, CType<TYPE>());          } // set memory container responsible for selected OBJ_TYPE

   // manage
   WorldManager& free  (                                                                  ); // manually free   cached  memory, you don't need to call this unless you wish to free some extra memory
   WorldManager& del   (  Bool  free=false                                                ); // manually delete current world, 'free'=if automatically call 'free' to release helper memory
   Bool          NewTry(C Str  &world_name                                                ); // initialize new world from 'world_name' name   , false on fail
   Bool          NewTry(C UID  &world_id                                                  ); // initialize new world from 'world_id'   name id, false on fail
   WorldManager& New   (C Str  &world_name                                                ); // initialize new world from 'world_name' name   , Exit  on fail
   WorldManager& New   (C UID  &world_id                                                  ); // initialize new world from 'world_id'   name id, Exit  on fail
   Bool          load  (  File &f                                                         ); // load previously saved world state from 'f'         file, false on fail
   void          save  (  File &f                                                         ); // save active           world state to   'f'         file,
   Bool          load  (C Str  &save_name, Bool (*load)(File &f)=NULL, Secure *secure=NULL); // load previously saved world state from 'save_name' file, 'load'=pointer to fuction loading custom save data (it must return false on fail), false on fail
   Bool          save  (C Str  &save_name, void (*save)(File &f)=NULL, Secure *secure=NULL); // save active           world state to   'save_name' file, 'save'=pointer to fuction  saving custom save data                               , false on fail

   static void Create(C Str &world_name, C WorldSettings &settings); // create folders for empty game world so it can be loaded using 'New' method, and save its settings

   // get / set
   Bool           is           (               )C {return _name.is()          ;} // if  there is any world specified
 C UID&           id           (               )C {return _id                 ;} // get name id               of current world
 C Str&           name         (               )C {return _name               ;} // get name                  of current world
 C Str&           dataPath     (               )C {return _data_path          ;} // get data path             of current world
 C WorldSettings& settings     (               )C {return _settings           ;} // get settings              of current world
   Flt            areaSize     (               )C {return _settings.areaSize();} // get size of a single Area of current world
 C PathWorld&     path         (               )C {return _path               ;} // get path finder           of current world
   WORLD_MODE     mode         (               )C {return _mode               ;} // get manager mode, default=WORLD_STREAM
   WorldManager&  mode         (WORLD_MODE mode);                                // set manager mode, changing mode requires current world to be deleted first
   Flt            activeRange  (               )C {return _range              ;} // get Worlds Active Range, default value is set in 'init' method
   WorldManager&  activeRange  (Flt       range);                                // set Worlds Active Range
   Flt            objUpdateTime(               )C {return _time_obj_update    ;} // get amount of CPU time which was needed to update all objects during last world update

   Vec2  areaToWorld(C VecI2 &xz  )C {return                                      xz*areaSize() ;} // convert Area  Coordinates to World Position in meters
   VecI2 worldToArea(C Vec2  &xz  )C {return                                Floor(xz/areaSize());} // convert World Position    to Area  Coordinates
   VecI2 worldToArea(C Vec   &pos )C {return                              worldToArea(pos .xz());} // convert World Position    to Area  Coordinates
   RectI worldToArea(C Rect  &rect)C {return RectI(worldToArea(rect.min), worldToArea(rect.max));} // convert World Position    to Area  Coordinates
   RectI worldToArea(C Box   &box )C {return RectI(worldToArea(box .min), worldToArea(box .max));} // convert World Position    to Area  Coordinates

   // area
   struct AreaState
   {
      VecI2      xz   ; // xz coordinates of Area
      AREA_STATE state; // desired state  of Area

      void set(C VecI2 &xz, AREA_STATE state) {T.xz=xz; T.state=state;}

      AreaState(C VecI2 &xz=VecI2(0, 0), AREA_STATE state=AREA_UNLOADED) {set(xz, state);}
   };
   void  areaSetState (C Memp<AreaState> &area_states, Bool unload_remaining=false); // manually set the state of areas, this method can be used for WORLD_MANUAL (for other modes it is ignored), 'area_states'=list of area coordinates and their desired states, 'unload_remaining'=if automatically unload all areas that aren't included in the 'area_states' list
   Int   areaActiveNum(           )C; // get number of active areas
   Area* areaActive   (  Int    i )C; // get i-th      active area                         , if the index is out of range                                  then NULL is returned
   Area* areaActive   (C VecI2 &xz)C; // get           active area at 'xz' area coordinates, if the area doesn't exist or isn't active at that coordinates then NULL is returned (which means that only area with                          AREA_ACTIVE state can be returned)
   Area* areaLoaded   (C VecI2 &xz)C; // get           loaded area at 'xz' area coordinates, if the area doesn't exist or isn't loaded at that coordinates then NULL is returned (which means that only area with AREA_CACHE AREA_INACTIVE AREA_ACTIVE state can be returned)

   // heightmap
   Flt          hmHeight  (C Vec2 &xz, Bool smooth=true); // get world heightmap height   at 'xz' world 2D position,    0 on fail, this method is fast because it uses lookup table (Game::Area::Data::height      Image), see also 'Game::Area::hmHeight  ', 'smooth'=if calculate smooth value using linear interpolation
 C MaterialPtr& hmMaterial(C Vec2 &xz                  ); // get world heightmap material at 'xz' world 2D position, NULL on fail, this method is fast because it uses lookup table (Game::Area::Data::materialMap Image), see also 'Game::Area::hmMaterial'

   // water
 C WaterMtrlPtr& waterUnder(C Vec &pos, Flt *depth=NULL); // test if 'pos' world position is under water, 'depth'=optional parameter which can receive point under water depth if it is under water, if 'pos' is underwater then the method will return water material in which the position is located, if not underwater then NULL is returned

   Waypoint* findWaypoint(C Str &name) {return name.is   () ? Waypoints.get(dataPath()+"Waypoint/"+name              ) : NULL;} // find waypoint in this world, NULL on fail
   Waypoint* findWaypoint(C UID &id  ) {return id  .valid() ? Waypoints.get(dataPath()+"Waypoint/"+EncodeFileName(id)) : NULL;} // find waypoint in this world, NULL on fail
   Waypoint*  getWaypoint(C Str &name) {return name.is   () ? Waypoints    (dataPath()+"Waypoint/"+name              ) : NULL;} // get  waypoint in this world, Exit on fail
   Waypoint*  getWaypoint(C UID &id  ) {return id  .valid() ? Waypoints    (dataPath()+"Waypoint/"+EncodeFileName(id)) : NULL;} // get  waypoint in this world, Exit on fail

   // objects
   Obj* objCreateNear(              ObjParams &obj_params   , C Matrix &matrix, C UID *obj_id=NULL); // dynamically create object into world from 'obj_params' object parameters and desired matrix, 'matrix' scale will be used as objects scale, method fails    if 'matrix' is out of active range                                     , 'obj_id'=optional parameter specifying forcing custom object id for the object (the parameter can be useful if you've created an object on the server, and need to create it on client using the same id from the server, if the parameter is not specified then object id will be randomized), NULL  on fail
   Bool objCreate    (              ObjParams &obj_params   , C Matrix &matrix, C UID *obj_id=NULL); // dynamically create object into world from 'obj_params' object parameters and desired matrix, 'matrix' scale will be used as objects scale, method succeeds if 'matrix' is out of active range but pointer to object isn't returned, 'obj_id'=optional parameter specifying forcing custom object id for the object (the parameter can be useful if you've created an object on the server, and need to create it on client using the same id from the server, if the parameter is not specified then object id will be randomized), false on fail
   Bool objInject    (Int obj_type, File      &obj_save_data, C Vec    *pos                       ); // dynamically inject object into world from previously saved object data (using 'Obj::save'), 'obj_type'=OBJ_TYPE, 'pos'=optional parameter to specify new position after loading the object (if NULL is passed then position will not be modified), false on fail

          Obj* moveWorldObjToStorage  (Obj &  world_obj, Memx<Obj> &    storage                            ); // move   'world_obj' world   object into a custom 'storage' object container, this function will be performed only if   'world_obj' belongs to this world    and 'storage' is a container                   storing exactly the same type as the   'world_obj', if those conditions are met then the object will have its 'willBeMovedFromWorldToStorage' method called, then it will be removed from        world  and placed in the storage   , then it will have its 'memoryAddressChanged' method called followed by 'wasMovedFromWorldToStorage' and address of the object (now inside the     storage container) will be returned, if this method fails then NULL  is returned and no operation is performed
         Bool  moveStorageObjToWorld  (Obj &storage_obj, Memx<Obj> &    storage, C Matrix  *obj_matrix=NULL); // move 'storage_obj' storage object into world                              , this function will be performed only if 'storage_obj' belongs to     'storage' and  world    is capable (see 'setObjType') of storing exactly the same type as the 'storage_obj', if those conditions are met then the object will have its 'willBeMovedFromStorageToWorld' method called, then it will be removed from      storage  and placed in the world     , then it will have its 'memoryAddressChanged' method called followed by 'wasMovedFromStorageToWorld' and true                                                         will be returned, if this method fails then false is returned and no operation is performed, 'obj_matrix'=optional parameter specifying new object matrix applied to the object when being moved to world (it's not applied if it's NULL or this method returned false)
   static Obj* MoveStorageObjToStorage(Obj &storage_obj, Memx<Obj> &src_storage, Memx<Obj> &dest_storage   ); // move 'storage_obj' storage object from 'src_storage' into 'dest_storage'  , this function will be performed only if 'storage_obj' belongs to 'src_storage' and 'storage' is a container                   storing exactly the same type as the 'storage_obj', if those conditions are met then the object                                                                      will be removed from 'src_storage' and placed in 'dest_storage', then it will have its 'memoryAddressChanged' method called                                          and address of the object (now inside the new storage container) will be returned, if this method fails then NULL  is returned and no operation is performed

   WorldManager& objGetAdd(Memp<Obj*> objects, C Ball    &ball   , Int obj_type=-1);                                                                 // get pointers to objects which position (Obj::pos) is inside 'ball'   , process only objects with 'obj_type' OBJ_TYPE (-1=process all types), this function does not clear 'objects' container at start which means that objects are added to the container
   WorldManager& objGetAdd(Memp<Obj*> objects, C Capsule &capsule, Int obj_type=-1);                                                                 // get pointers to objects which position (Obj::pos) is inside 'capsule', process only objects with 'obj_type' OBJ_TYPE (-1=process all types), this function does not clear 'objects' container at start which means that objects are added to the container
   WorldManager& objGetAdd(Memp<Obj*> objects, C Box     &box    , Int obj_type=-1);                                                                 // get pointers to objects which position (Obj::pos) is inside 'box'    , process only objects with 'obj_type' OBJ_TYPE (-1=process all types), this function does not clear 'objects' container at start which means that objects are added to the container
   WorldManager& objGetAdd(Memp<Obj*> objects, C OBox    &obox   , Int obj_type=-1);                                                                 // get pointers to objects which position (Obj::pos) is inside 'obox'   , process only objects with 'obj_type' OBJ_TYPE (-1=process all types), this function does not clear 'objects' container at start which means that objects are added to the container
   WorldManager& objGet   (Memp<Obj*> objects, C Ball    &ball   , Int obj_type=-1) {objects.clear(); return objGetAdd(objects, ball   , obj_type);} // get pointers to objects which position (Obj::pos) is inside 'ball'   , process only objects with 'obj_type' OBJ_TYPE (-1=process all types)
   WorldManager& objGet   (Memp<Obj*> objects, C Capsule &capsule, Int obj_type=-1) {objects.clear(); return objGetAdd(objects, capsule, obj_type);} // get pointers to objects which position (Obj::pos) is inside 'capsule', process only objects with 'obj_type' OBJ_TYPE (-1=process all types)
   WorldManager& objGet   (Memp<Obj*> objects, C Box     &box    , Int obj_type=-1) {objects.clear(); return objGetAdd(objects, box    , obj_type);} // get pointers to objects which position (Obj::pos) is inside 'box'    , process only objects with 'obj_type' OBJ_TYPE (-1=process all types)
   WorldManager& objGet   (Memp<Obj*> objects, C OBox    &obox   , Int obj_type=-1) {objects.clear(); return objGetAdd(objects, obox   , obj_type);} // get pointers to objects which position (Obj::pos) is inside 'obox'   , process only objects with 'obj_type' OBJ_TYPE (-1=process all types)

   Obj* objFindById(C UID &obj_id, Int obj_type=-1); // find world object by its Unique ID (this is the ID of the world object itself, and not its base object or class), 'obj_type'=OBJ_TYPE of the object (or if you don't know it, then use -1), NULL on fail (if not found)

   // terrain
   WorldManager& terrainAddDecal  (C Color &color, C MaterialPtr &material, C Matrix &  decal_matrix, Flt time_to_fade_out=10); // add a Decal       to current Worlds terrain
   WorldManager& terrainAddOverlay(                C MaterialPtr &material, C Matrix &overlay_matrix, Flt time_to_fade_out=10); // add a MeshOverlay to current Worlds terrain

   // path
   AreaPath2D* path2DGet     (C VecI2 &xz ); // get pointer to Area paths at given Area coordinates, returns NULL when path's don't exist at specified coordinates
   Bool        path2DWalkable(C Vec   &pos); // check if path is walkable at specified world position
   void        path2DBuild   (            ); // call this once after making changes to AreaPath2D's to rebuild the path database

   // update
   Bool updated       (           ) {return _updated        ;} // if current world has been updated at least once since it was loaded, you can use this method to startup loading screen
   Flt  updateProgress(           ) {return _update_progress;} // get update progress (0..1), this can be called in a secondary thread to access the progress of updating the world using 'update' method
   void updateBreak   (           );                           // break updating, this can be called from a secondary thread to break any current world updating, for example if during loading a world the user requests quitting the game, you can break the loading and exit immediately
   void update        (C Vec2 &xz );                           // update, 'xz' =x and z coordinates of center of action (in meters), the parameter is used only for WORLD_STREAM mode (for other modes it is ignored)
   void update        (C Vec  &pos) {update(pos.xz());}        // update, 'pos'=                       center of action (in meters), the parameter is used only for WORLD_STREAM mode (for other modes it is ignored)
   // World update automatically loads all needed areas located nearby the center of action (and unloads those which are too far away).
   // Additionally it calls the following methods:
   //    D.grassUpdate()
   //    Physics.startSimulation().stopSimulation()
   //    Obj::update() on all active game objects (which are located in AREA_ACTIVE areas)

   // draw
   void draw(); // call this inside Render function for every RENDER_MODE

  ~WorldManager();
   WorldManager();

private:
   struct ObjContainer
   {
      CPtr         type;
      ObjMap<Obj> *map ;
   };
   struct Resources
   {
      Memc<MaterialPtr       > materials;
      Memc<WaterMtrlPtr      > water_mtrls;
      Memc<PhysBodyPtr       > phys_bodies;
      Memc<MeshPtr           > meshes;
      Memc<Game::ObjParamsPtr> objects;
      Memc<EnvironmentPtr    > environments;
   };

   UID        _id;
   Str        _name,
              _data_path;
   WORLD_MODE _mode;

   Bool _updated, _update_break;
   Byte _update_count;
   Flt  _update_progress;
   Int  _areas_to_load;

   Int                _rangei, _rangei2, _rangei2_inactive, _rangei2_cache;
   Flt                _range;
   Vec2               _xz;
   VecI2              _xzi;
   Memc<ObjContainer> _obj_container;
   Memc<Obj        *> _obj_newly_added;
   Memc<VecI2       > _area_row_min_max_x;
   RectI              _area_active_rect, _area_loaded_rect;
   Memc<Area       *> _area_active    , _area_draw, _area_draw_shadow, _area_draw_temp, _area_draw_mirror,
                      _area_inactive  ,
                      _area_cache     ,
                      _area_background;
   Area::Data&      (*_area_data)(Area::Data* &data, Area &area);
   Grid<Area>         _grid;
   PathWorld          _path;
   WorldSettings      _settings;
   Resources          _resources;

   UInt     _path_iteration;
   PathFind _path_find;
  _Memc     _path_node, _path_neighbor;

   CritSect  _cs;
   Thread    _thread;
   SyncEvent _thread_event;

   struct Decal2       : Decal       {Flt time;};   Memc<Decal2      > _decals       ;
   struct MeshOverlay2 : MeshOverlay {Flt time;};   Memc<MeshOverlay2> _mesh_overlays;

   Flt _time_area_update_state,

       _time_area_update_state_now ,
       _time_area_update_state_back,
       _time_area_update_state_path,
       
       _time_area_update_state_unload_cache,
       _time_area_update_state_unload,
       _time_area_update_state_load,
       _time_area_update_state_load_data,
       _time_area_update_state_activate,
       _time_area_update_state_deactivate,

       _time_obj_update;

   T1(TYPE) static Area::Data& NewAreaData(Area::Data* &data, Area &area) {data=new TYPE(area); return *data;}
   T1(TYPE) WorldManager& _setAreaData() {ASSERT_BASE_EXTENDED<Area::Data, TYPE>(); _area_data=NewAreaData<TYPE>; return T;}
            WorldManager& _setObjType (ObjMap<Obj> &obj_map, Int obj_type, CPtr c_type);
   T1(TYPE) friend struct EE::Reference;
   NO_COPY_CONSTRUCTOR(WorldManager);
};extern WorldManager
   World; // Main World
/******************************************************************************/
} // namespace
/******************************************************************************/
