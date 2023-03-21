/****************************************************************************
 *                                                                          *
 * FILE NAME:   MTE.H                                                       *
 *                                                                          *
 * MODULE NAME: MTE                                                         *
 *                                                                          *
 * PROGRAMMER:  Ofir Efrati.                                                *
 *                                                                          *
 * DESCRIPTION: API functions declarations                                  *
 *                                                                          *
 * REVISION:    4.10 08/08/95.                                              *
 *              6.01 13.04.99 (6.00 & 5.20 merged)                          *
 ****************************************************************************/

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/

          /*==========================================*
           *       P R I V A T E  T Y P E S           *
           *==========================================*/
typedef void (*applbkgr_func)(void);

typedef enum {
               MTE_MAIN_ID  = 1, /* Main task (NOS+APPL) ID */
               MTE_PHONE_ID = 2  /* Phone task ID */

             }  Mte_TasksEnum;


           /*=========================================*
            *   P U B L I C     F U N C T I O N S     *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Mte_ConnectToBkgr
 *
 * DESCRIPTION:   Set pointer to application background function or
 *                NULL for application background disable.
 *
 * RETURN:        none.
 *
 * NOTES:         The application background function must not use any
 *                Kb_Read, Kb_WaitForKey, Mte_Wait and Printer functions.
 *                The application background function must not have any
 *                long loops.
 *
 * ------------------------------------------------------------------------ */
void Mte_ConnectToBkgr(applbkgr_func _applbkgr_func);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Mte_Wait(time_in_miliseconds)
 *
 * DESCRIPTION:   Delay foreground the specified time,
 *                meanwhile call Mte_Suspend for background functions.
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void Mte_Wait(ulint time_in_miliseconds);

#ifdef __NOS__
  #include mte_nos
#endif
