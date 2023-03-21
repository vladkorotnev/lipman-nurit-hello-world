/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * FILE NAME:   SETUP_DB.H                                                 *
 * MODULE NAME: SetupDB                                                    *
 * PROGRAMMER:  Hai Shalom                                                 *
 * DESCRIPTION: Manage application setup variables in Data-Base.           *
 * REVISION:    01.00                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __SETUP_DB_H
#define __SETUP_DB_H

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/


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
/* void */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SetupDb_Read
 * DESCRIPTION:   Read setup variables from RAM.
 * RETURN:        TRUE if successful, FALSE if an error has occurred.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
boolean SetupDb_Read( byte *Data, usint Size );

/* --------------------------------------------------------------------------
 * FUNCTION NAME: SetupDb_Write
 * DESCRIPTION:   Write setup variables to RAM.
 * RETURN:        TRUE if successful, FALSE if an error has occurred.
 * NOTES:         None
 * ------------------------------------------------------------------------*/
boolean SetupDb_Write( byte *Data, usint Size );

#ifdef __NOS__
  #include setup_db_nos
#endif

#endif