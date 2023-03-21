/****************************************************************************
 *                                                                          *
 * FILE NAME:   applmngr.h                                                  *
 *                                                                          *
 * MODULE NAME: applmngr                                                    *
 *                                                                          *
 * PROGRAMMER:  Ofir & Miri.                                                *
 *                                                                          *
 * DESCRIPTION: API functions declarations                                  *
 *                                                                          *
 * REVISION:    06_00 09/11/99 Oren S.                                      *
 *              04_00 25/08/95                                              *
 *                                                                          *
 ****************************************************************************/
#ifndef __APPLMNGR_H__
#define __APPLMNGR_H__

          /*==========================================*
           *             I N C L U D E S              *
           *==========================================*/

#include protmngr_def
#include platform_def

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

/* Used in ApplMngr_ReplaceAppl function */

#define NEW_PARAMS_LOADED    1
#define OLD_PARAMS_REMAIN    0
#define ERR_OCCURED         -1
#define NOT_SUPPORTED       -2

/* Used in ApplMngr_Diagnostics function */

#define  FP_MANUAL      0
#define  FP_AUTOMATIC   1
#define  FP_RESTART     2

#define DIAGNOSTICS_RS      1
#define DIAGNOSTICS_MODEM   2
#define DIAGNOSTICS_TONE   'T'
#define DIAGNOSTICS_PULSE  'P'

/* Used For Application with _GetNosType function: */

#define TYPE_2035 2035

#define TYPE_2050  2050
#define TYPE_2050H 2051
#define TYPE_2050E 2052

#define TYPE_2060 2060
#define TYPE_2070 2070 /* MASK RADIO */
#define TYPE_CDPD 2073 /* CDPD RADIO */
#define TYPE_2080 2080
#define TYPE_2085 2085
#define TYPE_2090 2090 /* MASK RADIO */
#define TYPE_2091 2091 /* CDPD RADIO */
#define TYPE_2092 2092 /* NATIVE RADIO */
#define TYPE_3000 3000
#define TYPE_3001 3001
#define TYPE_3003 3003 /* Spain */
#define TYPE_3010_MASC   3010
#define TYPE_3010_CDPD   3011
#define TYPE_3010_NATIVE 3012
#define TYPE_3010_GSM    3013
#define TYPE_3010_AMPS   3014

#define TYPE_5000 5000   /* ATM */
#define TYPE_8000 8000   /* Handle */
#define TYPE_8000_MASC   8010
#define TYPE_8000_CDPD   8011
#define TYPE_8000_NATIVE 8012
#define TYPE_8000_GSM    8013

#define TYPE_PINPAD 272
#define TYPE_2159 2159
#define TYPE_2055 2055
#define TYPE_2058 2058
#define TYPE_2059 2059
#define TYPE_292  292

#define TYPE_8320_AT 8320
#define TYPE_8320_ST 8321
#define TYPE_8100    8100

#define APPLMNGR_RESET                0
#define APPLMNGR_GET                  2
#define APPLMNGR_SET                  1
#define MANUAL_RESET_MADE             1

#define APPLMNGR_APPLICATION           1
#define APPLMNGR_PARAMETERS            2
#define APPLMNGR_APPL_AND_PARAMS       3
#define APPLMNGR_PROTOCOL              4
#define APPLMNGR_APPLICATION_STORE     5
#define APPLMNGR_NOS                   6
#define APPLMNGR_TSP_BLOCK             7

#define APPLMNGR_DONT_USE_FPD          0x0400 /* dont use FPD for connection if exist */
#define APPLMNGR_LOAD_NO_CONNECT       0x0200 /* line is connected dont connect */
#define APPLMNGR_LOAD_NO_DISPLAY       0x0100 /* dont echo to display */
#define APPLMNGR_LOAD_WITH_RETRY       0x0080
#define APPLMNGR_LOAD_NO_BREAK_FLAG    0x0040 /* use as "or" load mode */
#define APPLMNGR_LOAD_RETRY_BY_APPL    0x0020 /* use as "or" load mode */
#define APPLMNGR_LOAD_ALPHA_SITE_ID    0x0010 /* use as "or" load mode */

