/****************************************************************************
 *                                                                          *
 * FILE NAME:   ComHndlr.h                                                  *
 *                                                                          *
 * MODULE NAME: ComHndlr                                                    *
 *                                                                          *
 * PROGRAMMER:  Avishai                                                     *
 *                                                                          *
 * DESCRIPTION: dialer and radio/modem shell                                *
 *                                                                          *
 * REVISION:    01_10   01/07/94                                            *
 *                                                                          *
 * HISTORY:     01_00 - Original.                                           *
 *              01_01 - new parameters.                                     *
 *              01_10 - ComHndlr_Rx and ComHndlr_Tx are changed to be       *
 *                      foregroung functions (i.e. the program stays in a   *
 *                      loop there).                                        *
 *                    - ComHndlr_Rx finds STX, ETX etc.                     *
 *              01_11 - some small changes.                                 *
 *              01_12 - in ComHndlr_RxLine, purge garbage before STX...     *
 *              01_13 - _RadioOn and _RadioOff were added.                  *
 *                                                                          *
 ****************************************************************************/

#include comhndlr_def

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

               /* call1 and call2 return values */

#define SWITCHED_TO_RADIO  1
#define CONNECTED_LINE     2
#define FAIL_CONNECT       3
#define FAIL_NO_PARAM      4
#define FAIL_WRONG_INPUT   5
#define USER_BREAK         6
#define NOT_FINISHED_YET   7
#define CONNECTED_LINE_LOGON_PROTOCOL  8
#define SWITCHED_TO_CDPD   9  /* not return value!!!, used in application */
#define TIMEOUT_UNTIL_FH               60000
#define LINE_DISCONNECTED  11
#define COMHNDLR_NO_SUPPORT 12

                   /* Rx and Tx return values */

#define X_OK                      0
#define X_MAX_LENGTH              0
#define X_TIMEOUT                -1
#define X_BAD_INPUT              -2
#define X_ESC_PRESSED            -3
#define X_RADIO_BUFFER_TOO_BIG   -4
#define X_UART_ERROR             -5
#define X_NOT_SWITCHED_TO_RADIO  -6
#define X_NOT_SWITCHED_TO_MODEM  -7
#define X_DIAL_UP_PRESSED        -8
#define X_MSG_RETURNED           -9
#define X_NEW_MSG                -10
#define X_NO_MSG                 -11
#define X_LINE_DISCONNECTED      -12
#define X_SYNC_NOT_ALLOWED       -13
#define X_NOTHING_RECEIVED       -14
#define X_OK_DATA_RCV            -15
#define X_FAILURE                -16

/* New NS Turkey errors */
#define X_TRANSFER_ERROR         -17
#define X_CONGEST_ERROR          -18
#define X_NETWORK_BUSY           -19

/* New HDLC (China) errors */
#define X_RCV_BUSY              -20
#define X_HDLC_RESTARTED        -21


/* Synchronous communications ComHndlr_WaitForSyncCall definitions */
#define SYNC_SECONDARY 0
#define SYNC_PRIMARY   1

/* ComHndlr ConnectAutoAnswer input parameters */
#define SYNC_HDLC485   2
#define SYNC_HDLC      1
#define UART_COMM      0


#define CCITT_FAST_CONNECT       0x01
#define HYPERCOM_FAST_CONNECT    0x03


#define MAX_COND  6   /* max. number of conditions in RxLineConditionsType */


/* Auto Answer Mode return values */
#define AA_DURING_CONNECT     0
#define AA_WAIT_FOR_RING      1
#define AA_CONNECTED          2
#define AA_DISCONNECT         3
#define AA_HDLC_FAIL          4
#define AA_CHANGE_BAUD_300    300
#define AA_CHANGE_BAUD_1200   1200
#define AA_CHANGE_BAUD_2400   2400


/* RBM (Radio BkGr Msg utility) : */

#define RBM_BAD_RECORD_SIZE       -201  /* Rec size out of boundries */
#define RBM_DURING_A_CALL         -202  /* between _Call to _EndCall. */
#define RBM_NOT_ENOUGH_DISK_SPACE -203  /* too many record requested. */
#define RBM_WRONG_INPUT           -204  /* if prm (_ActivateBkGrMsg)
					   is not 0. */
#define RBM_NOT_SUPPORTED         -205  /* NOS system without RBM utility.*/


#define MASC_NORMAL_DATA           0
#define MASC_HP_DATA               1

/* GSM/AMPS Driver modes */

#define COMHNDLR_RADIO_DRV_ENABLE     1
#define COMHNDLR_RADIO_DRV_DISABLE    0

/* Dial mode set options */
#define BREAK_MODE_CLEAR_DISABLE      22

	  /*==========================================*
	   *      T Y P E   D E C L A R A T I O N     *
	   *==========================================*/

typedef struct
{
   byte wanted_char;    /* e.g. STX, ETX, NAK etc. */
   byte pre;       /* number of wanted bytes BEFORE wanted_char. 255 = ALL */
   byte post;      /* number of wanted bytes AFTER  wanted_char. 255 = ALL */
} OneConditionType;


