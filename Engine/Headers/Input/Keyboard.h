/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Kb' to access Keyboard input.

   Use 'KbSc' to describe keyboard shortcuts.

/******************************************************************************/
enum KB_LAYOUT
{
   KB_QWERTY,
   KB_QWERTZ,
   KB_AZERTY,
};
/******************************************************************************/
struct Keyboard // Keyboard Input
{
   Bool b (KB_BUTTON x)C {return InRange(x, _button) ? ButtonOn(_button[x]) : false;} // if button 'x' is on
   Bool bp(KB_BUTTON x)C {return InRange(x, _button) ? ButtonPd(_button[x]) : false;} // if button 'x' pushed   in this frame
   Bool br(KB_BUTTON x)C {return InRange(x, _button) ? ButtonRs(_button[x]) : false;} // if button 'x' released in this frame
   Bool bd(KB_BUTTON x)C {return InRange(x, _button) ? ButtonDb(_button[x]) : false;} // if button 'x' double clicked

   Bool ctrl ()C {return _ctrl ;} // if any Ctrl  is on (this is equal to "b(KB_LCTRL ) || b(KB_RCTRL )")
   Bool shift()C {return _shift;} // if any Shift is on (this is equal to "b(KB_LSHIFT) || b(KB_RSHIFT)")
   Bool alt  ()C {return _alt  ;} // if any Alt   is on (this is equal to "b(KB_LALT  ) || b(KB_RALT  )")
   Bool win  ()C {return _win  ;} // if any Win   is on (this is equal to "b(KB_LWIN  ) || b(KB_RWIN  )")

   KB_FUNC f(         )C {return    _func;} // get    functional key pressed in this frame
   Bool    f(KB_FUNC f)C {return f==_func;} // if 'f' functional key pressed in this frame

   Char c(       )C {return            _chr ;} // get    character pressed in this frame
   Bool c(Char  c)C {return EqualCS(c, _chr);} // if 'c' character pressed in this frame
   Bool c(Char8 c)C {return EqualCS(c, _chr);} // if 'c' character pressed in this frame

   Char    nextBufferedChar(); // get next buffered character      pressed in this frame, this can be optionally called if you want to process all characters      pressed in this frame, if you will not call this, any remaining characters      will be processed in the following frames, this function takes the next character      from the buffer, sets it to the '_chr'  member so it can be accessed using 'c' methods, and also returns the '_chr'  character     , 0 on fail (if the buffer is empty)
   KB_FUNC nextBufferedFunc(); // get next buffered functional key pressed in this frame, this can be optionally called if you want to process all functional keys pressed in this frame, if you will not call this, any remaining functional keys will be processed in the following frames, this function takes the next functional key from the buffer, sets it to the '_func' member so it can be accessed using 'f' methods, and also returns the '_func' functional key, 0 on fail (if the buffer is empty)

   Char buttonChar(KB_BUTTON b)C; // get button    character, buttonChar(KB_SPACE) -> ' '
   Str  buttonName(KB_BUTTON b)C; // get button         name, buttonName(KB_SPACE) -> "Space"
   Str    funcName(KB_FUNC   f)C; // get functional key name,   funcName(KF_SPACE) -> "Space"

   // get
   Bool hwAvailable (          ); // if hardware keyboard is available
   Bool softCoverage(Rect &rect); // get soft keyboard (on-screen) coverage, false if no screen keyboard is currently displayed

   // operations
   void eat(                ); // eat any button  input from this frame so it will not be processed by the remaining codes in frame
   void eat(KB_BUTTON button); // eat    'button' input from this frame so it will not be processed by the remaining codes in frame

   void exclusive     (Bool      on     );                                                           // manually adjust keyboard exclusive mode (APP_KB_EXCLUSIVE)
   void layout        (KB_LAYOUT layout );   KB_LAYOUT layout        ()C {return _layout          ;} // set/get keyboard layout, default=autodetect
   void swappedCtrlCmd(Bool      swapped);   Bool      swappedCtrlCmd()C {return _swapped_ctrl_cmd;} // set/get if Ctrl is swapped with Cmd key under Mac OS, enable this method if you have swapped Ctrl with Cmd key under System Preferences but you wish to get their original mapping under the engine, this method is used only under Mac, default=false

   void requestTextInput(); // call this each frame if you wish to manually process the keyboard input in text format, this enables IMM on Windows and displays screen keyboard on Mobile platforms, this is automatically enabled if Gui keyboard focus is on 'TextLine' object

