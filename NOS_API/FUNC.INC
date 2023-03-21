PUBLIC     _Formater_DialogeBox              =$800
PUBLIC     _Formater_GoMenu                  =$806
PUBLIC     _Formater_GetStrChoice            =$80C
PUBLIC     _SysUtil_GetAccount               =$812
PUBLIC     _SysUtil_EnterSum                 =$818
PUBLIC     _Formater_PreDialogeBox           =$81E
PUBLIC     _Formater_GoMenuEntry             =$824
PUBLIC     _RtcUtil_Enter_TimeOrDate         =$82A



PUBLIC     _PrntUtil_ALine                   =$830
PUBLIC     _PrntUtil_Int                     =$836
PUBLIC     _PrntUtil_DataSum                 =$83C
PUBLIC     _PrntUtil_Date                    =$842
PUBLIC     _PrntUtil_DateTime                =$848
PUBLIC     _PrntUtil_IntTime                 =$84E
PUBLIC     _PrntUtil_Ldate                   =$854
PUBLIC     _PrntUtil_LDate                   =$854
PUBLIC     _PrntUtil_Line                    =$85A
PUBLIC     _PrntUtil_Long                    =$860
PUBLIC     _PrntUtil_LongDate                =$866
PUBLIC     _PrntUtil_LongDateCr              =$86C
PUBLIC     _PrntUtil_Sum                     =$872
PUBLIC     _PrntUtil_SumCr                   =$878
PUBLIC     _PrntUtil_Time                    =$87E
PUBLIC     _PrntUtil_Cr                      =$884
PUBLIC     _PrntUtil_FormFeed                =$88A
PUBLIC     _PrntUtil_UpperCase               =$890
PUBLIC     _PrntUtil_WaitForPrinting         =$896
PUBLIC     _PrntUtil_BufAsciiHex             =$89C
PUBLIC     _Util_JulianDate                  =$8A2
PUBLIC     _SysUtil_SetLanguage              =$8A8
PUBLIC     _ComHndlr_SetUserParams           =$8AE
PUBLIC     _ComHndlr_ActivateBkGrMsg         =$8B4
PUBLIC     _ComHndlr_StopBkGrMsg             =$8BA
PUBLIC     _SysUtil_GetAcc2                  =$8C0
PUBLIC     _SysUtil_PageEditor               =$8C6
PUBLIC     _SysUtil_LineEditor               =$8CB
PUBLIC     _SysUtil_RotateStr                =$8D2
PUBLIC     _Display_PopUp                    =$8D8
PUBLIC     _Display_PopDown                  =$8DE
PUBLIC     _Display_ClrLDisp                 =$8E4
PUBLIC     _Display_ClrUDisp                 =$8EA
PUBLIC     _Display_Cls                      =$8F0
PUBLIC     _Display_ClrDsp                   =$8F6
PUBLIC     _Display_BlinkingOn               =$8FC
PUBLIC     _Display_BlinkingOff              =$902
PUBLIC     _Display_DownDisplay              =$908
PUBLIC     _Display_UpDisplay                =$90E
PUBLIC     _Display_Write                    =$914
PUBLIC     _Display_WriteStr                 =$91A
PUBLIC     _Display_OnOff                    =$920
PUBLIC     _Display_VisibleCursor            =$926
PUBLIC     _Display_BlinkAtCursor            =$92C
PUBLIC     _Display_CursorMoveTo             =$932
PUBLIC     _Rtc_SetTime                      =$938
PUBLIC     _Rtc_SetDate                      =$93E
PUBLIC     _Uart_Init                        =$944
PUBLIC     _Uart_SendByte                    =$94A
PUBLIC     _Uart_GetByte                     =$950
PUBLIC     _Uart_SendBuf                     =$956

PUBLIC     _Kb_Insert                        =$95C
PUBLIC     _Kb_Read                          =$962
PUBLIC     _Kb_WaitForKey                    =$968
PUBLIC     _Kbhw_BuzzerPulse                 =$96E
PUBLIC     _Kb_Idle                          =$974

PUBLIC     _ComHndlr_ChangeParam             =$97A
PUBLIC     _ComHndlr_RadioOn                 =$980
PUBLIC     _ComHndlr_RadioOff                =$986
PUBLIC     _ComHndlr_RxConditions            =$98C

PUBLIC     _Mte_Wait                         =$992

