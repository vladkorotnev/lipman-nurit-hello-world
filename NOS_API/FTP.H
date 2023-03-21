/****************************************************************************
 *                                                                          *
 * FILE NAME:   FTP.H                                                       *
 *                                                                          *
 * MODULE NAME: FTP                                                         *
 *                                                                          *
 * PROGRAMMER:  Oren S.                                                     *
 *                                                                          *
 * DESCRIPTION: Header file for FTP.C                                       *
 *                                                                          *
 * REVISION:    01.00 01/08/98.                                             *
 *                                                                          *
 * HISTORY:     none.                                                       *
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

                 /* Function return values */

#define            FTP_OK             0   /* File transfer completed o.k */
#define            FTP_COM_FAIL      -1   /* Communication error */
#define            FTP_ESCAPE        -2   /* User pressed ESC */
#define            FTP_NO_SPACE      -3   /* Ram disk out of space */
#define            FTP_RD_ERROR      -4   /* Ram disk fatal error */
#define            FTP_NO_EXIST      -5   /* File not found */
#define            FTP_ALREADY_EXIST -6   /* File already exists */
#define            FTP_BAD_SIZE      -7   /* Bad file record size */
#define			   FTP_DISK_TRAN_OK  -8    /* Whole Disk Transfer Passed OK */

                   /* File transfer type */

#define            TRAN_NEW              0   /* Recieve a new file              */
					                         /* Do not overwrite if file exists */
#define            TRAN_APPEND           1   /* Append an existing file */
#define            TRAN_OVERWRITE        2   /* Overwrite an existing file */
#define            TRAN_APPEND_CREATE    3   /* Append an existing file in not 
                                                exist treat like new */
#define            TRAN_OVERWRITE_CREATE 4   /* Overwrite an existing file in not
                                                exist treat like new  */

                /* FTP Man Machine Interface */

#define            FTP_NUM_MSG        4   /* Number of FTP messages */
#define            FTP_NUM_MENU_MSG   8   /* Number of menu messages */
#define            FTP_MSG_LEN        33  /* Message length */ 

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

typedef char FTPMsgType[FTP_MSG_LEN];     /* One FTP message */

           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

/* void */

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_Init
 *
 * PARAMETERS:    MyPort  - Port for FTP transfer
 *
 *                          UART_A - COM1
 *                          UART_B - MODEM
 *
 *                TimeOut - Communication tiemout
 *
 * DESCRIPTION:   Initialize the FTP module.
 *
 * RETURN:        FTP_OK       - File Transfer init O.K
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint FTP_Init(usint MyPort,usint TimeOut);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_SetUserMessages
 *
 * PARAMETERS:    Msg - Pointer to user messages :
 *                       
 *                Each user message is of type FTPMsgType, an array of these
 *                types should be declared as follows :
 *
 *                Msg[0] - This message will be displayed when receing data.
 *                         This message must contain a %d in it to allow for
 *                         displaying of the received record number.
 *
 *                Msg[1] - This message will be displayed when sending data.
 *                         This message must contain a %d in it to allow for
 *                         displaying of the sended record number.
 *
 *                Msg[2] - This message will be displayed when waiting to 
 *                         receive a file.
 *
 *                Msg[3] - Thie message will be displayed when wating for
 *                         receiver side.
 *
 * DESCRIPTION:   Set FTP interactive user messages
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void FTP_SetUserMessages(FTPMsgType *Msg);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_Menu
 *
 * PARAMETERS:    none.
 *
 * DESCRIPTION:   Opens an FTP menu. This function handles an interactive
 *                FTP session through COM1
 *
 * RETURN:        none.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
