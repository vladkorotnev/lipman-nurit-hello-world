/****************************************************************************
 *                                                                          *
 * FILE NAME:   ATMHW.H                                                     *
 *                                                                          *
 * MODULE NAME: ATMHW   					                                     *
 *                                                                          *
 * PROGRAMMER:                                                              *
 *                                                                          *
 * DESCRIPTION: The ATMEVENT Module supports the ATM spcific HW,            *
 *              detects the events of ATM hardwere and stores them into     *
 *              cyclic buffer for using by application.                     *
 *                                                                          *
 * REVISION:    00.01   18/04/2002.                                         *
 *                                                                          *
 ****************************************************************************/

#ifndef __ATMHW_H
#define __ATMHW_H

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
/* void */

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

typedef  enum { ResetEvent,
                FatalErrorEvent,
                NewNOSEvent,
                PwrOnEvent,
                PwrLossEvent,
                ShutDownEvent,
                PwrOkEvent,
                PwrUpEvent,
                OutOfPaperEvent,
                LowPaperEvent,
                PaperOkEvent,
                AtmDoorOpenEvent,
                AtmDoorCloseEvent,
                AtmCabinetOpenEvent,
                AtmCabinetCloseEvent,
                TechModeOnEvent,
                TechModeOffEvent,
                AtmAlarm1_OnEvent,
                AtmAlarm1_OffEvent,
                AtmAlarm2_OnEvent,
                AtmAlarm2_OffEvent,
                PhoneLineDisconnectEvent,
                PhoneLineConnectEvent,
                EventBufOverflowEvent,
                EventBufCorruptedEvent,
                MaxNumEvent
              } ATM_EventType;


typedef struct
   {
      byte seconds;
      byte minutes;
      byte hours;
      byte day;
      byte month;
      byte year;
      byte event;
      byte CheckSum;
   }AtmEventStr;


	   /*=========================================*
	    *   P U B L I C       F U N C T I O N S   *
	    *=========================================*/
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: AtmHw_GetEvent
 *
 * DESCRIPTION:   Pull the event from events FIFO buffer, if it isn't empty.
 *
 * RETURN:        TRUE  - some event exist;
 *                FALSE - event buffer is empty.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
boolean AtmHw_GetEvent(AtmEventStr *NextEvent);
#ifdef __NOS__
  #include atmhw_nos
#endif

#endif /* __ATMHW_H */
