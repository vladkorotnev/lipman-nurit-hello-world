/****************************************************************************
 *                                                                          *
 * FILE NAME:   KB.H                                                        *
 *                                                                          *
 * MODULE NAME: KB                                                          *
 *                                                                          *
 * PROGRAMMER:  Ofir                                                        *
 *              MTE + 2035 + 2085 by Oren S.                                *
 *                                                                          *
 * DESCRIPTION: Prototypes For KB                                           *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    1.00 26/01/94                                               *
 *              6.10 16/04/99 Oren S.                                       *
 *                                                                          *
 * HISTORY:                                                                 *
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

/* Parameters for Kb_NosModeSet functuons:  */
/* Kb_NosModeSet(KB_NOS_DISABLE) - shell NOS disable, RESET enable */
/* Kb_NosModeSet(KB_RESET_DISABLE) - shell NOS enable, RESET disable */
/* Kb_NosModeSet(KB_RESET_DISABLE|KB_NOS_DISABLE) - all disable */
/* Kb_NosModeSet(0) - all enable */

#define KB_NOS_DISABLE        0x01
#define KB_RESET_DISABLE      0x02
#define KB_FEED_DISABLE       0x04
#define KB_CONTRAST_DISABLE   0x08

#ifndef CONFIG_IN_USE
  /* Number of combination to be added: */
  #if defined(BARAN_KBF1MAP1AS_KEYBOARD)
       #define KB_NUMBER_OF_COMBINATIONS  5
  #elif defined(NURIT_2055)
     #if defined(NURIT_2058)
       #define KB_NUMBER_OF_COMBINATIONS  39
     #else
       #define KB_NUMBER_OF_COMBINATIONS  37
     #endif
  #elif defined(NURIT_2086)
     #if defined(NURIT_3001) || defined(NURIT_3003)
       #define KB_NUMBER_OF_COMBINATIONS  21
     #else
       #define KB_NUMBER_OF_COMBINATIONS  6
     #endif
  #elif defined(NURIT_ATM)
       #define KB_NUMBER_OF_COMBINATIONS  10
  #elif defined(NURIT_8000)
       #define KB_NUMBER_OF_COMBINATIONS  19
  #else /*non-2086, non-2055: */
       #define KB_NUMBER_OF_COMBINATIONS  5
  #endif

  #if defined(NURIT_2055)
    #define PHONE_KEY                  ((byte)F3_KEY)
  #else
    #define PHONE_KEY                  ((byte)F1_KEY)
  #endif

  #ifdef NURIT_2055
    #undef STBY_KEY_ASCII
    #define STBY_KEY_ASCII           MENU        /* ON STBY key ascii code */
  #else
    #undef STBY_KEY_ASCII
    #define STBY_KEY_ASCII           ON_STBY      /* ON STBY key ascii code */
  #endif

#endif