void FTP_Menu(void);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_SendFile
 *
 * DESCRIPTION:   This function sends the FileName file from the RamDisk to
 *                another Nurit using the FTP protocol.
 *
 * PARAMETERS:    FileName          - File to send
 *
 * RETURN:        FTP_OK            - File Transfer ended O.K
 *                FTP_COM_FAIL      - Communication error
 *                FTP_RD_ERROR      - Ram disk fata error (NO DISK etc. )
 *                FTP_NO_SPACE      - Ram disk is out of space
 *                FTP_NO_EXIST      - File not found  
 *                FTP_ALREADY_EXIST - The file already exists in the receiver
 *                                    RamDisk.
 *                FTP_BAD_SIZE      - An FTP Append operation can not be made
 *                                    beacuse of missmatch in file record size.
 *                FTP_ESCAPE        - User pressed Escape.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint FTP_SendFile(char *FileName);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_ReceiveFile
 *
 * DESCRIPTION:   This function receivs a file from another Nurit 
 *                using the FTP protocol.
 *
 * PARAMETERS:    ThisFTPType  - File Transfer Type :
 *
 *                               TRAN_NEW       - This is a new file , if an 
 *                                                older file already exists, 
 *                                                the older file will NOT be
 *                                                overwritten.
 *
 *                               TRAN_APPEND    - Append the received records
 *                                                to an existing file. 
 *
 *                               TRAN_OVERWRITE - Overwrite an existing file.
 *
 * RETURN:        FTP_OK            - File Transfer ended O.K
 *                FTP_COM_FAIL      - Communication error
 *                FTP_RD_ERROR      - Ram disk fata error (NO DISK etc. )
 *                FTP_NO_SPACE      - Ram disk is out of space
 *                FTP_NO_EXIST      - File not found (if Append or OverWrite)
 *                FTP_ALREADY_EXIST - The received file already exists in the
 *                                    RamDisk (if TRAN_NEW)    
 *                FTP_BAD_SIZE      - An FTP Append operation can not be made
 *                                    beacuse of missmatch in file record size.
 *                FTP_ESCAPE        - User pressed Escape.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint FTP_ReceiveFile(byte ThisFTPType);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_SendDisk
 *
 * DESCRIPTION:   This function sends all the files in the RamDisk of the nurit
 *                to another Nurit using the FTP protocol.
 *
 * PARAMETERS:    none.
 *
 * RETURN:        FTP_OK            - Whole disk Transfer ended O.K
 *                FTP_COM_FAIL      - Communication error
 *                FTP_RD_ERROR      - Ram disk fata error (NO DISK etc. )
 *                FTP_NO_SPACE      - Ram disk is out of space
 *                FTP_NO_EXIST      - Disk is empty.
 *                FTP_ALREADY_EXIST - One of the files already exists in
 *                                    the receiver RamDisk.
 *                FTP_BAD_SIZE      - An FTP Append operation can not be made
 *                                    beacuse of missmatch in file record size.
 *                FTP_ESCAPE        - User pressed Escape.
 *
 * NOTES:         YR.
 *
 * ------------------------------------------------------------------------ */
sint FTP_SendDisk(void *Dummy);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FTP_ReceiveDisk
 *
 * DESCRIPTION:   This function receivs a whole RamDisk from another Nurit 
 *                using the FTP protocol.
 *
 * PARAMETERS:    ThisFTPType  - Disk Transfer Type :
 *
 *                               TRAN_NEW               - Each file received is 
 *                                                        considerd to be a new file
 *                                                        if an older file already 
 *                                                        exists the older file will 
 *                                                        NOT be overwritten and the
 *                                                        transfer will be ABORTED.
 *
 *                               TRAN_APPEND            - Append the received records
 *                                                        to existing files. 
 *
 *                               TRAN_OVERWRITE         - Overwrite existing files if file Does not
 *                                                        Exist, Aborts Operation.
 *                               
 *                               TRAN_APPEND_CREATE     - Append the received records
 *                                                        to existing files. if not exist 
 *                                                        creates and then appends. 
 *
 *                               TRAN_OVERWRITE_CREATE  - Overwrite existing files. if not exist 
 *                                                         creates and then overwrites. 
 *
 *
 * RETURN:        FTP_OK            - Whole disk transfer ended O.K
 *                FTP_COM_FAIL      - Communication error
 *                FTP_RD_ERROR      - Ram disk fata error (NO DISK etc. )
 *                FTP_NO_SPACE      - Ram disk is out of space
 *                FTP_NO_EXIST      - File(s) not found (if Append or OverWrite)
 *                FTP_ALREADY_EXIST - One of the received file already exists 
 *                                    in the RamDisk (if TRAN_NEW)    
 *                FTP_BAD_SIZE      - An FTP Append operation can not be made
 *                                    beacuse of missmatch in file record size.
 *                FTP_ESCAPE        - User pressed Escape.
 *
 * NOTES:         YR.
 *
 * ------------------------------------------------------------------------ */
sint FTP_ReceiveDisk(byte ThisFTPType);