typedef struct
{

   ulint timeout;    /* in mSec.    when timeout    acceded, return anyway */
   usint max_length;             /* when max_length acceded, return anyway */
   byte  num_of_conditions;      /* number of conditions                   */
   OneConditionType OneCondition[MAX_COND];
                           /* when one of these conditions is o.k., return */
} RxLineConditionsType;

typedef packed enum
{
  RADIO_NOT_EXIST,
  RADIO_OFF,      /* Radio OFF*/
  RADIO_NOT_READY,/* Radio ON, but not ready */
  RADIONET_OFF,   /* Radio ON, Radio Network OFF */
  RADIONET_DISABLE, /* Radio ON, Network is disable(Die mode) - for MASC only */
  RADIO_READY,    /* Radio ON, Radio Network ON (and enable for MASC)*/
  RADIO_CONNECTED,/* Radio connected to network (after ATD) - for CDPD only */
  RADIO_SEND,     /* Radio ON, Radio Network ON, Send mode */
  RADIO_REC,      /* Radio ON, Radio Network ON, Recieve mode */
  RADIO_SEND_REC,  /* Radio ON, Radio Network ON, Send&Recieve mode */
  RADIONET_REGISTERING,    /* Radio ON Registering to Network - GSM Only             */
  RADIO_SIM_ERROR,         /* No SIM card or SIM failure - GSM Only                  */
  RADIO_SIM_PIN_NEEDED,    /* PIN required - GSM Only                                */
  RADIO_SIM_PUK_NEEDED,    /* PUK required - GSM Only                                */
  RADIO_SIM_PH_SIM_NEEDED, /* PH_SIM PIN required - GSM Only                         */
  RADIO_SIM_PIN2_NEEDED,   /* PIN2 required - GSM Only                               */
  RADIO_SIM_PUK2_NEEDED,   /* PUK2 required - GSM Only                               */
  RADIO_RING               /* Indicates that an incoming voice call is ringing       */
} RadioConnectType;

typedef packed enum
{
 NO_RADIONETWORK,
 MOBITEX_NETWORK,
 CDPD_NETWORK,
 NATIVE_NETWORK,
 GSM_NETWORK,
 AMPS_NETWORK,
 WIFI_NETWORK
}RadioNetType;

typedef packed struct
{
  RadioNetType            NetType;
  RadioConnectType        ConnectStatus;
  char                   *RadioSelfId;  /* MAN for MASC, Self IP for CDPD*/
  usint                   Rssi;     /* 0 is min., 50 is max. for MASC */
  usint                   Channel;  /* Base Station for MASC, channel for CDPD*/
}RadioDescrStr;

typedef struct
{
   char  ManName[32];
   char  ModelName[48];
   char  SerialNum[32];
   char  DeviceID[32];
   char  SWVer[48];
   byte  Reserved[64];        /* Reserved for future usage   */

} RadioInfoStruct; /* device info */

/* Type of short messages */

typedef enum {

  COMHNDLR_RADIO_MSG_SMS_TXT,          /* GSM SMS Text message  */
  COMHNDLR_RADIO_MSG_USSD_TXT,         /* GSM USSD Text message */
  COMHNDLR_RADIO_MSG_SMS_PDU           /* GSM SMS PDU message   */

} RadioMsgType;

/* Type of destination address */

typedef enum {

  COMHNDLR_RADIO_ADDR_INDEX  ,          /* Address is an index into targets block */
  COMHNDLR_RADIO_ADDR_TARGET            /* Address point to a target blcok        */

} RadioAddrType;

/* Type of message file appending mode */

