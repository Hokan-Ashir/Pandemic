/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'CritSect'      for multi-threaded synchronization
   Use 'CritSectLock'  for simplified usage of the 'CritSect'
   Use 'SyncEvent'     for multi-threaded synchronization
   Use 'ReadWriteSync' to  handle synchronization between multiple "reader" and "writer" threads, where multiple "readers" can access a resource at once, while only 1 "writer" (and no other "readers" or "writers") can access a resource at once
   Use 'Thread'        to  run functions simultaneously on the Cpu

   Use 'MultiThreadedCall' to process data in multi-threaded mode by splitting the work into multiple threads

   Use 'Proc' functions for OS processes management.

/******************************************************************************/
struct CritSect // Critical Section (multi-threaded safe)
{
   Bool owned()C; // if           critical section is owned by current thread
   Bool tryOn()C; // try entering critical section, false on fail (after receiving 'true' you must call the 'off' method, while after receiving 'false' you may not call the 'off' method)
   void on   ()C; //     enter    critical section
   void off  ()C; //     leave    critical section

  ~CritSect();
   CritSect();

private:
   UInt _cs[20];
   NO_COPY_CONSTRUCTOR(CritSect);
};
struct CritSectLock // Critical Section Lock (automatically locks and unlocks the critical section at object creation and destruction)
{
   CritSectLock(C CritSect &cs) : _cs(cs) {_cs.on ();}
  ~CritSectLock(              )           {_cs.off();}

private:
 C CritSect &_cs;
   NO_COPY_CONSTRUCTOR(CritSectLock);
};
struct CritSectLockEx // Critical Section Lock Extended
{
   void on () {if(!_on){_on=true ; _cs.on ();}} // manually enter critical section
   void off() {if( _on){_on=false; _cs.off();}} // manually leave critical section

   Bool tryOn() {if(!_on && _cs.tryOn())_on=true; return _on;} // try entering critical section, false on fail

   CritSectLockEx(C CritSect &cs, Bool on=true) : _cs(cs) {if(T._on=on)cs.on();}
  ~CritSectLockEx(                            )           {off();}

private:
   Bool      _on;
 C CritSect &_cs;
   NO_COPY_CONSTRUCTOR(CritSectLockEx);
};
/******************************************************************************/
struct SyncEvent // Synchronization Event (multi-threaded safe)
{
   void on  (                   ); //   activate
   void off (                   ); // deactivate
   Bool wait(Int milliseconds=-1); // wait 'milliseconds' until activated (<0 = infinite wait), false on timeout

  ~SyncEvent();
   SyncEvent();

private:
   Bool _condition;
   Ptr  _handle, _mutex;
   NO_COPY_CONSTRUCTOR(SyncEvent);
};
/******************************************************************************/
struct ReadWriteSync // allows multiple "readers/writers" synchronization (multi-threaded safe)
{
   void enterRead(); // enter reading (shared mode)
   void leaveRead(); // leave reading (shared mode)

