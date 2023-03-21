/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * FILE NAME:   GSMRADIO.H                                                 *
 * MODULE NAME: GSMRADIO                                                   *
 * PROGRAMMER:  Hai Shalom                                                 *
 * DESCRIPTION: GSM radio modem.                                           *
 * REVISION:    01.00                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */

 /* Function return values */

#define      GSMRADIO_OK                0
#define      GSMRADIO_FAIL             -1
#define      GSMRADIO_NO_MEM           -2
#define      GSMRADIO_TIMEOUT          -3
#define      GSMRADIO_PIN_NEEDED       -4
#define      GSMRADIO_WAIT             -6

#define      GSM_RI_POPUP_LEN          33      /* Length of popup string for ring action */
#define      GSM_SIM_POPUP_LEN         33      /* Length of popup string for SIM Card action */
#define      GSMRADIO_VOLUME_LOWEST    30      /* Lowest volume */
#define      GSMRADIO_VOLUME_HIGHEST   50	   /* Highest volume */

#define      GSM_OPTIONS_STRUCT_VER_1   1

                /* ======================================= *
                 *     T Y P E   D E C L A R A T I O N     *
                 * ======================================= */

/*   Ring indication action structure       */

/* NOTE : The field PopupWindow contorls    */
/*        the action to be taken by the     */
/*        NOS, if this field is FALSE the   */
/*        rest of the fields of this        */
/*        structure has no meaning and are  */
/*        not used. If this field is TRUE   */
/*        the rest of the structure is used */
/*        by the NOS.                       */

typedef struct 
{
  boolean PopupWindow;             /* Display pop up window ? */
  boolean RingSpeaker;             /* Sound speaker on ring ? */
  byte    AnswerKey;               /* Answer key              */
  byte    DisconnectKey;           /* Disconnect key          */
  char    Msg[ GSM_RI_POPUP_LEN ]; /* Message to be displayed */
                                   /* on popup window         */
} GSMRIActionType;

typedef struct 
{
  boolean PopupWindow;             /* Display pop up window ? */
  boolean RingSpeaker;             /* Beep speaker ?          */
  char    Msg[ GSM_SIM_POPUP_LEN ];/* Message to be displayed */
                                   /* on popup window         */
} GSMSIMCardActionType;

typedef struct 
{
   ulint   OperatorID;   /* currently selected operator's numeric represntation */
   char    OperLongName[18];  /* currently selected operator's long name */
   char    OperShortName[10];  /* currently selected operator's short name */
      
} OperatorInfo;

typedef packed struct 
{
   /* sizeof (GSMStatistics) = 64                                        */
   usint Size;               /* Size of this structure as input          */
                             /* Must be filled by appl as actual size!!  */
   usint LastConnectTime;    /* Last connect time in seconds             */
   usint ConnectOK;          /* Num. of successful Connections           */
   usint NoDialTone;         /* No dial tone counter                     */
   usint NoCarrier;          /* No carrier counter                       */
   usint Busy;               /* Busy counter                             */
   usint NoAnswer;           /* No answer counter                        */
   usint SMSTxOK;            /* Num. of successful SMS submits      (Tx) */
   usint SMSRxOK;            /* Num. of successful SMS deliveries   (Rx) */
   usint SMSTxErr;           /* Num. of UNsuccessful SMS submits    (Tx) */
   usint SMSRxErr;           /* Num. of UNsuccessful SMS deliveries (Rx) */
   usint USSDTxOK;           /* USSD send o.k. counter                   */
   usint USSDRxOK;           /* USSD receive o.k. counter                */
   usint USSDTxErr;          /* USSD send failed counter                 */
   usint USSDRxErr;          /* USSD receive failed counter              */
   usint NoNetwork;          /* No network coverage counter              */
   byte  LastConnectRate;    /* Last dialup call rate(as in GSMRADIO.PRM)*/
   byte  SIMError;           /* SIM errors counter                       */
   byte  PIN1Required;       /* PIN 1 was needed by SIM counter          */
   byte  PUK1Required;       /* PUK 1 was needed by SIM counter          */
   byte  PIN2Required;       /* PIN 2 was needed by SIM counter          */
   byte  PUK2Required;       /* PUK 2 was needed by SIM counter          */
   byte  ModemFatalErr;      /* Modem Fatal Errors counter               */
   byte Reserved[25];        /* Reserved for future usage                */ 
   
}GSMStatistics;

typedef struct 
{
   usint   AreaCode;   /* Current location area code (hex format) */
   usint   CellID;     /* Current cell ID (hex format)            */
      
} LocationInfo;

typedef enum
{
  OPER_UNKNOWN = 0,
  OPER_AVAILABLE,
  OPER_CURRENT,
  OPER_FORBIDDEN,

} OperatorStatus;

