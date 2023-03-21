/****************************************************************************
 *                                                                          *
 * FILE NAME:   ERRLOG.H                                                    *
 *                                                                          *
 * MODULE NAME: ERRLOG                                                      *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati.                                                *
 *                                                                          *
 * DESCRIPTION: Error Logger prototypes.                                    *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    5.00 09/08/95.                                              *
 *                                                                          *
 ****************************************************************************/
#ifndef __ERRLOG_H__
  #define __ERRLOG_H__
	  /*==========================================*
	   *         I N T R O D U C T I O N          *
	   *==========================================*/

	  /*==========================================*
	   *             I N C L U D E S              *
	   *==========================================*/

	  /*==========================================*
	   *           D E F I N I T I O N S          *
	   *==========================================*/
#define MAX_ERRLOG_TEXT_SIZE 33
#define ERRLOG_BUFFER_FULL   -1
#define NO_SHELL_FUNC        0

	  /*==========================================*
	   *       P R I V A T E  T Y P E S           *
	   *==========================================*/

typedef struct errlog_msg
{
  sint module_code;   /* Module (assigned with a name)  (2)*/
  sint event_code;    /* Event Number                   (2)*/
  char *variable_name;/* The Qualifier var text name    (4)*/
  long variable;      /* Save time variable value       (4)*/
  long value;        /* The value with which to use    (4)*/
		      /* the qualifier                     */
  char *module_name;  /* to Support the OLD method of   (4)*/
		      /* saving the module name.           */
  char text[MAX_ERRLOG_TEXT_SIZE];      /* Text+null                     (33)*/
  byte qualifier;     /* ==, <=, >=, >, < - definitions (1)*/
  byte msg_type;      /* Trigger, Collect or Err type   (1)*/
		      /* Err - Real System Problem         */
		      /*       Can be inserted by Nos      */
		      /*       Only.                       */
		      /* Collect & Trigger Used for debug  */
		      /* Messages.                         */
  byte time[3];       /* Time in bcd 0-Sec,1-Min,2-Hours(3)*/
  byte date[3];       /* Date in bcd 0-Day,1-Mon,2-Year (3)*/

		      /* Total Message size:             61 Actual = 62 */
} errlog_msg;

	   /*=========================================*
	    *   P U B L I C     F U N C T I O N S     *
	    *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Errlog_Clear
 *
 * DESCRIPTION:   Clears error logger buffer and zeroes counter.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Errlog_Clear(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Errlog_GetSingleError
 *
 * DESCRIPTION:   Get information about a specific event in the error logger.
 *                The function returns the structure errlog_msg.
 *
 * RETURN:        TRUE  - Info retrieved successfully.
 *                FALSE - No such event exists.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
boolean Errlog_GetSingleError(sint        msg_co,  /* In : Message # to get */
                              errlog_msg *err);    /* Out */

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Errlog_Insert
 *
 * DESCRIPTION:   Insert an error into errors buffer return TRUE for success
 *		  or -1 for buffer full.
 *
 *                parameters:
 *		  module_name - string of max 8 chars, Ex: "DISPLAY".
 *		  error_text - string of max 32 chars Ex: "Radio receive error."
 *
 * RETURN:        TRUE-error inserted -1 - buffer is full.
 *
 * NOTES:         Not accessible By Applications !
 *                Called By NOS only.
 *
 * ------------------------------------------------------------------------ */
sint Errlog_Insert(char *module_name,char *error_text);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Errlog_GetModuleCode
 *
 * DESCRIPTION:   Get the module name & assign it a module code.
 *
 * RETURN:        module code.
 *
 * NOTES:         Mustn't be Called directly (Called from Macro).
 *
 * ------------------------------------------------------------------------ */
sint Errlog_GetModuleCode(char *module_name,boolean nos_module);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Errlog_DebugInsert
 *
 * DESCRIPTION:   Check whether to output a Debug Message
 *
 * RETURN:        None.
 *
 * NOTES:         Mustn't be Called directly (Called from Macro).
 *
 * ------------------------------------------------------------------------ */
void Errlog_DebugInsert(sint module_code,   /* Module number */
			sint event_code,    /* Event number */
			long variable,      /* long casted Variable  */
			char *text,         /* Message */
			char *variable_name);/* The variable text name */

#ifdef __NOS__
  #include errlog_nos
#endif

#endif
