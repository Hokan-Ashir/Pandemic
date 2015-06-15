/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
namespace Game{
/******************************************************************************/
enum AREA_STATE
{
   AREA_UNLOADED, // the area is completely unloaded, it doesn't contain any data at all
   AREA_CACHE   , // the area has data loaded from the disk to the temporary memory, but not used in the game, objects are not listed in object containers, actors are not created
   AREA_INACTIVE, // the area has data loaded and used in the game, objects are listed in object containers however they're not updated or  drawn, all actors are frozen (set to kinematic and cannot move)
   AREA_ACTIVE  , // the area has data loaded and used in the game, objects are listed in object containers         and are     updated and drawn,     actors can be dynamic

   AREA_LOAD, // this state can be specified only for World.areaSetState, it converts state from AREA_UNLOADED to AREA_CACHE (if the state was not AREA_UNLOADED then it remains unmodified)
};
/******************************************************************************/
struct AreaPath2D
{
   Int resolution()C {return _map.w();}

   Bool        walkable(Int x, Int y               )C; // get if pixel is walkable, x=0..World.settings().path2DRes()-1, y=0..World.settings().path2DRes()-1
   AreaPath2D& walkable(Int x, Int y, Bool walkable) ; // set if pixel is walkable, x=0..World.settings().path2DRes()-1, y=0..World.settings().path2DRes()-1, after making all desired changes to paths you must call World.pathBuild once, any changes made aren't stored in the SaveGame (custom modifications need to be applied every time an Area is reloaded)

private:
   struct Neighbor
   {
      Byte a, b, cost;
   };
   Bool           _changed;
   Byte           _groups;
   Image          _map;
   Memc<Neighbor> _neighbor;

   AreaPath2D();
};
struct Path2DWalker
{
   Vec        target;
   Memc<Vec2> points;

   Path2DWalker& clear();
   Bool          find (C Vec &start, C Vec &target, C Vec *alternate_start=NULL);
};
/******************************************************************************/
struct Area // World Area
{
   struct Data // Data of an World Area
   {
      STRUCT(AreaObj , ObjParams)
      //{
         UID id;

         void save(File &f, CChar *path=NULL)C; // 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
         Bool load(File &f, CChar *path=NULL) ; // 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
      };

      struct TerrainObj
      {
         ObjParamsPtr obj;
         Matrix       matrix;
         Actor        actor;
         Int          mesh_variation;
      };

      struct GrassObj
      {
         struct Instance
         {
            Matrix matrix;
            Actor  actor ;
         };
         Bool           shrink;
         MeshPtr        mesh;
         Int            mesh_variation;
         PhysBodyPtr    phys;
         Memc<Instance> instances;

         GrassObj() {shrink=false;}
      };

      MeshGroup         mesh            ; // area mesh         , this can contain terrain and all terrain objects which are too big and needed to be split into smaller parts
      PhysBody          phys            ; // area physical body, this can contain terrain and all terrain objects which are too big and needed to be split into smaller parts
      Actor             actor           ; // area actor, created from the 'phys' member
      Memc<AreaObj    > objs            ; // list of all area objects which are not dynamic (their access is not ACCESS_CUSTOM), this does not include terrain objects which are too big and needed to be split into smaller parts (those objects are stored in the 'mesh' and 'phys' members)
      Memc<TerrainObj > terrain_objs    ; // list of all area objects of ACCESS_TERRAIN access, these objects are always taken from the 'objs' container ('terrain_objs' container is not stored in the area data file, instead it is always copied from 'objs' member at area load)
      Box               terrain_objs_box; // this covers all 'terrain_objs'
      Memc<GrassObj   > foliage_objs    ; // list of all area objects of ACCESS_GRASS   access, these objects are always taken from the 'objs' container ('foliage_objs' container is not stored in the area data file, instead it is always copied from 'objs' member at area load)
      Box               foliage_objs_box; // this covers all 'foliage_objs'
      Image             height          , // area height   map, each pixel value stores information about the height of the terrain
                        material_map    ; // area material map, each pixel value stores information about index of the most significant material in the 'materials' container, must be in sync with 'materials' member !!
      Mems<MaterialPtr> materials       ; // list of materials used by the terrain, must be in sync with 'material_map' member !!
      Memc<WaterMesh  > waters          ; // area water meshes
      Memc<Decal      > decals          ; // area decals
      Memc<MeshOverlay> mesh_overlays   ; // area mesh overlays

