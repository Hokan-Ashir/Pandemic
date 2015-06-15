/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'TextStyle'       to specify custom text style which can be used when drawing texts, use it      as a global/class variable for storage.
   Use 'TextStyleParams' to specify custom text style which can be used when drawing texts, use it only as a local        variable inside functions for drawing/calculation.

   Use 'TextCode' to manually draw text with different settings for different parts of the text.

/******************************************************************************

   'TextStyle' and 'TextStyleParams' are mostly the same, as 'TextStyle' is based on 'TextStyleParams'.
      The only difference is that 'TextStyle' stores the 'font' information as a reference counted pointer,
         which allows releasing the 'font' when it's no longer used.
      Therefore 'TextStyle' should be used anywhere for storage purposes.

   'TextStyleParams' does NOT store the 'font' information as a reference counted pointer, but as a regular pointer.
      Therefore it cannot be used for storage globally or in classes.
      The purpose of 'TextStyleParams' is to be used only inside function for drawing or temporary processing.

   For example it is often needed to draw the text on the screen, based on an existing 'TextStyle' however with small modification.
      Normally we would do something like that:
         void draw()
         {
            TextStyle ts=some_other_existing_text_style; ts.size=0.1; D.text(ts, ..); // draw text using modified 'some_other_existing_text_style'
         }
      The above code however requires a copy constructor for the 'TextStyle' object,
         and since it has a 'font' member as a reference counted pointer, the copy operation does incur some performance penalty.
      Since we're not interested in storing the modified text style, but only to use it for drawing,
         instead of using 'TextStyle', 'TextStyleParams' can be used, like that:
         void draw()
         {
            TextStyleParams tsp=some_other_existing_text_style; tsp.size=0.1; D.text(tsp, ..); // draw text using modified 'some_other_existing_text_style'
         }
      When using 'TextStyleParams' the copy operation is much faster, and does not incur any performance penalty.

   In short:
      Keep 'TextStyle' globally or in classes:
         class Class
         {
            TextStyle ts;
         }

      Use 'TextStyleParams' inside drawing/processing functions when modification is required:
         void draw()
         {
            TextStyleParams tsp=some_other_existing_text_style; "modify tsp"; "draw using tsp";
         }

/******************************************************************************/
enum AUTO_LINE_MODE // Automatic Lines Mode
{
   AUTO_LINE_NONE       , // doesn't       set  new lines in text (only manual new-lines '\n' are used)
   AUTO_LINE_SPACE      , // automatically sets new lines in text (new lines can be  calculated on spaces, words are not split)
   AUTO_LINE_SPACE_SPLIT, // automatically sets new lines in text (new lines can be  calculated on spaces, words can be  split if their length exceeds available width)
   AUTO_LINE_SPLIT      , // automatically sets new lines in text (new lines are not calculated on spaces, words can be  split if their length exceeds available width)
   AUTO_LINE_NUM        , // number of auto line modes
};
/******************************************************************************/
struct TextStyleParams // Text Style Params
{
   SPACING_MODE spacing    ; // spacing mode              , default=SPACING_NICE
   Bool         pixel_align; // pixel alignment           , default=true (if enabled then every character will be aligned per pixel, you can disable this if you'd like to have smooth movement on the screen at the cost of slightly more blurriness of the text)
   Byte         shadow     , // shadow              0..255, default=255
                shade      ; // shade               0..255, default=230
   Color        color      , // color                     , default=WHITE
                selection  ; // selection background color, default=(51, 153, 255, 64)
   Vec2         align      , // aligning                  , default=(0   , 0   )
                size       , // size                      , default=(0.08, 0.08)
                space      ; // space                     , default=(0.06, 1   )
   TextEdit    *edit       ; // text edit settings        , default=NULL

   Font* font()C {return _font;}   void font(Font *font) {T._font=font;} // get/set font, default=NULL (if set to NULL then current value of 'Gui.skin.font' is used)

