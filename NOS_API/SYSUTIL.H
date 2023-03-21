/****************************************************************************
 *                                                                          *
 * FILE NAME:   SYSutil.h                                                   *
 *                                                                          *
 * MODULE NAME: SYSutil.                                                    *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati & Nimrod stoler.                                *
 *                                                                          *
 * DESCRIPTION: Specific system utils.                                      *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    04.30 11/07/96.                                             *
 *                                                                          *
 * HISTORY:     None.                                                       *
 *                                                                          *
 ****************************************************************************/

#ifndef __SYSUTIL_H__
  #define __SYSUTIL_H__
	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/
/* void */

	  /*==========================================*
	   *         P A R A M E T E R S              *
	   *==========================================*/
/* void */

	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/

#define RET_ON_TIMER  255

	  /*==========================================*
	   *      T Y P E   D E C L A R A T I O N     *
	   *==========================================*/
typedef struct
{
  usint HeaderType;
  struct /*we'll make union later to accomodate different types of the header */
  {
    usint JumpTableSize;      /* number of characters in full table */
    usint NumberOfCharacters; /*number of characters in application table*/
    usint BytesPerCharDisplay;/*size of a character's bitmap in the Display table*/
    usint BytesPerCharPrinter;/*size of a character's bitmap in the Printer table*/
    char  VersionAndDate[16]; /*optional, used by the application itself*/
  } Chinese;
} ApplFontHeader;

#ifndef LOADER_PROJ

	   /*=========================================*
	    *        M I S C E L L A N E O U S        *
	    *=========================================*/
/* void */

	   /*=========================================*
	    *   F U N C T I O N  P R O T O T Y P E S  *
	    *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SysUtil_PageEditor.
 *
 * DESCRIPTION:   edits Several Lines placed inside input Queue by using
 *                LineEditor Function.
 *
 * RETURN:        exit char ESC/ENTER.
 *
 * NOTES:         FullStr contains all edit lines separated by a NULL.
 *                The Control Character returns in first byte of each Line.
 *
 * ------------------------------------------------------------------------ */
sint SysUtil_PageEditor (char *header,         /*Header of Editor*/
			  char *FullStr,
			  byte LineLen,         /*Input Length of 1 Line*/
			  byte LinesNumber);    /*Total Number of Lines*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SysUtil_LineEditor.
 *
 * DESCRIPTION:   edits a Single Line Of Printed Data including
 *                Predefined Data Edititng (Such as WIDE or NORMAL chars etc.)
 *
 * RETURN:        exit char ESC/ENTER/UP_ARROW/DOWN_ARROW.
 *
 * NOTES:         CLEAR button has changed its meaning - If Pressed it
 *                Erases the whole Line, if pressed again jumps back
 *                to Caller.
 *
 * ------------------------------------------------------------------------ */
char SysUtil_LineEditor (char *header,         /*Header on 1st Line*/
			  char *str,
			  char *ControlChar,    /* Printer Control Char*/
			  byte MaxLen);         /*Maximum Input Length*/



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SysUtil_RotateStr.
 *
 * DESCRIPTION:   Gets a 16 or more characters string and returns a constant
 *                rotatation of the string.
 *
 * RETURN:        16 characters to be displayed currently.
 *
 * NOTES:         The Time Span between every rotation is 600ms.
 *
 * ------------------------------------------------------------------------ */
char *SysUtil_RotateStr (char *rotate, boolean *Refresh);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SysUtil_GetAcc2.                 By Ofir.E 21/8/96
 *
 * DESCRIPTION:   Derived from _GetAccount exept it enables user to
 *                Set Several "requested" parameters, Notice that
 *                All the Spare parameters Should be kept 0
 *                In order to define "Parameters Not In Use"
 *                I've Added these spare parameters since I've been
 *                requested "quite a lot" to add optional features
 *                In _GetAccount, those spare parameters might be
 *                used in the future and hence, they must kept 0
 *                In this case Older application will work with newer Nos.
 *
 *                Additional Parameters:
 *
 *                TimeOutInSec - Time out while waiting for Card.
 *                               (in seconds).
 *
 *                ManualExprDate - TRUE for enables manual Expiration Date
 *				        input.
 *
 * 			           FALSE  for no manual Expiration Date
 *					  input.
 *                EditTimeOut    - Time out in seconds
 *			           (inside the Edit Dialog Box)
 *
 *                Spare - Must Kept 0.
 *
 *
 * RETURN:
 *                RET_ON_TIMER  For Time Out or:
 *
 *		  Manual: Exit character Pressed.
 *
 *
 *                Card Passed:Track2 result in Least byte
 *                  & Track1 result in most significant byte of the short
 *                  integer (See CardRdr_IsCardCompleted for more information
 *                  on status result).
 *
 * NOTES:         see _GetAccount for more information.
 *
 * ------------------------------------------------------------------------ */

