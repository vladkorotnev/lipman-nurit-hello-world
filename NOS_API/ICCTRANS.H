/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *                  
 *                                                                         *
 * FILE NAME:   ICCTRANS.H                                                 *
 *                                                                         *
 * MODULE NAME: ICCTRANS                                                   * 
 *                                                                         *
 * PROGRAMMER:  Ephraim                                                    *
 *                                                                         *
 * DESCRIPTION: Transport layer of smart card interface that conform to    *
 *              ISO 7816-1,2,3                                             *
 *                                                                         *
 *              API functions declarations                                 *
 *                                                                         *
 * REVISION:    01_00  November 16, 1997                                   *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef __ICCTRANS_H 
#define  __ICCTRANS_H


                /* ======================================= *
                 *         I N T R O D U C T I O N         *
                 * ======================================= */
#define ICCTRANSPORT_VERSION 118

#define Transport_Status  ICC_Status
#define Transport_Reset   ICC_AnswerToReset
#define Transport(x)      ICC_Command(x)


                /* ======================================= *
                 *           P A R A M E T E R S           *  
                 * ======================================= */
/* void */


                /* ======================================= *
                 *          D E F I N I T I O N S          *
                 * ======================================= */
/* PROTOCOL TYPES */
#define      T0_ASYN_PROTOCOL         0
#define      T1_ASYN_PROTOCOL         1
#define      MAX_ASYN_PROTOCOL        100
#define      GPM2K_SYN_CARD_PROTOCOL  101
#define      GPM896_SYN_CARD_PROTOCOL 102
#define      UNDEFINED_PROTOCOL       0xff

#define      ICC_OK                   0
#define      ICC_SOCKET_EMPTY         1
#define      ICC_BAD_CARD             2
#define      ICC_NEEDS_RESET          3
#define      ICC_SOFTWARE_ERROR       4
#define      ICC_CARD_BLOCKED         5
#define      ICC_NO_ATR               6     /* card didn't response to ATR at all (Maybe Vcc is incorrect) */

#define      MAX_EMV_ATR_SIZE         32    /* not included TS and LRC                              */
/*------------ ATR modes for ISO ATR---------------*/

#define      ATR_WITHOUT_IFS          0x01  /* don't send IFS command after ATR protocol T1         */
#define      ATR_WITHOUT_SIZE_CHECK   0x02  /* don't check ATR size, by EMV must <=32               */
#define      ATR_TB3_BY_EMV           0x04  /* check TB3 byte of ATR by EMV                         */
#define      ATR_NOT_REJECT_BAD_TA1   0x10  /* if TA1 byte of ATR is out of range, use default      */
#define      ICC_CARD_3v_VCC          0x80  /* make VCC to a 3v card, if hardware supports it       */
#define      ICC_CARD_AUTO_VCC        0x40  /* make auto selection of card's VCC - starts with lowest available voltage */
#define      ATR_WITH_PPS             0x08  /* ATR with PPS if Negotiation Protocol                 */
#define      MORE_ATR_MODES           0x20  /* more ATR options in IccAnswerToResetStruct.Protocol  */

/* ATR modes which will be send through IccAnswerToResetStruct.Protocol                             */
/*              !!! Those modes MUST be sent with MORE_ATR_MODES mode !!!!                          */
#define      ICC_CARD_1_8v_VCC        0x01  /* make VCC to a 1.8v card, if hardware supports it     */
#define      ATR_TA2_BY_EMV           0x02  /* check TA2 byte by EMV 2000 - Bulletin 2, Nov. 2001   */

/*Old definitions: */
typedef enum
{
   TRANS_OK               = ICC_OK            ,
   TRANS_SOCKET_EMPTY     = ICC_SOCKET_EMPTY  ,
   TRANS_BAD_CARD         = ICC_BAD_CARD      ,
   TRANS_NEEDS_RESET      = ICC_NEEDS_RESET   ,
   TRANS_SOFTWARE_ERROR   = ICC_SOFTWARE_ERROR,
   TRANS_CARD_BLOCKED     = ICC_CARD_BLOCKED
}TransStatusEnum;

                /* ======================================= *
                 *     T Y P E   D E C L A R A T I O N     *
                 * ======================================= */