#define APPLMNGR_DOWNLOAD_RETRY_NUM    5
#define APPLMNGR_DOWNLOAD_RETRY_TIME   600  /* in sec */
                 /* DOWN LOAD MODES */
#define APPLMNGR_AUTO_LOAD                11 /* load both */
#define APPLMNGR_APPL_LOAD                12
#define APPLMNGR_PARAM_LOAD               13
#define APPLMNGR_TSP_LOAD                 14
#define APPLMNGR_AUTO_LOAD_WITH_RETRY   (APPLMNGR_AUTO_LOAD|APPLMNGR_LOAD_WITH_RETRY)
#define APPLMNGR_APPL_LOAD_WITH_RETRY   (APPLMNGR_APPL_LOAD|APPLMNGR_LOAD_WITH_RETRY)
#define APPLMNGR_PARAM_LOAD_WITH_RETRY  (APPLMNGR_PARAM_LOAD|APPLMNGR_LOAD_WITH_RETRY)
#define APPLMNGR_TSP_LOAD_WITH_RETRY    (APPLMNGR_TSP_LOAD|APPLMNGR_LOAD_WITH_RETRY)
typedef enum
{
   MSG_INDEX_DOWNLOAD_FAIL = 0,   /* Fail! ENT->RetryESC->Load Menu  */
   MSG_INDEX_CLEARING_PROG,       /* Clearing PROG   Memory... */
   MSG_INDEX_CLEARING_PRM,        /* Clearing PRM    Memory... */
   NUM_OF_APPLMNGR_MSGS
} ApplMngrMessages;

#define APPLMNGR_MSG_LEN_SIZE   33
#define INIT_STR_LENGTH         40
#define DIAL_PREFIX_LENGTH      16
#define DIAL_SUFFIX_LENGTH      16
#define HANGUP_LENGTH           16

typedef struct
{
   char  InitString[INIT_STR_LENGTH];    /*for INIT_STR_LENGTH  see CALLER.H*/
   char  DialPrefix[DIAL_PREFIX_LENGTH]; /*for DIAL_PREFIX_LENGTH see CALLER.H*/
   char  DialSuffix[DIAL_SUFFIX_LENGTH]; /*for DIAL_SUFFIX_LENGTH see CALLER.H*/
   char  LockBaudrate; /*0/1 - change br after connect(if necessry)/do not change*/
   char  HangupType;                     /*0/1 - drop DTR/send hangup command*/
   char  HangupCommand[HANGUP_LENGTH];   /*for HANGUP_LENGTH see CALLER.H*/
}ExternalModemPrm;

/* For Applmngr_TcpIpPrm function */
#define APPLMNGR_TCPIP_GET                    0
#define APPLMNGR_TCPIP_SET                    1

typedef enum
{
  CDT_DIRECT=0,
  CDT_MODEM,
  CDT_GSM_DIAL,
  CDT_EXT_MODEM=0x73,

  CDT_TCPIP_DIRECT=0x80,
  CDT_TCPIP_MODEM,
  CDT_TCPIP_GSM_DIAL,
  CDT_TCPIP_GPRS_DIAL,
  CDT_TCPIP_ETHERNET,
  CDT_TCPIP_WIFI,
  CDT_TCPIP_EXT_MODEM=0xF3

} CommDeviceType;

typedef struct
{
   byte     IsByModem;       /* see CommMediaType for definitions */
   char     DialMode;        /* if='T', then TONE , else PULSE' */
   usint    BitRate;         /* 300,1200,2400,9600,19200  */
   char     *PhoneNum;       /*  pointer to ASCII string  */
   char     *ExchangePrefix; /*  pointer to ASCII string or NULL */
   char     *Suffix;         /*  pointer to ASCII string or NULL */
   byte     RetryNum;        /*  Retry number to be set by application */
   byte     Spare;
   usint    RetryTimeInSec;  /*  Retry time to be set by application */
   ExternalModemPrm *ExtModem; /*  pointer to external modem structure*/
}ApplDownLoadPrm;


typedef char MyApplMngrTextMsgs[NUM_OF_APPLMNGR_MSGS][APPLMNGR_MSG_LEN_SIZE];

/* ApplMngr_CallAppl return codes  */

