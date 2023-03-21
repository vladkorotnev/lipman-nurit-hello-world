/***************************************************************************
 *                                                                         *
 * FILE NAME:   DES.H                                                      *
 *                                                                         *
 * MODULE NAME: DES                                                        *
 *                                                                         *
 * PROGRAMMER:  Philippe Berrebi.                                          *
 *                                                                         *
 * DESCRIPTION: Performs Data Encryption Standard,                         *
 *              for ARM, and MCC 68K, 6811                                 *
 *              NOTE: DO NOT USE on Dallas 5002FP                          *
 *                                                                         *
 * REVISION:    10_00  08/06/2004.                                         *
 *                                                                         *
 ***************************************************************************/

#ifndef _DES_H_
#define _DES_H_



                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Des_DEA
 *
 * DESCRIPTION:   Set key and Performs the encryption/decryption
 *                of a given block, using Data-Encryption-Algorithm.
 *
 * INPUT:         in:      packed 64-bit input block (8 bytes).
 *                key:     packed 64-bit key blook (8 bytes).
 *                encrypt: TRUE - encrypt, FALSE - decrypt.
 *
 * OUTPUT:        out:     packed 64-bit output block (8 bytes).
 *
 * ------------------------------------------------------------------------ */
void Des_DEA ( byte    *in,
               byte    *out,
               byte    *key,
               boolean  encrypt );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Des_3DES_DEA
 *
 * DESCRIPTION:   Performs Triple DES encryption/decryption
 *                of a given block, using Data-Encryption-Algorithm.
 *                If encrypt == TRUE
 *                   CipheredText = DES(k1, UNDES(k2, DES(k1, Plaintext)))
 *                else
 *                   PlainText = UNDES(k1, DES(k2, UNDES(k1, CipheredText)))
 *
 * INPUT:         in:      packed 64-bit input block (8 bytes).
 *                key:     packed 128-bit key blook (16 bytes).
 *                encrypt: TRUE - encrypt, FALSE - decrypt.
 *
 * OUTPUT:        out:     packed 64-bit output block (8 bytes).
 *
 * ------------------------------------------------------------------------ */
void Des_3DES_DEA ( byte       *in,
                    byte       *out,
                    byte       *key,
                    boolean     encrypt );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Des_3DES_3Length_DEA
 *
 * DESCRIPTION:   Performs Triple DES Triple Length encryption/decryption
 *                of a given block, using Data-Encryption-Algorithm.
 *                If encrypt == TRUE
 *                   CipheredText = DES(k3, UNDES(k2, DES(k1, Plaintext)))
 *                else
 *                   PlainText = UNDES(k1, DES(k2, UNDES(k3, CipheredText)))
 *
 * INPUT:         in:      packed 64-bit input block (8 bytes).
 *                key:     packed 192-bit key blook (24 bytes).
 *                encrypt: TRUE - encrypt, FALSE - decrypt.
 *
 * OUTPUT:        out:     packed 64-bit output block (8 bytes).
 *
 * ------------------------------------------------------------------------ */
void Des_3DES_3Length_DEA ( byte       *in,
                            byte       *out,
                            byte       *key,
                            boolean     encrypt );


#ifdef __NOS__
    #include des_nos
#endif

#endif