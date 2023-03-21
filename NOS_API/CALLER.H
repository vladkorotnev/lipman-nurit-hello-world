/****************************************************************************
 *                                                                          *
 * FILE NAME:   caller.h                                                    *
 *                                                                          *
 * MODULE NAME: CALLER                                                      *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati.                                                *
 *                                                                          *
 * DESCRIPTION: Connecting Services for RS/MODEM ports.                     *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01_00 07/09/95                                              *
 *                                                                          *
 ****************************************************************************/
#ifndef __CALLER_H__
  #define __CALLER_H__


	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/

	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/

#define MODEM_V32BIS_ONLY       14148       /* Allow V.32bis only (4800-14400bps) */

           /*=========================================*
            *   P U B L I C     F U N C T I O N S     *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Caller_GetLastConnectStatus.
 *
 * DESCRIPTION:   Returns the Connection status of modem for last call
 *                of modem.
 *
 * RETURN:        modem status by MODEM.H definition.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
sint Caller_GetLastConnectStatus(void);
#endif

#ifdef __NOS__
  #include caller_nos
#endif
