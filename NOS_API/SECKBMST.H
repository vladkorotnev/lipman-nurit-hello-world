/****************************************************************************
 *                                                                          *
 * FILE NAME:   seckbmst.h                                                  *
 *                                                                          *
 * MODULE NAME: SecureKb Master                                             *
 *                                                                          *
 * PROGRAMMER:  Rami Rosenbaum                                              *
 *                                                                          *
 * DESCRIPTION: Master part of the SecureKb module (see SecKb.doc).         *
 *              Manages the Slave in the process of obtaining an encrypted  *
 *              Pin # from the user.                                        *
 *                                                                          *
 * REVISION:    01.00                                                       *
 *                                                                          *
 ****************************************************************************/
#ifndef _SECURE_KB_MASTER_H_
#define _SECURE_KB_MASTER_H_


        /*==========================================*
         *             I N C L U D E S              *
         *==========================================*/

#include seckb_def


        /*=========================================*
         *   F U N C T I O N  P R O T O T Y P E S  *
         *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_DiversifyKey
 * DESCRIPTION:   Diversify a key to generate a one-time use Working Key.
 * INPUT:         pKeyName      - unique name of Key to diversify with.
 *                                NULL-terminated or max 8 bytes.
 *                pDiversifyKey - diversification key params (encryptr.def).
 * RETURN:        _OK                      - Key diversified OK
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _PARAM_ERROR             - Wrong Parameter
 *                _ENCRYPTR_KEY_TYPE_ERROR - Mismatch in Key Type
 *                _KEYDB_ERROR             - Error in module KeyDB
 *                _FATAL_ERROR
 * NOTES:         - If the Diversified Key already exists in the Key DB, 
 *                  it will be replaced by the new one.
 *                - To avoid a Key DB Overflow, it is recommended to erase
 *                  a Diversified Key after its use.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_DiversifyKey (  byte                        *pKeyName,
                                U_Encryptr_DiversifyKeyPrms *pDiversifyKey );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_Encrypt
 * DESCRIPTION:   Encrypt PIN Block / Data.
 *                Set module state to ENCRYPT.
 * INPUT:         pKeyName         - unique name of Key to encrypt with.
 *                                   NULL-terminated or max 8 bytes.
 *                PinBlockType     - pin-block format (encryptr.def).
 *                pPinUnion        - pin-block union  (encryptr.def).
 *                EncryptionType   - encryption type  (encryptr.def).
 * RETURN:        _OK                      - Encryption launched successfully
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _STATE_ERROR             - Not in expected state
 *                _PIN_TOO_OFTEN           - Over 120 PIN attempts per hour
 *                _PARAM_ERROR             - Wrong Parameter
 *                _PIN_LEN_MISMATCH        - Application PIN Length mismatch
 *                _ENCRYPTR_KEY_TYPE_ERROR - Mismatch in Key Type
 *                _KEYDB_ERROR             - Error in module KeyDB
 *                _ENCRYPTION_DUKPT_PINPAD_END  - Specific error during encryption
 *                _ENCRYPTION_DUKPT_COUNT_EMPTY - Specific error during encryption
 *                _ENCRYPTR_PINBLOCK_TYPE_ERROR - PIN Block Type not supported
 *                _SECURITY_MISMATCH       - Problem with KTK or Security incompatibility
 *                _ERROR                   - Protocol Error (External Secured Keyboard)
 *                _FATAL_ERROR
 * NOTES:         - If any error occured - change State to IDLE.
 *                - In MAC/DATA encryption, must be called from IDLE State.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_Encrypt ( byte                     *pKeyName,
                          E_Encryptr_PinBlockType   PinBlockType,
                          U_Encryptr_InputBlock    *pPinUnion,
                          E_EncryptionType          EncryptionType );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_GetEncryption.
 * DESCRIPTION:   To obtain the encryption result, whether of PIN Block or 
 *                Message Authentication Code (MAC).
 * RETURN:        _OK              - Encryption retrieved successfully
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _STATE_ERROR     - Not in expected state (= ENCRYPTION_READY)
 *                _PARAM_ERROR     - Wrong Parameter
 *                _BUF_TOO_SHORT   - Buffer given for Result is too short
 *                _FATAL_ERROR
 * NOTES:         - If not in State ENCRYPTION_READY - change State to IDLE.
 *                - At end of process, State is automatically set to IDLE.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_GetEncryption ( U_Encryption_Result  *pResult );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_GetExternalKbSwVersion
 * DESCRIPTION:   Retrieve the SW version of the External Keyboard (4 digits).
 * OUTPUT:        pExternalKbSwVersion - The SW version of the External KB (4 digits).
 * RETURN:        _OK              - Version is returned OK
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _FATAL_ERROR     - Function not supported
 * NOTES:         Valid only when an External Keyboard is used.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_GetExternalKbSwVersion ( usint    *pExternalKbSwVersion );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_GetState
 * DESCRIPTION:   Returns the current working state.
 * RETURN:        State.
 * ------------------------------------------------------------------------ */
