/****************************************************************************
 *                                                                          *
 * FILE NAME:   FAT_API.H                                                   *
 *                                                                          *
 * MODULE NAME: FatFS                                                       *
 *                                                                          *
 * PROGRAMMER:  Oren Sokoler                                                *
 *                                                                          *
 * DESCRIPTION: FAT File System API public definitions                      *
 *                                                                          *
 * REVISION:    01.00 29/04/04.                                             *
 *                                                                          *
 ****************************************************************************/

#ifndef __FAT_API_H__                  
#define __FAT_API_H__         

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
           
/* DLM Definitions */

#define        DLM_LIBFAT_VERSION       "01.00.00"
#define        DLM_LIBFAT_NAME          "LIBFAT"
#define        DLM_DEFAULT_RETURN       -41 /* Same as FATFS_NO_SUPPORT */

/* Function return values */

#define       FATFS_OK                   0
#define       FATFS_HANDLE_ERR          -1
#define       FATFS_ARG_ERR             -2
#define       FATFS_NOT_FOUND           -3
#define       FATFS_NO_MEM              -4
#define       FATFS_FULL                -5
#define       FATFS_EOF                 -6
#define       FATFS_NOT_EMPTY           -7
#define       FATFS_ERR                -40
#define       FATFS_NO_SUPPORT         -41

/* Common definitions */

#define       FATFS_MAX_FNAME            8
#define       FATFS_MAX_FEXT             3

/* Seek types */

#define       FATFS_SEEK_SET             0
#define       FATFS_SEEK_CUR             1
#define       FATFS_SEEK_END             2

/* File attributes */

#define       FATFS_ATTR_NORMAL          0x00
#define       FATFS_ATTR_RDONLY          0x01
#define       FATFS_ATTR_HIDDEN          0x02
#define       FATFS_ATTR_SYSTEM          0x04
#define       FATFS_ATTR_VOLID           0x08
#define       FATFS_ATTR_DIR             0x10
#define       FATFS_ATTR_ARCHIVE         0x20
#define       FATFS_ATTR_DEVICE          0x40
#define       FATFS_ATTR_ALL             (D_RDONLY | D_HIDDEN | D_SYSTEM | D_DIR | D_ARCHIVE)

          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

/* File Handle */

typedef lint FHandle;

/* Search Handle */

typedef lint SHandle;

/* File information structure */

typedef struct {

  usint StructSize;               /* Size of this structure */
   char Name[FATFS_MAX_FNAME];    /* File name              */
   char Ext[FATFS_MAX_FEXT];      /* File extension         */
  ulint Attribute;                /* File attributes        */
  DATET CreateDate;               /* File create date       */
  TIMET CreateTime;               /* File create time       */
  DATET UpdateDate;               /* File update date       */
  TIMET UpdateTime;               /* File update time       */
  ulint Size;                     /* File size              */

} FileInfo;

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Open
 *
 * DESCRIPTION:   Opens the file named by the string Name. The string Mode 
 *                indicates how the file is to be opened.
 *
 * PARAMETERS:    Name - File Name ( format : X:\....\NAME.EXT )
 *                Mode - Contain one (but only one) of r, w, or a. 
 *                       Mode can also contain + :
 *
 *                       r  — Open existing file for reading.
 *                       r+ — Open existing file for update.
 *                       w  — Create file for writing; if file exists, 
 *                            truncate it.
 *                       w+ — Create file for update; if file exists, 
 *                            truncate it.
 *                       a  — Open or create file for appending to 
 *                            end of file.
 *                       a+ — Open or create file for update, appending 
 *                            to end of file.
 *
 *                       Mode can also contain one, but only one, of b (binary) 
 *                       or t (text)
 *
 * RETURN:        >= 0 : File handle
 *                <  0 : FATFS_ARG_ERR    - Argument error
 *                       FATFS_NOT_FOUND  - File not found
 *                       FATFS_NO_MEM     - Out of memory
 *                       FATFS_ERR        - Fatal error
 *                       FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
