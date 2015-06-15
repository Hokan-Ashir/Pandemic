/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'PathMesh' to specify a path mesh for a single area.

   Use 'PathWorld' for pathfinding on many 'PathMesh'es.

   Use 'PathObstacle' for temporary obstacles in 'PathWorld's.

/******************************************************************************/
enum PATH_MESH_TYPE
{
   PM_OBSTACLE, // can not be crossed
   PM_GROUND  , // can     be crossed if traveller supports PMF_WALK
   PM_WATER   , // can     be crossed if traveller supports PMF_SWIM
};
enum PATH_MESH_FLAG
{
   PMF_WALK=0x0001,
   PMF_SWIM=0x0002,
};
/******************************************************************************/
struct PathSettings
{
   Flt areaSize  ()C {return _area_size;}   PathSettings& areaSize  (Flt size ); // get/set area size         (in meters ), 0..Inf , default=32
   Flt ctrlRadius()C {return _ctrl_r   ;}   PathSettings& ctrlRadius(Flt r    ); // get/set controller radius (in meters ), 0..Inf , default=0.33f
   Flt ctrlHeight()C {return _ctrl_h   ;}   PathSettings& ctrlHeight(Flt h    ); // get/set controller height (in meters ), 0..Inf , default=2.0f
   Flt  maxClimb ()C {return _max_climb;}   PathSettings&  maxClimb (Flt climb); // get/set max climb  height (in meters ), 0..Inf , default=0.7f
   Flt  maxSlope ()C {return _max_slope;}   PathSettings&  maxSlope (Flt slope); // get/set max slope  angle  (in radians), 0..PI_2, default=PI_4
   Flt cellSize  ()C {return _cell_size;}   PathSettings& cellSize  (Flt size ); // get/set path cell  size   (in meters ), 0..Inf , default=1.0f/3
   Flt cellHeight()C {return _cell_h   ;}   PathSettings& cellHeight(Flt h    ); // get/set path cell  height (in meters ), 0..Inf , default=0.1f

   // operations
   PathSettings& reset(); // reset to default settings

   Bool operator==(C PathSettings &path)C; // if settings are equal
   Bool operator!=(C PathSettings &path)C; // if settings are different

   // io
   void save(File &f)C; // save to   file
   Bool load(File &f) ; // load from file, false on fail

   PathSettings() {reset();}

private:
   Flt _area_size, _ctrl_r, _ctrl_h, _max_climb, _max_slope, _cell_size, _cell_h;
};
/******************************************************************************/
struct PathObstacle
{
   // manage
   void del   ();                                        // delete manually                                                         , deleting an obstacle requires rebuilding path meshes (avoid calling this frequently as it may decrease performance)
   Bool create(C Shape &shape, C PathWorld *world=NULL); // create path obstacle from 'shape' in 'world' (NULL for Game::World.path), creating an obstacle requires rebuilding path meshes (avoid calling this frequently as it may decrease performance)

   // get / set
   Shape shape(              ); // get obstacle shape, SHAPE_NONE on fail (if doesn't exist)
   void  shape(C Shape &shape); // set obstacle shape, adjusting the shape of the obstacle requires rebuilding path meshes (avoid calling this frequently as it may decrease performance), only following shape types are supported: SHAPE_POINT, SHAPE_EDGE, SHAPE_BOX, SHAPE_BALL, SHAPE_CAPSULE, SHAPE_TUBE, SHAPE_OBOX, SHAPE_PYRAMID, attempting to set a different type of shape is equivalent to calling 'del' method

  ~PathObstacle() {del();}
   PathObstacle() {_world=NULL; _shape=NULL;}

private:
   PathWorld *_world;
   Shape     *_shape;
   NO_COPY_CONSTRUCTOR(PathObstacle);
};
/******************************************************************************/
struct PathMesh
{
   // manage
   void del   (); // delete manually
   Bool create(MeshBase &mesh, C VecI2 &area_xy, C PathSettings &settings); // build path mesh from source 'mesh', at 'area_xy' area coordinates using 'settings' path build settings, false on fail ("mesh.tri.flag" and "mesh.quad.flag" can be manually set to PATH_MESH_TYPE to specify the type of the face)