SecKbState  SecKbMstr_GetState ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_IsEncryptionReady
 * DESCRIPTION:   Check if the Encryption process has finished, and Result is
 *                ready to be retrieved.
 * RETURN:        _OK          - Encryption Result is ready
 *                _NOT_READY   - Encryption process has not finished yet
 *                _STATE_ERROR - Not in expected state (= ENCRYPT)
 * NOTES:         If not in State ENCRYPT - change State to IDLE.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_IsEncryptionReady ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_SetGetPinTOut
 * DESCRIPTION:   Update timeout for entering a PIN number by the user. 
 *                Can be called only when in state IDLE.
 * INPUT:         TOut - In seconds.
 * RETURN:        _OK          - Timeout updated successfully
 *                _STATE_ERROR - Not in expected state (= IDLE)
 * NOTES:         - Default Time Out is  30 seconds.
 *                - Maximum Time Out is 120 seconds.
 *                - If TOut == 0            ->  Time Out = Default Time Out.
 *                - If TOut > Max Time Out  ->  Time Out = Max Time Out.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_SetGetPinTOut ( byte  TOut );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_ToStateGetPin.
 * DESCRIPTION:   Switch the working state to GET_PIN.
 * RETURN:        _OK          - State is set to GET_PIN
 *                _STATE_ERROR - Not in expected state (= IDLE)
 *                _FATAL_ERROR
 * NOTES:         - If not in State IDLE - change State to IDLE.
 *                - The function flushes the Keyboard buffer.
 *                - This State is irrelevant for MAC or DATA Encryption.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_ToStateGetPin ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_ToStateIdle
 * DESCRIPTION:   Switch the working state to IDLE.
 * RETURN:        _OK - State is set to IDLE
 * NOTES:         - Can be called from ANY State.
 *                - The function flushes the Keyboard buffer.
 *                - In IDLE State, the Keyboard is in non-secure mode. 
 *                  Any key press will be passed to calling applications unmasked.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_ToStateIdle ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_ToStatePinObtained
 * DESCRIPTION:   Switch the working state to PIN_OBTAINED.
 * RETURN:        _OK          - State is set to PIN_OBTAINED
 *                _STATE_ERROR - Not in expected state (= GET_PIN)
 *                _FATAL_ERROR
 * NOTES:         - If not in State GET_PIN or PIN_OBTAINED - change State to IDLE.
 *                - The function flushes the Keyboard buffer.
 *                - This State is irrelevant for MAC or DATA Encryption.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_ToStatePinObtained ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_VerifyOffLinePin
 * DESCRIPTION:   Perform EMV Off-Line PIN verification of a user entered PIN,
 *                versus the PIN number of a Smart Card.
 * INPUT:         pIccPin - Off-Line PIN verification structure (seckb.def)
 * RETURN:        _OK               - Off-Line PIN verification succeed
 *                _NULL_ASSIGNMENT  - NULL given as pointer
 *                _STATE_ERROR      - Not in expected state (= PIN_OBTAINED)
 *                _PIN_TOO_OFTEN    - Over 120 PIN attempts per hour
 *                _PIN_LEN_MISMATCH - Application PIN Length mismatch
 *                _ERROR            - Error in RSA calculation (if encrypted PIN)
 *                _FATAL_ERROR
 * NOTES:         If not in State PIN_OBTAINED - change State to IDLE.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_VerifyOffLinePin ( S_SecKb_IccPin   *pIccPin );


           /*======================================================*
            *   T E S T   F U N C T I O N S   P R O T O T Y P E S  *
            *======================================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_SetTestKey
 * DESCRIPTION:   Writes a Test Key in Key DB, for the _TestEncrypt() function.
 * INPUT:         pTestKey - Key Data block union (encryptr.def).
 * RETURN:        _OK                      - Test Key written in DB successfully
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _PARAM_ERROR             - Wrong Parameter
 *                _STATE_ERROR             - Not in expected state (= IDLE)
 *                _ENCRYPTR_KEY_TYPE_ERROR - Mismatch in Key Type
 *                _KEYDB_ERROR             - Error in module KeyDB
 *                _SECURITY_MISMATCH       - Problem with KTK or Security incompatibility
 *                _FATAL_ERROR
 * NOTES:         - If not in State IDLE - change State to IDLE.
 *                - Test Key name is hard-coded, therefore only Key Data is needed.
 *                - DUKPT is NOT supported for Test Key.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_SetTestKey ( U_Encryption_Key   *pTestKey );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_ClearTestKey
 * DESCRIPTION:   Clears THE Test Key, if exists in Key DB.
 * RETURN:        _OK              - Test Key deleted from DB successfully
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _STATE_ERROR     - Not in expected state (= IDLE)
 *                _KEYDB_ERROR     - Error in module KeyDB
 *                _FATAL_ERROR
 * NOTES:         - If not in State IDLE - change State to IDLE.
 *                - Test Key name is hard-coded, therefore no Input name is needed.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_ClearTestKey ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SecKbMstr_TestEncrypt
 * DESCRIPTION:   Make Encryption with THE Test Key and returns Result.
 *                The function manages the whole Encryption process, and
 *                internally controls the correct flow of the State Machine.
 * INPUT:         PinBlockType     - pin-block format  (encryptr.def).
 *                pPinUnion        - input block union (encryptr.def).
 *                EncryptionType   - encryption type   (encryptr.def).
 *                pPinCode         - ASCII string, digits only.
 *                                   If pPinCode == NULL -> PinCode = "1234".
 *                PinSize          - number of digits in pin code.
 *                pResult          - encryption result.
 * RETURN:        _OK                      - Encryption finished successfully
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _STATE_ERROR             - Not in expected state
 *                _PIN_TOO_OFTEN           - Over 120 PIN attempts per hour
 *                _PARAM_ERROR             - Wrong Parameter
 *                _PIN_LEN_MISMATCH        - Application PIN Length mismatch
 *                _ENCRYPTR_KEY_TYPE_ERROR - Mismatch in Key Type
 *                _KEYDB_ERROR             - Error in module KeyDB
 *                _SECURITY_MISMATCH       - Problem with KTK or Security incompatibility
 *                _FATAL_ERROR
 * NOTES:         - If not in State IDLE - change State to IDLE.
 *                - Test Key name is hard-coded, therefore no Input name is needed.
 *                - DUKPT is NOT supported for Test Key encryption.
 *                - The Test Key is automatically erased at the end of the process.
 * ------------------------------------------------------------------------ */
char  SecKbMstr_TestEncrypt ( E_Encryptr_PinBlockType   PinBlockType,
                              U_Encryptr_InputBlock    *pPinUnion,
                              E_EncryptionType          EncryptionType,
                              byte                     *pPinCode,       /* ASCII string*/
                              byte                      PinSize,        /* in Bytes    */
                              U_Encryption_Result      *pResult         );


#ifdef __NOS__
    #include seckbmstr_nos
#endif

#endif

