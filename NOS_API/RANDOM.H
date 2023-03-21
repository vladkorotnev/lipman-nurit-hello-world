/****************************************************************************
 *                                                                          *
 * FILE NAME:   RANDOM.H                                                    *
 *                                                                          *
 * MODULE NAME: Random                                                      *
 *                                                                          *
 * PROGRAMMER:  Oren Sokoler                                                *
 *                                                                          *
 * DESCRIPTION: Random number generator public definitions                  *
 *                                                                          *
 * REVISION:    01.00 31/05/04.                                             *
 *                                                                          *
 ****************************************************************************/

#ifndef __RANDOM_H_
#define __RANDOM_H_

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
           
/* void */

           /*=========================================*
            *   P U B L I C     F U N C T I O N S     *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Random_GetRnd
 *
 * DESCRIPTION:   Returns an unsigned short (16 bit) random number 
 *
 * PARAMETERS:    none.
 *
 * RETURN:        Random number 
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
usint Random_GetRnd ( void );


#ifdef __NOS__
  #include random_nos
#endif

#endif