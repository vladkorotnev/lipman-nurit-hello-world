/****************************************************************************
 * FILE NAME:   EEPROM.H                                                    *
 * MODULE NAME: EEPROM                                                      *
 * PROGRAMMER:  EPHRAIM.                                                    *
 *              Shlomo Yakar - Revision for PEN project.                    *
 * DESCRIPTION: This module controls the EEPROM of ST25C02/4/8 type         *
 *              and compatible.                                             *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01.01 18/08/96.                                             *
 * HISTORY:     01.00 20/01/96.                                             *
 ****************************************************************************/


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

#define REPEAT_NUM       3     /* repeat number for eeprom communication error  */
#define EEPROM_REPEAT    3     /* repeat number for eeprom write error  */
#define EEPROM_OK        0     /* EEPROM O.K! */
#define COMM_ERROR       0x10  /* no ACK from EEPROM  */
#define EEPROM_WRITE_ER  0x11  /* read array != write array  */
#define OVER_SIZE        0x12  /* read or write address > EEPROM_SIZE  */
#define COMM_ERROR1      0x13  /* no ACK from EEPROM  */
#define COMM_ERROR2      0x14  /* no ACK from EEPROM  */
#define COMPARE_ERROR    0x15  /* no compare in test  */


          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
/* void */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */




    /*==================================================================*
     *           F U N C T I O N S     P R O T O T Y P E S              *
     *==================================================================*/


/*------------------------------------------------------------------------
 *
 * FUNCTION NAME: Eeprom_Reset
 *
 * DESCRIPTION    Resets  the EEPROM after any POWER ON
 *
 * RETURN:        Void.
 *
 * NOTES:         None.
 *
------------------------------------------------------------------------*/

void Eeprom_Reset(void);



/*------------------------------------------------------------------------
 *
 * FUNCTION NAME: Eeprom_Read
 *
 * DESCRIPTION:   Reads any bytes from the EEPROM.
 *
 * RETURN:        Error code:  0 - O.K!
 *                           COMM_ERROR  - EEPROM communication error
 *                           OVER_SIZE  _ any address > EEPROM SIZE
 *
 * NOTES:         None.
 *
------------------------------------------------------------------------*/

BYTE Eeprom_Read(
          BYTE *read_array,   /*pointer to array in RAM for read */
          USINT address,      /*  address of first byte in EEPROM  */
          USINT  array_size   /*  read array size  */
                               );

/*------------------------------------------------------------------------
 * FUNCTION NAME: Eeprom_Write
 * DESCRIPTION:   Writes bytes to the application area of the EEPROM:
 *                0..(EEPROM_SIZE-RESTRICTED_NOS_AREA)
 * RETURN:        Error code:  0 - O.K!
 *                           COMM_ERROR  - EEPROM communication error
 *                           EEPROM_WRITE_ER - EEPROM write error
 *                           OVER_SIZE  _ any address 
 *                                          > EEPROM SIZE-RESTRICTED_NOS_AREA
 * NOTES:         None.
 ------------------------------------------------------------------------*/
BYTE  Eeprom_Write(USINT  address,     /*address of first byte in EEPROM  */
                   BYTE  *write_array, /*pointer to array in RAM for write*/
                   USINT  array_size); /*read array size  */

#ifdef __NOS__
  #include eeprom_nos
#endif
