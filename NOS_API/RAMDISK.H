/**************************************************************************** *                                                                          *
 * FILE NAME:   RamDisk.h                                                   *
 *                                                                          *
 * MODULE NAME: RAMDISK.                                                    *
 *                                                                          *
 * PROGRAMMER:  Nimrod (Modified By Oren)                                   *
 *                                                                          *
 * DESCRIPTION: This Version of RAMDISK uses Indexes as pointers to Read    *
 *              Record and Free (LAST) Record.                              *
 *                                                                          *
 *              API functions declarations                                  *
 *                                                                          *
 * REVISION:    02.21f   2 March 1995                                       *
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

#define RD_OK                 0
#define RD_ERROR             -1
#define RD_OUT_OF_ENTRIES    -2
#define RD_OUT_OF_MEM        -3
#define RD_OUT_OF_DIR        -4
#define RD_EOF               -5
#define RD_CHECK_FAIL        -6
#define RD_CHECK_OK          -7
#define RD_FILENOTFOUND      -8
#define RD_WRONG_INX         -9
#define RD_LAST             -10
#define RD_NOT_FOUND        -11
#define RD_VIOLATION        -12
#define RD_TLV_REC_NOT_FOUND -13
#define   RD_OWNER_ERROR    -14

#define RD_NEAR_OUT_OF_MEM  '!'
#define SEEK_FIRST           -1
#define SEEK_LAST            -2
#define REOPEN_RESET        255
#define RD_FILENAME_LEN       6

#define TLV_DONT_OVERWRITE    0
#define TLV_OVERWRITE         1

#define SH_FILE_NOT_SHARED 0x00000000
#define SH_FILE_SHARED     0x00000001

          /*=========================================*
           *     T Y P E   D E C L A R A T I O N     *
           *=========================================*/

/* used for searching inside records in funcs LinearSearch and BinarySearch */
typedef struct
{
  usint Offset;
  usint Length;
  byte *Pattern;
} PATTERN_REC;




typedef struct
{
   sint   Handle;
   byte   FileName[RD_FILENAME_LEN];
   usint  Clusters;
   lint   ByteSize;
   byte   RecordSize;
   usint  RecordVer;
   usint  RcrdSize2Byte;
}
   File_Entry;

          /*=========================================*
           *        M I S C E L L A N E O U S        *
           *=========================================*/
/* ---------- PRAGMAS ---------- */

/* ---------- ETCETERA ---------- */

          /*=========================================*
           *  F U N C T I O N   P R O T O T Y P E S  *
           *=========================================*/


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: RamDisk_Reset
 *
 * DESCRIPTION:   This Function Initializes DIRECTORY and FAT Data.
 *                This function destroys all previously recorded data
 *
 * RETURN:         RD_OK - if succeded
 *                 RD_ERROR - if an Error Occured during Initialization
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint RamDisk_Reset (void);


/* ------------------------------------------------------------------------ *
 *
 * FUNCTION NAME: RamDisk_NewFile
 *
 * DESCRIPTION:   This function creates (and opens) a new file, of the name
 *                FileName, and allocates a new cluster for it.
 *
 *                RecrdSize specifies the size of a single record in bytes.
 *                IT MUST BE A POSITIVE EVEN NUMBER!
 *
 *                Rec_Ver is stored in the RecrdVer field of file's dir struct,
 *                for the sole use of the application (where it can 'remember'
 *                which application version created the file).
 *
 * RETURN:         Handle (file index) - if succeeded.
 *                 RD_OUT_OF_MEM - if there are no more free clusters.
 *                 RD_OUT_OF_DIR - if there are no more free file locations
 *                 RD_ERROR - if an error occured during initialization
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint RamDisk_NewFile (byte *FileName, usint RecrdSize, usint Rec_Ver);


/* ------------------------------------------------------------------------ *
 *
 * FUNCTION NAME: RamDisk_Append
 *
 * DESCRIPTION:   Writes records to the end of the file
 *
 * RETURN:         Number of records in file - if succeded.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_OUT_OF_MEM - if there are no more free clusters.
 *                 RD_WRONG_INX - wrong index
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint RamDisk_Append (sint Index, void *Record);


/* ------------------------------------------------------------------------ *
 *
 * FUNCTION NAME: RamDisk_FastAppend
 *
 * DESCRIPTION:   Writes records to the end of the file
 *
 * RETURN:         Number of records in file - if succeded.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_OUT_OF_MEM - if there are no more free clusters.
 *                 RD_WRONG_INX - wrong index
 *
 * NOTES:         THIS FUNCTION ASSUMES THAT Cluster Size is no bigger than
 *                64Kbytes.
 *                Furthermore, this function is a dangerous function !!!!
 *                inorder to save time, if it is called with the same
 *                handle again, it will assume that no changes were made
 *                to the file between the two calls and treat it accordingly
 *                So, between two calls to this function with the same
 *                handle -> the user can not change anything in this file
 ****************************************************************************
 *                To reset the static handle call this function with a
 *                RD_ERROR handle.
 ****************************************************************************
 * ------------------------------------------------------------------------ */
