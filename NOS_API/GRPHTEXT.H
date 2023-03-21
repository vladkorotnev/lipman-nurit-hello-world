/****************************************************************************
 * FILE NAME:   GrphText.H                                                  *
 * MODULE NAME: GrphText                                                    *
 * PROGRAMMER:  Ephraim Ben-Ishai                                           *
 * DESCRIPTION: public defines, types, variables, function prototypes       *
 *              API functions declarations                                  *
 ****************************************************************************/

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
#ifndef __GrphText_H
  #define __GrphText_H


/*
1. Formats the display into lines.
   The display is defined by its columns and rows. The user can then divide
   the rows of pixels into lines. The lines size determins the font type that
   is permitted to be written on that line. For example if line one is defined
   as 14 pixels then all three font types can be written to that line. If line
   two is defined as 9 pixels then, only the 7X5 font can be written.

   If the user only wants to define two line sizes line one header and the
   rest all the same size then, only the first two lines need to be given
   to the _FORMAT function with a contiuatin code the function will then
   create the remainder of the lines based on the line before the ETC code.

2. Creates popups based on lines.
   PopUps are created base on a row,col point the width (columns)of the
   window, and the number of lines in the window. Once a window is formed
   then all the functions in this module assume the new WORLD. For example
   if _CLS is used then only the window will be cleared. When writting
   to Line one this will correspond to line one in the window and
   the offset based from the begining of the window.

6. Set cursor attruibutes and position.
   The cursor is definined to be blinking or not, visible or not, per font
   type and thickness 1/2/3 lines. These parameters are set at any time by
   the user.

7. Activates the cursor on the display.
   An interupt driven routine _CURSORCONNECT is called every 1/2 sec. This
   routine uses the cursor attributes listed above and preformes them.

8. The cursor can be moved to any location with-in the current world by
   defining the line and offset. The user can also determine the location
   of the cursor at any given time.*/
          /*==========================================*
           *           I N C L U D E S                *
           *==========================================*/

#include grphtext_def

#if (defined(COLOR_DISPLAY) || defined(_ARM))
   #include bmp_def
#endif

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/
#define PARAM_ERROR  -1
#define END_OF_LINES  0xff /* signifies end of line format array */
#define ETC           0xFE /* signifies to make all lines the same as the line
			      preceding the ETC
			    */
#define POPUP_T_UNDERFLOW  0
#define POPUP_T_OVERFLOW   1
#define POPUP_T_OK         3


#if (defined(COLOR_DISPLAY) || defined(_ARM))

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

#define NULL_RECTANGLE(R) ((R).x1>=(R).x2 && (R).y1>=(R).y2)

/*Horizontal format, the same as in DISPLAY.H: */
#define SET_LEFT            0
#define SET_RIGHT           0x10
#define SET_CENTER          0x20
/*Vertical format:                             */
#define SET_TOP             0
#define SET_BOTTOM          0x01
#define SET_VCENTER         0x02
#define SET_SPREAD          0x03



           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: DBlock_GetFontHandle
 * DESCRIPTION  : Return font block handle. 
 * PARAMETERS   : char * FontName. - The FontName is 6 byte NULL terminated string.                   
 * RETURN:      : if   success   return  BlockHandle (>0).
 *                else           rerutn  DBLOCK_FAIL (0).
 * Note         : The FontBlockHandle is the serial number of the font block at 
 *                the memory(flash) ,depends on the blocks order.
 *                The FontBlockHandle might be changed after each block download
 *                or Reset.
 *                Called by application.
 * ------------------------------------------------------------------------ */
#ifdef NOS_WITH_DYNAMIC_FONT
char GrphText_GetFontHandle(char * FontName);
#endif 
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_RelativeToAbsolute
 * DESCRIPTION:   converts the coordinates given reletively to the current
 *                window to the absolute coordinates in the display.
 *                Truncates the rectangle if it's outside of the window
 * RETURN:        absolute coordinates or NULL_RECTANGLE if outside of the window
 * NOTES:         the absolute coordinates are those used by GRPHDISP module
 * ------------------------------------------------------------------------- */
