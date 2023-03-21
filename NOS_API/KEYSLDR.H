/***************************************************************************
 *                                                                         *
 * FILE NAME:   keysldr.h                                                  *
 *                                                                         *
 * MODULE NAME: Keys Loader                                                *
 *                                                                         *
 * PROGRAMMER:  Rami Rosenbaum.                                            *
 *                                                                         *
 * DESCRIPTION: Load Keys to KeyDB database and erase keys from it.        *
 *              Module is in charge of the BlockCom protocol interface,    *
 *              and the aplication interface. See KeysLdr.doc & SecKb.doc. *
 *                                                                         *
 * REVISION:    01_00                                                      *
 *                                                                         *
 ***************************************************************************/

#ifndef _KEYS_LOADER_H_
#define _KEYS_LOADER_H_


            /* ======================================== *
             *             I N C L U D E S              *
             * ======================================== */

#include keysldr_def
#include encryptr_def


            /* ======================================== *
             *   F U N C T I O N  P R O T O T Y P E S   *
             * ======================================== */

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_ApplicationDataRead
 * DESCRIPTION:   Retrieve specific Application Data stored in the non-volatile Secured KeyDB.
 * INPUT:         pName - Name of unique Data-Block (NULL-terminated or max 8 bytes).
 *                pSize - Size of the Application allocated buffer for data.
 * OUTPUT:        pData - Pointer to the retrieved data stored in DB.
 *                pSize - Size of the retrieved data.
 * RETURN:        _OK               - Data-Block Application retrieved OK
 *                _NULL_ASSIGNMENT  - NULL given as pointer
 *                _NOT_FOUND        - Data-Block Application not found in DB
 *                _KEYDB_NOT_EXIST  - Key DB not allocated
 *                _KEYDB_TYPE_ERROR - Not an Application Data-Block
 *                _KEYDB_DATA_LEN_MISMATCH - Invalid Data-Block size
 *                _KEYDB_TOO_SMALL         - Given buffer too small
 *                _FATAL_ERROR
 * NOTES:         Maximum Data Size: 512 bytes.
 * ------------------------------------------------------------------------ */
char  KeysLdr_ApplicationDataRead ( byte       *pName,
                                    byte       *pData,
                                    usint      *pSize   );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_ApplicationDataWrite
 * DESCRIPTION:   Store specific Application Data in the non-volatile Secured KeyDB.
 *                If Data-Block already stored in DB, will be overwritten with new value.
 * INPUT:         pName - Name of unique Data-Block (NULL-terminated or max 8 bytes).
 *                pData - Pointer to the data to be stored in DB.
 *                Size  - Size of the Data block.
 * RETURN:        _OK                      - Data-Block Application stored OK
 *                _KEYDB_NOT_EXIST         - Key DB not allocated
 *                _KEYDB_DATA_LEN_MISMATCH - Invalid Data-Block size
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _KEYDB_SIGNATURE_ERROR   - Signature of Data-Block incorrect
 *                _KEYDB_DB_FULL           - KeyDB is full
 *                _KEYDB_WRITE_ERROR       - Can't write to memory
 *                _FATAL_ERROR
 * NOTES:         Maximum Data Size: 512 bytes.
 * ------------------------------------------------------------------------ */
char  KeysLdr_ApplicationDataWrite (byte    *pName, 
                                    byte    *pData,
                                    usint    Size   );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_CheckKeyPassword
 * DESCRIPTION:   Check an input Password validity. 
 * INPUT:         pKeyName    - Name of unique Key-Block.
 *                              NULL-terminated or max 8 bytes.
 *                pPassword   - Password value entered by the loader person.
 *                PasswordLen - Length of the entered password
 * RETURN:        _OK                     - Password is OK
 *                _NOT_FOUND              - Key not found in DB
 *                _KEYDB_NOT_EXIST        - Key DB not allocated 
 *                _NULL_ASSIGNMENT        - NULL given as pointer
 *                _KEYDB_INVALID_PASSWORD - Invalid Password provided by user
 *                _KEYDB_LOCKED_PASSWORD  - Password entry attempt is locked
 *                _FATAL_ERROR
 * NOTES:         The key maintains a retry counter. After the number of 
 *                unsuccessful retries is equal to or exceeds the maximum number  
 *                of retries associated to the password, it will be locked.
 *                This behavior can be used in accordance with Application 
 *                specific requirements.
 *                If the function is called with a correct user Password, 
 *                the Retry counter will be reset. 
 *                If the Retry counter is set to zero by the Application, 
 *                the number of retries will not be limited and the Key Password 
 *                will never be locked.
 * ------------------------------------------------------------------------ */
char  KeysLdr_CheckKeyPassword (byte   *pKeyName,
                                byte   *pPassword,
                                byte    PasswordLen );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_EraseKey
 * DESCRIPTION:   Erase Key-Block from KeyDB.
 * INPUT:         pKeyName - Name of unique Key-Block.
 *                           NULL-terminated or max 8 bytes.
 * RETURN:        _OK              - Key erased OK
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _NOT_FOUND       - Key not found in DB
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_EraseKey ( byte  *pKeyName );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_EraseKeyDB
 * DESCRIPTION:   Erase entire KeyDB database (all keys for all applications),
 *                including the Key Transport Key.
 * RETURN:        _OK              - Key DB erased OK
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR 
 * NOTES:         This function may be used to initialize the Key DB,
 *                before keys are written to the Database.
 * ------------------------------------------------------------------------ */