#define MIN_IDLE_TIME_OUT 5          /* Minimum 5 seconds till shut down
                                        in IDLE mode */



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
 * FUNCTION NAME: Kb_NosDisable.
 *
 * DESCRIPTION:   Disables the NOS shell.
 *
 * RETURN:        void.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void Kb_NosDisable(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_NosEnable.
 *
 * DESCRIPTION:   Enables the NOS shell.
 *
 * RETURN:        void.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void Kb_NosEnable(void);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: Kb_Flush.
 * DESCRIPTION:   Clear all Kb buffers.
 * NOTES:         Can be called from Bkgr. 
 * ------------------------------------------------------------------------ */
void Kb_Flush(void);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: Kb_Read.
 *
 * DESCRIPTION:   Since 08_66:
 *                If defined 'NOS_WITH_SECURE_KB_MODULE', function calls
 *                Kb_Read through module Secure-Kb-Master, which calls 
 *                Kb_Read_NotSecure (the old Kb_Read).
 *                If not defined, function calls  Kb_Read_NotSecure.
 *
 * RETURN:        key pressed, '*' or nothing, according to SecKb security
 *                state.
 *
 * NOTES:         Module SecKbMstr prevents using a non-secure Kb, when in
 *                a secure state. If in State IDLE, will return to module Kb.
 *                See SeureKb.doc in module SecKb.
 * ------------------------------------------------------------------------ */
char Kb_Read(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_Insert
 *
 * DESCRIPTION:   Inserts a Key into the buffer as if it was pressed
 *                When Kb_Read calls it will read this key !
 *
 * RETURN:        OK if inserted or FAILURE if no such key exists.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------ */
void Kb_Insert(byte ch);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ExtendKb_Insert.
 *
 * DESCRIPTION:   inserts a char into external KB buffer.
 *
 * RETURN:        TRUE-all OK, FALSE-buffer full or doesn't exist.
 *
 * NOTES:         if nothing was sent, nothing will be added and function return TRUE.
 * ------------------------------------------------------------------------ */
void ExtendKb_Insert(byte ch);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_WaitForKey
 *
 * DESCRIPTION:   Waits until a key is pressed and returns it !
 *
 * RETURN:        a keystroke/combination value (char).
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
char Kb_WaitForKey(void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ExtendKb_WaitForKey
 *
 * DESCRIPTION:   Waits until a key is pressed and returns its new value
 *
 * RETURN:        a keystroke/combination value (char).
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte ExtendKb_WaitForKey(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_Idle(usint time_out).
 *
 * DESCRIPTION:   Switches system into IDLE out of IDLE mode.
 *
 *                time_out (in seconds) :
 *                if time_out is 0 IDLE mode is turned off (if was on).
 *                else IDLE mode is set on and time out mechanism start
 *                counting time (when timer zeros, system will shut down).
 *                if any key was pressed during IDLE mode , IDLE mode
 *                is turned off.
 *
 * RETURN:        none.
 *
 * NOTES:         (Minimum time for IDLE mode is 5 seconds)
 *
 * ------------------------------------------------------------------------ */
void Kb_Idle(usint time_out);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_NosModeSet.
 *
 * DESCRIPTION:   Enable/Disable the the RESET and/or NOS shell.
 *
 * RETURN:        void.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void Kb_NosModeSet(byte NosMode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_ClickTimeSet.
 *
 * DESCRIPTION:   Set the keyboard click time in msec. If click time=0,
 *                the click will disable.
 *
 * RETURN:        void.
 *
 * NOTES:
 *
 * ------------------------------------------------------------------------ */
void Kb_ClickTimeSet(usint time);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Kb_OffTimeSet.
 *
 * DESCRIPTION:   Set the off time in msec. Go to shutdown process, if
 *                the on/off key was pressed during time > off time,
 *                else return the code of on/off key.
 *
 * RETURN:        void.
 *
 * NOTES:         valid for buttery operation only.
 *
 * ------------------------------------------------------------------------ */
void Kb_OffTimeSet(usint time);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: ExtendKb_Read
 *
 * DESCRIPTION:   Since 08_66:
 *                If defined 'NOS_WITH_SECURE_KB_MODULE', function calls
 *                ExtendKb_Read through module Secure-Kb-Master, which calls 
 *                ExtendKb_Read_NotSecure (the old ExtendKb_Read).
 *                If not defined, function calls  ExtendKb_Read_NotSecure.
 *
 * RETURN:        key pressed, '*' or nothing, according to SecKb security
 *                state.
 *
 * NOTES:         See SeureKb.doc in module SecKb.
 * ------------------------------------------------------------------------ */
byte  ExtendKb_Read ( void );


/* --------------------------------------------------------------------------
 * FUNCTION NAME: ExtendKb_Enable.
 *
 * DESCRIPTION:   enables reading from external KB.
 *
 * RETURN:        none.
 *
 * NOTES:         if not CASH_REGISTER nothing is done.
 * ------------------------------------------------------------------------ */
void ExtendKb_Enable (void);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ExtendKb_Disable.
 *
 * DESCRIPTION:   Disables reading from external KB.
 *
 * RETURN:        none.
 *
 * NOTES:         if not CASH_REGISTER nothing is done.
 * ------------------------------------------------------------------------ */
void ExtendKb_Disable (void);
/* --------------------------------------------------------------------------
* FUNCTION NAME: Kb_Check.
*
* DESCRIPTION:   returns old value of keys pressed as definedin "nurit.def".
*                without polling it out from the KB buffer.
*
* RETURN:        key pressed.
*
* NOTES:         Use this function to avoid the use of the Kb_Insert function
*                which might cause unpredictable result at some platforms.              
* ------------------------------------------------------------------------ */
char Kb_Check(void);


#ifdef __NOS__
  #include kb_nos
#endif
