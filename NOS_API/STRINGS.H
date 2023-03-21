/****************************************************************************
 * FILE NAME:   Strings.h
 * MODULE NAME: Strings
 * PROGRAMMER:  Barak Schiby
 * DESCRIPTION: RunTime used of data blocks containing Strings
 * REVISION:    01.00
 * DATE:        18.04.01
 ****************************************************************************/

#ifndef __STRINGS_H
#define __STRINGS_H

          /*==========================================*
           *   P U B L I C    F U N C T I O N S       *
           *==========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Strings_GetStr
 *
 * DESCRIPTION:   This function retrive a Sting out of the Application
 *                Strings list in the flash
 *
 * PARAMETERS:    StrID - ID of the wanted string
 *
 *     RETURN:    Null terminated String
 *
 *       NOTE:    none
 * ------------------------------------------------------------------------ */
const byte * Strings_GetStr (usint StrID);

#ifdef __NOS__
  #include strings_nos
#endif

#endif