char  KeysLdr_EraseKeyDB ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_GetKeyControlValue
 * DESCRIPTION:   Calculates the control value of a key. 
 * INPUT:         Standard - the standard determines Key Control Value calculation 
 *                pKeyName - Name of unique Key-Block.
 *                           NULL-terminated or max 8 bytes.
 * OUTPUT:        pKeyControlValue - The calculated Key Control Value.
 * RETURN:        _OK              - Key Control Value is returned OK
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _NOT_SUPPORTED   - Not supported by the Standard
 *                _NOT_FOUND       - Key not found in DB
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * NOTES:         For specific standards, this function is also used to 
 *                retrieve an accumulating Keys Control Value calculation.
 * ------------------------------------------------------------------------ */
char  KeysLdr_GetKeyControlValue (  E_KeysLdr_Std   Standard,
                                    byte           *pKeyName,
                                    byte           *pKeyControlValue    );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_GetKeyVersion
 * DESCRIPTION:   Retrieve the initial version of a Key Block.
 * INPUT:         pKeyName - Name of unique Key-Block.
 *                           NULL-terminated or max 8 bytes.
 * OUTPUT:        pKeyVersion - The initial version of the key.
 * RETURN:        _OK              - Version is returned OK
 *                _NOT_FOUND       - Key not found in DB
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_GetKeyVersion (   byte    *pKeyName,
                                lipver  *pKeyVersion    );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_GetPinPadId
 * DESCRIPTION:   Retrieve the PIN Pad Id, stored in KeyDB.
 * OUTPUT:        *pPINPadId - pointer to buffer with return value.
 *                Note: This buffer must be KEYSLDR_PIN_PAD_ID_SIZE length.
 * RETURN:        _OK              - PIN Pad Id is returned OK
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _KEYDB_CS_ERROR  - PIN Pad Id with wrong Check Sum 
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_GetPinPadId ( byte    *pPINPadId );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_GetSystemKeyControlValue
 * DESCRIPTION:   Calculates the control value of a System Key.
 *                A System Key is unique per terminal. Therefore, it is 
 *                identifiable by its Key Type.
 * INPUT:         SystemKeyType - Type of unique System Key.
 * OUTPUT:        pSystemKeyControlValue - The calculated Key Control Value.
 * RETURN:        _OK              - System Key Control Value is returned OK
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _FOUND           - System Key found in DB
 *                _NOT_FOUND       - System Key not found in DB
 *                _TYPE_ERROR      - System Key Type not valid
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_GetSystemKeyControlValue ( E_EncryptionKeyType    SystemKeyType,
                                         byte                  *pSystemKeyControlValue );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_IsKeyExist
 * DESCRIPTION:   Check if a Key-Block exists in KeyDB.
 * INPUT:         pKeyName - Name of unique Key-Block.
 *                           NULL-terminated or max 8 bytes.
 * RETURN:        _FOUND           - Key found in DB
 *                _NOT_FOUND       - Key not found in DB
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_IsKeyExist ( byte  *pKeyName );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_IsKeyPasswordLocked
 * DESCRIPTION:   Check if a Key Password is locked. 
 * INPUT:         pKeyName    - Name of unique Key-Block.
 *                              NULL-terminated or max 8 bytes.
 * RETURN:        _OK                     - Password is not locked
 *                _KEYDB_LOCKED_PASSWORD  - Password is locked
 *                _NOT_FOUND              - Key not found in DB
 *                _KEYDB_NOT_EXIST        - Key DB not allocated
 *                _NULL_ASSIGNMENT        - NULL given as pointer
 *                _FATAL_ERROR
 * NOTES:         The key maintains a retry counter. After the number of 
 *                unsuccessful retries is equal to or exceeds the maximum number  
 *                of retries associated to the password, it will be locked.
 *                This behavior can be used in accordance with Application 
 *                specific requirements.
 *                If the Retry counter is set to zero by the Application, 
 *                the number of retries will not be limited and the Key Password 
 *                will never be locked.
 * ------------------------------------------------------------------------ */
char  KeysLdr_IsKeyPasswordLocked ( byte   *pKeyName );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_IsSystemKeyExist
 * DESCRIPTION:   Check if a System Key exists in KeyDB.
 *                A System Key is unique per terminal. Therefore, it is 
 *                identifiable by its Key Type.
 * INPUT:         SystemKeyType - Type of unique System Key.
 * RETURN:        _FOUND           - System Key found in DB
 *                _NOT_FOUND       - System Key not found in DB
 *                _TYPE_ERROR      - System Key Type not valid
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_IsSystemKeyExist ( E_EncryptionKeyType    SystemKeyType );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_IsTSPBlockExist
 * DESCRIPTION:   Check if a TSP Block (= Terminal Security Parameters Block) 
 *                exists in the terminal.
 * RETURN:        Boolean value
 * NOTES:         Determine which Default Key Transport Key value has to be used 
 *                when loading an Operative Key Transport Key in Key DB.
 * ------------------------------------------------------------------------ */
