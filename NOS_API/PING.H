/****************************************************************************
 *                                                                          *
 * FILE NAME:   PING.H                                                      *
 *                                                                          *
 * MODULE NAME: PING                                                        *
 *                                                                          *
 * PROGRAMMER:  Barak.                                                      *
 *                                                                          *
 * DESCRIPTION: Ping Utility.                                               *
 *                                                                          *
 *              Base on Track Ping Utility                                  *
 *                                                                          *
 * REVISION:    01.00 28/06/2004                                            *
 *                                                                          *
 ****************************************************************************/
#ifndef __PING_H__
  #define __PING_H__

	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/
/*
 * PING User API
 */

/*
 * Open a PING ICMP socket, start sending PING requests to RemoteHostName,
 * and keep sending PING requests at every PingInterval seconds (which
 * defaults to 1 second if set to zero). 
 * Size of the ping request data is PingDataLength (which defaults to 56
 * if set to zero).
 * To stop the system from sending PING ICMP echo requests, the user
 * need to call Ping_Close(SocketDesc);
 * Ping_Open returns a valid socket descriptor upon success,
 * PING_FAIL otherwise.
 */

	  /*==========================================*
	   *             I N C L U D E S              *
	   *==========================================*/

#include ping_def

	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/

#define PING_OK    1
#define PING_FAIL -1

      /*=========================================*
       *   P U B L I C     F U N C T I O N S     *
       *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Ping_Open
 *
 * DESCRIPTION:   Open Ping utility
 *
 * PARAMETERS:    RemoteHostName - character array containing a dotted decimal IP address 
 *                                 representation of the remote host.
 *                                 (e.g "192.168.5.20")  
 *                PingInterval   - the interval in seconds between PING echo requests.  
 *                                 If set to zero, defaults to 1 second.
 *                                  
 *                PingDataLength - the user data length of the PING echo requests.
 *                                 If set to zero, defaults to 56 bytes. If set to a value between 1,
 *                                 and 3, defaults to 4 bytes.   
 * RETURN:        If successful, returns a socket descriptor. ( >= 0 ) else error.
 *
 * NOTES:         Before using this function Physical layer must first be open using 
 *                ProtMngr Connection functions.
 *
 * ------------------------------------------------------------------------ */
sint Ping_Open (char *RemoteHostName,ulint PingInterval,ulint PingDataLength);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Ping_GetStatistics
 *
 * DESCRIPTION:   Get Ping Statistics 
 *
 * PARAMETERS:    SocketDesc - a socket descriptor return value from Ping_OpenStart
 *                InfoPtr    - Pointer To PingInfo structure. (defined in ping.def)  
 * 
 * RETURN:        If successful, PING_OK else PING_FAIL.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Ping_GetStatistics ( sint  SocketDesc , PingInfo *InfoPtr );
                           

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Ping_Close
 *
 * DESCRIPTION:   Stop sending PING requests to RemoteHostName, and close SocketDesc.
 *
 * PARAMETERS:    SocketDesc - a socket descriptor return value from Ping_OpenStart
 *
 * RETURN:        If successful, PING_OK else PING_FAIL.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Ping_Close (sint SocketDesc);

#endif