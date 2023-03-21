/****************************************************************************
 *                                                                          *
 * FILE NAME:   display.h                                                   *
 *                                                                          *
 * MODULE NAME: display.                                                    *
 *                                                                          *
 * PROGRAMMER:  Shmuel Meymann.                                             *
 *                                                                          *
 * DESCRIPTION: display driver for 2 display units 2X16 characters each     *
 *              selected by ident. the lang of the display selected by lan  *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01.10 01/06/94.                                             *
 *                                                                          *
 * HISTORY:     <Version history>.                                          *
 *                                                                          *
 ****************************************************************************/

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
#ifndef __Display_H
  #define __Display_H

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

#define DSPL1         1          /* Display #1 identity number */
#define DSPL2         2          /* Display #2 identity number */
#define SYMBOL_START  192        /* Start of symbol table (arrows etc.) */
#define SYMBOL_LENGTH 15         /* Length of symbol table */
#define SYMBOL_END    SYMBOL_START+SYMBOL_LENGTH-1
                                 /* End of symbol table */
#define UPPER_DISPLAY 0
#define LOWER_DISPLAY 1


/* Display Type : (Compatible for Both The Old Display Type
   & The Hebrew - Arabic One.*/
#define HEBREW_ARAB_DISPLAY

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

typedef enum
{
    LEFT_JST            =0,   /* -\                         */
   RIGHT_JST            =0x10,/*   --overwrite prev display */
  CENTER_JST            =0x20 /* -/                         */
} format;




           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_PopUp(int ident,char *text,char *buf_into_save)
 *
 * DESCRIPTION:   save current display in buf_to_save and outputs text string
 *                to display.
 *
 *                ident         - DSPL1 or DSPL2.
 *                text          - text to be displayed.
 *                buf_into_save -  buffer of 32 bytes to save current display.
 *
 * RETURN:        none.
 *
 * NOTES:         Usage:
 *                Calling this function and later on calling to
 *                Display_RestorePopUp() to display previous text.
 *
 * ------------------------------------------------------------------------ */
void Display_PopUp(int ident,char *text,char *buf_into_save);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_PopDown(int ident,char *saved_buf)
 *
 * DESCRIPTION:   Displays previous text (Before pop up).
 *                to display.
 *
 *                ident         - DSPL1 or DSPL2.
 *                saved_buf     - buffer of 32 bytes used to save the
 *                                display in Display_PopUp.
 *
 * RETURN:        none.
 *
 * NOTES:         Usage:
 *                Calling Display_PopUp and later on calling
 *                this function to display previous text.
 *
 * ------------------------------------------------------------------------ */
