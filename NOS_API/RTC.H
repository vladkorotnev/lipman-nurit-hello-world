/****************************************************************************
 *                                                                          *
 * FILE NAME:   RTC.H                                                       *
 *                                                                          *
 * MODULE NAME: RTC                                                         *
 *                                                                          *
 * PROGRAMMER:  Yossi Rubinstein                                            *
 *                                                                          *
 * DESCRIPTION: Driver for Setting and reading the RTC model S-3510A.       *
 *              Private declarations.                                       *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01.00  22/03/1998.                                          *
 ****************************************************************************/

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


/* For 3150 Only */
#define        RTC_OK            0
#define        RTC_NO_SET        1    /* RTC in disable mode. */
#define        RTC_DATA_INVALID  2
#define        RTC_NO_CLOCK      3
#define        RTC_SLOW_CLOCK    4
#define        RTC_FAST_CLOCK    5
#define        RTC_INVALID       6
#define        RTC_NEW_DATA      7
#define        RTC_UPDATE        8    /* update RTC by last time */

              /* The times here are in BCD format */

/* For Both RTC types */
typedef struct
   {
      byte seconds;
      byte minutes;
      byte hours;
      byte day;
      byte month;
      byte year;
      long ldate;
      long ltime;
   }real_time_clock;





          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
/* void */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

	   /*=========================================*
	    *   F U N C T I O N  P R O T O T Y P E S  *
	    *=========================================*/

/* --------------------------------------------------------------------------
*
* FUNCTION NAME: Rtc_Read.
*
* DESCRIPTION:   Read the real-time clock.
*
* RETURN:        none.
*
* NOTES:         none.
*
* ------------------------------------------------------------------------ */
void Rtc_Read(real_time_clock *time
        /* time - the structure in which the information is stored */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Rtc_SetTime.
 *
 * DESCRIPTION:   Set the real time clock.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Rtc_SetTime(real_time_clock *time
     /* stucture which contains the information for setting the time */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Rtc_SetDate.
 *
 * DESCRIPTION:   Set the real-time clock date.
 *
 * RETURN:        none.
 *
 *  NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Rtc_SetDate(real_time_clock *time /* structure which contains the
                                        information for setting the date */);

#ifdef __NOS__
  #include rtc_nos
#endif
