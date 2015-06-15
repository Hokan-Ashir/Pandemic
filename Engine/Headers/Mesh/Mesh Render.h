/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   'MeshRender' is the hardware version of the 'MeshBase'.
   It contains vertexes and triangles.
   It is stored on the GPU memory.

/******************************************************************************/
struct MeshRender // Mesh Renderable (Hardware: contains Vertexes + Triangles)
{
   // manage
   MeshRender& del();

   // get
   Bool is  ()C {return vtxs() || tris();} // if  has any data
   Int  vtxs()C {return _vb.vtxs()      ;} // get number of vertexes
   Int  tris()C {return    _tris        ;} // get number of triangles

   UInt memUsage(                )C {return _vb.memUsage()+_ib.memUsage();} // get memory usage of the mesh (in bytes)
   Int  vtxSize (                )C {return _vb.vtxSize ()               ;} // get size of a single vertex
   Int  vtxOfs  (UInt elm        )C;                                        // get offset of a specified vertex component in the vertex data, -1 if not found, 'elm'=one of MESH_BASE_FLAG enums
   Bool indBit16(                )C {return _ib.bit16()                  ;} // if  indices are 16-bit (false for 32-bit)
   UInt    flag (                )C {return _flag                        ;} // get MESH_BASE_FLAG that this mesh has
   Bool getBox  (Box &box        )C;                                        // get box encapsulating the mesh, this method iterates through all vertexes, false on fail (if no vertexes are present)
   Flt     area (Vec *center=NULL)C;                                        // get surface area of all mesh faces, 'center'=if specified then it will be calculated as the average surface center

   // transform
   void scaleMove(C Vec &scale, C Vec &move=VecZero);

   // texture transform
   void texMove  (C Vec2 &move , Byte tex_index=0);
   void texScale (C Vec2 &scale, Byte tex_index=0);
   void texRotate(  Flt   angle, Byte tex_index=0);

   // operations
 C Byte* vtxLockedData(                              )C {return _vb.lockedData(    );} //    get vertex data if it's already locked, NULL on fail
 C Byte* vtxLockedElm (UInt elm                      )C;                               //    get vertex data if it's already locked offseted by specified vertex component in the vertex data according to 'vtxOfs' method, 'elm'=one of MESH_BASE_FLAG enums, NULL on fail (if the vertex buffer is not locked or if the component was not found)
   Byte* vtxLock      (LOCK_MODE lock=LOCK_READ_WRITE)  {return _vb.lock      (lock);} //   lock vertex data and return it, this method may be used to directly modify values of hardware mesh vertexes after getting their offset in the data by using 'vtxOfs' method (currently you should use it only for 'VTX_POS' as 'Vec', 'VTX_TEX' as 'Vec2' and 'VTX_COLOR' as 'Color' components, as others may be stored in compressed format), NULL on fail
 C Byte* vtxLockRead  (                              )C {return _vb.lockRead  (    );} //   lock vertex data and return it, this method may be used to directly access values of hardware mesh vertexes after getting their offset in the data by using 'vtxOfs' method (currently you should use it only for 'VTX_POS' as 'Vec', 'VTX_TEX' as 'Vec2' and 'VTX_COLOR' as 'Color' components, as others may be stored in compressed format), NULL on fail
   void  vtxUnlock    (                              )C {       _vb.unlock    (    );} // unlock vertex data

   CPtr indLockedData(                              )C {return _ib.  lockedData(    );} //    get index data if it's already locked, NULL on fail
    Ptr indLock      (LOCK_MODE lock=LOCK_READ_WRITE)  {return _ib.  lock      (lock);} //   lock index data and return it, this method may be used to directly access values of hardware mesh indexes, NULL on fail
   CPtr indLockRead  (                              )C {return _ib.  lockRead  (    );} //   lock index data and return it, this method may be used to directly modify values of hardware mesh indexes, NULL on fail
   void indUnlock    (                              )C {       _ib.unlock      (    );} // unlock index data

   MeshRender& operator =(C MeshRender &src); // create from 'src'
   MeshRender& operator+=(C MeshRender &src); // add         'src'

  ~MeshRender() {del ( );}
   MeshRender() {Zero(T);}
   MeshRender(C MeshRender &src) {Zero(T); T=src;}

private:
   Byte   _storage;
   Int    _tris, _bone_splits;
   UInt   _flag;
   VtxBuf _vb;
   IndBuf _ib;
   Ptr    _bone_split, _vf;
};
/******************************************************************************/