typedef struct
{
   byte *Data;         /* ATR data                             */
   byte SizeOfData;    /* "Out" if Data == NULL; else "In/Out" */
   byte SizeOfHistory; /* "Out"                                */
   byte Protocol;      /* "Out"                                */
   byte port_indx;     /* SAM1/SAM2/EX_CARD                    */
}
   IccAnswerToResetStruct;

typedef struct
{
   byte  *DataFromCard; /*   response data                                               */
   byte  *DataToCard;   /*   (in a command)                                              */
   usint Le;            /*   (in a command) Max length of DataFromCard (length expected) */
   usint Lr;            /*   (Nowhere) Actual length of DataFromCard                     */
   byte  Lc;            /*   (in a command) Length of DataToCard  (length of command)    */
   byte  Session;       /*   (in a command: ------xx) Logical channel                    */
   byte  Class;         /*   (in a command: xxxxxx--)                                    */
   byte  Instruct;      /*   (in a command)                                              */
   byte  P1;            /*   (in a command)                                              */
   byte  P2;            /*   (in a command)                                              */
   byte  SW1;           /*   (in a response)                                             */
   byte  SW2;           /*   (in a response)                                             */
   byte  port_indx;     /*   SAM1/SAM2/EX_CARD                                           */
   byte dummy;          /*   number of sent bytes                                        */ 
}
   IccInstructStruct;

typedef struct
{
   byte  *DataToCard;   /*   (in a command)                            */
   byte  *DataFromCard; /*    response data                            */
   usint Lc;            /*   (in a command) Length of DataToCard       */
   usint Le;            /*   (in a command) Max length of DataFromCard */
   usint Lr;            /*   (Nowhere) Actual length of DataFromCard   */
   byte  port_indx;     /*   SAM1/SAM2/EX_CARD                         */
   byte dummy;
}
   T1_DataStruct;


typedef struct {
   byte send_from;   /* source address for send         */
   byte send_to;     /* dest. address for send          */
   byte rec_from;    /* source address of received block */
   byte rec_to;      /* dest. address of received block  */
   }T1_adr_param;




                /* ======================================= *
                 *        M I S C E L L A N E O U S        *
                 * ======================================= */
/* void */


                /* ======================================= *
                 *  F U N C T I O N   P R O T O T Y P E S  *
                 * ======================================= */


/* --------------------------------------------------------------------------
 * FUNCTION NAME: ICC_AnswerToReset
 * DESCRIPTION:   Reset card by EMV v.4.1.
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD
 * NOTES:         There are two alternative ways of calling this function:
 *                1 - Info->Data == NULL and then the function will assign
 *                    Info->Data with the address of its own buffer containing
 *                    the received data.
 *                2 - Info->Data != NULL and then the function will put the
 *                    received data in the buffer pointed to by Info->Data,
 *                    whose size is given by Info->SizeOfData.
 *                In any case, if the function returns ICC_OK, the actual
 *                size of data will be returned in Info->SizeOfData.
 * ------------------------------------------------------------------------ */
byte ICC_AnswerToReset (IccAnswerToResetStruct *Info);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: ICC_ISO_AnswerToReset
 * DESCRIPTION:   Reset card by ISO 7816 and ATR_Mode parameter,
 *                which can be ATR_WITHOUT_IFS or/and ATR_WITHOUT_SIZE_CHECK.
 *                or/and ICCASYN_NOT_REJECT_BAD_TA1.
 *                If ATR_Mode=0, then ATR by EMV v.4.1.
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD
 * NOTES:         There are two alternative ways of calling this function:
 *                1 - Info->Data == NULL and then the function will assign
 *                    Info->Data with the address of its own buffer containing
 *                    the received data.
 *                2 - Info->Data != NULL and then the function will put the
 *                    received data in the buffer pointed to by Info->Data,
 *                    whose size is given by Info->SizeOfData.
 *                In any case, if the function returns ICC_OK, the actual
 *                size of data will be returned in Info->SizeOfData.
 * ------------------------------------------------------------------------ */