sint RamDisk_FastAppend (sint Index, void *Record);



/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_Seek
 *
 * DESCRIPTION:   Moves the read pointer of a file:
 *
 *                Index is the file's handle.
 *
 *                Pointer_Move is absolute number of the record to which
 *                the read pointer should point (0 .. number of records - 1)
 *                Alternatively, Pointer_Move may be:
 *                   SEEK_FIRST - point to the first record.
 *                   SEEK_LAST  - point to the last record.
 *
 * RETURN:         Number of Records in FILE - if succeded.
 *                 RD_EOF - if Reached End of File (beyond last record).
 *                 RD_WRONG_INX - if FILE_index parameter is Wrong.
 *                 RD_ERROR - if error occured while Seeking.
 *
 * NOTES:         For Pointer_Move - SEEK_FIRST and 0 have the same effect.
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_Seek (sint Index, int Pointer_Move);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_Read
 *
 * DESCRIPTION:   Copies Data which ReadRecrd Points to Into Buffer
 *
 * RETURN:         The Record Number Read (Starts from 0) - if succeded.
 *                 RD_EOF - Read has Reached the End Of File.
 *                 RD_WRONG_INX - if FILE_index parameter is Wrong.
 *                 RD_ERROR - if error occured while Reading.
 *
 * NOTES:         None.
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_Read (sint Index, void *Buffer);


/* ------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_ClearFile
 *
 * DESCRIPTION:   Erases Records within a FILE (From Record To Record)
 *
 * RETURN:         RD_OK  - if succeded.
 *                 RD_WRONG_INX - if Index Number is Wrong.
 *                 RD_ERROR - if error occured.
 *
 * NOTES:         Record Numbers start from 0
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_ClearFile (sint Index, sint FromRec, sint ToRec);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_Delete
 *
 * DESCRIPTION:   Deletes a single Record PRIOR to the record
 *                pointed by the read pointer of a file.
 *
 *                The read pointer will continue to point to the SAME data!
 *                (Which means that the read pointer is actually decremented,
 *                because the record pointed by it is shifted into the
 *                deleted record)
 *
 * RETURN:         RD_OK  - if _Delete succeded.
 *                 RD_WRONG_INX - if Index Number is Wrong.
 *                 RD_ERROR - if error occured while Deleting
 *
 * NOTES:         If the read_pointer points at the start of a file
 *                and delete function is called, an RD_ERROR will occur.
 *
 *                If you call this function more than once in a row, then
 *                the deletions will be performed downwards (toward the
 *                first record of the file). This is because the function
 *                always deletes the record which is located before the read
 *                pointer.
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_Delete (sint Index);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_Insert
 *
 * DESCRIPTION:   Inserts a single Record at the address pointed by the read
 *                pointer of a file.
 *
 * RETURN:         RD_OK - if succeded.
 *                 RD_WRONG_INX - if Index Number is Wrong.
 *                 RD_ERROR - if error occured while Inserting.
 *                 RD_OUT_OF_MEM - if no more memory available
 *
 * NOTES:         - In order to insert the record, the function shifts by one
 *                  place all of the records starting from the read pointer to
 *                  the end of the file.
 *
 *                - After the insertion, the read pointer will point to the
 *                  newly inserted record.
 *
 *                - If the read pointer is at the end of file (e.g. the last
 *                  record has been read) then calling this function is
 *                  of course equivalent to calling RamDisk_Append.
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_Insert (sint Index, void *Record);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_EraseFile
 *
 * DESCRIPTION:   Erases a file from the directory entirely.
 *
 * RETURN:         Number of Erased Clusters - if succeded.
 *                 RD_FILENOTFOUND - didnt find file name in DIRECTORY
 *                 RD_ERROR - Internal ramdisk error...
 *
 * NOTES:         After calling this function the file no longer exists!
 *                (As opposed to calling RamDisk_ClearFile).
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_EraseFile (byte *FileName);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_ChkDsk
 *
 * DESCRIPTION:   Checks CHECKSUM and structure of ONE file -or- ALL files.
 *
 *                If FileName==NULL .........>>>> check all files.
 *                Otherwise .................>>>> check the file whose name
 *                                                is pointed to by FileName.
 *
 * RETURN:         RD_CHECK_OK   - if FILE/DISK checks OK.
 *                 RD_CHECK_FAIL - if FILE/DISK checks NOT OK.
 *                 RD_FILENOTFOUND - if 'File_Name' does not exist.
 *                 RD_ERROR - Internal ramdisk error...
 *
 * NOTES:         None.
 *
 *-------------------------------------------------------------------------   */
