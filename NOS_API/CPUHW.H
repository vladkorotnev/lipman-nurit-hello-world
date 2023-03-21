/****************************************************************************
 *                                                                          *
 * FILE NAME:   cpuhw.h                                                     *
 *                                                                          *
 * MODULE NAME: cpuhw                                                       *
 *                                                                          *
 * PROGRAMMER:  Jacob Keret                                                 *
 *                                                                          *
 * DESCRIPTION: API functions declarations                                  *
 *                                                                          *
 * REVISION:    01_00. Changed by Ephraim for NURIT-2085 (29/04-98)         *
 *                                                                          *
 ****************************************************************************/
#ifndef __CPUHW_H__
 #define __CPUHW_H__



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


#define UART_A                    0     /* index of 1st UART */
#define UART_B                    1     /* index of 2nd UART */
#define UART_C                    2     /* index of 3nd UART */
#define UART_D                    3     /* index of 4nd UART */
#define UART_E                    4     /* index of 5nd UART */
#define UART_F                    5     /* index of 6nd UART */
#define  _COM1             0
#define  _PINPAD           1
#define  _MODEM            2
#define  _RADIO            3
#define  _RS_232           4
#define  _RS_485           5
#define  _RS_485_MONITOR   6
#define  _COM2_2159        7
#define  _COM3_2159        8

#define  PC_PINPAD_CHANEL         UART_A   /*All devices*/
#define  MODEM_RADIO_CHANEL       UART_B   /*All devices*/
#define  COM2_OR_RS485_CHANEL     UART_C   /*NURIT-2085*/
#define  COM4_OR_RS485_CHANEL     UART_C   /*NURIT-2055*/
#define  COM3_OR_RS485_CHANEL     UART_E   /*NURIT-2058*/
#define  COM2_CHANEL              UART_D   /*NURIT-2055*/
#define  COM3_CHANEL              UART_E   /*NURIT-2055*/
#define  COM4_CHANEL              UART_C   /*NURIT-2058*/
#define  RADIO_CHANEL_2058        UART_F   /*NURIT-2058*/

/* To use with Cpuhw_IsRomAddress: */

#define POINTS_TO_RAM      1
#define NOT_POINTS_TO_RAM  0

#define CPUHW_TEXT_MSG_LEN_SIZE  33   /* Including terminating '\0' */

#define CPUHW_BATSYS_CHARGE         0    /* Battery is charging    */
#define CPUHW_BATSYS_DISCHARGE      1    /* Battery is discharging */
#define CPUHW_BATSYS_NO_CHARGE      2    /* Battery is idle        */
#define CPUHW_BATSYS_NO_BAT         3    /* Battery does not exist */

/* To use with Cpuhw_SetPort8000: */
#define P8000_OUT_OFF                (0x01)
#define P8000_OUT_ON                 (0x02)
#define P8000_OUT_NO_CHANGE          (0x03)
#define P8000_BARCLK_BIT             (0x01)
#define P8000_BARDATA_BIT            (0x02)
          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
typedef PACKED enum
{
EX_CARD=0,
#ifndef NURIT_2159
 SAM1,
 SAM2,
 #ifndef NURIT_8000
  SAM3,
  SAM4,
 #endif
#endif
MAX_SMART_PORT_NUM
} enum_port_indx;

typedef PACKED enum
{
SAM_DISABLE=0,
SAM_ENABLE,
SAM_3v_ENABLE,
SAM_1_8v_ENABLE,
SAM_SYN_ENABLE
}
enum_SAM_mode;


typedef struct
{
  boolean Graphics;
  usint   MaxRows;
  usint   MaxColumns;
} DisplayPnPType;

/* List of cpu_hw message definitions */
typedef enum
{
   CPUHW_MSG_INDEX_LOW_BAT = 0,
   CPUHW_NUM_OF_MSGS
} CpuhwMessages;

/* Messages type to be used by user */
typedef char CpuhwTextMsgs[CPUHW_NUM_OF_MSGS][CPUHW_TEXT_MSG_LEN_SIZE];

