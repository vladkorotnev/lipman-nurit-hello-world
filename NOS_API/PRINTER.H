/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * FILE NAME:   PRINTER.H                                                  *
 * MODULE NAME: PRINTER                                                    *
 * PROGRAMMER:  Oren Tir                                                   *
 *                                                                         *
 * DESCRIPTION: Printer logic level                                        *
 *              API functions declarations                                 *
 * REVISION:    01_00  May 6, 1998                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef   __PRNTER_H_INCLUDED__
#define   __PRNTER_H_INCLUDED__
                /* ======================================= *
                 *         I N T R O D U C T I O N         *
                 * ======================================= */

                /* ======================================= *
                 *           P A R A M E T E R S           *
                 * ======================================= */
/* void */

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */


#define OUT_O_PAPER     -1
#define ERROR_PRINT     -2

     /*   definitions for Printer_GetStatus      */
#define PRINTER_ACTIVE  0x0001     /* motor is/should be working           */
#define PAPER_OUT       0x0002     /* printer stopped because out of paper */
#define PAPER_JEM       0x0004     /* printer stopped because jem of paper */
#define PRINTER_ERROR   0x8000     /* hardware problem                     */

     /*     definitions for Printer_Test         */
#define WITHOUT_PRINT   0          /* for use during normal operation      */
#define WITH_PRINT      1          /* print one line                       */

     /*          control   characters            */
#define START_HALF_CUTER     0x0f /* only one control byte  */
#define START_CUTER          8  /* only one control byte  */
#define WIDE_CH              0x0E       /* large  size characters               */
#define NORM_CH              0x14       /* normal size characters (default)     */
#define GRAPHICS             0x1F       /* next byte is graphics                */


/* Ready to Print Text/Graphics Definitions: */
#define NOT_READY_ERROR      -1   /* Error in printer device */
#define NOT_READY_TIME_OUT   -2   /* Time out */
#define NOT_READY_USER_BREAK -3   /* User pressed ESC */


/* Control bytes for Printer_SetMode function */
#define STANDART_HIGH_STRING  0
/*#define TOTAL_RED_ENABLE    1*/  /* only one control byte  */
/*#define TOTAL_RED_DISABLE   2*/ /* only one control byte  */
#define RED_STRING            3  /* only one control byte  */
#define TURN_TO_RED           4  /* only one control byte  */
/*#define TURN_TO_BLACK       5*/  /* only one control byte  */
#define STRING_FORMAT_SET     6  /* 3 bytes: control byte,LineWidth,LeftMargin*/
#define DOUBLE_HIGH_STRING    7  /* FOR FUTURE USE */

#define ONE_AND_HALF_HIGH_STRING   0x15
/*#define START_CONDENSED       9*/  /* FOR FUTURE USE */
/*#define STOP_CONDENSED        10*/ /* FOR FUTURE USE */
#define CHANGE_FONT           11 /* Change byte ,FontType */
#define CHANGE_LANG           12 /* Change byte, Language */
/*******************************************************************/
/*#define SET_LINE_SPACE        11*/ /* FOR FUTURE USE */
/*#define FORM_FEED             12*//* FOR FUTURE USE */
/*#define SET_CONTROL_SEQUENCE  13*/ /* control byte, sequence size, sequence */

/*Control bytes for controling spacing between Chinese characters */
#define STRING_FORMAT_CHINESE_SET      14 
#define PRINTER_CHINESE_WITH_SPACES    0 
#define PRINTER_CHINESE_WITHOUT_SPACES 1 

/* GRAPHICS MODES FOR USE WITH Printer_DrawBitmap */
enum EX_GRAPHICS_MODE {

     EX_TEXT_ONLY = 0 ,
     EX_DOUBLE_VERTICAL ,       /* 1 */
     EX_SINGLE_LINEAR ,         /* 2 */
     EX_DOUBLE_LINEAR ,         /* 3 */
     EX_SINGLE_VERTICAL ,       /* 4 */
     EX_MAX_MODES               /* 5 */
};

#define EX_ALLIGN_LEFT        0
#define EX_ALLIGN_RIGHT       0xFFFF
#define EX_ALLIGN_CENTRE      0xFFFE

#define EX_DIRECT             0
#define EX_BUFFERED           1

#define PRINTER_TEXT_MSG_LEN_SIZE  33   /* Including terminating '\0' */

#define  PRINTER_NORMAL_PAPER 0
#define  PRINTER_HEAVY_PAPER  1




                /* ======================================= *
                 *     T Y P E   D E C L A R A T I O N     *
                 * ======================================= */


typedef struct {

  byte         Mode;        /* Graphics mode (0-3) (see EX_DIRECT and
             EX_BUFFERED */
  byte         InBuff;      /* 1 - Place data into the buffer
                               0 - Place pointer to data into the buffer */
  usint        Pixels;      /* Bytes per line */
  usint        Lines;       /* Number of lines ,ignored if InBuff == 1
                               (print only one line) */
  usint        Allign;      /* Picture allignment (see EX_ALLIGN_...) */
  byte         Reserved[ 8 ]; /* For future use */

} ExGraphicsDescriptor;


