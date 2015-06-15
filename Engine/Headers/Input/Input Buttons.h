/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
enum BS_FLAG // Button State Flag
{
   BS_ON      =0x01, // on
   BS_PUSHED  =0x02, // pushed
   BS_RELEASED=0x04, // released
   BS_DOUBLE  =0x08, // double clicked
   BS_TAPPED  =0x10, // tapped
};
inline Bool ButtonOn(Byte x) {return FlagTest(x, BS_ON      );} // if button is on
inline Bool ButtonPd(Byte x) {return FlagTest(x, BS_PUSHED  );} // if button pushed
inline Bool ButtonRs(Byte x) {return FlagTest(x, BS_RELEASED);} // if button released
inline Bool ButtonDb(Byte x) {return FlagTest(x, BS_DOUBLE  );} // if button double clicked
inline Bool ButtonTp(Byte x) {return FlagTest(x, BS_TAPPED  );} // if button tapped
/******************************************************************************/
enum KB_FUNC // Keyboard Functional Keys (used for Kb.f)
{
   KF_ESC  =0x1B, // escape
   KF_ENTER=0x0D, // enter
   KF_SPACE=0x20, // space
   KF_BACK =0x08, // backspace
   KF_TAB  =0x09, // tab

   KF_SHIFT=0x10, // left or right shift
   KF_CTRL =0x11, // left or right control
   KF_ALT  =0x12, // left or right alt
   KF_MENU =0x5D, // menu

   KF_LEFT =0x25, // left  arrow
   KF_RIGHT=0x27, // right arrow
   KF_UP   =0x26, // up    arrow
   KF_DOWN =0x28, // down  arrow

   KF_INS =0x2D, // insert
   KF_DEL =0x2E, // delete
   KF_HOME=0x24, // home
   KF_END =0x23, // end
   KF_PGUP=0x21, // page up
   KF_PGDN=0x22, // page down

   KF_F1 =0x70, // F1
   KF_F2 =0x71, // F2
   KF_F3 =0x72, // F3
   KF_F4 =0x73, // F4
   KF_F5 =0x74, // F5
   KF_F6 =0x75, // F6
   KF_F7 =0x76, // F7
   KF_F8 =0x77, // F8
   KF_F9 =0x78, // F9
   KF_F10=0x79, // F10
   KF_F11=0x7A, // F11
   KF_F12=0x7B, // F12

   KF_NPDIV=0x6F, // numpad divide   /
   KF_NPMUL=0x6A, // numpad multiply *
   KF_NPSUB=0x6D, // numpad subtract -
   KF_NPADD=0x6B, // numpad add      +

   KF_NP0=0x60, // numpad 0
   KF_NP1=0x61, // numpad 1
   KF_NP2=0x62, // numpad 2
   KF_NP3=0x63, // numpad 3
   KF_NP4=0x64, // numpad 4
   KF_NP5=0x65, // numpad 5
   KF_NP6=0x66, // numpad 6
   KF_NP7=0x67, // numpad 7
   KF_NP8=0x68, // numpad 8
   KF_NP9=0x69, // numpad 9

   KF_NAV_BACK   =0xA6, // navigate backward
   KF_NAV_FORWARD=0xA7, // navigate  forward

   KF_ZOOM_IN =0xFB, // zoom in
   KF_ZOOM_OUT=0xFC, // zoom out

   KF_SUB       =0xBD, // -_
   KF_EQUAL     =0xBB, // =+
   KF_LBRACKET  =0xDB, // [{
   KF_RBRACKET  =0xDD, // ]}
   KF_SEMICOLON =0xBA, // ;:
   KF_APOSTROPHE=0xDE, // '"
   KF_BACKSLASH =0xDC, // \|
   KF_COMMA     =0xBC, // ,<
   KF_DOT       =0xBE, // .>
   KF_SLASH     =0xBF, // /?
   KF_TILDE     =0xC0, // `~

   KF_0='0',
   KF_1='1',
   KF_2='2',
   KF_3='3',
   KF_4='4',
   KF_5='5',
   KF_6='6',
   KF_7='7',
   KF_8='8',
   KF_9='9',

   KF_A='A',
   KF_B='B',
   KF_C='C',
   KF_D='D',
   KF_E='E',
   KF_F='F',
   KF_G='G',
   KF_H='H',
   KF_I='I',
   KF_J='J',
   KF_K='K',
   KF_L='L',
   KF_M='M',
   KF_N='N',
   KF_O='O',
   KF_P='P',
   KF_Q='Q',
   KF_R='R',
   KF_S='S',
   KF_T='T',
   KF_U='U',
   KF_V='V',
   KF_W='W',
   KF_X='X',
   KF_Y='Y',
   KF_Z='Z',

   // shorter names
   KF_LBR   =KF_LBRACKET  ,
   KF_RBR   =KF_RBRACKET  ,
   KF_SEMI  =KF_SEMICOLON ,
   KF_APO   =KF_APOSTROPHE,
   KF_BSLASH=KF_BACKSLASH ,
};
/******************************************************************************/
enum KB_BUTTON // Keyboard Buttons (used for Kb.button Kb.b*)
{
   KB_0=0x0B, // 0
   KB_1=0x02, // 1
   KB_2=0x03, // 2
   KB_3=0x04, // 3
   KB_4=0x05, // 4
   KB_5=0x06, // 5
   KB_6=0x07, // 6
   KB_7=0x08, // 7
   KB_8=0x09, // 8
   KB_9=0x0A, // 9

