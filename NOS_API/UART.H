/****************************************************************************
 *                                                                          *
 * FILE NAME:   uart.h                                                      *
 *                                                                          *
 * MODULE NAME: UART                                                        *
 *                                                                          *
 * PROGRAMMER:  Ephraim Ckrolovich                                          *
 *                                                                          *
 * DESCRIPTION: Driver for UART, based on Z85C30 and PEN ASIC UART          *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    1.00   16/05/98                                             *
 *                                                                          *
 ****************************************************************************/
#ifndef __UART_85_H__
  #define __UART_85_H__



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
#ifndef TR_BUF_SIZE
  #define   TR_BUF_SIZE   1100    /* size of transmiter buffer */
  #define   REC_BUF_SIZE  1100    /* size of transmiter buffer */
#endif
/*---------------- UART BAUD RATE -------------------------------*/
#define   UART_BAUD_300    300
#define   UART_BAUD_1200   1200
#define   UART_BAUD_2400   2400
#define   UART_BAUD_4800   4800
#define   UART_BAUD_7200   7200
#define   UART_BAUD_9600   9600
#define   UART_BAUD_12000  12000
#define   UART_BAUD_14400  14400
#define   UART_BAUD_19200  19200
#define   UART_BAUD_28800  28800
#define   UART_BAUD_38400  38400
#define   UART_BAUD_57600  57600
#define   UART_BAUD_115K   21
#define   UART_BAUD_256K   22
/*---------------- UART errors -------------------------------*/
#define    UART_OK           0    /*     good execution   */
#define    UART_ER          -10   /*     error            */
#define    NO_UART          -1    /*   UART no exist       */
#define    UART_NO_CREATE   -2    /*   UART no created     */

/*---------- UART return codes for inerrupt ------------*/
#define  U_OK     1   /* Return code: OK */
#define  U_FALSE  0   /* Return code: FALSE */

       /* input bits status */
#define    CLEAR_TO_SEND      0
#define    CARRIER_DETECTED   0
#define    RINGING            0

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

	   /*=========================================*
	    *   P U B L I C     F U N C T I O N S     *
	    *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_Init
 *
 * DESCRIPTION:   This function sets the receive and transmit parameters
 *                of the UART and begins receive. Receive interrupt enable.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         None.
 *
 * NOTES:         Communication parameters:
 *  typedef struct
 *  {
 *     usint    baud_rate;     baud rate in bit per sec.
 *     byte     numbits;       bits number in byte
 *     char     parity;        parity mode: 'n', 'o' or 'e'
 *     boolean  rts_cts;       FALSE - RTS is user controled by
 *                                     Uart_RtsClear and  Uart_RtsSet.
 *                             TRUE  - RTS is automatically controled
 *                                     by the MC68681.
 *                             RTS_RADIO - RTS will be hign when the UART is
 *                                     ready to receive data
 *
 *    boolean  dtr_mode;        FALSE - DTR is user controled by Uart_DtrClear
 *                                   and Uart_DtrSet.
 *		                TRUE  - DTR will be hign when UART is ready to
 *	                               receive data
 *  }comm_param;
 *
 * ------------------------------------------------------------------------*/
#define   Uart_SetMode   Uart_Init
sint Uart_Init (
      usint  UartIndx,   /* in - index of this UART module in the system */
 comm_param  *UartParam  /* in - pointer to communication parameters structure      */
		     );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_RtsCtsSetMode
 *
 * DESCRIPTION:   This function sets Rts-Cts auto mode to the UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------ */

sint  Uart_RtsCtsSetMode (
    usint   UartIndx    /*  in - index of this UART module in the system */
		      );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_RtsCtsClrMode
 *
 * DESCRIPTION:   This function sets Rts-Cts manual mode to the UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------ */

sint Uart_RtsCtsClrMode (
    usint   UartIndx    /*  in - index of this UART module in the system */
		      );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_DtrSetMode
 *
 * DESCRIPTION:   This function sets DTR auto mode to the UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------ */

