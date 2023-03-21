/****************************************************************************
 * FILE NAME:   winform.h
 * MODULE NAME: WinForm
 * PROGRAMMER:  CL
 * DESCRIPTION: window form handling: buttons, panels etc.
 * REVISION:    01.00
 ****************************************************************************/
          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
#ifndef __WinForm_H
  #define __WinForm_H
/** This module (WINFORM) deals with three objects: panels, buttons and forms.
 The panel is rectangle placed into display's specific coordinates, that has
 some kind of frame (see enum PanelStyle) and client area image and/or text
 (for structures Text and Icon see GRPHTEXT.H). Optionally, the application
 specified function  can be supplied to show application-dependant image
 (e.g. running string).
 The button is a clickable panel, i.e. button will be activated (
 application-supplied button handler function will be called) if one of the
 events specified in event array occured.
 Currently there are two types of the events : keyboard and timer, but in the
 future other types of events can be added (e.g. CardReader/BarCodeReader
 etc.).
 The form is a set of the buttons and the set of the exit events (events
 which will cause the form to be removed)

 *********************************************************************/

	  /*==========================================*
	   *             I N C L U D E S              *
	   *==========================================*/

#include  winform_def

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
/* void */
          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
/* void */
          /*=========================================*
           *   P U B L I C     F U N C T I O N S     *
           *=========================================*/
/* --------------------------------------------------------------------------
 * FUNCTION NAME: WinForm_ShowPanel
 * DESCRIPTION:   draws panel
 * RETURN:        void
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void WinForm_ShowPanel(Panel *panel, boolean FrameShowFlag);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: WinForm_ClearClientArea
 * DESCRIPTION:   restores the panel's background color in the client area
 * RETURN:        none
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void WinForm_ClearClientArea(Panel *p);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: WinForm_DeletePanel
 * DESCRIPTION:   restores the display background color in the coordinates
 *                of the panel
 * RETURN:        none
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
void WinForm_DeletePanel(Panel *panel);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: WinForm_GetClientArea
 * DESCRIPTION:   calculates the client area of the panel
 * RETURN:        coordinates of the client area
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
Rectangle WinForm_GetClientArea(Panel *panel);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: WinForm_RunForm
 * DESCRIPTION:   draws the set of panels and enters the loop of the
 *                KB input waiting and envoking a panel's handler if the
 *                pressed key matched with this panel's hot_key
 * RETURN:        last choosed button's index (first button has index 0)
 *                in case of the timeout or exit key pressed returns -1
 * NOTES:
 * ------------------------------------------------------------------------ */
short WinForm_RunForm(Form *form, boolean ShowForm);

           /*=========================================*
            *              E P I L O G E              *
            *=========================================*/

#ifdef __NOS__
  #include winform_nos
#endif

#endif /* #ifndef __WinForm_H */