boolean  KeysLdr_IsTSPBlockExist ( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_SetPinPadId
 * DESCRIPTION:   Set the input PIN Pad Id, into KeyDB.
 * INPUT:         *pPPID - pointer to buffer with PIN Pad Id value .
 *                Note: This buffer must be KEYSLDR_PIN_PAD_ID_SIZE length.
 * RETURN:        _OK              - PIN Pad Id is set OK
 *                _NULL_ASSIGNMENT - NULL given as pointer
 *                _KEYDB_NOT_EXIST - Key DB not allocated
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_SetPinPadId ( byte    *pPINPadId );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_WriteCipheredKey
 * DESCRIPTION:   Write a new Key-Block to KeyDB. 
 * INPUT:         pNewApplKeyHdr - point to Application-Key-Header struct.
 *                pKeyData       - point to Key-Data struct (see encryptr.def).
 *                KeyDataLen     - sizeof of pKeyData struct.
 * RETURN:        _OK                      - Key written OK
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _KEYDB_NOT_EXIST         - Key DB not allocated
 *                _KEYDB_SIGNATURE_ERROR   - Signature of Key-Block incorrect
 *                _KEYDB_FOUND             - Specific Key-Block found in KeyDB
 *                _KEYDB_DB_FULL           - Key Database is full
 *                _KEYDB_WRITE_ERROR       - Can't write to memory
 *                _KEYDB_DATA_LEN_MISMATCH - Key Data Len does not fit the Key Type
 *                _SECURITY_MISMATCH       - Problem with the Key Transport Key (KTK)
 *                _FATAL_ERROR
 * NOTES:         The Key Data must be 3-DES encrypted by the Key Transport Key.
 * ------------------------------------------------------------------------ */
char  KeysLdr_WriteCipheredKey ( S_KeysLdrApplKeyHdr  *pNewApplKeyHdr,
                                 byte                 *pKeyData,
                                 usint                 KeyDataLen       );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_WriteCipheredKeyWithOp
 * DESCRIPTION:   Write a new Key-Block to KeyDB. 
 *                Performs specific operations, before writing the Key in DB,
 *                according to the input operations parameters.
 * INPUT:         pKeyLdOp - point to Application-Key-Header, and operation params struct.
 * RETURN:        _OK                      - Key written OK
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _KEYDB_NOT_EXIST         - Key DB not allocated
 *                _KEYDB_SIGNATURE_ERROR   - Signature of Key-Block incorrect
 *                _KEYDB_FOUND             - Specific Key-Block found in KeyDB
 *                _KEYDB_DB_FULL           - KeyDB is full
 *                _KEYDB_WRITE_ERROR       - Can't write to memory
 *                _KEYDB_DATA_LEN_MISMATCH - Key Data Len does not fit the Key Type
 *                _NOT_SUPPORTED           - Not supported by the Standard
 *                _WRONG_KEY_CONTROL_VALUE - Wrong Key Control Value
 *                _KEY_ALL_ZERO            - Determine if Key Data is all zeroes
 *                _INVALID_TRANSPORT_KEY   - Transport Key is not valid for that Key
 *                _SECURITY_MISMATCH       - Problem with the Key Transport Key (KTK)
 *                _FATAL_ERROR
 * ------------------------------------------------------------------------ */
char  KeysLdr_WriteCipheredKeyWithOp ( S_KeysLdr_WithOp    *pKeyLdOp );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: KeysLdr_WriteClearKey
 * DESCRIPTION:   Write a new Key-Block to KeyDB.
 * INPUT:         pNewApplKeyHdr - point to Application-Key-Header struct.
 *                pKeyData       - point to Key-Data.
 *                KeyDataLen     - length of pKeyData.
 * RETURN:        _OK                      - Key written OK
 *                _NULL_ASSIGNMENT         - NULL given as pointer
 *                _KEYDB_NOT_EXIST         - Key DB not allocated
 *                _KEYDB_SIGNATURE_ERROR   - Signature of Key-Block incorrect
 *                _KEYDB_FOUND             - Specific Key-Block found in KeyDB
 *                _KEYDB_DB_FULL           - KeyDB database is full
 *                _KEYDB_WRITE_ERROR       - Can't write to memory
 *                _KEYDB_DATA_LEN_MISMATCH - Key Data Len does not fit the Key Type
 *                _SECURITY_MISMATCH       - Functionality disabled in this model
 *                _FATAL_ERROR
 * NOTES:         - This function is not allowed in Secured Terminals.
 *                - The key Data is passed in plain-text. NOT encrypted.
 * ------------------------------------------------------------------------ */
char  KeysLdr_WriteClearKey ( S_KeysLdrApplKeyHdr  *pNewApplKeyHdr,
                              byte                 *pKeyData,
                              usint                 KeyDataLen      );

#ifdef __NOS__
  #include keysldr_nos
#endif

#endif