/* Battery sub-system status structure */
typedef struct {

  usint        Version;    /* Structure version               */
  boolean      IsBatExist; /* Is there a battery sub-system ? */
  byte         BatEnergy;  /* Battery energy ( 1% - 100% )    */
  byte         BatState;   /* Battery state                   */
  byte         Spare[16];  /* Reserved for future use         */

} CpuhwBatSysType;

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_OpenDrawer.
 *
 * PARAMETERS:    none.
 *
 * DESCRIPTION:   Closes the cashier drawer.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Cpuhw_OpenDrawer(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_TechnicianJumperOn
 *
 * DESCRIPTION:   Returns the status of the technician jump
 *
 * PARAMETERS:    none.
 *
 * RETURN:        TRUE  - Technician jumper is on the jumper
 *                FALSE - Technician jumper is off the jumper
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
boolean Cpuhw_TechnicianJumperOn(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_CheckPhoneLine
 *
 * DESCRIPTION:   Checks if line exist with delay for new hybrid.
 *
 * RETURN:        TRUE  - line is o.k.
 *                FALSE - no line (DC voltage is too low).
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
boolean Cpuhw_CheckPhoneLine(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_SwitchTo.
 *
 * DESCRIPTION:   Switch pinpad/pc option or modem/radio option.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

void Cpuhw_SwitchTo(usint device);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_Switch1Direction.
 *
 * DESCRIPTION:   Return Switch1 direction _COM1 or _PINPAD.
 *
 * RETURN:        _COM1 or _PINPAD
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

usint Cpuhw_Switch1Direction(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_IsBattery.
 *
 * DESCRIPTION:   Inform the application for Battery exist.
 *
 * RETURN:        TRUE for Battery exist, FALSE for Battery not exist.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

boolean Cpuhw_IsBattery(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_GetBatteryEnergy.
 *
 * DESCRIPTION:   Battery status in percent.
 *
 * RETURN:        1. No battery System - returns 0.
 *                2. Battery system without battery monitor
 *                      - returns 50 for good battery
 *                      - returns 5  for low battery
 *                      - returns 1  for very low battery
 *                3. Battery system with battery monitor
 *                      - returns energy in battery in percent (1-100).
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte Cpuhw_GetBatteryEnergy(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_IsRadio.
 *
 * DESCRIPTION:   Inform the application for 2070/2060 models.
 *
 * RETURN:        TRUE for 2070 (with radio), FALSE for 2060 (without radio).
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

boolean Cpuhw_IsRadio(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_IsExternalPower
 *
 * DESCRIPTION:   Check power status.
 *
 * RETURN:        TRUE  - The terminal is running from external power supply
 *                FALSE - The terminal is running from battery power
 *
 * NOTES:         This function was added to CPUHW for the use of the 
 *                application instead of Cpuhw_PowerSense
 *
 * ------------------------------------------------------------------------ */
boolean Cpuhw_IsExternalPower(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_BackLightMenu
 *
 * DESCRIPTION:   This function opens a menu for controlling the backlight
 *                feature.
 *
 * PARAMETERS:    none.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Cpuhw_BackLightMenu(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_SetBackLight
 *
 * DESCRIPTION:   This function sets the backlight parameters
 *
 * PARAMETERS:    BLControl : TRUE  - Backlight control is on
 *                            FALSE - Backlight control is off
 *
 *                BL50Time  : Time in seconds of 50% power duration
 *                            of backlight
 *
 *                BL10Time  : Time in seconds of 10% power duration
 *                            of backlight
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Cpuhw_SetBackLight(boolean BLControl,lint BL50Time,lint BL10Time);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_SetMessages
 *
 * DESCRIPTION:   Sets NOS user messages.
 *
 * PARAMETERS:    Messages - Pointer to a two dimensional array that contains
 *                           the messages :
 *
 *                           Messages[ 0 .. 32] - Message #0
 *                           Messages[33 .. 65] - Message #1
 *                                            .
 *                                            .
 *                                            .
 *
 *                           See the enumerated type CpuhwMessages for messages
 *                           meaning.
 *
 *                           If this poniter is NULL the default english
 *                           nessages will be used.
 *
 * RETURN:        void.
 *
 * NOTES:         The maximum message index is CPUHW_NUM_OF_MSGS
 *
 * ------------------------------------------------------------------------ */
void Cpuhw_SetMessages(const char *Messages);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_GetBatSystemStatus
 *
 * DESCRIPTION:   Returns the battery sub-system status
 *
 * PARAMETERS:    BT - (Output) Pointer to a CpuhwBatSysType structure
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Cpuhw_GetBatSystemStatus(CpuhwBatSysType *BT);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Cpuhw_SetPort8000
 *
 * DESCRIPTION:   Change the status of three outputs of 8000 port: 5v, AUX_OUT 
 *                and CONTR_OUT. New status can be P8000_OUT_ON, P8000_OUT_OFF
 *                and P8000_OUT_NO_CHANGE.
 *
 * RETURN:        Status of two inputs of 8000 port - P8000_BARCLK_BIT and 
 *                P8000_BARDATA_BIT. 
 *
 * NOTES:         For 8000/8010 only. On other devices (not 8000/8010) return 0.
 *
 * ------------------------------------------------------------------------ */
byte Cpuhw_SetPort8000(byte Ext5v_NewStatus, 
                       byte AUX_NewStatus,
                       byte CONTR_NewStatus);

#ifdef __NOS__
  #include cpuhw_nos
#endif
#endif