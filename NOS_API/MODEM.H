/****************************************************************************
 *                                                                          *
 * FILE NAME:   modem.h                                                     *
 *                                                                          *
 * MODULE NAME: MODEM_AT.                                                   *
 *                                                                          *
 * PROGRAMMER:  Hai Shalom.                                                 *
 *                                                                          *
 * DESCRIPTION: AT Modem driver header.                                     *
 *                                                                          *
 ****************************************************************************/

#ifndef __MODEM_OLD_TDK_H
#define __MODEM_OLD_TDK_H

#include modem_prm

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

#define LAST_PHONE_NUM_SIZE    20

#define NO_CHECK_DIAL_TONE      1
#define NO_WAIT_ANSWER          2

/* Modem status flags */
#define DIAL_UP_ERROR          -9    /* Unused (Compatibility) */
#define NO_HANDSHAKE           -8    /* No connection after answer tone */
#define NO_ANSWER              -7    /* Timeout after dialing */
#define NO_CARRIER             -6    /* Carrier loss */
#define NO_LINE                -5    /* Phone line is not connected */
#define NO_DIAL_TONE           -4    /* No dial tone before dialing */
#define BUSY                   -3    /* Called number is busy */
#define NO_RING_BACK           -2    /* No ring back after dialing */
#define NO_ANSWER_TONE         -1    /* Unused (Compatibility) */
#define DURING_CONNECT          1    /* During connection */
#define STILL_CONNECTED         2    /* Modem is connected to other side */
#define WAIT_FOR_RING           3    /* Auto answer mode */

/* Originate states */
#define IDLE                    0    /* Modem is idle */
#define SETUP                   1    /* Modem setup */
#define END_SETUP               2    /* End of modem setup */
#define DIALING                 3    /* Modem is dialing */
#define END_DIALING             4    /* Unused (Compatibility) */
#define WAIT_CONNECT            5    /* Waiting for connection */
#define CONNECT                 6    /* Connection is made */
#define DISCONNECT1             7    /* During disconnection phase 1 */
#define DISCONNECT2             8    /* During disconnection phase 2 */
#define DISCONNECT              9    /* Modem is disconnected */
#define RESET                   10   /* Modem reset */
#define PWR_UP                  11   /* Modem power up */
#define DIAL_ERR                12   /* Unused (Compatibility) */

/* Modem connection speeds */
#define JUST_CONNECTED_300      300 
#define JUST_CONNECTED_1200     1200 
#define JUST_CONNECTED_2400     2400 

/* For 14.4K, 33.6K and 56K modems only */
#define JUST_CONNECTED_4800     4800 
#define JUST_CONNECTED_7200     7200
#define JUST_CONNECTED_9600     9600
#define JUST_CONNECTED_12000    12000
#define JUST_CONNECTED_14400    14400

/* For 33.6K and 56K modems only */
#define JUST_CONNECTED_16800     0x400C
#define JUST_CONNECTED_21600     0x400D
#define JUST_CONNECTED_24000     0x400E
#define JUST_CONNECTED_26400     0x400F
#define JUST_CONNECTED_28800     0x4010
#define JUST_CONNECTED_31200     0x4011
#define JUST_CONNECTED_33600     0x400B

/* For 56K (V.90) modem only */
#define JUST_CONNECTED_56000     0x4012
#define JUST_CONNECTED_32000     0x4013
#define JUST_CONNECTED_48000     0x4014
#define JUST_CONNECTED_28000     0x4015
#define JUST_CONNECTED_29333     0x4016
#define JUST_CONNECTED_30666     0x4017
#define JUST_CONNECTED_33333     0x4018
#define JUST_CONNECTED_34666     0x4019
#define JUST_CONNECTED_36000     0x401A
#define JUST_CONNECTED_37333     0x401B
#define JUST_CONNECTED_38666     0x401C
#define JUST_CONNECTED_40000     0x401D
#define JUST_CONNECTED_41333     0x401E
#define JUST_CONNECTED_42666     0x401F
#define JUST_CONNECTED_44000     0x4020
#define JUST_CONNECTED_45333     0x4021
#define JUST_CONNECTED_46666     0x4022
#define JUST_CONNECTED_49333     0x4023
#define JUST_CONNECTED_50666     0x4024
#define JUST_CONNECTED_52000     0x4025
#define JUST_CONNECTED_53333     0x4026
#define JUST_CONNECTED_54666     0x4027

/* Bits number in byte */
#define START_6N_STOP           8
#define START_6E_STOP           9
#define START_6O_STOP           9
#define START_7N_STOP           9
#define START_7E_STOP           10
#define START_7O_STOP           10
#define START_8N_STOP           10
#define START_8E_STOP           11
#define START_8O_STOP           11
#define DEFAULT_BITS_IN_BYTE    10

