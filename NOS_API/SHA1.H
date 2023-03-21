/****************************************************************************
 * FILE NAME:   SHA1.H
 * MODULE NAME: SHA-1 (Secure Hash Algorithm)
 * PROGRAMMER:  Fehmi Ozgun. (modifications)
 *
 * DESCRIPTION: SHA-1 algorithm implementation in C. Original version is part
 *              of GNUPG (a free replacement of PGP) libarary verion 1.0.6 by
 *              Free Software Foundation, Inc. (SHA1 File Revision: 1.17)
 *              Original version can be obtained from http://www.gnupg.org
 *
 * REVISION:    01.00   17/10/2001 - Fehmi Ozgun
 * HISTORY:     ver 01.01
 *                  Modified to get it an independent module
 *                  Company conventions for function prototypes have been applied.
 *              ver 01.02
 *                  Removed all the static variables
 *                  Removed all the references on standard libraries
 *                  Public function prototypes changed accordingly
 *
 * NOTES:       Test Vectors (from FIPS PUB 180-1) to verify implementation
 *              1- Input : "abc"
 *              Output : A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D
 *              2- Input : "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
 *              Output : 84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1
 *              2- Input : A million repetitions of 'a' - not applied (memory shortage)
 *              Output : 34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F
 *              More test vectors can be obtained from FIPS web site
 *
 *              Be aware that implementation is endian(byte order) dependant
 *              For little endian machines (such as Intel)
 *              remove "BIG_ENDIAN_HOST" directive from this file
 ****************************************************************************/

#ifndef __NOS_SHA1_H
#define __NOS_SHA1_H


          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

#define SHA1_DIGEST_SIZE      20  /* In bytes SHA-1 (ISO/IEC CD 10118-3) */
#define MAX_SHA1_SIZE        128  /* Size of user's buffer allocation    */


#ifdef _WindowsSw
#define SHA1_Open           NOS_SHA1_Open
#define SHA1_Write          NOS_SHA1_Write
#define SHA1_Final          NOS_SHA1_Final
#endif


          /*=========================================*
           *   F U N C T I O N  P R O T O T Y P E S  *
           *=========================================*/

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
 * FUNCTION NAME: NOS_SHA1_Open
 * DESCRIPTION:   Open calculation of digest (result of sha1-hash function)
 *                Initializes new context
 * PARAMETERS:    inhd  (in)  : SHA1 context to be initialized
 * NOTES:         - Use once at start of calculation
 *                - The size of inhd buffer must be at last MAX_SHA1_SIZE
 *                - Each Entity will be assigned a different Context
 *                  (Multiple Entities can perform SHA1 in parallel)
 ****************************************************************************/
void NOS_SHA1_Open( void *inhd );

/****************************************************************************
 * FUNCTION NAME:   NOS_SHA1_Write
 * DESCRIPTION:     Update the message digest with given buffer
 * PARAMETERS:      inhd  (in) : SHA1 context
 *                  inbuf (in) : Pointer to buffer to Hash
 *                  inlen (in) : Buffer length
 * NOTES:           Data buffer (inbuf) must be 64 bytes length or more. 
 *                  If less than 64 bytes, buffer must be padded with zeros.
 ****************************************************************************/
void NOS_SHA1_Write( void *inhd,  byte *inbuf,   ulint inlen );

/****************************************************************************
 * FUNCTION NAME: NOS_SHA1_Final
 * DESCRIPTION:   Ends calculation of digest (result of sha1-hash function)
 *                and retrieve result.
 * PARAMETERS:    inhd    (in)  : SHA1 context
 *                digest  (out) : Result of hash calculation
 * NOTES:         - Use once at end of calculation.
 *                - The size of digest is SHA1_DIGEST_SIZE = 20 bytes exactly
 ****************************************************************************/
void NOS_SHA1_Final( void *inhd,  byte *digest );


#ifdef __cplusplus
}
#endif

#endif