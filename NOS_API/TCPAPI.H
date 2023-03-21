/****************************************************************************
 *                                                                          *
 * FILE NAME:   TCPAPI.H                                                    *
 * MODULE NAME: COM:TCP                                                     *
 * PROGRAMMER:  Arie Gleizer                                                *
 * DESCRIPTION: TCP application program interface               	    *
 * REVISION:    7/12/1999                                                   *
 ****************************************************************************/

#ifndef __TCPAPI_H
#define __TCPAPI_H

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

#ifndef _WindowsSw
  typedef int           SOCKET;
  #define INVALID_SOCKET  -1
#endif

/*=================================================================== */


#define TCPAPI_SUCCESS					 0
#define TCPAPI_ERROR					-1
#define TCPAPI_ABORTED					-2
#define TCPAPI_TIMEOUT                  -3
#define TCPAPI_NODATA					-4
#define TCPAPI_EMSGSIZE                 -5
#define TCPAPI_WAIT_FOR_OPEN            -6
#define TCPAPI_DISCONNECTED_PHYSICAL    -7



typedef enum
{
    TCP_protocol = 1,
    UDP_protocol = 2
}
    TCPAPI_protocol_t;

typedef enum
{
    TCPAPI_TM_TCP_SEL_ACK = 1,     /*Turn ON/OFF Selective Acknolwlegements (default ON)*/
    TCPAPI_TM_TCP_WND_SCALE,       /* Turn ON/OFF Big Window Scaling (default ON )*/
    TCPAPI_TM_TCP_TS,              /* Turn ON/OFF Time stamp (default ON) */
    TCPAPI_TM_TCP_DELAY_ACK,       /*Set the TCP delay ack time( default: 200ms). */
    TCPAPI_TCP_NODELAY,           /*set to non zero to disable Nagle algorithm (default: 0) */
    TCPAPI_SO_SNDBUF,             /*buffer size for output (Default 8192 bytes)*/
    TCPAPI_SO_RCVBUF,             /*buffer size for input (Default 8192 bytes)*/
    TCPAPI_TCP_SLOW_START,        /*enable slow start algorithm (rfc2001). (default enabled) */
    TCPAPI_SO_KEEPALIVE,          /*enable disable keep connection alive (default disabled)*/
    TCPAPI_TCP_KEEPALIVE,         /*idle time before start send probes (default 7200 sec), */
                                  /* time can not be set below the default value */
    TCPAPI_MAX_OPTIONS
}
    TCPAPI_SockOpt_t;
/*=================================================================== */

	   /*=========================================*
	    *        M I S C E L L A N E O U S        *
	    *=========================================*/



	   /*=========================================*
	    *   F U N C T I O N  P R O T O T Y P E S  *
	    *=========================================*/


/*########################################################################
FUNCTION NAME: TCPAPI_Open
DESCRIPTION  : Client side of TCP
RETURN       : Socket descriptor on success
               or INVALID_SOCKET  - 1 on connection error
               or TCPAPI_DISCONNECTED_PHYSICAL -7 if Line is disconnected
NOTES        :
########################################################################*/

SOCKET TCPAPI_Open( char *RemoteIP, usint PortId, TCPAPI_protocol_t );

/*########################################################################
FUNCTION NAME: TCPAPI_SetTimeout
DESCRIPTION  : Initialization of receive timeout
RETURN       :
NOTES        : If timeout is 0 the receive function will return only after
               data is received.
########################################################################*/

void TCPAPI_SetTimeout( lint to );

/*########################################################################
FUNCTION NAME: TCPAPI_Close
DESCRIPTION  : Close specified socket
RETURN       :
NOTES        :
########################################################################*/

void TCPAPI_Close( SOCKET sd );

/*########################################################################
FUNCTION NAME: TCPAPI_Send
DESCRIPTION  : Sending buffer on TCP
RETURN       : on success TCPAPI_SUCCESS
               on error   TCPAPI_ERROR
               on User abort TCPAPI_ABORTED
               or TCPAPI_DISCONNECTED_PHYSICAL -7 if Line is disconnected
NOTES        :
########################################################################*/
sint TCPAPI_Send( SOCKET sd, byte *data, usint datalen );

/*########################################################################
FUNCTION NAME: TCPAPI_Receive
DESCRIPTION  : Receive message
RETURN       : on success : TCPAPI_SUCCESS
               on error   : TCPAPI_ERROR
               on User abort : TCPAPI_ABORTED
               if time-out defined by TCPAPI_Timeout passed : TCPAPI_TIMEOUT
               TCPAPI_EMSGSIZE is return only on UDP socket when user buffer
               is to small to get the data.
               or TCPAPI_DISCONNECTED_PHYSICAL -7 if Line is disconnected

NOTES        : Timeout may be changed by TCPAPI_Timeout()
#######################################################################*/
sint TCPAPI_Receive( SOCKET sd, byte *data, usint *datalen );