sint Uart_DtrSetMode(
    usint   UartIndx    /*  in - index of this UART module in the system */
		      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_DtrClrMode
 *
 * DESCRIPTION:   This function sets DTR manual mode to the UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------ */

sint Uart_DtrClrMode (
    usint   UartIndx    /*  in - index of this UART module in the system */
		      );




/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_Flush
 *
 * DESCRIPTION:   This function disables UART interrups, clears all
 *                buffers and begins new receive. Receive interrupt enable.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         None.
 *
 * ------------------------------------------------------------------------*/

sint Uart_Flush (
     usint   UartIndx    /*   in - index of this UART module in the system */
                     );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_DtrSet
 *
 * DESCRIPTION:   This function sets DTR in manual mode.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_DtrSet (
    usint   UartIndx      /* in - index of this UART module in the system */
                      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_DtrClear
 *
 * DESCRIPTION:   This function clears DTR in manual mode.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_DtrClear (
    usint   UartIndx      /* in - index of this UART module in the system */
                      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_RtsSet
 *
 * DESCRIPTION:   This function sets RTS in manual mode.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_RtsSet (
    usint   UartIndx      /* in - index of this UART module in the system */
                      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_RtsClear
 *
 * DESCRIPTION:   This function clears RTS in manual mode.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_RtsClear (
    usint   UartIndx      /* in - index of this UART module in the system */
		      );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_BreakSetMode
 *
 * DESCRIPTION:   Enable/Disable break process.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_BreakSetMode (
    usint   UartIndx,      /* in - index of this UART module in the system */
    boolean BreakMode  );  /* TRUE-break start, FALSE-back to transmit*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_Read_CTS
 *
 * DESCRIPTION:   This function reads CTS input of this UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         status = CLEAR_TO_SEND  or  status != CLEAR_TO_SEND
 *
 * ------------------------------------------------------------------------*/

sint Uart_Read_CTS (
    usint   UartIndx,     /* in - index of this UART module in the system  */
    byte   *status        /* out- input status  */
		      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_Read_CD
 *
 * DESCRIPTION:   This function reads CD input of this UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         status = CARRIER_DETECTED  or  status != CARRIER_DETECTED
 *
 * ------------------------------------------------------------------------*/

sint Uart_Read_CD (
    usint   UartIndx,    /*  in - index of this UART module in the system */
    byte   *status        /* out- input status  */
		      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_Read_RI
 *
 * DESCRIPTION:   This function reads RI input of this UART.
 *
 * RETURN:        UART_ER or UART_OK.
 *
 * NOTES:         status = RINGING  or  status != RINGING
 *
 * ------------------------------------------------------------------------*/

sint Uart_Read_RI (
    usint   UartIndx,    /*  in - index of this UART module in the system */
    byte   *status        /* out- input status  */
		      );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_GetBuf
 *
 * DESCRIPTION:   This function  returns to the calling routine the receive
 *                data and its length.
 *
 * RETURN:        >0  - receiver data size !!!
 *                0  - receiver buffer is empty.
 *                <0 - Uart error code.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_GetBuf (
    usint   UartIndx,      /* in - index of this UART module in the system */
     byte   *buf,          /* in - pointer to data buffer    */
   usint    buf_size       /* in - buffer size for received data  */
                     );



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_CheckBuf
 *
 * DESCRIPTION:   This function  returns to the calling routine the receive
 *                data and its length. Data and its length in the receiver
 *                buffer remains unchanged!!!
 *
 * RETURN:        >0  - receiver data size !!!
 *                0  - receiver buffer is empty.
 *                <0 - Uart error code.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_CheckBuf (
    usint   UartIndx,   /*  in - index of this UART module in the system */
     byte   *buf,       /*  in - pointer to data buffer  */
   usint    buf_size    /*  in - buffer size for received data  */
                     );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_GetByte
 *
 * DESCRIPTION:   This function returns to the calling routine one byte
 *                from the received data.
 *
 * RETURN:        1  - O.K!!!
 *                0  - receiver buffer is empty.
 *                <0 - Uart error code.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_GetByte (
     usint   UartIndx,      /* in - index of this UART module in the system */
      byte   *buf            /* in - pointer to data buffer    */
                     );




/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_SendBuf
 *
 * DESCRIPTION:   This function moves data to transmit buffer and
 *                sets  UART to the transmit mode.
 *
 * RETURN:        >0  - O.K!!! (data size)
 *                0  - transmiter buffer is full.
 *                <0 - Uart error code.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_SendBuf (
     usint   UartIndx,   /* in - index of this UART module in the system */
      byte   *buf,       /* in - pointer to data buffer  */
    usint    buf_size    /* in - size of data buffer     */
                     );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_SendByte
 *
 * DESCRIPTION:   This function moves this byte to transmit buffer and
 *                sets  UART to the transmit mode.
 *
 * RETURN:        >0  - O.K!!! (data size)
 *                0  - transmiter buffer is full.
 *                <0 - Uart error code.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_SendByte (
     usint   UartIndx,      /* in - index of this UART module in the system */
      byte   tr_byte         /* in - byte for transmit           */
                     );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_StartTx
 *
 * DESCRIPTION:   This function Start Tx Interrupt
 *
 * RETURN:        None
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

sint Uart_StartTx (
     usint   UartIndx   /* in - index of this UART module in the system */
                     );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Uart_GetTxStatus
 *
 * DESCRIPTION:   None.
 *
 * RETURN:        =0  - all transmit data is transmited.
 *                >0 - bytes number of transmit data that exists in
 *                      any software or hardware data buffer
 *                <0 - Uart error code.
 *
 * NOTES:         none
 *
 * ------------------------------------------------------------------------*/

#define   Uart_GetTxStatus  Uart_SendStatus
sint Uart_SendStatus (
     usint   UartIndx      /* in - index of this UART module in the system */
                   );

#ifdef __NOS__
  #include uart_nos
#endif

#endif  /*#ifndef __UART_85_H__*/