PUBLIC     _ComHndlr_Menu                    =$998
PUBLIC     _ComHndlr_TxLine                  =$99E
PUBLIC     _ComHndlr_RxRadio                 =$9A4
PUBLIC     _ComHndlr_TxRadio                 =$9AA
PUBLIC     _ComHndlr_EndCall                 =$9B0
PUBLIC     _ComHndlr_Call1                   =$9B6

PUBLIC     _Printer_WriteStr                 =$9BC
PUBLIC     _Printer_Write                    =$9C2
PUBLIC     _Printer_GetStatus                =$9C8
PUBLIC     _Printer_LineSpacing              =$9CE
PUBLIC     _Printer_WaitForGraphicsReady     =$9D4
PUBLIC     _Printer_WaitForTextReady         =$9DA
PUBLIC     _ComHndlr_AfterLoad               =$9E0
PUBLIC     _ComHndlr_RxLineDirect            =$9E6
PUBLIC     _ComHndlr_GetAutoAnswerState      =$9EC


PUBLIC     _ApplMngr_LedOff                  =$9F2
PUBLIC     _ApplMngr_LedOn                   =$9F8
PUBLIC     _ApplMngr_Diagnostics             =$9FE

*** Old Prototype:
PUBLIC     _Main_RestartAppl                 =$A04
PUBLIC     _Main_LoadParams                  =$A0A
PUBLIC     _Main_IsApplFirstRun              =$A10

*** New Prototype:
PUBLIC     _ApplMngr_RestartAppl             =$A04
PUBLIC     _ApplMngr_LoadParams              =$A0A
PUBLIC     _ApplMngr_IsApplFirstRun          =$A10

PUBLIC     _Errlog_Insert                    =$A16
PUBLIC     _Errlog_GetModuleCode             =$A1C
PUBLIC     _Errlog_DebugInsert               =$A22

PUBLIC     _Util_AddTime                     =$A28
PUBLIC     _Util_AsciiToBcd                  =$A2E
PUBLIC     _Util_BcdToAscii                  =$A34
PUBLIC     _Util_DateToLong                  =$A3A
PUBLIC     _Util_AccountCompress             =$A40
PUBLIC     _Util_BufCompare                  =$A46
PUBLIC     _Util_AccountDecompress           =$A4C
PUBLIC     _Util_Itoa                        =$A52
PUBLIC     _Util_IToA                        =$A52
PUBLIC     _Util_IncrementDate               =$A58
PUBLIC     _Util_LToA                        =$A5E
PUBLIC     _Util_MemCopy                     =$A64
PUBLIC     _Util_MemFill                     =$A6A
PUBLIC     _RtcUtil_SetTimeDate              =$A70
PUBLIC     _Util_SumToStr                    =$A76
PUBLIC     _ComHndlr_Call2                   =$A7C
PUBLIC     _RtcUtil_EnterDate                =$A82
PUBLIC     _Util_UlintToStr                  =$A88
PUBLIC     _Util_LongToDate                  =$A8E
PUBLIC     _Util_ShortToTime                 =$A94
PUBLIC     _RtcUtil_GetLongDate              =$A9A
PUBLIC     _CardRdr_Enable                   =$AA0
PUBLIC     _CardRdr_Disable                  =$AA6
PUBLIC     _CardRdr_GetTrack1                =$AAC
PUBLIC     _CardRdr_GetTrack2                =$AB2
PUBLIC     _CardRdr_GetSiteNo                =$AB8
PUBLIC     _Modem_SetParam                   =$ABE
PUBLIC     _CardRdr_IsCardCompleted          =$AC4
PUBLIC     _Rtc_Read                         =$ACA
PUBLIC     _Modem_ChangeParam                =$AD0
PUBLIC     _RamDisk_NewFile                  =$AD6
PUBLIC     _RamDisk_Append                   =$ADC
PUBLIC     _RamDisk_Seek                     =$AE2
PUBLIC     _RamDisk_Read                     =$AE8
PUBLIC     _RamDisk_Delete                   =$AEE
PUBLIC     _RamDisk_ClearFile                =$AF4
PUBLIC     _RamDisk_Insert                   =$AFA
PUBLIC     _RamDisk_Alloc                    =$B00
PUBLIC     _RamDisk_EraseFile                =$B06
PUBLIC     _RamDisk_ChkDsk                   =$B0C
PUBLIC     _RamDisk_CheckSize                =$B12
PUBLIC     _RamDisk_Reopen                   =$B18
PUBLIC     _RamDisk_Reset                    =$B1E
PUBLIC     _RamDisk_GetFreeSpace             =$B24
PUBLIC     _ComHndlr_RbmTxRadio              =$B2A

