/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Accelerometer' to access Accelerometer input.
   Use 'Gyroscope'     to access Gyroscope     input.
   Use 'Magnetometer'  to access Magnetometer  input.

   Use 'Location*' functions to access device world location.

   Use 'InputButton' and 'Input' as general inputs.

   Use 'InputCombo' to check for keyboard button combinations.

/******************************************************************************/
#define INPUT_COMBO_NUM 8 // number of remembered input buttons

#define        LongPressTime 0.55f // amount of time to consider any                   button press a long   press
#define      DoubleClickTime 0.25f // amount of time to consider Keyboard/Mouse/JoyPad button press a double click
#define TouchDoubleClickTime 0.33f // amount of time to consider Touch                        press a double click
/******************************************************************************/
// ACCELEROMETER, GYROSCOPE, LOCATION
/******************************************************************************/
enum LOCATION_AUTHORIZATION_STATUS
{
   LAS_UNKNOWN   , // The user has not yet made a choice regarding whether this app can use location services
   LAS_RESTRICTED, // The app  cannot make use of Location because the device has this restricted (for example due to Parental Controls)
   LAS_DENIED    , // The user explicitly denied the use of location services for this app or location services are currently disabled in Settings.
   LAS_FOREGROUND, // The app  is authorized to make use of Location while running in foreground
   LAS_BACKGROUND, // The app  is authorized to make use of Location while running in foreground and background
};

C Vec& Accelerometer(); // get current value of the accelerometer         , if not supported then (0, 0, 0) is returned
C Vec& Gyroscope    (); // get current value of the gyroscope (in radians), if not supported then (0, 0, 0) is returned
C Vec& Magnetometer (); // get current value of the magnetometer          , if not supported then (0, 0, 0) is returned

C Matrix3&          Orientation(); // get current value of the           orientation, if not supported then identity is returned
C Matrix3& PredictedOrientation(); // get current value of the predicted orientation, if not supported then identity is returned

  Dbl       LocationLatitude (Bool gps=true); // get last known location latitude  (in degrees               ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Dbl       LocationLongitude(Bool gps=true); // get last known location longitude (in degrees               ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Flt       LocationAltitude (Bool gps=true); // get last known location altitude  (in meters above sea level,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Flt       LocationAccuracy (Bool gps=true); // get last known location precision (in meters                ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
  Flt       LocationSpeed    (Bool gps=true); // get last known location speed     (in meters per second     ,    0 if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)
C DateTime& LocationTimeUTC  (Bool gps=true); // get last known location time      (in UTC time zone         , zero if unknown), 'gps'=if obtain location using GPS (more precision) or Network (cell towers and internet access points)

void LocationRefresh(Flt interval, Bool gps=true, Bool background=false); // after calling this function the device will start refreshing its location continuously each 'interval' seconds, 'gps'=if refresh the GPS (more precision) or Network (cell towers and internet access points), 'interval'=seconds between sequential updates (0..Inf) - small interval results in more frequent updates while big interval conserves the battery better. 'background'=if allow location updates even when the application is in background mode. This function can be called just once and the location will start refreshing itself as long as the app is active or until 'LocationDisable' is called. This and all other Location functions operate on GPS and Network separately, which means that you can start and stop refreshing both GPS and the Network independently.
void LocationDisable(              Bool gps=true                       ); // after calling this function the device will stop  refreshing its location                                     , 'gps'=if disable the GPS                  or Network

LOCATION_AUTHORIZATION_STATUS LocationAuthorizationStatus(); // get the current Location Authorization Status (this is used only on Apple platforms)

void MagnetometerRefresh(Flt interval=1.0f/30); // after calling this function the device will start refreshing direction of the magnetic field continuously each 'interval' seconds
void MagnetometerDisable(                    ); // after calling this function the device will stop  refreshing direction of the magnetic field

