/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
// MATH
/******************************************************************************/
struct Vec2;
struct VecD2;
struct VecI2;
struct Vec;
struct VecD;
struct VecI;
struct Vec4;
struct VecD4;
struct VecI4;
struct VecB4;

struct Plane;
struct PlaneD;

struct Edge2;
struct EdgeD2;
struct Edge;
struct EdgeD;

struct Tri2;
struct TriD2;
struct Tri;
struct TriD;

struct Quad2;
struct QuadD2;
struct Quad;
struct QuadD;

struct Rect;
struct RectI;
struct Box;
struct BoxD;
struct BoxI;
struct OBox;
struct Circle;
struct Ball;
struct Capsule;
struct Tube;
struct Torus;
struct Cone;
struct Pyramid;
struct Shape;

struct Matrix3;
struct MatrixD3;
struct Matrix;
struct MatrixD;
struct Matrix4;

struct Orient;
struct OrientP;

struct Quaternion;

struct FrustumClass;
/******************************************************************************/
// ANIMATION
/******************************************************************************/
struct SkeletonBone;
struct SkeletonPoint;
struct Skeleton;
struct AnimatedSkeletonBone;
struct AnimatedSkeleton;
struct AnimationKeys;
struct AnimationBone;
struct AnimationEvent;
struct Animation;
struct SkelAnim;
struct Motion;
/******************************************************************************/
// GRAPHICS
/******************************************************************************/
struct Color;
struct Image;
struct ImageHeader;
struct Video;
struct Font;
struct Display;
struct MainShaderClass;
struct RendererClass;
struct RenderTargets;
struct VtxFormatGL;
struct VtxFormat;
struct VtxIndBuf;
struct VtxFull;
struct Light;
struct RippleFx;
struct TextStyleParams;
struct TextStyle;
struct TextInput;
struct ShaderParam;
struct ShaderParamChange;
struct ShaderTech;
struct Shader;
struct FRST;
struct BLST;
/******************************************************************************/
// GUI
/******************************************************************************/
struct  GUI;
struct  GuiObj;
struct  GuiObjs;
struct  GuiObjChildren;
struct  Button;
struct  CheckBox;
struct  ColorPicker;
struct  ComboBox;
struct  Desktop;
struct  GuiCustom;
struct  TextCodeData;
struct  Text;
struct  Viewport;
struct  GuiImage;
struct _List;
struct  ListColumn;
struct  MenuElm;
struct  Menu;
struct  MenuBar;
struct  Progress;
struct  Region;
struct  SlideBar;
struct  Slider;
struct  Tab;
struct  Tabs;
struct  TextBox;
struct  TextLine;
struct  Window;
struct  WindowIO;
/******************************************************************************/
// MESH
/******************************************************************************/
struct Blocks;
struct BlocksMap;
struct MeshBase;
struct MeshRender;
struct MeshPart;
struct MeshLod;
struct Mesh;
struct MeshGroup;
/******************************************************************************/
// MISC
/******************************************************************************/
struct Str8;
struct Str;
struct BStr;
struct File;
struct Pak;
struct PakSet;
struct PakFile;
struct TextNode;
struct TextData;
struct XmlNode;
struct XmlData;
struct TextEdit;
struct CalcValue;
struct DateTime;
struct Keyboard;
struct Mouse;
struct KbSc;
struct Secure;
struct PathWorld;
struct UID;
struct _Memc;
struct _Memb;
struct _Memx;
struct  MemlNode;
T1(TYPE) struct Mems;
T1(TYPE) struct FixedMems;
T1(TYPE) struct Memc;
T1(TYPE) struct Memb;
T1(TYPE) struct Memx;
T1(TYPE) struct Meml;
template<typename TYPE, int size=64*1024>   struct Memt;
template<typename TYPE, int size=64*1024>   struct Memp;
struct _Grid;
struct _Map;
struct _Cache;
T1(TYPE) struct Cache;
template<typename TYPE, Cache<TYPE> &CACHE>   struct CacheElmPtr;
template<typename TYPE, Cache<TYPE> &CACHE>   struct CacheCounted;
/******************************************************************************/
// PHYSICS
/******************************************************************************/
struct PhysHit;
struct PhysCutsCallback;
struct PhysHitCallback;
struct Joint;
struct Actor;
struct ActorInfo;
struct PhysMtrl;
struct Ragdoll;
struct Controller;
struct Grab;
struct PhysPart;
struct PhysBody;
struct PhysGroup;
struct PhysicsClass;
struct RigidBody;
/******************************************************************************/
// NET
/******************************************************************************/
struct Socket;
/******************************************************************************/
// GAME
/******************************************************************************/
namespace Game
{
   struct Obj;
   struct ObjParams;
   struct Item;
   struct Chr;
   struct Area;
   struct WorldSettings;
   struct WorldManager;
   T1(TYPE) struct ObjMap;
}
/******************************************************************************/
// EDIT
/******************************************************************************/
namespace Edit
{
   struct Symbol;
   struct Line;
   struct Source;
   struct Token;
   struct Macro;
   struct Expr;
   struct Command;
   struct Message;
   struct Compiler;
   struct CompilerContext;
}
/******************************************************************************/
// NET
/******************************************************************************/
namespace Net
{
   struct Obj;
   struct Area;
   struct World;
}
/******************************************************************************/
#ifdef HAS_MOVE_CONSTRUCTOR
Str operator+(Str &&a,   CChar  *b);
Str operator+(Str &&a,   CChar8 *b);
Str operator+(Str &&a, C Str    &b);
Str operator+(Str &&a, C Str8   &b);
Str operator+(Str &&a,   Char    b);
Str operator+(Str &&a,   Char8   b);
Str operator+(Str &&a,   Bool    b);
Str operator+(Str &&a,   SByte   b);
Str operator+(Str &&a,   Int     b);
Str operator+(Str &&a,   Long    b);
Str operator+(Str &&a,   Byte    b);
Str operator+(Str &&a,   UInt    b);
Str operator+(Str &&a,   ULong   b);
Str operator+(Str &&a,   Flt     b);
Str operator+(Str &&a,   Dbl     b);
Str operator+(Str &&a,   CPtr    b);
Str operator+(Str &&a, C Vec2   &b);
Str operator+(Str &&a, C VecD2  &b);
Str operator+(Str &&a, C VecI2  &b);
Str operator+(Str &&a, C Vec    &b);
Str operator+(Str &&a, C VecD   &b);
Str operator+(Str &&a, C VecI   &b);
Str operator+(Str &&a, C Vec4   &b);
Str operator+(Str &&a, C VecD4  &b);
Str operator+(Str &&a, C VecI4  &b);
Str operator+(Str &&a, C VecB4  &b);
Str operator+(Str &&a, C BStr   &b);

