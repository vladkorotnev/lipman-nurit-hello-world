/****************************************************************************
 * FILE NAME:   dns.H
 * MODULE NAME: dns
 * PROGRAMMER:  Gilad Hirsch
 * DESCRIPTION: implement dns resolving over udp. The implementation
 *              is using the tcpapi functions.
 * REVISION:
 ****************************************************************************/

#ifndef __dns_H
#define __dns_H
          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/


#define DNS_SUCCESS              1
#define DNS_ERROR                0
#define DNS_PACKING_ERROR       -1
#define DNS_SEND_ERROR          -2
#define DNS_RECEIVE_ERROR       -3
#define DNS_OPEN_ERROR          -4
#define DNS_ENTITY_ERROR        -5
#define DNS_WAIT_NOT_FINISH     -6
#define DNS_TIME_OUT            -7


           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/


/****************************************************************************
 * FUNCTION NAME: DNS_Resolver
 * DESCRIPTION:   Resolve host name to ip using dns request.
 *                DnsServerIp can be set to one of the following:
 *                1. A Dns server Ip (if known).
 *                2. The Destination Host name (e.g. "HOST1") - in this case it will
 *                   use the dns servers received from the Isp connection (PPP or DHCP).
 *                3. Null - In this case it will take the Dns server from the current
 *                   connection.
 * RETURN:        DNS_SUCCESS if DNS successed.
 *                DNS_SEND_ERROR     Send Error
 *                DNS_RECEIVE_ERROR  Receive Error
 *                DNS_OPEN_ERROR     Open Socket Error
 *                DNS_PACKING_ERROR  Worng parameters.
 *                DNS_ERROR          if DNS did not successed.
 * NOTES:         none.
 ****************************************************************************/
sint DNS_Resolver(char*  HostName, char* HostIp, char* DnsServerIp);

/****************************************************************************
 * FUNCTION NAME: DNS_ResolverAsync
 * DESCRIPTION:   Asynchronously Resolve host name to ip using dns request
 * RETURN:        > 0 Handle for the Session.
 *                DNS_SEND_ERROR     Send Error
 *                DNS_RECEIVE_ERROR  Receive Error
 *                DNS_OPEN_ERROR     Open Socket Error
 *                DNS_PACKING_ERROR  Worng parameters.
 *                DNS_ERROR          if DNS did not successed.
 * NOTES:         The resualt for the query should be later get by DNS_GetResult.
 ****************************************************************************/
sint DNS_ResolverAsync(char*  HostName, char* DnsServerIp , ulint TimeOut);
/****************************************************************************
 * FUNCTION NAME: DNS_GetResult
 * DESCRIPTION:   Get Result of the DNS Query
 *
 * RETURN:
 *
 * NOTES:         none.
 ****************************************************************************/
sint DNS_GetResult( sint Handle , char* HostIp);


#ifdef __NOS__
  #include dns_nos
#endif

#endif
