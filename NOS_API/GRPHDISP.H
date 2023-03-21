/****************************************************************************
 *                                                                          *
 * FILE NAME:   Grphdisp.h                                                  *
 *                                                                          *
 * MODULE NAME: Grphdisp                                                    *
 *                                                                          *
 * PROGRAMMER:  Ephraim Ben-Ishai                                           *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * DESCRIPTION: Lower level graphic primitives and virtual screen           *
 *              management                                                  *
 *                                                                          *
 * $Revision:   1.0  $                                                      *
 *                                                                          *
 * $Date:   24 Nov 1994 11:32:38  $                                         *
 *                                                                          *
 * $Log:   N:\subj\68drv\grphdisp\src\vcs\grphdisp.h__  $                   *
 *                                                                          *
 *    Rev 1.0   24 Nov 1994 11:32:38   EphraimBenIshai                      *
 * Initial revision.                                                        *
 *                                                                          *
 ****************************************************************************/
#ifndef __GRPHDISP_H__
  #define __GRPHDISP_H__
          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
/*
This module implements the following:
            1. Creates a virtual display workspace
            2. Saves and restors window segments to and from the workspace.
            3. Writes characters with different font type to the workspace.
            4. Calls specific display driver for writting to the display
            5. Writes/reads stray bytes into the virtual workspace.
            6. Graphic primitive funcitons line,setpixel

1. Creates a virtual display workspace
The actual column/row of the display is only know to the module at its
creation. At that time the module allocates memory space for the virtual
display and the stack. Memory is allocated for the virtual display using
the following eq:
                 column*row/8 (bytes)
Memory is also allocated for the stack. The stack is used for saving window
sections from the virtual display. It is assumed that a window to be saved
will not be more than one fourth the entire display size. The parameter that
is used to determine the memory space is the MaxWindow this can be 1,2,5....
whatever. Using this parameter the following equations allocates the memory
space:
                 (column*row/8)*(1/4)*MaxWindows (bytes)
It should be noted that windows can be created that exceed the MaxWindow
size as long as the total amount of memory allocated to the stack has not
exceeded.


2. Saves and restors window segments to and from the workspace.
Segments of the display can be stored so that new information can be written
in their place thus, allowing windowed information. The area that needs to
be stored is calculated and checked aganst an upper bound value of the
allocated stack memory. If there is room on the stack then the current area
is copied along with pertinent information about the area being stored
(starting col,starting row,ending row ending col). The top byte of the last
piece of information stored is refereced by an index. This index is used to
retrieve the window from the stack. Retreiving is done by first reading the
stack header and then using its information to read the data back into the
virtual display.

3. Writes characters with different font type and performs reversed video.
There are three font types defined by the tables below which are available
for display. the width inbetween characters is determined by the user. It
is recomended that this width be as follows: for 7X5 one pixel inbetween
characters making it a total of 6 pixels. For the 10X7 and 14X10 two pixels
inbetween characters making the 9 and 12 pixels apart respectively.
The given row and col are at the bottom left hand side of the character.
Characters are written to the virtual memory according the the lenght
given. There is no checking done on the total length or if the characters
are stings what is given is written upto the given length. There are three
cursor widths per font type: 1 line 2 line and 3 line cursors these are
located at 0x1D, 0x1E, 0x1F respectively in the ASCII font table.

4. Calls specific display driver for writting to the display
The virtual display is sent to the hardware display using a specific display
dirver.

5. Writes/reads stray bytes into the virtual workspace.
This allows the user to read a segment out of the virtual display in order
to later proccess that segment. Any segment can be written to the display
using the Write routine.

6. Graphic primitive funcitons line,setpixel
These functions are used as privates for this module. However, the are given
to the public so that advanced grphic routines can be written based on these
primitives.*/


          /*==========================================*
           *             I N C L U D E S              *
           *==========================================*/

#if (defined(COLOR_DISPLAY) || defined(_ARM))
   #include grphdisp_def
   #include bmp_def
#endif


          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

/* font types : */
#ifdef MAX_FONTS
  #undef MAX_FONTS
#endif
#ifndef NOS_WITH_DYNAMIC_FONT
 #define MAX_FONTS          11
#else
 #define MAX_FONTS          255
#endif
#define FONT_24X16         10
#define FONT_CHINESE12X12   9
#define FONT_13X7           8
#define FONT_10X7BOLD       7
#define FONT_8X8            6
#define FONT_16X16_WORDS    5
#define FONT_16X8_HIGH      4
#define FONT_16X8_LOW       3
#define FONT_14X10          2
#define FONT_10X7           1
#define FONT_7X5            0

