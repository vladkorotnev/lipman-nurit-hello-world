/****************************************************************************
 *                                                                          *
 * FILE NAME:   SESSION.H                                                   *
 *                                                                          *
 * MODULE NAME: SESSION                                                     *
 *                                                                          *
 * PROGRAMMER:  Arie Gleizer                                                *
 *                                                                          *
 * DESCRIPTION: Session Communication Protocol Layer.                       *
 *                                                                          *
 * REVISION:    01_00                                                       *
 *                                                                          *
 *                                                                          *
 ****************************************************************************/

#ifndef __SESSION_H
#define __SESSION_H


	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/


	  /*==========================================*
	   *             I N C L U D E S              *
	   *==========================================*/

#include session_def
#ifdef _WindowsSw
#include session_nos
#endif
	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/

/*******************/
/* Standart Output */
/*******************/

/* Text messages Indexes for use with New text/language set: */
typedef enum
{                             /* Default Text String: */
  /* User software bugs: */
  BUG_ALREADY_OPENED = 0,     /*"Session already opened!"*/
  BUG_SES_NOT_OPENED,         /*"Session Not opened!"*/
  BUG_WRONG_SES_INDX,         /*"Wrong Session Index!"*/
  BUG_OUT_OF_SYNC,            /*"Out of Rx-Tx synchronization!"*/
  BUG_OUT_OF_STRUCT_SYN,      /*"Out of Structure synchronization!"*/
  BUG_FRAMES_ERROR,           /*"Frame Managment Error!"*/

  /* Status/Error on communication */
  SESS_ABORTED,                /*"Session Aborted."*/
  UNDEXPECTED_FRAME_RECEIVED, /*"Unexpected Frame."*/
  ERROR_SETTING_ZIP,          /*"Error setting Zip"*/
  ERROR_SETTING_UZIP,         /*"Error setting UZip"*/
  ERROR_BAD_INPUT,            /*"Comm Error On Lower Level due to bad inpt."*/
  ABORTED_BY_OTHER_SIDE,       /*"Session Aborted on other side."*/
  ABORT_NOT_COMPLETED,        /*"Couldn't complete abort procedure." -
				 double user break ! */
  HW_LEVEL_ERROR,             /*"Hardware Level Failure or T.O." */
  LOGIC_LEVEL_ERROR,          /*"Logic Level Failure."*/
  BUG_ZIP_ERROR,              /*"ZIP Error"*/
  /*****************************************/
  /**** defines number of text messages ****/
  /*****************************************/
  NUM_OF_SES_MSGS
} SESSION_MESSAGES;

/**************************/
/*** Session Types      ***/
/**************************/

#define SESSION_WAIT     0
#define SESSION_OK       1
#define SESSION_OPENED   2
#define SESSION_CLOSED   3
#define SESSION_EOM      4
#define SESSION_FAILURE -2
#define SESSION_BROKEN  -3

#define MAX_MSG_TEXT 64 /* Up to 64 bytes of Error/Status Messages */

	   /*=========================================*
	    *   P U B L I C     F U N C T I O N S     *
	    *=========================================*/



/*########################################################################
FUNCTION NAME: RS232_SetAbortFunc
DESCRIPTION  :
RETURN       :
NOTES        :
########################################################################*/
void SESSION_SetDispFunc( void (*func)(sint port, char *msg, sint flag) );

/*########################################################################
FUNCTION NAME: SESSION_DispOnOff
DESCRIPTION  : Enables or disables Displaying messages on screen
RETURN       :
NOTES        : on = 1 : display ; on = 0: don't display
########################################################################*/
void SESSION_DispOnOff( sint on );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_Reset
 *
 * DESCRIPTION:   Reset All Sessions parameters.
 *
 * RETURN:        None.
 *
 * NOTES:         Called Before Any Session_Create.
 *
 * ------------------------------------------------------------------------ */