sint RamDisk_ChkDsk (byte *FileName);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_CheckSize
 *
 * DESCRIPTION:   Checks size of ONE file -or- total of ALL files.
 *
 *                If FileName==NULL .........>>>> total size of all files.
 *                Otherwise .................>>>> size of the file whose name
 *                                                is pointed to by FileName.
 *
 * RETURN:        In HighWord Number of Occupied Clusters By the file/s
 *                In LowWord Number of Total Records in the file/s
 *                Or an error:
 *                 RD_ERROR - Internal ramdisk error...
 *                 RD_FILENOTFOUND - if File Does not exist in DIRectory
 *
 *               ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 *               ³ To Extract Cluster and Record Data From Return Parameter  ³
 *               ³ you can use LOWORD and HIWORD Macros defined in RAMDISK.h ³
 *               ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 *
 * NOTES:         None.
 *
 *-------------------------------------------------------------------------   */
int RamDisk_CheckSize (byte *FileName);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_Reopen
 *
 * DESCRIPTION:   Given a file name the function returns a structure which
 *                describes the file.
 *
 * RETURN:        In structure File_Entry (see definition of it):
 *                If succeded -
 *                   information about the file.
 *                If error occured -
 *                   'FileEntry->Handle' is one of the following return codes:
 *                    RD_ERROR - if an Error Occured while reopening
 *                    RD_FILENOTFOUND - if File Does not exist in DIRectory
 *
 * NOTES:         - If 'File_Name' is NULL, the Function returns the Next
 *                  FILE Entry data in the DIRECTORY.
 *                  (If No FILES had been Reopened the Data of the First
 *                  FILE is Returned).
 *
 *                - Inorder To Reset the FILE Pointer of the Function
 *                  To The First FILE entry in DIRECTORY, put 'REOPEN_RESET'
 *                  in FileName[0]. This Action also Returns a File_Entry
 *                  Struct Which Conains data of the First FILE Entry in Disk.
 *
 *-------------------------------------------------------------------------   */
File_Entry *RamDisk_Reopen (byte *FileName);


/* -------------------------------------------------------------------------*
 *
 * FUNCTION NAME: RamDisk_GetFreeSpace.
 *
 * DESCRIPTION:   Returns The Total RDisk Net Free Space Available.
 *
 * RETURN:         Size in Bytes - If succeded
 *                 RD_ERROR - if RDisk Is Not Created.
 *
 * NOTES:         None.
 *
 *------------------------------------------------------------------------- */
ulint RamDisk_GetFreeSpace (void);



/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_GetNumberOfRecords
 *
 * DESCRIPTION  : Returns the number of records in the input file
 *
 * RETURN       : Number of records in the input file
 *
 * NOTES        : Handle = Input file's handle
 * -------------------------------------------------------------------*/
sint  RamDisk_GetNumberOfRecords( sint Handle);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_GetCheckSum
 *
 * DESCRIPTION  : Returns the checksum of the file who's handle is Handle
 *
 * RETURN       : Check sum of file
 *
 * NOTES        : Handle = Input file's handle
 * -------------------------------------------------------------------*/
