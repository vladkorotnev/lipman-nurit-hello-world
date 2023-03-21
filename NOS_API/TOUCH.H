/****************************************************************************
 *                                                                          *
 * FILE NAME:   TOUCH.H                                                     *
 *                                                                          *
 * MODULE NAME: TOUCH                                                       *
 *                                                                          *
 * PROGRAMMER:  Rami Rosenbaum                                              *
 *                                                                          *
 * DESCRIPTION: Touch panel driver.                                         *
 *                                                                          *
 * REVISION:    02_00                                                       *
 *                                                                          *
 ****************************************************************************/

#ifndef __TOUCH_H__
#define __TOUCH_H__

          /*==========================================*
           *             I N C L U D E S              *
           *==========================================*/

#include touch_def               /* Module Structures */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

#define     TOUCH_OK                  0
#define     TOUCH_FAIL                1
#define     TOUCH_TIMEOUT             2
#define     TOUCH_NOT_READY           3
#define     TOUCH_NOT_PRESSED         4
#define     TOUCH_BUF_OVERFLOW        5
#define     TOUCH_DISABLED            6
#define     TOUCH_USER_BREAK          7

#define     TOUCH_ERROR_PARAM       101
#define     TOUCH_NO_POINT          102



          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
/*
 *   See touch.def
 */
          /*=========================================*
    	     *  INLINE FUNCTIONS IMPLEMENTED BY MACROS *
   	     *=========================================*/

/* --------------------------------------------------------------------------
 * MACRO NAME:    TOUCH_SAME_POINT
 * DESCRIPTION:   Are p1 & p2 the same point?
 * RETURN:        TRUE/FALSE.
 * NOTES:         p1 & p2 are of type point.
 * ------------------------------------------------------------------------ */
#define  TOUCH_SAME_POINT(p1,p2) ( (p1).X==(p2).X && (p1).Y==(p2).Y)


          /*=========================================*
           *   P U B L I C     F U N C T I O N S     *
           *=========================================*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Touch_Disable
 *
 * DESCRIPTION:   Disables the touch panel.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Touch_Disable(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Touch_Enable
 *
 * DESCRIPTION:   Clear module data and enable the module.
 *
 * RETURN:        void.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Touch_Enable ( void );

 
/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Touch_GetPoint
 *
 * DESCRIPTION:   Read one point from the touch panel.
 * 
 * PARAMETERS:    P - (Output) Pointer to a point structure to fill
 *
 * RETURN:        TOUCH_OK          - Point read O.K.
 *                TOUCH_NOT_READY   - The touch sample is not ready.
 *                TOUCH_NOT_PRESSED - The pen is not pressed on the screen.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Touch_GetPoint(Point *P);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Touch_GetDiscretePoint
 *
 * DESCRIPTION:   Read a discrete point from the touch panel.
 * 
 * OUTPUT:        P - Pointer to a point structure to fill
 *
 * RETURN:        TOUCH_OK            - Point read O.K.
 *                TOUCH_ERROR_PARAM   - Null Pointer assignment.
 *                TOUCH_NOT_READY     - The touch sample is not ready.
 *                TOUCH_NOT_PRESSED   - The pen is not pressed on the screen.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint Touch_GetDiscretePoint ( Point* P );



#ifdef __NOS__
  #include touch_nos
#endif

#endif __TOUCH_H__
