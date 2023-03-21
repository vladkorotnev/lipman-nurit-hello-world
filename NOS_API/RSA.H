/****************************************************************************
 * FILE NAME:   RSA.H
 * MODULE NAME: RSA (Rivert-Shamir-Adleman  Algorithm)
 * PROGRAMMER:  Fehmi Ozgun. (modifications)
 *
 * DESCRIPTION:
 *
 * REVISION:    01.00   17/10/2001 - Fehmi Ozgun
 * REVISION:    01.01   10/08/2002 - Yshaiahu
 * REVISION:    01.10   10/09/2002 - Yshaiahu
 * REVISION:    01.11   30/09/2002 - Yshaiahu
 * REVISION:    01.12   05/10/2002 - Yshaiahu
 * REVISION:    01.13   26/11/2002 - Yshaiahu
 * HISTORY:     Modified to get it an independent module
 *     01.10    Company conventions for function prototypes have been applied.
 *              function prototypes changed.
 *     01.11    Function prototypes changed.
 *     01.12    'bits' field in KEY's structures are renamed to KeyLengh
 *     01.13    The definition of UnSign(...) function goes from rsa.def into
 *              rsaprv.h 
 *     01.14    Removed all the static variables
 *              Removed all the references on standard linraries
 *
 ****************************************************************************/

#ifndef __NOS_RSA_H
#define __NOS_RSA_H

          /*=========================================*
           *            I N C L U D E S              *
           *=========================================*/

#ifdef rsa_def
  #include rsa_def
#endif

#ifdef _WindowsSw
#define RSA_CalculateRsa	NOS_RSA_UnSign
#define RSA_UnSign		NOS_RSA_UnSign
#endif



          /*=========================================*
           *   F U N C T I O N  P R O T O T Y P E S  *
           *=========================================*/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
  FUNCTION NAME: NOS_RSA_CalculateRsa
  DESCRIPTION:   Performs RSA on data, using Public Key
  PARAMETERS:    output (out)  : Pointer to encrypted data
                 outputLen(out): Length for output data - Sould be the same as
                                 input data buffer length
                 input(in)     : Pointer to buffer to be encrypted
                 inputLen(in)  : Input buffer length
                 publicKey     : Public key pair - see rsa.def
  RETURN:        TRUE          Operation completed
                 FALSE         Fatal Error
 ****************************************************************************/
byte NOS_RSA_CalculateRsa(  byte             *output, 
                            usint            *outputLen,
                            byte             *input,  
                            usint             inputLen,
                            RSA_PUBLIC_KEY   *publicKey      );

/****************************************************************************
  FUNCTION NAME: NOS_RSA_UnSign
  DESCRIPTION:   Recovers  signed data using Public Key
  PARAMETERS:    HashResult (out)  : Pointer to recovered data
                 HashResultLen(out): Length for output data - Sould be the same as
                                     input data buffer length
                 Signature(in)     : Pointer to buffer to be Unsigned
                 SignatureLen(in)  : Input Signature buffer length
                 publicKey         : Public key pair - see rsa.def
  RETURN:        TRUE          Operation completed
                 FALSE         Fatal Error
 ****************************************************************************/
byte NOS_RSA_UnSign(byte            *HashResult, 
                    usint           *HashResultLen,
                    byte            *Signature, 
                    usint            SignatureLen, 
                    RSA_PUBLIC_KEY  *publicKey      );


#ifdef __cplusplus
}
#endif

#endif