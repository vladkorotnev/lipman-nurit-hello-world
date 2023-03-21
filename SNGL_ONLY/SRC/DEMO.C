#include "project.def"
#include  nurit_def
#include  display_h
#include  kb_h
#include  mte_h
#include  printer_h
#include <stdio.h>
#include <string.h>
#include  uart_h
#include  cpuhw_h
#include formater_def
#include formater_h
#include cardrdr_h

 /* Entries to appear in the menu */
 static const entry menu_entries[]=
    {
         { "SerialPrinter", 0 , 0 , 0 } ,
         { "HelloCard", 0 , 0 , 0 },
	{ "RawCard", 0 , 0 , 0 },
	{ "AdvancedPrinter", 0 , 0 , 0 }
    } ;
/* Menu */
static const menu function_menu =
    {
          "Genjitsu Labs",
          sizeof(menu_entries)/sizeof(entry) ,
          (entry *)&menu_entries[0],
          DEFAULT_MODE|MENU_TIMEOUT_2_MIN
    } ;



static comm_param CommSetting = { UART_BAUD_9600, 8, 'n', FALSE, TRUE };


void genjitsu_print () {
	sint   ret, gotData ;
    char   buf[32];
    byte   serbuf[32];
    
    Display_Cls(DSPL1);
    Display_SetFont(7);
    Display_UpDisplay("Genjitsu Printer");
    Display_SetFont(1);
    Display_OnOff(DSPL1, TRUE);
    Display_WriteStr(DSPL2, "(C) Akasaka, 2016");
    
    Display_PopUp(DSPL1, "Starting COM", buf);
    ret = Uart_Init(UART_A, &CommSetting);
    Display_PopDown(DSPL1, buf);
    if( ret != UART_OK ) {
    	if(ret == UART_ER) Display_PopUp(DSPL1, "COM Error, halt.", buf);
    	else if (ret == NO_UART) Display_PopUp(DSPL1, "COM not exist", buf);
    	else if (ret == UART_NO_CREATE) Display_PopUp(DSPL1, "COM not create", buf);
    	while( TRUE ) {
    		Mte_Wait(100);
    		if(Kb_Read() == MENU) return;
    	}
    }
    Uart_Flush(UART_A);
    
    Display_Cls(DSPL1);
    Display_SetFont(7);
    Display_WriteStr(DSPL1, "Printer on: 9600b, 8bit, no parity");
    Display_SetFont(1);
    
    
    while( TRUE )
    {
        /* Call background */
        if(Kb_Read() == MENU) return;
       
       /* Check if printer ready */
       
        ret = Printer_GetStatus();
        while( ret != 0 ) {
        	if(Kb_Read() == MENU) return;
        	if (ret == PRINTER_ACTIVE) {
        		Display_PopUp(DSPL1, "Printer busy, wait...", buf);
        	}
        	if (ret == PAPER_OUT) {
        		Display_PopUp(DSPL1, "Insert paper!", buf);
        	}
        	if (ret == PAPER_JEM) {
        		Display_PopUp(DSPL1, "Mechanical issues!", buf);
        	}
        	Mte_Wait(250);
        	Display_PopDown(DSPL1, buf);
        	if(Kb_Read() == MENU) return;
        	Mte_Wait(250);
        	ret = Printer_GetStatus();
        	Uart_GetBuf(UART_A, serbuf, 32);
        }
        
        	/* Have Data */
        	ret = Printer_GetStatus();
        	if(Uart_CheckBuf(0,serbuf,1) > 0) {
        		Display_PopUp(DSPL1, "Printing", buf);
        		Mte_Wait(250);
        		if(Kb_Read() == MENU) return;
        			while( (ret == 0 || ret == PRINTER_ACTIVE) && Uart_CheckBuf(UART_A,serbuf,1) > 0) {
						gotData = Uart_GetBuf(UART_A, serbuf, 32);
						Printer_Write((const char *)serbuf, gotData);
						Display_Write(DSPL1, (char*)serbuf, gotData);
						if(Kb_Read() == MENU) return;
						ret = Printer_GetStatus();
					} 
        		Display_PopDown(DSPL1, buf);
        	}
        	
        Mte_Wait(100);
    }
}

void card_reader() {
	Display_Cls(DSPL1);
    Display_UpDisplay("Swipe a card >>>");
    Display_SetFont(1);
    Display_OnOff(DSPL1, TRUE);
     Display_SetFont(0);
    CardRdr_SetBeepTime(300);
    CardRdr_Enable();
    boolean track_ret;
     sint tr1_error, tr2_error;
	while( TRUE ) {
		if(Kb_Read() == MENU) break;
		
		track_ret = CardRdr_IsAnyTrackCompleted(&tr1_error, &tr2_error);
		if(track_ret && (tr1_error == 0) && (tr2_error == 0)) {
			char* trk1 = (char*)CardRdr_GetTrack1();
			
			// Get Card Number
			char cardno[16];
			memcpy(cardno, &trk1[2], 16);
			Printer_WriteStr("Card #:");
			Printer_Write(cardno, 16);
			Printer_WriteStr("\r\n");
			// Get Holder Name
			char owner[26];
			memcpy(owner, &trk1[19], 26);
			Printer_WriteStr("Name:");
			Printer_Write(owner, 26);
			Printer_WriteStr("\r\n");
			// Get Expire Date
			char expire[4];
			memcpy(expire, &trk1[46], 4);
			Printer_WriteStr("Expires:");
			Printer_Write( expire, 4);
			Printer_WriteStr("\r\n");

			Printer_AdjustPaper(50);
		} 
	
		Mte_Wait(100);
	}
	CardRdr_Disable();
}


