/****************************************************************************
 *
 * FILE NAME:   PHONE.H
 *
 * MODULE NAME: PHONE
 *
 * PROGRAMMER:  Igal Mioni.
 *
 * DESCRIPTION: Phone task for NURIT 2050 (placed in the 2050 NOS)
 *
 *              API functions declarations
 *
 * REVISION:    01.00 - Jul 11 '95
 *
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

#define   DISABLED_KEY      0xFF  /* Non working character */

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
typedef struct
{
  char   Asterisk    ; /* '*' key (DTMF funnction)            */
  char   Diez        ; /* '#' key (DTMF funnction)            */
  char   SpeedDial   ; /* speed-dial key                      */
  char   Redial      ; /* redial key                          */
  char   Line_Flash  ; /* Line and 'Flash' key                */
  char   Pulses_Tones; /* Pulses/DTMF toggle at dial-time key */
  char   Enter       ; /* enter                               */
  char   Escape      ; /* escape                              */
  char   Menu        ; /* menu/update                         */
  char   spare1      ; /* spare key                           */
  char   spare2      ; /* spare key                           */
  char   spare3      ; /* spare key                           */
} phone_keys; /* 6 + 1 + 1 + 1 + 1 + 1 + 1  = 12 bytes */



           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Phone_SetKeyStruct
 *
 * DESCRIPTION:   Set the function-keys used by Phone task .
 *
 * RETURN:        none.
 *
 * NOTES:         to disable a key, set its value to DISABLED_KEY
 * ------------------------------------------------------------------------ */
void    Phone_SetKeyStruct( phone_keys *Struct);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Phone_GetKeyStruct
 *
 * DESCRIPTION:   Get the function-keys used by Phone task .
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void    Phone_GetKeyStruct( phone_keys *Struct);

#ifdef __NOS__
  #include phone_nos
#endif