void Display_PopDown(int ident,char *saved_buf);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_ClrLDisp
 *
 * DESCRIPTION:   Clears the lower display line
 *
 * RETURN:        none.
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void Display_ClrLDisp(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_ClrUDisp
 *
 * DESCRIPTION:   Clears the upper display line
 *
 * RETURN:        none.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */

void Display_ClrUDisp(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_Cls
 *
 * DESCRIPTION:   Clears a certain display port
 *
 * RETURN:        none.
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void Display_Cls(int ident); /* Ident = DSPL1 or DSPL2 */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_ClrDsp
 *
 * DESCRIPTION:   Clear display.
 *
 * RETURN:        none.
 *
 * NOTES:         For speed conciderations, only display #1 will be cleaned
 *
 * ------------------------------------------------------------------------ */

void Display_ClrDsp(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_BlinkingOn
 *
 * DESCRIPTION:   Cause blinking on display
 *
 * RETURN:        none.
 *
 * NOTES:         ident  = DSPL1 or DSPL2
 *                period = Blinking period in mSec (100mS resolution)
 *
 * ------------------------------------------------------------------------ */

void Display_BlinkingOn(int ident, int period);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_BlinkingOff
 *
 * DESCRIPTION:   Siezes blinking on a display port.
 *
 * RETURN:        none.
 *
 * NOTES:         ident  = DSPL1 or DSPL2
 *
 * ------------------------------------------------------------------------ */

void Display_BlinkingOff(int ident);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_DownDisplay
 *
 * DESCRIPTION:   Displays the desired message on the display bottom line.
 *
 * RETURN:        none.
 *
 * NOTES:         If text is too short, the rest of the line will be filled
 *                 with spaces
 *                If text is too long, it would be trimmed to the length of
 *                 the line (16 characters including space)
 *
 * ------------------------------------------------------------------------ */

void Display_DownDisplay(char *msg); /* msg = Message to be displayed */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_UpDisplay
 *
 * DESCRIPTION:   Displays the desired message on the display top line.
 *
 * RETURN:        none.
 *
 * NOTES:         If text is too short, the rest of the line will be filled
 *                 with spaces
 *                If text is too long, it would be trimmed to the length of
 *                 the line (16 characters including space)
 *
 * ------------------------------------------------------------------------ */

void Display_UpDisplay(char *msg); /* msg = Message to be displayed */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_Write.
 *
 * DESCRIPTION:   This function writes to display a transparent line
 *                (No CLR to end of screen) according to the length
 *                specified by length
 *
 * RETURN:        Current language. Language constants are specified in
 *                NURIT.DEF
 *
 * NOTES:         ident may be set to either DSPL1 or DSPL2. If Display 2
 *                is not supported by hardware, the statement will be
 *                IGNORED !
 *
 * ------------------------------------------------------------------------ */

int Display_Write(int ident,           /* DSPL1 or DSPL2 */
                  char *array_to_dump, /* String to be dunped */
                  int length);         /* Length of required string */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_WriteStr.
 *
 * DESCRIPTION:   This function writes to display a transparent line
 *                (No CLR to end of screen) Suffixed by a NULL character.
 *                If line is shorter than 32, the rest wouldn't be
 *                Erased. (Similar to Display_Write)
 *
 * RETURN:        Current language. Language constants are specified in
 *                NURIT.DEF.
 *
 * NOTES:         ident may be set to either DSPL1 or DSPL2. If Display 2
 *                is not supported by hardware, the statement will be
 *                IGNORED !
 *
 * ------------------------------------------------------------------------ */

int  Display_WriteStr(int ident,            /* DSPL1 or DSPL2 */
                      char *array_to_dump); /* Subject string */

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Display_SetFont
 * DESCRIPTION:   set default font that will be used in Display_FormatWrite
 * RETURN:        none.
 * NOTES:         in the case of non-graphic display nopthing happens
 * ------------------------------------------------------------------------ */
void Display_SetFont(byte ApplFont);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Display_FormatWrite
 * DESCRIPTION:   Displays the desired message justified to LEFT, RIGHT or
                  CENTER into specified line (in the current window)
 * RETURN:        none.
 * NOTES:         If text is too short, the rest of the line will be filled
 *                 with spaces
 *                If text is too long, it would be truncated to the length
                  of the line
 * ------------------------------------------------------------------------ */
void Display_FormatWrite(int ident, byte line, byte format, char *msg);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_OnOff.
 *
 * DESCRIPTION:   puts the display on or off.
 *
 * RETURN:        none.
 *
 * NOTES:         ident may be set to either DSPL1 or DSPL2. If Display 2
 *                is not supported by hardware, the statement will be
 *                IGNORED !
 *
 * ------------------------------------------------------------------------ */

void Display_OnOff( int ident,             /* DSPL1 or DSPL2 */
                    boolean on_off );      /* True=ON False=OFF */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_VisibleCursor.
 *
 * DESCRIPTION:   Displays or omits a visible cursor.
 *
 * RETURN:        none.
 *
 * NOTES:         ident may be set to either DSPL1 or DSPL2. If Display 2
 *                is not supported by hardware, the statement will be
 *                IGNORED !
 *
 * ------------------------------------------------------------------------ */

void Display_VisibleCursor(int ident,            /* Dispaly identity */
                           char cursor);         /* Cursor ON/OFF    */
                   /* Any value else than ON or OFF shall be ignored */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_CursorMoveTo.
 *
 * DESCRIPTION:   Move The Cursor X spaces from start of Line n.
 *
 * RETURN:        none.
 *
 * NOTES:         ident may be set to either DSPL1 or DSPL2. If Display 2
 *                is not supported by hardware, the statement will be
 *                IGNORED !
 *
 * ------------------------------------------------------------------------ */

void Display_CursorMoveTo(int ident,            /* Dispaly identity */
                          char LineNo,          /* starting of Line Number */
                          byte MoveDistance);   /* How Many to move cursor */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Display_BlinkAtCursor.
 *
 * DESCRIPTION:   Causes or forbids blinking at cursor position.
 *
 * RETURN:        none.
 *
 * NOTES:         ident may be set to either DSPL1 or DSPL2. If Display 2
 *                is not supported by hardware, the statement will be
 *                IGNORED !
 *
 * ------------------------------------------------------------------------ */

void Display_BlinkAtCursor(int ident,             /* Dispaly identity  */
                           char blink_at_cursor); /* Blink at cursor   */
                                                  /* Position : ON/OFF */
                     /* Any value else than ON or OFF shall be ignored */

#ifdef __NOS__
  #include display_nos
#endif

#endif /*ifndef __Display_H*/
