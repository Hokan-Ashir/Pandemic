/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'List' to display a list of elements (with custom columns) in a gui object.

   List supports 2 types of indexes:
      -absolute indexes (known as 'abs') it is the order in which elements are stored in original memory containers
      -visible  indexes (known as 'vis') it is the order in which elements are displayed in the list, this order is affected by: sorting, element visibility

   Elements that are hidden will have their visible index set to -1.

/******************************************************************************/
enum LIST_COLUMN_WIDTH_MODE // List Column Width Mode
{
   LCW_DATA           =-1, // set List Column width from                                data width
   LCW_PARENT         =-2, // set List Column width from     Lists GuiObj parent width
   LCW_MAX_DATA_PARENT=-3, // set List Column width from Max(Lists GuiObj parent width, data width)
};
/******************************************************************************/
STRUCT(ListColumn , Button) // List Column
//{
   Int        precision ; // data number precision, default=3
   Flt        width     , // column width (can also be set to LCW_DATA, LCW_PARENT or LCW_MAX_DATA_PARENT)
              text_align; // text   aligning
   MemberDesc md        , // member description
             *sort      ; // member description used for sorting (if NULL then 'md' will be used instead, default=NULL)

   T1(TYPE) ListColumn(TYPE    &member                     , Flt width, CChar *name) : md(member            ) {create(NULL             , width, name);} // create using member auto-detection     , 'member'      =custom class member - 'MEMBER' macro usage is required  , 'width'=column width (can also be set to LCW_DATA, LCW_PARENT or LCW_MAX_DATA_PARENT), 'name'=column name
   T1(TYPE) ListColumn(Str    (*data_to_text)(C TYPE &data), Flt width, CChar *name)                          {create((Ptr)data_to_text, width, name);} // create using manual conversion function, 'data_to_text'=custom function converting data to text                 , 'width'=column width (can also be set to LCW_DATA, LCW_PARENT or LCW_MAX_DATA_PARENT), 'name'=column name
            ListColumn(DATA_TYPE type, Int offset, Int size, Flt width, CChar *name) : md(type, offset, size) {create(NULL             , width, name);} // create using manual member description , 'type'=data type, 'offset'=member offset in class, 'size'=sizeof member, 'width'=column width (can also be set to LCW_DATA, LCW_PARENT or LCW_MAX_DATA_PARENT), 'name'=column name
            ListColumn(                                                            )                          {create(NULL             ,     0, NULL);} // create empty

   virtual void update(C GuiPC &gpc);

