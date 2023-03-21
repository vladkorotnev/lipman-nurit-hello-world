/****************************************************************************
 *                                                                          *
 * FILE NAME:   FORMATER.H                                                  *
 *                                                                          *
 * MODULE NAME: FORMATER for 2050/60/70 & loaders                           *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati.                                                *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * DESCRIPTION: Menu Library Prototypes                                     *
 *                                                                          *
 * REVISION:    5.00 06/07/94.                                              *
 *                                                                          *
 ****************************************************************************/

#ifndef __FORMATER_H_
#define __FORMATER_H_

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
          /*==========================================*
           *             I N C L U D E S              *
           *==========================================*/
#include formater_def

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/


/* Menu mode_flag definitions for menu structure: */



#define DEFAULT_MODE   0x0 /* default menu mode */
#define NUMBERS_SELECT 0x1 /* if user pressed a number key step into it's */
			   /* entry. */
#define CYCLIC_MENU    0x2 /* if end of menu reached the next entry will be
                              selected (e.g if last entry is selected and
                              down key was pressed first entry will be
                              selected) */
#define NO_NUMBER_SHOW 0x4 /* Does not show numbers */

/* 0x8,0x10 are empty */

/* Time out definitions for mode_flags bits 5,6,7: */

#define MENU_TIMEOUT_2_SEC  0x20
#define MENU_TIMEOUT_5_SEC  0x40
#define MENU_TIMEOUT_10_SEC 0x60
#define MENU_TIMEOUT_30_SEC 0x80
#define MENU_TIMEOUT_1_MIN  0xa0
#define MENU_TIMEOUT_2_MIN  0xc0
#define MENU_TIMEOUT_5_MIN  0xe0

/* Menu mode parameter for go_menu : */

/* mode : bit 0 */

#define MENU_MODE 0    /* Used as the parameter for go_menu whether the */
		       /* menu will be in pop up mode (MENU_MODE) */
		       /* or in CHOICE mode (CHOICE_MODE)*/
#define CHOICE_MODE 1

/* mode flags: bit 1 */

#define MENU_JUMP_NEXT 2 /* if this flag is defined return back to menu */
			 /* will increase line no by 1 */
/* mode bits : 2,3 */
/* Added for version 04_40 :
   New options for mode parameter in ..GoMenu functions: bits 2,3 */

#define AUTO_SCROLL_MENU_HSEC 0x04
#define AUTO_SCROLL_MENU_1SEC 0x08
#define AUTO_SCROLL_MENU_3SEC 0x0C



/* Format for dialog_box (FLAGS) :*/

/*      Definition:    Valid characters:        bit 0,1,2*/

#define __STRING  0x0  /* Any character */
#define __INTEGER 0x1  /* digits and optional hex letters */
#define __LONG    0x2  /* digits and optional hex letters */
#define __BYTE    0x3  /* digits and optional hex letters */

#define __FLOAT   0x4  /* digits and optional hex letters */
                       /* (and float point) */

#define __POINT   0x5  /* digits and decimal point */

#define __PASSWORD 0x6  /* Any character, displayed as '*' */

#define __STRING_TO_LEFT  0x7  /* Any character from rigth to left*/

/* definitions for selected format -  bits 3,4 */

#define DEFAULT_FORMAT           0x00 /* decimal for integers and float and */
                                      /* all characters valid for srings */
#define HEX_ONLY                 0x08 /* hex-decimal digits and letters only */
                                      /* (in flot point '.' is valid too)  */
#define DIGITS_ONLY              0x10 /* decimal digits only */
                                      /* (in flote point '.' is valid too)  */
#define TRUE_DIGITS_ONLY         0x18

/* mode of editor bit 5 */

#define OVERWRITE_ONLY           0x20 /* If this flag is zero then it is */
                                      /* DEFAULT FORMAT : both insert and */
                                      /* overwrite. */

/* bit #6 */

#define DISPLAY_CURSOR_POSITION 0x40 /* Used for long strings to display */
                                      /* the index in the string. */

/* disable beep bit #7 */

#define BEEP_DISABLED            0x80 /* When this flag is zero dialog */
                                      /* will beep each time user presses */
                                      /* non valid key. */


#define MAX_EXIT_KEYS             20   /* Maximum user defined Exit keys */

typedef struct
{
  char *header;      /* header string */
  void *format;      /* Format pointer to string or
                        integer and so on . . . */
  byte format_flags; /* format flags */
  byte length;       /* max of length to be editted
					    (relevant in string editting only) */
  byte return_value; /* used as a returned value
                        from dialog_box (since dialog_box is void) */
} dialoge;