/* popup related */
#define POPUP_OVERFLOW  10    /* user can not make anymore popup windows */
#define POPUP_UNDERFLOW 20    /* there is nothing to pop */
#define POPUP_OK        30    /* the pop operation succeeded */
/* the following are defined per font type in the ASCII font tables */
#define LINE_1          0   /* one line cursor */
#define LINE_2          1   /* two line cursor */
#define LINE_3          2   /* three line cursor */
#define FILL            3   /* cursor covers the character completely */
#define VERTICAL_CURSOR 4   /* Rectangle with exlusive left edge      */
#define BIT_ON            0    /* turn pixel on at a given row,col    */
#define BIT_OFF           1    /* turn pixel off at a given row,col   */


#if (defined(COLOR_DISPLAY) || defined(_ARM))

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

typedef enum
{
  WINFRAME_NO_FRAME =0,
  WINFRAME_2D_SIMPLE=1,
  WINFRAME_3D_SIMPLE=2,
} WindowFrame;

typedef struct
{
  long from;
  long to;
} ConvertColor;


           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphDisp_SetPixel
 * DESCRIPTION:   sets a pixel at a given col,row on/off in the virtual
 *                memory buffer
 * RETURN:        none.
 * NOTES:         Toggle (in case of B&W display): BIT_ON: sets pixel on
 *                                                 BIT_OFF: sets pixel off
 *                in case of the color display the 'Toggle' will define color
 *                to set pixel to
 * ------------------------------------------------------------------------- */
void GrphDisp_SetPixel(usint row,    /* row of pixel */
                       usint col,    /* column of pixel */
                       long  color);  /* Color to set pixel to */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphDisp_Line
 *
 * DESCRIPTION:   Writes a line inbetween two points to the virtual memory
 *                buffer.
 *
 * RETURN:        none.
 *
 * NOTES:         straight and diagonal line allowed
 *                the only white line will be drawn
 * ------------------------------------------------------------------------- */
void GrphDisp_Line( byte startx, /* from column */
                    byte starty, /* from row    */
                    byte endx,   /* to column   */
                    byte endy);   /* to row      */
/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphDisp_NewLine
 * DESCRIPTION:   Writes a line inbetween two points to the virtual memory
 *                buffer.
 * RETURN:        none.
 * NOTES:         the input parameters  are of the USINT type now to be
 *                compatibale with the bigger screen. However in oprder to
 *                preserve the backward compatibility the old function is
 *                also alive (this function was accessible to the application)
 * ------------------------------------------------------------------------- */
void GrphDisp_NewLine( usint startx, /* from column */
                       usint starty, /* from row    */
                       usint endx,   /* to column   */
                       usint endy,   /* to row      */
                       long  color); /* color to draw th eline of */

#else /*#ifdef COLOR_DISPLAY*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphDisp_SetPixel
 *
 * DESCRIPTION:   sets a pixel at a given col,row on/off in the virtual
 *                memory buffer
 *
 * RETURN:        none.
 *
 * NOTES:         Toggle:
 *                        BIT_ON: sets pixel on
 *                       BIT_OFF: sets pixel off
 *
 * ------------------------------------------------------------------------- */
void GrphDisp_SetPixel(byte row,    /* row of pixel */
                       byte col,    /* column of pixel */
                       byte Toggle); /* BIT_ON/BIT_OFF sets pixel on/off */
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: GrphDisp_Line
 *
 * DESCRIPTION:   Writes a line inbetween two points to the virtual memory
 *                buffer.
 *
 * RETURN:        none.
 *
 * NOTES:         straight and diagonal line allowed
 *
 * ------------------------------------------------------------------------- */
void GrphDisp_Line( byte startx, /* from column */
                    byte starty, /* from row    */
                    byte endx,   /* to column   */
                    byte endy);   /* to row      */
#endif /*#ifdef COLOR_DISPLAY*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GrphDisp_NewLine
 * DESCRIPTION:   Writes a line inbetween two points to the virtual memory
 *                buffer.
 * RETURN:        none.
 * NOTES:         the input parameters  are of the USINT type now to be
 *                compatibale with the bigger screen. However in oprder to
 *                preserve the backward compatibility the old function is
 *                also alive (this function was accessible to the application)
 * ------------------------------------------------------------------------- */
void GrphDisp_NewLine( usint startx, /* from column */
                       usint starty, /* from row    */
		       usint endx,   /* to column   */
		       usint endy,   /* to row      */
		       long  color); /* color to draw th eline of */

#ifdef __NOS__
  #include grphdisp_nos
#endif
#endif
