/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   'MeshBase' is the most low level software mesh.
      It contains vertexes, edges, triangles and quads.

/******************************************************************************/
enum VTX_FLAGS // flags of a single vertex 'MeshVtxs::flag'
{
   VTX_FLAG_CLOTH=0x1, // when converting MeshBase to ClothMesh then use the vertex in physical cloth creation
};
enum ETQ_FLAG // Edge-Triangle-Quad Flag
{
   ETQ_L      =0x01, // has solid left  side
   ETQ_R      =0x02, // has solid right side
   ETQ_NO_PHYS=0x04, // no  physical body will be created from this face

   ETQ_LR=ETQ_L|ETQ_R,
};
enum MESH_BASE_FLAG // Mesh Base Flag
{
   VTX_POS     =1<< 0, // vertex position
   VTX_NRM     =1<< 1, // vertex normal
   VTX_TAN     =1<< 2, // vertex tangent
   VTX_BIN     =1<< 3, // vertex binormal
   VTX_HLP     =1<<28, // vertex helper
   VTX_TEX0    =1<< 4, // vertex texture uv 0
   VTX_TEX1    =1<< 5, // vertex texture uv 1
   VTX_TEX2    =1<<31, // vertex texture uv 2
   VTX_COLOR   =1<<29, // vertex color
   VTX_MATERIAL=1<<27, // vertex material blend
   VTX_MATRIX  =1<< 6, // vertex matrix index
   VTX_BLEND   =1<< 7, // vertex matrix blend
   VTX_SIZE    =1<< 8, // vertex size
   VTX_FLAG    =1<<30, // vertex flag
   VTX_DUP     =1<< 9, // vertex duplicate

   EDGE_IND     =1<<10, // edge vertex index
   EDGE_ADJ_FACE=1<<11, // edge adjacent face
   EDGE_NRM     =1<<12, // edge normal
   EDGE_FLAG    =1<<13, // edge flag
   EDGE_ID      =1<<14, // edge id

   TRI_IND     =1<<15, // triangle vertex index
   TRI_ADJ_FACE=1<<16, // triangle adjacent face
   TRI_ADJ_EDGE=1<<17, // triangle adjacent edge
   TRI_NRM     =1<<18, // triangle normal
   TRI_FLAG    =1<<19, // triangle flag
   TRI_ID      =1<<20, // triangle id

   QUAD_IND     =1<<21, // quad vertex index
   QUAD_ADJ_FACE=1<<22, // quad adjacent face
   QUAD_ADJ_EDGE=1<<23, // quad adjacent edge
   QUAD_NRM     =1<<24, // quad normal
   QUAD_FLAG    =1<<25, // quad flag
   QUAD_ID      =1<<26, // quad id

   VTX_TEX_ALL    =VTX_TEX0  |VTX_TEX1 |VTX_TEX2,
   VTX_TAN_BIN    =VTX_TAN   |VTX_BIN           ,
   VTX_NRM_TAN_BIN=VTX_NRM   |VTX_TAN_BIN       ,
   VTX_SKIN       =VTX_MATRIX|VTX_BLEND         ,

   FACE_IND     =TRI_IND     |QUAD_IND     ,
   FACE_ADJ_FACE=TRI_ADJ_FACE|QUAD_ADJ_FACE,
   FACE_ADJ_EDGE=TRI_ADJ_EDGE|QUAD_ADJ_EDGE,
   FACE_NRM     =TRI_NRM     |QUAD_NRM     ,
   FACE_FLAG    =TRI_FLAG    |QUAD_FLAG    ,
   FACE_ID      =TRI_ID      |QUAD_ID      ,

    VTX_ALL= VTX_POS|VTX_NRM_TAN_BIN|VTX_HLP|VTX_TEX_ALL|VTX_COLOR|VTX_MATERIAL|VTX_MATRIX|VTX_BLEND|VTX_SIZE|VTX_DUP|VTX_FLAG,
   EDGE_ALL=EDGE_IND|EDGE_ADJ_FACE|              EDGE_NRM|EDGE_FLAG|EDGE_ID,
    TRI_ALL= TRI_IND| TRI_ADJ_FACE| TRI_ADJ_EDGE| TRI_NRM| TRI_FLAG| TRI_ID,
   QUAD_ALL=QUAD_IND|QUAD_ADJ_FACE|QUAD_ADJ_EDGE|QUAD_NRM|QUAD_FLAG|QUAD_ID,
   FACE_ALL=FACE_IND|FACE_ADJ_FACE|FACE_ADJ_EDGE|FACE_NRM|FACE_FLAG|FACE_ID,
    ADJ_ALL=EDGE_ADJ_FACE|TRI_ADJ_FACE|TRI_ADJ_EDGE|QUAD_ADJ_FACE|QUAD_ADJ_EDGE,
    NRM_ALL= VTX_NRM |EDGE_NRM |TRI_NRM |QUAD_NRM ,
   FLAG_ALL= VTX_FLAG|EDGE_FLAG|TRI_FLAG|QUAD_FLAG,
     ID_ALL=          EDGE_ID  |TRI_ID  |QUAD_ID  ,
};
enum MESH_SIMPLIFY
{
   SIMPLIFY_DENSITY, // vertex matrixes are   dependent on vertex/face density
   SIMPLIFY_UNIFORM, // vertex matrixes are independent on vertex/face density
   SIMPLIFY_PLANES , // vertex matrixes are stored separately for each plane
};
/******************************************************************************/
struct VtxSkin
{
   Int bone  ; // bone matrix index
   Flt weight; // bone blend  weight

