/****************************************************************************
 *                                                                          *
 * FILE NAME:   Params.H                                                    *
 *                                                                          *
 * MODULE NAME: Params                                                      *                                                                          *
 *                                                                          *
 * PROGRAMMER:  Ofir                                                        *
 *                                                                          *
 * DESCRIPTION: Parameters for nurit appl.                                  *
 *                                                                          *
 *              API function declarations                                   *
 *                                                                          *
 * REVISION:    01.00 22/05/1994.                                           *
 *                                                                          *
 ****************************************************************************/

   /*==========================================*
    *         I N T R O D U C T I O N          *
    *==========================================*/
   /*==========================================*
    *             I N C L U D E S              *
    *==========================================*/

   /*==========================================*
    *           D E F I N I T I O N S          *
    *==========================================*/

/* RETURN ERROR VALUES: */

#define PRM_NO_PRM_TO_CLR       3     /* no parmas to clear */
#define PRM_NOT_EXIST           4     /* params do not exist. */
#define PRM_INVALID_BLOCK_NAME  5     /* Invalid parameters block name. */
#define PRM_ERROR_WRITE         11    /* Error Writing to Prot.Ram/Flash */
#define PRM_BUF_TO_BIG          13    /* user Buffer too big , part of data
                                         was lost. */
#define PRM_PRINT_ERROR         14    /* printer error. */
#define PRM_INVALID_INDEX       15    /* Invalid index / index to big or end>start (see Params_SetIndx) */
#define PRM_OUT_OF_FLASH        32    /* cannot update parameters on
                                         FLASH memory because not engough
                                         bytes left. --> User should load
                                         new parameters. */
#define PRM_COMM_FAIL           34    /* Modem Rs Disconnected */

    /*=========================================*
     *        M I S C E L L A N E O U S        *
     *=========================================*/

    /*=========================================*
     *   P U B L I C       F U N C T I O N S   *
     *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_Get.
 *
 * DESCRIPTION:   copy specified Params block to user's buffer.
 *
 *                block_name - string (Id of block).
 *                buf        - pointer to user buffer (since module
 *                             doesn't know the real type of the
 *                             parameters it keeps it void).
 *                buf_size   - amount of user buffer (in bytes) to copy
 *                             parameters block to.
 *                block_size - to return actual size of block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                  Meaning:
 *
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Params_Get (char *block_name, void *buf, sint buf_size, usint *block_size);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_GetPtr.
 *
 * DESCRIPTION:   Returns specified Parameter block's pointer (address).
 *
 *                *block_name - string (Id of block).
 *                **block_ptr - pointer to pointer in which address
 *                              of block will be put.
 *                *size       - to return actual size of block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                  Meaning:
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name.
 *
 * NOTES:         * This function should be used instead of Params_Get since
 *                  it doesn't waste buffers memory.
 *                * Pointer to user's data is void since module does'nt know
 *                  the exact type of data.
 *
 * ------------------------------------------------------------------------ */
sint Params_GetPtr (char *block_name, void **block_ptr, usint *size);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_GetDataPtr.
 *
 * DESCRIPTION:   Returns specified Data Parameter block's (not executable) pointer (address).
 *
 *                *block_name - string (Id of block).
 *                **block_ptr - pointer to pointer in which address
 *                              of block will be put.
 *                *size       - to return actual size of block.
 *
 * RETURN:        Returns 0 for ok or error no
 *
 *                Error's:
 *                Value:                  Meaning:
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name.
 *
 * NOTES:         * This function should be used instead of Params_Get since
 *                  it doesn't waste buffers memory.
 *                * Pointer to user's data is void since module does'nt know
 *                  the exact type of data.
 *                * Use this function only on VISA secured terminals to get Data blocks. 
 * ------------------------------------------------------------------------ */