typedef enum {

  COMHNDLR_MSG_FILE_OVER   ,            /* Message file will be overwritten       */
  COMHNDLR_MSG_FILE_APPEND ,            /* New messages will replace old messages */
  COMHNDLR_MSG_FILE_BLOCK               /* Old messages will not be deleted       */

} FileMsgType;

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_ChangeParam
 *
 * DESCRIPTION:   Sets new parameters (from application).
 *
 * RETURN:        void
 *
 * NOTES:         1.The input is 3 pointers to structures.
 *                2.The structures must not be static.
 *                3.If ComHndlrParam_p1==NULL, the function uses default
 *                  parametrs.
 *                4.If RadioParam_p1==NULL, the radio communication
 *                  will desable.
 *                5.Only one parameter block is allow for Dial Target pointer
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_ChangeParam
   ( DialTargetType    *DialTarget_p1,
     ComHndlrParamType *ComHndlrParam_p1,
     RadioParamType    *RadioParam_p1);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_AfterLoad
 *
 * DESCRIPTION:   Takes new parameters from parameters memory.
 *
 * RETURN:        void
 *
 * NOTES:         Called by Main_AfterLoad after new parameters has been
 *                loaded.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_AfterLoad (void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetupRadio
 *
 * DESCRIPTION:   Setup specific radio parameters. The parameters are radio model
 *                dependent and it is assumed that the application is aware of
 *                the parameters and their structure.
 *
 *                For GSM radio the parameters are defined in the file GSMRADIO.PRM
 *                and the parameters structure is GSMRadioParamStruct.
 *
 * PARAMETERS:    RadioParams - Pointer to radio setup parameters
 *                Size        - Size of the radio setup parameters structure
 *
 * RETURN:        COMHNDLR_NO_SUPPORT - The radio does not support params setup
 *                FAIL_WRONG_INPUT    - Setup parameters are invalid.
 *                FAILURE             - Failure while setting parameters.
 *                OK                  - Parameters set o.k.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_SetupRadio(void *RadioParams,usint Size);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_GetRadioInfo
 *
 * DESCRIPTION:   Retrieves the underlying radi device information
 *                such as model,id, software version, manufacturer.
 *
 *
 * PARAMETERS:    RadioInfo(output)   - Pointer to structure for holding
 *                                      the info.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_GetRadioInfo(RadioInfoStruct *RadioInfo);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_DialShow
 *
 * DESCRIPTION:   Set mode of dialing number show: ON or OFF.
 *
 * RETURN:        void.
 *
 * NOTES:         This mode uses for dialing by dial target only!
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_DialShow (byte ShowMode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_CallModeSet
 *
 * DESCRIPTION:   Set the call mode by user parameters:
 *                      1 - dialing number show: ON or OFF.
 *                      2 - user break enable: ON, OFF or BREAK_MODE_CLEAR_DISABLE.
 *                          OFF: user can not interrupt the dial process.
 *                          ON: user can interrupt the process by pressing the
 *                              Break Key or CLEAR (The break key can be CLEAR).
 *                          BREAK_MODE_CLEAR_DISABLE: User can interrupt the
 *                              process by pressing the Break Key only
 *                              (CLEAR button is disabled, the break key can not be CLEAR).
 *                      3 - key for user break: MENU,CLEAR or other key.
 *
 * RETURN:        void.
 *
 * NOTES:         if the function was called during communication
 *                between CALL to END, the BreakMode and BreakKey will
 *                be used in current and next communications until they will
 *                be changed.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_DialModeSet (byte ShowMode,byte BreakMode,byte BreakKey);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_CallDirectRadio
 *
 * DESCRIPTION:   Initiate a call by a radio. (CDPD Or MASC)
 *
 * PARAMETERS:    RadioTarget - Pointer to radio parameters structure
 *
 *                For CDPD - Pointer to AtTargetParamStruct, Type is dummy.
 *                For MASC - Pointer to RadioParamType
 *
 * RETURN:        SWITCHED_TO_RADIO/FAIL_CONNECT
 *                /FAIL_WRONG_INPUT/USER_BREAK
 *
 *                X_DIAL_UP_PRESSED
 *
 * NOTES:         Use call type parameter. Can be MASC_NORMAL_DATA and
 *                MASC_HP_DATA
 *
 * ------------------------------------------------------------------------ */
usint ComHndlr_CallDirectRadio (void *RadioTarget ,byte Type);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_PreDialRadioBkgr
 *
 * DESCRIPTION:   establish connection in background
 *                this function will begin a foreground process which will
 *                bring to the connection of the terminal through a radio
 *                line, to an external modem. It must be called only ONCE
 *                and then it will start running by itself!
 *                When it's time to communicate user must call
 *                ComHndlr_PreDialForegrnd() inorder to continue communcations
 *                process or learn about connection status.
 *                You can use ComHndlr_GetRadioStatus for to know connect status
 *                and to call ComHndlr_PreDialForegrnd() after RADIO_CONNECTED.
 *
 * RETURN:        TRUE if process is on the way, FAIL_CONNECT if error occured.
 *
 * NOTES:         If error occured user must call for foreground call.
 *                See ComHndlr_PreDialForegrnd before writing code!
 *                Use for GSM or CDPD radio only!!!
 *
 * ------------------------------------------------------------------------ */
usint ComHndlr_PreDialRadioBkgr (void *RadioTarget ,byte Type);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RadioSendMessage
 *
 * DESCRIPTION:   Sends a messages through the short message mechanism of the
 *                radio driver
 *
 * PARAMETERS:    MsgType  - Type of message to send
 *                AddrType - Type of destination address
 *                Addr     - Pointer to destination address
 *                Msg      - Pointer to message
 *                Size     - Size of message
 *                TimeOut  - Send message timeout in milliseconds
 *
 * RETURN:        OK               - Message was sent succesfully
 *                FAIL_WRONG_INPUT - Wrong arguments given to function
 *                FAILURE          - Can not send message
 *                X_TIMEOUT        - Timeout has expired before succesful
 *                                   sending of the message
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RadioSendMessage(RadioMsgType MsgType , RadioAddrType AddrType ,
                               void * Addr , byte * Msg , usint Size , ulint TimeOut);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RadioEnableRxMessages
 *
 * DESCRIPTION:   Enables receiving messages in the background from the
 *                radio modem. The messages are stored in a file and
 *                later can be read by the application.
 *
 * PARAMETERS:    MsgType   - Type of messages to receive
 *                FileName  - File name to put messages in
 *                MaxMsg    - Maximum messages to append to the file
 *                Mode      - Mode flag :
 *
 *                            COMHNDLR_MSG_FILE_OVER   - Overwrite records in the message file.
 *                            COMHNDLR_MSG_FILE_APPEND - Append message to end of file and delete
 *                                                       the oldest record.
 *                            COMHNDLR_MSG_FILE_BLOCK  - Append messages to the file until MaxMsg
 *                                                       messages have arrived and stop appending.
 *
 * RETURN:        OK               - Receving message was enabled
 *                FAIL_WRONG_INPUT - Wrong arguments given to function
 *                FAILURE          - Can not enabled message receiving
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RadioEnableRxMessages(RadioMsgType MsgType , const char * FileName , usint MaxMsg ,
                                    FileMsgType Mode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RadioDisableRxMessages
 *
 * DESCRIPTION:   Disable given messages receiving
 *
 * PARAMETERS:    MsgType          - Type of messages to disable receiving
 *
 * RETURN:        OK               - Receving message was disabled
 *                FAIL_WRONG_INPUT - Wrong arguments given to function
 *                FAILURE          - Can not disable message receiving
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RadioDisableRxMessages(RadioMsgType MsgType);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_Call1
 *
 * DESCRIPTION:   Initiate a call using index to dial targets in parameters.
 *
 * RETURN:        SWITCHED_TO_RADIO/CONNECTED_LINE/FAIL_CONNECT/FAIL_NO_PARAM
 *                /FAIL_WRONG_INPUT/CONNECTED_LINE_LOGON_PROTOCOL
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_Call1 (usint target_index,
                     boolean force_line   /* TRUE = force line */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_Call2
 *
 * DESCRIPTION:   Initiate a call using the parameters in the input structure.
 *
 * RETURN:        SWITCHED_TO_RADIO/CONNECTED_LINE/FAIL_CONNECT/
 *                FAIL_WRONG_INPUT/USER_BREAK/CONNECTED_LINE_LOGON_PROTOCOL
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
usint ComHndlr_Call2 (DialTargetType *DialTarget);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_TxLine
 *
 * DESCRIPTION:   Transmits data via telephone line.
 *                Waits until there is enough room in transmit buffer or
 *                until timeout.
 *
 * RETURN:        X_OK      - data transmitted o.k.
 *                X_TIMEOUT - exit on timeout.
 *                X_ESC_PRESSED - break by user.
 *                X_NOT_SWITCHED_TO_MODEM - we are not switched to modem.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_TxLine (byte *buf, usint length);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_TxHdlc
 *
 * DESCRIPTION:   Transmits data via telephone line through HDLC sync comm.
 *
 * RETURN: X_OK          - data transmitted o.k.
 *         X_RCV_BUSY    - no free frame,buffer was not taken,wait
 *         X_NOT_SWITCHED_TO_MODEM - not switched to modem or no carrier
 *         X_UART_ERROR  - critical problem.
 *         X_SYNC_NOT_ALLOWED - requested sync mode when not available
 * NOTES:         Uses timeout from ComHndlr parameters.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_TxHdlc (byte *buf, usint length);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_TxHdlcWithAck
 *
 * DESCRIPTION:   Transmits data via telephone line through HDLC sync comm.
 *                Waits until there is enough room in transmit buffer or
 *                until timeout. Does not return until the frame was acked
 *                by PRIMARY HOST.
 *
 *  ~~~~~~~~  timeout - in seconds   ~~~~~~~~
 *
 * RETURN: X_OK          - data transmitted o.k.
 *         X_TIMEOUT     - exit on timeout.
 *         X_ESC_PRESSED - break by user.
 *         X_UART_ERROR  - critical problem.
 *         X_NOT_SWITCHED_TO_MODEM - we are not switched to modem.
 *         X_SYNC_NOT_ALLOWED - requested sync mode when not available
 *
 * NOTES:         Uses timeout from ComHndlr parameters. The timeout is for the
 *                whole process.
 * ------------------------------------------------------------------------ */
sint ComHndlr_TxHdlcWithAck (byte *buf, usint length, usint timeout);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_TxRadio
 *
 * DESCRIPTION:   transmits data via radio
 *                Waits until there is enough room in transmit buffer or
 *                until timeout.
 *
 * RETURN:        X_OK  - data transmitted o.k.
 *                X_TIMEOUT - exit by timeout.
 *                X_ESC_PRESSED - break by user.
 *                X_RADIO_BUFFER_TOO_BIG - Too much Data (radio)
 *                X_NOT_SWITCHED_TO_RADIO - we are not switched to radio.
 *                X_NO_MSG - tx message is out on the air and no message was
 *                           received.
 *                X_NEW_MSG - new message is present in rx buffer - go and take it out
 *                X_MSG_RETURNED - the message in the Mpak buffer is the message
 *                                 returned by the radio.
 *
 *
 * NOTES:         Uses timeout from ComHndlr parameters.
 *                This is the function called by the application for sending
 *                a text message to the MOBITEX network.
 *                the parameter time_out - the number of miliseconds to wait
 *                until system is sure that message is out on the AIR or
 *                transmitted message was returned (or another message
 *                received)
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_TxRadio (byte *buf, usint *length);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RxRadioOrLine
 *
 * DESCRIPTION:   Receives data from telephone line or CDPD radio.
 *                Waits until received data satisfy one of n conditions (that
 *                were described in the input structure)
 *                or until timeout,
 *                or until max. length acceded.
 *
 * RETURN:
 *                X_UART_ERROR  - critical problem in uart.
 *                X_NOT_SWITCHED_TO_MODEM - we are not switched to modem.
 *                X_NOT_SWITCHED_TO_RADIO - we are not switched to modem.
 *                X_ESC_PRESSED (-3) - break by user.
 *                X_BAD_INPUT   (-2) - error in the input structue or in any
 *                                     other input.
 *                X_TIMEOUT     (-1) - exit on timeout.
 *                X_MAX_LENGTH  ( 0) - max. length acceded.
 *                1                  - exit on condition #1.
 *                2                  - exit on condition #2.
 *                .                   .
 *                .                   .
 *                .                   .
 *
 * NOTES:         In the conditions structure there are also timeout and
 *                max. length (both of them are inputs).
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RxRadioOrLine(RxLineConditionsType *RxLineConditions,
							 /* end conditions */
		      byte **buf,        /* in  - pointer to output buffer */
					 /* out - pointer to output buffer */
					 /* showing where from wanted data */
					 /* starts.                        */
		      usint *actual_length,
					 /* actual length of received data */
					 /* IMPORTANT: this is the length  */
					 /* is measured from the returned  */
					 /* *buf, not from the input *but. */
            byte  RadioWork   /* if 0, works with line */
		     );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RxConditions
 *
 * DESCRIPTION:   Receives data from telephone line or CDPD radio.
 *                Waits until received data satisfy one of n conditions (that
 *                were described in the input structure)
 *                or until timeout,
 *                or until max. length acceded.
 *
 * RETURN:
 *                X_UART_ERROR  - critical problem in uart.
 *                X_NOT_SWITCHED_TO_MODEM - we are not switched to modem.
 *                X_NOT_SWITCHED_TO_RADIO - we are not switched to modem.
 *                X_ESC_PRESSED (-3) - break by user.
 *                X_BAD_INPUT   (-2) - error in the input structue or in any
 *                                     other input.
 *                X_TIMEOUT     (-1) - exit on timeout.
 *                X_MAX_LENGTH  ( 0) - max. length acceded.
 *                1                  - exit on condition #1.
 *                2                  - exit on condition #2.
 *                .                   .
 *                .                   .
 *                .                   .
 *
 * NOTES:         In the conditions structure there are also timeout and
 *                max. length (both of them are inputs).
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RxConditions (RxLineConditionsType *RxLineConditions,
							 /* end conditions */
		      byte **buf,        /* in  - pointer to output buffer */
					 /* out - pointer to output buffer */
					 /* showing where from wanted data */
					 /* starts.                        */
		      usint *actual_length
					 /* actual length of received data */
					 /* IMPORTANT: this is the length  */
					 /* is measured from the returned  */
					 /* *buf, not from the input *but. */
		     );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RxHdlc
 *
 * DESCRIPTION:  This function receives a frame from the HDLC Z8530
 *               port and transfers it to the upper level.
 *               Inputs:
 *                 buf - pointer to receive buffer;
 *                 *length - max.size of receive buffer;
 *                 time_out - in seconds
 *
 * RETURN:
 *                X_TIMEOUT     (-1) - exit on timeout.
 *                X_UART_ERROR       - lower levels collapsed
 *                X_ESC_PRESSED      - user break.
 *                X_HDLC_RESTARTED   - HDLC session was restarted before
 *                                     ACK for all transmitted frames.
 *                X_BAD_INPUT        - Unknown error.
 *                X_LINE_DISCONNECT  - modem line is disconnected
 *                > 0                - length of frame copied into buf
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RxHdlc( byte *buf, usint *length, ulint time_out);




/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RxLineDirect
 *
 * DESCRIPTION:   Receives data directly from telephone line.
 *
 * RETURN:        buf length or X_NOT_SWITCHED_TO_MODEM if no CARRIER
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

sint ComHndlr_RxLineDirect (byte *buf, usint len);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RxRadio
 *
 * DESCRIPTION:   Receives data from radio.
 *                Waits until data received or until timeout.
 *
 * RETURN:        X_OK  - data received o.k.
 *                X_TIMEOUT - exit by timeout.
 *                X_ESC_PRESSED - break by user.
 *                X_NOT_SWITCHED_TO_RADIO - we are not switched to radio.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RxRadio (
                    byte  *buf,      /* pointer to data buffer             */
                    usint *buf_size, /* in - buffer size for received data */
                                     /* out - acctual received data size   */
                    ulint timeout    /* timeout in mSec.                   */
                );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_EndCall
 *
 * DESCRIPTION:   ^
 *
 * RETURN:        void
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

void ComHndlr_EndCall (void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RadioOn
 *
 * DESCRIPTION:   tern on the radio.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

void ComHndlr_RadioOn(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RadioOff
 *
 * DESCRIPTION:   tern off the radio.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

void ComHndlr_RadioOff(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_GetRadioStatus
 *
 * DESCRIPTION:   Write the radio status Radio structure.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_GetRadioStatus(RadioDescrStr *Radio);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_Menu
 *
 * DESCRIPTION:   ^
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_Menu(void *dummy);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_WaitForSyncCall
 *
 * DESCRIPTION:   Set modem to wait for an synchronous incoming calls.
 *                The parameters are:
 *                MaxBitRate - 300 for 300   baud
 *                             1200 for 1200 baud
 *                             2400 for 2400 baud
 *                TerminalType - SYNC_PRIMARY / SYNC_SECONDARY
 *                NoCarrierTime- Time until carrier is up on the calling side
 *                NumberOfRings - Number of rings before answering. default 2.
 *
 * RETURN:        OK or FAIL
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_WaitForSyncCall ( usint  MaxBitRate,
				                     byte  TerminalType,
				                      usint AnswerToneTimeOut,
				                       ulint NumberOfRings);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_WaitForAsyncCall
 *
 * DESCRIPTION:   Set modem to wait for an asynchronous incoming calls.
 *                The parameters are:
 *                MaxBitRate - 300 for 300   baud
 *                             1200 for 1200 baud
 *                             2400 for 2400 baud
 *                Format     - 8, 9, 10 or 11 bits in character
 *                AnswerToneTimeOut- Time until carrier is up on the calling side
 *                NumberOfRings - Number of rings before answering. default 2.
 *
 * RETURN:        OK or FAIL
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_WaitForAsyncCall ( usint MaxBitRate,
				                      byte  Format,
				                       usint AnswerToneTimeOut,
				                        ulint NumberOfRings);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_GetAutoAnswerState
 *
 * DESCRIPTION:   Returns the current modem auto answer status
 *
 * RETURN:        AA_DURING_CONNECT
 *                AA_WAIT_FOR_RING
 *                AA_CHANGE_BAUD_300
 *                AA_CHANGE_BAUD_1200
 *                AA_CHANGE_BAUD_2400
 *                AA_CONNECTED
 *                AA_DISCONNECT
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_GetAutoAnswerState(void);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_DisableWaitForCall
 *
 * DESCRIPTION:   Disables modem auto-answer mode
 *
 * RETURN:        OK or FAIL
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_DisableWaitForCall ( void);




/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetLanguage
 *
 * DESCRIPTION:   Sets new strings instead of the English ones
 *
 * RETURN:        void.
 *
 * NOTES:         Use first 29 messages from MyStrings,
 *                last used message is MSG_INDEX_LINE_CHECK_OFF.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetLanguage( char *MyStrings);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetUserMsgs
 *
 * DESCRIPTION:   Sets new strings instead of the English ones
 *
 * RETURN:        void.
 *
 * NOTES:         Use first UserMsgsNum messages from MyStrings.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetUserMsgs( char *MyStrings, byte UserMsgsNum);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetCallerLanguage
 *
 * DESCRIPTION:   Sets new strings instead of the English ones
 *
 * RETURN:        void.
 *
 * NOTES:         Use first 14 messages from UserCallerMessages,
 *                last used message is MSG_INDEX_DIALING_WAIT.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetCallerLanguage( char *UserCallerMessages);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetCallerUserMsgs
 *
 * DESCRIPTION:   Sets new strings instead of the English ones
 *
 * RETURN:        void.
 *
 * NOTES:         Use first UserMsgsNumber messages from UserCallerMessages.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetCallerUserMsgs( char *UserCallerMessages,byte UserMsgsNumber);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetUserParams
 *
 * DESCRIPTION:   Sets the user parameters without user interaction (i.e.
 *                Menu handling).
 *                MinNumOfTrials: minimum number of trials (0=Don't Change)
 *                                should be betwen 1 to 100.
 *                DialType: 'T' = TONE, 'P' = PULSE (other=Don't Change)
 *                ExPrefix: char representing the exchange prefix
 *                          '0' - '9' or NULL for no ex. prefix. Other
 *                          char = Don't Change previous.
 *                LineOnly: 1 = don't use radio, 0 = normal(MODEM+RADIO)
 *                          other = Don't Change previous.
 *
 * RETURN:        none.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetUserParams( byte MinNumOfTrials,
			     char DialType,
			     char ExPrefix,
			     byte LineOnly);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetExPrefix
 *
 * DESCRIPTION:   Sets the user exchange prefix (max 8 digits).
 *
 * RETURN:        none.
 *
 * NOTES:         must not be calling before ComHndlr_SetUserParams,
 *                because this function set the exchange prefix too!!!.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetExPrefix( char *ExPrefix);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_ActivateBkGrMsg
 *
 * DESCRIPTION:   Activate the Radio BkGr Msgs utility - enables The Bkgr
 *                Mechanism to store received messages on a RamDisk file.
 *
 * RETURN:        OK - successfuly activated or
 *                RamDisk error value:
 *                 Bad file handle/Error on reading etc...
 *                or RBM error value:
 *
 *                RBM_BAD_RECORD_SIZE        Rec size out of boundries.
 *                RBM_DURING_A_CALL          between _Call to _EndCall.
 *                RBM_NOT_ENOUGH_DISK_SPACE  too many record requested.
 *                RBM_WRONG_INPUT            if *prm is not 0.
 *                RBM_NOT_SUPPORTED          NOS system without RBM utility.
 *                X_NOT_SWITCHED_TO_RADIO    Switch set to modem !
 *
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_ActivateBkGrMsg(sint FileHandle,    /* File Index */
			      usint RecSize,      /* File's Record Size */
			      usint MaxNumOfRecs, /* Max Records to allow */
			      void *prm);         /* pointer to an options
						     structure may be used
						     in the future -> keep it
						     0 */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_StopBkGrMsg
 *
 * DESCRIPTION:   DeActivate the Radio BkGr Msgs utility.
 *
 * RETURN:        None.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_StopBkGrMsg(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_RbmTxRadio
 *
 * DESCRIPTION:   transmits data via radio
 *                Waits until there is enough room in transmit buffer or
 *                until timeout.
 *
 * RETURN:        X_OK  - data transmitted o.k.
 *                X_TIMEOUT - exit by timeout.
 *                X_ESC_PRESSED - break by user.
 *                X_RADIO_BUFFER_TOO_BIG - Too much Data (radio)
 *                X_NOT_SWITCHED_TO_RADIO - we are not switched to radio.
 *                X_NO_MSG - tx message is out on the air and no message was
 *                           received.
 *                X_NEW_MSG - new message is present in rx buffer - go and take it out
 *                X_MSG_RETURNED - the message in the Mpak buffer is the message
 *                                 returned by the radio.
 *                RBM_NOT_SUPPORTED - if RBM is not supported by this NOS.
 *
 *
 * NOTES:
 *                This is the function called by the application for sending
 *                a text message to the MOBITEX network.
 *                the parameter time_out - the number of miliseconds to wait
 *                until system is sure that message is out on the AIR or
 *                transmitted message was returned (or another message
 *                received)
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_RbmTxRadio (
			  byte  *buf,   /* pointer to data to be sent */
			  usint *length, /* pointer to length of data. Amount */
					 /* actually sent will be placed here */
			  ulint to_addr, /* Send To Address */
			  usint time_out /* Send Time out */
			 );






/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_PreDialBkgr
 *
 * DESCRIPTION:   establish connection in background
 *                this function will begin a foreground process which will
 *                bring to the connection of the terminal through a telephone
 *                line, to an external modem. It must be called only ONCE
 *                and then it will start running by itself!
 *                Termination of the process will take place when connection
 *                is established via MODEM or when an error occurs.
 *                When it's time to communicate user must call
 *                ComHndlr_PreDialForegrnd() inorder to continue communcations
 *                process or learn about connection status.
 *
 *
 * RETURN:        TRUE if process is on the way, FAIL_CONNECT if error occured.
 *                FAIL_WRONG_INPUT - WRONG INDEX #
 *
 * NOTES:         If error occured user must call for foreground call.
 *                See ComHndlr_PreDialForegrnd before writing code!
 *
 * ------------------------------------------------------------------------ */
usint ComHndlr_PreDialBkgr (usint target_index);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ComHndlr_PreDialBkgr2
 * DESCRIPTION:   establish connection in background
 *                this function will begin a foreground process which will
 *                bring to the connection of the terminal through a telephone
 *                line, to an external modem. It must be called only ONCE
 *                and then it will start running by itself!
 *                Termination of the process will take place when connection
 *                is established via MODEM or when an error occurs.
 *                When it's time to communicate user must call
 *                ComHndlr_PreDialForegrnd() inorder to continue communcations
 *                process or learn about connection status.
 * RETURN:        TRUE if process is on the way,
                  FAIL_CONNECT if an error occured.
 * NOTES:         If error occured user must call for foreground call.
 *                See ComHndlr_PreDialForegrnd before writing code!
 * ------------------------------------------------------------------------ */
usint ComHndlr_PreDialBkgr2 (DialTargetType *DialTarget);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_PreDialForegrnd
 *
 * DESCRIPTION:   continue establishing  connection in foreground
 *                This function is a part of the PreDial process.
 *                It should be called as soon as the terminal gains
 *                foreground control and ready to communicate.
 *                User must not call this function without FIRST calling
 *                the Background function (see ahead...)
 *
 * RETURN:           CONNECTED_LINE - if all ok and connected
 *                   CONNECTED_LINE_LOGON_PROTOCOL - if connected to logon
 *                   USER_BREAK - if user pressed escape <ESC>
 *                   FAIL_CONNECT - if connection has failed or not called
 *                                  background function first.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
usint ComHndlr_PreDialForegrnd (void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_GetDialType
 *
 * DESCRIPTION:
 *
 * RETURN:        returns the character 'T' if tone or 'P' if pulse.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
char Comhndlr_GetDialType(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_LinkInit
 *
 * DESCRIPTION:   Initializes Link & reset static data.
 *                Must be called each time communication is about
 *                to start.
 *
 * RETURN:        Returns : What's Link_Init returns:
 *
 *		  OK		for success.
 *		  FAILURE	for error if Link hasn't been created
 *                              yet.
 *
 * NOTES:         Cannot be Called before Link_Create called.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_LinkInit(sint port,usint time_out_per_retry);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_LinkSnd
 *
 * DESCRIPTION:   Sends Data (using buffers)
 *
 *                Since this function may wait for receive before send
 *                it must keep the option of receiving data.
 *
 * RETURN:        X_OK          - Data was sent.
 *                X_OK_DATA_RCV - Sent buffer sent & also Data
 *                                was received.
 *                X_FAILURE     - Error on lower communication level
 *                                Need to end communication.
 *                X_ESC_PRESSED - Canceled by user (ESC).
 *
 * NOTES:         May be Called From a Protocol Communication Handler.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_LinkSnd(sint port,         /* Link Entity Port */
		      byte *snd_buf,     /* Send buffer */
		      sint snd_size,     /* Send data size */
		      byte *rcv_buf,     /* Receive buffer */
		      sint *rcv_buf_size /* in - max rcv buffer
			      	            out - actual size received
					    if retval = X_OK_DATA_RCV */);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_LinkRcv
 *
 * DESCRIPTION:   Receives Data (using buffers).
 *
 * RETURN:        X_OK      -  Received Data.
 *
 *                X_FAILURE -  Error on lower communication level
 *                             Need to end communication.
 *
 *                X_ESC_PRESSED -  Canceled by user (ESC).
 *
 * NOTES:         May be Called From a Protocol Communication Handler.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_LinkRcv(sint port,         /* Link Entity Port */
		      byte *rcv_buf,     /* Recieve buffer */
		      sint *rcv_buf_size /* in : rcv buffer size
			  	            out: actual received size */);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_LinkCheckRcv
 *
 * DESCRIPTION:   Check if ther's received data & returns.
 *
 * RETURN:        X_OK               - Received Data:
 *
 *                X_NOTHING_RECEIVED - Nothing Received.
 *
 *                X_FAILURE          -  Error on lower communication
 *                                      level Need to end communication.
 *
 * NOTES:         May be Called From a Protocol Communication Handler.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_LinkCheckRcv(sint port,         /* Link Entity Port */
		           byte *rcv_buf,     /* Recieve buffer */
		           sint *rcv_buf_size /* in : rcv buffer size
			                         out: actual received size */);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ComHndlr_GetStatistics
 * DESCRIPTION:   fills ComStatistics structure pointed by csp
                  with communication fail reasons statistics
 * RETURN:        none
 * NOTES:         ResetFlag=TRUE  will reset statistics counters to 0
                  ResetFlag=FALSE will leave statistics counters as is
 * ------------------------------------------------------------------------ */
void ComHndlr_GetStatistics(TComStatistics *csp, boolean ResetFlag);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetRadioDriverMode
 *
 * DESCRIPTION:   This function is used to Enable / Disable the radio
 *                driver of the NOS.
 *
 * PARAMETERS:    Mode - Mode of the driver
 *
 *                       COMHNDLR_RADIO_DRV_ENABLE  - Enable driver
 *                       COMHNDLR_RADIO_DRV_DISABLE - Disable driver
 *
 * RETURN:        OK      - Radio driver was enabled / disabled succesfuly
 *                FAILURE - Can not enable / disable radiodriver
 *
 * NOTES:         The radio driver is enabled by default.
 *
 * ------------------------------------------------------------------------ */
sint ComHndlr_SetRadioDriverMode(byte Mode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetRadioPwrSaveMode
 *
 * DESCRIPTION:   Sets the Enhanced Power Save mode for the radio.
 *
 * PARAMETERS:    Mode - PWRSAVE_DISABLED - Power savings is disabled.
 *                       PWRSAVE_MAXIMUM  - Maximum power savings.
 *                       PWRSAVE_AVERAGE  - Average power savings.
 *                       PWRSAVE_MINIMUM  - Minimum power savings.
 *
 * RETURN:        None.
 *
 * NOTES:         The radio driver is enabled by default.
 *
 * ------------------------------------------------------------------------ */
void ComHndlr_SetRadioPwrSaveMode(PwrSaveMode Mode);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_GetLastModemCall
 *
 * DESCRIPTION:   Return the address of modem last call statistic.
 *
 * RETURN:        number of data of last call array.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte ComHndlr_GetLastModemCall(void **LastCall);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ComHndlr_SetNetworkAddress
 *
 * DESCRIPTION:   Set the Network address for HDLC over 485 address
 *
 * RETURN:        OK      if set OK
 *                FAILURE if Driver not exist
 *
 * NOTES:         Before working with 485 network user must call this function.
 * ------------------------------------------------------------------------ */
sint ComHndlr_SetNetworkAddress(byte Address);



#ifdef __NOS__
  #include comhndlr_nos
#endif


	   /*=========================================*
	    *  INLINE FUNCTIONS IMPLEMENTED BY MACROS *
	    *=========================================*/
/* void */

           /*=========================================*
            *           E P I L O G                   *
            *=========================================*/
/* void */

