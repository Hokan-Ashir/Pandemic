/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'SoundCallback' to play dynamically generated sound data.

   Use 'AppVolume' to set the total application volume in the operating system.

   Use 'SoundCapture' to capture sound data.

/******************************************************************************/
const_mem_addr struct SoundCallback // Sound Callback used to dynamically create sound data !! must be stored in constant memory address !! this object is passed on to functions which store pointer to it, therefore it must be stored in a constant memory address
{
   virtual Bool create(Byte &bits, Byte &channels, Int &frequency, Int &raw_length, Int &bit_rate)=NULL; // 'create' will be called upon creation of the sound, you should override this method and inside it fill all of the parameters, 'bits'=number of bits per sample (valid values are 8 and 16), 'channels'=number of channels (valid values are '1'=mono, '2'=stereo), 'frequency'=number of samples per second (valid values are 1..192000, recommended value is 44100), 'raw_length'=total size of the uncompressed sound data in bytes (use -1 if the size is unknown), 'bit_rate'=this parameter is optional, it specifies the average number of compressed data bytes needed to fill a 1 second of uncompressed data (use -1 if unknown), return false on fail, warning: this may get called on secondary thread
   virtual Bool raw   (Int   raw           ) {return true;} // 'raw' will be called when the sound is being requested to jump to specified position, the position is specified in raw bytes of uncompressed data, return false on fail, warning: this may get called on secondary thread
   virtual Int  set   (Ptr   data, Int size)=NULL;          // 'set' will be called when the sound is being requested to fill the 'data' buffer with raw uncompressed sound data of 'size' length, you should not write more data than requested 'size', return the number of bytes written or -1 on fail, warning: this may get called on secondary thread
   virtual void del   (                    ) {}             // 'del' will be called when the sound is being destroyed, and this callback will no longer be accessed by it, warning: this may get called on secondary thread
};
/******************************************************************************/
struct AppVolumeClass // Application Volume (in the system) Control
{
   // get / set
   void volume(Flt  volume);   Flt  volume()C; // set/get volume (0..1)
   void mute  (Bool mute  );   Bool mute  ()C; // set/get mute   (true/false)

private:
   AppVolumeClass();
}extern
   AppVolume;
/******************************************************************************/
struct SoundCaptureClass
{
   struct Device
   {
      Str name;
      UID id  ;

      Device() {id.zero();}
   };

   static void GetDevices(Memp<Device> devices); // get list of sound capture devices in the system

   void del   (); // manually delete, this doesn't need to be called as the engine will automatically delete the sound capture at the application end, however you may want to call this if you no longer want to capture sounds
   Bool create(Device *device=NULL, Int bits=16, Int channels=1, Int frequency=44100); // start capturing using specified 'device' (use NULL for default), 'bits'=bits per sample (8 or 16), 'channels'=number of channels (1 or 2), 'frequency'=recording frequency, false on fail

   Bool is() {return _buf.data()!=NULL;} // if sound capture is currently created

   void update(); // update the sound capture to get the most recent data, normally you don't need to call this as the buffer will get automatically updated over time, however you may want to call this if you need to make sure that all latest data is available in the buffer (if you want immediate access - lowest latency)

   CPtr data()C {return _buf.data();} // get pointer to captured sound data buffer, this buffer is initialized during 'create' method and will exist until the 'del' method
   Int  size()C {return _buf.elms();} // get size    of captured sound data buffer (in bytes)
   Int  pos ()C {return _pos       ;} // get current position in the buffer        (in bytes)

  ~SoundCaptureClass() {del();}
   SoundCaptureClass();

private:
   Int        _pos;
   Mems<Byte> _buf;
   Ptr _dsc, _dscb;
   NO_COPY_CONSTRUCTOR(SoundCaptureClass);
}extern
   SoundCapture;
/******************************************************************************/
