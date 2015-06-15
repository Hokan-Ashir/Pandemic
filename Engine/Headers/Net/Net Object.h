/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
namespace Net{
/******************************************************************************/
struct Neighbor // Net Object Neighbor
{
   Bool direct_connection; // if the object and the neighbor share a separate external direct connection between each other, which means that they can exchange data directly between each other and not involving the server

   Obj& obj() {return *_obj;} // get neighbor object

   Neighbor() {direct_connection=false; _obj=NULL;}

private:
   Obj *_obj;
};
/******************************************************************************/
struct Obj // Net Object
{
   // get
   virtual Obj& pos(C Vec &pos);   virtual C Vec& pos  () {return _pos  ;} // set/get object position
                                           World* world() {return _world;} //     get object world

   Int       neighbors(     )C {return _neighbors.elms();} // get number of neighbors
   Neighbor& neighbor (Int i)  {return _neighbors[i]    ;} // get i-th neighbor

   Bool inGame()C {return _area!=NULL;} // if object is currently in game

   // set
   void setWorld(World *world, C Vec &pos); // does not automatically enters the game

   // operations
   void enterGame(); // this adds the object to a world area, and detects nearby objects and stores them as neighbors, in order to enter the game, the object must have a world set
   void leaveGame(); // this disconnects from all neighbors and removed object from world area (but world pointer is unchanged)

   // callbacks
   virtual void disconnected(Obj &obj) {} // called when we're being disconnected from 'obj', most likely because objects got too far away from each other
   virtual void    connected(Obj &obj) {} // called when we're being    connected with 'obj', most likely because objects got close        to   each other

   // network
   void   compress(File &f, C StrLibrary *worlds=NULL); //   compress data so it can be sent  using network connection
   void decompress(File &f, C StrLibrary *worlds=NULL); // decompress data from data obtained using network connection, 'worlds'=must point to a StrLibrary with same data as the one which was used during 'compress' (or NULL if none was used)

   // io
   void save(File &f); // save
   Bool load(File &f); // load, false on fail

   Obj();

private:
   Vec            _pos, _old_pos;
   Area          *_area;
   World         *_world;
   Memc<Neighbor> _neighbors;
   NO_COPY_CONSTRUCTOR(Obj);
};
/******************************************************************************/
} // namespace
/******************************************************************************/
