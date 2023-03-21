/****************************************************************************
 * FILE NAME:   FornProt.H                                                  *
 * MODULE NAME: FORNPROT                                                    *
 * PROGRAMMER:  Hai Shalom                                                  *
 * DESCRIPTION: Foreign Protocol Module for NOS 7                           *
 * REVISION:    01.00                                                       *
 ****************************************************************************/

#ifndef __FORNPROT_H__
  #define __FORNPROT_H__

          /*=========================================*
           *          D E F I N I T I O N S          *
           *=========================================*/

/* Return values */
#define FORNPROT_OK                    0        /* OK, No errors */
#define FORNPROT_FAIL                 -1        /* Failure */
#define FORNPROT_LAST                 -2        /* Last block in list */
#define FORNPROT_NOT_EXIST            -3        /* Block doesn't exist */
#define FORNPROT_OPEN_WRITE_FAIL      -4        /* Error opening block */
#define FORNPROT_WRITE_DATA_FAIL      -5        /* Error writing block data */
#define FORNPROT_WRITE_SPECIFIC_FAIL  -6        /* Error writing specific header */
#define FORNPROT_SEC_KEY_FAIL         -7        /* Error occured during RSA process */
#define FORNPROT_SEC_DOWNLOAD_FAIL    -8        /* Error secured download */
#define FORNPROT_SEC_TYPE_FAIL        -9        /* Block of type must be secured, tried to download
                                                   a non-secured block */

/* Paramaters for Fpd_Go() function */
#define FPD_START_COMM_ACTIVE          1
#define FPD_START_COMM_INACTIVE        2
#define FPD_START_RESET                3

#define MAX_FILENAME_SIZE              12

          /*=========================================*
           *        P U B L I C     T Y P E S        *
           *=========================================*/

typedef struct
{
  BlockIdent    Ident;                           /* Block name, owner and type */
  ulint         BlockSize;                       /* Block size */
  lipver        Version;                         /* Block version */
  DateStruct    Date;                            /* Block date */
  usint         CheckSum;                        /* Block check sum */
  usint         IsSecured;                       /* Block secured */
  void         *Signature;                       /* RSA block signature for secured block */
  char          FileName[ MAX_FILENAME_SIZE ];   /* Block file name (optional) */

  byte Spare[ 30 ];

} FpBlockHeader;

          /*=========================================*
           *     P U B L I C   F U N C T I O N S     *
           *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FornProt_ListGetFirst
 * DESCRIPTION  : Get the first block information
 * PARAMETERS   : (Output) Block header
 * RETURN       : Block handle for success, FORNPROT_NOT_EXIST,
 *                or FORNPROT_FAIL.
 * NOTE         : none
 * ------------------------------------------------------------------------ */
sint FornProt_ListGetFirst( FpBlockHeader *BlockHeader );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FornProt_ListGetNext
 * DESCRIPTION  : Get next block information
 * PARAMETERS   : (Input)Block handle (Output) Block header
 * RETURN       : FORNPROT_OK for success, FORNPROT_LAST for last block,
 *                else FORNPROT_FAIL.
 * NOTE         : none
 * ------------------------------------------------------------------------ */
sint FornProt_ListGetNext( sint Handle, FpBlockHeader *BlockHeader );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FornProt_DeleteBlock
 * DESCRIPTION  : Delete a block
 * PARAMETERS   : Block name, block type
 * RETURN       : FORNPROT_OK for success, else FORNPROT_FAIL
 * NOTE         : none
 * ------------------------------------------------------------------------ */
sint FornProt_DeleteBlock( const BlockIdent *Ident );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FornProt_OpenWrite
 * DESCRIPTION  : Open write session
 * PARAMETERS   : (Input) Block header, Specific header and size
 *                (Output) Last written offset
 * RETURN       : Handle to block
 * NOTE         : none
 * ------------------------------------------------------------------------ */
sint FornProt_OpenWrite( const FpBlockHeader *BlockHeader, const void *SpecificHeader, usint SpecificSize, ulint *LastOffset );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FornProt_Write
 * DESCRIPTION  : Write block data
 * PARAMETERS   : Handle, a pointer to the data, data size, current offset
 * RETURN       : FORNPROT_OK for success, else FORNPROT_FAIL
 * NOTE         : none
 * ------------------------------------------------------------------------ */
sint FornProt_Write( sint Handle, const void *BlockData, ulint BlockSize, ulint Offset );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FornProt_CloseWrite
 * DESCRIPTION  : Close write session
 * PARAMETERS   : Block handle
 * RETURN       : FORNPROT_OK for success, else FORNPROT_FAIL
 * NOTE         : none
 * ------------------------------------------------------------------------ */
sint FornProt_CloseWrite( sint Handle );

#ifdef __NOS__
  #include fornprot_nos
#endif

#endif