PUBLIC     _ApplMngr_GetNosType              =$B36
PUBLIC     _Params_Get                       =$B3C
PUBLIC     _Params_Set                       =$B42
PUBLIC     _Params_GetPtr                    =$B48
PUBLIC     _Params_SetIndex                  =$B4E
PUBLIC     _Formater_AdditionalExitKey       =$B54
PUBLIC     _Formater_SetAutoScroll           =$B5A
PUBLIC     _Cpuhw_IsRadio                    =$B60
PUBLIC     _Cpuhw_IsBattery                  =$B66
PUBLIC     _Cpuhw_SwitchTo                   =$B6C
PUBLIC     _Cpuhw_Switch1Direction           =$B72

PUBLIC     _Scan_MillSec                     =$B84
PUBLIC     _ComHndlr_RxRadioOrLine           =$B8A
PUBLIC     _ComHndlr_PreDialBkgr             =$B90
PUBLIC     _ComHndlr_PreDialForegrnd         =$B96

PUBLIC     _Test_RadioRSSI                   =$B9C
PUBLIC     _Test_RadioInfo                   =$BA2
PUBLIC     _Test_RadioMan                    =$BA8
PUBLIC     _Test_Battery                     =$BAE

PUBLIC     _Printer_FlushBuffer              =$BB4

PUBLIC     _Link_Init                        =$BCC
PUBLIC     _Link_Receive                     =$BD8
PUBLIC     _Link_Send                        =$BDE
PUBLIC     _Link_SendAck                     =$BE4
PUBLIC     _Link_GetCrc16Table               =$BEA

PUBLIC     _Uart_RtsCtsSetMode               =$BF0
PUBLIC     _Uart_RtsCtsClrMode               =$BF6
PUBLIC     _Uart_DtrSetMode                  =$BFC
PUBLIC     _Uart_DtrClrMode                  =$C02
PUBLIC     _Uart_Flush                       =$C08
PUBLIC     _Uart_DtrSet                      =$C0E
PUBLIC     _Uart_DtrClear                    =$C14
PUBLIC     _Uart_RtsSet                      =$C1A
PUBLIC     _Uart_RtsClear                    =$C20
PUBLIC     _Uart_Read_CTS                    =$C26
PUBLIC     _Uart_Read_CD                     =$C2C
PUBLIC     _Uart_Read_RI                     =$C32
PUBLIC     _Uart_GetBuf                      =$C38
PUBLIC     _Uart_CheckBuf                    =$C3E
PUBLIC     _Uart_SendStatus                  =$C44
PUBLIC     _ComHndlr_RxHdlc                  =$C4A
PUBLIC     _ComHndlr_WaitForSyncCall         =$C50
PUBLIC     _ComHndlr_WaitForAsyncCall        =$C56
PUBLIC     _ComHndlr_DisableWaitForCall      =$C5C
PUBLIC     _ComHndlr_SetLanguage             =$C62
PUBLIC     _ComHndlr_TxHdlc                  =$C68