   void set(Int bone, Flt weight) {T.bone=bone; T.weight=weight;}

   VtxSkin() {}
   VtxSkin(Int bone, Flt weight) {set(bone, weight);}
};

inline Int Compare(C VtxSkin &vs0, C VtxSkin &vs1) {return Compare(vs1.weight, vs0.weight);} // compare in reversed order because we're sorting from most to least important

void SetSkin(C Memp<VtxSkin> &skin, VecB4 &matrix, VecB4 &blend, C Skeleton *skeleton); // set 'matrix' and 'blend' skinning values from 'skin' and 'skeleton' (optional)
/******************************************************************************/
struct VtxFull // Vertex containing all possible data
{
   Vec   pos, nrm, tan, bin, hlp;
   Vec2  tex0, tex1, tex2;
   Color color;
   VecB4 material, matrix, blend;
   Flt   size;

   void reset(); // reset vertex values, this sets all members to zero, except 'color' which is set to WHITE

   VtxFull& from(C MeshBase &mshb, Int i) ; // set VtxFull from i-th vertex in 'mshb'
   void     to  (  MeshBase &mshb, Int i)C; // set i-th 'mshb' vertex from VtxFull

   VtxFull& avg(C VtxFull &a, C VtxFull &b); // set as average from vertexes, T=Avg(a, b)

   VtxFull& lerp(C VtxFull &a, C VtxFull &b,                 Flt  step ); // set as linear interpolation from vertexes, T=Lerp(a, b, step)
   VtxFull& lerp(C VtxFull &a, C VtxFull &b, C VtxFull &c, C Vec &blend); // set as linear interpolation from vertexes, T=a*blend.x + b*blend.y + c*blend.z

