/****************************************************************************
 FILE NAME:   SAFE_DB.H
 MODULE NAME: SAFE_DB
 PROGRAMMER:  Oren tar change by  Nimni nissan
 DESCRIPTION: Safe management (safe data kept in ram-disk)
              API functions declarations
 REVISION:    15/08/97
 ****************************************************************************/
                /* ======================================= *
                 *         I N T R O D U C T I O N         *
                 * ======================================= */
#ifndef __Safe_Db_H
  #define __Safe_Db_H
                /* ======================================= *
                 *             I N C L U D E S             *
                 * ======================================= */

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

                /* ======================================= *
                 *        P U B L I C E    T Y P E S       *
                 * ======================================= */
typedef enum
{
  SAFE_OK        , /*- Ok                           */
  SAFE_NO_DISK   , /*- No ram disk                  */
  SAFE_CREATED   , /*- Called SafeDB_Build()        */
  SAFE_BAD_DB    , /*- Failed to call SafeDB_Build()*/
  SAFE_OUT_OF_MEM, /*- Not enough memory */
  SAFE_BAD_PARAM ,   /*- Parameters Module or Object out of range*/
  SAFE_BLOCK_NOT_EXIST
} SAFE_RETVAL;
  /* ======================================= *
		 *     P U B L I C   F U N C T I O N S     *
		 * ======================================= */
/* --------------------------------------------------------------------------

 * FUNCTION NAME: SafeDB_Verify
 * DESCRIPTION:   This function checks for the existance and integrity of the
 *                safe-data-base.
 * RETURN:        SAFE_OK      - Ok
 *                SAFE_NO_DISK - No ram disk
 *                SAFE_CREATED - Called SafeDB_Build()
 *                SAFE_BAD_DB  - Failed to call SafeDB_Build()
 * NOTES:         The function calls SafeDB_Build() if necessary.
 * ------------------------------------------------------------------------*/
sint SafeDB_Verify (void);

/* --------------------------------------------------------------------------
* FUNCTION NAME: SafeDB_Build
* DESCRIPTION:   Terminals with RAM DISK:                
*                This function creates a new safe-data-base with default
*                values, after it destroys the current one if there is one.
*                The function call SafeDB_BuildRD with the application file name.
*                Terminal with new SafeDB(without RAM DISK):
*                1.Verify the safe db and create one if not verified.
*                2.Delte all current application records.
* RETURN:        SAFE_OK         - Ok
*                SAFE_NO_DISK    - No ram disk
*                SAFE_OUT_OF_MEM - Not enough memory
* NOTES:         none.
* ------------------------------------------------------------------------*/
sint SafeDB_Build (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SafeDB_StoreBlock
 * DESCRIPTION:   Store a block in the safe-data-base (replacing the
 *                existing block of the same type)
 * RETURN:        The Safe_WriteDb return value .
 * NOTES:       - Object must be in the range 0..7
 *              - The function calls SafeDB_Build() if necessary.
 * ------------------------------------------------------------------------*/
sint SafeDB_StoreBlock (byte *Block, byte Module, byte Object, usint Size);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SafeDB_GetBlock
 * DESCRIPTION:   Get a block from the safe-data-base
 * RETURN:       The Safe_ReadDb return value .
 * NOTES:       - Object must be in the range 0..7
 *              - The function calls SafeDB_Build() if necessary.
 * ------------------------------------------------------------------------*/
sint SafeDB_GetBlock (byte *Block, byte Module, byte Object, usint Size);

#ifdef __NOS__
  #include safe_nos
#endif

#endif /*__Safe_Db_H*/