Str8 operator+(Str8 &&a,   CChar  *b);
Str8 operator+(Str8 &&a,   CChar8 *b);
Str8 operator+(Str8 &&a, C Str    &b);
Str8 operator+(Str8 &&a, C Str8   &b);
Str8 operator+(Str8 &&a,   Char    b);
Str8 operator+(Str8 &&a,   Char8   b);
Str8 operator+(Str8 &&a,   Bool    b);
Str8 operator+(Str8 &&a,   SByte   b);
Str8 operator+(Str8 &&a,   Int     b);
Str8 operator+(Str8 &&a,   Long    b);
Str8 operator+(Str8 &&a,   Byte    b);
Str8 operator+(Str8 &&a,   UInt    b);
Str8 operator+(Str8 &&a,   ULong   b);
Str8 operator+(Str8 &&a,   Flt     b);
Str8 operator+(Str8 &&a,   Dbl     b);
Str8 operator+(Str8 &&a,   CPtr    b);
Str8 operator+(Str8 &&a, C Vec2   &b);
Str8 operator+(Str8 &&a, C VecD2  &b);
Str8 operator+(Str8 &&a, C VecI2  &b);
Str8 operator+(Str8 &&a, C Vec    &b);
Str8 operator+(Str8 &&a, C VecD   &b);
Str8 operator+(Str8 &&a, C VecI   &b);
Str8 operator+(Str8 &&a, C Vec4   &b);
Str8 operator+(Str8 &&a, C VecD4  &b);
Str8 operator+(Str8 &&a, C VecI4  &b);
Str8 operator+(Str8 &&a, C VecB4  &b);
Str8 operator+(Str8 &&a, C BStr   &b);
#endif
/******************************************************************************/
