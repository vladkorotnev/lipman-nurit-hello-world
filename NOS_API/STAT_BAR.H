/****************************************************************************
 *                                                                          *
 * FILE NAME:   STAT_BAT.H                                                  *
 *                                                                          *
 * MODULE NAME: STATUS BAR.                                                 *
 *                                                                          *
 * PROGRAMMER:  Ephraim & Svetlana.                                         *
 *                                                                          *
 * DESCRIPTION: Battery & Radio Status                                      *
 *                                                                          *
 * REVISION:    01.00 23/12/99.                                             *
 *                                                                          *
 ****************************************************************************/

#ifndef _STAT_BAR_H_
#define _STAT_BAR_H_

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
/* void */

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

/* Status for display of Time. */
#define  STATUSBAR_MODE_DEFAULT  0x00000000      /* No display.   */
#define  STATUSBAR_MODE_TIME     0x00000001      /* Display time. */
#define  STATUSBAR_MODE_DATE     0x00000002      /* Display date. */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: StatusBar_SetMode
 *
 * DESCRIPTION:   Set mode ( for Date/Hour display, etc.)
 *
 * INPUT:         Stat - STATUSBAR_MODE_DEFAULT, STATUSBAR_MODE_TIME,
 *                       STATUSBAR_MODE_DATE.
 *
 * RETURN:        void.
 *
 * NOTES:         Stat is a bitmap. For now, no combination is possible.
 *
 * ------------------------------------------------------------------------ */
void StatusBar_SetMode ( ulint Stat );

#ifdef __NOS__
  #include stat_bar_nos
#endif

#endif /* _STAT_BAR_H_ */