private:
   Int _resize_edge;
   void create(Ptr data_to_text, Flt width, CChar *name);
};
/******************************************************************************/
enum LIST_CUR_MODE // List Cursor Mode
{
   LCM_DEFAULT, // default, cursor is hidden when not active
   LCM_MOUSE  , // cursor is always under mouse
   LCM_ALWAYS , // cursor is always visible
};
enum LIST_DRAW_MODE // List Draw Mode
{
   LDM_LIST , // standard list, one element per line
   LDM_RECTS, // elements are displayed in rectangle areas, can be multiple elements per line, used for displaying images
};
enum LIST_SEL_MODE // List Selection Mode
{
   LSM_SET          , // set     element  as   selection
   LSM_TOGGLE       , // toggle  element  in   selection
   LSM_INCLUDE      , // include element  in   selection
   LSM_EXCLUDE      , // exclude element  from selection
   LSM_EXCLUDE_MULTI, // exclude elements from selection
};
enum LIST_FLAG // List Flag
{
   LIST_SORTABLE         =0x001, // if list is sortable
   LIST_SCALABLE         =0x002, // if list is scalable   (zoomable)
   LIST_ROLLABLE         =0x004, // if list is rollable   (moving the cursor up while being at the top will move it to the bottom and vice-versa)
   LIST_SEARCHABLE       =0x008, // if list is searchable (typing keys will change cursor position)
   LIST_IMMEDIATE_DESC   =0x010, // if immediately show description without any delays
   LIST_TYPE_SORT        =0x020, // if elements will be sorted by their "types" first (types are set using 'setElmType' method)
   LIST_TYPE_LINE        =0x040, // if elements of different "types" won't be displayed in the same line in LDM_RECTS mode
   LIST_MULTI_SEL        =0x080, // if list supports selection of multiple elements at one time (by using Shift, Ctrl, ..)
   LIST_RESIZABLE_COLUMNS=0x100, // if list columns can be resized using mouse
};
/******************************************************************************/
const_mem_addr STRUCT(_List , GuiObj) // Gui List !! must be stored in constant memory address !!
//{
   // columns
   Bool columns_hidden, // if column buttons are hidden
        sort_swap  [3]; // swap order of sorting (true/false)        , default={false, false, false}
   Int  sort_column[3], // index of sorting columns (-1=none)        , default={   -1,    -1,    -1}
        draw_column   ; // index of column which toggles drawing mode, default=-1, this is automatically set to first column of Image type

   // elements
   Int       cur, // current     element  (in visible  indexing mode)
             lit; // highlighted element  (in visible  indexing mode)
   Memc<Int> sel; // selected    elements (in absolute indexing mode to allow selecting hidden elements), this allows to obtain all selected elements, this is valid only if 'flag' has LIST_MULTI_SEL option enabled

   // misc
   LIST_CUR_MODE  cur_mode  ; // cursor    mode       , default=LCM_DEFAULT
   LIST_SEL_MODE  sel_mode  ; // selection mode       , default=LSM_SET  affects the default action for handling selection of an element upon its clicking for lists with LIST_MULTI_SEL option enabled
   UInt          flag       ; // LIST_FLAG            , default=LIST_SORTABLE|LIST_SEARCHABLE
   ALPHA_MODE    image_alpha; // images alpha blending, default=ALPHA_BLEND
   Flt           zoom_min   , // minimum zoom         , default=0.58
                 zoom_max   ; // maximum zoom         , default=1.44
   Vec2          padding    ; // list padding         , default=(0, 0)  amount of padding applied to the list size

   // manage
  _List& del   (                                                            );                                                               // delete
  _List& clear (Bool quiet=false                                            );                                                               // clear list elements, 'quiet'=if apply the changed in quiet mode (if set to true then 'func' will not be called)
  _List& create(                                                            );                                                               // create
  _List& create(C ListColumn *column, Int columns, Bool columns_hidden=false) {return create().setColumns(column, columns, columns_hidden);} // create and set columns, list columns are copied internally
  _List& create(C _List &src                                                );                                                               // create from 'src'

   // set / get
  _List& setColumns(C ListColumn *column, Int columns, Bool columns_hidden=false); // set columns, list columns are copied internally

   T1(TYPE) _List& setData    ( TYPE       *data, Int elms, C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from continuous memory  !! after any change in source data, 'setData' must be called again !!
   T1(TYPE) _List& setData    ( Mems<TYPE> &mems,           C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from Mems               !! after any change in source data, 'setData' must be called again !!
            _List& setData    (_Memc       &memc,           C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from Memc               !! after any change in source data, 'setData' must be called again !!
            _List& setData    (_Memb       &memb,           C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from Memb               !! after any change in source data, 'setData' must be called again !!
            _List& setData    (_Memx       &memx,           C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from Memx               !! after any change in source data, 'setData' must be called again !!
            _List& setData    (_Meml       &meml,           C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from Meml               !! after any change in source data, 'setData' must be called again !!
   T1(TYPE) _List& setDataNode( Memx<TYPE> &memx,           C Memp<Bool> &visible=NULL, Bool keep_cur=false); // set list data from Memx with children !! after any change in source data, 'setData' must be called again !! TYPE must have a "Memx<TYPE> children" member, for example: "struct TYPE { Memx<TYPE> children; }", in that case 'setDataNode' will add all elements including children recursively

  _List& columnHeight(Flt height                                         );   Flt      columnHeight   ()C {return               _column_height;} // set/get columns   height,        0..Inf     , default= 0.055
  _List&    elmHeight(Flt height                                         );   Flt         elmHeight   ()C {return                  _elm_height;} // set/get elements  height,        0..Inf     , default= 0.050
  _List&     textSize(Flt base, Flt relative=0                           );   Flt      textSizeBase   ()C {return                   _text_base;} // set/get text      size  ,        0..Inf     , default=(0.050, 0.0   ), final text  size = "zoom * elmHeight() *  textSizeRel() +  textSizeBase() "
                                                                              Flt      textSizeRel    ()C {return                   _text_rel ;} // set/get text      size  ,        0..Inf     , default=(0.050, 0.0   ), final text  size = "zoom * elmHeight() *  textSizeRel() +  textSizeBase() "
                                                                              Flt      textSizeActual ()C;                                       //     get text      size actual                                                           = "zoom * elmHeight() *  textSizeRel() +  textSizeBase() "
  _List&    imageSize(C Vec2 &base, Flt relative, C Rect &padding=Vec2(0)); C Vec2&   imageSizeBase   ()C {return                  _image_base;} // set/get image     size  ,        0..Inf     , default=(0.0  , 0.1/64), final text  size = "zoom * (image.xy   * imageSizeRel() + imageSizeBase())", 'padding'=padding applied to the whole element rectangle
                                                                              Flt     imageSizeRel    ()C {return                  _image_rel ;} // set/get image     size  ,        0..Inf     , default=(0.0  , 0.1/64), final image size = "zoom * (image.xy   * imageSizeRel() + imageSizeBase())"
                                                                            C Rect&   imageSizePadding()C {return                  _image_padd;} // set/get image     size  ,        0..Inf     , default=(0.0  , 0.1/64), final image size = "zoom * (image.xy   * imageSizeRel() + imageSizeBase())"
  _List&         zoom(Flt zoom                                           );   Flt                 zoom()C {return                        _zoom;} // set/get list      zoom  , zoom_min..zoom_max, default= 1.0
  _List&         skin(C GuiSkinPtr &skin                                 ); C GuiSkinPtr&         skin()C {return                        _skin;} // set/get skin override, default=NULL (if set to NULL then current value of 'Gui.skin' is used), changing this value will automatically change the skin of the list columns
                                                                              GuiSkin   *      getSkin()C {return _skin ? _skin() : Gui.skin();} //     get actual skin
                                                                              TextStyle * getTextStyle()C;                                       //     get actual text style
  _List&   horizontal(Bool           horizontal                          );   Bool          horizontal()C {return                  _horizontal;} // set/get if LDM_RECTS mode should be displayed horizontally, default=false
  _List&     vertical(Bool           vertical                            );   Bool            vertical()C {return                 !_horizontal;} // set/get if LDM_RECTS mode should be displayed   vertically, default=true
  _List&     drawMode(LIST_DRAW_MODE mode                                );   LIST_DRAW_MODE  drawMode()C {return                   _draw_mode;} // set/get draw      mode  ,   LIST_DRAW_MODE  , default=LDM_LIST
                                                                              LIST_SEL_MODE    selMode()C;                                       //     get selection mode affected by keyboard modifiers
  _List&   selProcess(Int absolute, Int sel_mode=-1                      );                                                                      // process selection of specified 'absolute' element index, 'sel_mode'=selection mode (use -1 for 'selMode')

   Int   totalElms()C {return   _total_elms;} // get number of total   elements
   Int visibleElms()C {return _visible_elms;} // get number of visible elements
   Int        elms()C {return _visible_elms;} // get number of visible elements

   VecI2 visibleElmsOnScreen(C GuiPC *gpc=NULL)C; // get range of elements that are currently visible on the screen, this range covers visible elements from VecI2.x to VecI2.y inclusive, this function is useful if you want to draw additional graphics on top of visible elements (if the range is empty then VecI2(0, -1) is returned), if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)

   Ptr  operator()(             )C {return visToData(cur    );} // convert visible  index to data
   Ptr  operator()(Int  visible )C {return visToData(visible);} // convert visible  index to data
   Ptr  visToData (Int  visible )C;                             // convert visible  index to data
   Int  visToAbs  (Int  visible )C;                             // convert visible  index to absolute index
   Ptr  absToData (Int  absolute)C;                             // convert absolute index to data
   Int  absToVis  (Int  absolute)C;                             // convert absolute index to visible  index
   Int dataToVis  (CPtr data    )C;                             // convert data           to visible  index
   Int dataToAbs  (CPtr data    )C;                             // convert data           to absolute index

   Int screenToVisX      (  Flt   x      , C GuiPC *gpc=NULL)C; // convert screen  position X to visible index                                        , if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   Int screenToVisY      (  Flt   y      , C GuiPC *gpc=NULL)C; // convert screen  position Y to visible index                                        , if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   Int screenToVis       (C Vec2 &pos    , C GuiPC *gpc=NULL)C; // convert screen  position   to visible index                                        , if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   Ptr screenToData      (  Flt   y      , C GuiPC *gpc=NULL)C; // convert screen  position Y to data                                                 , if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   Ptr screenToData      (C Vec2 &pos    , C GuiPC *gpc=NULL)C; // convert screen  position   to data                                                 , if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   Vec2   visToScreenPos (  Int   visible, C GuiPC *gpc=NULL)C; // convert visible index      to top left corner position of the element on the screen, if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   Rect   visToScreenRect(  Int   visible, C GuiPC *gpc=NULL)C; // convert visible index      to rectangle                of the element on the screen, if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)

   Int         columns(     )C {return _columns.elms();} // number of columns
   ListColumn& column (Int i)  {return _columns[i]    ;} // get i-th  column

                                               Flt  columnOffset (Int i)C; //     get i-th column horizontal offset
  _List& columnWidth  (Int i, Flt  width  );   Flt  columnWidth  (Int i)C; // set/get i-th column width, ('width' can also be set to LCW_DATA, LCW_PARENT or LCW_MAX_DATA_PARENT)
  _List& columnVisible(Int i, Bool visible);   Bool columnVisible(Int i)C; // set/get i-th column visibility

   Int firstColumn    (DATA_TYPE type); // return index of first 'ListColumn' which is of 'type'   , -1 on fail
   Int firstColumnText(              ); // return index of first 'ListColumn' which is of text type, -1 on fail

            _List& func(void (*func)(Ptr   user), Ptr   user=NULL);                                            // set function called when list 'sel' selection has changed, with 'user' as its parameter
   T1(TYPE) _List& func(void (*func)(TYPE *user), TYPE *user     ) {return T.func((void(*)(Ptr))func,  user);} // set function called when list 'sel' selection has changed, with 'user' as its parameter
   T1(TYPE) _List& func(void (*func)(TYPE &user), TYPE &user     ) {return T.func((void(*)(Ptr))func, &user);} // set function called when list 'sel' selection has changed, with 'user' as its parameter

            _List& funcPre(void (*func)(Ptr   user), Ptr   user=NULL);                                               // set function called when list 'sel' selection is about to change, with 'user' as its parameter
   T1(TYPE) _List& funcPre(void (*func)(TYPE *user), TYPE *user     ) {return T.funcPre((void(*)(Ptr))func,  user);} // set function called when list 'sel' selection is about to change, with 'user' as its parameter
   T1(TYPE) _List& funcPre(void (*func)(TYPE &user), TYPE &user     ) {return T.funcPre((void(*)(Ptr))func, &user);} // set function called when list 'sel' selection is about to change, with 'user' as its parameter

   // per element parameters
   _List& clearElmType      (                  ) {       _type_offset=-1                             ; return T;} // clear per element type
   _List& clearElmDesc      (                  ) {       _desc_offset=-1                             ; return T;} // clear per element description
   _List& clearElmImageColor(                  ) {_image_color_offset=-1                             ; return T;} // clear per element image color
   _List& clearElmTextColor (                  ) { _text_color_offset=-1                             ; return T;} // clear per element text  color
   _List& clearElmTextShadow(                  ) {_text_shadow_offset=-1                             ; return T;} // clear per element text  shadow
   _List& clearElmAlphaMode (                  ) { _alpha_mode_offset=-1                             ; return T;} // clear per element ALPHA_MODE
   _List& clearElmOffset    (                  ) {     _offset_offset=-1                             ; return T;} // clear per element offset
   _List& clearElmGroup     (                  ) {      _group_offset=-1                             ; return T;} // clear per element group
   _List&   setElmType      (UInt       &member) {       _type_offset=UIntPtr(&member)               ; return T;} // set   per element type        , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmDesc      (CChar*     &member) {       _desc_offset=UIntPtr(&member)               ; return T;} // set   per element description , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmDesc      (Str        &member) {       _desc_offset=UIntPtr(&member)+OFFSET(Str,_d); return T;} // set   per element description , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmImageColor(Color      &member) {_image_color_offset=UIntPtr(&member)               ; return T;} // set   per element image color , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmTextColor (Color      &member) { _text_color_offset=UIntPtr(&member)               ; return T;} // set   per element text  color , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmTextShadow(Byte       &member) {_text_shadow_offset=UIntPtr(&member)               ; return T;} // set   per element text  shadow, from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmAlphaMode (ALPHA_MODE &member) { _alpha_mode_offset=UIntPtr(&member)               ; return T;} // set   per element ALPHA_MODE  , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmOffset    (Flt        &member) {     _offset_offset=UIntPtr(&member)               ; return T;} // set   per element offset      , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required
   _List&   setElmGroup     (Str        &member) {      _group_offset=UIntPtr(&member)               ; return T;} // set   per element group       , from list data elements member, for 'member' parameter 'MEMBER' macro usage is required

   // operations
   void scrollTo(Int i     , Bool immediate=false); // scroll to i-th visible element
   void sort    (Int column, Int  swap     =-1   ); // sort according to 'column' column
   void setCur  (Int i                           ); // set cursor to specified index, and if list has 'LIST_MULTI_SEL' enabled then set 'sel' accordingly

   _List& addChild(GuiObj &child, Int abs, Int column=0); // add 'child' to the list, 'abs'=absolute element index, 'column'=list column

   // main
   virtual GuiObj* test  (C GuiPC &gpc, C Vec2 &pos, GuiObj* &mouse_wheel); // test if 'pos' screen position intersects with the object, by returning pointer to object or its children upon intersection and NULL in case no intersection, 'mouse_wheel' may be modified upon intersection either to the object or its children or NULL
   virtual void    update(C GuiPC &gpc); // update object
   virtual void    draw  (C GuiPC &gpc); // draw   object

  ~_List() {del();}
   _List();

private:
   struct Children : GuiObjChildren
   {
      struct Child : GuiObjChildren::Child
      {
         VecI2 abs_col; // x=abs, y=column
      };
      Children();
   };
   Int   _total_elms, _visible_elms, _elm_size;
   Int  *_vis_to_abs , *_abs_to_vis;
   Ptr  *_vis_to_data, *_abs_to_data;
   Rect *_rects;

   Children         _children;
   Mems<ListColumn> _columns;

   Ptr   _data;
  _Memb *_memb;
  _Memx *_memx;
  _Meml *_meml;
  _Memx *_node;

   Char _search[32];
   Byte _search_i;
   Flt  _search_t;

   LIST_DRAW_MODE _draw_mode;
   Bool           _horizontal;
   Int            _type_offset, _desc_offset, _image_color_offset, _text_color_offset, _text_shadow_offset, _alpha_mode_offset, _offset_offset, _group_offset, _children_offset, _tap_vis;
   UInt           _tap_touch_id;
   Flt            _column_height, _elm_height, _text_base, _text_rel, _image_rel, _zoom, _height_ez;
   Vec2           _image_base;
   Rect           _image_padd;
   Ptr            _func_user, _func_pre_user;
   void         (*_func)(Ptr user), (*_func_pre)(Ptr user);
   GuiSkinPtr     _skin;

protected:
  _List& _setData(Ptr data, Int elms, Int elm_size, C Memp<Bool> &visible=NULL, Bool keep_cur=false);
  _List& _setData(_Memx &node, Int children_offset, C Memp<Bool> &visible=NULL, Bool keep_cur=false);

   virtual void parentClientRectChanged(C Rect *old_client, C Rect *new_client);
   virtual void        childRectChanged(C Rect *old_rect  , C Rect *new_rect  , GuiObj &child);

   NO_COPY_CONSTRUCTOR(_List);
};
/******************************************************************************/
const_mem_addr T1(TYPE) struct List : _List // Gui List Template !! must be stored in constant memory address !!
{
   TYPE* operator()(                )C {return                visToData(cur     );} // convert visible  index to data
   TYPE* operator()(  Int   visible )C {return                visToData(visible );} // convert visible  index to data
   TYPE* visToData (  Int   visible )C {return (TYPE*)_List:: visToData(visible );} // convert visible  index to data
   Int   visToAbs  (  Int   visible )C {return        _List:: visToAbs (visible );} // convert visible  index to absolute index
   TYPE* absToData (  Int   absolute)C {return (TYPE*)_List:: absToData(absolute);} // convert absolute index to data
   Int   absToVis  (  Int   absolute)C {return        _List:: absToVis (absolute);} // convert absolute index to visible  index
   Int  dataToVis  (C TYPE *data    )C {return        _List::dataToVis (data    );} // convert data           to visible  index
   Int  dataToAbs  (C TYPE *data    )C {return        _List::dataToAbs (data    );} // convert data           to absolute index

   TYPE* screenToData(  Flt   y  , C GuiPC *gpc=NULL)C {return (TYPE*)_List::screenToData(y  , gpc);} // convert screen  position Y to data, if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)
   TYPE* screenToData(C Vec2 &pos, C GuiPC *gpc=NULL)C {return (TYPE*)_List::screenToData(pos, gpc);} // convert screen  position   to data, if you know the GuiPC then pass it to 'gpc' which will speed up calculations (otherwise leave it to NULL)

   List& setData    (TYPE       *data, Int elms, C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setData    (data, elms, visible, keep_cur); return T;} // set list data from continuous memory  !! after any change in source data, 'setData' must be called again !!
   List& setData    (Mems<TYPE> &mems,           C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setData    (mems,       visible, keep_cur); return T;} // set list data from Mems               !! after any change in source data, 'setData' must be called again !!
   List& setData    (Memc<TYPE> &memc,           C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setData    (memc,       visible, keep_cur); return T;} // set list data from Memc               !! after any change in source data, 'setData' must be called again !!
   List& setData    (Memb<TYPE> &memb,           C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setData    (memb,       visible, keep_cur); return T;} // set list data from Memb               !! after any change in source data, 'setData' must be called again !!
   List& setData    (Memx<TYPE> &memx,           C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setData    (memx,       visible, keep_cur); return T;} // set list data from Memx               !! after any change in source data, 'setData' must be called again !!
   List& setData    (Meml<TYPE> &meml,           C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setData    (meml,       visible, keep_cur); return T;} // set list data from Meml               !! after any change in source data, 'setData' must be called again !!
   List& setDataNode(Memx<TYPE> &memx,           C Memp<Bool> &visible=NULL, Bool keep_cur=false) {_List::setDataNode(memx,       visible, keep_cur); return T;} // set list data from Memx with children !! after any change in source data, 'setData' must be called again !! TYPE must have a "Memx<TYPE> children" member, for example: "struct TYPE { Memx<TYPE> children; }", in that case 'setDataNode' will add all elements including children recursively
};
/******************************************************************************/
inline Int Elms(C _List &list) {return list.elms();}
/******************************************************************************/