/*########################################################################
FUNCTION NAME: TCPAPI_GetStatus
DESCRIPTION  : Returns status of socket
RETURN       : on success : TCPAPI_SUCCESS
               on error   : TCPAPI_ERROR
               or TCPAPI_DISCONNECTED_PHYSICAL -7 if Line is disconnected

               No data in socket: TCPAPI_NODATA
NOTES        :
########################################################################*/
sint TCPAPI_GetStatus( SOCKET sd );


/*########################################################################
FUNCTION NAME: TCPAPI_WaitForOpen
DESCRIPTION  : Server side of TCP
RETURN       : Socket descriptor on success or INVALID_SOCKET on error
               or TCPAPI_DISCONNECTED_PHYSICAL -7 if Line is disconnected
NOTES        :
########################################################################*/
SOCKET TCPAPI_WaitForOpen( char *LocalIP, usint PortId ,TCPAPI_protocol_t Protocol);

/*########################################################################
FUNCTION NAME: TCPAPI_EndWaitForOpen
DESCRIPTION  : Close listen socket  opened by TCPAPI_WaitForOpen
RETURN       :
NOTES        :
########################################################################*/
void  TCPAPI_EndWaitForOpen( char *LocalIP, usint PortId );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: TCPAPI_PreOpen
 *
 * DESCRIPTION:   Open socket and start waiting for connection
 *
 * PARAMETERS:    RemoteIP - Ip Address of remote server.
 *                PortId   - Port Number of remote server.
 *                TCPAPI_protocol_t - Ptotocol Type can be.
 *                                    TCP_protocol for TCP connection.
 *                                    UDP_protocol for UDP connection.
 *
 * RETURN:        >= 0 if OK , Socket descriptor
 *                on error INVALID_SOCKET
 *                or physical not connected TCPAPI_DISCONNECTED_PHYSICAL
 *
 * NOTES:         The Status of the Socket will be returned by TCPAPI_PreOpenStatus .
 *
 * ------------------------------------------------------------------------ */
SOCKET TCPAPI_PreOpen(char *RemoteIP, usint PortId, TCPAPI_protocol_t Protocol );
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: TCPAPI_PreOpenStatus
 *
 * DESCRIPTION:   Return the status of the socket that was opened in TCPAPI_PreOpen
 *
 * PARAMETERS:    sd - Socket Descriptor
 *                RemoteIP - Ip Address of remote server.
 *                PortId   - Port Number of remote server.
 *
 * RETURN:        Status of the connection:
 *                Socket connected TCPAPI_SUCCESS
 *                Socket error     TCPAPI_ERROR
 *                connect time out TCPAPI_TIMEOUT
 *                wait for connection TCPAPI_WAIT_FOR_OPEN
 *                physical not connected TCPAPI_DISCONNECTED_PHYSICAL
 *
 * NOTES:         return the status of the Socket That was opened by TCPAPI_PreOpen
 *
 * ------------------------------------------------------------------------ */
sint TCPAPI_PreOpenStatus( SOCKET sd, char *RemoteIP, usint PortId );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: TCPAPI_SetSockOpt
 *
 * DESCRIPTION:   change default value of socket option to the given value.
 *
 * PARAMETERS:    TCPAPI_SockOpt_t Option - the requested option to change.
 *                lint Value              - new value to set.
 *
 * RETURN:        TCPAPI_SUCCESS - paramters ok. option will be set while
 *                                 calling TCPAPI_Open()
 *                TCPAPI_ERROR -  parameter error (option or value).
 *
 * NOTES:         This function must be call right before calling TCPAPI_Open()
 *                it will set the options to the socket created in TCPAPI_Open().
 *                The socket returned from TCPAPI_Open() will have the requested
 *                options and default values will reset, when calling TCPAPI_Open()
 *                again, if TCPAPI_SetSockOpt() had not being called before, the
 *                returned socket will have default values.
 *
 * ------------------------------------------------------------------------ */
sint TCPAPI_SetSockOpt(SOCKET sd,TCPAPI_SockOpt_t Option, lint Value);
/* --------------------------------------------------------------------------
* FUNCTION NAME: TCPAPI_GetTimeout
* DESCRIPTION  : Get Current timeout
* RETURN       : ^.
* NOTES        :
 * ------------------------------------------------------------------------ */
lint TCPAPI_GetTimeout( void );

/*########################################################################
FUNCTION NAME: TCPAPI_End
DESCRIPTION  : Close listen socket
RETURN       :
NOTES        : For windows user only (can't be used on NURIT)
########################################################################*/
void TCPAPI_End( void );

#ifdef __NOS__
  #include TCPAPI_NOS
#endif

#endif
