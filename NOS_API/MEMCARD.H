/****************************************************************************
 *                                                                          *
 * FILE NAME:   MEMCARD.H                                                   *
 *                                                                          *
 * MODULE NAME: MemCard                                                     *
 *                                                                          *
 * PROGRAMMER:  Oren Sokoler                                                *
 *                                                                          *
 * DESCRIPTION: Secure Digital (SD) / MMC device driver public definitions  *
 *                                                                          *
 * REVISION:    01.00 07/04/04.                                             *
 *                                                                          *
 ****************************************************************************/

#ifndef __MEMCARD_H__
#define __MEMCARD_H__

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

/* Function return values */

#define         MEMCARD_OK             0    /* Operation was o.k.      */
#define         MEMCARD_TIMEOUT        1    /* Operation timed out     */
#define         MEMCARD_COM_ERR        2    /* Communication error     */
#define         MEMCARD_NOT_EXIST      3    /* Card does not exist     */
#define         MEMCARD_WRITE_PROT     4    /* Card is write protected */
#define         MEMCARD_ARG_ERR        5    /* Function argument error */
#define         MEMCARD_FAIL          20    /* Card fatal error        */

/* Memory card block size */

#define         MEMCARD_BLOCK_SIZE   512L

          /*==========================================*
           *       P U B L I C   T Y P E S            *
           *==========================================*/

/* Memory card type */

typedef enum {

  MEMCARD_TYPE_MMC ,
  MEMCARD_TYPE_SD  

} MemCardType;

/* Memory card information */

typedef struct {

        usint Size;           /* Size of this structure     */
  MemCardType Type;           /* MMC / SD                   */
         byte MfgID;          /* Manufacture ID             */
        usint ApplID;         /* Application ID             */
         char ProductName[6]; /* Product name               */
         char ProductRev[3];  /* Product revision M.N       */
        ulint SerialNumber;   /* Serial number              */
         char MfgDate[7];     /* Manufacture Date MM/YYYY   */
        ulint NumOfBlocks;    /* Number of blocks (sectors) */

} MemCardInf;

           /*=========================================*
            *   P U B L I C     F U N C T I O N S     *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: MemCard_ReadBlock
 *
 * DESCRIPTION:   Read a block from the SD Card
 *
 * PARAMETERS:    BlockNum - (Input)  Block number to read
 *                Buf      - (Output) Pointer to buffer
 *
 * RETURN:        MEMCARD_OK      - Read was successful
 *                MEMCARD_ARG_ERR - Function argument error 
 *                MEMCARD_FAIL    - Read error
 *
 * NOTES:         Blocks are always read in units of 512 bytes
 *
 * ------------------------------------------------------------------------ */
byte MemCard_ReadBlock ( ulint BlockNum , byte * Buf );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: MemCard_WriteBlock
 *
 * DESCRIPTION:   Write a block to the SD Card
 *
 * PARAMETERS:    BlockNum - (Input) Block number to write
 *                Buf      - (Input) Pointer to buffer
 *
 * RETURN:        MEMCARD_OK         - Write was successful
 *                MEMCARD_ARG_ERR    - Function argument error 
 *                MEMCARD_WRITE_PROT - Card is write protected
 *                MEMCARD_FAIL       - Write error
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte MemCard_WriteBlock ( ulint BlockNum , byte * Buf );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: MemCard_GetInfo
 *
 * DESCRIPTION:   Return the SD card information
 *
 * PARAMETERS:    Info - (Output) Card information
 *
 * RETURN:        MEMCARD_OK        - Card information returned
 *                MEMCARD_NOT_EXIST - Card does not exist
 *                MEMCARD_ARG_ERR   - Function argument error 
 *                MEMCARD_FAIL      - Card fatal error
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte MemCard_GetInfo(MemCardInf * Info);

#ifdef __NOS__
  #include memcard_nos
#endif  

#endif