byte ICC_ISO_AnswerToReset (IccAnswerToResetStruct *Info,byte ATR_Mode);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_Status
 *
 * DESCRIPTION:   Check presence of card in the port by it index.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_NEEDS_RESET, /
 *                ICC_BAD_CARD
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte ICC_Status (byte port_indx);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_EMVCommand
 *
 * DESCRIPTION:   Send a command APDU and receive a response APDU.
 *                If need, send the GET RESPONSE COMMNAD to the card and
 *                receive a response APDU. Works by EMV standard.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD /
 *                ICC_NEEDS_RESET, / ICC_SOFTWARE_ERROR
 *
 * NOTES:         There are 2 ways of calling this function with Inst->le != 0:
 *
 *                1 - Inst->DataFromCard == NULL, and then, if the function is
 *                    about to return TRUE, it will make Inst->DataFromCard
 *                    point to static buffer which "belongs" to this function.
 *
 *                2 - Inst->DataFromCard != NULL, and then, if the function is
 *                    about to return TRUE, it will copy the relevant data to
 *                    where Inst->DataFromCard points to.
 *
 * ------------------------------------------------------------------------ */
byte ICC_EMVCommand (IccInstructStruct *Inst);



/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_CommandT1
 *
 * DESCRIPTION:   Send a command APDU and receive a response APDU
 *                by protocol T1
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD /
 *                ICC_NEEDS_RESET, / ICC_SOFTWARE_ERROR
 *
 *
 * ------------------------------------------------------------------------ */
byte ICC_CommandT1 (IccInstructStruct *Inst,T1_adr_param *adr);


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_SendReceiveT1.
 *
 * DESCRIPTION:   Send the data block to asynchronous card by T1 protocol
 *                with block retry if needs and receive the answer block.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD /
 *                ICC_NEEDS_RESET / ICC_SOFTWARE_ERROR 
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */

byte ICC_SendReceiveT1(
      T1_DataStruct    *Data,
      T1_adr_param     *adr);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_SetIFS.
 *
 * DESCRIPTION:   Send the IFS request end receive IFS response.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD /
 *                ICC_NEEDS_RESET / ICC_SOFTWARE_ERROR
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte ICC_SetIFS(byte from, byte to, byte size, byte port_adr);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_Command
 *
 * DESCRIPTION:   Send a command APDU and receive a response APDU.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_BAD_CARD /
 *                ICC_NEEDS_RESET, / ICC_SOFTWARE_ERROR
 *
 * NOTES:         There are 2 ways of calling this function with Inst->le != 0:
 *
 *                1 - Inst->DataFromCard == NULL, and then, if the function is
 *                    about to return TRUE, it will make Inst->DataFromCard
 *                    point to static buffer which "belongs" to this function.
 *
 *                2 - Inst->DataFromCard != NULL, and then, if the function is
 *                    about to return TRUE, it will copy the relevant data to
 *                    where Inst->DataFromCard points to.
 *
 * ------------------------------------------------------------------------ */
byte ICC_Command (IccInstructStruct *Inst);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Icc_Disactive
 *
 * DESCRIPTION:   Deactivate the card.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_NEEDS_RESET, /
 *                ICC_BAD_CARD
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte ICC_Disactive (byte port_indx);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: ICC_Reject
 *
 * DESCRIPTION:   Deactivate the card and reject it.
 *
 * RETURN:        ICC_OK / ICC_SOCKET_EMPTY / ICC_NEEDS_RESET, /
 *                ICC_BAD_CARD
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte ICC_Reject (byte port_indx);


#ifdef __NOS__
  #include icctrans_nos
#endif

#endif
