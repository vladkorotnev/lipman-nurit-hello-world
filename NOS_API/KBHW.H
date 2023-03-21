/****************************************************************************
 *                                                                          *
 * FILE NAME:   Kbhw.h                                                      *
 *                                                                          *
 * MODULE NAME: Kbhw.                                                       *
 *                                                                          *
 * PROGRAMMER:  Oren Sokoler                                                *
 *                                                                          *
 * DESCRIPTION: Hardware Keyboard, card scanner, and display managing card  *
 *              driver.                                                     *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01.00 02/04/98.                                             *
 *                                                                          *
 * HISTORY:     <Version history>.                                          *
 *                                                                          *
 ****************************************************************************/
#ifndef __KBHW_85_H
#define  __KBHW_85_H


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




#define NO_OF_DISPLAYS      1       /* LCD Devices */
#define    DSPL1            1
#define	   DSPL2            2


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
 * FUNCTION NAME: Kbhw_BuzzerPulse.
 *
 * DESCRIPTION:   Launches a signal to make buzzer beep for a given
 *                interval, an then, hush.
 *
 * RETURN:        none.
 *
 * NOTES:         interval is in mSec, and has to be in 100's products
 *                or else, it would be trucated to the closest lower one.
 *
 * ------------------------------------------------------------------------ */

void Kbhw_BuzzerPulse(usint interval);/* interval î {interval ö 100 î N} */

#ifdef __NOS__
  #include kbhw_nos
#endif

#endif
