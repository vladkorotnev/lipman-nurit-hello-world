/***************************************************************************
 * FILE NAME:   fismem.h
 * MODULE NAME: fismem
 * PROGRAMMER:  CL
 * DESCRIPTION: Fiscal memory (EPROM)  driver
 *
 *              API functions declarations
 *
 * REVISION:    01.00 25/04/99
 ***************************************************************************/
          /*==========================================*
           *         I N T R O D U C T I O N          *
           *==========================================*/
/**
Fiscal memory is an EPROM used in the ECR to store tax-sensitive information.
The size of the chip and the structure of the information has to be defined
by tax authority and, therefore, are outside the scope of this description.
There are 2 functions accessable by the application : _Write and _Read.
The parameters are the same: 1)the start address to write/read within the
Fiscal memory chip, 2)the application buffer to write from / read to, and 3)
the buffer's size. Therefore the area in the fiscal memory chip to write to /
read from has the limits: [StartAddress...StartAddress+BufferSize[

The address of the first byte in the fiscal memory is 00000, the last byte
address is FISMEM_SIZE-1, where FISMEM_SIZE is the size of the fiscal memory
chip, as it was defined in hardware specifications.

Physically the writing means turning few or all ones to zeroes. This process
is unreversible, i.e. there's impossible to turn a zero to one. The module
FISMEM doesn't check whether the current state of a bit (before writing)
is '0'. It means that trying to write 0x80 into byte already containing 0x01
will produce 0x00, i.e the actual result of the writing is bitwise AND of
old and new values.


*/

          /*==========================================*
           *         P A R A M E T E R S              *
           *==========================================*/
/* void */

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/
#define FISMEM_OK              0
#define FISMEM_FAIL           -1
#define FISMEM_OVERFLOW       -2
#define FISMEM_NO_EXIST       -3   /* FisMem driver doesn't exist*/
#define FISMEM_NO_TYPE        -4   /* FisMem type can't be read */
#define FISMEM_UNKNOWN        -5   /* FisMem type is unknown    */




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
 * FUNCTION NAME: Fismem_Write
 * DESCRIPTION:   writes buffer into the memory
 * RETURN:        FISMEM_OK        everything is ok
 *                FISMEM_NO_EXIST       - FisMem driver doesn't exist
 *                FISMEM_NO_TYPE        - FisMem type can't be read
 *                FISMEM_UNKNOWN        - FisMem type is unknown
 *                FISMEM_FAIL      fail during writing to the fiscal memory
 *                FISMEM_OVERFLOW  trying to write to out of the memory
 *                                  (StartAddress+BufferSize) > FISMEM_SIZE
 *                *BufferSize = number of good writed bytes.
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint Fismem_Write(ulint StartAddress, byte *Buffer, usint *BufferSize);

/* --------------------------------------------------------------------------
 * FUNCTION NAME: Fismem_Read
 * DESCRIPTION:   read the memory into specified buffer
 * RETURN:        FISMEM_OK        everything is ok
 *                FISMEM_NO_EXIST       - FisMem driver doesn't exist
 *                FISMEM_NO_TYPE        - FisMem type can't be read
 *                FISMEM_UNKNOWN        - FisMem type is unknown
 *                FISMEM_OVERFLOW  trying to read from out of the memory
 *                                  (StartAddress+BufferSize) > FISMEM_SIZE
 * NOTES:         none.
 * ------------------------------------------------------------------------ */
sint Fismem_Read(ulint StartAddress, byte *Buffer, usint BufferSize);

#ifdef __NOS__
  #include fismem_nos
#endif
