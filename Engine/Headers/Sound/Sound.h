/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'SoundVolume' to set  volume for different sound groups
   Use 'SoundPlay'   to play custom sounds
   Use 'Sound'       to play custom sounds and control them later
   Use 'Listener'    to set  3D listener parameters which receives 3D sounds

/******************************************************************************/
enum SOUND_CODEC
{
   SOUND_NONE   , // none
   SOUND_WAV    , // waveform
   SOUND_OGG    , // ogg vorbis
   SOUND_MP3    , // mp3
   SOUND_DYNAMIC, // data is provided dynamically from user provided 'SoundCallback'
};
/******************************************************************************/
enum VOLUME_GROUP // Sound Volume Group
{
   VOLUME_FX     , // Sound Effects
   VOLUME_MUSIC  , // Music
   VOLUME_AMBIENT, // Ambient Surroundings
   VOLUME_VOICE  , // Voices
};
/******************************************************************************/
struct SoundVolumeClass
{
   void fx     (Flt v);   Flt fx     ()C {return _fx     ;} // set/get fx      volume (0..1)
   void music  (Flt v);   Flt music  ()C {return _music  ;} // set/get music   volume (0..1)
   void ambient(Flt v);   Flt ambient()C {return _ambient;} // set/get ambient volume (0..1)
   void voice  (Flt v);   Flt voice  ()C {return _voice  ;} // set/get voice   volume (0..1)
   void global (Flt v);   Flt global ()C {return _global ;} // set/get global  volume (0..1)

private:
   union
   {
      struct{Flt                                  _d[5];};
      struct{Flt _fx, _music, _ambient, _voice, _global;};
   };
   SoundVolumeClass();
}extern
   SoundVolume; // Main Sound Volume Control
/******************************************************************************/
struct ListenerClass
{
   // get
 C Vec& pos()C {return _pos;} // get listener position
 C Vec& dir()C {return _dir;} // get listener looking direction
 C Vec& up ()C {return _up ;} // get listener up      direction

   // set
   ListenerClass& orn(C Vec &dir, C Vec &up =Vec(0, 1, 0)); // set listener orientation, 'dir'=looking direction (must be normalized), 'up'=up direction (must be normalized)
   ListenerClass& pos(C Vec &pos, C Vec &vel=VecZero     ); // set listener position and velocity

   ListenerClass& mute() {return pos(Vec(FLT_MAX));} // mute 3d sound listener, this is done by moving the listener to a very distant location where no sounds are normally located

private:
   Vec _pos, _vel, _dir, _up;
   ListenerClass();
};extern ListenerClass
   Listener; // Main 3D Sound Listener Control