PUBLIC     _itoa                             =$C6E
PUBLIC     _strcat                           =$C74
PUBLIC     _strncpy                          =$C7A
PUBLIC     _ltoa                             =$C80
PUBLIC     _sprintf                          =$C86
PUBLIC     _atol                             =$C8C
PUBLIC     _atoi                             =$C92
PUBLIC     __lrem                            =$C98
PUBLIC     _memset                           =$C9E
PUBLIC     __lmul                            =$CA4
PUBLIC     __ldiv                            =$CAA
PUBLIC     _memcmp                           =$CB0
PUBLIC     _Test_IsEeprom                    =$10CB6
PUBLIC     _Eeprom_Reset                     =$10CBC
PUBLIC     _Eeprom_Read                      =$10CC2
PUBLIC     _Eeprom_Write                     =$10CC8
PUBLIC     _ComHndlr_DialShow                =$10CCE
*** new RAM DISK functions
PUBLIC     _RamDisk_DeleteTLV                =$10CD4
PUBLIC     _RamDisk_ReadTLV                  =$10CDA
PUBLIC     _RamDisk_CreateTLVFile            =$10CE0
PUBLIC     _RamDisk_WriteTLV                 =$10CE6
PUBLIC     _RamDisk_FastAppend               =$10CEC
PUBLIC     _RamDisk_GetNumberOfRecords       =$10CF2
PUBLIC     _RamDisk_BinarySearchSequence     =$10CF8
PUBLIC     _RamDisk_Rename                   =$10CFE
PUBLIC     _RamDisk_ExtractRecord            =$10D04
PUBLIC     _RamDisk_ChangeTimeStamp          =$10D10
PUBLIC     _RamDisk_LinearSearchPattern      =$10D16
PUBLIC     _RamDisk_Overwrite                =$10D1C
PUBLIC     _RamDisk_SetTimeStamp             =$10D22
PUBLIC     _RamDisk_GetTimeStamp             =$10D28
*** NURIT-2080 new function
PUBLIC     _Printer_GetLineFormat            =$10D2E
PUBLIC     _Printer_SetMode                  =$10D34
PUBLIC     _Kb_NosEnable                     =$10D3A
PUBLIC     _Kb_NosDisable                    =$10D40
PUBLIC     _ApplMngr_Shell                   =$10D46
PUBLIC     _Formater_SetTout                 =$10D4C
*** COMHNDLR new function
PUBLIC     _ComHndlr_LinkInit                =$10D52
PUBLIC     _ComHndlr_LinkSnd                 =$10D58
PUBLIC     _ComHndlr_LinkRcv                 =$10D5E
PUBLIC     _ComHndlr_LinkCheckRcv            =$10D64
PUBLIC     _Errlog_GetSingleError            =$10D6A
PUBLIC     _Errlog_Clear                     =$10D70
PUBLIC     _SafeDB_StoreBlock                =$10D76
PUBLIC     _SafeDB_GetBlock                  =$10D7C
PUBLIC     _Caller_GetLastConnectStatus      =$10D82
PUBLIC     _Kb_NosModeSet                    =$10D88
PUBLIC     _ICC_Status                       =$10D8E
PUBLIC     _ICC_AnswerToReset                =$10D94
PUBLIC     _ICC_Command                      =$10D9A
PUBLIC     _ICC_EMVCommand                   =$10DA0
PUBLIC     _ICC_CommandT1                    =$10DA6
PUBLIC     _ICC_SendReceiveT1                =$10DAC
PUBLIC     _ICC_SetIFS                       =$10DB2
PUBLIC     _SafeDB_Build                     =$10DB8
PUBLIC     _SafeDB_Verify                    =$10DBE
PUBLIC     _Cpuhw_CheckPhoneLine             =$10DC4
PUBLIC     _ComHndlr_SetCallerLanguage       =$10DCA

