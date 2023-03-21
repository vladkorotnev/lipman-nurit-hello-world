/****************************************************************************
 *                                                                          *
 * FILE NAME:   NBMP.H                                                      *
 *                                                                          *
 * MODULE NAME: NBMP                                                        *
 *                                                                          *
 * PROGRAMMER:  Oren Sokoler                                                *
 *                                                                          *
 * DESCRIPTION: NOS Bitmap public definitions                               *
 *                                                                          *
 * REVISION:    01.00 30/10/02.                                             *
 *                                                                          *
 ****************************************************************************/

          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

/* Function return values */

#define           NBMP_OK                0
#define           NBMP_INVALID_FORMAT    1
#define           NBMP_ARG_ERR           2
#define           NBMP_NO_BLOCK          3
#define           NBMP_FATAL_ERR         4

/* Default arguments */

#define           NBMP_USE_DEFAULT      -1

           /*=========================================*
            *   F U N C T I O N  P R O T O T Y P E S  *
            *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: NBitmap_Show
 *
 * DESCRIPTION:   Show a NBMP image on the terminal screen.
 *
 * PARAMETERS:    X         - Horizontal position on the screen or 
 *                            NBMP_USE_DEFAULT for using the default 
 *                            X position inside the block
 *                Y         - Vertical position on the screen or 
 *                            NBMP_USE_DEFAULT for using the default 
 *                            Y position inside the block
 *                BlockName - NBMP block name
 *                DisplayIt - TRUE  : Display image on the screen
 *                            FALSE : Copy image only to the virtual 
 *                                    screen
 *
 * RETURN:        NBMP_OK             - Block was processed o.k.
 *                NBMP_INVALID_FORMAT - The block contains an unsupported
 *                                      format
 *                NBMP_NO_BLOCK       - No such block was found
 *                NBMP_ARG_ERR        - Function argument error
 *                NBMP_FATAL_ERR      - Fatal error occured
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte NBitmap_Show(lint X,lint Y,const char *BlockName,boolean DisplayIt);

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: NBitmap_ShowPNG
 *
 * DESCRIPTION:   Show a PNG image on the terminal screen.
 *
 * PARAMETERS:    X         - Horizontal position on the screen.
 *                Y         - Vertical position on the screen.
 *                BlockName - NBMP block name
 *                DisplayIt - TRUE  : Display image on the screen
 *                            FALSE : Copy image only to the virtual 
 *                                    screen
 *
 * RETURN:        NBMP_OK             - Picture was processed o.k.
 *                NBMP_INVALID_FORMAT - The block contains an unsupported
 *                                      format
 *                NBMP_ARG_ERR        - Function argument error
 *                NBMP_FATAL_ERR      - Fatal error occured
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
byte NBitmap_ShowPNG(lint X,lint Y,byte * PngPtr,boolean DisplayIt);