   void enterWrite(); // enter writing (exclusive mode)
   void leaveWrite(); // leave writing (exclusive mode)

private:
   struct Lock
   {
      UIntPtr thread_id;
      Int     locks;
   };
   CritSect   _lock_cs, _write_cs;
   SyncEvent  _left_reading;
   Memc<Lock> _lock;
};
struct ReadLock // ReadWriteSync Read Lock (automatically locks and unlocks for reading the 'ReadWriteSync' at object creation and destruction)
{
   ReadLock(ReadWriteSync &rws) : _rws(rws) {_rws.enterRead();}
  ~ReadLock(                  )             {_rws.leaveRead();}

private:
   ReadWriteSync &_rws;
   NO_COPY_CONSTRUCTOR(ReadLock);
};
struct WriteLock // ReadWriteSync Write Lock (automatically locks and unlocks for writing the 'ReadWriteSync' at object creation and destruction)
{
   WriteLock(ReadWriteSync &rws) : _rws(rws) {_rws.enterWrite();}
  ~WriteLock(                  )             {_rws.leaveWrite();}

private:
   ReadWriteSync &_rws;
   NO_COPY_CONSTRUCTOR(WriteLock);
};
/******************************************************************************/
const_mem_addr struct Thread // Thread !! must be stored in constant memory address !!
{
   Ptr user; // user data

   // get
   Bool created   ()C {return _handle!=NULL;} // if the thread is created             (this will be false only if the thread hasn't yet been created, or if it has been manually deleted, if the thread was created but stopped running, the return value will be still true)
   Bool active    ()C {return _active      ;} // if the thread is created and running (this will be false      if the thread hasn't yet been created, or if it has been manually deleted,                         or it stopped running                                     )
   Bool wantToStop()C {return _want_stop   ;} // if the thread is requested to be stopped by the 'stop' method
   Int  priority  ()C {return _priority    ;} // get    thread priority (-2..2)

   // manage
   Bool create    (Bool func(Thread &thread), Int priority=0, Int sleep=0, Int sleep_min=0, Ptr user=NULL, Bool paused=false); // create, 'func'=function which will be called in the created thread, 'priority'=thread priority (-2..2), 'sleep'=how much milliseconds to sleep between continuous 'func' calls, 'sleep_min'=minimum of milliseconds to sleep between continuous 'func' calls, 'user'=custom user data, 'paused'=if start the thread in paused mode, threads have a default stack size of 1MB, if the thread will require performing operations on GPU data, then you must call 'ThreadMayUseGPUData' inside the thread, please check that function comments for more info
   void del       (Int milliseconds=-1); // delete thread, if it's active then wait 'milliseconds' until finishes (<0 = infinite wait), if after the waiting time it's still active then the thread will be killed
   void       stop(                   ); // stop   thread, notifies that the thread should stop calling 'func' and exit, this method doesn't however wait until the thread exits
   void cancelStop(                   ); // cancel thread stopping, this method has no effect if the thread has already been stopped
   void pause     (                   ); // pause  thread, 'func' will no longer be called until the thread is resumed
   void resume    (                   ); // resume thread from paused state
   void priority  (Int priority       ); // set    thread priority, 'priority'=-2..2
   void kill      (                   ); // kill   thread, immediately shut down the thread, usage of this method is not recommended because it may cause memory leaks
   Bool wait      (Int milliseconds=-1); // wait   until the thread finishes processing (<0 = infinite wait), false on timeout

  ~Thread() {del();}
   Thread();
   Thread(Bool func(Thread &thread), Int priority=0, Int sleep=0, Int sleep_min=0, Ptr user=NULL, Bool paused=false);

private:
   Bool   _want_stop, _want_pause, _active, _paused;
   Int    _priority, _sleep, _sleep_min;
   Ptr    _handle;
   Bool (*_func)(Thread &thread);
#ifndef WINDOWS
   SyncEvent _se;
#endif
   NO_COPY_CONSTRUCTOR(Thread);
};
/******************************************************************************/
const_mem_addr struct Threads // Worker Threads, allow to process data on multiple threads !! must be stored in constant memory address !!
{
   void del   (                                     ); // delete the threads without finishing all queued work
   void create(Bool ordered, Int threads=Cpu.cores()); // 'ordered'=if process queued elements in the order as they were given (this will be a bit slower)

   // perform multi-threaded call on 'func' function, by giving a unique 'data' element from the memory container as the function parameter, this function will return only after all elements have been processed
   T1(DATA           )   void process(Mems<DATA> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T1(DATA           )   void process(Memc<DATA> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T1(DATA           )   void process(Memt<DATA> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T1(DATA           )   void process(Memb<DATA> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int max_threads=-1) {_process(data       ,                              (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T1(DATA           )   void process(Memx<DATA> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int max_threads=-1) {_process(data       ,                              (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T2(DATA, USER_DATA)   void process(Mems<DATA> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memc<DATA> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memt<DATA> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memb<DATA> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int max_threads=-1) {_process(data       ,                              (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memx<DATA> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int max_threads=-1) {_process(data       ,                              (void (*)(Ptr data, Ptr user))func,  user, max_threads);}
   T2(DATA, USER_DATA)   void process(Mems<DATA> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memc<DATA> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memt<DATA> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int max_threads=-1) {_process(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memb<DATA> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int max_threads=-1) {_process(data       ,                              (void (*)(Ptr data, Ptr user))func, &user, max_threads);}
   T2(DATA, USER_DATA)   void process(Memx<DATA> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int max_threads=-1) {_process(data       ,                              (void (*)(Ptr data, Ptr user))func, &user, max_threads);}

   // queue call on 'func' function with 'data' and 'user' parameters to be performed on one of the worker threads, this function will queue the object for processing and return immediately without waiting for it to be processed
   T1(DATA           )   void queue(DATA &data, void func(DATA &data, Ptr        user), Ptr        user=NULL) {_queue((Ptr)&data, (void (*)(Ptr data, Ptr user))func,  user);}
   T2(DATA, USER_DATA)   void queue(DATA &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL) {_queue((Ptr)&data, (void (*)(Ptr data, Ptr user))func,  user);}
   T2(DATA, USER_DATA)   void queue(DATA &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     ) {_queue((Ptr)&data, (void (*)(Ptr data, Ptr user))func, &user);}

   // cancel queued call on 'func' function with 'data' and 'user' parameters
   T1(DATA           )   void     cancel(DATA &data, void func(DATA &data, Ptr        user), Ptr        user=NULL) {_cancel((Ptr)&data, (void (*)(Ptr data, Ptr user))func,  user);}
   T2(DATA, USER_DATA)   void     cancel(DATA &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL) {_cancel((Ptr)&data, (void (*)(Ptr data, Ptr user))func,  user);}
   T2(DATA, USER_DATA)   void     cancel(DATA &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     ) {_cancel((Ptr)&data, (void (*)(Ptr data, Ptr user))func, &user);}
                         Threads& cancel(); // cancel all queued calls

   // wait until queued call on 'func' function with 'data' and 'user' parameters has finished processing
   T1(DATA           )   void     wait(DATA &data, void func(DATA &data, Ptr        user), Ptr        user=NULL) {_wait((Ptr)&data, (void (*)(Ptr data, Ptr user))func,  user);}
   T2(DATA, USER_DATA)   void     wait(DATA &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL) {_wait((Ptr)&data, (void (*)(Ptr data, Ptr user))func,  user);}
   T2(DATA, USER_DATA)   void     wait(DATA &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     ) {_wait((Ptr)&data, (void (*)(Ptr data, Ptr user))func, &user);}
                         Threads& wait(); // wait until all queued calls have finished processing

   Int  threads()C {return _threads.elms();} // get number of threads that were created for this object
   Int  queued ()C;                          // get number of elements still waiting in the queue for processing (this includes elements being currently processed)
   Bool busy   ()C;                          // if there's something being processed right now

  ~Threads() {del();}

private:
   struct Call
   {
      Ptr    data, user;
      void (*func)(Ptr data, Ptr user);
   };
   struct ThreadEx : Thread
   {
      Call      call;
      SyncEvent se;
      ThreadEx();
     ~ThreadEx();
   };
   Mems<ThreadEx> _threads;
   Memc<Call    > _calls;
   SyncEvent      _se;
   CritSect       _cs, _cs2;
   Call           _call;
  _Memb          *_memb;
  _Memx          *_memx;
   Bool           _ordered;
   Int            _left, _processed, _elms;
   Int            _elm_size;

   void _process( Ptr   data, Int elms, Int elm_size, void func(Ptr data, Ptr user), Ptr user, Int max_threads);
   void _process(_Memb &data,                         void func(Ptr data, Ptr user), Ptr user, Int max_threads);
   void _process(_Memx &data,                         void func(Ptr data, Ptr user), Ptr user, Int max_threads);

   void _queue (Ptr data, void func(Ptr data, Ptr user), Ptr user);
   void _cancel(Ptr data, void func(Ptr data, Ptr user), Ptr user);
   void _wait  (Ptr data, void func(Ptr data, Ptr user), Ptr user);
};
/******************************************************************************/
struct ConsoleProcess // allows running console processes and reading their output
{
   // get
   Bool created ()C;                     // if the process is created             (this will be false only if the process hasn't yet been created, or if it has been manually deleted, if the process was created but stopped running, the return value will be still true)
   Bool active  ()C;                     // if the process is created and running (this will be false      if the process hasn't yet been created, or if it has been manually deleted,                          or it stopped running                                     )
   Int  exitCode()C {return _exit_code;} // get exit code of the process

   // manage
   void del      (); // request process to be closed and close all handles without killing it
   Bool create   (C Str &name  , C Str &params=S, Bool hidden=true, Bool binary=false); // 'name'=process file to execute, 'params'=custom params to be passed to the process, 'hidden'=if start the process as hidden, 'binary'=if treat the output as binary data
   Bool createMem(C Str &script, C Str &cur_dir , Bool hidden=true, Bool binary=false); // 'script'=list of commands to be executed, multiple commands should be separated with new line '\n' character, commands will be executed by cmd.exe on Windows (they should be BAT compatible) and bash on Unix (they should be SH compatible), 'cur_dir'=directory at which the commands should be executed, 'hidden'=if start the process as hidden, 'binary'=if treat the output as binary data

   // operations
   Bool wait(Int milliseconds=-1); // wait 'milliseconds' for process to close (-1 for infinite), false on fail
   void stop(); // request process to be closed
   void kill(); // kill the process
   
   // io
   Str get(); // read new data that the console did output

  ~ConsoleProcess() {del();}
   ConsoleProcess() {_binary=false; _exit_code=-1; _proc_id=0; _proc=_out_read=_in_write=NULL;}

private:
   Bool     _binary;
   Int      _exit_code;
   UInt     _proc_id;
   Ptr      _proc, _out_read, _in_write;
   Str8     _data;
   CritSect _cs;
   Thread   _thread;
   NO_COPY_CONSTRUCTOR(ConsoleProcess);
};
/******************************************************************************/
UIntPtr GetThreadId          (                               ); // get current thread id
UIntPtr GetThreadIdFromWindow(Ptr hwnd                       ); // get id of the thread which owns the OS window handle
void    SetThreadName        (UIntPtr thread_id, C Str8 &name); // set custom thread name for debugging purpose, supported only under Windows

void ThreadMayUseGPUData       (); // call    this from a secondary thread if you expect the thread to perform any operations on GPU data (like Mesh, Material, Image, Shaders, ..., this includes any operation like creating, editing, loading, saving, deleting, ...). This function is best called at the start of the thread, it needs to be called at least once, further calls are ignored. Once the function is called, the thread locks a secondary OpenGL context (if no context is available, then the function waits until other threads finish processing and release their context lock, amount of OpenGL contexts is specified in 'D.secondaryOpenGLContexts'). Context lock is automatically released once the thread exits. This call is required only for OpenGL renderer.
void ThreadFinishedUsingGPUData(); // calling this function is optional (it does not need to be called manually), call it if you wish to manually release a thread from locking an OpenGL context. Threads automatically call this function at end of their life, which means that they automatically release any locked contexts, however in some scenarios you may want to manually release any locked context if you wish to provide more contexts for background processing on other threads. This call is used only for OpenGL renderer.

// Multi-threaded calls
   // base functions, do not use
   void _MultiThreadedCall                 ( Ptr   data, Int elms, Int elm_size, void func(Ptr data     ,                                        Ptr user), Ptr user, Int threads,             Bool data_ptr);
   void _MultiThreadedCall                 (_Memb &data,                         void func(Ptr data     ,                                        Ptr user), Ptr user, Int threads,             Bool data_ptr);
   void _MultiThreadedCall                 (_Memx &data,                         void func(Ptr data     ,                                        Ptr user), Ptr user, Int threads,             Bool data_ptr);
   void _MultiThreadedCallWithPerThreadData(             Int elms,               void func(Int elm_index, Int thread_index, Ptr per_thread_data, Ptr user), Ptr user, Int threads, _Memc &ptd               );
   void _MultiThreadedCallWithPerThreadData( Ptr   data, Int elms, Int elm_size, void func(Ptr data     , Int thread_index, Ptr per_thread_data, Ptr user), Ptr user, Int threads, _Memc &ptd, Bool data_ptr);
   void _MultiThreadedCallWithPerThreadData(_Memb &data,                         void func(Ptr data     , Int thread_index, Ptr per_thread_data, Ptr user), Ptr user, Int threads, _Memc &ptd, Bool data_ptr);
   void _MultiThreadedCallWithPerThreadData(_Memx &data,                         void func(Ptr data     , Int thread_index, Ptr per_thread_data, Ptr user), Ptr user, Int threads, _Memc &ptd, Bool data_ptr);

   // perform multi-threaded call on 'func' function, by giving a unique 'elm_index' from the "0 .. elms-1" range as the function parameter
                   void MultiThreadedCall(Int elms, void func(Int elm_index, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores());
   T1(USER_DATA)   void MultiThreadedCall(Int elms, void func(Int elm_index, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {MultiThreadedCall(elms, (void (*)(Int elm_index, Ptr user))func,  user, threads);}
   T1(USER_DATA)   void MultiThreadedCall(Int elms, void func(Int elm_index, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {MultiThreadedCall(elms, (void (*)(Int elm_index, Ptr user))func, &user, threads);}

   // perform multi-threaded call on 'func' function, by giving a unique 'data' element from the memory container as the function parameter
   T1(DATA           )   void MultiThreadedCall(Mems<DATA > &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T1(DATA           )   void MultiThreadedCall(Mems<DATA*> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T1(DATA           )   void MultiThreadedCall(Memc<DATA > &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T1(DATA           )   void MultiThreadedCall(Memc<DATA*> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T1(DATA           )   void MultiThreadedCall(Memt<DATA > &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T1(DATA           )   void MultiThreadedCall(Memt<DATA*> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T1(DATA           )   void MultiThreadedCall(Memb<DATA > &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T1(DATA           )   void MultiThreadedCall(Memb<DATA*> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T1(DATA           )   void MultiThreadedCall(Memx<DATA > &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T1(DATA           )   void MultiThreadedCall(Memx<DATA*> &data, void func(DATA &data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Mems<DATA > &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Mems<DATA*> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memc<DATA > &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memc<DATA*> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memt<DATA > &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memt<DATA*> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memb<DATA > &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memb<DATA*> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memx<DATA > &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memx<DATA*> &data, void func(DATA &data, USER_DATA *user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func,  user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Mems<DATA > &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Mems<DATA*> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memc<DATA > &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memc<DATA*> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memt<DATA > &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memt<DATA*> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Ptr user))func, &user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memb<DATA > &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func, &user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memb<DATA*> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func, &user, threads, true );}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memx<DATA > &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func, &user, threads, false);}
   T2(DATA, USER_DATA)   void MultiThreadedCall(Memx<DATA*> &data, void func(DATA &data, USER_DATA &user), USER_DATA &user     , Int threads=Cpu.cores()) {_MultiThreadedCall(data                                    , (void (*)(Ptr data, Ptr user))func, &user, threads, true );}

// Multi-threaded calls with per thread data
   // perform multi-threaded call on 'func' function, by giving a unique 'elm_index' from the "0 .. elms-1" range as the function parameter, each function will have its own 'per_thread_data'
   T1(PER_THREAD_DATA           )   void MultiThreadedCallWithPerThreadData(Int elms, void func(Int elm_index, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(elms, (void (*)(Int elm_index, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd);}
   T2(PER_THREAD_DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Int elms, void func(Int elm_index, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(elms, (void (*)(Int elm_index, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd);}
   T2(PER_THREAD_DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Int elms, void func(Int elm_index, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(elms, (void (*)(Int elm_index, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd);}

   // perform multi-threaded call on 'func' function, by giving a unique 'data' element from the memory container as the function parameter, each function will have its own 'per_thread_data'
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Mems<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Mems<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memc<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memc<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memt<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memt<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memb<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memb<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memx<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T2(PER_THREAD_DATA, DATA           )   void MultiThreadedCallWithPerThreadData(Memx<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, Ptr        user), Ptr        user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Mems<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Mems<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memc<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memc<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memt<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memt<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memb<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memb<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memx<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memx<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA* user), USER_DATA *user=NULL, Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func,  user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Mems<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Mems<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memc<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memc<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memt<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memt<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data.data(), data.elms(), data.elmSize(), (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memb<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memb<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, true );}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memx<DATA > &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, false);}
   T3(PER_THREAD_DATA, DATA, USER_DATA)   void MultiThreadedCallWithPerThreadData(Memx<DATA*> &data, void func(DATA &data, Int thread_index, PER_THREAD_DATA &per_thread_data, USER_DATA& user), USER_DATA &user     , Int threads=Cpu.cores()) {Memc<PER_THREAD_DATA> ptd; _MultiThreadedCallWithPerThreadData(data                                    , (void (*)(Ptr data, Int thread_index, Ptr per_thread_data, Ptr user))func, &user, threads, ptd, true );}

// Process functions
UInt ProcGet     (  Ptr  hwnd                   ); // get   process from OS window handle
void ProcPriority(  Int  priority               ); // set   process priority (-2..2)
void ProcClose   ( UInt  id                     ); // close process
void ProcClose   (C Str &name                   ); // close process
Bool ProcKill    ( UInt  id                     ); // kill  process, false on fail
Bool ProcKill    (C Str &name                   ); // kill  process, false on fail
Bool ProcWait    ( UInt  id, Int milliseconds=-1); // wait  for process to exit (<0 = infinite wait), false on timeout
Ptr  ProcWindow  ( UInt  id                     ); // get   OS window handle of process
Str  ProcName    ( UInt  id                     ); // get   process name
UInt ProcFind    (C Str &name                   ); // find  process id
void ProcList    (Memp<UInt> id                 ); // get   list of process id's, after calling this function the 'id' will contain a list of process id's

// Atomic operations
Int AtomicInc(Int &x); // increase value of 'x' by 1 in an atomic operation and return its previous value, this is a thread-safe version of function "return x++;" (this allows to modify the value across multiple threads without usage of critical sections)
Int AtomicDec(Int &x); // decrease value of 'x' by 1 in an atomic operation and return its previous value, this is a thread-safe version of function "return x--;" (this allows to modify the value across multiple threads without usage of critical sections)

Int AtomicAdd(Int &x, Int y); // increase value of 'x' by 'y' in an atomic operation and return its previous value, this is a thread-safe version of function "Int old=x; x+=y; return old;" (this allows to modify the value across multiple threads without usage of critical sections)
Int AtomicSub(Int &x, Int y); // decrease value of 'x' by 'y' in an atomic operation and return its previous value, this is a thread-safe version of function "Int old=x; x-=y; return old;" (this allows to modify the value across multiple threads without usage of critical sections)

Int AtomicOr (Int &x, Int y); // or       value of 'x' by 'y' in an atomic operation and return its previous value, this is a thread-safe version of function "Int old=x; x|=y; return old;" (this allows to modify the value across multiple threads without usage of critical sections)

Int AtomicSet(Int &x, Int y); // set      value of 'x' to 'y' in an atomic operation and return its previous value, this is a thread-safe version of function "Int old=x; x =y; return old;" (this allows to modify the value across multiple threads without usage of critical sections)
/******************************************************************************/