PUBLIC     _GrphText_Format                  =$10DD0
PUBLIC     _GrphText_FontPrm                 =$10DD6
PUBLIC     _GrphText_PopUp                   =$10DDC
PUBLIC     _GrphText_PopAll                  =$10DE2
PUBLIC     _GrphText_PopDown                 =$10DE8
PUBLIC     _GrphText_Cls                     =$10DEE
PUBLIC     _GrphText_ClrArea                 =$10DF4
PUBLIC     _GrphText_ClrToEndOfLine          =$10DFA
PUBLIC     _GrphText_ClrLine                 =$10E00
PUBLIC     _GrphText_RevVideo                =$10E06
PUBLIC     _GrphText_Write                   =$10E0C
PUBLIC     _GrphText_WriteByCursor           =$10E12
PUBLIC     _GrphText_GetLineCol              =$10E18
PUBLIC     _GrphText_SetCursorPosition       =$10E1E
PUBLIC     _GrphText_GetCursorPosition       =$10E24
PUBLIC     _GrphText_CursorAttribute         =$10E2A
PUBLIC     _GrphText_DrawDisp                =$10E30
PUBLIC     _GrphText_LineToPixel             =$10E36
PUBLIC     _GrphText_DispInfo                =$10E3C
PUBLIC     _GrphDisp_Line                    =$10E42
PUBLIC     _GrphText_ShowImage               =$10E48
PUBLIC     _GrphText_InvertLine              =$10E4E
PUBLIC     _Formater_Form                    =$10E54
PUBLIC     _ComHndlr_PreDialBkgr2            =$10E5A
PUBLIC     _ComHndlr_GetStatistics           =$10E60
PUBLIC     _ApplMngr_CommPrmMenu             =$10E66
PUBLIC     _ApplMngr_ReplaceAppl             =$10E6C
PUBLIC     _ApplMngr_GetCommPrm              =$10E72
PUBLIC     _ApplMngr_GetNosVers              =$10E78
PUBLIC     _ApplMngr_GetTerminalID           =$10E7E
PUBLIC     _FTP_Init                         =$10E84
PUBLIC     _FTP_Menu                         =$10E8A
PUBLIC     _FTP_SendFile                     =$10E90
PUBLIC     _FTP_ReceiveFile                  =$10E96
PUBLIC     _FTP_SetUserMessages              =$10E9C
PUBLIC     _FTP_SendDisk                     =$10EA2
PUBLIC     _FTP_ReceiveDisk                  =$10EA8
PUBLIC     _Printer_CheckPaperDisable        =$10EAE
PUBLIC     _Printer_CheckPaperEnable         =$10EB4
*** NURIT-2080 RS-485 function ***
PUBLIC     _Flink_CreateStation              =$10EBA
PUBLIC     _Flink_DestructStation            =$10EC0
PUBLIC     _Flink_SetMode                    =$10EC6
PUBLIC     _Flink_Send                       =$10ECC
PUBLIC     _Flink_Receive                    =$10ED2
PUBLIC     _Flink_GetChannelStatus           =$10ED8
PUBLIC     _Flink_GetTxStatus                =$10EDE
PUBLIC     _Mte_ConnectToBkgr                =$10EE4
PUBLIC     _ComHndlr_SetExPrefix             =$10EEA
*** KB new functions ***
PUBLIC     _Kb_ClickTimeSet                  =$10EF0
PUBLIC     _Kb_OffTimeSet                    =$10EF6
*** Cash register functions
PUBLIC     _Cpuhw_OpenDrawer                 =$10EFC
PUBLIC     _BarCode_Disable                  =$10F02
PUBLIC     _BarCode_IsCompleted              =$10F08
PUBLIC     _BarCode_BufferAddress            =$10F0E
****New Display functions: *****************
PUBLIC     _Display_SetFont                  =$10F14
PUBLIC     _Display_FormatWrite              =$10F1A
PUBLIC     _GrphText_SwitchDisplay           =$10F20
PUBLIC     _ICC_Disactive                    =$10F26
PUBLIC     _ComHndlr_CallDirectRadio         =$10F2C
PUBLIC     _Cpuhw_BackLightMenu              =$10F32
PUBLIC     _Cpuhw_SetBackLight               =$10F38
PUBLIC     _Printer_PrintBitMap              =$10F3E
PUBLIC     _ApplMngr_GetExtModemPrm          =$10F44
PUBLIC     _Phone_GetKeyStruct               =$10F4A
PUBLIC     _Touch_GetDiscretePoint           =$10F50
PUBLIC     _IccSyn_RunScript                 =$10F56
PUBLIC     _Statistics_System                =$10F5C
PUBLIC     _Statistics_Communication         =$10F62
PUBLIC     _Appload_Copy                     =$10F68
****Fiscal memory functions ****************
PUBLIC     _Fismem_Write                     =$10F6E
PUBLIC     _Fismem_Read                      =$10F74

PUBLIC     _Cpuhw_TechnicianJumperOn         =$10F7A
PUBLIC     _SysUtil_SetApplLanguage          =$10F80

****External keyboard functions ****************
PUBLIC     _ExtKb_Read                       =$10F86
PUBLIC     _ExtKb_Flush                      =$10F8C

PUBLIC     _ComHndlr_TxHdlcWithAck           =$10F92

PUBLIC     _ExtendKb_Read                    =$10F98
PUBLIC     _ExtendKb_Enable                  =$10F9E
PUBLIC     _ExtendKb_Disable                 =$10FA4
PUBLIC     _ExtendKb_WaitForKey              =$10FAA
PUBLIC     _ExtendKb_Insert                  =$10FB0

PUBLIC     _ComHndlr_DialModeSet             =$10FB6

PUBLIC     _Printer_GraphLogo                =$10FBC
PUBLIC     _GrphText_ShowLogo                =$10FC2

PUBLIC     _GrphText_ReSize                  =$10FC8

