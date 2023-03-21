/****************************************************************************
 *                                                                          *
 * FILE NAME:   APPLOAD.H                                                   *
 *                                                                          *
 * MODULE NAME: APPLOAD                                                     *
 *                                                                          *
 * PROGRAMMER:  Ephraim     		                                            *
 *                                                                          *
 * DESCRIPTION: Application download from NURIT to NURIT                    *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01.00 25/12/1997.                                           *
 *                                                                          *
 ****************************************************************************/


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
/*------- Copy mode -----------*/
#define    APPLOAD_OUT                0
#define    APPLOAD_APL                1
#define    APPLOAD_PRM                2
#define    APPLOAD_ALL                3

/*------- Return codes -----------*/
#define    APPLOAD_OK                 0
#define    APPLOAD_HANDSHAKE_TOUT     1
#define    APPLOAD_APL_NO_MATCH       2
#define    APPLOAD_NOS_NO_MATCH       3
#define    APPLOAD_PARAMS_NO_SUPPORT  4
#define    APPLOAD_FLASH_ERR         -1
#define    APPLOAD_USER_BREAK        -2
#define    APPLOAD_COMM_ERROR        -3
#define    APPLOAD_TR_ERR            -4
#define    APPLOAD_REC_ERR           -5
#define    APPLOAD_TOUT_ERR          -6
#define    APPLOAD_REC_ACK           -7



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
 *
 * FUNCTION NAME: Appload_Copy
 *
 * DESCRIPTION:   Application or/and parameters copy: main function.
 *
 * RETURN:        Error code, if error or copy out.
 *
 * NOTES:         If OK in copy in mode, reset for go to new application.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Appload_Copy(byte mode,/*APPLOAD_OUT/APL/PRM/ALL*/
             char *ApplLoadMess);  /* Pointer to messages, if =NULL, use English */
/*
  Example:
    Appload_Copy(APPLOAD_APL,NULL);  - Use the standart English messages.
For to use the user messages:
    Appload_Copy(APPLOAD_APL,&AploadMessages[0][0]);

static const char AploadMessages[20][17]={
{"COPY OUT:       "},
{"Copy APPL:      "},
{"Copy PARAMS:    "},
{"Copy APPL+PARAMS"},
{"Wait for Master "},
{"Wait for REQ.!  "},
{"Wait for ID     "},
{"Wait for DATA   "},
{"ERASE! Wait...  "},
{"Read from       "},
{"Write to        "},
{"DOWNLOAD SUCCESS"},
{"COMMUNIC. ERROR!"},
{"FLASH ERASE ERR!"},
{"FLASH WRITE ERR!"},
{"Not Enough RAM  "},
{"Not Enough FLASH"},
{"NOS is mismatch!"},
{"Fail! ENT->Retry"},
{"ESC->SystemReset"}};
*/

#ifdef __NOS__
  #include appload_nos
#endif
