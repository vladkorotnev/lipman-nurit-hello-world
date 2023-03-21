/****************************************************************************
 *                                                                          *
 * FILE NAME:   test.h                                                      *
 *                                                                          *
 * MODULE NAME: TEST.                                                       *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati .                                               *
 *                                                                          *
 * DESCRIPTION: called by main. performed test for I/O devices.             *
 *                                                                          *
 * REVISION:    01.00 18/03/94.                                             *
 *                                                                          *
 * HISTORY:     <Version history>.                                          *
 *                                                                          *
 ****************************************************************************/
#ifndef __TEST_H__
  #define __TEST_H__
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

enum       { POWER_OK ,POWER_LOW ,POWER_VERY_LOW }; /* Current power status */

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

typedef	struct {

	usint	rssi;
	usint	base_stn;
	usint	status;
	usint	reserved;              /* reserved */

} InfoRSSI;

typedef PACKED enum
{
EX_POWER_OPERATING,
INT_BAT_OPERATING
}PowerStatus;


typedef PACKED enum
{
NO_BAT_IN_SYSTEM,
BAT_IS_GOOD,
BAT_IS_LOW,
BAT_IS_VERY_LOW
}BatteryStatus;

typedef struct {
 PowerStatus    power_status;   /* EX_POWER_OPERATING, INT_BAT_OPERATING*/
 BatteryStatus  battery_status; /* NO_BAT_IN_SYSTEM,BAT_IS_GOOD,...*/
} InfoBattery;


           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Test_Battery.
 *
 * DESCRIPTION:   test back-up battery.
 *
 * RETURN:        TRUE/FALSE.
 *
 * NOTES:         (Should be called via menu).
 *
 * ------------------------------------------------------------------------ */

void Test_Battery(void *dummy);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Test_Radio.
 *
 * DESCRIPTION:   test radio activity.
 *
 * RETURN:        TRUE/FALSE.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Test_Radio(void *dummy);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Test_IsEeprom.
 *
 * DESCRIPTION:   Does EEPROM short test.
 *
 * RETURN:        Size of EEPROM if it exist, or 0.
 *
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
usint Test_IsEeprom(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Test_RadioRSSI.
 *
 * DESCRIPTION:   Receives and displays RADIO RSSI and BASE STN.
 *
 * RETURN:        none.
 *
 * NOTES:         (Should be called via menu).
 *
 * ------------------------------------------------------------------------ */
void Test_RadioRSSI(void *dummy);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Test_RadioMan
 *
 * DESCRIPTION:   Displays Radio MAN information
 *
 * RETURN:        none.
 *
 * NOTES:         (Should be called via menu).
 *
 * ------------------------------------------------------------------------ */
void Test_RadioMan(void *dummy);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Test_GetRadioInfo
 *
 * DESCRIPTION:   Displays Radio Product Information
 *
 * RETURN:        none.
 *
 * NOTES:         (Should be called via menu).
 *
 * ------------------------------------------------------------------------ */
void Test_RadioInfo(void *dummy);

#ifdef __NOS__
  #include test_nos
#endif
#endif
