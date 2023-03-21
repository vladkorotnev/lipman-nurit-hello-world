/* **************************************************************************
 *                                                                          *
 * FILE NAME:   prntutil.h                                                  *
 *                                                                          *
 * MODULE NAME: prntutil.                                                   *
 *                                                                          *
 * PROGRAMMER:  Shmuel Meymann.                                             *
 *                                                                          *
 * DESCRIPTION: User printer Utils                                          *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01.00 02/06/94.                                             *
 *                                                                          *
 * HISTORY:     <Version history>.                                          *
 *                                                                          *
 ****************************************************************************/
#ifndef __PRNTUTIL_H__
  #define __PRNTUTIL_H__

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
#define MONTH_DAY_YEAR  0
#define DAY_MONTH_YEAR  1


          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
/* void */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Cr
 *
 * DESCRIPTION:   Prints a line feed n times
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Cr(int n);  /* N§ of lines to feed */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_FormFeed
 *
 * DESCRIPTION:   Prints six empty lines.
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_FormFeed(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_UpperCase
 *
 * DESCRIPTION:   Sets BOLD character to printer.
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */
void PrntUtil_UpperCase(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_DateTime
 *
 * DESCRIPTION:   Prints the present date and time
 *
 * RETURN:        None
 *
 * NOTES:         The printing format shall be dd/mm/yy hh:mm
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_DateTime(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Date
 *
 * DESCRIPTION:   Prints the present date
 *
 * RETURN:        None
 *
 * NOTES:         The printing format shall be dd/mm/yy.
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Date(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_IntTime
 *
 * DESCRIPTION:   Translate an integer to time.
 *
 * RETURN:        None
 *
 * NOTES:         The printing format shall be hh:mm
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_IntTime(int data);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Time
 *
 * DESCRIPTION:   Prints the present time
 *
 * RETURN:        None
 *
 * NOTES:         The printing format shall be hh:mm
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Time(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_ALine
 *
 * DESCRIPTION:   Prints "************************"
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_ALine(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Int
 *
 * DESCRIPTION:   Prints an integer and text with line_feed.
 *
 * RETURN:        None
 *
 * NOTES:         The integer value will be justified to the left.
 *                The text string will be justified to the right,
 *                     and it MUST end with NULL.
 *		  In case of collision, Last LETTERs will be run over.
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Int(int data,   /* Number to print */
		            char *buf);  /* Text to print   */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_DataSum
 *
 * DESCRIPTION:   Prints an amount with a decimal point.
 *
 * RETURN:        None
 *
 * NOTES:         The integer value will be justified to the left.
 *                The text string will be justified to the right,
 *                     and it MUST end with NULL.
 *                In case of collision, Last LETTERs will be run over.
 *                This Function Assumes that Printer is at the beginning
 *                of a new line.
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_DataSum(long data,                       /*  Data to print */
                      char *buf);                      /*  Text to print */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_LDate
 *
 * DESCRIPTION:   Prints long number as a date.
 *
 * RETURN:        None
 *
 * NOTES:         The printing format will be dd/mm/yy.
 *                the input format is : yymmdd.
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_LDate(long data); /* data is the date to be printed : yymmdd */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Line
 *
 * DESCRIPTION:   Prints a line of '-'
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Line(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Long
 *
 * DESCRIPTION:   Prints a long integer
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Long(long data); /* data represents the long number to print */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_LongDate
 *
 * DESCRIPTION:   Prints a long integer date.
 *
 * RETURN:        None
 *
 * NOTES:         Formats : data - ddmmyy
 *		            printing format : dd/mm/yy
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_LongDate(long data); /* data represents the date to print */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_LongDateCr
 *
 * DESCRIPTION:   Prints a long integer date, justified to the right, with
 *		  line feed.
 *
 * RETURN:        None
 *
 * NOTES:         Formats : data - ddmmyy
 *		            printing format : dd/mm/yy
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_LongDateCr(long data); /* data represents the date to print */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_Sum
 *
 * DESCRIPTION:   Prints long integered amount at a sum's format <num>.<xx>
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_Sum(long data);  /* data represents the number to print */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_SumCr
 *
 * DESCRIPTION:   Prints long integered amount at a sum's format <num>.<xx>
 *                justified to the right with a LineFeed.
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_SumCr(long data);  /* data represents the number to print */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_WaitForPrinting
 *
 * DESCRIPTION:   Suspends execution (foreground) till printing has come
 *                to an end.
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void PrntUtil_WaitForPrinting(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: PrntUtil_BufAsciiHex(byte *buf,usint buf_size)
 *
 * DESCRIPTION:   Prints a buffer in ASCII and in HEX (like displaying
 *                a file in NORTON utilities).  Ex:
 *
 *                HEX:             ASCII:
 *                31 32 33 34 35   12345
 *
 * RETURN:        TRUE - ok, FALSE -User Break.
 *
 * NOTES:         Maybe in the future this function should be in a util
 *                module.
 *
 * ------------------------------------------------------------------------ */

boolean PrntUtil_BufAsciiHex(byte *buf,usint buf_size);

#ifdef __NOS__
  #include prntutil_nos
#endif

#endif