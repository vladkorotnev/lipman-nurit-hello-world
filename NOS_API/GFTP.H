/****************************************************************************
 * FILE NAME:   gftp.H
 * MODULE NAME: gftp
 * PROGRAMMER:  Gilad Hirsch
 * DESCRIPTION: implement ftp application over tcp.
 *              Each function can be called independently there is no need to
 *              create a sequence of calls.
 *              for example: to upload a file you should call the following-
 *              GFTP_Upload(...)
 *              this call will go through all the states untill the upload (the
 *              connection the login etc. ).
 *
 * REVISION:
 ****************************************************************************/

#ifndef __GFTP_H
#define __GFTP_H

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/
#include gftp_def



           /*=========================================*
            *        M I S C E L L A N E O U S        *
            *=========================================*/

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/


/****************************************************************************
 * FUNCTION NAME: GFTP_New_Session
 * DESCRIPTION:   Creates a new ftp client seesion
 * PARAMETERS:    ServerIp - FTP server Ip.
 *                username - Login UserName
 *                password - Login PassWord
 * RETURN:        a handle that should be used for multiple consecutive connections
 *                GFTP_FULL_HANDLES   - If there is no free handle
 * NOTES:         none.
 ****************************************************************************/
GFTP_User_Handle  GFTP_NewSession(char* ServerIp,char* username, char* password);

/****************************************************************************
 * FUNCTION NAME: GFTP_Free_Session
 * DESCRIPTION:   frees resources associated with specified ftp seesion
 * PARAMETERS :   GFTP_User_Handle - FTP Session handle
 * RETURN:        GFTP_SUCCESS      success
 *                GFTP_INVALID_PTR  invalid ftp session pointer
 * NOTES:         none.
 ****************************************************************************/
GFTP_err_t        GFTP_FreeSession(GFTP_User_Handle hndl);


/****************************************************************************
 * FUNCTION NAME: GFTP_Logout
 * DESCRIPTION:   quit ftp server
 * PARAMETERS :   GFTP_User_Handle - FTP Session handle
 * RETURN:        GFTP_SUCCESS      success
 *                GFTP_ERROR        Fail to logout
 * NOTES:         none.
 ****************************************************************************/
GFTP_err_t        GFTP_Logout( GFTP_User_Handle hndl);

/****************************************************************************
 * FUNCTION NAME: GFTP_Download
 * DESCRIPTION:   Download a file from remote ftp server
 * PARAMETERS :   GFTP_User_Handle - FTP Session handle
 *                Type             - type of data/place to store (flash, ram, ramdisk,ramdisktlv)
 *                Src_file         - a path and name of file to download
 *                Dest_file        - The name for the stored file
 *                datalen          - 1. return the file size
 *                                   2. input for record size in case of data type RamDisk.
 *                                      input for ram size in case of data type Ram.
 *                Transfer         - type of transfer ( append, overwrite, resume )
 *                                   and also type of data (ascii[default], ebcdic,image)
 *                                   this flags should be ored e.g. (GFTP_OVERWRITE\GFTP_IMAGE)
 *                RunMode          - blocking or nonblocking mode
 * RETURN:        GFTP_SUCCESS          success
 *                GFTP_DOWNLOAD_ERROR   Fail to Download
 *
 * NOTES:         none.
 ****************************************************************************/
GFTP_err_t        GFTP_Download(GFTP_User_Handle hndl,GFTP_FileType_t Type,char* Src_file, char* Dest_file,
                                lint* datalen, GFTP_TransferType_t Transfer, GFTP_RunMode_t RunMode );

/****************************************************************************
 * FUNCTION NAME: GFTP_Upload
 * DESCRIPTION:   Upload a file to remote ftp server
 * PARAMETERS :   GFTP_User_Handle - FTP Session handle
 *                Type  -  type of data (flash, ram, ramdisk, ramdisktlv)
 *                Src_file         - pointer to address to upload from
 *                Dest_file        - The name (include path) for the stored file
 *                datalen          - the Src_file size.
 *                Transfer         - type of transfer ( append, overwrite, resume )
 *                                   and also type of data (ascii[default], ebcdic,image)
 *                                   this flags should be ored e.g. (GFTP_OVERWRITE\GFTP_IMAGE)
 *                RunMode          - blocking or nonblocking mode
 * RETURN:       GFTP_SUCCESS       success
 *                GFTP_UPLOAD_ERROR  Fail to upload
 * NOTES:         none.
 ****************************************************************************/
GFTP_err_t     GFTP_Upload(GFTP_User_Handle hndl,GFTP_FileType_t Type,char* Src_file, char* Dest_file,
                           lint datalen, GFTP_TransferType_t Transfer, GFTP_RunMode_t RunMode);

/****************************************************************************
 * FUNCTION NAME: GFTP_Delete
 * DESCRIPTION:   Delete a file from server.
 * PARAMETERS :   GFTP_User_Handle - FTP Session handle
 *                file             - full name (path) of the file to be deleted.
 * RETURN:        GFTP_SUCCESS      success
 *                GFTP_DELETE_ERROR     Fail to delete file
 * NOTES:         none.
 ****************************************************************************/
GFTP_err_t GFTP_Delete(GFTP_User_Handle hndl, char* file);


#endif
