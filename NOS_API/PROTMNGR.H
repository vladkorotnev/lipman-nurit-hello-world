/****************************************************************************
 * FILE NAME:   protmngr.H
 * MODULE NAME: protmngr
 * PROGRAMMER:  CL
 * DESCRIPTION: TCP/IP protocol manager (public function prototypes)
 * REVISION:    01.00 25/01/00 15:52
 ****************************************************************************/

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
#ifndef __protmngr_H
  #define __protmngr_H

/** The Protocol manager functions explanation:
 *  There are two groups of functions:
 *  I.( ProtMngr_Connect, ProtMngr_ConnectISP,  ProtMngr_DisconnectISP )
 *    works with the ISP entity (Internet Service Provider). These functions
 *    connects and disconnects unconditionally, i.e. in case if the
 *    application trying to connect to an ISP, when an another ISP already
 *    has been connected, the previous connection will be aborted.
 *
 *  II.( ProtMngr_ConnectDestination, ProtMngr_DisconnectDestination )
 *    works with the InetDest entity, which is internet-connected computer
 *    (its IP addr) and the refernce to an ISP to connect through.
 *    It is possible to make multiple calls of ProtMngr_ConnectDestination
 *    without terminating the physical and link connection to an ISP, unless
 *    all these different InetDest refers to the same ISP.
 *    The call of the ProtMngr_DisconnectDestination doesn't necessary
 *    terminates the connection to an ISP, it depends of how many times
 *    ProtMngr_ConnectDestination was called without terminating the
 *    connection, i.e. how many destinations are still working through this
 *    ISP (each call of ProtMngr_DisconnectDestination reduces this counter).
 *
 * In the case of following scenario:
 *   1.ProtMngr_Connect (or ProtMngr_ConnectISP)
 *   2.ProtMngr_ConnectDestination
 *    ...
 *   N.ProtMngr_DisconnectDestination
 * N+1.ProtMngr_DisconnectISP ,

 * the ProtMngr_DisconnectDestination never disconnects and explicite call
 * of ProtMngr_DisconnectISP is required.
 */

          /*==========================================*
           *           I N C L U D E S                *
           *==========================================*/

#include tcpapi_h
#include protmngr_def


          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/****************************************************************************
 * FUNCTION NAME: ProtMngr_ConnectDestination
 * DESCRIPTION:   looks into DestHost table and searches the ISP to connect
 *                to. If the ISP is already connected, does nothing; if not,
 *                calls ProtMngr_ConnectISP.
 * RETURN:        See 'ISP_return_codes' for description of return values
 *                also copies Host IP address to the caller's 'HostIpAddr'
 *                pointer
 * NOTES:         none.
 ****************************************************************************/
lint  ProtMngr_ConnectDestination(char  *DestHost,
                                char  *LoggingMessage,
                                char  *HostIpAddr);

/****************************************************************************
 * FUNCTION NAME: ProtMngr_ConnectDestinationBkgr
 * DESCRIPTION:   Connect to Host/ISP in background. start the connect proccess,
 *                when needed you can be update with the connection status by
 *                calling ProtMngr_GetStatus(). to bring proccess to foreground
 *                call ProtMngr_ConnectForegrnd.
 * RETURN:        See ISP_return_codes for description of return values
 *                also copies Host IP address to the caller's 'HostIpAddr'
 *                pointer
 * NOTES:         none.
 ****************************************************************************/
lint ProtMngr_ConnectDestinationBkgr(char  *DestHost, char  *LoggingMessage, char  *HostIpAddr,
                                     usint PortId, TCPAPI_protocol_t Protocol);

/****************************************************************************
 * FUNCTION NAME: ProtMngr_ConnectDestination2
 * DESCRIPTION:   Connect TCP/IP Host using parameter from user or DestHost table
 * RETURN:        See ISP_return_codes for description of return values
 *                also copies Host IP address to the caller's 'HostIpAddr'
 *                pointer
 * NOTES:         none.
 ****************************************************************************/
lint ProtMngr_ConnectDestination2(char *DestHost,char *LoggingMessage,char  *HostIp,ConnectParams *Connect,boolean Blocking);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ProtMngr_GetStatus
 * DESCRIPTION:   check machine state and line status.
 * RETURN:        ISP_NOT_CONNECTED - an error occured isp had disconnected.
 *                ISP_OK            - connect proccess complete successfully.
 *                ISP_INPROGRESS    - connect proccess in progress.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
lint ProtMngr_GetStatus(char  *DestHost);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ProtMngr_ConnectForegrnd
 * DESCRIPTION:   Bring the connection proccess to foreground, return to user
 *                when finished.
 * RETURN:        ISP_OK             - connection established.
 *                ISP_NOT_CONNECTED  - connection fail.
 *                ISP_USER_BREAK     - user break.
 *
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
lint ProtMngr_ConnectForegrnd(char  *DestHost,char  *HostIpAddr);

/****************************************************************************
 * FUNCTION NAME: ProtMngr_DisconnectDestination
 * DESCRIPTION:   checks number of dest. connected through the same ISP.
 *                if there is only one ('DestHost'), disconnects physically.
 *                Otherwise marks this DestHost as unactive (it can be
 *                reached later by ProtMngr_ConnectDestination(...) ).
 * RETURN:        none
 * NOTES:         none.
 ****************************************************************************/
void ProtMngr_DisconnectDestination(char  *DestHost);

/****************************************************************************
 * FUNCTION NAME: ProtMngr_GetInterfaceIPAdr
 * DESCRIPTION:   Gets some connection parameters: IP adress, gateway IP adress,
 *                Netmask and primary+secondary DNS IP form ISP and from Block.
 *                if DestHost was not found it will return the current
 *                connection parameters.
 *
 * RETURN:        ISP_OK
 *                ISP_NOT_CONNECTED
 *                ISP_NOT_FOUND
 *
 * NOTES:         none
 ****************************************************************************/
sint ProtMngr_GetInterfaceIPAdr(char* DestHost, InterfaceIPAdr* Interface_prm);

/****************************************************************************
 * FUNCTION NAME: ProtMngr_SetOption
 *
 * DESCRIPTION:   change default value of a Protmngr option to the given value.
 *                Protmngr options described in Protmngr.def
 *
 * PARAMETERS:    ProtMngr_Option_t Option - the requested option to change.
 *                lint Value              - new value to set.
 *
 * RETURN:         - PROTMNGR_OK. option will be set from the next connection
 *
 *                 -  PROTMNGR_FAIL (option or value are wrong).
 *
 * NOTES:         This function must be call before calling Protmngr_ConectDestination/2/Bkgr
 *                function.
 ****************************************************************************/
char ProtMngr_SetOption(ProtMngr_Option_t Option, lint value);

/****************************************************************************
 * FUNCTION NAME: ProtMngr_GetOption
 *
 * DESCRIPTION:   return option value
 *
 *
 * PARAMETERS:    ProtMngr_Option_t Option - the requested option .
 *                lint* Value              - pointer to the value.
 * RETURN:
 ****************************************************************************/
char ProtMngr_GetOption(ProtMngr_Option_t Option, lint* value);





           /*=========================================*
            *                E P I L O G              *
            *=========================================*/
  #ifdef __NOS__ /*include the NOS-only functions */
    #include protmngr_nos
  #endif

#endif /* #ifndef __protmngr_H */