   VtxFull& mul(C Matrix &matrix, C Matrix3 &matrix3); // transform vertex by matrixes ('pos hlp' by 'matrix', and 'nrm tan bin' by 'matrix3')
};
/******************************************************************************/
struct MeshVtxs // Mesh Vertexes
{
   Int    elms    ()C {return _elms    ;}                                                                            // get number of vertexes
   Vec  * pos     ()  {return _pos     ;}     Vec  & pos     (Int i)  {RANGE_ASSERT(i, _elms); return _pos     [i];} // get i-th vertex position
 C Vec  * pos     ()C {return _pos     ;}   C Vec  & pos     (Int i)C {RANGE_ASSERT(i, _elms); return _pos     [i];} // get i-th vertex position
   Vec  * nrm     ()  {return _nrm     ;}     Vec  & nrm     (Int i)  {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th vertex normal
 C Vec  * nrm     ()C {return _nrm     ;}   C Vec  & nrm     (Int i)C {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th vertex normal
   Vec  * tan     ()  {return _tan     ;}     Vec  & tan     (Int i)  {RANGE_ASSERT(i, _elms); return _tan     [i];} // get i-th vertex tangent
 C Vec  * tan     ()C {return _tan     ;}   C Vec  & tan     (Int i)C {RANGE_ASSERT(i, _elms); return _tan     [i];} // get i-th vertex tangent
   Vec  * bin     ()  {return _bin     ;}     Vec  & bin     (Int i)  {RANGE_ASSERT(i, _elms); return _bin     [i];} // get i-th vertex binormal
 C Vec  * bin     ()C {return _bin     ;}   C Vec  & bin     (Int i)C {RANGE_ASSERT(i, _elms); return _bin     [i];} // get i-th vertex binormal
   Vec  * hlp     ()  {return _hlp     ;}     Vec  & hlp     (Int i)  {RANGE_ASSERT(i, _elms); return _hlp     [i];} // get i-th vertex helper
 C Vec  * hlp     ()C {return _hlp     ;}   C Vec  & hlp     (Int i)C {RANGE_ASSERT(i, _elms); return _hlp     [i];} // get i-th vertex helper
   Vec2 * tex0    ()  {return _tex0    ;}     Vec2 & tex0    (Int i)  {RANGE_ASSERT(i, _elms); return _tex0    [i];} // get i-th vertex texture uv 0
 C Vec2 * tex0    ()C {return _tex0    ;}   C Vec2 & tex0    (Int i)C {RANGE_ASSERT(i, _elms); return _tex0    [i];} // get i-th vertex texture uv 0
   Vec2 * tex1    ()  {return _tex1    ;}     Vec2 & tex1    (Int i)  {RANGE_ASSERT(i, _elms); return _tex1    [i];} // get i-th vertex texture uv 1
 C Vec2 * tex1    ()C {return _tex1    ;}   C Vec2 & tex1    (Int i)C {RANGE_ASSERT(i, _elms); return _tex1    [i];} // get i-th vertex texture uv 1
   Vec2 * tex2    ()  {return _tex2    ;}     Vec2 & tex2    (Int i)  {RANGE_ASSERT(i, _elms); return _tex2    [i];} // get i-th vertex texture uv 2
 C Vec2 * tex2    ()C {return _tex2    ;}   C Vec2 & tex2    (Int i)C {RANGE_ASSERT(i, _elms); return _tex2    [i];} // get i-th vertex texture uv 2
   Color* color   ()  {return _color   ;}     Color& color   (Int i)  {RANGE_ASSERT(i, _elms); return _color   [i];} // get i-th vertex color
 C Color* color   ()C {return _color   ;}   C Color& color   (Int i)C {RANGE_ASSERT(i, _elms); return _color   [i];} // get i-th vertex color
   VecB4* material()  {return _material;}     VecB4& material(Int i)  {RANGE_ASSERT(i, _elms); return _material[i];} // get i-th vertex material blend
 C VecB4* material()C {return _material;}   C VecB4& material(Int i)C {RANGE_ASSERT(i, _elms); return _material[i];} // get i-th vertex material blend
   VecB4* matrix  ()  {return _matrix  ;}     VecB4& matrix  (Int i)  {RANGE_ASSERT(i, _elms); return _matrix  [i];} // get i-th vertex bone/matrix index , index maps to a specific bone of a skeleton, where 0=skeleton root bone, 1=skeleton bone #0, 2=skeleton bone #1, 3=skeleton bone #2, and so on, this can be summarized in the following : bone = (index ? skeleton.bone[index-1] : skeleton.root), only xyz components are used which point to 3 bones, w is unused and should be set to 0
 C VecB4* matrix  ()C {return _matrix  ;}   C VecB4& matrix  (Int i)C {RANGE_ASSERT(i, _elms); return _matrix  [i];} // get i-th vertex bone/matrix index , index maps to a specific bone of a skeleton, where 0=skeleton root bone, 1=skeleton bone #0, 2=skeleton bone #1, 3=skeleton bone #2, and so on, this can be summarized in the following : bone = (index ? skeleton.bone[index-1] : skeleton.root), only xyz components are used which point to 3 bones, w is unused and should be set to 0
   VecB4* blend   ()  {return _blend   ;}     VecB4& blend   (Int i)  {RANGE_ASSERT(i, _elms); return _blend   [i];} // get i-th vertex bone/matrix weight, weight factor between corresponding matrix.xyzw bones, only xyz components are used, their sum must be equal to 255 !! w is unused and should be set to 0
 C VecB4* blend   ()C {return _blend   ;}   C VecB4& blend   (Int i)C {RANGE_ASSERT(i, _elms); return _blend   [i];} // get i-th vertex bone/matrix weight, weight factor between corresponding matrix.xyzw bones, only xyz components are used, their sum must be equal to 255 !! w is unused and should be set to 0
   Flt  * size    ()  {return _size    ;}     Flt  & size    (Int i)  {RANGE_ASSERT(i, _elms); return _size    [i];} // get i-th vertex size
 C Flt  * size    ()C {return _size    ;}   C Flt  & size    (Int i)C {RANGE_ASSERT(i, _elms); return _size    [i];} // get i-th vertex size
   Byte * flag    ()  {return _flag    ;}     Byte & flag    (Int i)  {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th vertex VTX_FLAGS
 C Byte * flag    ()C {return _flag    ;}   C Byte & flag    (Int i)C {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th vertex VTX_FLAGS
   Int  * dup     ()  {return _dup     ;}     Int  & dup     (Int i)  {RANGE_ASSERT(i, _elms); return _dup     [i];} // get i-th vertex duplicate, index of identical vertex
 C Int  * dup     ()C {return _dup     ;}   C Int  & dup     (Int i)C {RANGE_ASSERT(i, _elms); return _dup     [i];} // get i-th vertex duplicate, index of identical vertex

private:
   Int _elms; Vec *_pos, *_nrm, *_tan, *_bin, *_hlp; Vec2 *_tex0, *_tex1, *_tex2; Color *_color; VecB4 *_material, *_matrix, *_blend; Flt *_size; Byte *_flag; Int *_dup;
};
/******************************************************************************/
struct MeshEdges // Mesh Edges
{
   Int    elms   ()C {return _elms    ;}                                                                           // get number of edges
   VecI2* ind    ()  {return _ind     ;}     VecI2& ind    (Int i)  {RANGE_ASSERT(i, _elms); return _ind     [i];} // get i-th edge vertex indexes
 C VecI2* ind    ()C {return _ind     ;}   C VecI2& ind    (Int i)C {RANGE_ASSERT(i, _elms); return _ind     [i];} // get i-th edge vertex indexes
   VecI2* adjFace()  {return _adj_face;}     VecI2& adjFace(Int i)  {RANGE_ASSERT(i, _elms); return _adj_face[i];} // get i-th edge adjacent faces, index to faces adjacent to the edge encoded in following way : if(adj_face==-1) -> no face, else if(adj_face&SIGN_BIT)adj_quad_index=adj_face^SIGN_BIT, else adj_tri_index=adj_face
 C VecI2* adjFace()C {return _adj_face;}   C VecI2& adjFace(Int i)C {RANGE_ASSERT(i, _elms); return _adj_face[i];} // get i-th edge adjacent faces, index to faces adjacent to the edge encoded in following way : if(adj_face==-1) -> no face, else if(adj_face&SIGN_BIT)adj_quad_index=adj_face^SIGN_BIT, else adj_tri_index=adj_face
   Vec  * nrm    ()  {return _nrm     ;}     Vec  & nrm    (Int i)  {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th edge normal
 C Vec  * nrm    ()C {return _nrm     ;}   C Vec  & nrm    (Int i)C {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th edge normal
   Byte * flag   ()  {return _flag    ;}     Byte & flag   (Int i)  {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th edge flag
 C Byte * flag   ()C {return _flag    ;}   C Byte & flag   (Int i)C {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th edge flag
   Int  * id     ()  {return _id      ;}     Int  & id     (Int i)  {RANGE_ASSERT(i, _elms); return _id      [i];} // get i-th edge id
 C Int  * id     ()C {return _id      ;}   C Int  & id     (Int i)C {RANGE_ASSERT(i, _elms); return _id      [i];} // get i-th edge id

private:
   Int _elms; VecI2 *_ind, *_adj_face; Vec *_nrm; Byte *_flag; Int *_id;
};
/******************************************************************************/
struct MeshTris // Mesh Triangles
{
   Int   elms   ()C {return _elms    ;}                                                                           // get number of triangles
   VecI* ind    ()  {return _ind     ;}     VecI& ind    (Int i)  {RANGE_ASSERT(i, _elms); return _ind     [i];} // get i-th triangle vertex indexes
 C VecI* ind    ()C {return _ind     ;}   C VecI& ind    (Int i)C {RANGE_ASSERT(i, _elms); return _ind     [i];} // get i-th triangle vertex indexes
   VecI* adjFace()  {return _adj_face;}     VecI& adjFace(Int i)  {RANGE_ASSERT(i, _elms); return _adj_face[i];} // get i-th triangle adjacent faces, index to faces adjacent to the triangle encoded in following way : if(adj_face==-1) -> no face, else if(adj_face&SIGN_BIT)adj_quad_index=adj_face^SIGN_BIT, else adj_tri_index=adj_face
 C VecI* adjFace()C {return _adj_face;}   C VecI& adjFace(Int i)C {RANGE_ASSERT(i, _elms); return _adj_face[i];} // get i-th triangle adjacent faces, index to faces adjacent to the triangle encoded in following way : if(adj_face==-1) -> no face, else if(adj_face&SIGN_BIT)adj_quad_index=adj_face^SIGN_BIT, else adj_tri_index=adj_face
   VecI* adjEdge()  {return _adj_edge;}     VecI& adjEdge(Int i)  {RANGE_ASSERT(i, _elms); return _adj_edge[i];} // get i-th triangle adjacent edges, index to edges adjacent to the triangle encoded in following way : if(adj_edge==-1) -> no edge, else adj_edge_index=adj_edge
 C VecI* adjEdge()C {return _adj_edge;}   C VecI& adjEdge(Int i)C {RANGE_ASSERT(i, _elms); return _adj_edge[i];} // get i-th triangle adjacent edges, index to edges adjacent to the triangle encoded in following way : if(adj_edge==-1) -> no edge, else adj_edge_index=adj_edge
   Vec * nrm    ()  {return _nrm     ;}     Vec & nrm    (Int i)  {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th triangle normal
 C Vec * nrm    ()C {return _nrm     ;}   C Vec & nrm    (Int i)C {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th triangle normal
   Byte* flag   ()  {return _flag    ;}     Byte& flag   (Int i)  {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th triangle flag
 C Byte* flag   ()C {return _flag    ;}   C Byte& flag   (Int i)C {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th triangle flag
   Int * id     ()  {return _id      ;}     Int & id     (Int i)  {RANGE_ASSERT(i, _elms); return _id      [i];} // get i-th triangle id
 C Int * id     ()C {return _id      ;}   C Int & id     (Int i)C {RANGE_ASSERT(i, _elms); return _id      [i];} // get i-th triangle id

private:
   Int _elms; VecI *_ind, *_adj_face, *_adj_edge; Vec *_nrm; Byte *_flag; Int *_id;
};
/******************************************************************************/
struct MeshQuads // Mesh Quads
{
   Int    elms   ()C {return _elms    ;}                                                                           // get number of quads
   VecI4* ind    ()  {return _ind     ;}     VecI4& ind    (Int i)  {RANGE_ASSERT(i, _elms); return _ind     [i];} // get i-th quad vertex indexes
 C VecI4* ind    ()C {return _ind     ;}   C VecI4& ind    (Int i)C {RANGE_ASSERT(i, _elms); return _ind     [i];} // get i-th quad vertex indexes
   VecI4* adjFace()  {return _adj_face;}     VecI4& adjFace(Int i)  {RANGE_ASSERT(i, _elms); return _adj_face[i];} // get i-th quad adjacent faces, index to faces adjacent to the quad encoded in following way : if(adj_face==-1) -> no face, else if(adj_face&SIGN_BIT)adj_quad_index=adj_face^SIGN_BIT, else adj_tri_index=adj_face
 C VecI4* adjFace()C {return _adj_face;}   C VecI4& adjFace(Int i)C {RANGE_ASSERT(i, _elms); return _adj_face[i];} // get i-th quad adjacent faces, index to faces adjacent to the quad encoded in following way : if(adj_face==-1) -> no face, else if(adj_face&SIGN_BIT)adj_quad_index=adj_face^SIGN_BIT, else adj_tri_index=adj_face
   VecI4* adjEdge()  {return _adj_edge;}     VecI4& adjEdge(Int i)  {RANGE_ASSERT(i, _elms); return _adj_edge[i];} // get i-th quad adjacent edges, index to edges adjacent to the quad encoded in following way : if(adj_edge==-1) -> no edge, else adj_edge_index=adj_edge
 C VecI4* adjEdge()C {return _adj_edge;}   C VecI4& adjEdge(Int i)C {RANGE_ASSERT(i, _elms); return _adj_edge[i];} // get i-th quad adjacent edges, index to edges adjacent to the quad encoded in following way : if(adj_edge==-1) -> no edge, else adj_edge_index=adj_edge
   Vec  * nrm    ()  {return _nrm     ;}     Vec  & nrm    (Int i)  {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th quad normal
 C Vec  * nrm    ()C {return _nrm     ;}   C Vec  & nrm    (Int i)C {RANGE_ASSERT(i, _elms); return _nrm     [i];} // get i-th quad normal
   Byte * flag   ()  {return _flag    ;}     Byte & flag   (Int i)  {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th quad flag
 C Byte * flag   ()C {return _flag    ;}   C Byte & flag   (Int i)C {RANGE_ASSERT(i, _elms); return _flag    [i];} // get i-th quad flag
   Int  * id     ()  {return _id      ;}     Int  & id     (Int i)  {RANGE_ASSERT(i, _elms); return _id      [i];} // get i-th quad id
 C Int  * id     ()C {return _id      ;}   C Int  & id     (Int i)C {RANGE_ASSERT(i, _elms); return _id      [i];} // get i-th quad id

private:
   Int _elms; VecI4 *_ind, *_adj_face, *_adj_edge; Vec *_nrm; Byte *_flag; Int *_id;
};
/******************************************************************************/
struct MeshBase // Mesh Base (the most low level software mesh, contains : Vertexes + Edges + Triangles + Quads)
{
   MeshVtxs  vtx ; // vertexes
   MeshEdges edge; // edges
   MeshTris  tri ; // triangles
   MeshQuads quad; // quads

   // manage
   MeshBase& del       (                                                                                                    ); // delete manually
   MeshBase& create    (  Int         vtxs, Int edges, Int tris, Int quads, UInt flag=0                                     ); // create, 'vtxs'=number of vertexes, 'edges'=number of edges, 'tris'=number of triangles, 'quads'=number of quads, 'flag'=MESH_BASE_FLAG (here VTX_POS, EDGE_IND, TRI_IND, QUAD_IND are always created automatically so you don't have to specify them manually)
   MeshBase& create    (C MeshBase   &src ,           UInt flag_and=~0                                                      ); // create from 'src'      , 'flag_and'=MESH_BASE_FLAG
   MeshBase& create    (C MeshRender &src ,           UInt flag_and=~0                                                      ); // create from 'src'      , 'flag_and'=MESH_BASE_FLAG
   MeshBase& create    (C MeshPart   &src ,           UInt flag_and=~0                                                      ); // create from 'src'      , 'flag_and'=MESH_BASE_FLAG
   MeshBase& create    (C MeshLod    &src ,           UInt flag_and=~0              , Bool set_face_id_from_part_index=false); // create from 'src'      , 'flag_and'=MESH_BASE_FLAG, 'set_face_id_from_part_index'=if set face 'id' members to the index of the original MeshPart that they were created from
   MeshBase& create    (C MeshBase   *src , Int elms, UInt flag_and=~0              , Bool set_face_id_from_part_index=false); // create from 'src' array, 'flag_and'=MESH_BASE_FLAG, 'set_face_id_from_part_index'=if set face 'id' members to the index of the original MeshPart that they were created from
   MeshBase& create    (C PhysPart   &src                                                                                   ); // create from 'src'
   MeshBase& createPhys(C MeshLod    &src ,           UInt flag_and=VTX_POS|FACE_IND, Bool set_face_id_from_part_index=false); // create from 'src'      , 'flag_and'=MESH_BASE_FLAG, 'set_face_id_from_part_index'=if set face 'id' members to the index of the original MeshPart that they were created from, this method ignores parts with MSHP_NO_PHYS_BODY flag and does not include them in the final mesh

   MeshBase& include (UInt flag); // include   elements specified with 'flag' MESH_BASE_FLAG
   MeshBase& exclude (UInt flag); // exclude   elements specified with 'flag' MESH_BASE_FLAG
   MeshBase& keepOnly(UInt flag); // keep only elements specified with 'flag' MESH_BASE_FLAG

   // create
   MeshBase& createPlane (  Int x=2, Int y=2, UInt flag=0                                       ); // create mesh as 3D plane from (0,0,0) to (1,1,0) vertex positions using quads, 'x, y'=vertex resolution, 'flag'=VTX_FLAG
   MeshBase& create      (C Box     &box    , UInt flag=0, Int resolution=-1                    ); // create mesh as 3D box                                  , 'flag'=VTX_FLAG
   MeshBase& create      (C OBox    &obox   , UInt flag=0, Int resolution=-1                    ); // create mesh as 3D oriented box                         , 'flag'=VTX_FLAG
   MeshBase& create      (C Ball    &ball   , UInt flag=0, Int resolution=-1                    ); // create mesh as 3D ball in cube      mode and uv mapping, 'flag'=VTX_FLAG
   MeshBase& create2     (C Ball    &ball   , UInt flag=0, Int resolution=-1, Int resolution2=-1); // create mesh as 3D ball in spherical mode and uv mapping, 'flag'=VTX_FLAG
   MeshBase& create      (C Capsule &capsule, UInt flag=0, Int resolution=-1, Int resolution2=-1); // create mesh as 3D capsule                              , 'flag'=VTX_FLAG
   MeshBase& create      (C Tube    &tube   , UInt flag=0, Int resolution=-1                    ); // create mesh as 3D tube                                 , 'flag'=VTX_FLAG
   MeshBase& create      (C Cone    &cone   , UInt flag=0, Int resolution=-1                    ); // create mesh as 3D cone                                 , 'flag'=VTX_FLAG
   MeshBase& create      (C Torus   &torus  , UInt flag=0, Int resolution=-1, Int resolution2=-1); // create mesh as 3D torus                                , 'flag'=VTX_FLAG
   MeshBase& create      (C Shape   &shape  , UInt flag=0, Int resolution=-1, Int resolution2=-1); // create mesh as 3D shape                                , 'flag'=VTX_FLAG
   MeshBase& createConvex(C Vec     *point  , Int  points, Int max_points=-1                    ); // create mesh as 3D convex mesh created from 'point' array of 'points' elements, you can optionally limit the maximum number of generated points to 'max_points' by setting it to a value different than -1

   // get
   Bool is       ()C {return vtx.elms() || edge.elms() || tri.elms() || quad.elms()  ;} // if  has any data
   Int  vtxs     ()C {return vtx.elms()                                              ;} // get number of vertexes
   Int  edges    ()C {return               edge.elms()                               ;} // get number of edges
   Int  tris     ()C {return                              tri.elms()                 ;} // get number of triangles
   Int  quads    ()C {return                                            quad.elms()  ;} // get number of quads
   Int  faces    ()C {return                              tri.elms()  + quad.elms()  ;} // get number of faces
   Int  trisTotal()C {return                              tri.elms()  + quad.elms()*2;} // get number of triangles including quads (each quad can be represented by 2 triangles)

   UInt flag        (                 )C; // get MESH_BASE_FLAG
   UInt memUsage    (                 )C; // get memory usage
   Bool getBox      (Box  &box        )C; // get box  encapsulating the mesh, this method iterates through all vertexes, false on fail (if no vertexes are present)
   Bool getBall     (Ball &ball       )C; // get ball encapsulating the mesh, this method iterates through all vertexes, false on fail (if no vertexes are present)
   Bool getRect     (Rect &rect       )C; // get 2D rectangle encapsulating the mesh on XY  plane, false on fail (if no vertexes are present)
   Flt  area        (Vec  *center=NULL)C; // get surface area of all mesh faces, 'center'=if specified then it will be calculated as the average surface center
   Flt  convexVolume(                 )C; // calculate volume of this mesh assuming that it's convex
   Int  maxId       (                 )C; // get maximum value of ID in edges/faces, -1 if doesn't have any
   Bool hasId       (Int   id         )C; // if  any of the edges/faces have their id set to 'id'

   // set
   MeshBase& setNormals    (Bool by_face_area=true                          ); // recalculate vertex 3D normals, 'by_face_area'=if use weight according to face surface area - default, (if false then face angle is used)
   MeshBase& setTangents   (                                                ); // recalculate vertex 3D tangents
   MeshBase& setBinormals  (                                                ); // recalculate vertex 3D binormals
   MeshBase& setAutoTanBin (                                                ); // automatically calculate vertex tangents and binormals if needed, if binormals are not needed then they will be removed
   MeshBase& setVtxDup2D   (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f); // set vertex 2D duplicates (vtx.dup)
   MeshBase& setVtxDup     (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f); // set vertex 3D duplicates (vtx.dup)
   MeshBase& setAdjacencies(                                                ); // set all adjacencies

   // transform
   MeshBase& move     (                           C Vec &move  ); //           move mesh
   MeshBase& scale    (C Vec              &scale               ); // scale          mesh
   MeshBase& scaleMove(C Vec              &scale, C Vec &move  ); // scale and move mesh
   MeshBase& setSize  (C Box              &box                 ); // scale and move mesh to fit box
   MeshBase& transform(C Matrix3          &matrix              ); // transform by matrix
   MeshBase& transform(C Matrix           &matrix              ); // transform by matrix
   MeshBase& animate  (C Matrix           *matrix, Int matrixes); // animate   by matrixes
   MeshBase& animate  (C AnimatedSkeleton &anim_skel           ); // animate   by skeleton
   MeshBase& mirrorX  (                                        ); // mirror in X axis
   MeshBase& mirrorY  (                                        ); // mirror in Y axis
   MeshBase& mirrorZ  (                                        ); // mirror in Z axis
   MeshBase& reverse  (                                        ); // reverse all      faces
   MeshBase& reverse  (  Int        face                       ); // reverse selected face , here the 'face'  index can point to both triangles and quads, if face is a triangle then "face=triangle_index", if face is a quad then "face=quad_index^SIGN_BIT"
   MeshBase& reverse  (C Memp<Int> &faces                      ); // reverse selected faces, here the 'faces' index can point to both triangles and quads, if face is a triangle then "face=triangle_index", if face is a quad then "face=quad_index^SIGN_BIT"

   // texture transform
   MeshBase& texMove  (C Vec2 &move , Byte tex_index=0); // move   texture uv's
   MeshBase& texScale (C Vec2 &scale, Byte tex_index=0); // scale  texture uv's
   MeshBase& texRotate(  Flt   angle, Byte tex_index=0); // rotate texture uv's

   // texturize
   MeshBase& texMap(  Flt     scale=1, Byte tex_index=0); // map texture uv's according to vertex xy position and scale
   MeshBase& texMap(C Matrix &matrix , Byte tex_index=0); // map texture uv's according to matrix
   MeshBase& texMap(C Plane  &plane  , Byte tex_index=0); // map texture uv's according to plane
   MeshBase& texMap(C Ball   &ball   , Byte tex_index=0); // map texture uv's according to ball
   MeshBase& texMap(C Tube   &tube   , Byte tex_index=0); // map texture uv's according to tube

   // operations
   MeshBase& weldVtx      (UInt flag=0, Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld 3D vertexes     , this function will weld vertexes together if they share the same position             , 'flag'=if selected elements aren't equal then don't weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes
   MeshBase& weldVtxValues(UInt flag  , Flt pos_eps=EPS, Flt nrm_cos=0.999f, Bool remove_degenerate_faces=true); // weld    vertex values, this function will weld values of vertexes which  share the same position             , 'flag'=                                 elements to weld (MESH_BASE_FLAG), 'remove_degenerate_faces'=if automatically remove degenerate faces which may occur after welding vertexes

   MeshBase& subdivide    (); // smooth subdivide faces
   MeshBase& subdivideEdge(Bool freeze_z=false, C Memp<Bool> &is=NULL); // smooth subdivide edges, 'is'=only selected edges

   MeshBase& boneRemap(C Memp<Byte> &old_to_new); // remap vertex bone/matrix indexes according to bone 'old_to_new' remap

   MeshBase& explodeVtxs(); // separate vertexes so that each edge/face has its own unique vertexes

   // fix
   MeshBase& fixTexOffset  (Byte tex_index=0); // fix texture offset , this reduces big texture coordinates to small ones increasing texturing quality on low precision video cards
   MeshBase& fixTexWrapping(Byte tex_index=0); // fix texture wraping, fixes texture coordinates created by spherical/tube mapping (this can add new vertexes to the mesh)

   // link
   void getVtxNeighbors (Int vtx , Memp<Int> vtxs )C; // get 'vtxs'  neighbors of 'vtx'  (including itself), this will return an array of vertexes that are connected to each other
   void getFaceNeighbors(Int face, Memp<Int> faces)C; // get 'faces' neighbors of 'face' (including itself), this will return an array of faces    that are connected to each other, here the 'face' and 'faces' indexes can point to both triangles and quads, if face is a triangle then "face=triangle_index", if face is a quad then "face=quad_index^SIGN_BIT"

   // convert
   MeshBase& edgeToDepth    (Bool tex_align=true  ); // edges     to depth     (extrude 2D edges to 3D faces)
   MeshBase& edgeToTri      (Bool set_id   =false ); // edges     to triangles (triangulation)
   MeshBase& triToQuad      (Flt  cos      =0.999f); // triangles to quads    , 'cos'=minimum cosine between 2      triangle normals to weld  them into 1 quad (0..1)
   MeshBase& quadToTri      (Flt  cos      =2     ); // quads     to triangles, 'cos'=minimum cosine between 2 quad triangle normals to leave them as   1 quad (0..1, value >1 converts all quads into triangles)
   MeshBase& toStencilShadow(                     ); // convert   to stencil shadow mesh, mesh must be closed (have no holes) and can't be infinite

   enum TEX_MODE
   {
      TEX_NONE   , // don't create   texture coordinates
      TEX_KEEP   , // keep  existing texture coordinates
      TEX_UNIFORM, // set   uniform  texture coordinates in range 0..1
      TEX_SCALED , // set   scaled   texture coordinates (X coords are scaled by vertex size, Y coords are scaled by distances between vertexes)
   };
   MeshBase& inflateEdges(TEX_MODE x_tex_coords=TEX_SCALED, TEX_MODE y_tex_coords=TEX_SCALED, Bool to_edges=false); // inflate mesh edges, 'x_tex_coords'=mode for settings X texture coordinates, 'y_tex_coords'=mode for settings Y texture coordinates, 'to_edges'=if inflate into edges (if false then faces will be created), this function operates on XY plane

   // add / remove
   MeshBase& addVtx (C Vec        &pos                  ); // add empty vertex at 'pos' position
   MeshBase& addEdge(C VecI2      &ind                  ); // add edge     by giving vertex indexes
   MeshBase& addTri (C VecI       &ind                  ); // add triangle by giving vertex indexes
   MeshBase& addQuad(C VecI4      &ind                  ); // add quad     by giving vertex indexes
   MeshBase& add    (C MeshBase   &src, UInt flag_and=~0); // add MeshBase
   MeshBase& add    (C MeshRender &src, UInt flag_and=~0); // add MeshRender
   MeshBase& add    (C MeshPart   &src, UInt flag_and=~0); // add MeshPart

   MeshBase& removeVtx (Int vtx );
   MeshBase& removeEdge(Int edge);
   MeshBase& removeTri (Int tri );
   MeshBase& removeQuad(Int quad);
   MeshBase& removeFace(Int face); // remove face, here the 'face' index can point to both triangles and quads, if face is a triangle then "face=triangle_index", if face is a quad then "face=quad_index^SIGN_BIT"

   MeshBase& removeVtxs (C Memp<Int> &vtxs                               ); // remove selected vertexes
   MeshBase& removeEdges(C Memp<Int> &edges, Bool remove_unused_vtxs=true); // remove selected edges
   MeshBase& removeFaces(C Memp<Int> &faces, Bool remove_unused_vtxs=true); // remove selected faces, here the 'faces' indexes can point to both triangles and quads, if face is a triangle then "face=triangle_index", if face is a quad then "face=quad_index^SIGN_BIT"

   MeshBase& removeDoubleSideFaces(Bool remove_unused_vtxs=true);

   // optimize
   MeshBase& removeDegenerateFaces();
   MeshBase& removeUnusedVtxs     (Bool include_edge_references=true); // remove vertexes which aren't used by any face or edge, if 'include_edge_references' is set to false then only face references are tested (without the edges)

   MeshBase& simplify(Flt intensity, Flt max_distance=1.0f, Flt max_uv=1.0f, Flt max_color=0.03f, Flt max_material=0.08f, Flt max_normal=PI, Bool keep_border=false, Flt border_priority=0.0f, MESH_SIMPLIFY mode=SIMPLIFY_DENSITY, MeshBase *dest=NULL); // simplify mesh by removing vertexes/faces, 'intensity'=how much to simplify (0..1, 0=no simplification, 1=full simplification), 'max_distance'=max distance between elements to merge them (0..Inf), 'max_uv'=max allowed vertex texture UV deviations (0..1), 'max_color'=max allowed vertex color deviations (0..1), 'max_material'=max allowed vertex material deviations (0..1), 'max_normal'=max allowed vertex normal angle deviations (0..PI), 'keep_border'=if always keep border edges (edges that have faces only on one side), 'border_priority'=priority of border faces (-Inf..Inf, <0 decreases priority and makes border edges more likely to be removed, >0 increases priority and makes border edges less likely to be removed), 'dest'=destination MeshBase (if set to NULL then the mesh will simplify itself), returns dest

   // draw
   void drawAuto(Material *material)C; // draw 3D, doesn't use automatic Frustum culling, optionally call this outside Render or inside Render function in any desired RENDER_MODE

   // io
   void operator=(C Str  &name) ; // load, Exit  on fail
   Bool save     (C Str  &name)C; // save, false on fail
   Bool load     (C Str  &name) ; // load, false on fail
   void save     (  File &f                  )C; // save
   Bool load     (  File &f, CChar *path=NULL) ; // load, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail

   MeshBase& operator*=(C Matrix3    &m  ) {return transform(m  );} // transform by matrix
   MeshBase& operator*=(C Matrix     &m  ) {return transform(m  );} // transform by matrix
   MeshBase& operator+=(C MeshBase   &src) {return add      (src);} // add 'src'
   MeshBase& operator+=(C MeshRender &src) {return add      (src);} // add 'src'
   MeshBase& operator+=(C MeshPart   &src) {return add      (src);} // add 'src'
   MeshBase& operator =(C MeshBase   &src) {return create   (src);} // create from 'src'

           ~MeshBase() {del ( );}
            MeshBase() {Zero(T);}
   explicit MeshBase(  Int         vtxs, Int edges, Int tris, Int quads, UInt flag=0) {Zero(T); create(vtxs, edges, tris, quads, flag);}
   explicit MeshBase(C MeshBase   &src , UInt flag_and=~0                           ) {Zero(T); create(src , flag_and);}
   explicit MeshBase(C MeshRender &src , UInt flag_and=~0                           ) {Zero(T); create(src , flag_and);}
   explicit MeshBase(C MeshPart   &src , UInt flag_and=~0                           ) {Zero(T); create(src , flag_and);}
   explicit MeshBase(C MeshLod    &src , UInt flag_and=~0                           ) {Zero(T); create(src , flag_and);}
   explicit MeshBase(C PhysPart   &src                                              ) {Zero(T); create(src );}
};
/******************************************************************************/
inline Int Elms(C MeshVtxs  &vtx ) {return vtx .elms();}
inline Int Elms(C MeshEdges &edge) {return edge.elms();}
inline Int Elms(C MeshTris  &tri ) {return tri .elms();}
inline Int Elms(C MeshQuads &quad) {return quad.elms();}
/******************************************************************************/