FHandle FatFS_Open ( const char * Name , const char * Mode );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Close
 *
 * DESCRIPTION:   Close a file and flush all its buffers
 *
 * PARAMETERS:    Handle - File handle to close
 *
 * RETURN:        FATFS_OK         - Files closed OK
 *                FATFS_HANDLE_ERR - Invalid handle
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Close ( FHandle Handle );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Read
 *                       
 * DESCRIPTION:   Read a stream of bytes from a file
 *
 * PARAMETERS:    Ptr       - Pointer to the output buffer 
 *                Size      - Size of each element to read
 *                NumOfElem - The number of elements to read
 *                Handle    - File handle
 *
 * RETURN:        >= 0 : Number of elements read
 *                <  0 : FATFS_ARG_ERR    - Argument error
 *                       FATFS_HANDLE_ERR - Invalid handle
 *                       FATFS_ERR        - Fatal error
 *                       FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Read ( void * Ptr , ulint Size , ulint NumOfElem , FHandle Handle );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Write
 *
 * DESCRIPTION:   Write a stream of bytes to a file
 *
 * PARAMETERS:    Ptr       - Pointer to the input buffer 
 *                Size      - Size of each element to write
 *                NumOfElem - The number of elements to write
 *                Handle    - File handle
 *
 * RETURN:        >= 0 : Number of elements written
 *                <  0 : FATFS_ARG_ERR    - Argument error
 *                       FATFS_HANDLE_ERR - Invalid handle
 *                       FATFS_FULL       - Disk is full
 *                       FATFS_ERR        - Fatal error
 *                       FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Write ( void * Ptr , ulint Size , ulint NumOfElem , FHandle Handle );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Seek
 *
 * DESCRIPTION:   This function moves the file pointer for the file associated 
 *                with FileHandle to Offset bytes from one of three positions 
 *                specified by the value of PtrType.
 *
 * PARAMETERS:    Handle  - File handle
 *                Offset  - Offset of bytes to move
 *                PtrType - Position type : FATFS_SEEK_SET (beginning of file)
 *                                          FATFS_SEEK_CUR (current position)
 *                                          FATFS_SEEK_END (end of file)
 * 
 * RETURN:        FATFS_OK         - Seek pointer moved OK
 *                FATFS_HANDLE_ERR - Invalid handle
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Seek ( FHandle Handle , lint Offset , lint PtrType );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Rename
 *
 * DESCRIPTION:   Rename a file
 *
 * PARAMETERS:    Old - Old file name
 *                New - New file name
 * 
 * RETURN:        FATFS_OK         - File was deleted
 *                FATFS_NOT_FOUND  - File not found
 *                FATFS_ARG_ERR    - Argument error
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Rename ( const char * Old , const char * New );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Remove
 *
 * DESCRIPTION:   Delete a file
 *
 * PARAMETERS:    Name - File Name
 * 
 * RETURN:        FATFS_OK         - File was deleted
 *                FATFS_NOT_FOUND  - File not found
 *                FATFS_ARG_ERR    - Argument error
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Remove ( const char * Name );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_MkDir
 *
 * DESCRIPTION:   Create a directory
 *
 * PARAMETERS:    Path - Directory path
 * 
 * RETURN:        FATFS_OK         - Directory was created
 *                FATFS_NOT_FOUND  - Path not found
 *                FATFS_ARG_ERR    - Argument error
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_MkDir ( const char * Path );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_RmDir
 *
 * DESCRIPTION:   Remove a directory
 *
 * PARAMETERS:    Path - Directory path
 * 
 * RETURN:        FATFS_OK         - Directory was deleted
 *                FATFS_NOT_FOUND  - Path not found
 *                FATFS_NOT_EMPTY  - Directory is not empty
 *                FATFS_ARG_ERR    - Argument error
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_RmDir ( const char * Path );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_FindFirst
 *
 * DESCRIPTION:   Starts a file search operation
 *
 * PARAMETERS:    Path - Path to start the file find operation.
 *                Attr - Attribute filter
 *                Info - Pointer to output information structure
 * 
 * RETURN:        >= 0 : Search operation handle
 *                <  0 : FATFS_NOT_FOUND  - Path not found
 *                       FATFS_ARG_ERR    - Argument error
 *                       FATFS_ERR        - Fatal error
 *                       FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
SHandle FatFS_FindFirst ( const char * Path , ulint Attr , FileInfo * Info );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_FindNext
 *
 * DESCRIPTION:   Finds the next file in a find operation that was started
 *                with FatFS_FindFirst
 *
 * PARAMETERS:    Handle - Find operation handle
 *                Info   - Pointer to output information structure
 * 
 * RETURN:        FATFS_OK         - Next file information was retrieved
 *                FATFS_EOF        - End of find operation
 *                FATFS_HANDLE_ERR - Invalid handle
 *                FATFS_ARG_ERR    - Argument error
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_FindNext ( SHandle Handle , FileInfo * Info );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_FindClose
 *
 * DESCRIPTION:   Terminates a find file operation
 *
 * PARAMETERS:    Handle - Find operation handle
 * 
 * RETURN:        FATFS_OK         - Find file operation was terminated
 *                FATFS_HANDLE_ERR - Invalid handle
 *                FATFS_ERR        - Fatal error
 *                FATFS_NO_SUPPORT - FAT File System not supported 
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_FindClose ( SHandle Handle );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_IsEOF
 *
 * DESCRIPTION:   Check if a given file read pointer is at the end of the file
 *
 * PARAMETERS:    Handle - File handle
 *
 * RETURN:        TRUE  - End of file reached
 *                FALSE - End of file not reached
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
boolean FatFS_IsEOF ( FHandle Handle );

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: FatFS_Tell
 *
 * DESCRIPTION:   Returns the current file position
 *
 * PARAMETERS:    Handle - File handle
 * 
 * RETURN:        >= 0 : Current file position
 *                <  0 : FATFS_HANDLE_ERR - Invalid handle
 *                       FATFS_ERR        - Fatal error
 *                       FATFS_NO_SUPPORT - FAT File System not supported
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
lint FatFS_Tell ( FHandle Handle );

#ifdef __NOS__
  #include fat_nos
#endif  
  
#endif
