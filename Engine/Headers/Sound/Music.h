/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'MusicManager's 'Music' and 'Ambient' to play different 'Playlist's.

   A 'Playlist' is a list of multiple songs.

/******************************************************************************/
const_mem_addr struct Playlist // List of Music Tracks !! must be stored in constant memory address !!
{
   Flt volume; // volume multiplier for songs played from this playlist, 0..1, default=1 (this value is taken only when a new song is played, the value is not taken if a song is already playing)

   // get
   Int songs (     )C {return _songs.elms();} // get number           of      songs in this playlist
   Str song  (Int i)C;                        // get the file name    of i-th song  in this playlist, NULL    on fail
   UID songID(Int i)C;                        // get the file name id of i-th song  in this playlist, UIDZero on fail

   // operations
   void operator+=(C Str &name); // add song to playlist, 'name'=song file name
   void operator+=(C UID &id  ); // add song to playlist, 'id'  =song file name id

  ~Playlist();
   Playlist();

private:
   Int       _cur;
   Memc<Int> _songs;
};
/******************************************************************************/
struct MusicManager
{
   Bool shuffle   ; // if select songs from Playlist's in random order, default=true
   Flt  fade_in   , // fade in  time for starting  new songs            , default=0.5
        fade_out  , // fade out time for finishing old songs            , default=3.0
        time_reset; // minimum  time left needed to play a song again from its last position instead of playing it from the start, default=10, for example: if song "A" was playing, and user manually switched to song "B", the last position of "A" song is remembered before switching to "B" song, then if user switches back to "A" song, the engine first checks if last position of "A" song has at least 'time_reset' seconds before the end of the song, if yes then song "A" is played from its last remembered position, if not then it is played from the start of the song

   // get
   Str       name    ()C;                    // current song file name
   UID       id      ()C;                    // current song file name id
   Flt       time    ()C;                    // current song time position
   Flt       length  ()C;                    // current song length
   Playlist* playlist()C {return _playlist;} // active  playlist

   // set
   void set (const_mem_addr Playlist *playlist             );                         // set active   playlist, this playlist will be used after current song finishes playing
   void set (const_mem_addr Playlist &playlist             ) {set (&playlist      );} // set active   playlist, this playlist will be used after current song finishes playing
   void play(const_mem_addr Playlist *playlist, Int song=-1);                         // set and play playlist with 'song' i-th song in the playlist (-1=last played song in the playlist)
   void play(const_mem_addr Playlist &playlist, Int song=-1) {play(&playlist, song);} // set and play playlist with 'song' i-th song in the playlist (-1=last played song in the playlist)

   void next(); // skip to the next song from active playlist

private:
   Int          _song [2];
   Sound        _sound[2];
   VOLUME_GROUP _volume_group;
   Playlist    *_playlist;
   explicit MusicManager(VOLUME_GROUP volume_group);
   NO_COPY_CONSTRUCTOR(MusicManager);
}extern
   Music  , // Music   MusicManager with VOLUME_MUSIC   sound VOLUME_GROUP
   Ambient; // Ambient MusicManager with VOLUME_AMBIENT sound VOLUME_GROUP
/******************************************************************************/