sint Params_GetDataPtr (char *block_name, void **block_ptr, usint *size);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_SetIndex.
 *
 * DESCRIPTION:   Sets specified Parameter block's from index to index.
 *
 *                *block_name  - string (Id of block).
 *                start        - Start (From) index in parameter.
 *                end          - End (Up to) index in parameter.
 *                *user_data   - pointer to user's data/buffer.
 *
 *                *index range : 0 .. block size - 1 (index in bytes).
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Errors...
 *                Value:                  Meaning:
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name.
 *                PRM_OUT_OF_FLASH        Not engough memory in FLASH to
 *                                        update parameters block.
 *                PRM_ERROR_WRITE         Error writing.
 *                PRM_INVALID_INDEX       Invalid index / index to big or
 *                                        end > start.
 *
 * NOTES:         *Pointer to user's data is void since module doesn't know
 *                the exact data type.
 *                *Make sure indexes are valid and in the right order.
 *
 * ------------------------------------------------------------------------ */
sint Params_SetIndex (char *block_name, usint start, usint end, void *user_data);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_Set.
 *
 * DESCRIPTION:   Set params block according to user's buffer.
 *
 *                block_name - string (Id of block).
 *                buf        - pointer to user buffer (since
 *                             module dont no the real type of the
 *                             parameters it keeps it void).
 *                buf_size   - amount of user buffer (in bytes) to copy
 *                             to parameters block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                 Meaning:
 *
 *                PRM_NOT_EXIST          params do not exist.
 *                PRM_INVALID_BLOCK_NAME Invalid parameters block name.
 *                PRM_OUT_OF_FLASH       Not engough memory in FLASH to
 *                                       update parameters block.
 *                PRM_ERROR_WRITE        Error writing.
 *                PRM_BUF_TO_BIG         Buffer too big , part of data
 *                                       was lost.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Params_Set (char *block_name, void *buf, sint buf_size);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_Create.
 *
 * DESCRIPTION:   Create New params block according to user's buffer.
 *
 *                block_name - string (Id of block).
 *                buf        - pointer to user buffer (since
 *                             module dont no the real type of the
 *                             parameters it keeps it void).
 *                buf_size   - amount of user buffer (in bytes) to copy
 *                             to parameters block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                 Meaning:
 *
 *                PRM_OUT_OF_FLASH       Not engough memory in FLASH to
 *                                       update parameters block.
 *                PRM_ERROR_WRITE        Error writing.
 *                PRM_BUF_TO_BIG         Buffer too big , part of data
 *                                       was lost.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Params_Create (char *block_name, void *buf, sint buf_size);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_GetPtrByType.
 *
 * DESCRIPTION:   Returns specified Parameter block's pointer (address).
 *                Type        - Type of block
 *                *block_name - string (Id of block).
 *                **block_ptr - pointer to pointer in which address
 *                              of block will be put.
 *                *size       - to return actual size of block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                  Meaning:
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name or type.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Params_GetPtrByType (char *block_name, byte Type ,void **block_ptr, ulint *size);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_FindFirst.
 *
 * DESCRIPTION:   Find First block from Type.
 *                Type        - Type of block
 *                *block_name - string (output).
 *                **block_ptr - pointer to pointer in which address
 *                              of block will be put.
 *                *size       - to return actual size of block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                  Meaning:
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name or type.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Params_FindFirst (char *block_name, byte Type ,void **block_ptr, ulint *size);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_FindNext.
 *
 * DESCRIPTION:   Find Next block from Type.
 *                Type        - Type of block
 *                *block_name - input : the last block name returned
 *                              by _FindFirst or FindNext
 *                              output : the block name that was found.
 *                **block_ptr - pointer to pointer in which address
 *                              of block will be put.
 *                *size       - to return actual size of block.
 *
 * RETURN:        Returns 0 for ok or error no.
 *
 *                Error's:
 *                Value:                  Meaning:
 *                PRM_NOT_EXIST           params do not exist.
 *                PRM_INVALID_BLOCK_NAME  Invalid parameters block name or type.
 *
 * NOTES:         To be called only after Params_FindFirst.
 *
 * ------------------------------------------------------------------------ */
sint Params_FindNext (char *block_name, byte Type ,void **block_ptr, ulint *size);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Params_IsDLMExist.
 *
 * DESCRIPTION:   Check if DLM exist
 *
 * RETURN:        Returns 0 if exist or PRM_NOT_EXIST if not.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Params_IsDLMExist (char *block_name);

#ifdef __NOS__
  #include params_nos
#endif
