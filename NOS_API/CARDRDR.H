/****************************************************************************
 *                                                                          *
 * FILE NAME:   cardrdr.h                                                   *
 *                                                                          *
 * MODULE NAME: CARDRDR                                                     *
 *                                                                          *
 * PROGRAMMER:  Originally - Ofir. This version - Oren.                     *
 *                                                                          *
 * DESCRIPTION: Magnetic Card Reader (Tracks 1 and 2)                       *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    01_30  18/01/95                                             *
 *                                                                          *
 ****************************************************************************/

          /*=========================================*
           *         I N T R O D U C T I O N         *
           *=========================================*/
/* void */

          /*=========================================*
           *           P A R A M E T E R S           *
           *=========================================*/
/* void */

          /*=========================================*
           *          D E F I N I T I O N S          *
           *=========================================*/

/* Card Reader error code */

#define CARDRDR_OK               0  /* Track was read OK */
#define CARDRDR_NO_TRACK         1  /* No track          */
#define CARDRDR_NO_1_FOUND       2  /* No '1' found      */
#define CARDRDR_NOT_ENOUGH_PULSS 3  /* Not enough pulss  */
#define CARDRDR_PARITY_ERROR     4  /* Parity error      */
#define CARDRDR_LRC_ERROR        5  /* Lrc Error         */
#define CARDRDR_NO_END_SENTINL   6  /* No end sentinl    */
#define CARDRDR_NO_START_SENTINL 7  /* No start sentinl  */
#define CARDRDR_LRC_PARITY_ERROR 8  /* Lrc Parity error  */

          /*=========================================*
           *     T Y P E   D E C L A R A T I O N     *
           *=========================================*/
/* void */

          /*=========================================*
           *        M I S C E L L A N E O U S        *
           *=========================================*/
/* ---------- PRAGMAS ---------- */

/* ---------- ETCETERA ---------- */

          /*=========================================*
           *  F U N C T I O N   P R O T O T Y P E S  *
           *=========================================*/

/* --------------------------------------------------------------------------
 * FUNCTION NAME: CardRdr_GetSiteNo.
 * DESCRIPTION:   Utility function , reads Technician or Merchant card .
 *                INPUT PARAMETER:
 *                   header  - string (text header to be displayed).
 *                OUTPUT PARAMETERS:
 *                   error   - error value (if one occured).
 *                      Error Values:
 *                      0 - No Error , Ok.
 *                      1 - Neither an Merchant nor Technician card.
 *                   return_key - if user pressed a key, card read is stopped
 *                                and the function will return its value.
 *                                You should ignore the return value if a key
 *                                was pressed.
 *                                If no key was pressed return_key pointer
 *                                will point to 0.
 * RETURN:        the site number (the Merchant or Technician no )
 * NOTES:         You may determine whether it's a Merchant or Technician
 *                card by the site number value.
 *                ( > 1000 - Merchant       < 1000 - Technician )
 * ------------------------------------------------------------------------ */
ulint CardRdr_GetSiteNo (char *header, sint *error, char *return_key);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_Enable
 *
 * DESCRIPTION:   Enables the card reader and the Timer/Counter
 *
 * RETURN:        void
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void CardRdr_Enable (void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_Disable
 *
 * DESCRIPTION:   Disables the card reader
 *
 * RETURN:        void
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void CardRdr_Disable (void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_SetBeepTime
 *
 * DESCRIPTION:   Set the beep time im msec after swipe card.
 *                0 - beep disable.
 *
 * RETURN:        void
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void CardRdr_SetBeepTime(usint BeepTimeInMiliSec/* 0 - beep disable */);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_IsCardCompleted
 *
 * DESCRIPTION:   Checks if card reading is completed
 *
 * RETURN:        TRUE  - completed.
 *                FALSE - not yet completed.
 *
 *                OUTPUT PARAMETERS:
 *                *track1_error, *track2_error:
 *                   0    - valid information (format o.k. and lrc o.k.).
 *                   else - error number.
 *
 * NOTES:         This function performs all the analysis.
 *
 *                The first phase of the analysis is performed on track #2
 *                (which containes the more important information). If it
 *                succedes, track #1 will also be analyzed, but if the
 *                analysis of track #2 failed, there will be no attempt to
 *                analyze track #1, and the output parameter track1_error
 *                will be assigned 1 ("no track" error).
 *
 * ------------------------------------------------------------------------ */
boolean CardRdr_IsCardCompleted (sint *track1_error, sint *track2_error);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_IsAnyTrackCompleted
 *
 * DESCRIPTION:   Checks if card reading is completed
 *
 * RETURN:        TRUE  - one or both tracks are completed.
 *                FALSE - both tracks are not yet completed.
 *
 *                OUTPUT PARAMETERS:
 *                *track1_error, *track2_error:
 *                   0    - valid information (format o.k. and lrc o.k.).
 *                   else - error number.
 *
 * NOTES:         This function performs all the analysis.
 *
 * ------------------------------------------------------------------------ */
boolean CardRdr_IsAnyTrackCompleted (sint *track1_error, sint *track2_error);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_IsAnyTrackCompleted3Tracks
 *
 * DESCRIPTION:   Checks if reading of any of 3 tracks is completed.
 *
 * RETURN:        TRUE  - one or both tracks are completed.
 *                FALSE - both tracks are not yet completed.
 *
 *                OUTPUT PARAMETERS:
 *                *track1_error, *track2_error, *track3_error:
 *                   0    - valid information (format o.k. and lrc o.k.).
 *                   else - error number.
 *
 * NOTES:         This function performs all the analysis.
 *
 * ------------------------------------------------------------------------ */
boolean CardRdr_IsAnyTrackCompleted3Tracks ( sint *track1_error,
                                             sint *track2_error,
                                             sint *track3_error );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_GetTrack1
 *
 * DESCRIPTION:   return pointer to track1 ascii array.
 *
 * RETURN:        pointer to track1 ascii array.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte *CardRdr_GetTrack1 (void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_GetTrack2
 *
 * DESCRIPTION:   return pointer to track2 ascii array.
 *
 * RETURN:        pointer to track2 ascii array.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte *CardRdr_GetTrack2 (void);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: CardRdr_GetTrack3
 *
 * DESCRIPTION:   return pointer to track3 ascii array.
 *
 * RETURN:        pointer to track3 ascii array.
 *
 * NOTES:         When using old 2-track system, return pointer to track1.
 *
 * ------------------------------------------------------------------------ */
byte *CardRdr_GetTrack3 (void);


#ifdef __NOS__
  #include cardrdr_nos
#endif
