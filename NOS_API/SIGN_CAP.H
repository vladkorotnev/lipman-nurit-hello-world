/****************************************************************************
 *                                                                          *
 * FILE NAME:   SIGNATURE.H                                                 *
 *                                                                          *
 * MODULE NAME: SIGNATURE                                                   *
 *                                                                          *
 * PROGRAMMER:  Rami Rosenbaum                                              *
 *                                                                          *
 * DESCRIPTION: Captures a users' signature from the Touch-Panel.           *
 *                                                                          *
 * REVISION:    01_00                                                       *
 *                                                                          *
 ****************************************************************************/

#ifndef _SIGNATURE_H_
#define _SIGNATURE_H_


          /*==========================================*
           *           D E F I N I T I O N S          *
           *==========================================*/

#define     MAX_SIGN                   2048  /* 2KB - for 16*128 bytes of Bitmap. */

/* Module return types. */
#define     SigRetType                 sint

#define     SIGNATURE_OK                  0
#define     SIGNATURE_CANCEL              1
#define     SIGNATURE_TIMEOUT             2
#define     SIGNATURE_ERROR               5
#define     SIGNATURE_ERROR_BOX           6
#define     SIGNATURE_ERROR_PARAM         7
#define     SIGNATURE_DISABLED            8

/* Modes for Signature_Print(). For bitwise OR. */
#define     SIGNATURE_PRINT_LEFT       0x01
#define     SIGNATURE_PRINT_RIGHT      0x02
#define     SIGNATURE_PRINT_CENTER     0x04
#define     SIGNATURE_PRINT_BOX        0x08
#define     SIGNATURE_PRINT_LINE       0x10

/* Header Bar types. */
#define     BAR_CLEAR                     0
#define     BAR_INVERT                    1
#define     BAR_LINE                      2


          /*==========================================*
           *      T Y P E   D E C L A R A T I O N     *
           *==========================================*/

/* Signature - Basic data-type of module. */
typedef struct
{
   usint  Version;               /* Version of struct.  */
   usint  OffsetX;               /* Location & size     */
   usint  OffsetY;               /* of box for          */
   usint  Width;                 /* signature.          */
   usint  Height;                /*                     */
   byte   SignData[MAX_SIGN];    /* Signature data.     */
   byte   Spare[6];              /* For future use.     */
   
} Signature;


/* SigBox - a signature-capture box. */
typedef struct
{
   byte   Frame;         /* Types:   WINFRAME_NO_FRAME,
                         /  default: WINFRAME_2D_SIMPLE ( makes window 4 pixels smaller), 
                         /           WINFRAME_3D_SIMPLE */
   byte   Bar;                   /* Bar type of SigBox. */
   byte   TOutBegin;     /* Timeout in sec's till start */
   byte   TOutEnd;       /* and after end of capture.   */
   char*  Hdr;                   /* SigBox text header. */
   byte   FontID;                /* Header font.        */
   ulint  BgClr;                 /* Background color.   */
   ulint  FgClr;                 /* Foreground color.   */
   ulint  FrClr;                 /* Frame color.        */
   
} SigBox;



          /*=========================================*
           *   P U B L I C     F U N C T I O N S     *
           *=========================================*/

/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Signature_Capture
 *
 * DESCRIPTION:   Capture a signature from Touch-Panel in a specified box.
 *
 * INPUT:         Sig - signature structure.
 *                X,Y - upper left corner of capture-box (SB), in pixels.
 *                W,H - width & height of box in pixels.
 *                SB  - sig' box description.
 *
 * RETURN:        SIGNATURE_OK      - new signature saved.
 *                SIGNATURE_TIMEOUT - timeout occured before capture began.
 *                SIGNATURE_CANCEL  - capture canceled by user.
 *                SIGNATURE_ERROR_BOX - error in box creation (check params).
 *                SIGNATURE_ERROR_PARAM - error in params.
 *                SIGNATURE_DISABLED - no touch-pannel in NOS.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
SigRetType  Signature_Capture ( Signature* Sig,
								        usint      X,
                                usint      Y,
                                usint      W,
                                usint      H,
                                SigBox*    SB );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Signature_Print
 *
 * DESCRIPTION:   Print a signature on the printer.
 *
 * INPUT:         Sig    - pointer to signature structure.
 *                Mode   - a bitwise OR for printing.
 *                Offset - offset of printing from start of alignment.              
 *
 * RETURN:        Void.
 *
 * NOTES:         The func' shifts the data, row by row, Offset bits (could 
 *                be more than a byte), and then adds the box and its' offset
 *                (if mode includes Box).
 *                If total length is larger than Buf size (== printer size 
 *                in EX_DOUBLE_LINEAR), func' returns.
 *
 * ------------------------------------------------------------------------ */
void  Signature_Print ( Signature* Sig,
								ulint      Mode,
                        usint      Offset );


/* --------------------------------------------------------------------------
 *
 * FUNCTION NAME: Signature_View
 *
 * DESCRIPTION:   Display a signature on the graphic display.
 *
 * INPUT:         Sig - signature structure.
 *                X,Y - upper left corner coordinates in pixels.
 *
 * RETURN:        SIGNATURE_ERROR_BOX.
 *                SIGNATURE_DISABLED - no touch-pannel in NOS.
 *
 * NOTES:         none.
 *
 * ------------------------------------------------------------------------ */
SigRetType  Signature_View ( Signature* Sig,
                             usint      X,
                             usint      Y );


#endif _SIGNATURE_H_ /* #ifndef _SIGN_CAP_H_ */