PUBLIC     _ComHndlr_GetRadioStatus          =$10FCE
PUBLIC     _Cpuhw_GetBatteryEnergy           =$10FD4
PUBLIC     _CardRdr_SetBeepTime              =$10FDA
PUBLIC     _Cpuhw_SetMessages                =$10FE0
PUBLIC     _Printer_SetMessages              =$10FE6
PUBLIC     _CardRdr_IsAnyTrackCompleted      =$10FEC
PUBLIC     _ComHndlr_SetUserMsgs             =$10FF2
PUBLIC     _ComHndlr_SetCallerUserMsgs       =$10FF8

PUBLIC     _FornProt_EndOfWrite              =$10FFE
PUBLIC     _FornProt_StartWriteAppl          =$11004
PUBLIC     _FornProt_WriteAppl               =$1100A
PUBLIC     _ApplMngr_CustomLoaderConnect     =$11010
PUBLIC     _ApplMngr_CloseConnection         =$11016

PUBLIC     _ComHndlr_SetRadioDriverMode      =$1101C

PUBLIC     _ComHndlr_RadioSendMessage        =$11022
PUBLIC     _ComHndlr_RadioEnableRxMessages   =$11028
PUBLIC     _ComHndlr_RadioDisableRxMessages  =$1102E

PUBLIC     _GSMTest_RadioToPC                =$11034
PUBLIC     _GSMRadio_VoiceRIDisable          =$1103A
PUBLIC     _GSMRadio_VoiceRIEnable           =$11040
PUBLIC     _GSMRadio_VoiceAnswer             =$11046

PUBLIC     _ComHndlr_SetupRadio              =$1104C

PUBLIC     _WinForm_ShowPanel                =$11052
PUBLIC     _WinForm_ClearClientArea          =$11058
PUBLIC     _WinForm_DeletePanel              =$1105E
PUBLIC     _WinForm_GetClientArea            =$11064
PUBLIC     _WinForm_RunForm                  =$1106A
PUBLIC     _AtmMenu_SetOptions               =$11070
PUBLIC     _AtmMenu_Run                      =$11076

PUBLIC     _GrphDisp_NewLine                 =$1107C
PUBLIC     _GrphDisp_SetPixel                =$11082
PUBLIC     _GrphText_SetColors               =$11088
PUBLIC     _GrphText_GetColors               =$1108E
PUBLIC     _GrphText_FillWithText            =$11094

PUBLIC     _FSTP_Open                        =$1109A
PUBLIC     _FSTP_Close                       =$110A0
PUBLIC     _FSTP_Abort                       =$110A6
PUBLIC     _FSTP_End                         =$110AC
PUBLIC     _FSTP_GetFileHeader               =$110B2
PUBLIC     _FSTP_Reverse                     =$110B8
PUBLIC     _FSTP_Response                    =$110BE
PUBLIC     _FSTP_RetrieveFile                =$110C4
PUBLIC     _FSTP_StoreFile                   =$110CA

PUBLIC     _ProtMngr_ConnectDestination      =$110D0
PUBLIC     _ProtMngr_DisconnectDestination   =$110D6

PUBLIC     _TCPAPI_Open                      =$110DC
PUBLIC     _TCPAPI_SetTimeout                =$110E2
PUBLIC     _TCPAPI_Close                     =$110E8
PUBLIC     _TCPAPI_Send                      =$110EE
PUBLIC     _TCPAPI_Receive                   =$110F4
PUBLIC     _TCPAPI_GetStatus                 =$110FA

PUBLIC     _Cpuhw_IsExternalPower            =$11100
PUBLIC     _Config_GetPlatform               =$11106

PUBLIC     _Touch_Enable                     =$1110C
PUBLIC     _Touch_Disable                    =$11112
PUBLIC     _Touch_GetPoint                   =$11118

PUBLIC     _GSMRadio_GetSIMLockState         =$1111E
PUBLIC     _GSMRadio_SetSIMLockState         =$11124
PUBLIC     _GSMRadio_ChangePIN               =$1112A
PUBLIC     _GSMRadio_GetLastError            =$11130
PUBLIC     _GSMRadio_GetCurrentOperator      =$11136

PUBLIC     _ComHndlr_GetRadioInfo            =$1113C

PUBLIC     _MultiApplMngr_SetTimer           =$11142
PUBLIC     _MultiApplMngr_ConnectHotKey      =$11148

