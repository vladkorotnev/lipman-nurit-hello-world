/****************************************************************************
 *                                                                          *
 * FILE NAME:   SOFT_KB.H                                                   *
 *                                                                          *
 * MODULE NAME: SOFTWARE KEYBOARD                                           *
 *                                                                          *
 * PROGRAMMER:  Rami Rosenbaum                                              *
 *                                                                          *
 * DESCRIPTION: Implementation of a software keyboard on the terminal       *
 *              screen, generating key strokes using the touch-panel.       *
 *                                                                          *
 * REVISION:    01_00                                                       *
 *                                                                          *
 ****************************************************************************/

#ifndef _SOFT_KB_H_
#define _SOFT_KB_H_


          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/


          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/


          /*=========================================*
           *   P U B L I C     F U N C T I O N S     *
           *=========================================*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SoftKB_Disable.
 *
 * DESCRIPTION:   Disable the module, disable TOUCH-PANEL module and clear
 *                keyboard from screan.
 *
 * RETURN:        None.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
void  SoftKB_Disable ( void );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: SoftKB_Enable.
 *
 * DESCRIPTION:   Enable the module, enable TOUCH-PANEL module and draw
 *                keyboard on screan.
 *
 * RETURN:        None.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
void  SoftKB_Enable ( void );


#ifdef __NOS__
  #include soft_kb_nos
#endif

#endif _SOFT_KB_H_ /* #ifndef _SOFT_KB_H_ */