sint SysUtil_GetAcc2 (char *header,     /*Header on 1st Line*/
		      char *EditLine1,      /*first edit line   */
		      char *EditLine2,      /*Second edit Line  */
		      boolean KBDInput,     /*Want Keyboard input*/
		      byte MaxLen,          /*Maximum Input Length*/

		      /* Additional parameters: */

		      usint TimeOutInSec,   /*Time Out in seconds */
		      boolean ManualExprDate, /*With or without
						  Manual Expriation Date*/
		      ulint EditTimeOut,   /* Time out in seconds
					      inside the Edit Dialog Box */
		      ulint Spare);        /* Spare parameter for future */



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SysUtil_GetAccount.
 *
 * DESCRIPTION:   edits an Account and Expiration String.
 *                Accepts : header string, 2 EditLines which are Transferred
 *                as Second Lines Headers and Keyboard Data is Formatted
 *                into them (While Erasing the Header Lines (Account and
 *                Expiration Date), KBDInput - Want Keyboard input or not
 *                and Maximum Account (!) Length (Expiration Date's Length
 *                is Always Known).
 *
 * RETURN:        Exit character Pressed or Track2 result in Least byte
 *                & Track1 result in most significant byte of the short
 *                integer (See CardRdr_IsCardCompleted for more information
 *                on status result).
 *
 * NOTES:         CLEAR button has changed its meaning - If Pressed it
 *                Erases the whole Line, if pressed again jumps back
 *                to Caller.
 *
 * ------------------------------------------------------------------------ */
sint SysUtil_GetAccount (char *header,         /*Header on 1st Line*/
		      char *EditLine1,      /*first edit line   */
		      char *EditLine2,      /*Second edit Line  */
		      boolean KBDInput,     /*Want Keyboard input*/
		      byte MaxLen);         /*Maximum Input Length*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SysUtil_EnterSum.
 *
 * DESCRIPTION:   Asks User to Enter Amount in American Format (Cents).
 *                Displays Two Headers (headerup and headerdwn) and
 *                a Formatted Amount in the Following way : "0.00...."
 *                when Number of Zeros after the decimal point (Cents) are
 *                declared by the parameter AfterPnt and Before Point (Dollars)
 *                by the parameter BeforePnt.
 *
 *
 * RETURN:        Sum String in sum. or ESC/ENTER, if no continue.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint SysUtil_EnterSum(char *headerup,
		   char *headerdwn,
		   char *sum,
		   byte AfterPnt,
		   byte BeforePnt);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME:   SysUtil_SetLanguage
 *
 * DESCRIPTION:     Set System Language & Date Format
 *                  (Set Both Printer & Display)
 *
 * PARAMETERS:      language might be one of the follows:
 *
 *                  ENGLISH(Default)
 *                  HEBREW
 *                  RUSSION
 *                  LATVIAN
 *                  ESTONIAN
 *                  HUNGARIAN
 *
 *                  date_format might be one of the follows:
 *
 *                  MONTH_DAY_YEAR
 *                  DAY_MONTH_YEAR
 *                  YEAR_MONTH_DAY
 *
 * RETURN:          None.
 *
 *
 * NOTES:           None.
 *
 * ------------------------------------------------------------------------ */
void SysUtil_SetLanguage(sint language, sint date_format);

/* --------------------------------------------------------------------------
 * FUNCTION NAME:   SysUtil_SetApplLanguage
 * DESCRIPTION:     the font for 'language' will be substituted by one descripted
 *                  in font_header (see SYSUTIL.H for structure).
 *                  Set also the Date Format.
 * PARAMETERS:      language might be one of the follows:
 *                  HEBREW
 *                  RUSSION
 *                  LATVIAN
 *                  ESTONIAN
 *                  HUNGARIAN
 *                  date_format might be one of the follows:
 *                  MONTH_DAY_YEAR
 *                  DAY_MONTH_YEAR
 *                  YEAR_MONTH_DAY
 *                  font_header should be of ApplFontHeader type (FONT.H)
 * RETURN:          None.
 * NOTES:           None.
 * ------------------------------------------------------------------------ */
void SysUtil_SetApplLanguage(sint            language,
                             sint            date_format,
                             ApplFontHeader *font_header);

#endif

#ifdef __NOS__
  #include sysutil_nos
#endif
#endif