typedef dialoge dialog;

typedef struct
{
  byte EntriesFont; /* Used for Font Type for GrphText function */
  byte HeaderFont;  /* Used for Font Type for GrphText function */
  byte Format[31];  /* Height for every line */
  byte spare[9];

} WinFormat;



/* Flags for EditBox. */
#define  EB_SOFT_KB_ENABLE             0x01     /* Enable SoftKB when opening.         */
#define  EB_OVERWRITE                  0x02     /* Overwrite data (Default: Insert).   */
#define  EB_RIGHT_TO_LEFT              0x80     /* Edit from Right to Left.            */
/* Do not use - for future usage:      0x10   -/
/-                                     0x20   -/
/-                                     0x40   */



/*------------------------------------------------------------/ 
/- ExitStr    - (16 chars)*2, 'ENTER' to save, 'ESC' not to.
/- DataSize   - not more than 256.
/- BoxLineNum - if box too big, as big as possible. 
/- Flags      - EB_SOFT_KB_ENABLE, EB_OVERWRITE, 
/-              EB_RIGHT_TO_LEFT
/------------------------------------------------------------*/ 
typedef struct
{
   char  *Header,          /* Header of EditBox.             */
         *ExitStr,         /* Exit string.                   */
         *Data;            /* Buffer for data.               */
   usint  DataSize;        /* Size of Data.                  */
   byte   BoxLineNum,      /* # of lines in box (excludind   */ 
                           /* header). Page could be larger! */
          PageWidth;       /* # of char's in line. Could be  */
                           /* larger than Box.               */          
   usint  Flags;           /* Bitmap.                        */
} EditBox;



          /*==========================================*
           *       P R I V A T E  T Y P E S           *
           *==========================================*/


          /*==========================================*
           *        P R I V A T E  D A T A            *
           *==========================================*/

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

           /*=========================================*
            *   P U B L I C     F U N C T I O N S     *
            *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_SetTout.
 * DESCRIPTION:   Set time out in sec for menu and dialog box.
 * RETURN:        None.
 * NOTES:         None.
 * ------------------------------------------------------------------------ */
void Formater_SetTout(usint timeout);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_Form.
 * DESCRIPTION:   Initialization for font statics and GrphText_Format.
 * RETURN:        none.
 * NOTES:         GrphText_Format return the line_form - number of row in
 *                window.
 * ------------------------------------------------------------------------ */
void Formater_Form(WinFormat *win_format);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_AdditionalExitKey
 * DESCRIPTION:   Used For Defining extra keys for Aborting Menu/Dialog Box.
 *                exit_keys_string is a string in which each character
 *                represents an "Exit Key".
 *                for no additional exit key: exit_keys_string[0] = 0    -
 *                or exit_keys_string = 0
 * RETURN:        none.
 * NOTES:         Prototype Changed From ver 04_50 (as requested by
 *                Irina - Lipman USA).
 * ------------------------------------------------------------------------ */
void Formater_AdditionalExitKey(char *exit_keys_string);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_SetAutoScroll
 * DESCRIPTION:   Sets the auto scroll mode (for All menus)
 *                mode(scroll mode):
 *                ON - All menus work with autoscroll.
 *                OFF - NON Auto scroll mode (except menus which will be
 *                      opened with specified parameters in the _GoMenu
 *                      function)
 *                delay(scroll time): delay time in miliseconds before
 *	          updating new menu line.
 * RETURN:        none.
 * NOTES:         Used By Application.
 * ------------------------------------------------------------------------ */
void Formater_SetAutoScroll(boolean mode,usint delay);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_GoMenu.
 * DESCRIPTION:   Performs the menu-select operation.
 *                m    : pointer to menu structure.
 *                mode : MENU_MODE or CHOICE_MODE or:
 *                AUTO_SCROLL_MENU_HSEC
 *                       AUTO_SCROLL_MENU_1SEC
 *                AUTO_SCROLL_MENU_3SEC
 *                       these are used for auto scrolling in the menu
 *                       update time 0.5s,1s or 3s.
 * RETURN:        return value : if mode is MENU_MODE return value is NULL
 *                               and it shold be ignored.
 *                               if mode is CHOICE_MODE return value is the
 *                               entry number or NULL if user pressed
 *                               ESCAPE or menu not exists.
 *                      !!! If any additional exit key was be pressed,
 *                          the function returns the negative value
 *                          of this key.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint Formater_GoMenu(menu *m,sint mode);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_GoMenuExt
 * DESCRIPTION:   Run a Formater Menu with extended options.
 *                pMenu     - pointer to menu structure (formater.def).
 *                pMenu_Ext - pointer to a Menu_Ext struct (formater.def).
 * RETURN:        MENU_MODE:   return value is NULL
 *                CHOICE_MODE: return value is the entry number or NULL if 
 *                             user pressed ESCAPE or menu not exists.
 *                             !!! If any additional exit key was pressed,
 *                             returns the negative value of this key.
 *                             (See pMenu_Ext.Mode)
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint Formater_GoMenuExt ( menu     * pMenu,
                          Menu_Ext * pMenu_Ext );