   // IMM (Windows Input Method Manager) control
   Bool       immNative   ()C;   void immNative(Bool native); // get/set if native typing mode is currently enabled
   Int        immCursor   ()C {return _imm_cursor   ;}        // get     IMM cursor position
 C VecI2    & immSelection()C {return _imm_selection;}        // get     IMM clause selection range, where x=min index, y=max index
 C Str      & immBuffer   ()C {return _imm_buffer   ;}        // get     IMM text buffer
 C Memc<Str>& immCandidate()C {return _imm_candidate;}        // get     IMM candidate list

#ifndef APPLE
   Bool    ctrlCmd    ()C {return _ctrl ;} // if any Ctrl is on on platforms other than Apple, and if any Command is on on Apple platforms
   Bool    winCtrl    ()C {return _win  ;} // if any Win  is on on platforms other than Apple, and if any Control is on on Apple platforms
   CChar8* ctrlCmdName()C {return "Ctrl";}
   CChar8* winCtrlName()C {return "Win" ;}
#else
   Bool    ctrlCmd    ()C {return _win  ;} // if any Ctrl is on on platforms other than Apple, and if any Command is on on Apple platforms
   Bool    winCtrl    ()C {return _ctrl ;} // if any Win  is on on platforms other than Apple, and if any Control is on on Apple platforms
   CChar8* ctrlCmdName()C {return "Cmd" ;}
   CChar8* winCtrlName()C {return "Ctrl";}
#endif

private:
   Bool       _ctrl, _shift, _shift2, _alt, _win, _hidden, _swapped_ctrl_cmd, _text_input, _visible, _refresh_visible, _imm, _imm_candidate_hidden, _disable_shift, _exclusive;
   Char       _chr , _c_buffer[256], _button_char[256];
   Byte       _lang, _f_buffer[256], _button[256], _c_buffer_pos, _c_buffer_len, _f_buffer_pos, _f_buffer_len;
   Int        _cur, _last, _imm_cursor;
   Flt        _curh_t, _curh_tn, _last_t;
   RectI      _recti;
   KB_FUNC    _func;
   KB_LAYOUT  _layout;
   VecI2      _imm_selection;
   Str        _imm_buffer;
   Memc<Str>  _imm_candidate, _imm_candidate_temp;
   Memc<Byte> _force_keys;
   CChar     *_button_name[256], *_func_name[256];
   Ptr        _did, _imc;
	Keyboard();
   NO_COPY_CONSTRUCTOR(Keyboard);
}extern
   Kb;
/******************************************************************************/
enum KBSC_FLAG // Keyboard Shortcut Flags
{
   KBSC_CTRL =0x01, // Control required
   KBSC_SHIFT=0x02, // Shift   required
   KBSC_ALT  =0x04, // Alt     required
   KBSC_WIN  =0x08, // Win     required

   KBSC_CTRL_CMD=0x10, // Control required on platforms other than Apple, and Command required on Apple platforms
   KBSC_WIN_CTRL=0x20, // Win     required on platforms other than Apple, and Control required on Apple platforms
};
enum KBSC_MODE // Keyboard Shortcut Mode
{
   KBSC_CHAR  , // treat 'index' as Char (with this flag enabled : KBSC_SHIFT is skipped, also if KBSC_ALT is selected then only left alt is checked)
   KBSC_FUNC  , // treat 'index' as KB_FUNC
   KBSC_BUTTON, // treat 'index' as KB_BUTTON
};
struct KbSc // Keyboard Shortcut
{
   Byte      flag ; // KBSC_FLAG
   KBSC_MODE mode ; // mode
   UShort    index; // Char/KB_FUNC/KB_BUTTON depending on 'mode'

   Bool on    ()C; // if on
   Bool pd    ()C; // if pushed   in this frame
   Bool rs    ()C; // if released in this frame, this function returns a valid value only for KBSC_BUTTON mode
   Bool db    ()C; // if double clicked        , this function returns a valid value only for KBSC_BUTTON mode
   Str  asText()C; // get text describing the shortcut

   Bool is()C {return index!=0;} // if shortcut is valid

   void eat()C; // eat this shortcut keys input from this frame so it will not be processed by the remaining codes in frame

   KbSc(                             ) {T.index=0           ; T.flag=0   ; T.mode=KBSC_CHAR  ;}
   KbSc(Char8     c     , Byte flag=0) {T.index=Char8To16(c); T.flag=flag; T.mode=KBSC_CHAR  ;}
   KbSc(Char      c     , Byte flag=0) {T.index=c           ; T.flag=flag; T.mode=KBSC_CHAR  ;}
   KbSc(KB_FUNC   func  , Byte flag=0) {T.index=func        ; T.flag=flag; T.mode=KBSC_FUNC  ;}
   KbSc(KB_BUTTON button, Byte flag=0) {T.index=button      ; T.flag=flag; T.mode=KBSC_BUTTON;}
};
/******************************************************************************/
