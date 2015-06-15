/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Cpu' to check your cpu capabilities.

/******************************************************************************/
enum CPU_FLAG // CPU Flags
{
   CPU_MMX   =0x01, // if MMX     supported
   CPU_3DNOW =0x02, // if 3DNow   supported
   CPU_SSE   =0x04, // if SSE     supported
   CPU_SSE2  =0x08, // if SSE 2   supported
   CPU_SSE3  =0x10, // if SSE 3   supported
   CPU_SSE4_1=0x20, // if SSE 4.1 supported
   CPU_SSE4_2=0x40, // if SSE 4.2 supported
};
/******************************************************************************/
struct CPU // Central Processing Unit
{
   // get
   UInt  cores()C {return _cores;} // number of available cores
   UInt  flag ()C {return _flag ;} // get CPU_FLAG
 C Str8& name ()C {return _name ;} // get cpu name

private:
   UInt _cores, _flag;
   Str8 _name;
}extern
   Cpu;
/******************************************************************************/
inline Int Elms(C CPU &cpu) {return cpu.cores();}
/******************************************************************************/
