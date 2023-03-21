/****************************************************************************
 *                                                                          *
 * FILE NAME:   LINK.H                                                      *
 *                                                                          *
 * MODULE NAME: LINK                                                        *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati (Previous by: ARIE GLEIZER & EPHR_CH)           *
 *                                                                          *
 * DESCRIPTION: LINK LAYER (including framing)                              *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    04.10 20/08/95.                                             *
 *                                                                          *
 ****************************************************************************/

	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/

	  /*==========================================*
	   *         D E F I N I T I O N S            *
	   *==========================================*/


/* RETURN VALUES FROM SEND/RECEIVE FUNCTIONS: */
/* SEND OK: */
#define OK_SENT 1
/* RECEIVE/SEND ERRORS : */
#define ERROR_SEND            -1  /* SEND ERROR */
#define ERROR_TIME_OUT        -2  /* RECEIVE ERROR */
#define ERROR_PACKET_TOO_BIG  -3  /* Received data Excceeds user buffer */
                                  /* or User Transmitted data excceeds */
                                  /* link buffer. */

/* WAIT NOT FINISHED : HAS NOT FINISHED YET RECEIVING */
#define WAIT_NOT_FINISHED 0
/* ACKNOLEDGE RECEIVED : */
#define ACKNOLEDGE_RECEIVED 1
/* DATA RECEIVED : return_value>1 */



	   /*=========================================*
	    *   P U B L I C     F U N C T I O N S     *
	    *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Link_Init.
 *
 * DESCRIPTION:   Initialization/reset specified port for link level.
 *
 *                port : 		1...Number of ports.
 *		  time_out_per_retry:	Time to wait (in miliseconds)
 *					between retrys.
 *
 * RETURN:        Returns : OK		for success.
 *			    FAILURE	for error (if hasn't been created
 *					yet).
 *
 * NOTES:         Must be called each time you wish to start communication.
 *
 * ------------------------------------------------------------------------ */
sint Link_Init(sint port,usint time_out_per_retry);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Link_Send.
 *
 * DESCRIPTION:   Sends a buffer.
 *
 *                port : 		1...Number of ports.
 *                snd_buf:		User's buffer to be sent.
 *                snd_len:		length of user's buffer.
 *
 * RETURN:        Returns : 	OK_SENT.
 *			    	ERROR_SEND.
 *                              ERROR_PACKET_TOO_BIG
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Link_Send (sint port,BYTE *snd_buf,sint snd_len );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Link_Receive.
 *
 * DESCRIPTION:   Receives a buffer.
 *
 *                port : 		1...Number of ports.
 *                rcv_buf:		User's buffer to write in.
 *                rcv_len:		length of user's buffer.
 *
 * RETURN:      On success :
 *			returns received 	buffer size+1 !
 *
 *			or for ACKNOLEDGE       ACKNOLEDGE_RECEIVED (1)
 *
 *              On Wait has not finished yet:  	WAIT_NOT_FINISHED (0)
 *
 *		On error :      	      	ERROR_TIME_OUT or
 *						ERROR_SEND
 *                                              ERROR_PACKET_TOO_BIG
 *
 * NOTES:       Function should be called in a loop that continue until
 *		return value is not WAIT_NOT_FINISHED.
 * ------------------------------------------------------------------------ */
sint Link_Receive (sint port,BYTE *rcv_buf,sint rcv_len);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Link_SendAck.
 *
 * DESCRIPTION:   Send Acknoledge Frame (frame without data).
 *
 *                port :         	1...Number of ports.
 *
 * RETURN:        ACKNOLEDGE SENT or
 *                ERROR_SEND.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Link_SendAck (sint	port);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Link_GetCrc16Table.
 *
 * DESCRIPTION:   Returns a pointer to the CRC16 table.
 *
 * RETURN:        ^.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
usint *Link_GetCrc16Table(void);

#ifdef __NOS__
  #include link_nos
#endif
