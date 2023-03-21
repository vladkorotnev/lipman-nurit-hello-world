/****************************************************************************
 *                                                                          *
 * FILE NAME:   RTCUTIL.H                                                   *
 *                                                                          *
 * MODULE NAME: RTCUTIL                                                     *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati.                                                *
 *                                                                          *
 * DESCRIPTION: Rtc utility functions (Setting time, Displaying Time,       *
 *              Etc..)                                                      *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    1.00 04/11/94.                                              *
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

#define RTCUTIL_ALARM_SET_FAIL 0
#define RTCUTIL_ALARM_SET_OK   1
      
	  /*==========================================*
	   *       P R I V A T E  T Y P E S           *
	   *==========================================*/

	  /*==========================================*
	   *        P R I V A T E  D A T A            *
	   *==========================================*/

	   /*=========================================*
	    *        M I S C E L L A N E O U S        *
	    *=========================================*/

	   /*=========================================*
	    *   P U B L I C     F U N C T I O N S     *
	    *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RtcUtil_GetLongDate
 *
 * DESCRIPTION:   Make an unsigned long int out of date formed : MMDDYY
 *
 * RETURN:        a long integer formed (YYYYMMDD) hex.
 *
 * NOTES:         Date from RTC is Received in BCD code.
 *                e.g. the year 89 would be 10001001 binary or Hex 89
 *                and not 89 decimal.
 *
 * ------------------------------------------------------------------------ */
ulint RtcUtil_GetLongDate(real_time_clock *time);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RtcUtil_SetTimeDate
 *
 * DESCRIPTION:   Displays and sets time & date.
 *
 * RETURN:        none
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void RtcUtil_SetTimeDate(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RtcUtil_EnterDate
 *
 * DESCRIPTION:   Editor for Date.
 *
 *                header  : string to be displayed as header.
 *                date_str: date string to be edited.
 *                          date_str format:
 *                          "MMDDYY" - if date format was set MONTH_DAY_YEAR
 *                          "DDMMYY" - if date format was set DAY_MONTH_YEAR
 *
 * RETURN:        date string in the field date_str.
 *                return value:
 *                True - if date_str was set.
 *                False - if wasn't (ESC pressed - date_str could be
 *                        dummy !).
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
boolean RtcUtil_EnterDate(char *header,char *date_str);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RtcUtil_Enter_TimeOrDate.
 *
 * DESCRIPTION:   Wait for time or date input.
 *
 * RETURN:        last keystroke before exit.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
char RtcUtil_Enter_TimeOrDate(char *str,char *text,char *valids,char *currtext,byte place);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RtcUtil_ResetPwrOnAlarm
 *
 * DESCRIPTION:   Resets\disable the the power-on alarm.
 *
 * PARAMETERS:    none.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void RtcUtil_ResetPwrOnAlarm(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RtcUtil_SetPwrOnAlarm
 *
 * DESCRIPTION:   Sets the the power-on alarm.
 *
 * PARAMETERS:    The time to wake up
 *
 * RETURN:        RTCUTIL_ALARM_SET_FAIL if failed to set the alarm.
 *                RTCUTIL_ALARM_SET_OK   if alarm was set successfuly.
 * NOTES:         The resolution is in min within 24hr 
 *                means 22:32 every night.
 *
 * ------------------------------------------------------------------------ */
sint RtcUtil_SetPwrOnAlarm(real_time_clock *time);


#ifdef __NOS__
  #include rtcutil_nos
#endif