/* List of printer message definitions */
typedef enum
{
   PRINTER_MSG_INDEX_OOP    = 0,           /* Out of paper message */
   PRINTER_MSG_PAPER_LOADED = 1,
   PRINTER_NUM_OF_MSGS
} PrinterMessages;

/* Messages type to be used by user */
typedef char PrinterTextMsgs[PRINTER_NUM_OF_MSGS][PRINTER_TEXT_MSG_LEN_SIZE];


                /* ======================================= *
                 *        M I S C E L L A N E O U S        *
                 * ======================================= */
/* void */

                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_FlushBuffer
 * DESCRIPTION:   Stops print and printer reset.
 * RETURN:        void
 * NOTES:         none
 * ------------------------------------------------------------------------ */
void Printer_FlushBuffer (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_GetStatus
 * DESCRIPTION:   Returns printer status
 * RETURN:        PRINTER_ACTIVE: 0x0001 printer is working
 *                PAPER_OUT     : 0x0002 out of paper or hardware problem
 *                PAPER_JEM     : 0x0004 jem of paper or hardware problem
 *                (Idle)        : 0
 * NOTES:         none
 * ------------------------------------------------------------------------ */
sint Printer_GetStatus (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_Write
 * DESCRIPTION:   Writes a sequence of characters (a string without a
 *                terminating null). The input parameters are:
 *                SrcBuf - A pointer to the first character
 *                Length - The number of characters.
 * RETURN:        OUT_O_PAPER or the number of bytes taken for printing.
 *                (If there is not enough room for the complete string in
 *                the buffer, nothing is taken and 0 is returned).
 * NOTES:         If out of paper when this function is being called, the user
 *                will be asked to insert paper.
 * ------------------------------------------------------------------------ */
sint Printer_Write (const char *SrcBuf, usint Length);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_WriteStr
 * DESCRIPTION:   Writes an ASCII string (ended with NULL).
 * RETURN:        OUT_O_PAPER or the number of bytes taken for printing.
 *                (If there is not enough room for the complete string in
 *                the buffer, nothing is taken and 0 is returned).
 * NOTES:         If out of paper when this function is being called, the user
 *                will be asked to insert paper.
 * ------------------------------------------------------------------------ */
sint Printer_WriteStr (const char *buf);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_CheckPaperDisable
 * DESCRIPTION:   Disable the check paper routine.
 * RETURN:        none.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void Printer_CheckPaperDisable (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_CheckPaperEnable
 * DESCRIPTION:   Enable the check paper routine.
 * RETURN:        none.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void Printer_CheckPaperEnable (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_LineSpacing
 * DESCRIPTION:   Defines the space between two text lines.
 *                For graphics printing use space=0 and fast=FALSE.
 *                IMPORTANT: The user must verify that the printer is not
 *                           working when this function is being called. A
 *                           good time to call this function is immediately
 *                           after Printer_Init.
 * RETURN:        void
 * NOTES:         Before calling this function, the defaults (set by
 *                Printer_Init) are: space = 60, fast = TRUE.
 *                space - can be 0 to 255, saying how many motor turns the
 *                        printer will count between lines.
 *                fast  - says whether the paper feed (between lines) will be
 *                        fast or slow. For text, use fast paper feed (as the
 *                        default is).  For graphics use slow paper feed for
 *                        minimal (zero) space between lines.
 * ------------------------------------------------------------------------ */
void Printer_LineSpacing (byte space, boolean fast);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_WaitForTextReady, Printer_WaitForGraphicsReady
 * DESCRIPTION:   waits till printer is ready for  printing.
 * RETURN:        NOT_READY_TIME_OUT   - Time out reached and still printer
 *                                       is not ready (10 seconds) - user may
 *                                       wish to call function again.
 *                NOT_READY_USER_BREAK - User pressed ESC and still printer
 *                                       is not ready.
 *                OK                   - Printer is ready for printing.
 * NOTES:         user should not set any parameter (for Ex. Line Spacing)
 *                for its graphics printing before Printer is ready for
 *                graphics.
 * ------------------------------------------------------------------------ */
sint Printer_WaitForGraphicsReady (void);
sint Printer_WaitForTextReady (void);
/* --------------------------------------------------------------------------
* FUNCTION NAME: Printer_SetMode
* DESCRIPTION  : Set printer mode by application.
* PARAMETERS   : byte * mode which indicate the printer mode.
*                Modes:
*                Mode[0]                  | Mode[1]                    | DESCRIPTION
*             ___________________________________________________________________________
*             |RED_STRING               |                              | Print          |
*             |TURN_TO_RED              |                              | negative       |
*             |-------------------------|------------------------------|----------------|
*             |STRING_FORMAT_CHINESE_SET|PRINTER_CHINESE_WITH_SPACES   |Chinese with    |
*             |                         |PRINTER_CHINESE_WITHOUT_SPACES|or without space|
*             |-------------------------|------------------------------|----------------|
*             |STRING_FORMAT_SET        |Line width                    |Set line width  |
*             |-------------------------|------------------------------|--------------- |
*             |START_HALF_CUTER         |                              |Cutter mode     |
*             |START_CUTER              |                              |check           |
*             |-------------------------|------------------------------|_---------------|
*             |STANDART_HIGH_STRING     |                              |Change line     |
*             |DOUBLE_HIGH_STRING       |                              |Hight           |
*             |ONE_AND_HALF_HIGH_STRING |                              |                |
*             |-------------------------|------------------------------|----------------|
*             |CHANGE_FONT              | Font Id                      |Change font     |
*             |-------------------------|------------------------------|----------------|
*             |CHANGE_LANG              |                              |Chabge lang     |
*             |-------------------------|------------------------------|----------------|
* RETURN:        void
* NOTES:         
* ------------------------------------------------------------------------ */
void Printer_SetMode (byte *mode);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_PrintBitMap
 * DESCRIPTION:   Output bitmap to printer
 * RETURN:        0             - Cannot output data .Wait or abort ...
 *                Other         - Ok.
 *
 * NOTES:         (see ExGraphicsDescriptor structure)
 *
 *                 Valid modes :
 *                 0             - 192 bytes in line ,each byte for 16 lines ,
 *                                 double each pixel
 *                 1             - 48 bytes ,linear
 *                 2             - 24 bytes ,linear ,double each pixel
 *                 3             - 384 bytes ,each byte for 8 lines
 *
 *
 *      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *                 If InBuf == 0 - data must be static area.
 *                    InBuf == 1 - data can be in dynamic array.
 *      !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * ------------------------------------------------------------------------ */
sint Printer_PrintBitMap( ExGraphicsDescriptor * egd ,byte * data );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_GetLineFormat
 * DESCRIPTION:   Read the current line width and left margine
 * RETURN:        Line width.
 * NOTES:         If Width == 0 then there is no limit on the width of lines.
 * ------------------------------------------------------------------------ */
byte Printer_GetLineFormat (byte *Margine);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_GraphLogo
 * DESCRIPTION:   Prints logo
 * RETURN:        0 - Error
 * NOTES:         See GrphLogoHeadStr ...
 * ------------------------------------------------------------------------ */
sint Printer_GraphLogo(char *BlockName);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Printer_SetMessages
 *
 * DESCRIPTION:   Sets NOS user messages.
 *
 * PARAMETERS:    Messages - Pointer to a two dimensional array that contains
 *                           the messages :
 *
 *                           Messages[ 0 .. 32] - Message #0
 *                           Messages[33 .. 65] - Message #1
 *                                            .
 *                                            .
 *                                            .
 *
 *                           See the enumerated type PrinterMessages for messages
 *                           meaning.
 *
 *                           If this poniter is NULL the default english
 *                           nessages will be used.
 *
 * RETURN:        void.
 *
 * NOTES:         The maximum message index is PRINTER_NUM_OF_MSGS
 *
 * ------------------------------------------------------------------------ */
void Printer_SetMessages(const char *Messages);
/* --------------------------------------------------------------------------
 * FUNCTION NAME: Printer_GetFontHandle
 * DESCRIPTION  : Get printer font block handle
 * PARAMETER    : char * FontName    - 6 charachters font name.
 * RETURN:        none.
 * NOTES:         Called by application.
 * ------------------------------------------------------------------------ */
#ifdef NOS_WITH_DYNAMIC_PRINTER_FONT
char Printer_GetFontHandle(char * FontName);
#endif
/* --------------------------------------------------------------------------
*
* FUNCTION NAME: Printer_AdjustPaper
*
* DESCRIPTION  : Adjust printer paper forward or backward in a pixel resolution.
*
* PARAMETERS   :
*                sint NumberOfPixels  - Number of lines to move printer's paper
*                                       (pixel resolution).
*                                       Positive value (>0) move paper forward.
*                                       Negative value (<0) move paper backword.
* RETURN:        none.
*
* NOTES:         
*
* ------------------------------------------------------------------------ */
void Printer_AdjustPaper(sint NumberOfPixels);
/* --------------------------------------------------------------------------
*
* FUNCTION NAME: Printer_SetPaperMode
*
* DESCRIPTION:   Set printer paper mode .               
*
* PARAMETERS:    byte PaperMode :PRINTER_NORMAL_PAPER 
*                                PRINTER_HEAVY_PAPER   150g.
* RETURN:        none.
*
* NOTES:         none.
*
* ------------------------------------------------------------------------ */
void Printer_SetPaperMode(byte PaperMode);
#ifdef __NOS__
  #include printer_nos
#endif

#endif /*#ifndef   __PRNTER_H_INCLUDED__*/