void raw_reader() {
	Display_Cls(DSPL1);
    Display_UpDisplay("Raw card reader >>>");
    Display_SetFont(1);
    Display_OnOff(DSPL1, TRUE);
     Display_SetFont(0);
    CardRdr_SetBeepTime(300);
    CardRdr_Enable();
    boolean track_ret;
     sint tr1_error, tr2_error;
	while( TRUE ) {
		if(Kb_Read() == MENU) break;
		
		track_ret = CardRdr_IsAnyTrackCompleted(&tr1_error, &tr2_error);
		if(track_ret && (tr1_error == 0) && (tr2_error == 0)) {
			char* trk1 = (char*)CardRdr_GetTrack1();
			
			Printer_WriteStr("Trk1:\r\n");
			Printer_Write(trk1, 79);
			Printer_WriteStr("\r\n");
			
			trk1 = (char*)CardRdr_GetTrack2();
			
			Printer_WriteStr("Trk2:\r\n");
			Printer_Write(trk1, 79);
			Printer_WriteStr("\r\n");
			Printer_AdjustPaper(50);
		} 
	
		Mte_Wait(100);
	}
	CardRdr_Disable();
}

void mega_print() {
sint   ret, gotData ;
    char   buf[128];
    byte   serbuf[128];
    
    Display_Cls(DSPL1);
    Display_SetFont(7);
    Display_UpDisplay("Advanced Printer");
    Display_SetFont(1);
    Display_OnOff(DSPL1, TRUE);
    Display_WriteStr(DSPL2, "(C) Akasaka, 2016");
    
    Display_PopUp(DSPL1, "Starting COM", buf);
    ret = Uart_Init(UART_A, &CommSetting);
    Display_PopDown(DSPL1, buf);
    if( ret != UART_OK ) {
    	if(ret == UART_ER) Display_PopUp(DSPL1, "COM Error, halt.", buf);
    	else if (ret == NO_UART) Display_PopUp(DSPL1, "COM not exist", buf);
    	else if (ret == UART_NO_CREATE) Display_PopUp(DSPL1, "COM not create", buf);
    	while( TRUE ) {
    		Mte_Wait(100);
    		if(Kb_Read() == MENU) return;
    	}
    }
    Uart_Flush(UART_A);
    
    Display_Cls(DSPL1);
    Display_SetFont(7);
    Display_WriteStr(DSPL1, "9600b, 8bit, no parity");
    Display_SetFont(1);
    
    
    while( TRUE )
    {
        /* Call background */
        if(Kb_Read() == MENU) return;
       
       /* Check if printer ready */
       
        ret = Printer_GetStatus();
        while( ret != 0 ) {
        	if(Kb_Read() == MENU) return;
        	if (ret == PRINTER_ACTIVE) {
        		Display_PopUp(DSPL1, "Printer busy, wait...", buf);
        	}
        	if (ret == PAPER_OUT) {
        		Display_PopUp(DSPL1, "Insert paper!", buf);
        	}
        	if (ret == PAPER_JEM) {
        		Display_PopUp(DSPL1, "Mechanical issues!", buf);
        	}
        	Mte_Wait(250);
        	Display_PopDown(DSPL1, buf);
        	if(Kb_Read() == MENU) return;
        	Mte_Wait(250);
        	ret = Printer_GetStatus();
        	Uart_GetBuf(UART_A, serbuf, 128);
        }
        
        	/* Have Data */
        	ret = Printer_GetStatus();
        	if(Uart_CheckBuf(0,serbuf,1) > 0) {
        		Display_PopUp(DSPL1, "Active...", buf);
        		Mte_Wait(250);
        		if(Kb_Read() == MENU) return;
        			while( (ret == 0 || ret == PRINTER_ACTIVE) && Uart_CheckBuf(UART_A,serbuf,1) > 0) {
						gotData = Uart_GetBuf(UART_A, serbuf, 128);
						if( serbuf[0] == 'T' ) {
							Printer_Write((const char *)serbuf[1], gotData-1);
						} else if ( serbuf[0] == 'C' ) {
							
						}
						
						if(Kb_Read() == MENU) return;
						ret = Printer_GetStatus();
					} 
        		Display_PopDown(DSPL1, buf);
        	}
        	
        Mte_Wait(100);
    }
}
void main (void)
{
	sint ret;
	for( ; ; ) {
		ret = 0;
		/* Background utility */
        Kb_Read() ;

        /* Run the menu */
        ret = Formater_GoMenu( (menu *)&function_menu, CHOICE_MODE );
        
        /* Switch of the user entry choice */
        switch( ret )
        {
            /* Printer App */
            case 1 :
                genjitsu_print();
                break;

            /* Card Reader App */
            case 2 :
                card_reader();
                break;
	    case 3: /* Raw card reader */
		raw_reader();
		break;
	case 4: /* Advanced printer */
		mega_print();
		break;
        }
	}//for
}