/******************************************************************************/
struct Sound
{
   // manage
   Sound& del   ();
   Sound& create(               C Str         &name,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create             sound, 'name'=sound file name   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(               C UID         &id  ,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create             sound, 'id'  =sound file name id,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(const_mem_addr SoundCallback &call,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create             sound, 'call'=sound call back   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(               C Str         &name, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create          3D sound, 'name'=sound file name   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(               C UID         &id  , C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create          3D sound, 'id'  =sound file name id, 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Sound& create(const_mem_addr SoundCallback &call, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX);                                                                      // create          3D sound, 'call'=sound call back   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Bool   play  (               C Str         &name,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(name,             loop, volume, volume_group).play();} // create and play    sound, 'name'=sound file name   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Bool   play  (               C UID         &id  ,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(id  ,             loop, volume, volume_group).play();} // create and play    sound, 'id'  =sound file name id,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Bool   play  (const_mem_addr SoundCallback &call,                          Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(call,             loop, volume, volume_group).play();} // create and play    sound, 'call'=sound call back   ,                                                                       , 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Bool   play  (               C Str         &name, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(name, pos, range, loop, volume, volume_group).play();} // create and play 3D sound, 'name'=sound file name   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Bool   play  (               C UID         &id  , C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(id  , pos, range, loop, volume, volume_group).play();} // create and play 3D sound, 'id'  =sound file name id, 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)
   Bool   play  (const_mem_addr SoundCallback &call, C Vec &pos, Flt range=1, Bool loop=false, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX) {return create(call, pos, range, loop, volume, volume_group).play();} // create and play 3D sound, 'call'=sound call back   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'loop'=if sound is looped, 'volume'=sound volume (0..1)

   // stop / play
   Sound& stop (); // stop
   Sound& pause(); // pause
   Bool   play (); // play

   // get / set
                                   Bool is       ()C; // if created
                                   Bool playing  ()C; // if playing
                           SOUND_CODEC  codec    ()C; //     get source codec
                                CChar8* codecName()C; //     get source codec name
                                   Str  name     ()C; //     get source file  name
                                   UID  id       ()C; //     get source file  name id
                                   Int  raws     ()C; //     get source raw   length
                                   Flt  length   ()C; //     get source time  length
                                   Int  channels ()C; //     get source number of channels
                                   Int  freq     ()C; //     get source frequency rate
                                   Int  bitRate  ()C; //     get source bit rate
   Sound& raw   (  Int  raw   );   Int  raw      ()C; // set/get sound raw      position  , 0..raws  ()
   Sound& time  (  Flt  t     );   Flt  time     ()C; // set/get sound time     position  , 0..length()
   Sound& frac  (  Flt  f     );   Flt  frac     ()C; // set/get sound fraction position  , 0..1
   Sound& loop  (  Bool loop  );   Bool loop     ()C; // set/get sound looping            , true/false
   Sound& volume(  Flt  volume);   Flt  volume   ()C; // set/get sound volume             , 0..1
   Sound& speed (  Flt  speed );   Flt  speed    ()C; // set/get sound speed              , 0..3, default=1
   Sound& range (  Flt  range );   Flt  range    ()C; // set/get sound 3D range multiplier, 0..Inf
   Sound& pos   (C Vec &pos   );   Vec  pos      ()C; // set/get sound 3D position
   Sound& vel   (C Vec &vel   );   Vec  vel      ()C; // set/get sound 3D velocity

   // volume fade
   Sound& fadeInFromSilence(Flt fade_duration); // perform volume fade-in  from silence              to max  volume
   Sound& fadeIn           (Flt fade_duration); // perform volume fade-in  from current volume level to max  volume
   Sound& fadeOut          (Flt fade_duration); // perform volume fade-out from current volume level to zero volume

   // io
   void save(File &f)C; // save sound state (name, raw, pos, volume, ..)
   Bool load(File &f) ; // load sound state (name, raw, pos, volume, ..), false on fail

  ~Sound() {del();}
   Sound() {sound=NULL;}

private:
   Ptr sound;
   NO_COPY_CONSTRUCTOR(Sound);
};
/******************************************************************************/
CChar8* CodecName(SOUND_CODEC codec); // get codec name

Bool CacheSound(C Str &name); // cache sound file into memory so it won't be played every time from the disk, usage of this function is optional, you can call it at some initialization stage of your game, false on fail
Bool CacheSound(C UID &id  ); // cache sound file into memory so it won't be played every time from the disk, usage of this function is optional, you can call it at some initialization stage of your game, false on fail

void SoundPlay(               C Str         &name,                          Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play    sound, 'name'=sound file name                                                                           , 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(               C UID         &id  ,                          Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play    sound, 'id'  =sound file name id                                                                        , 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(const_mem_addr SoundCallback &call,                          Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play    sound, 'call'=sound call back                                                                           , 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(               C Str         &name, C Vec &pos, Flt range=1, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play 3D sound, 'name'=sound file name   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(               C UID         &id  , C Vec &pos, Flt range=1, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play 3D sound, 'id'  =sound file name id, 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
void SoundPlay(const_mem_addr SoundCallback &call, C Vec &pos, Flt range=1, Flt volume=1, VOLUME_GROUP volume_group=VOLUME_FX, Flt speed=1); // play 3D sound, 'call'=sound call back   , 'pos'=sound position in World, 'range'=sound range multiplier (0..Inf), 'volume'=sound volume (0..1), 'speed'=sound speed (0..3)
/******************************************************************************/
