/****************************************************************************
 * FILE NAME:   IccSyn.H                                                    *
 * MODULE NAME: IccSyn                                                      *
 * PROGRAMMER:  CL                                                          *
 * DESCRIPTION: synchronius smart card driver (script interpreter)          *                                                     *
 * REVISION:    01.00 15/12/97.                                             *
 * HISTORY:     .                                                           *
 ****************************************************************************/

#ifndef __ICCSYN_H
#define  __ICCSYN_H



          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
/**
    a script:         <CODE>,<CODE>,<CODE>...<STOP_SCRIPT>
    loop in a script: ...,<START_LOOP>,i,<CODE>...<CODE>,<END_LOOP>...
    NOTE: if the number of iterations, 'i' more than 127
          two bytes used to define the  number of iterations:
          ...,<START_LOOP>,i1,i2,<CODE>...<CODE>,<END_LOOP>...
          MSB of the first byte =1 and the number of iterations is
          (i1)&(7F)+i2
    NOTE: loops cannot be nested
 */

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
typedef enum
{
  scSTOP_SCRIPT,     /* this byte has to be the last byte in the script */
  scSTART_LOOP,      /* starts the loop, next byte is number of iterations*/
  scEND_LOOP,        /* ends the loop */
  scCONTINUE,        /* void command, do nothing */

  scDELAY_5mcs,      /* make a delay 5 microseconds */
  scDELAY_50mcs,     /* make a delay 50 microseconds */

  scPOWER_UP,        /* powers the card up (use before answer-to-reset */

  scRESET_SET,       /* set RESET to high */
  scRESET_CLR,       /* set RESET to low  */
  scRESET_10mcs,     /* RESET to high for 10mcs, then to low for 10mcs */

  scCLOCK_SET,       /* set CLOCK to high */
  scCLOCK_CLR,       /* set CLOCK to low  */
  scCLOCK_10mcs,     /* CLOCK to high for 10mcs, then to low for 10mcs */

  scDATA_SET,        /* set I/O to high */
  scDATA_CLR,        /* set I/O to low  */
  scDATA_READ_LO,    /* read the I/O from LSB to MSB: *p=((*p)>>1)|0x80 */
  scDATA_READ_HI,    /* read the I/O from MSB to LSB: *p=((*p)<<1)|1    */


  scVPP_IDLE,        /* make VPP idle  (n/a) */
  scVPP_12V,         /* set VPP to 12V (n/a) */
  scVPP_15V,         /* set VPP to 15V (n/a) */
  scVPP_21V,         /* set VPP to 21V (n/a) */

  scC4_SET,          /* set C4 to high (n/a) */
  scC4_CLR,          /* set C4 to low  (n/a) */

  scC8_SET,          /* set C8 to high */
  scC8_CLR,          /* set C8 to low  */
} ScriptCommand;

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/
/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/
/* --------------------------------------------------------------------------
 * FUNCTION NAME: IccSyn_RunScript
 * DESCRIPTION:   receives the application's script and executes it
 * RETURN:    ICC_OK             -- command performed successfully
 *            ICC_SOFTWARE_ERROR -- error in the script syntax
 *
 * NOTES:     the use of the 'Script' structure is as following:
 *            *DataFromCard  -- data received from the card
 *            *DataToCard    -- script of the command to perform
 *             Le            -- not used, set to 0
 *             Lr            -- size of data received into DataFromCard
 *             Lc            -- size of script (in DataToCard)
 *             Session       -- not used, set to 0
 *             Class         -- not used, set to 0
 *             Instruct      -- not used, set to 0
 *             P1            -- not used, set to 0
 *             P2            -- not used, set to 0
 *             SW1           -- not used, set to 0
 *             SW2           -- not used, set to 0
 *             port_indx     -- port index where the ICC present
 *             dummy         -- not used, set to 0
 * ------------------------------------------------------------------------ */
sint IccSyn_RunScript(IccInstructStruct *Script);
#endif
