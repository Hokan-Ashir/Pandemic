/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct BlocksOcclusion // helper class used for Blocks Ambient Occlusion calculation
{
   enum COMBINE_MODE // Combine Mode
   {
      ADD,
      MAX,
   };

   // get
   Int  steps    ()C {return _steps   [0];} // get number of steps    set during creation
   Int  steps1   ()C {return _steps   [1];} // get number of steps    set during creation
   Flt  strength ()C {return _strength[0];} // get occlusion strength set during creation
   Flt  strength1()C {return _strength[1];} // get occlusion strength set during creation
   Bool angles   ()C {return _angles     ;}
   Int  maxSteps ()C {return Max(_steps[0], _steps[1]);} // get max number of steps

   COMBINE_MODE aoCombineMode()C {return _aocm;} // get dual ambient occlusion combine mode

   // manage
   void create(Int steps=2, Flt strength=1.0f, Int steps_1=0, Flt strength_1=0.0f, COMBINE_MODE ao_combine_mode=ADD, Bool angles=false); // 'steps'=number of block steps used during occlusion calculation, bigger number will increase the quality however it will also reduce performance, 'strength'=occlusion strength 0..1 (0=no occlusion, 1=full occlusion), use 'steps_1 and strength_1 ao_combine_mode' for a secondary ambient occlusion effect (dual ambient occlusion), 'angles'=if include angle between light and surface normal when computing occlusion

   // operations, each of these methods recreate the entire 'BlocksOcclusion' by calling 'create', with just one parameter changed
   BlocksOcclusion& steps        (Int          steps   );
   BlocksOcclusion& steps1       (Int          steps   );
   BlocksOcclusion& strength     (Flt          strength);
   BlocksOcclusion& strength1    (Flt          strength);
   BlocksOcclusion& aoCombineMode(COMBINE_MODE aocm    );
   BlocksOcclusion& angles       (Bool         on      );

   BlocksOcclusion();

private:
   struct Node
   {
      Byte       dir;
      VecI       pos;
      UInt       fraction_axis[4];
      Flt        fraction     [2];
      Memc<Node> nodes;
   };

   Bool         _angles;
   Int          _steps   [2];
   Flt          _strength[2];
   COMBINE_MODE _aocm;
   Memc<Node>   _nodes;
};
/******************************************************************************/
struct Blocks
{
   struct Light
   {
      Ball ball; // world space range and position (not 'Blocks' local position)
      Vec color; // light color (0, 0, 0) .. (1, 1, 1)

      Light& set(C Ball &ball, C Vec &color=1) {T.ball=ball; T.color=color; return T;}
   };

   // manage
   Blocks& del   (                                  ); // delete manually
   Blocks& create(Int resolution, Int sub_division=1); // create Blocks capable of storing 'resolution' number of blocks in X Z dimensions, Y dimension will have no limit, 'sub_division'=sub division for mesh faces, 1..Inf

   // get / set
   Bool is         ()C {return _levels.elms()>0;}                                   // if has any data
   Int  resolution ()C {return _resolution     ;}                                   // get resolution used at Blocks creation
   Int  subDivision()C {return _sub_division   ;}   Blocks& subDivision(Int steps); // get/set mesh sub division, changing the 'subDivision' does not automatically rebuild the mesh, you should call 'setMesh' afterwards

   Bool        hasBlock(C VecI &pos                                                          )C; // if there is a block     at 'pos' local coordinates
   MaterialPtr material(C VecI &pos                                                          )C; // get     block material  at 'pos' local coordinates (this will return the 'top' material of the block)
   void        get     (C VecI &pos, MaterialPtr &top, MaterialPtr &side, MaterialPtr &bottom)C; // get all block materials at 'pos' local coordinates

   Bool set(Int x, Int y, Int z, C MaterialPtr &material                                       ); // set block to 'material'                , true is returned if any change was made during this operation, this does not automatically rebuild the mesh or the physical body, after calling this method you should call 'setMesh' and 'setPhysBody'
   Bool set(Int x, Int y, Int z, C MaterialPtr &top, C MaterialPtr &side, C MaterialPtr &bottom); // set block material to 'top side bottom', true is returned if any change was made during this operation, this does not automatically rebuild the mesh or the physical body, after calling this method you should call 'setMesh' and 'setPhysBody'

