/****************************************************************************
 *                                                                          *
 * FILE NAME:   BlockDsc.h                                                  *
 *                                                                          *
 * MODULE NAME: BlockDsc                                                    *
 *                                                                          *
 * PROGRAMMER:  Barak Schiby                                                *
 *                                                                          *
 * DESCRIPTION: Blocks Descriptor Maneger    	                            *
 *                                                                          *
 * REVISION:    01.00                                                       *
 ****************************************************************************/
#ifndef __BLOCKDSC_H__
 #define __BLOCKDSC_H__

#define BLOCK_DSC_OK           0
#define BLOCK_DSC_FATAL_ERROR -1     /*   */
#define BLOCK_DSC_NO_MORE     -4     /* No more blocks  */


   /*=========================================*
    *         I N T R O D U C T I O N         *
    *=========================================*/
   /*=========================================*
	   *             I N C L U D E S             *
	   *=========================================*/

	

	  /*=========================================*
	   *     P U B L I C   F U N C T I O N S     *
	   *=========================================*/
/* --------------------------------------------------------------------------
* FUNCTION NAME: BlockDsc_BuildDescriptor
* DESCRIPTION:   Build terminal information of the terminals blocks.
* RETURN:        BLOCK_DSC_OK
*                BLOCK_DSC_FATAL_ERROR
* NOTE:          This function should be called  before looping with BlockDsc_Next 
*                function.
*                e.g:
*                BlockDsc_BuildDescriptor()
*                for(...)
*                { ...
*                 BlockDsc_NextData();
*                  ...
*                }
* ------------------------------------------------------------------------ */
sint BlockDsc_BuildDescriptor(void);
/* --------------------------------------------------------------------------
* FUNCTION NAME: BlockDsc_Next
* DESCRIPTION  : Return block description as collected in the start function
* PARAMETERS   : char * Str (Output)- The returned block descriptor string.
*                usint  Size(Input )- Size of Str(Minimum 100 bytes). 
* RETURN:        BLOCK_DSC_OK 
*                BLOCK_DSC_FATAL_ERROR  -No privios call to BlockDsc_BuildDescriptor.         
*                BLOCK_DSC_NO_MORE  -
* NOTE:          This Function should be called after a privious call to 
*                BlockDsc_BuildDescriptor.
* ------------------------------------------------------------------------ */
sint BlockDsc_Next (char * Str , usint Size);
#ifdef __NOS__
 #include blockdsc_nos
#endif
#endif
