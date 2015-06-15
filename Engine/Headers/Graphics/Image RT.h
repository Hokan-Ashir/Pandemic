/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum IMAGERT_TYPE // Image Render Target Type, this describes a group of Image Types
{
   IMAGERT_RGBA  , // IMAGE_DEFAULT
   IMAGERT_RGB   , // IMAGE_R10G10B10A2, IMAGE_DEFAULT
   IMAGERT_RGBA_F, // IMAGE_F16_4, IMAGE_DEFAULT
   IMAGERT_RGB_F , // IMAGE_F16_3, IMAGE_F16_4, IMAGE_R10G10B10A2, IMAGE_DEFAULT
   IMAGERT_F32   , // IMAGE_F32, IMAGE_F16
   IMAGERT_F16   , // IMAGE_F16, IMAGE_F32
   IMAGERT_ONE   , // (DX9: IMAGE_A8, IMAGE_L8A8, Rest: IMAGE_R8, IMAGE_R8G8), IMAGE_DEFAULT
   IMAGERT_TWO   , // (Non-DX9: IMAGE_R8G8), IMAGE_DEFAULT !! THIS IS SLOW, AVOID !!
   IMAGERT_DS    , // (DX9: IMAGE_INTZ, IMAGE_RAWZ, IMAGE_DF24), IMAGE_D24S8, IMAGE_D24X8, IMAGE_D32, IMAGE_D16
   IMAGERT_NUM   , // number of Image render targets
};
/******************************************************************************/
struct ImageRC : Image // Reference Counted Image
{
   ImageRC() {_ptr_num=0;}

private:
   UInt _ptr_num;
   NO_COPY_CONSTRUCTOR(ImageRC);
};
/******************************************************************************/
struct ImageRTPtr // Render Target Pointer
{
   Bool       find(Int w, Int h, IMAGERT_TYPE rt_type, Byte samples=1); // find Render Target, false on fail, 'samples'=number of samples per-pixel (allows multi-sampling)
   ImageRTPtr& get(Int w, Int h, IMAGERT_TYPE rt_type, Byte samples=1); // find Render Target, Exit  on fail, 'samples'=number of samples per-pixel (allows multi-sampling)

   Image* operator ()  (               )C {return  T._data         ;} // access the data, you can use the returned reference as long as this 'ImageRTPtr' object exists and not modified
   Image* operator ->  (               )C {return  T._data         ;} // access the data, you can use the returned reference as long as this 'ImageRTPtr' object exists and not modified
   Image& operator *   (               )C {return *T._data         ;} // access the data, you can use the returned reference as long as this 'ImageRTPtr' object exists and not modified
   Bool   operator ==  (  int          )C {return  T._data==NULL   ;} // if pointers are equal     (this simulates "T==NULL")
   Bool   operator !=  (  int          )C {return  T._data!=NULL   ;} // if pointers are different (this simulates "T!=NULL")
   Bool   operator ==  (C Image      *p)C {return  T._data==p      ;} // if pointers are equal
   Bool   operator !=  (C Image      *p)C {return  T._data!=p      ;} // if pointers are different
   Bool   operator ==  (C ImageRTPtr &p)C {return  T._data==p._data;} // if pointers are equal
   Bool   operator !=  (C ImageRTPtr &p)C {return  T._data!=p._data;} // if pointers are different
          operator Bool(               )C {return  T._data!=NULL   ;} // if pointer  is  valid

   void clear    (               );           // clear the pointer to NULL, this automatically decreases the reference count of current data
   void operator=(  int          ) {clear();} // clear the pointer to NULL, this automatically decreases the reference count of current data, this simulates "T=NULL"
   void operator=(C ImageRTPtr &p);           // set       pointer to 'p' , this automatically decreases the reference count of current data and increases the reference count of the new data
   void operator=(  ImageRC    *p);           // set       pointer to 'p' , this automatically decreases the reference count of current data and increases the reference count of the new data

   ImageRTPtr(C ImageRTPtr &p);
   ImageRTPtr(  ImageRC    *p);
   ImageRTPtr(  int          ) {_data=NULL; _last_index=-1;} // simulate NULL constructor
   ImageRTPtr(               ) {_data=NULL; _last_index=-1;}
  ~ImageRTPtr(               ) {clear();}

private:
   ImageRC *_data;
   Int      _last_index;
};
/******************************************************************************/