usint RamDisk_GetCheckSum( sint Handle);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_Overwrite
 *
 * DESCRIPTION  : Overwrite an existing record with a given one.
 *                The current position of the seek pointer is the place
 *                where the input record (Rec) will be written (see NOTES)
 *
 * RETURN       :  RD_OK        - if action succeeded.
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *                   RD_EOF       - if overwriting at end of file.
 *                 RD_ERROR     - if error occurred during operation.
 *
 * NOTES        : BEFORE calling this function, call first to
 *                RamDisk_Read or -
 *                RamDisk_LinearSearchPattern or -
 *                RamDisk_BinarySearchSequence
 * -------------------------------------------------------------------*/
sint RamDisk_Overwrite (sint Handle, byte *Record);


/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_LinearSearchPattern
 *
 * DESCRIPTION  : Performs a linear (sequential) search for a specific
 *                pattern (a part of a record).
 *                The action uses the seek pointer (see NOTES)
 *
 * RETURN       :  Index of found record, or -
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *                 RD_ERROR     - if error occurred during operation.
 *                 RD_NOT_FOUND - if no matching record was found
 *                                 (reached the End of File - beyond
 *                                 last record).
 *
 * NOTES        : 1. BEFORE calling this function for the first time in
 *                   a session, first set the file's pointer to the
 *                   beginning of the file, since it searches from the
 *                   the current position of the seek pointer
 *
 *                2. It is possible to find more than one matching
 *                   record. to do so, call this function until it
 *                   returns RD_EOF (or RD_ERROR, if an error occured)
 *
 *                3. Offset  = start of pattern within the record.
 *                   Length  = length of the pattern (in bytes)
 *                   Pattern = pattern to search
 *                   These fields are passed via a pointer a the record
 *                   of PATTERN_REC type
 *
 *            record ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 *                   ³   XXXXX          ³
 *                   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 *                 start ^
 *               pattern ^ÄÄÄ^
 *
 *                4. The file doesn't have to be sorted, although it's
 *                   an advantage if it is sorted already.
 *
 *                5. see also: RamDisk_mark
 * -------------------------------------------------------------------*/
sint  RamDisk_LinearSearchPattern( sint         Handle,
                                   PATTERN_REC *Pattern_Ptr);












/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_BinarySearchSequence
 *
 * DESCRIPTION  : Performs a binary search for a specific sequence of
 *                byte(s) within a record
 *                The action uses the seek pointer (see NOTES)
 *                The given sequence is treated as a unique key of the
 *                record
 *
 * RETURN       :  Index of found record, or -
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *                 RD_ERROR     - if error occurred during operation.
 *                 RD_NOT_FOUND - if no matching record was found
 *
 * NOTES        : 1. There is no need to set the file's pointer.
 *                   The function will handle it internally.
 *
 *                2. Only ONE matching record can be found.
 *
 *                3. Offset   = offset, in the record, where the sequence
 *                              starts.
 *                   Length   = length of the sequence (in bytes)
 *                   Sequence = sequence to search
 *                   These fields are passed via a pointer a the record
 *                   of PATTERN_REC type
 *
 *            record ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 *                   ³   XXXXX          ³
 *                   ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 *                 start ^
 *              sequence ^ÄÄÄ^
 *
 *                4. The file MUST be sorted before calling the function.
 * -------------------------------------------------------------------*/
sint  RamDisk_BinarySearchSequence( sint         Handle,
                                    PATTERN_REC *Sequence_Ptr);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_SetTimeStamp
 *
 * DESCRIPTION  : This function 'stamps' a file with the current
 *                date and time values.
 *
 * RETURN       :  RD_OK        - if operation succeeded.
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *
 * NOTES        : see File_Entry structure.
 *                see also: RamDisk_GetTimeStamp
 * -------------------------------------------------------------------*/
sint  RamDisk_SetTimeStamp( sint Handle);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_GetTimeStamp
 *
 * DESCRIPTION  : Returns the last updated value of the the file's date
 *                and time fields, found in the appropriate File_Entry
 *                structure
 *                FileDate: format = YYYYMMDD (Year - 4 digits,
 *                --------                     Month - 2 digits,
 *                                             Day  - 2 digits)
 *                          type   = unsigned long integer
 *
 *                FileTime: format = HHMM    (Hour    - 2 digits,
 *                --------                     Minutes - 2 digits)
 *                          type   = unsigned short integer
 *
 * RETURN       :  RD_OK        - if operation succeeded.
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *
 * NOTES        : see File_Entry structure.
 *                see also: RamDisk_SetTimeStamp
 * -------------------------------------------------------------------*/
