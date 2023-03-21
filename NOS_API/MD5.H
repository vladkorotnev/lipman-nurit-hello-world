/****************************************************************************
 *                                                                          *
 * FILE NAME:   MD5.C                                                       *
 *                                                                          *
 * MODULE NAME: MD5                                                         *
 *                                                                          *
 * PROGRAMMER:  Philippe Berrebi                                            *
 *                                                                          *
 * DESCRIPTION: Manages the MD5 functionality.                              *
 *              MD = Message Digest                                         *
 *                                                                          *
 * REVISION:    01_00                                                       *
 *                                                                          *
 ****************************************************************************/

#ifndef _NOS_MD5_H_
#define _NOS_MD5_H_

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

#define MD5_DIGEST_SIZE     16  /* Size in bytes of Digest  user's buffer allocation */
#define MD5_CONTEXT_SIZE    80  /* Size in bytes of Context user's buffer allocation */
#define MD5_MAX_DATA_SIZE   48  /* Maximum size in bytes of Data user's buffer       */


	   /*=========================================*
	    *   P U B L I C     F U N C T I O N S     *
	    *=========================================*/

/****************************************************************************
 * FUNCTION NAME: NOS_MD5_Open
 * DESCRIPTION:   Open calculation of digest (result of hash function)
 *                Initializes new context
 * INPUT:         pContext  - Pointer to MD5 context to be initialized
 * NOTES:         - Use once at start of calculation
 *                - The size of pContext buffer must be at least MD5_CONTEXT_SIZE
 *                - Each Entity will be assigned a different Context
 *                  (Multiple Entities can perform MD5 in parallel)
 ****************************************************************************/
void NOS_MD5_Open( void *pContext );

/****************************************************************************
 * FUNCTION NAME: NOS_MD5_Write
 * DESCRIPTION:   Update the message digest with given buffer
 * INPUT:         pContext  - Pointer to MD5 context 
 *                pInBuf    - Pointer to buffer to Hash
 *                InLen     - Input Buffer length
 * NOTES:         Data buffer must be MD5_MAX_DATA_SIZE = 48 bytes length. 
 *                If less than MD5_MAX_DATA_SIZE bytes, buffer must be padded with zeros.
 ****************************************************************************/
void NOS_MD5_Write( void *pContext,  byte *pInBuf,   int InLen );

/****************************************************************************
 * FUNCTION NAME: NOS_MD5_Final
 * DESCRIPTION:   Ends calculation of digest (result of MD5-hash function)
 *                and retrieve result.
 * INPUT:         pContext  - Pointer to MD5 context 
 * OUTPUT:        pDigest   - Pointer to result of hash calculation
 * NOTES:         - Use once at end of calculation.
 *                - The size of digest is MD5_DIGEST_SIZE = 16 bytes exactly
 ****************************************************************************/
void NOS_MD5_Final( void *pContext,  byte *pDigest );


#endif