#define    APPLMNGR_APPL_OK        0
#define    APPLMNGR_APPL_NOEXIST  -1
#define    APPLMNGR_APPL_NOVER    -2
#define    APPLMNGR_APPL_NOMEM    -3


           /*=========================================*
            *   P U B L I C     F U N C T I O N S     *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_Shell.
 *
 * DESCRIPTION:   Jump subroutine To Nos (From application).
 *
 * RETURN:        none.
 *
 * NOTES:         Called from Kb driver when detected SHELL combination.
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_Shell(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_IsApplFirstRun.
 *
 * DESCRIPTION:   Detemines whether this is the first time application is
 *                running or not.
 *
 * RETURN:        TRUE - first time , FALSE - not the first time.
 *
 * NOTES:         Called by Appl Only (works Only whan application is
 *                running).
 *
 * ------------------------------------------------------------------------ */
boolean ApplMngr_IsApplFirstRun(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_LoadParams.
 *
 * DESCRIPTION:   Download of parameters , via menus , (the same
 *                communication parameters used by the nos menu) ,
 *                displays messages on screen . At the
 *                end of download calls all modules that need to be
 *                updated and return to application with the status
 *                (diplays back the previous text & all status).
 *
 *                site_no: site no to be used for download.
 *
 * RETURN:        status:
 *                NEW_PARAMS_LOADED  - if parameters loaded (new parameters),
 *
 *                OLD_PARAMS_REMAIN  - not loaded (old parameters remain),
 *
 *                ERR_OCCURED        - error occured (no parameters exists).
 *
 *
 * NOTES:         Called from application (request for parameters).
 *
 * ------------------------------------------------------------------------ */
sint ApplMngr_LoadParams(ulint site_no);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_RestartAppl.
 *
 * DESCRIPTION:   Restart appl.
 *
 * RETURN:        none.
 *
 * NOTES:         Might Called from application (No turnning back).
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_RestartAppl(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_Diagnostics.
 *
 * DESCRIPTION:   Opens The Diagnostics Menu.
 *
 * RETURN:        none.
 *
 * NOTES:         Called from application (request for diagnostics).
 *                (Prototype Designed for Formater Menus
 *                 dummy must be : (void *)0 !!)
 * ------------------------------------------------------------------------ */
void ApplMngr_Diagnostics(void *dummy);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_LedOn
 *
 * DESCRIPTION:   Activates the Unused led - which is free to use
 *                by applications.
 *
 * RETURN:        none.
 *
 * NOTES:         Called from application.
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_LedOn(sint period);/*  On/Off period in tenths of second.
                                    0 means : Just Turn On */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_LedOff
 *
 * DESCRIPTION:   Turns the Unused led ( which is free to use
 *                by applications) Off.
 *
 * RETURN:        none.
 *
 * NOTES:         Called from application.
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_LedOff(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_GetNosType
 *
 * DESCRIPTION:   Return The Nos Type : 2060 , 2070, 2080 ..
 *
 * RETURN:        TYPE_2060 or
 *                TYPE_2070 or
 *                TYPE_2080
 *
 * NOTES:         Called from application.
 *
 * ------------------------------------------------------------------------ */
sint ApplMngr_GetNosType(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_CommPrmMenu
 *
 * DESCRIPTION:   Call communication params menu.
 *
 * RETURN:        None.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_CommPrmMenu(void *dummy);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: LdComMgr_LoadApplData
 * DESCRIPTION:   Download Application data block.
 * RETURN:        >0 - OK, <0 - Error code.
 * NOTES:         1. This function behave like _ReplaceAppl
 *                with one extra parmeter to set the Appl ID
 *                (The application on the PC to connect to)
 *                2. Reserved var must be 0.
 * ------------------------------------------------------------------------ */
sint ApplMngr_LoadApplData(
     sint  LoadMode, /* APPLMNGR_AUTO_LOAD/APPL_LOAD/PARAM_LOAD*/
     ulint site_no,
     ApplDownLoadPrm *ApplPrm,  /* if =NULL, use caller parameters */
     char *ApplLoadMess,  /* Pointer to messages, if =NULL, use English */
     sint  AppId,
     ulint Reserved
     );
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_ReplaceAppl
 *
 * DESCRIPTION:   Download new application or/and parameters.
 *
 * RETURN:        >0 - OK, <0 - Error code.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint ApplMngr_ReplaceAppl(
     sint LoadMode, /* APPLMNGR_AUTO_LOAD/APPL_LOAD/PARAM_LOAD/TSP_LOAD*/
     ulint site_no,
     ApplDownLoadPrm *ApplPrm,  /* if =NULL, use caller parameters */
     char *ApplLoadMess  /* Pointer to messages, if =NULL, use English */
     );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_GetCommPrm
 *
 * DESCRIPTION:   Get current communication parameters for down load.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_GetCommPrm(ApplDownLoadPrm *ApplPrm);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ApplMngr_GetExtModemPrm
 * DESCRIPTION:   Get current external modem parameters for down load.
 * RETURN:        void.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void ApplMngr_GetExtModemPrm(ExternalModemPrm *ExtModemPrm);
/* --------------------------------------------------------------------------
 * FUNCTION NAME: ApplMngr_TcpIpDownloadPrm
 * DESCRIPTION:   Get/Set current TCP/IP parameters for download.
 * PARAMETERS     TcpIp - Pointer to Tcpip parameters
 *                Mode  - APPLMNGR_TCPIP_GET or APPLMNGR_TCPIP_SET
 * RETURN:        void.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void ApplMngr_TcpIpDownloadPrm(TcpIpDownloadSafe * TcpIp,byte Mode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_GetNosVers
 *
 * DESCRIPTION:
 *
 * RETURN:        NOS version, as usint.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
usint ApplMngr_GetNosVers(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_GetTerminalID.
 *
 * DESCRIPTION:   Set to BoardID the pointer to CPU board ID string
 *                (16 ASCII characters). If CPU board serial
 *                number does not exist, BoardID=0.
 *
 * RETURN:        Pointer to terminal ID string or 0, if terminal ID
 *                does not exist.
 *                Teminal/board ID format:
 *                PPCHHNNNNNNNMMYY
 *                PP - 2 char of device code.
 *                C  - country code (I,T,U,R,C,H .....), '0' for board ID.
 *                HH - 2 char of hardware model code
 *                NNNNNNN - 7 characters of serial number.
 *                MMYY - month and year of manufacture test
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
char *ApplMngr_GetTerminalID(char **BoardID);
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_GetTerminalInfo.
 *
 * DESCRIPTION:   Get The full terminal info as defined in the terminal
 *                configuration.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_GetTerminalInfo(NuritPlatform *N_Pl);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ApplMngr_CallAppl
 *
 * DESCRIPTION:   This function will call the FLASH application which runs
 *                in user mode from the ROM application which runs is
 *                supervisor mode.
 *
 * PARAMETERS:    Data    - Pointer to data structure to pass to FLASH
 *                          application entry point.
 *
 *                RetCode - Output parameter. On return contains the
 *                          return code from the FLASH application
 *
 * RETURN:        APPLMNGR_APPL_OK      - FLASH application exists.
 *                APPLMNGR_APPL_NOEXIST - FLASH application does not exists.
 *                APPLMNGR_APPL_NOVER   - NOS lacks minimum version for application
 *                APPLMNGR_APPL_NOMEM   - Not enough static data memory to run application
 *
 * NOTES:         The FLASH application entry function must be declared as :
 *
 *                RetType FuncName(void *Data)
 *
 * ------------------------------------------------------------------------ */
sint ApplMngr_CallAppl(void *Data,ulint *RetCode);
#ifdef FOREIGN_PROTOCOL_SUPPORT
/* --------------------------------------------------------------------------
 * FUNCTION NAME: ApplMngr_CustomLoaderConnect
 * DESCRIPTION:   Open Connection For Custom Loader Download.
 * RETURN:        TRUE if connected else FALSE.
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
boolean ApplMngr_CustomLoaderConnect(ApplDownLoadPrm *ApplPrm);  /* if =NULL, use caller parameters */
/* --------------------------------------------------------------------------
 * FUNCTION NAME: ApplMngr_CloseConnection
 * DESCRIPTION:   Close Connection For Custom Loader Download.
 * RETURN:        void.
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void ApplMngr_CloseConnection(void);
#endif

#ifdef __NOS__
  #include applmngr_nos
#endif
#endif