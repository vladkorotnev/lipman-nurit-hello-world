 /***************************************************************************
 * FILE NAME:   fisflash.h
 * MODULE NAME: fisflash
 * PROGRAMMER:  Uri  
 * DESCRIPTION: Fiscal memory (Flash)  driver
 *
 *              API functions declarations
 *  
 * REVISION:    01.00 25/11/2004
 ***************************************************************************/
#ifndef __FISFLASH_H_
  #define __FISFLASH_H_

          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
/**
Fiscal memory is an FLASH used in the ECR to store some imported applicaon
information. The structure of the information has to be defined by application
writery and, therefore, is outside the scope of this description.
There are 5 functions accessable by the application : _Write, _Read, _Erase,
_Enable and _GetSize.
   
The parameters are the same: 1)the start address to write/read within the
Fiscal memory chip, 2)the application buffer to write from / read to, and 3)
the buffer's size. Therefore the area in the fiscal memory chip to write to /
read from has the limits: [StartAddress...StartAddress+BufferSize]
The address of the first byte in the fiscal memory is 00000, the last byte
address is FISMEM_SIZE-1, where FISMEM_SIZE is the size of the fiscal memory
chip, as it was defined in model configuration.

Physically the writing means turning few or all ones to zeroes. This process
is unreversible, i.e. there's impossible to turn a zero to one. The module
FISMEM checks whether the current state of a bit (before writing)is '0'.
It means that trying to write some byte into byte already containing other
value is not equivalent 0xff, the _Write functions returns FISMEM_OVERWRITE
error.

Protection mechanism: general the fiscal memory accessis disable. The calling
FisFlash_Enable() enables  the one time calling of the Erase/Write/Read functions.
If thise functions didn't call during some timeout( ~0.5sec), the fiscal memory
comback to disable mode.

*/

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
#define FISMEM_OK              0
#define FISMEM_FAIL           -1   /* Write/erase error*/
#define FISMEM_OVERFLOW       -2   /* trying to write/read/erase outsite of memory*/
#define FISMEM_NO_EXIST       -3   /* FisMem driver doesn't exist or Fis|Mem size == 0*/
#define FISMEM_OVERWRITE      -6   /* trying to write on existing byte*/
#define FISMEM_DATA_CHANGED   -7   /* write on existing byte, no error*/
#define FISMEM_DISABLE        -8   /* FisMem is not enable by FisFlash_Enable */






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

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FisFlash_Write
 * DESCRIPTION:   Writes buffer into the memory
 * PARAMETERS:    StartAdress       start memory adress
                  Buffer            buffer with the data to write to memory
                  BuffferSize       size of Buffer parameter (size to write to memory)
 * RETURN:        FISMEM_OK         everything is ok
 *                FISMEM_NO_EXIST   FisMem doesn't exist
 *                FISMEM_DISABLE   FisMem is not enable by FisFlash_Enable()
 *                FISMEM_FAIL       fail during writing to the fiscal memory
 *                FISMEM_OVERFLOW   trying to write to out of the memory
 *                                  (StartAddress+BufferSize) > FISMEM_SIZE
 *                FISMEM_OVERWRITE  trying to write on existing byte
 *                FISMEM_DATA_CHANGED  write on existing byte, no error
 *                
 * NOTES:         None.
 * ------------------------------------------------------------------------ */
sint FisFlash_Write(ulint StartAddress, byte *Buffer, usint BufferSize);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: FisFlash_Read
 * DESCRIPTION:   read the memory into specified buffer
 * PARAMETERS:    StartAddress     start memory adress
                  Buffer           Buffer to write the data which was read from memory.
                  BufferSize       size of Buffer parameter
 * RETURN:        FISMEM_OK        everything is ok
 *                FISMEM_NO_EXIST  FisMem doesn't exist
 *                FISMEM_DISABLE   FisMem is not enable by FisFlash_Enable()
 *                FISMEM_OVERFLOW  trying to read from out of the memory
 *                                  (StartAddress+BufferSize) > FISMEM_SIZE
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint FisFlash_Read(ulint StartAddress, byte *Buffer, usint BufferSize);
  
    
/* --------------------------------------------------------------------------
 * FUNCTION NAME: FisFlash_Erase
 * DESCRIPTION:   Erase part of the memory
   PARAMETERS   : StartAddress     start adress
                  Size      `      size of memory to erase
 * RETURN:        FISMEM_OK        everything is ok
 *                FISMEM_NO_EXIST  FisMem  doesn't exist
 *                FISMEM_DISABLE   FisMem is not enable by FisFlash_Enable()
 *                FISMEM_FAIL      fail during erasing of the fiscal memory
 *                                 or parameters error.
 *                FISMEM_OVERFLOW  trying to erase from out of the memory
 *                                  (StartAddress+BufferSize) > FISMEM_SIZE
 * NOTES:         StartAddress and Size must be 0xX0000.
 * ------------------------------------------------------------------------ */
sint FisFlash_Erase(ulint StartAddress,  ulint Size);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: FisFlash_Enable
 * DESCRIPTION:   Enable the one time calling the Erase/Write/Read functions.
 *                If thise functions didn't call during some timeout( ~0.5sec),
 *                the fiscal memory comback to disable mode.
 * RETURN:        FISMEM_OK        everything is ok
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint FisFlash_Enable(void);


/* --------------------------------------------------------------------------
 * FUNCTION NAME: FisFlash_GetSize
 * DESCRIPTION:   Check the size of fiscal memory.
 * RETURN:        The size of fiscal memory in bytes
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
ulint FisFlash_GetSize(void);




#ifdef __NOS__
  #include fisflash_nos
#endif

#endif