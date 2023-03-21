/****************************************************************************
 * FILE NAME:   APPLHEAD.C                                                  *
 * MODULE NAME: Single Application Specific Header                          *
 * PROGRAMMER:  Lipman Application Wizard                                   *
 * NOTES:       Set the number of DLMs field to 1                           *
 * REVISION:    01.00                                                       *
 ****************************************************************************/

#include "project.def"
#include nurit_def
#include liptypes_def
#include applhead_def
#include dlmlinkr_def

extern void static_data_size(void);
extern DLMEntryData BaseDlmIndex;

static const application_header id =
              {
                APPL_SIGNATURE,                       /* Signatrue              */
                ((unsigned long)static_data_size),    /* End of Static data     */
                {'0','1','.','0','0'},                /* minimum NOS Version    */
                {"PlayGrnd"},                         /* Application Name       */
                {'0','1','.','0','0'},                /* Application Version    */
                {"Genjitsu"},                              /* Appl Description       */
                {"01/01/01"},                         /* Date                   */
                0,                                    /* New header format      */
                0,                                    /* Number of DLMs         */
                DLMS_FIRST_DLM(BaseDlmIndex),         /* Pointer to DLM list    */
                0,                                    /* Industry type          */
                0,                                    /* Protocol type          */
                0,                                    /* Spare bytes            */
                0
              };