Bool OculusRiftDetected(                ); // if  Oculus Rift device is currently connected to the computer
Flt  OculusRiftFovY    (Bool adjust=true); // get Oculus Rift device vertical Field of View (in radians), 'adjust'=if adjust by 'D.stereoScale'
/******************************************************************************/
// GENERAL INPUT
/******************************************************************************/
enum INPUT_TYPE // Input Device Type
{
   INPUT_NONE    , // None
   INPUT_KEYBOARD, // Keyboard
   INPUT_MOUSE   , // Mouse
   INPUT_JOYPAD  , // Joypad
};
/******************************************************************************/
struct InputButton // universal Input Button, may be a button from Keyboard, Mouse, Joypad
{
   INPUT_TYPE type  ; // input  type
   Byte       button, // button index (KB_BUTTON for keyboard or index for Mouse/Joypad)
              device; // device index (for example Joypad device index, unused for Keyboard and Mouse)

   Bool operator==(C InputButton &b)C; // if input buttons are equal
   Bool operator!=(C InputButton &b)C; // if input buttons are different

   Bool on()C; // if button on
   Bool pd()C; // if button pushed
   Bool rs()C; // if button released
   Bool db()C; // if button double clicked

   Str name()C; // get button name, can be one of the following : Kb.buttonName(button), Ms.buttonName(button), Joypads[device].buttonName(button), NULL

   InputButton(INPUT_TYPE type=INPUT_NONE, Byte button=0, Byte device=0) {T.type=type; T.button=button; T.device=device;}
};
/******************************************************************************/
struct Input // Action Input (for example "walk_forward"), may be defined by maximum 3 custom buttons
{
   UInt        group; // custom input group (for example Movement, Interaction, Combat, ...)
   Str         name ; // action name
   InputButton b[3] ; // 3 custom buttons

   Bool on()C; // if action on             (checks if any of the 3 buttons is on            )
   Bool pd()C; // if action pushed         (checks if any of the 3 buttons is pushed        )
   Bool rs()C; // if action released       (checks if any of the 3 buttons is released      )
   Bool db()C; // if action double clicked (checks if any of the 3 buttons is double clicked)

   void set(Str name=S, UInt group=0                                                                 ); // set action properties
   void set(Str name  , UInt group, C InputButton &b0, C InputButton *b1=NULL, C InputButton *b2=NULL); // set action properties

   Bool operator()(C InputButton &b)C; // if 'b' button enables action, this checks if any of the 3 buttons is equal to 'b'

   Input() {group=0;}
};
/******************************************************************************/
// INPUT COMBINATION
/******************************************************************************/
struct InputComboClass // Input Combination, used for detecting special moves/attacks
{
   void clear(); // clear stored combination

   Bool operator()(C Input &i0, C Input &i1                                       )C; // if action 'i0' was pressed, followed by 'i1'
   Bool operator()(C Input &i0, C Input &i1, C Input &i2                          )C; // if action 'i0' was pressed, followed by 'i1', 'i2'
   Bool operator()(C Input &i0, C Input &i1, C Input &i2, C Input &i3             )C; // if action 'i0' was pressed, followed by 'i1', 'i2', 'i3'
   Bool operator()(C Input &i0, C Input &i1, C Input &i2, C Input &i3, C Input &i4)C; // if action 'i0' was pressed, followed by 'i1', 'i2', 'i3', 'i4'

   InputComboClass();

private:
   Byte        pos, length;
   Flt         t[INPUT_COMBO_NUM], dt;
   InputButton b[INPUT_COMBO_NUM];
}extern
   InputCombo;
/******************************************************************************/
struct TextEdit // Text Edit Settings
{
   Bool overwrite, // if cursor  is in overwriting mode
        password ; // if editing is in password mode from which you can't copy the text
   Int  cur      , // cursor    position
        sel      ; // selection position, -1=none

   void reset() {overwrite=false; password=false; cur=0; sel=-1;}
   TextEdit() {reset();}
};
Bool EditText(Str &str, TextEdit &edit); // edit 'str' text according to keyboard input, returns true if text has been changed
/******************************************************************************/