typedef struct 
{
   OperatorInfo    Operator;   /* Operator information */
   OperatorStatus  Status;     /* Operator status: See OperStatus */

} OperatorList;

typedef enum
{
  LOGIN_DEFAULT = 0,
  LOGIN_NONE,
  LOGIN_PAP,
  LOGIN_CHAP,
  LOGIN_PAP_CHAP,

} LoginScriptType;

typedef struct 
{
   usint            StructVer;  /* Structure version */
   LoginScriptType  Login;      /* Login script type */

} GSMOptionsStruct;


                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_VoiceRIDisable
 *
 * DESCRIPTION:   Disables ring indication detection of voice calls
 *
 * PARAMETERS:    none.
 *
 * RETURN:        void.
 *
 * NOTES:         none
 * ------------------------------------------------------------------------ */
void GSMRadio_VoiceRIDisable(void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_VoiceRIEnable
 *
 * DESCRIPTION:   Enables the ring indication for incoming voice calls
 *
 * PARAMETERS:    Size   - Size of Ring Indiaction action struture
 *                Action - Pointer to action structure. This structure
 *                         informs the NOS what actions to take upon
 *                         detecting an incoming call 
 *                         
 *                         see GSMRIActionType definition for field definitions.
 *
 * RETURN:        Void.
 *
 * NOTES:         The field PopupWindow in the GSMRIActionType structure 
 *                contorls the action to be taken by the NOS, if this field 
 *                is FALSE the rest of the fields of this structure has no 
 *                meaning and are not used. If this field is TRUE the rest 
 *                of the structure is used by the NOS.
 *
 * ------------------------------------------------------------------------ */
void GSMRadio_VoiceRIEnable(usint Size , const GSMRIActionType * Action);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_VoiceAnswer
 *
 * DESCRIPTION:   Answer an incoming voice call. opens all the audio channels
 *                and "picks up" the receiver.
 *
 * PARAMETERS:    none.
 *
 * RETURN:        Void.
 *
 * NOTES:         None
 * ------------------------------------------------------------------------ */
void GSMRadio_VoiceAnswer( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_SIMCardAction
 *
 * DESCRIPTION:   Selects action to take when there is no SIM card present.
 *
 * PARAMETERS:    Size   - Size of Ring Indiaction action structure
 *                Action - Pointer to action structure. This structure
 *                         informs the NOS what actions to take upon
 *                         detecting there is no SIM card present. 
 *
 * RETURN:        Void.
 *
 * NOTES:         None
 * ------------------------------------------------------------------------ */
void GSMRadio_SIMCardActionType( usint Size, const GSMSIMCardActionType *Action );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMTest_RadioToPC
 * DESCRIPTION:   Radio will be connected to PC port.
 * PARAMETERS:    Timeout - Timeout of connection (in seconds) / 0 no timeout 
 * RETURN:        none,
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void GSMTest_RadioToPC(ulint Timeout);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetSIMLockState
 * DESCRIPTION:   Queries SIM's lock status.
 * PARAMETERS:    (output)State to write the state to 
 *                (TRUE if locked FALSE otherwise).
 * RETURN:        GSMRADIO_OK   - Command was executed successfully.
 *                GSMRADIO_FAIL - Command failed.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
sint GSMRadio_GetSIMLockState(boolean *State);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_CheckMessageNow
 * DESCRIPTION:   Check for new messages
 * RETURN:        none
 * NOTES:         The function will return if the interval from last call,
 *                is less than 750ms or radio not in idle state
 * ------------------------------------------------------------------------ */
void GSMRadio_CheckMessageNow( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetLocationInfo
 * DESCRIPTION:   returns location information: Area code and Cell ID.
 * PARAMETERS:    Loc - (output) pointer to LocationInfo structure.
 * RETURN:        GSMRADIO_OK   - info been retreived successfully.
 *                GSMRADIO_FAIL - radio off or location info not available
 * ------------------------------------------------------------------------*/
sint GSMRadio_GetLocationInfo( LocationInfo* Loc );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_SetSIMLockState
 * DESCRIPTION:   Locks/unlocks SIM card
 * PARAMETERS:    (input) LOCK = TRUE, UNLOCK = FALSE
 *                
 * RETURN:        GSMRADIO_OK   - Command was executed successfully.
 *                GSMRADIO_FAIL - Command failed.
 *                GSMRADIO_PIN_NEEDED - if PIN needed by application.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
sint GSMRadio_SetSIMLockState(boolean Lock);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetOperators
 * DESCRIPTION:   Gets all the available operators
 * PARAMETERS:    (output) Oprators list, must be an array of OperatorList,
 *                (input) The size of the list (output) Total operators in list
 *                
 * RETURN:        GSMRADIO_OK   - Command was executed successfully.
 *                GSMRADIO_FAIL - Command failed.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
sint GSMRadio_GetOperators( OperatorList List[], byte *ListSize );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_SetOperator
 * DESCRIPTION:   Set the active operator to the requested one.
 * PARAMETERS:    (input) Operator ID.
 *                
 * RETURN:        GSMRADIO_OK   - Command was executed successfully.
 *                GSMRADIO_FAIL - Command failed.
 * NOTES:         OK Return code does not guaranty that the operator has
 *                changed to the requested one. The application must check
 *                this by calling GSMRadio_GetOperators function.
 * ------------------------------------------------------------------------*/
sint GSMRadio_SetOperator( ulint OperatorID );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_ChangePIN
 * DESCRIPTION:   Changes SIM's PIN.
 * PARAMETERS:    (input)new PIN between 4 to 8 characters.(NULL char excluded)
 * RETURN:        GSMRADIO_OK   - Command was executed successfully.
 *                GSMRADIO_FAIL - Command failed.
 *                GSMRADIO_PIN_NEEDED - if PIN needed by application.
 * NOTES:         SIM PIN could only be changed when SIM is locked.
 * ------------------------------------------------------------------------*/
sint GSMRadio_ChangePIN(char* NewPin);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetCardID
 * DESCRIPTION:   Returns Card ID
 * PARAMETERS:    CardID - (output) pointer to char array.
 *                Size   - Max Size of CardID
 * RETURN:        GSMRADIO_OK   - Info has been retreived successfully.
 *                GSMRADIO_FAIL - Error with pointers or command failure
 *                GSMRADIO_WAIT - Radio is not initialized yet
 * NOTES:         Max Size will be 32 bytes.
 * ------------------------------------------------------------------------*/
sint GSMRadio_GetCardID( char *CardID , usint Size );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetCallerID
 * DESCRIPTION:   returns Caller ID
 * PARAMETERS:    CallerID - (output) pointer to char array.
 *                Size     - Max Size of CardID
 * RETURN:        GSMRADIO_OK   - info been retreived successfully.
 *                GSMRADIO_FAIL - radio off or no ring indication.
 * NOTES:         - If output is NULL, number is restricted.
 *                - Max Size will be 32 bytes.
 * ------------------------------------------------------------------------*/
sint GSMRadio_GetCallerID( char *CallerID , usint Size );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetLastError
 * DESCRIPTION:   Writes the last error string received by the modem.
 * PARAMETERS:    (input)Size = the size of user's buffer.
 *                (output)ErrStr = pointer to buffer to write response to.
 * RETURN:        None
 * NOTES:         if Size is smaller then the error string the error string
 *                will be trimmed.
 * ------------------------------------------------------------------------*/
void GSMRadio_GetLastError(char* ErrStr, usint Size);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetCurrentOperator
 * DESCRIPTION:   returns the currently selected operator's name and ID.
 * PARAMETERS:    (output) structure to hold the info
 * RETURN:        GSMRADIO_OK   - info been retreived successfully.
 *                GSMRADIO_FAIL - no info.
 * NOTES:         None.
 * ------------------------------------------------------------------------*/
sint GSMRadio_GetCurrentOperator(OperatorInfo* Info);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_RejectCall
 * DESCRIPTION:   Rejects a call (Busy sound)
 * PARAMETERS:    None.
 * RETURN:        GSMRADIO_FAIL in case of no ring indication
 *                GSMRADIO_OK if call was rejected.
 * NOTES:         None.
 * ------------------------------------------------------------------------*/
sint GSMRadio_RejectCall( void );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_SetVolumeLevel
 * DESCRIPTION:   Set volume level.
 * PARAMETERS:    Level of volume in range of 0-10
 *                or GSMRADIO_VOLUME_LOWEST for lowest volume possible
 *                or GSMRADIO_VOLUME_HIGHEST for highest volume possible                 
 * RETURN:        GSMRADIO_OK   - Command was executed successfully.
 *                GSMRADIO_FAIL - Command failed.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
sint GSMRadio_SetVolumeLevel( byte Level );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_GetStatistics
 * DESCRIPTION:   Retrieves the GSM communication statistics
 *                and resets all the counters to zero if indicated by the user.
 * PARAMETERS:    GS - (Output) pointer to a GSMStatistics structure.
 *                ResetFlag - TRUE  : Resets to zero all counters.
 *                            FALSE : Leaves counters untouched.
 * RETURN:        None.
 *
 * NOTES:         None.
 * ------------------------------------------------------------------------*/
void GSMRadio_GetStatistics(GSMStatistics* GS, boolean ResetFlag);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: GSMRadio_SetRadioOptions
 * DESCRIPTION:   Set a variety of options in the GSM module
 * RETURN:        GSMRADIO_OK on success or GSMRADIO_FAIL if failed.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
sint GSMRadio_SetRadioOptions( GSMOptionsStruct *Options );

#ifdef __NOS__
  #include gsmradio_nos
#endif