   // get
   Bool is()C; // if has any mesh data

   // operation
   void preSave(); // saving 'PathMesh' typically requires compressing some data, which may take some time, you can call this method at an earlier stage to compress and prepare the data so saving later will be without any delays, this method is optional and does not need to be called

   // io
   void save(File &f)C; // save to   file
   Bool load(File &f) ; // load from file, false on fail

  ~PathMesh();
   PathMesh();

private:
   Ptr _pm;
   NO_COPY_CONSTRUCTOR(PathMesh);
};
/******************************************************************************/
const_mem_addr struct PathWorld // !! must be stored in constant memory address !!
{
   // manage
   void del   (             ); // delete manually
   Bool create(Flt area_size); // initialize path world manager, 'area_size'=size of a single area (in meters), false on fail

   // operations
   Bool set(PathMesh *path_mesh, C VecI2 &area_xy); // set 'path_mesh' at specified 'area_xy' area coordinates (can be NULL for no path mesh at that location)

   // get
   Flt areaSize()C {return _area_size;} // get area size

   Bool find(C Vec &start, C Vec &end, Memp<Vec> path, Int max_steps=-1, UInt walkable_flags=PMF_WALK, Bool allow_partial_paths=true, C Vec &end_extents=Vec(1, 16, 1))C; // find path from 'start' to 'end' world position, 'max_steps'=maximum number of allowed steps in the result path (use <=0 for unlimited), 'walkable_flags'=faces that are walkable (PATH_MESH_FLAG), 'allow_partial_paths'=if there is no direct path from 'start' to 'end' then return partial path to the point closest to the 'end', false on fail (path not found), 'end_extents'=extents used to find nearest walkable surface to the 'end' point

   Bool nearestSurface(C Vec &pos, C Vec &extents, Vec &surface_pos, UInt walkable_flags=PMF_WALK)C; // find nearest point on path surface, 'pos'=center position of the search, 'extents'=maximum distance to search in each dimension, 'surface_pos'=output position, 'walkable_flags'=faces that are walkable (PATH_MESH_FLAG), false on fail (point not found)

   Bool nearestWall(C Vec &pos, Flt max_distance, Flt *hit_distance=NULL, Vec *hit_pos=NULL, Vec *hit_normal=NULL, UInt walkable_flags=PMF_WALK)C; // calculate distance to nearest wall from 'pos' position, 'max_distance'=maximum distance to perform the search, 'hit_distance'=distance to wall, 'hit_pos'=hit position, 'hit_normal'=hit normal, 'walkable_flags'=faces that are walkable (PATH_MESH_FLAG), false on fail (wall not found)

   Bool ray(C Vec &start, C Vec &end, Flt *hit_frac=NULL, Vec *hit_pos=NULL, Vec *hit_normal=NULL, UInt walkable_flags=PMF_WALK)C; // perform a ray test on the path surface starting from 'start' towards 'end', 'hit_frac'=fraction of the movement (0..1), 'hit_pos'=hit position, 'hit_normal'=hit normal, 'walkable_flags'=faces that are walkable (PATH_MESH_FLAG), false on fail (no hit occured)

   // draw
   void draw(Byte surface_color_alpha=64, Flt y_offset=0, C Color &outer_edge_color=Color(0,48,64,220), C Color &inner_edge_color=Color(0,48,64,32))C; // 'y_offset'=vertical offset applied when drawing paths (can be set to positive value to draw the paths above the ground, so they will not be occluded by ground meshes)

  ~PathWorld() {del();}
   PathWorld() {_area_size=_ctrl_r=_ctrl_h=0; _mesh=NULL; _query=NULL; _filter=NULL;}

private:
   Flt         _area_size, _ctrl_r, _ctrl_h;
   Ptr         _mesh, _query, _filter;
	Memc<Ptr>   _changed;
   Memx<Shape> _obstacles;
   NO_COPY_CONSTRUCTOR(PathWorld);
};
/******************************************************************************/