PUBLIC     _Uart_BreakSetMode                =$1114E
PUBLIC     _GSMRadio_GetStatistics           =$11154

PUBLIC     _Signature_Capture                =$1115A
PUBLIC     _Signature_Print                  =$11160
PUBLIC     _Signature_View                   =$11166

PUBLIC     _MultiApplMngr_GetHotKey          =$1116C

PUBLIC     _RamDisk_NewFileEx                =$11172
PUBLIC     _Params_Create                    =$11178

PUBLIC     _Cpuhw_GetBatSystemStatus         =$1117E
PUBLIC     _StatusBar_SetMode                =$11184

PUBLIC     _RtcUtil_ResetPwrOnAlarm          =$1118A
PUBLIC     _RtcUtil_SetPwrOnAlarm            =$11190

PUBLIC	   _SoftKB_Disable                   =$11196
PUBLIC	   _SoftKB_Enable                    =$1119C
PUBLIC	   _Formater_EditBox                 =$111A2

PUBLIC	   _AtmHw_GetEvent                   =$111A8

PUBLIC	   _ICC_ISO_AnswerToReset            =$111AE

PUBLIC	   _ComHndlr_PreDialRadioBkgr        =$111B4
PUBLIC	   _DNS_Resolver                     =$111BA

PUBLIC	   _ComHndlr_SetRadioPwrSaveMode     =$111C0
PUBLIC     _GSMRadio_GetCardID               =$111C6
PUBLIC     _TCPAPI_PreOpen                   =$111CC
PUBLIC     _TCPAPI_PreOpenStatus             =$111D2
PUBLIC     _GSMRadio_GetCallerID             =$111D8
PUBLIC     _GSMRadio_RejectCall              =$111DE
PUBLIC     _GSMRadio_SetVolumeLevel          =$111E4
PUBLIC     _GrphText_FormatWrite             =$111EA
PUBLIC     _MultiApplMngr_PostEvent          =$111F0
PUBLIC	   _ComHndlr_GetLastModemCall        =$111F6
PUBLIC	   _Modem_SetRetrainParam            =$111FC

**** External Secure keyboard functions ****************
PUBLIC	   _SecKbMstr_SetGetPinTOut          =$11202
PUBLIC     _SecKbMstr_GetState               =$11208
PUBLIC	   _SecKbMstr_ToStateIdle            =$1120E
PUBLIC     _SecKbMstr_ToStateGetPin          =$11214
PUBLIC	   _SecKbMstr_ToStatePinObtained     =$1121A
PUBLIC     _SecKbMstr_Encrypt                =$11220
PUBLIC	   _SecKbMstr_IsEncryptionReady      =$11226
PUBLIC     _SecKbMstr_GetEncryption          =$1122C

**** Key Database functions ****************
PUBLIC	   _KeysLdr_EraseKey                 =$11232
PUBLIC     _KeysLdr_EraseKeyDB               =$11238
PUBLIC	   _KeysLdr_WriteClearKey            =$1123E
PUBLIC     _KeysLdr_IsKeyExist               =$11244

**** protmngr bkgr functions ****************
PUBLIC     _ProtMngr_ConnectDestinationBkgr  =$1124A
PUBLIC     _ProtMngr_GetStatus               =$11250
PUBLIC     _ProtMngr_ConnectForegrnd         =$11256

******** gftp functions ****************
PUBLIC     _GFTP_NewSession                  =$1125C
PUBLIC     _GFTP_FreeSession                 =$11262
PUBLIC     _GFTP_Logout                      =$11268
PUBLIC     _GFTP_Download                    =$1126E
PUBLIC     _GFTP_Upload                      =$11274
PUBLIC     _GFTP_Delete                      =$1127A

PUBLIC     _GSMRadio_CheckMessageNow         =$11280

******** session functions ****************

PUBLIC     _Session_Create                   =$11286
PUBLIC     _Session_Open                     =$1128C
PUBLIC     _Session_WaitForOpen              =$11292
PUBLIC     _Session_Close                    =$11298
PUBLIC     _Session_Abort                    =$1129E
PUBLIC     _Session_RxStruct                 =$112A4
PUBLIC     _Session_RxMsg                    =$112AA
PUBLIC     _Session_RxWord                   =$112B0
PUBLIC     _Session_RxLong                   =$112B6
PUBLIC     _Session_EOM                      =$112BC
PUBLIC     _Session_TxMsg                    =$112C2
PUBLIC     _Session_TxWord                   =$112C8
PUBLIC     _Session_TxStruct                 =$112CE
PUBLIC     _Session_TxLong                   =$112D4
PUBLIC     _Session_NewMessage               =$112DA
PUBLIC     _Session_DefaultMessages          =$112E0