/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_GoMenuEntry.
 * DESCRIPTION:   Performs the menu-select operation.
 *                m    : pointer to menu structure.
 *                mode : MENU_MODE or CHOICE_MODE or:
 *		         AUTO_SCROLL_MENU_HSEC
 *                       AUTO_SCROLL_MENU_1SEC
 *		         AUTO_SCROLL_MENU_3SEC
 *                       these are used for auto scrolling in the menu
 *                       update time 0.5s,1s or 3s.
 *                entry: which line will be displayed.
 * RETURN:        return value : if mode is MENU_MODE return value is NULL
 *                               and it shold be ignored.
 *                               if mode is CHOICE_MODE return value is the
 *                               entry number or NULL if user pressed
 *                               ESCAPE or menu not exists.
 *                      !!! If any additional exit key was be pressed,
 *                          the function returns the negative value
 *                          of this key.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint Formater_GoMenuEntry(menu *m,sint mode,usint entry_no);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_DialogeBox.
 * DESCRIPTION:   Performs Input operation:.
 *                void *paremeters is pointer to a dialog structure:
 *                header       - pointer to header string
 *                format       - pointer to format (STRING,INTEGER,LONG,FLOAT).
 *                format_flags - determine what format data is (STRING,INTEGER
 *                               ,LONG,FLOAT) and it's mode:
 *                               DEFUALT_MODE or other defined in formater.h.
 *                length   -     max length of string to be returned.
 *                               (for __STRING mode up to 255).
 *                return_value : size of string or NULL if user pressed
 *                               ESCAPE (or size (in bytes) of new string
 *                               in return_value field .
 * RETURN:        Last key (in ascii) pressed (MENU/ENTER).
 * NOTES:         This function requires at least 1K bytes of stack.
 *                Doesn't Support Languages.
 * ------------------------------------------------------------------------ */
char Formater_DialogeBox(void *parameters);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_PreDialogeBox.
 * DESCRIPTION:   Call to dialogue box with character value ,  this char
 *                is treated as if it was the first key to be pressed.
 *                parameters : - see Formater_DialogeBox
 *                chr - character value.
 * RETURN:        what Formater_DialogeBox returns.
 * NOTES:         Used when you need to reuse a single key stroke :
 *                For Ex:
 *                When waiting for a magnetic card you need to jump
 *                to the dialogue box with a 'NUMBER' ascii value if one
 *                pressed.
 *                Unlike Formater_DialogeBox , this function cannot be
 *                called via entry structure (because of it's prototype) !
 *                Doesn't Support Languages.
 * ------------------------------------------------------------------------ */
sint Formater_PreDialogeBox(void *parameters,char chr);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_GetStrChoice.
 * DESCRIPTION:   Performs menu-choice operation.
 *                *header:header string for menu.
 *                *str   :pointer to first string of strings array.
 *                size   :size of all strings.
 *
 *                Ex:    NULL      NULL     NULL
 *                |--------|--------|--------|
 *                "LINE #1""LINE #2""LINE #3" size=(8*3).
 *                |--------|--------|--------|
 * RETURN:        0 - if pressed ESC , or line number (1..no of strings).
 * NOTES:         Doesn't Support Languages.
 * ------------------------------------------------------------------------ */
char Formater_GetStrChoice(char *header,char *first_str,usint size_of_all);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Formater_EditBox.
 *
 * DESCRIPTION:   Performs Input operation for many lines.
 *
 * INPUT:         pEditBox  - EditBox structure casted to void.
 *
 * RETURN:        Last key (in ascii) pressed (MENU/ENTER).
 *
 * NOTES:         
 *                
 *
 * ------------------------------------------------------------------------ */
char Formater_EditBox ( void*  pEditBox );
 
#ifdef __NOS__
  #include formater_nos
#endif

#endif __FORMATER_H_