Rectangle GrphText_RelativeToAbsolute(Rectangle rel);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_ShowBMP
 *
 * DESCRIPTION:   shows an image in BMP format.
 *
 * PARAMETERS:    pBMPFile  - Pointer to a .bmp File. (see BMP.DEF)
 *                pR        - Area on screen to display image (Relative area!!!).
 *                DisplayIt - TRUE  - write to the physical sceen.
 *                            FALSE - write to Virtual Display only.
 *
 * RETURN:        GRAPHICS_OK             - File was processed o.k.
 *                GRAPHICS_INVALID_FORMAT - The file contains an unsupported format
 *                GRAPHICS_ARG_ERR        - Function argument error
 *                GRAPHICS_FATAL_ERR      - Fatal error occured
 *             
 * NOTES:         1. See BMP.DEF
 *                2. 3 speed levels:
 *                     a. Image Color-Depth != NOS Color-Depth => copy pixel-pixel.
 *                     b. Same Color-Depth, no byte-alignment => byte-masking.
 *                     c. Byte-alignment (pR->x1*COLOR_DEPTH)&7) == 0 => no masking!
 *                   (copying lint isn't possible, because BMP struct is 2-byte aligned!!!)
 *
 * ------------------------------------------------------------------------ */
sint GrphText_ShowBMP ( BMPHeader_T const *pBMPFile,
                        Rectangle   const *pR,
                        boolean            DisplayIt );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_ShowRawBitmap
 *
 * DESCRIPTION:   shows a Raw Bitmap image.
 *
 * PARAMETERS:    pRawBitmap - Pointer to a NOS Raw-Bitmap structure (see GrphDisp.h)
 *                pR         - Area on screen to display image (Relative area!!!).
 *                DisplayIt  - TRUE  - write to the physical sceen.
 *                            FALSE - write to Virtual Display only.
 *
 * RETURN:        GRAPHICS_OK             - Bitmap was processed o.k.
 *                GRAPHICS_INVALID_FORMAT - The file contains an unsupported format
 *                GRAPHICS_ARG_ERR        - Function argument error
 *                GRAPHICS_FATAL_ERR      - Fatal error occured
 *             
 * NOTES:         1. See GrphDisp.h
 *                2. 3 speed levels:
 *                     a. Image Color-Depth != NOS Color-Depth => copy pixel-pixel.
 *                     b. Same Color-Depth, no byte-alignment => byte-masking.
 *                     c. Byte-alignment (pR->x1*COLOR_DEPTH)&7) == 0 => no masking!
 *
 * ------------------------------------------------------------------------ */
sint GrphText_ShowRawBitmap ( RawBitmap_T const *pRawBitmap,
                              Rectangle   const *pR,
                              boolean            DisplayIt );


/* --------------------------------------------------------------------------
* FUNCTION NAME: GrphText_SetCursorPositionInText
* DESCRIPTION  : Set cursor position at a specific character of a given ASCII string.
* PARAMETRS    : Line      - Line of new cursor position.
*                TxtOffset - Offset in pixels of text.
*                Str       - ASCII string to set the cursur in.
*                TxtLen    - Length of Str.
*                FontType  - Font type.
*                CursorPosition   - CursorPosition --Position of cursor in text(chars units).    
* RETURN       : None.
* ------------------------------------------------------------------------- */
void GrphText_SetCursorPositionInText(
                                      byte Line, /* line of new cursor position */
                                      sint TxtOffset, /* offset in pixels of Text */
                                      char * Str,     /*ASCII data in which set cursor */
                                      byte TxtLen,     /*length of str */
                                      byte FontType,
                                      byte CursorPosition); /* location of a cursor in chars of Text */