void Session_Reset(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_OpenNbm
 *
 * DESCRIPTION:   Open Communication Session in none blockimg mode
 *                *sp - pointer to a static Session parameter structure
 *
 *                (May Also Set/Initializes under layer - Depend on system).
 *
 * RETURN:        SESSION_OPENED - Session Opened.
 *                SESSION_NONE   - Session not opened
 *                SESSION_FAILURE   Bad Session Index or Already opened
 *                          (Might occures if session not created)
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         Called by initiator (Caller) side.
 *
 * ------------------------------------------------------------------------ */
sint Session_OpenNbm( sint SessionId, SesPrm *slp, SesPrm *srp );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_Open
 *
 * DESCRIPTION:   Open Communication Session in blockimg mode
 *                *sp - pointer to a static Session parameter structure
 *
 *                (May Also Set/Initializes under layer - Depend on system).
 *
 * RETURN:        SESSION_OPENED - Session Opened.
 *                SESSION_NONE   - Session not opened
 *                SESSION_FAILURE   Bad Session Index or Already opened
 *                          (Might occures if session not created)
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         Called by initiator (Caller) side.
 *
 * ------------------------------------------------------------------------ */
sint Session_Open( sint SessionId, SesPrm *slp, SesPrm *srp );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_WaitForOpenNbm
 *
 * DESCRIPTION:   Check if Session Opened in none blockimg mode
 *
 *                sp - inside will be put Session parameters
 *                     if session opened.
 *
 * RETURN:        SESSION_OK - session opened.
 *                SESSION_CLOSED - opened & closed immidialtely.
 *                SESSION_WAIT - still not opened.
 *                SESSION_FAILURE - Communication error - Session Closed.
 *                          Or Bad Session Index or Already opened - Bug !
 *                          (Might occures if session not created)
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         Called by Host side.
 *
 * ------------------------------------------------------------------------ */
sint Session_WaitForOpenNbm( sint SessionId, SesPrm *slp, SesPrm *srp );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_WaitForOpen
 *
 * DESCRIPTION:   Check if Session Opened in blockimg mode
 *
 *                sp - inside will be put Session parameters
 *                     if session opened.
 *
 * RETURN:        SESSION_OK - session opened.
 *                SESSION_CLOSED - opened & closed immidialtely.
 *                SESSION_WAIT - still not opened.
 *                SESSION_FAILURE - Communication error - Session Closed.
 *                          Or Bad Session Index or Already opened - Bug !
 *                          (Might occures if session not created)
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         Called by Host side.
 *
 * ------------------------------------------------------------------------ */
sint Session_WaitForOpen( sint SessionId, SesPrm *slp, SesPrm *srp );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_Close
 *
 * DESCRIPTION:   Close Communication Session.
 *
 * RETURN:        SESSION_OK - Ok, Session Closed successfuly.
 *                SESSION_BROKEN - user break - Sesion closed.
 *                          break text -> put in the standard error.
 *                SESSION_FAILURE - Communication error/aborted - However,
 *                          Session closed.
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_Close(sint SessionId);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_Abort
 *
 * DESCRIPTION:   Abort Communication Session.
 *
 * RETURN:        SESSION_OK - Ok, Session Aborted successfuly.
 *                SESSION_BROKEN -  break - Sesion closed.
 *                           break text -> put in the standard error.
 *                SESSION_FAILURE - Communication error/aborted - However,
 *                          Session closed.
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *                          On any mater, error text -> put in the standard
 *                          error.
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_Abort(sint SessionId,
		   char *abort_text/*Abort reason to be sent to other side*/);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_RxStruct
 *
 * DESCRIPTION:   Receives Structure (Single structure or
 *                multiple but not part of structure).
 *
 * RETURN:        SESSION_OK - Ok, Receive success.
 *
 *                SESSION_EOM - Ok, Receive success & End of Message.
 *
 *                SESSION_CLOSED  - Session Normally Closed.
 *		               With or without received data.
 *                             (Depends on Other side)
 *
 *                SESSION_BROKEN - user break - Sesion closed.
 *                          break text -> put in the standard error.
 *
 *                SESSION_FAILURE - Communication error/aborted or non structure size
 *                          synchronization  - However, Session closed.
 *
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_RxStruct(sint SessionId,
		      void *buf,/* structure buffer */
		      usint size/* structure buffer size in bytes */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_RxMsg
 *
 * DESCRIPTION:   Receives Full Msg (till EOM).
 *
 * RETURN:        SESSION_OK - Ok, Receive success till EOM.
 *
 *                SESSION_CLOSED  - Session Normally Closed.
 *		               With or without received data.
 *                             (Depends on Other side)
 *
 *                SESSION_BROKEN - user break - Sesion closed.
 *                          break text -> put in the standard error.
 *
 *                SESSION_FAILURE - Aborted,Communication error or requested
 *                          size too small,
 *                          However, Session closed.
 *
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *
 *                          On any matter, error text -> put in the standard
 *                          error.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_RxMsg(sint SessionId,
		   void *buf,/* full msg buffer */
		   usint *size/* input : msg buffer size in bytes
				 output : actual size received */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_TxStruct
 *
 * DESCRIPTION:   Sends Structure.
 *
 * RETURN:        SESSION_OK - Ok, Send success.
 *
 *                SESSION_BROKEN - user break - Sesion closed.
 *                          break text -> put in the standard error.
 *
 *                SESSION_FAILURE - Aborted,Communication error -
 *                          However, Session closed.
 *
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_TxStruct(sint SessionId,
		      void *buf,/* structure buffer */
		      usint size/* structure buffer size in bytes */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_EOM
 *
 * DESCRIPTION:   Sends EOM(End Of Message) notification.
 *                (Used After the TxStruct which completes the message).
 *
 * RETURN:        SESSION_OK - Ok, Send success.
 *
 *                SESSION_BROKEN - aborted/user break - Sesion closed.
 *                          abort/break text -> put in the standard error.
 *
 *                SESSION_FAILURE - Communication error -
 *                          However, Session closed.
 *
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_EOM(sint SessionId);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_TxMsg
 *
 * DESCRIPTION:   Sends Full Message (with EOM).
 *
 * RETURN:        SESSION_OK - Ok, Send success.
 *
 *                SESSION_BROKEN - aborted/user break - Sesion closed.
 *                          abort/break text -> put in the standard error.
 *
 *                SESSION_FAILURE - Communication error -
 *                          However, Session closed.
 *
 *                          or:
 *                          Bad Session Index or Not Opened -
 *                          Software bug ! - Session may not be created.
 *
 *                          On any mater, error text -> put in the standard
 *                          error.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
sint Session_TxMsg(sint SessionId,
		   void *buf,/* msg buffer */
		   usint size/* msg buffer size in bytes */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_Create
 *
 * DESCRIPTION:   Create a single Session Entity:
 *                return session's index in SessionId parameter.
 *
 * RETURN:        SESSION_OK - Created.
 *                SESSION_FAILURE - No More Session Entities
 *                          Or Session was not Reset with Session_Reset.
 *
 * NOTES:         Called at initialization time.
 *                Must not be called before Session_Reset.
 *
 * ------------------------------------------------------------------------ */
sint Session_Create( sint *SessionId);/* Output:Session Handle/Index */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_CloseAll
 *
 * DESCRIPTION:   Close all Sessions:
 *
 * RETURN:        None
 *
 * NOTES:         Called at end of proccess.
 *
 * ------------------------------------------------------------------------ */
void Session_CloseAll( void );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_DefaultMessages
 *
 * DESCRIPTION:   Assign Session Text Messages pointers to the Default
 *                English Messages -> Which means Default messages set.
 *
 * RETURN:        None.
 *
 * NOTES:         May called from application if wish to return the
 *                session status/errors text to the default set
 *                after used Session_NewMessage.
 *
 * ------------------------------------------------------------------------ */
void Session_DefaultMessages(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_NewMessage
 *
 * DESCRIPTION:   Assign Session Messages pointer to user defined text.
 *
 * RETURN:        None.
 *
 * NOTES:         May called from application if wish to change the
 *                language/text of the status/error text.
 *
 * ------------------------------------------------------------------------ */
void Session_NewMessage(usint index,/* Any value defined in the
				       enumerated type for Message' indexes */
			char *text);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_TxWord
 *
 * DESCRIPTION:   Sends a word.(Unsigned Short Integer(2 bytes))
 *
 * RETURN:        SESSION_OK,SESSION_FAILURE,SESSION_BROKEN...(see _TxStruct)
 *
 * NOTES:         Used for keeping the same Word -> Bytes Transformation
 *                regardless of CPU type.
 * ------------------------------------------------------------------------ */
sint Session_TxWord(sint ses, /* Session Entity Index */
		    usint w);         /* Word to send */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_RxWord
 *
 * DESCRIPTION:   Receives a word (Unsigned Short Int).
 *
 * RETURN:        SESSION_OK,SESSION_FAILURE,SESSION_BROKEN...(see _RxStruct)
 *
 * NOTES:         Used for keeping the same Bytes -> Word Transformation
 *                regardless of CPU type.
 * ------------------------------------------------------------------------ */
sint Session_RxWord(sint ses /* Session Entity Index */,
		     usint *w /* inside word will be put */);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_TxLong
 *
 * DESCRIPTION:   Sends a word.(Unsigned Short Integer(2 bytes))
 *
 * RETURN:        SESSION_OK,SESSION_FAILURE...(see _TxStruct)
 *
 * NOTES:         Used for keeping the same Word -> Bytes Transformation
 *                regardless of CPU type.
 * ------------------------------------------------------------------------ */
sint Session_TxLong(sint ses, /* Session Entity Index */
		    ulint l);          /* Word to send */


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_RxLong
 *
 * DESCRIPTION:   Receives a word (Unsigned Short Int).
 *
 * RETURN:        SESSION_OK,SESSION_FAILURE...(see _RxStruct)
 *
 * NOTES:         Used for keeping the same Bytes -> Word Transformation
 *                regardless of CPU type.
 * ------------------------------------------------------------------------ */
sint Session_RxLong(sint ses /* Session Entity Index */,
		     ulint *l /* inside word will be put */);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Session_BlockingMode
 *
 * DESCRIPTION:   yesno = 0 will disable BlockinMode
 *                yesno = 1 will enable BlockinMode
 *
 * RETURN:
 *
 * NOTES:         By default BlockingMode is enabled
 * ------------------------------------------------------------------------ */
void Session_BlockingMode(sint ses, /* Session Entity Index */
		          sint yesno );

/*########################################################################
FUNCTION NAME: SESSION_SetTimeout
DESCRIPTION  : Initialization of receive timeout
RETURN       :
NOTES        : If timeout is 0 the receive function will return only after
               data is received.
########################################################################*/

void SESSION_SetTimeout( lint to );

#ifdef __NOS__
  #include session_nos
#endif
#endif
