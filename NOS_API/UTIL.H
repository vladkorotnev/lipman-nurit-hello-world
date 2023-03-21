/****************************************************************************
 *                                                                          *
 * FILE NAME:   util.h                                                      *
 *                                                                          *
 * MODULE NAME: util.                                                       *
 *                                                                          *
 * PROGRAMMER:  Shmuel Meymann (Additionals & Modifications by Ofir.E).     *
 *                                                                          *
 * DESCRIPTION: 68XXX projects general utils                                *
 *                                                                          *
 * REVISION:    01.00 12/04/94.                                             *
 *                                                                          *
 *              01.15 04/11/94                                              *
 *                                                                          *
 *		  Functions which aren't 68000 general utilities were       *
 *                moved to other modules.                                   *
 *                                                                          *
 ****************************************************************************/

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

/* void */

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/


           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_AsciiToBcd
 *
 * DESCRIPTION:   Collapses ASCII syntaxed variables to BCD form.
 *
 * RETURN:        None
 *
 * NOTES:         Illegal values will be concidered as zeros.
 *
 * ------------------------------------------------------------------------ */

void Util_AsciiToBcd(char *in,    /* Input buffer = number in ascii form */
                  byte *out,   /* Output buffer = number in BCD form  */
                  int length); /* length = length of source buffer    */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_BcdToAscii
 *
 * DESCRIPTION:   Expands BCD code densed data to ASCII.
 *
 * RETURN:        None
 *
 * NOTES:         Illegal values will be concidered as zeros.
 *
 * ------------------------------------------------------------------------ */

void Util_BcdToAscii(byte *in,    /* Input buffer - in BCD    */
                  char *out,   /* Output buffer - in ASCII */
                  int length); /* Length - length of Input buffer */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_AddTime
 *
 * DESCRIPTION:   Adds two variables of time type, (eg. 1:50 + 3:20 =...)
 *
 * RETURN:        None
 *
 * NOTES:         Illegal values will be concidered as zeros.
 *                Illegal time (eg. : 26:00) will be modulated
 *
 * ------------------------------------------------------------------------ */

void Util_AddTime(char *time1,   /*    First time var  (ascii array : hhmm) */
              char *time2,   /*  + Second time var (ascii array : hhmm) */
              char *time0);  /*  = Result time     (ascii array : hhmm) */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_BufCompare
 *
 * DESCRIPTION:   Compares 2 buffers byte-wise. (as if they were numbers)
 *
 * RETURN:        1  => first  >  second
 *                -1 => second <  first
 *                0  => first  =  second
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

int Util_BufCompare(byte *first,     /* First string to compare  */
            byte *second,    /* Second string to compare */
            int length);     /* Maximal length           */
            /* P. N. : compare */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_IToA
 *
 * DESCRIPTION:   Converts an integer to string with sending a "0".
 *
 * RETURN:        None
 *
 * NOTES:         In case of length limit, the least significant digits
 *                Will be deleted.
 *
 * ------------------------------------------------------------------------ */

void Util_IToA(int in,      /* Input variable */
            char *out,   /* Output string  */
            int length); /* Maximum length */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_LToA
 *
 * DESCRIPTION:   Converts a long integer to string with sending a "0".
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void Util_LToA(long in,     /* Input long integer */
            char *out,   /* Output string      */
            int length); /* Maximum length     */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_IncrementDate
 *
 * DESCRIPTION:   Increments a date by one day
 *
 * RETURN:        Incremented date.
 *
 * NOTES:         Both input and output date are given as follows :
 *                long date0 = yyyymmddÄÄ day
 *                    year ÄÄÄÄÄÄÄÙÀÄÄÄÄ- month
 *
 * ------------------------------------------------------------------------ */

long Util_IncrementDate(long date0); /* date0 is the input date */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_MemCopy
 *
 * DESCRIPTION:   Copies a memory block to another landscape.
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void Util_MemCopy(byte *from,     /* Domain of copy */
              byte   *to,     /* Range of copy  */
              int length);    /* Length of buffer to move */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_MemFill
 *
 * DESCRIPTION:   Fills a memory buffer with constant value
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void Util_MemFill(byte *from,  /* The buffer to be filled */
              byte   val,  /* Value to dump to buffer */
              int length); /* How many cells to fill? */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_SumToStr
 *
 * DESCRIPTION:   Converts a long integer to sum format (... XXXX.XX).
 *
 * RETURN:        String size.
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

int Util_SumToStr(long data,  /* Data to convert */
                  char *buf); /* Output buffer   */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_UlintToStr
 *
 * DESCRIPTION:   Translates unsigned long integer to string.
 *
 * RETURN:        None
 *
 * NOTES:         None
 *
 * ------------------------------------------------------------------------ */

void Util_UlintToStr(ulint *ul, char *st); /* ul - ulint => st - string */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_DateToLong
 *
 * DESCRIPTION:   Make a unsigned long int out of date formed : MMDDYY
 *
 * RETURN:        a long integer formed YYMMDD.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

ulint Util_DateToLong (char *date);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_LongToDate
 *
 * DESCRIPTION: Turns Long Integer into a Date String with or without slashes
 *              in the following form : MMDDYY or MM/DD/YY.
 *
 * RETURN:      New Date String inside 'DateStr'.
 *              American Date.
 *
 * NOTES:         MMDDYY or MM/DD/YY
 *
 * ------------------------------------------------------------------------ */
void Util_LongToDate (char *DateStr, ulint date, boolean WithSlashes);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_ShortToTime
 *
 * DESCRIPTION:  Get Time in Format HHMM as short integer.
 *
 *
 * RETURN:       Time Format String inside 'RetStr'.
 *
 *
 * NOTES:         output string format : HHMMSS.
 *
 * ------------------------------------------------------------------------ */
void Util_ShortToTime (char *RetStr, sint time);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_AccountCompress
 *
 * DESCRIPTION:   Compresses Account Number into BCD Code, placing an F
 *                (15 decimal) at the end of the Converted BCD String inorder
 *                to know (when Decompressing) where does the string end.
 *                currently used to compress Account Numbers.
 *
 * RETURN:        Translated BCD String in Dest.
 *
 * NOTES:         Max_Len is the Maximum Length allowed for Src.
 *
 * ------------------------------------------------------------------------ */

void Util_AccountCompress (byte *Dest, char *Src, byte Max_Len);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_AccountDecompress
 *
 * DESCRIPTION:   DeCompresses Account Number, by translating the BCD code
 *                Into Ascii (NULL Terminated String) using the F to know
 *                where does the BCD String End (see Previous Function).
 *
 * RETURN:        New Ascii String in Dest.
 *
 * NOTES:         Max_Len is the Maximum Length allowed for Dest.
 *
 * ------------------------------------------------------------------------ */
void Util_AccountDecompress (char *Dest, byte *Src, byte Max_Len);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME:   Util_JulianDate
 *
 * DESCRIPTION:     Converts a date (YYYYMMDD) into Julian number
 *
 * PARAMETERS:      long date    -  date to convert
 *
 * RETURN:          int          -  Julian of date
 *
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
int Util_JulianDate(long date);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Util_StrNLen
 *
 * DESCRIPTION:   Return number of characters in String, excluding the 
 *                terminal NULL.
 *
 * RETURN:        length of String (or MaxLength, if smaller).
 *
 * NOTES:         If String is longer than MaxLength, return MaxLength.
 *
 * ------------------------------------------------------------------------ */
ulint Util_StrNLen ( const char *String,
                     ulint       MaxLength );


           /*=========================================*
            *  INLINE FUNCTIONS IMPLEMENTED BY MACROS *
            *=========================================*/
/* void */
