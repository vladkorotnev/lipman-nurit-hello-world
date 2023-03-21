/****************************************************************************
 *                                                                          *
 * FILE NAME:   FSTP.H                                                      *
 * MODULE NAME: FSTP                                                        *
 * PROGRAMMER:  Arie Gleizer                                                *
 * DESCRIPTION: File Transfer Protocol	                      		    *
 * CREATED:     4/10/1999                                                   *
 * REVISION:    16/4/2001                                                   *
 ****************************************************************************/

#ifndef __FSTP_H
#define __FSTP_H

	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/
/* void */

	  /*==========================================*
	   *             I N C L U D E S              *
	   *==========================================*/

#include session_def

	  /*==========================================*
	   *         P A R A M E T E R S              *
	   *==========================================*/
/* void */
	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/

#define	FSTP_FILENAME_LEN 	RD_FILENAME_LEN

	  /*==========================================*
	   *      T Y P E   D E C L A R A T I O N     *
	   *==========================================*/


#ifdef __WIN32__
#pragma option -a1   /* set byte alignement */
#endif

typedef packed struct FILEINFO
{
  char  Name[FSTP_FILENAME_LEN+1]; /* File name            		*/
  byte  Reserved;
  USINT RecLen;		          /* File record length in bytes       	*/
  USINT Records;		  /* Records in File                    */
  ULINT Date;   		  /* File date YYYYMMDD                	*/
  USINT Time;		   	  /* File time HHMM                    	*/
  USINT RecVer;                   /* Record Version assigned by Creator */

} FILEINFO;


#ifdef __WIN32__
#pragma option -a.   /* restore default project alignement */
#endif

typedef enum
{
  FSTP_ERROR,
  FSTP_SUCCESS,
  FSTP_CLOSED,
  FSTP_EOM,
  FSTP_REVERSE,
  FSTP_NOFILE	/* File missing */

} FSTPRESULT;

	   /*=========================================*
	    *        M I S C E L L A N E O U S        *
	    *=========================================*/

	   /*=========================================*
	    *   F U N C T I O N  P R O T O T Y P E S  *
	    *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_IsAppId
 *
 * DESCRIPTION:   Check if AppId is for FSTP
 *
 * RETURN:        none
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------ */

sint FSTP_IsAppId( sint	AppId );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_SetAppId
 *
 * DESCRIPTION:   Set the Appl ID
 *
 * PARAMETES:     Appl Id
 *
 * RETURN:        none
 *
 * NOTES:         Set AppId to 0 (Zero) in order to use Regular Blockcom ApplId
 *                Call this function with 0 before using the Blockcom from NCC.
 *
 * ------------------------------------------------------------------------ */
void FSTP_SetAppId(sint AppId);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_Open
 *
 * DESCRIPTION  : Initializes Session dependent parameters
 *
 * RETURN       : error code
 *
 * NOTES        :
 *
 * ------------------------------------------------------------------------ */
sint FSTP_Open( sint *SessionId, APPINFO *fstp );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_Close
 *
 * DESCRIPTION:   Send frame END_OF_SESSION and close port ...
 *
 * RETURN:        none
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void  FSTP_Close( sint SessionId  );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_Abort
 *
 * DESCRIPTION:   Abort FSTP session
 *
 * RETURN:        error code
 *
 * NOTES:
 * ------------------------------------------------------------------------ */

sint FSTP_Abort( sint SessionId, char *Message );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_End
 *
 * DESCRIPTION:   Send END command
 *
 * RETURN:        none
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void  FSTP_End( sint SessionId  );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_GetFileHeader
 *
 * DESCRIPTION  : Receive a file header
 *
 * RETURN       : Return SUCCESS or error code = reason
 *
 * NOTES        :
 * ------------------------------------------------------------------------ */
sint FSTP_GetFileHeader (
  sint	SessionId,
  char  *FileName,          /* name of file                 */
  FILEINFO  *FileHeader      /* Received File header         */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_Reverse
 *
 * DESCRIPTION:   Send REVERSE command
 *
 * RETURN:        none
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint FSTP_Reverse( sint SessionId  );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_Response
 *
 * DESCRIPTION:   Respond to any command untill reverse control
 *
 * RETURN:        FSTP_REVERSE, FSTP_CLOSED, FSTP_ERROR
 *
 * NOTES:
 * ------------------------------------------------------------------------ */

sint FSTP_Response( sint SessionId );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_GetList
 *
 * DESCRIPTION  : Receive list of files in current folder
 *
 * RETURN       : Return SUCCESS or error code = reason
 *
 * NOTES        : list will be written to file and
 *		  file name will be returned in "ListFile"
 * ------------------------------------------------------------------------ */
sint FSTP_GetList ( sint SessionId, FILEINFO *RecTab, sint *MaxRec );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_DeleteFile
 *
 * DESCRIPTION  : Delete a file
 *
 * RETURN       : Return SUCCESS or error code = reason
 *
 * NOTES        :
 * ------------------------------------------------------------------------ */
sint FSTP_DeleteFile (
  sint	SessionId,
  char  *FileName           /* name of file                 */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_RenameFile
 *
 * DESCRIPTION  : Rename a file
 *
 * RETURN       : Return SUCCESS or error code = reason
 *
 * NOTES        :
 * ------------------------------------------------------------------------ */
sint FSTP_RenameFile (
  sint	SessionId,
  char  *OldFileName,          /* old name of file                 */
  char  *NewFileName           /* new name of file                 */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_RetrieveFile
 *
 * DESCRIPTION  : Receive a file procedure
 *
 * RETURN       : Return SUCCESS or error code = reason
 *
 * NOTES        :
 * ------------------------------------------------------------------------ */
sint FSTP_RetrieveFile (
  sint	SessionId,
  char  *FileName           /* name of file                 */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_StoreFile
 *
 * DESCRIPTION:   Send a file procedure
 *
 * RETURN       : Return SUCCESS or error code = reason
 *
 * NOTES        :
 * ------------------------------------------------------------------------ */
sint FSTP_StoreFile (
  sint	SessionId,
  char  *FileName           /* name of file                 */
);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FSTP_ErrorMessage
 *
 * DESCRIPTION:   Return pointer to error message according to sint
 *
 * RETURN:        char pointer to error message
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

char  *FSTP_ErrorMessage ( sint  sint );


	   /*=========================================*
	    *           E P I L O G                   *
	    *=========================================*/

#ifdef __NOS__
#include FSTP_NOS
#endif

#endif