   KB_A=0x1E, // A
   KB_B=0x30, // B
   KB_C=0x2E, // C
   KB_D=0x20, // D
   KB_E=0x12, // E
   KB_F=0x21, // F
   KB_G=0x22, // G
   KB_H=0x23, // H
   KB_I=0x17, // I
   KB_J=0x24, // J
   KB_K=0x25, // K
   KB_L=0x26, // L
   KB_M=0x32, // M
   KB_N=0x31, // N
   KB_O=0x18, // O
   KB_P=0x19, // P
   KB_Q=0x10, // Q
   KB_R=0x13, // R
   KB_S=0x1F, // S
   KB_T=0x14, // T
   KB_U=0x16, // U
   KB_V=0x2F, // V
   KB_W=0x11, // W
   KB_X=0x2D, // X
   KB_Y=0x15, // Y
   KB_Z=0x2C, // Z

   KB_F1 =0x3B, // F1
   KB_F2 =0x3C, // F2
   KB_F3 =0x3D, // F3
   KB_F4 =0x3E, // F4
   KB_F5 =0x3F, // F5
   KB_F6 =0x40, // F6
   KB_F7 =0x41, // F7
   KB_F8 =0x42, // F8
   KB_F9 =0x43, // F9
   KB_F10=0x44, // F10
   KB_F11=0x57, // F11
   KB_F12=0x58, // F12

   KB_ESC  =0x01, // escape
   KB_ENTER=0x1C, // enter
   KB_SPACE=0x39, // space
   KB_BACK =0x0E, // backspace
   KB_TAB  =0x0F, // tab

   KB_LCTRL =0x1D, // left  control
   KB_RCTRL =0x9D, // right control
   KB_LSHIFT=0x2A, // left  shift
   KB_RSHIFT=0x36, // right shift
   KB_LALT  =0x38, // left  alt
   KB_RALT  =0xB8, // right alt
   KB_LWIN  =0xDB, // left  win
   KB_RWIN  =0xDC, // right win
   KB_MENU  =0xDD, // menu key

   KB_LEFT =0xCB, // left  arrow
   KB_RIGHT=0xCD, // right arrow
   KB_UP   =0xC8, // up    arrow
   KB_DOWN =0xD0, // down  arrow

   KB_INS =0xD2, // insert
   KB_DEL =0xD3, // delete
   KB_HOME=0xC7, // home
   KB_END =0xCF, // end
   KB_PGUP=0xC9, // page up
   KB_PGDN=0xD1, // page down

   KB_SUB       =0x0C, // subtract      -
   KB_EQUAL     =0x0D, // equals        =
   KB_LBRACKET  =0x1A, // left  bracket [
   KB_RBRACKET  =0x1B, // right bracket ]
   KB_SEMICOLON =0x27, // semicolon     ;
   KB_APOSTROPHE=0x28, // apostrophe    '
   KB_COMMA     =0x33, // comma         ,
   KB_DOT       =0x34, // dot           .
   KB_SLASH     =0x35, // slash         /
   KB_BACKSLASH =0x2B, // backslash    '\'
   KB_TILDE     =0x29, // tilde         `
   KB_SCREEN    =0xB7, // print  screen
   KB_PAUSE     =0xC5, // pause  break
   KB_CAPS      =0x3A, // caps   lock
   KB_NUM       =0x45, // num    lock
   KB_SCROLL    =0x46, // scroll lock

   KB_NPDIV  =0xB5, // numpad divide   /
   KB_NPMUL  =0x37, // numpad multiply *
   KB_NPSUB  =0x4A, // numpad subtract -
   KB_NPADD  =0x4E, // numpad add      +
   KB_NPENTER=0x9C, // numpad enter
   KB_NPDEL  =0x53, // numpad delete
   KB_NP0    =0x52, // numpad 0
   KB_NP1    =0x4F, // numpad 1
   KB_NP2    =0x50, // numpad 2
   KB_NP3    =0x51, // numpad 3
   KB_NP4    =0x4B, // numpad 4
   KB_NP5    =0x4C, // numpad 5
   KB_NP6    =0x4D, // numpad 6
   KB_NP7    =0x47, // numpad 7
   KB_NP8    =0x48, // numpad 8
   KB_NP9    =0x49, // numpad 9

   KB_VOL_DOWN   =0xAE, // volume -
   KB_VOL_UP     =0xB0, // volume +
   KB_VOL_MUTE   =0xA0, // mute
   KB_NAV_BACK   =0xEA, // navigate backward
   KB_NAV_FORWARD=0xE9, // navigate  forward
   KB_MEDIA_PREV =0x90, // media previous
   KB_MEDIA_NEXT =0x99, // media next
   KB_MEDIA_PLAY =0xA2, // media play/pause
   KB_MEDIA_STOP =0xA4, // media stop
   KB_FIND       =0xE5, // find

   KB_OEM_102=0x56, // <> or \|

   // shorter names
   KB_LBR   =KB_LBRACKET  ,
   KB_RBR   =KB_RBRACKET  ,
   KB_SEMI  =KB_SEMICOLON ,
   KB_APO   =KB_APOSTROPHE,
   KB_BSLASH=KB_BACKSLASH ,
};
/******************************************************************************/