      Area    & area    () {return *_area     ;} // get area containing this data
      PathMesh* pathMesh() {return  _path_mesh;} // get area path mesh

      // custom interface
         // operations
         virtual void customSetShader() {} // reset shader of custom meshes stored inside area data

         // draw
         virtual UInt customDrawPrepare () {return 0;} // draw custom area data
         virtual void customDrawShadow  () {         } // draw custom area data
         virtual void customDrawBlend   () {         } // draw custom area data in RM_BLEND    mode
         virtual void customDrawPalette () {         } // draw custom area data in RM_PALETTE  mode
         virtual void customDrawPalette1() {         } // draw custom area data in RM_PALETTE1 mode

         // switching states
         virtual void customLoad         (File &f, CChar *chunk_name, UInt chunk_ver) {} // this is called when area is switching state from (AREA_UNLOADED               ) to (AREA_CACHE                  ), in this method you should load custom data using chunks from "game world", this method will be called by the engine on secondary thread, since physics simulation may be running on the main thread - you may not create/modify any physical objects in this method (actors, joints, ragdolls, ..) the only exception are physical bodies which can be created/loaded
         virtual void customUnloadToCache(                                          ) {} // this is called when area is switching state from (AREA_ACTIVE or AREA_INACTIVE) to (AREA_CACHE                  ), in this method you must delete all actors
         virtual void customLoadFromCache(                                          ) {} // this is called when area is switching state from (AREA_CACHE                  ) to (AREA_ACTIVE or AREA_INACTIVE), in this method you must create all actors
         virtual void customDeactivate   (                                          ) {} // this is called when area is switching state from (AREA_ACTIVE                 ) to (AREA_INACTIVE               ), in this method you must turn dynamic   actors into kinematic actors
         virtual void customActivate     (                                          ) {} // this is called when area is switching state from (AREA_INACTIVE               ) to (AREA_ACTIVE                 ), in this method you may  turn kinematic actors into dynamic   actors

         // saving area changes
         virtual Bool customSaveWant(               ) {return false;} // you can override this method and return true, this will cause saving the full Area into the game world folder
         virtual void customSave    (ChunkWriter &cw) {             } // you can override this method and within save custom chunks of data, this method will be called only if 'customSaveWant' returned true

               Data(Area &area);
      virtual ~Data();

      AreaPath2D* path2D() {return _path2D;} // get area path 2D

   private:
      Area       *_area;
      Int         _path_node_offset;
      PathMesh   *_path_mesh;
      AreaPath2D *_path2D;

      NO_COPY_CONSTRUCTOR(Data);
   };

   Bool         visited   (                            )C {return  _visited    ;} // if  area has been visited before
   VecI2        xz        (                            )C {return  _xz         ;} // get area coordinates
   AREA_STATE   state     (                            )C {return  _state      ;} // get current area state
   Int          objs      (                            )C {return  _objs.elms();} // get number of objects in the area (this includes only dynamic objects of ACCESS_CUSTOM access, all other objects are stored in 'Game.Area.Data')
   Obj&         obj       (  Int   i                   )C {return *_objs[i]    ;} // get i-th      object  in the area (this includes only dynamic objects of ACCESS_CUSTOM access, all other objects are stored in 'Game.Area.Data')
   Flt          hmHeight  (C Vec2 &xz, Bool smooth=true)C;                        // get heightmap height   at 'xz' world position,    0 on fail, this method is fast because it uses lookup table ('Game.Area.Data.height'       Image), 'smooth'=if calculate smooth value using linear interpolation
 C MaterialPtr& hmMaterial(C Vec2 &xz                  )C;                        // get heightmap material at 'xz' world position, NULL on fail, this method is fast because it uses lookup table ('Game.Area.Data.material_map' Image)

   Data*    data() {return _data;}   T1(TYPE) TYPE*    data() {return CAST(TYPE,   _data  );} // get Area::Data (don't create data if it's NULL)
   Data* getData();                  T1(TYPE) TYPE* getData() {return CAST(TYPE, getData());} // get Area::Data (      create data if it's NULL, NULL can still be returned if this area has AREA_UNLOADED state)

   virtual ~Area();
            Area(C VecI2 &xy, Ptr grid_user);

private:
   Bool       _visited, _temp;
   VecI2      _xz       ;
   AREA_STATE _state    ;
   Memc<Obj*> _objs     ;
   File       _saved_obj;
   Data      *_data     ;
   NO_COPY_CONSTRUCTOR(Area);
};
/******************************************************************************/
} // namespace
/******************************************************************************/
