/****************************************************************************
 *                                                                          *
 * FILE NAME:   scanner.h                                                   *
 *                                                                          *
 * MODULE NAME: Scanner.                                                    *
 *                                                                          *
 * PROGRAMMER:  Shmuel Meymann.                                             *
 *                                                                          *
 * DESCRIPTION: Timing interrupt usage manager and initializer.             *
 *                                                                          *
 * REVISION:    01.01 31/01/94.                                             *
 *                                                                          *
 * HISTORY:     <Version history>.                                          *
 *                                                                          *
 ****************************************************************************/
#ifndef _SCANNER_H_
  #define _SCANNER_H_
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
 * FUNCTION NAME: Scan_MillSec.
 *
 * DESCRIPTION:   Shows the millisecond counter.
 *
 * RETURN:        none.
 *
 * NOTES:         The millisecond counter ticks upwards every 4mSec
 *                it increases the counter each time by 4 and hence,
 *                you shold not take for granted comparing with this
 *                value.
 *
 * ------------------------------------------------------------------------ */
ulint Scan_MillSec(void);

#ifdef __NOS__
  #include scanner_nos
#endif

#endif


	   /*=========================================*
	    *  INLINE FUNCTIONS IMPLEMENTED BY MACROS *
	    *=========================================*/
/* void */

           /*=========================================*
            *           E P I L O G                   *
            *=========================================*/
/* void */