/* Disconnection reason values */
#define HANDSHAKE_STALLED                       0x8002
#define NO_DIALTONE_DETECTED                    0x8
#define NO_LINE_AVAILABLE                       0x8008
#define NO_LOOP_CURRENT_DETECTED                0x9
#define PARALLEL_PHONE_PICKUP_DISCONNECT        0x8009
#define NO_RINGBACK                             0xA
#define BUSY_SIGNAL_DETECTED                    0xB
#define V42_REQUESTED_DISCONNECT                0xD
#define MNP_REQUESTED_DISCONNECT                0xE
#define DROP_DEAD_TIMER_DISCONNECT              0x10
#define LOOP_CURRENT_LOSS                       0x8014
#define REMOTE_MODEM_REQUESTED_DISCONNECT       0x8017
#define SOFT_RESET_COMMAND_1_RECEIVED           0x8018
#define SOFT_RESET_COMMAND_2_RECEIVED           0x8019
#define V42_PROTOCOL_ERROR                      0x1a
#define MNP_PROTOCOL_ERROR                      0x1b
#define LOSS_OF_CARRIER_DISCONNECT              0x801c
#define LONG_SPACE_DISCONNECT                   0x801e
#define CHARACTER_ABORT_DISCONNECT              0x801f
#define RATE_REQUEST_FAILED                     0x802a
#define ANSWER_MODEM_ENERGY_NOT_DETECTED        0x802b
#define V8_NEGOTIATION_FAILED                   0x802c
#define TX_DATA_TIMEOUT                         0x2d


/******* Country settings indexes ******/

/* The following countries require FCC Settings: 
   Argentina, Brunei, Canada, Chile, Columbia, Dubai, Equador, El Salvador,
   Guam, Hong Kong, Hungary, India, Indonesia, Kuwait, Macao, Mexico, Peru, 
   Puerto Rico, Romania, Saudi Arabia, Singapore, Slovakia, Tunisia, UAE, 
   USA, Venezuela, and Yemen. */

#define MODEM_SETTING_INDEX_FCC            0

/* The following countries require CTR21 Settings: 
   Austria, Bahrain, Belgium, Bulgaria, Croatia, Cyprus, Denmark, Estonia,
   European Union, Finland, France, Germany, Greece, Guadeloupe, Iceland, 
   Ireland, Israel, Italy, Lebanon, Liechtenstein, Luxembourg, Malta, 
   Martinique, Morocco, Netherlands, Norway, Polynesia (French), Portugal, 
   Reunion, Spain, Sweden, Switzerland, Turkey, and the United Kingdom. */

#define MODEM_SETTING_INDEX_CTR21          1

/* Settings for Poland: */

#define MODEM_SETTING_INDEX_POLAND         2

/* The following countries require the same settings as Brazil: 
   Armenia, China, Egypt, Georgia, Japan, Jordan, Kazakhstan, Kyrgyzstan, 
   Muldova, Oman, Pakistan, Qatar, Russia, Syria, Taiwan, Thailand, 
   and Ukraine. */

#define MODEM_SETTING_INDEX_BRAZIL         3

/* Settings for South Africa: */
#define MODEM_SETTING_INDEX_SOUTH_AFRICA   4

/* Settings for Australia: */
#define MODEM_SETTING_INDEX_AUSTRALIA      5


          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

/*Dummy: Retrain Mode  for  compatibilty with ST modem*/
typedef struct
{
  byte  SelfRetrainMode;       /* Not used */
  byte  ResponseRetrainMode;   /* Not used */
  byte  MinBerForSelfRetrain;  /* Not used */

} ModemRetrainPrm;

typedef struct
{
  ulint HandShakeTime;    /* Time from dialing to connection (ms units) */
  ulint ConnectTime;      /* Connection time (from CONNECT to NO CARRIER, ms units) */
  usint MaxBaudRate;      /* Requested minimum baudrate */
  usint MinBaudRate;      /* Requested minimum baudrate */
  usint ConnectBaudRate;  /* Connection baudrate */
  usint TxBaudRate;       /* Tx (Downstream) baudrate */
  usint RxBaudRate;       /* Rx (Upstream) baudrate */
  usint TxErrors;         /* V.42 TX Errors */
  usint RxErrors;         /* V.42 RX Errors */
  usint DiscReason;       /* Disconnection by this error */
  byte  DialType;         /* 'T' for tone dialing, else pulses */
  byte  BitsInChar;       /* 8,9,10 or 11, default 10            */
  byte  ConnectMode;      /* Sync, Async, Fast */
  byte  RetrainCnt;       /* Retrains during connection */
  char  PhoneNum[LAST_PHONE_NUM_SIZE]; /* Target phone number */
  char  Protocol[ 20 ];   /* Connected protocol (V.42,V.32 etc.) */
  byte  RxLevel;          /* RX Level (dBM) */
  byte  TxLevel;          /* TX Level (dBM) */
  byte  EffectiveSN;      /* Effecting signal to noise ratio */
  byte  ResidualEcho;     /* Residual echo */

} ModemAtLastStatistic;