   // mesh
   Blocks& setMesh(Flt tex_scale, C BlocksOcclusion *occl=NULL, C BoxI *local_box=NULL, C VecI2 &blocks_pos=0, C BlocksMap *map=NULL, C Memp<Light> &lights=NULL, Bool optimize=false, Flt max_face_length=-1); // set Blocks mesh, 'tex_scale'=texture coordinates scale, 'occl'=Blocks occlusion object used for ambient occlusion calculation (use NULL for no AO), 'local_box'=if specified then the mesh will only be updated in specified local coordinates (use NULL for setting entire mesh), 'blocks_pos'=position of this Blocks object inside the 'BlocksMap' (based on this position neighbors will be obtained from the map), 'map'=map of all Blocks objects (you should pass a pointer to your custom class that extends from 'BlocksMap' to provide custom 'findBlocks' method which will be used for finding neighbors to this Blocks object), 'lights'=array of world space lights, 'optimize'=if automatically optimize the mesh by welding coplanar faces which will result in faster rendering ('max_face_length'=max allowed face length, -1=no limit)

   void setShader() {_mesh.setShader();} // reset mesh shader

   // physics
   Blocks& setPhysBody(C Matrix &matrix, C BoxI *local_box=NULL, Bool create_actor=false); // set Blocks physical body, 'matrix'=matrix of this 'Blocks' object, 'local_box'=if specified then the physical body will only be updated in specified local coordinates (use NULL for setting entire physical body), 'create_actor'=if automatically re-create the actor after updating the physical body
   Blocks&    delActor(); // delete blocks actor
   Blocks& createActor(); // create blocks actor from the physical body ('setPhysBody' should be called earlier)

   // operations
   Bool raycast(C Vec &start, C Vec &move, Vec *hit_pos=NULL, Vec *hit_normal=NULL, C Matrix *matrix=NULL)C; // raycast from 'start' local position along 'move' vector, returns true if collision occured and sets 'hit_pos' to its position and 'hit_normal' to its normal vector, 'matrix'=matrix of this 'Blocks' object

   // clean
   Blocks& cleanLevels   (); // clean Blocks from unused Y levels
   Blocks& cleanMaterials(); // clean Blocks from unused materials

   // draw
   void draw      (C Matrix &matrix)C {if(Frustum(_mesh.box, matrix))_mesh.draw      (matrix);} // 'matrix'=matrix of this 'Blocks' object
   void drawShadow(C Matrix &matrix)C {if(Frustum(_mesh.box, matrix))_mesh.drawShadow(matrix);} // 'matrix'=matrix of this 'Blocks' object

   // io
   void save(File &f, Bool include_mesh_and_phys_body, CChar *path=NULL)C; // save to   file, 'include_mesh_and_phys_body' if include mesh and physical body in the file, when enabled you don't need to build the mesh and physical body after load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path)
   Bool load(File &f                                 , CChar *path=NULL) ; // load from file                                                                                                                                                        , 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   // compress
   void   compress(File &f, C StrLibrary &materials_library)C;
   void decompress(File &f, C StrLibrary &materials_library) ;

   Blocks();

private:
   struct Level
   {
      Int      y;
      Byte   *_map;
      PhysPart phys;
      Actor    actor;

     ~Level() {actor.del(); Free(_map);} // manually delete actor before physical body
      Level() {y=0; _map=NULL;}
   };
   struct MtrlCombo
   {
      Byte top, side, bottom; // material indexes in '_materials'
   };

   Int             _resolution, _sub_division;
   MaterialPalette _materials;
   Memc<MtrlCombo> _mtrl_combos;
   Memc<Level>     _levels;
   Mesh            _mesh;
};
/******************************************************************************/
struct BlocksMap // extend this class to provide your own 'findBlocks' method
{
   // manage
   void create(Int resolution, C Matrix &base_matrix); // 'resolution'=resolution of all 'Blocks' in this map, 'base_matrix'=transformation matrix of Blocks at (0, 0) coordinates

   // get
   Int    resolution()C {return _resolution ;} // get resolution
   Matrix baseMatrix()C {return _base_matrix;} // get base matrix
   Matrix matrix    (Int x, Int y)C; // get transformation matrix of 'Blocks' at (x, y) coordinates, it will be calculated based on 'resolution' and 'base_matrix'

   // operations
   Bool raycast(C Vec &start, C Vec &move, Vec *hit_pos=NULL, Vec *hit_normal=NULL)C; // raycast from 'start' local position along 'move' vector, returns true if collision occured and sets 'hit_pos' to its position and 'hit_normal' to its normal vector

   Vec light(C Vec &pos, C BlocksOcclusion *occl=NULL, C Memp<Blocks::Light> &lights=NULL)C; // calculate light at 'pos' position, 'lights'=lights present in the scene

   // custom
   virtual Blocks* findBlocks(Int x, Int y)C {return NULL;} // override this method and return pointer to 'Blocks' at specified location

   BlocksMap();

private:
   Int    _resolution;
   Matrix _base_matrix;
};
/******************************************************************************/
