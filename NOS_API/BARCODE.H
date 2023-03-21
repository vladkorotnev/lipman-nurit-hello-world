/***************************************************************************
 * FILE NAME:   BARCODE.C
 *
 * MODULE NAME: BARCODE
 *
 * PROGRAMMER:  Oren Sokoler
 *
 * DESCRIPTION: Bar code reader
 *              API functions declarations
 *
 * REVISION:    01.00
 ***************************************************************************/

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

#define BAR_CODE_OK           0    /* Bar code in buffer is valid */
#define BAR_CODE_EMPTY       -1    /* No data in bar code buffer  */
#define BAR_CODE_DATA_ERR    -2    /* Data in bar code buffer is invalid */



          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

/* void */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: BarCode_Disable
 *
 * DESCRIPTION:   Disables the b-code reader
 *
 * RETURN:        void
 *
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void BarCode_Disable (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: BarCode_IsCompleted
 *
 * DESCRIPTION:   Checks if bar-code reading is completed
 *                automatically enables the BardCode reader, if it was
 *                previously disabled (by calling BarCode_Disable() )
 *
 * RETURN:        TRUE  - completed.
 *                FALSE - not yet completed.
 *
 * PARAMETERS:    *error :
 *
 *                BAR_CODE_OK        - valid information (format o.k.)
 *                BAR_CODE_EMPTY     - No barcode data is available
 *                BAR_CODE_DATA_ERR  - Error in barcode data stream
 *
 *
 * NOTES:         This function performs all the analysis.
 *                if bar-code not present, the output parameter error
 *                will be assigned BAR_CODE_EMPTY.
 * ------------------------------------------------------------------------ */
boolean BarCode_IsCompleted (sint *error);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: BarCode_BufferAddress
 *
 * DESCRIPTION:   return pointer to bar-code ascii array.
 *
 * RETURN:        pointer to b-code ascii array.
 *
 * NOTES:         **** End of buffer is marked with ENTER ****
 * ------------------------------------------------------------------------ */
byte *BarCode_BufferAddress(void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ExtKb_Read.
 *
 * DESCRIPTION:   Read one character from external keyboard (on PS/2).
 *
 * RETURN:        0     - No characters in buffer.
 *                Other - Code. If pressed key have ASCII
 *
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
byte ExtKb_Read( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ExtKb_Flush.
 *
 * DESCRIPTION:   Flush keyboard buffer.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void ExtKb_Flush( void );

#ifdef __NOS__
  #include barcode_nos
#endif
