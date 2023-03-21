/****************************************************************************
 *                                                                          *
 * FILE NAME:   STATIST.H                                                   *
 *                                                                          *
 * MODULE NAME: main.                                                       *
 *                                                                          *
 * PROGRAMMER:  EPHRAIM.                                                    *
 *                                                                          *
 * DESCRIPTION: Statistic types and function.                               *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    05.00 24/08/95.                                             *
 *                                                                          *
 * HISTORY:     <Version history>.                                          *
 *                                                                          *
 ****************************************************************************/
#ifndef __STATIST_H__
  #define __STATIST_H__

	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/
/* void */

	  /*==========================================*
           *             I N C L U D E S              *
	   *==========================================*/
#include dial_3_prm
	  /*==========================================*
	   *         P A R A M E T E R S              *
	   *==========================================*/
/* void */

	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/


	  /*==========================================*
	   *      T Y P E   D E C L A R A T I O N     *
	   *==========================================*/

typedef struct
{
    usint  PwrDownCnt;
    usint  PwrUpCnt;
    usint  PwrOkCnt;
    usint  ResetCnt;
}SystemStatistics1;

typedef struct
{
    usint  ConnectTime;/* time in 100ms units from start of dialing to
                          connect */
    byte   LastConnect;/* 300/1200/2400/FAST2400 etc.*/

    byte   NoDialTone;   /*no permanent tone after lifting the handset */
    byte   NoLine;       /*tel.line disconnected*/
    byte   NoRingBack;   /*silence after dialing the number*/
    byte   Busy;         /*short beeps after dialing the number*/
    byte   NoAnswer;     /*long beeps, the remote handset never lifted*/
    byte   NoAnswerTone; /*no 'whistle' of the remote modem */
    byte   NoHandshake;  /*modem's handshake failed*/
} PhoneStatistics1; /* per destination(phone number) */
typedef struct
{
  PhoneStatistics1 PhoneStat[MAX_PH_NUM_PER_TARGET];
} CommStatistics1;  /*fail reasons for a dial target */


	   /*=========================================*
	    *        M I S C E L L A N E O U S        *
	    *=========================================*/

	   /*=========================================*
	    *   F U N C T I O N  P R O T O T Y P E S  *
	    *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Statistics_System.
 * DESCRIPTION:   Read power  down/up and reset statistics to StatBuf.
 * RETURN:        none.
 * NOTES:         ResetFlag=TRUE  will reset statistics counters to 0
                  ResetFlag=FALSE will leave statistics counters as is
 * ------------------------------------------------------------------------ */
void Statistics_System(void *StatBuf, usint BufSize, boolean ResetFlag);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Statistics_Communication
 * DESCRIPTION:   Read communication statistics to Buf.
 * RETURN:        none.
 * NOTES:         ResetFlag=TRUE  will reset statistics counters to 0
                  ResetFlag=FALSE will leave statistics counters as is
 * ------------------------------------------------------------------------ */
void Statistics_Communication(void *Buf, usint BufSize, boolean ResetFlag);

#ifdef __NOS__
  #include statistics_nos
#endif

#endif    /* #ifndef __STATIST_H__ */