   // get
   Flt  colWidth (                               )C {return size.x*space.x;}                   // get column width  (this is valid if "spacing==SPACING_CONST")
   Flt lineHeight(                               )C {return size.y*space.y;}                   // get line   height
   Flt textWidth (C Str  &str , Int max_length=-1)C;                                           // get width  of 'str'  one line text
   Flt textWidth (C Str8 &str , Int max_length=-1)C;                                           // get width  of 'str'  one line text
   Flt textWidth (CChar  *text, Int max_length=-1)C;                                           // get width  of 'text' one line text
   Flt textWidth (CChar8 *text, Int max_length=-1)C;                                           // get width  of 'text' one line text
   Int textPos   (CChar  *text, Flt x, Bool round)C;                                           // get index  of character at given 'x' position, returns "0 .. Length(text)"
   Int textPos   (CChar8 *text, Flt x, Bool round)C;                                           // get index  of character at given 'x' position, returns "0 .. Length(text)"
   Int textLines (CChar  *text, Flt width, AUTO_LINE_MODE auto_line, Flt *actual_width=NULL)C; // get number of lines needed to draw 'text' in space as wide as 'width', 'actual_width'=actual width of the text (this is the Max of all line widths)
   Int textLines (CChar8 *text, Flt width, AUTO_LINE_MODE auto_line, Flt *actual_width=NULL)C; // get number of lines needed to draw 'text' in space as wide as 'width', 'actual_width'=actual width of the text (this is the Max of all line widths)

   // operations
   TextStyleParams& reset          (Bool gui=false); // reset all   parameters to default settings, this copies settings from 'Gui.skin.text_style' when 'gui' is false, and 'Gui.skin.text.text_style' when 'gui' is true
   TextStyleParams& resetColors    (Bool gui=false); // reset color parameters to default settings, this copies settings from 'Gui.skin.text_style' when 'gui' is false, and 'Gui.skin.text.text_style' when 'gui' is true, parameters which are copied include: 'shadow', 'shade', 'color', 'selection'
   void             setPerPixelSize(              ); // set 1:1 pixel size "size = D.pixelToScreenSize(VecI2(font.height()))"

   explicit TextStyleParams(                     Bool gui=false) {reset(gui);}
            TextStyleParams(TextStyleParams *ts, Bool gui      ) {if(ts)T=*ts;else reset(gui);}

private:
   Font *_font;
};
STRUCT(TextStyle , TextStyleParams) // Text Style
//{
 C FontPtr& font()C {return _font;}   TextStyle& font(C FontPtr &font); // get/set Font

   // operations
   TextStyle& reset      (Bool gui=false); // reset all   parameters to default settings, this copies settings from 'Gui.skin.text_style' when 'gui' is false, and 'Gui.skin.text.text_style' when 'gui' is true
   TextStyle& resetColors(Bool gui=false); // reset color parameters to default settings, this copies settings from 'Gui.skin.text_style' when 'gui' is false, and 'Gui.skin.text.text_style' when 'gui' is true, parameters which are copied include: 'shadow', 'shade', 'color', 'selection'

   // io
   void operator=(C Str &name) ; // load from file, Exit  on fail
   Bool save     (C Str &name)C; // save to   file, false on fail
   Bool load     (C Str &name) ; // load from file, false on fail

   void save(File &f, CChar *path=NULL)C; // save to   file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail
   Bool load(File &f, CChar *path=NULL) ; // load from file, 'path'=path at which resource is located (this is needed so that the sub-resources can be accessed with relative path), false on fail, false on fail

   TextStyle();

private:
   FontPtr _font;
};
/******************************************************************************/
struct TextCode // Text with modifiers, allowing to draw text on the screen with different settings for different parts of the text
{
   // get / set
   TextCode& clear(           );                                        // clear   text value
   TextCode& set  (C Str &text);   C Str& operator()()C {return _text;} // set/get text value
   TextCode& code (C Str &code);     Str  code      ()C;                // set/get text value in code format
      // 1. code format accepts following keywords:   in following formats:
      //    col, color                                RGB, RGBA, RRGGBB, RRGGBBAA (hexadecimal format)
      //    shadow                                    X, XX                       (hexadecimal format)
      // 2. codes should be surrounded by '[' ']' signs
      // 3. removing the effect of a code should be handled by '/' sign followed by code name
      // 4. sample codes:
      //       "Text without code. [color=F00]Text with code[/color]"        - will force red color  on "Text with code"
      //       "[shadow=0]No Shadow[/shadow] [shadow=F]Full Shadow[/shadow]" - will force no  shadow on "No Shadow" and full shadow on "Full Shadow"

   // draw
   void draw(C TextStyleParams &text_style, C Rect &rect, AUTO_LINE_MODE auto_line=AUTO_LINE_NONE)C;
   void draw(                               C Rect &rect, AUTO_LINE_MODE auto_line=AUTO_LINE_NONE)C;

   TextCode();

private:
   Str  _text;
  _Memc _codes;
   NO_COPY_CONSTRUCTOR(TextCode);
};
/******************************************************************************/
DECLARE_CACHE(TextStyle, TextStyles, TextStylePtr); // 'TextStyles' cache storing 'TextStyle' objects which can be accessed by 'TextStylePtr' pointer
/******************************************************************************/