typedef struct
{
   char HwRevCode[4];     /* Modem hardware revision code. */
   char SwRevCode[32];    /* Modem firm\software revision code. */
   char DAARevCode[8];    /* Modem line-side (DAA) revision code. */
   char ModelNum[32];     /* ISOmodem model number. */
   char ModuleName[16];   /* String description of the underlying modem */
} ModemInfo;    

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_SetParam
 *
 * DESCRIPTION:   Sets default modem parameters for every country.
 *
 * RETURN:        void
 *
 * NOTES:         The input is country name as define in nurit.def.
 *
 * ------------------------------------------------------------------------ */
void Modem_SetParam (usint Index);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_ChangeParam
 *
 * DESCRIPTION:   Sets new parameters (from application).
 *
 * RETURN:        void
 *
 * NOTES:         The input is pointer to a new parameters structure.
 *
 * ------------------------------------------------------------------------ */
void Modem_ChangeParam (ModemParamType  *ModemParam_p1);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_Status.
 *
 * DESCRIPTION:   returns modem status for connection step.
 *
 * RETURN:
 *         NO_HANDSHAKE           -8     no modem connect after answer tone
 *         NO_ANSWER              -7     time out after dialing or
 *                                       ring back was detected   
 *         NO_CARRIER             -6     carrier loss
 *         NO_LINE                -5     phone line is not connected
 *                                        - or -
 *                                       someone is talking now
 *         NO_DIAL_TONE           -4     no dial tone before dialing
 *         BUSY                   -3     called number is busy
 *         NO_RING_BACK           -2     no ring back after dialing
 *         NO_ANSWER_TONE         -1     called modem doesn't send
 *                                       answer tone or doesn't answer
 *         IDLE                    0     Modem is idle
 *         DURING_CONNECT          1     During connection
 *         STILL_CONNECTED         2     Modem is connected
 *         WAIT_FOR_RING           3     Modem is waiting for an incoming call
 *         JUST_CONNECTED_XXXXX    See above
 *         
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Modem_Status(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_SetRetrainParam
 *
 * DESCRIPTION:   Dummy function for compatibilty with ST modem.
 *
 * RETURN:        void
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void Modem_SetRetrainParam (ModemRetrainPrm *RetrainMode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_SendAtCommand.
 *
 * DESCRIPTION:   Send an AT command to modem.
 *
 * RETURN:        OK/FAILURE.
 *
 * NOTES:         AT command parameter MUST be a pointer to a constant NULL 
 *                terminated string.
 *                Value in the given address must not be changed after calling
 *                This function. Command must start with AT prefix and must end
 *                with \r suffix, and must be in UPPER case (Capital letters).
 *                Multiple AT commands are valid in the format:
 *                "ATxxxxx\rATxxxxxx\rATxxxxx\r....."
 * ------------------------------------------------------------------------ */
sint Modem_SendAtCommand( const char *AtCommand );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_GetInfo
 *
 * DESCRIPTION:   Returns modem information.
 *
 * PARAMETERS:    Output - pointer to struct containing modem info.
 *
 * RETURN:        OK\FAILED
 *
 * NOTES: 
 *
 * ------------------------------------------------------------------------ */
byte Modem_GetInfo(ModemInfo *Info);

/* --------------------------------------------------------------------
 *
 * FUNCTION NAME: Modem_CheckPhoneLine.
 *
 * DESCRIPTION:   Check if phone line is connected to NURIT.
 *
 * RETURN:        TRUE if phone line connected.
 *                FALSE if phone line is disconnected, or an error.
 *
 * NOTES:         Can be called only when modem is in IDLE state
 *                (Before making a phone call).
 *
 * -------------------------------------------------------------------- */
boolean Modem_CheckPhoneLine( void );

#ifdef __NOS__
  #include modem_nos
#endif

           /*=========================================*
            *  INLINE FUNCTIONS IMPLEMENTED BY MACROS *
            *=========================================*/
/* void */
#endif /*#ifndef __MODEM_OLD_TDK_H*/