#endif /*#ifdef COLOR_DISPLAY*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_ClrToEndOfLine
 *
 * DESCRIPTION:   Clears from the current cursor position to the end of line
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_ClrToEndOfLine(
boolean DisplayIt /* display on the physical screen or just the virtual screen */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_ClrLine
 *
 * DESCRIPTION:   Clears a specified line
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_ClrLine(
byte Line, /* Line number 1.... */
boolean DisplayIt /* show on physical screen or just virtual */
);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_RevVideo
 * DESCRIPTION:   Inverts text in specified line
 * RETURN:        none.
 * NOTES:         the height of inverted block=font's height, not line's height
 * ------------------------------------------------------------------------- */
void GrphText_RevVideo(byte Line, /* Line number 1.... */
                       byte len,  /* number of char  */
                       byte FontType,
                       boolean DisplayIt); /* show on physical screen or just virtual */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_GetLineCol
 *
 * DESCRIPTION:   passes the number of row lines and columns to the caller
 *
 *
 * RETURN:        none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_GetLineCol(
byte *NoOfLines, /* number of lines in rows being used */
byte *NoOfCol    /* number of columns across the display being used */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_SetCursorPosition
 *
 * DESCRIPTION:   1- Positions a cursor at a given line,column
 *
 *
 * RETURN:        none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_SetCursorPosition(
byte Line,   /* line of new cursor position */
byte Offset, /* offset in characters of new cursor position */
byte FontType
);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_GetCursorPosition
 *
 * DESCRIPTION:   1- Get the positions a cursor at a line,column
 *
 *
 * RETURN:        none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_GetCursorPosition(
byte *LastLine, /* current position before any action is taken */
byte *LastOffset /* current offset before any action is taken */
);

/* --------------------------------------------------------------------------
*
* FUNCTION NAME: GrphText_CursorAttribute
*
* DESCRIPTION:   1- Positions a cursor at line column
*
* RETURN:        none.
*
* NOTES:         Attributes:
*
*                     1.CursorOn:            TRUE
*                                            FALSE
*
*                     2.shape:               LINE_1
*                                            LINE_2
*                                            LINE_3
*                                            FILL
*                                            VERTICAL_CURSOR
*
*                     3.size:     FontTypes   FONT_7X5:   7 lines by 5 pixels
*                                             FONT_10X7:  10 lines by 7 pixels
*                                             FONT_14X10: 14 lines by 10 pixels
*
* ------------------------------------------------------------------------- */
void GrphText_CursorAttribute(
boolean CursorOn,  /* is cursor visible or not */
byte shape,        /* thickness of cursor 1/2/3 lines */
byte size          /* to what font type does this cursor belong too */
);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_ShowImage
 * DESCRIPTION:   outputs an image to the current window
                  width and height are 'Image'parameters,

 * RETURN:        none.
 * NOTES:         none.
 * ------------------------------------------------------------------------- */
void GrphText_ShowImage(byte *Image,
                        sint  width, /*width of 'Image' in pixels*/
                        sint  height,/*height of 'Image' in pixels*/
                        sint  top,   /*upper pixel in current window*/
                        sint  left,  /*left-most pixel in current window*/
                        boolean DisplayIt); /* Virtual only or send to hw also */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_DrawDisp
 *
 * DESCRIPTION:   Calls the primitive function GrphDisp_DrawDisp in
 *                order to send the buffer to the screen.
 *
 *
 * RETURN:        none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_DrawDisp(void);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_LineToPixel
 *
 * DESCRIPTION:   Converts a given line to its pixel equivalent
 *
 * RETURN:        pixel equivalent.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------- */
byte GrphText_LineToPixel(
byte Line /* Line number 1.... */
);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_FontId
 * DESCRIPTION:   locates Font descriptor struct by given FontId
 * RETURN:        pointer to const struct or NULL if font not found
 * NOTES:         FontId is unic key defined in GRPHDISP.DEF:
                  FONT_8X8           6 not supported
                  FONT_16X16_WORDS   5 not supported
                  FONT_16X8_HIGH     4 not supported
                  FONT_16X8_LOW      3 not supported
                  FONT_14X10         2 supported
                  FONT_10X7          1 supported
                  FONT_7X5           0 supported
 * ------------------------------------------------------------------------ */
TFont *GrphText_FontPrm(byte FontId);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_ShowLogo
 * DESCRIPTION:   show the graphic logo in the current window
 * RETURN:        none.
 * NOTES:         none.
 * ------------------------------------------------------------------------- */
void GrphText_ShowLogo(char *LogoName);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_SetColors
 * DESCRIPTION:   set background and foreground colors for current window
 * RETURN:        none
 * NOTES:
 * ------------------------------------------------------------------------ */
void GrphText_SetColors(long Bg, long Fg);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_GetColors
 * DESCRIPTION:   read current background and foreground colors
 * RETURN:        none
 * NOTES:         none
 * ------------------------------------------------------------------------ */
void GrphText_GetColors(long *Bg, long *Fg);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_FillWithText
 * DESCRIPTION:  writes the text into defined coordinates, parsing the text
 *               between lines.
 *               The formatting of the window doesn't used, i.e. this
 *               function temporary reformats the 'coord' part of the window
 * RETURN:       address of the truncated substring which is outside of the
 *               output rectangle, or *(ret val)==0, if the entire text was
 *               outputed into rectangle.
 * NOTES:        coord is relative to the current window
 * ------------------------------------------------------------------------- */
char *GrphText_FillWithText(Rectangle  coord,
                            Text      *text,
                            boolean    DisplayIt /*=TRUE send to HW also */);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_FormatWrite
 * DESCRIPTION:   formatted writing to the display
 * RETURN:        none.
 * NOTES:         FontTypes  FONT_7X5:   7 lines by 5 pixels
 *                          FONT_10X7:  10 lines by 7 pixels
 *                         FONT_14X10:  14 lines by 10 pixels
 *                Restrictions:  (1) text will not go past end of line
 *                               (2) text will not go past size
 *                               (3) text will not go past NULL (string)
 * ------------------------------------------------------------------------- */
void GrphText_FormatWrite(byte    Line,     /*line number 1,2,3.... */
                          format  Format,   /*see DISPLAY.H: LEFT,RIGHT etc*/
                          char   *data,     /*ASCII data to be written */
                          byte    FontType, /*see FONTS.DEF */
                          boolean DisplayIt,/*=TRUE send to HW also */
                          boolean RevVideo); /*=TRUE inverts string's bitmap*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_Write
 *
 * DESCRIPTION:   1- writes a set of chars starting at a given line,offset
 *                3- selects a font type
 *
 * RETURN:        none.
 *
 * NOTES:         FontTypes  FONT_7X5:   7 lines by 5 pixels
 *                          FONT_10X7:  10 lines by 7 pixels
 *                         FONT_14X10:  14 lines by 10 pixels
 *                Restrictions:  (1) text will not go past end of line
 *                               (2) text will not go past size
 *                               (3) text will not go past NULL (string)
 * ------------------------------------------------------------------------- */
void GrphText_Write(
byte Line, /* line number 1.... */
sint Offset, /* offset given in pixels */
char *data,  /* ASCII data to be written */
byte FontType, /* what fonttype do you want the data to be */
byte length,  /* length of data */
boolean DisplayIt, /* store in virtual display for display later or
                     display it write away. */
boolean RevVideo   /* preformes reverse video on the data */
);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_WriteByCursor
 *
 * DESCRIPTION:   1- writes a string from the given cursor line offset postion
 *
 *
 * RETURN:        none.
 *
 * NOTES:         FontTypes  FONT_7X5:   7 lines by 5 pixels
 *                          FONT_10X7:  10 lines by 7 pixels
 *                         FONT_14X10:  14 lines by 10 pixels
 * ------------------------------------------------------------------------- */
void GrphText_WriteByCursor(
char *data,  /* data to be written */
byte FontType, /* font type desired */
byte length,  /* lenght of data */
boolean DisplayIt, /* write to physical display or just virtual display */
boolean RevVideo   /* reverse video data */
);
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_ InvertLine
 * DESCRIPTION:   Inverts specified line
 * RETURN:        none.
 * NOTES:         none.
 * ------------------------------------------------------------------------- */
void GrphText_InvertLine(byte Line,         /* Line number 1.... */
                         boolean DisplayIt); /* show on physical screen or just virtual */

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_SwitchDisplay
 * DESCRIPTION:   prepare module to work with specified display
 *                (internal or customer)
 * RETURN:        none
 * ------------------------------------------------------------------------ */
void GrphText_SwitchDisplay(byte Display /*DSPL1 or DSPL2*/);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_Format
 *
 * DESCRIPTION:   1- Format the screen based on rows and their hights.
 *
 * RETURN:        number of lines the display was formated with
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint GrphText_Format(
byte *LineHight /* new line format defined by user */
);
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_ReSize
 * DESCRIPTION:   changes the size of the current window
 * RETURN:        OK/ERROR
 * NOTES:         if window exceeds boundries then the window will be shortened
 *                ERROR is returned if there was an error in the input parameters
 * ------------------------------------------------------------------------ */
sint GrphText_ReSize(byte y,  /* starting row of window */
                     byte x,  /* starting columns of window */
                     byte width,  /* width of window (columns across) */
                     byte *LineFormat, /* line format determins the hight of the window  */
                     boolean DisplayIt); /* send to HW or to Virtual display only*/
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_PopUp
 *
 * DESCRIPTION:   1- Takes the screen statics and pushes them on the stack.
 *                2- Calles GrphDisp_PopUp
 *
 * RETURN:        POPUP_T_OVERFLOW/OK
 *
 * NOTES:         if window exceeds boundries then the window will be shortened
 *
 * ------------------------------------------------------------------------ */
sint GrphText_PopUp(
byte y,  /* starting row of window */
byte x,  /* starting columns of window */
byte width,  /* width of window (columns across) */
byte *LineHight, /* line format determins the hight of the window  */
boolean DisplayIt /* displays new window write away or just stores in the
                     display workspace
                   */
);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_NewPopUp
 * DESCRIPTION:   1- Takes the screen statics and pushes them on the stack.
 *                2- Calles GrphDisp_PopUp
 * RETURN:        POPUP_OVERFLOW/OK/ERROR
 * NOTES:         if window exceeds boundries then the window will be shortened
 *                ERROR is returned if there was an error in the input parameters
 * ------------------------------------------------------------------------ */
sint GrphText_PopUpNew(usint y,  /* starting row of window */
                       usint x,  /* starting columns of window */
                       usint width,  /* width of window (columns across) */
                       byte *LineHight, /* line format determins the hight of the window  */
                       boolean DisplayIt); /* send to HW or to Virtual display only*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_PopAll
 *
 * DESCRIPTION:   Pops the complete screen
 *
 *
 * RETURN:        POPUP_T_OVERFLOW/OK/ERROR
 *
 * NOTES:         You must format the the screen after This function.
 * ------------------------------------------------------------------------ */
sint GrphText_PopAll(boolean DisplayIt);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_PopDown
 *
 * DESCRIPTION:   1- Pops the last window on the display
 *
 * RETURN:        POPUP_T_UNDERFLOW/OK
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint GrphText_PopDown(boolean DisplayIt);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_Cls
 *
 * DESCRIPTION:   Clears the entire current display
 *
 * RETURN:        none.
 *
 * NOTES:         DisplayIt- will either display the cleared screen write away
 *                or just store it in the display workspace memory
 *
 * ------------------------------------------------------------------------- */
void GrphText_Cls(
boolean DisplayIt
);
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_DispInfoNew
 * DESCRIPTION:   1. Returns the number of vertical pixels (y).
 *                2. Returns the current display line format.
 * RETURN:        3. the number of horizontal pixels (x).
 * NOTES:         LineFormat must be allocated at least 17 spaces for the
 *                maximum number of lines
 * ------------------------------------------------------------------------- */
usint GrphText_DispInfoNew(usint *MaxRowPix, byte *LineFormat);
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphText_DispInfo
 * DESCRIPTION:   1. Returns the number of vertical pixels (y).
 *                2. Returns the current display line format.
 * RETURN:        none.
 * NOTES:         LineFormat must be allocated at least 17 spaces for the
 *                maximum number of lines
 * ------------------------------------------------------------------------- */
byte GrphText_DispInfo(
byte *MaxRowPix,
byte *LineFormat);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphText_ClrArea
 *
 * DESCRIPTION:   Clears a defined segment of the display in lines/coloums
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------- */
void GrphText_ClrArea(
byte F_Line,/* from line number 1... */
sint F_Offset, /* given in pixels across column */
byte T_Line, /* to line number 1.... */
sint T_Offset, /* to offset given in pixels */
boolean DisplayIt /* clear physical screen or just the virtual screen */
);

#ifdef __NOS__
  #include grphtext_nos
#endif

/*ifndef __GrphText_H */
#endif