sint  RamDisk_GetTimeStamp( sint   Handle,
                             ulint *FileDate, usint *FileTime);



/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_Rename
 *
 * DESCRIPTION  : Renames a file from 'Oldname' (current name) to
 *                'NewName' (new file's name)
 *
 * RETURN       :  RD_OK        - if operation succeeded.
 *                 RD_ERROR     - if error occurred during operation.
 *                                 (like 'Oldname' doesn't match the
 *                                 file's handle)
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *
 * NOTES        : 'OldName' is provided (although 'Handle' is enough to
 *                rename the file) only for security matter
 * -------------------------------------------------------------------*/
 sint  RamDisk_Rename( sint Handle, char *OldName, char *NewName);




/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_ExtractRecord
 *
 * DESCRIPTION  : Read a record from a file and decrease the file's
 *                length by releasing previous read records
 *                (by freeing clusters)
 *
 *                ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
 *                ³IMPORTANT !!!                                       ³
 *                ³                                                    ³
 *                ³1. Before calling the function for the first time,  ³
 *                ³   in a session, set the file's pointer to the      ³
 *                ³   beginning of of the file, by calling RamDisk_Seek³
 *                ³   with the parameter SEEK_FIRST.                   ³
 *                ³                                                    ³
 *                ³2. It is totaly forbidden to call any other RamDisk ³
 *                ³   function during extraction, as related ONLY to   ³
                  ³   the extracted file.                              ³
 *                ³   (end of extraction is occured when the file's    ³
 *                ³   pointer has reached to the end of the file)      ³
 *                ³   However, should this happen, the extraction must ³
 *                ³   bt suspended and return a fatal violation code   ³
 *                ³   (RD_VIOLATION)                                   ³
 *                ³                                                    ³
 *                ³3. In the end of the extraction operation (if ended ³
 *                ³   successfully) the file will be empty but yet     ³
 *                ³   known for the RamDisk.                           ³
 *                ³                                                    ³
 *                ³4. The release operation of read records will not be³
 *                ³   executed by deleting records, but by freeing     ³
 *                ³   full read clusters                               ³
 *                ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
 *                see also: NOTES
 *
 * RETURN       :  RD_OK        - if operation succeeded.
 *                 RD_ERROR     - if error occurred during operation.
 *                 RD_WRONG_INX - if Handle Number is Wrong.
 *                 RD_EOF       - if Reached the End of the source file
 *                 RD_VIOLATION - violation error during extraction
 *
 * NOTES        : 1. The function will return RD_EOF when it encounters
 *                   the end of the file
 *
 *                2. In general, this is the way of how to use the
 *                   function:
 *
 *                   usint rv;
 *
 *                   RamDisk_Seek( SEEK_FIRST);
 *                   do
 *                     rv = RamDisk_ExtractRecord( Handle);
 *                   while( rv != RD_EOF);
 *                   RamDisk_EraseFile( FileName);
 *
 *                3.  Handle - file's handle
 *                    Record - a pointer where the extracted record will
 *                             be copied to
 * -------------------------------------------------------------------*/
 sint  RamDisk_ExtractRecord( sint Handle, byte *Record);


/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_WriteTLV
 *
 * DESCRIPTION  : Receives a TLV record, searches to see if there is
 *                a matching TYPE inside the file. If match found, the
 *                function replaces that record with a new one. If matching
 *                TYPE was not found, the function APPENDS a new record.
 *
 * RETURN:         Number of records in file - if succeded.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_OUT_OF_MEM - if there are no more free clusters.
 *                 RD_WRONG_INX - wrong index
 *
 * NOTES:         none.
 *
 * -------------------------------------------------------------------*/
sint  RamDisk_WriteTLV( sint Handle, byte Type,
                         usint Length, byte *TLVBuf,
                                    boolean Overwrite);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_CreateTLVFile
 *
 * DESCRIPTION  : Creates a New File in TLV format
 *
 * RETURN:         Handle (file index) - if succeeded.
 *                 RD_OUT_OF_MEM - if there are no more free clusters.
 *                 RD_OUT_OF_DIR - if there are no more free file locations
 *                 RD_ERROR - if an error occured during initialization
 *
 * NOTES:         none.
 *
 * -------------------------------------------------------------------*/
sint  RamDisk_CreateTLVFile( byte *TLVFileName,
                              usint BasicRecSize,
                               usint Rec_Ver);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_ReadTLV
 *
 * DESCRIPTION  : Receives, as a parameter the TYPE, returns the length
 *                and the VALUE
 *
 *
 * RETURN:         RD_OK - if succeded.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_WRONG_INX - wrong index
 *                 RD_REC_NOT_FOUND - TYPE record not found
 *
 * NOTES:         none.
 *
 * -------------------------------------------------------------------*/
sint  RamDisk_ReadTLV( sint Handle, byte Type,
                         usint *Length, byte *TLVBuf);




/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_DeleteTLV
 *
 * DESCRIPTION  : Deletes a TLV record using the _Delete function
 *
 *
 * RETURN:         RD_OK - if succeded.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_WRONG_INX - wrong index
 *                 RD_REC_NOT_FOUND - TYPE record not found
 *
 * NOTES:         none.
 *
 * -------------------------------------------------------------------*/
sint  RamDisk_DeleteTLV( sint Handle, byte Type);



/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_GetTimeStamp
 *
 * DESCRIPTION  : Retrives time stamp of a file
 *
 * RETURN:         RD_OK - if successful.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_WRONG_INX - wrong index
 *
 * NOTES:         Date is retrieved in the following form:
 *                   YYYYMMDD - all decimal, for example  19961010 decimal.
 *                Time is retrieved in the next way:
 *                   HHMM     - decimal numbers.
 *
 *                For more information see module RTC. ( Rtc_Read() )
 * -------------------------------------------------------------------*/
sint  RamDisk_GetTimeStamp( sint Handle, ulint *date, usint *time);


/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_SetTimeStamp
 *
 * DESCRIPTION  : Stamps a handle with current date and time
 *
 * RETURN:         RD_OK - if successful.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_WRONG_INX - wrong index
 *
 * NOTES:         Date is stamped in the following form:
 *                   YYYYMMDD - all decimal, for example  19961010 decimal.
 *                Time is stamped in the next way:
 *                   HHMM     - decimal numbers.
 *
 *                For more information see module RTC.
 * -------------------------------------------------------------------*/
sint  RamDisk_SetTimeStamp( sint Handle);

/* ---------------------------------------------------------------------
 * FUNCTION NAME: RamDisk_ChangeTimeStamp
 * DESCRIPTION  : Stamps a handle with received date and time
 * RETURN:         RD_OK - if successful.
 *                 RD_ERROR -  Internal ramdisk error (RamDisk not created).
 *                 RD_WRONG_INX - wrong index
 * NOTES:         Date is stamped in the following form:
 *                   YYYYMMDD - all decimal, for example  19961010 decimal.
 *                Time is stamped in the next way:
 *                   HHMM     - decimal numbers.
 * -------------------------------------------------------------------*/
sint RamDisk_ChangeTimeStamp(sint Handle, ulint Date, usint Time);
/* ------------------------------------------------------------------------ *
 *
 * FUNCTION NAME: RamDisk_NewFileEx
 *
 * DESCRIPTION:   This function creates (and opens) a new file, of the name
 *                FileName and the file Options , and allocates a new cluster for it.
 *
 *                RecrdSize specifies the size of a single record in bytes.
 *                IT MUST BE A POSITIVE EVEN NUMBER!
 *
 *                Rec_Ver is stored in the RecrdVer field of file's dir struct,
 *                for the sole use of the application (where it can 'remember'
 *                which application version created the file).
 *
 * PARAMETERS:    FileName  - The New File name.
 *                RecrdSize - The basic record Size.
 *                Rec_Ver   - The Record Version.
 *                Options   - sharing Option for the file
 *                            SH_FILE_NOT_SHARED
 *                            SH_FILE_SHARED
 *
 * RETURN:         Handle (file index) - if succeeded.
 *                 RD_OUT_OF_MEM - if there are no more free clusters.
 *                 RD_OUT_OF_DIR - if there are no more free file locations
 *                 RD_ERROR - if an error occured during initialization
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
sint RamDisk_NewFileEx (byte *FileName, usint RecrdSize, usint Rec_Ver, ulint Options);


          /*==========================================*
           *  INLINE FUNCTIONS IMPLEMENTED BY MACROS  *
           *==========================================*/


#define LOWORD(a)      ((a) & 0x0000FFFF)

#define HIWORD(a)      (((a) & 0xFFFF0000) >> 16)

#ifdef __NOS__
  #include ramdisk_nos
#endif