PUBLIC     _NBitmap_Show                     =$112E6

PUBLIC     _GSMRadio_GetLocationInfo         =$112EC

PUBLIC     _Params_GetPtrByType              =$112F2
PUBLIC     _Params_FindFirst                 =$112F8
PUBLIC     _Params_FindNext                  =$112FE

PUBLIC     _Modem_SendAtCommand              =$11304
PUBLIC     _Modem_GetInfo                    =$1130A

PUBLIC     _KeysLdr_WriteCipheredKey         =$11310

PUBLIC     _Des_DEA                          =$11316
PUBLIC     _Des_3DES_DEA                     =$1131C
PUBLIC     _TCPAPI_SetSockOpt                =$11322

PUBLIC     _GSMRadio_SIMCardActionType       =$11328

PUBLIC     _MultiApplMngr_SetCardRdrEvent    =$1132E
PUBLIC     _MultiApplMngr_SetWinFormOption   =$11334
PUBLIC     _Params_IsDLMExist                =$1133A

PUBLIC     _SecKbMstr_ClearTestKey           =$11340
PUBLIC     _SecKbMstr_SetTestKey             =$11346
PUBLIC     _SecKbMstr_TestEncrypt            =$1134C

PUBLIC     _ApplMngr_TcpIpDownloadPrm        =$11352
PUBLIC     _ProtMngr_ConnectDestination2     =$11358
PUBLIC     _ApplMngr_LoadApplData            =$1135E
PUBLIC     _ApplMngr_GetTerminalInfo         =$11364

PUBLIC	   _SecKbMstr_VerifyOffLinePin       =$1136A

PUBLIC	   _NOS_RSA_CalculateRsa             =$11370
PUBLIC	   _NOS_RSA_UnSign                   =$11376

PUBLIC	   _NOS_SHA1_Open                    =$1137C
PUBLIC	   _NOS_SHA1_Write                   =$11382
PUBLIC	   _NOS_SHA1_Final                   =$11388

PUBLIC     _ProtMngr_GetInterfaceIPAdr       =$1138E

PUBLIC     _GrphText_GetFontHandle           =$11394
PUBLIC     _Printer_GetFontHandle            =$1139A
PUBLIC     _MultiApplMngr_CallFunc           =$113A0
PUBLIC     _MultiApplMngr_ConfigureHotKey    =$113A6
PUBLIC     _Strings_GetStr                   =$113AC
PUBLIC     _MultiApplMngr_GetApplList        =$113B2

PUBLIC     _GSMRadio_SetOperator             =$113B8
PUBLIC     _GSMRadio_GetOperators            =$113BE
PUBLIC     _GSMRadio_SetRadioOptions         =$113C4

PUBLIC     _TCPAPI_GetTimeout                =$113CA

PUBLIC     _KeysLdr_GetPinPadId              =$113D0
PUBLIC     _KeysLdr_SetPinPadId              =$113D6

PUBLIC     _ProtMngr_SetOption               =$113DC
PUBLIC     _ProtMngr_GetOption               =$113E2

PUBLIC     _Des_3DES_3Length_DEA             =$113E8

PUBLIC     _Kb_Check                         =$113EE

PUBLIC     _FornProt_ListGetFirst            =$113F4
PUBLIC     _FornProt_ListGetNext             =$113FA
PUBLIC     _FornProt_DeleteBlock             =$11400
PUBLIC     _FornProt_OpenWrite               =$11406
PUBLIC     _FornProt_Write                   =$1140C
PUBLIC     _FornProt_CloseWrite              =$11412

PUBLIC     _KeysLdr_IsSystemKeyExist         =$11418
PUBLIC     _KeysLdr_GetSystemKeyControlValue =$1141E
PUBLIC     _KeysLdr_GetKeyControlValue       =$11424

PUBLIC     _GrphText_ShowBMP                 =$1142A
PUBLIC     _GrphText_ShowRawBitmap           =$11430

PUBLIC     _NBitmap_ShowPNG                  =$11436

PUBLIC     _SecKbMstr_GetExternalKbSwVersion =$1143C





