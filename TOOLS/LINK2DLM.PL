# ****************************************************************************
# * FILE NAME:   link2dlm.pl                                                 *
# * Module name: link2dlm                                                    *
# * PROGRAMMER:  Barak Schiby.                                               *
# * DESCRIPTION: 1. Build Nos relative function table MOTOROLA Only          *
# *              2. Build DLM jump table file .                              *
# *              2. Build DLM Lib File .                                     *
# *              3. Build DLM Api file                                       *
# * REVISION:    01.09 10/02/00.                                             *
# ****************************************************************************

#Main Entry to this application

$Cpu = "ARM";


Main_Entry();


#  * --------------------------------------------------------------------------
#  * FUNCTION NAME: Main_Entry
#  * DESCRIPTION:   read parameters from command line:
#  *                and parse them in to application parameters.
#  *
#  * PARAMETERS: none.
#  *
#  * RETURN:     none.
#  *
#  * NOTE:       none.
#  *
#  * ------------------------------------------------------------------------ *
sub Main_Entry(){

    if($ARGV[0])
    {
       $Source = $ARGV[0];
    }
    else
    {
       printf(   "No Api file found\n");
       printf(   "Useg : perl link2dlm.pl .API file \n");
       exit(1);
    }

    ($sec,$min,$hour,$mday,$mon,$year,$wday,$yday,$isdst) =
						   localtime(time);
    $Fulldate = sprintf("%02d.%02d.%04d %02d:%02d",$mday,$mon+1, $year + 1900,$hour,$min);

    # Find The Temp Directory

    @keys = keys %ENV;
    @values = values %ENV;
    $x = 0;
    foreach $_ (@keys) {
      if(/TEMP/)
      {
         $TEMP = $values[$x];
         break;
      }
      elsif(/TMP/)
      {
         $TEMP = $values[$x];
         break;
      }
      $x++;
    }

    if($TEMP eq "")
    {
       system("SET TEMP=c:\\");
       $TEMP = "c:\\";
    }



    SearchInApiFile();

    $DlmLink = "$TEMP\\DlmTable.s";
    $DlmLib  = "$TEMP\\$TmpDlmName.s";

    Link2Dlm();      # Build DLM jump table

    exit(0);
}
#  * --------------------------------------------------------------------------
#  * FUNCTION NAME: SearchInApiFile
#  * DESCRIPTION:   Search for Nos functions In one source file
#  *
#  * RETURN:     none.
#  *
#  * NOTE:       none.
#  *
#  * ------------------------------------------------------------------------ *
sub SearchInApiFile{
    unless (open(CURRENT,$Source)) {
         print STDERR "Can't open $Source: $!\n";
         exit(0);
    }

    @Lines = <CURRENT>;
    close CURRENT;

    $program = "";
    foreach $_ (@Lines){
       $program = "$program$_";
    }
    $_ = $program;

    # Delete (most) C comments. /* */

    $program =~ s {
        /\*     # Match the opening delimiter.
        .*?     # Match a minimal number of characters.
        \*/     # Match the closing delimiter.
    } []gsx;

    $_ = $program;

    # Delete (most) C++ comments. //

    $program =~ s {
        //      # Match the opening delimiter.
        .*?     # Match a minimal number of characters.
        \n     # Match the closing delimiter.
    } []gsx;

    $_ = $program;

    # Find the version


    m/\#define\s*DLM_.+_VERSION\s*\".+\"/;
    $_ = $&;
    @token = split;
    $_ = $token[2];
    s/\"//g;
    $DlmVer = $_;

    if(length($DlmVer)==0)
    {
       print "Can't find DLM_(YOUR DLM VERSION)_VERSION\n";
       exit(1);
    }


    # Find the name
    $_ = $program;
    m/\#define\s*DLM_.+_NAME\s*\".+\"/;
    $_ = $&;
    @token = split;
    $_ = $token[2];
    s/\"//g;
    $DlmName = $_;

    if(length($DlmName)==0)
    {
       print "Can't find DLM_(YOUR DLM NAME)_NAME\n";
       exit(1);
    }

    # Find the owner
    $_ = $program;
    m/\#define\s*DLM_.+_GROUP\s*\".+\"/;
    $_ = $&;
    @token = split;
    $_ = $token[2];
    s/\"//g;
    $DlmGroup = $_;

    $TmpDlmName = $DlmName;

    if(length($DlmGroup)!=0)
    {
       $DlmName = $DlmGroup;
    }
    #open(OUT,">tmp");
    #print OUT $DlmName;
    #print OUT "\n\n\n";
    #close OUT;


    #find the functions
    $_ = $program;

    @Token =  m/[\#A-Za-z0-9_ *&]+\s*[A-Za-z0-9_]+\s*\(>?[^()]+\)/g;

    foreach $_ (@Token)
    {
           #print "$_\n";
           $LastLine = $_;
           m/[A-Za-z0-9_]+\s*\(/g;
           if($` =~ m/\#/ || $` =~ m/typedef/)
           {
               # typedef found
           }
           elsif($&)
           {
                    $Ret = CheckReturnValueExist($_);
                    if($Ret == 1)
                    {
       	               $_ = $&;
       	               s/\(//;   #remove the '(' sign from the end of function
   	               s/\s//g;    #remove All white charcters from end of function
                       $Found = 0;
                       foreach $Func (@ParseFunc){
                          if($Func eq $_)
                          {
                             $Found = 1;
                             print "Duplacate Symbol defined $_ \n";
                          }

                       }
                       if($Found == 0)
                       {
                          $ParseFunc[$OutComeFunctions] = $_;
                          $Public[$OutComeFunctions++] = $LastLine;
                       }
                    }
                    else
                    {
                       #print "found non function\n";
                    }

           }

    }

}
sub Link2Dlm(){
     # Open the DlmLib.src file
     unless (open(LIBFILE, ">$DlmLib")) {
	   print STDERR "Can't open $DlmLib: $!\n";
	   exit(0);
     }
     # Open the DlmTable.src file
     unless (open(OUTFILE, ">$DlmLink")) {
	   print STDERR "Can't open $DlmLink: $!\n";
	   exit(0);
     }
     $x=0;

     foreach $_ (@ParseFunc){
       if($Cpu eq "MOTOROLA"){
          $_ = "$_"; # Add '_' sign in start of function
       }

     }


     if($Cpu eq "MOTOROLA"){
       BuildDlmIncFile();
       Write2DlmIncFile();
     }
     else
     {
       BuildDlmIncFileARM();
       Write2DlmIncFileARM();
     }

}
sub BuildDlmIncFileARM{
 print LIBFILE ";****************************************************************************";
 print LIBFILE "\n";
 print LIBFILE ";* FILE NAME:   DlmLib.s                                                    *";
 print LIBFILE "\n";
 print LIBFILE ";* Module name: DLMLIB                                                      *";
 print LIBFILE "\n";
 print LIBFILE ";* PROGRAMMER:  Lipman PreProcessor.                                        *";
 print LIBFILE "\n";
 print LIBFILE ";* DESCRIPTION: DLM Dynamic Link Lib.                                       *";
 print LIBFILE "\n";
 print LIBFILE ";* REVISION:    $DlmVer.                                                   *\n";
 print LIBFILE ";* DATE:        $Fulldate.                                                 *\n";
 print LIBFILE ";* NOTE:        This file is build by Lipman PreProcessor.                 *\n";
 print LIBFILE ";*              it is not recommended to edit it by hand.                  *\n";
 print LIBFILE ";****************************************************************************";
 print LIBFILE "\n\n
	   ;* ======================================= *
	   ;*         I N T R O D U C T I O N         *
	   ;* ======================================= *
	   ;* This is the DLM lib module \n
	   ;*==========================================*
	   ;*     A S S E M B L Y   O P T I O N S      *
	   ;*==========================================*
           .option code16      ; Assemble in 16 bit thumb mode

	   ;*==========================================*
	   ;*             I N C L U D E S              *
	   ;*==========================================*

	   ;*==========================================*
	   ;*             S Y M B O L S                *
	   ;*==========================================*

	   ;*==========================================*
	   ;*     E X T E R N A L   D E F I N I O N    *
	   ;*==========================================*
						       \n";


 print OUTFILE ";****************************************************************************\n";
 print OUTFILE ";* FILE NAME:   DlmTable.s                                                   *\n";
 print OUTFILE ";* Module name: DlmTable                                                     *\n";
 print OUTFILE ";* PROGRAMMER:  Lipman PreProcessor.                                        *\n";
 print OUTFILE ";* DESCRIPTION: DLM Dynamic Link Table.                                     *\n";
 print OUTFILE ";* REVISION:    $DlmVer.                                                    *\n";
 print OUTFILE ";* DATE:        $Fulldate.                                                  *\n";
 print OUTFILE ";* NOTE:        This file is build by Lipman PreProcessor.                  *\n";
 print OUTFILE ";*              it is not recommended to edit it by hand.                   *\n";
 print OUTFILE ";****************************************************************************\n\n";
 print OUTFILE "
	   ;* ======================================= *
	   ;*         I N T R O D U C T I O N         *
	   ;* ======================================= *
	   ;* This is the DLM Jump Table module \n
	   ;*==========================================*
	   ;*     A S S E M B L Y   O P T I O N S      *
	   ;*==========================================*
           .option code32      ; Assemble in 32 bit arm mode
	   ;*==========================================*
	   ;*             I N C L U D E S              *
	   ;*==========================================*

	   ;*==========================================*
	   ;*             S Y M B O L S                *
	   ;*==========================================*

	   ;*==========================================*
	   ;*     E X T E R N A L   D E F I N I O N    *
	   ;*==========================================*
						       \n";


}

sub Write2DlmIncFileARM{
        printf( LIBFILE "	.import BaseDlmIndex\n");
        printf( LIBFILE "	.import _%s\$\$Entry\n\n\n",$DlmName);

        printf( LIBFILE "       .seg \".dlms_index\",lit \n\n");
        printf( LIBFILE "_%sIndex:\n",$DlmName);
        printf( LIBFILE "        .long _%s\$\$Entry\n\n",$DlmName);


        printf( LIBFILE "       .seg \".dlms_entry\",lit \n\n");
        printf( LIBFILE "_%sEntry:\n",$DlmName);
        printf( LIBFILE "           .size  _%sEntry,0x14\n",$DlmName);
        printf( LIBFILE "           .ascii \"%s\"\n",$DlmName);
        printf( LIBFILE "           .ascii \"%s\"\n",$DlmVer);
        printf( LIBFILE "           .long  0\n\n\n");


        printf( LIBFILE "	.export _%sIndex\n",$DlmName);
        printf( LIBFILE "	.export _%sEntry\n",$DlmName);


        printf( OUTFILE "	.import _start \n");

        foreach $_ (@ParseFunc){
	        printf( OUTFILE "	.import  $_\n");
        }
       printf( LIBFILE "
	   ;*==========================================*
	   ;*    P U B L I C     F U N C T I O N S     *
	   ;*==========================================*\n");
       printf( LIBFILE "\t\t.seg \".text\",text                       \n\n\n");


       printf( OUTFILE "
	   ;*==========================================*
	   ;*    P U B L I C     F U N C T I O N S     *
	   ;*==========================================*\n");

       printf( OUTFILE "\t\t.seg \".jump_table\",text                       \n\n\n");


printf( OUTFILE "
           ;_start Entry
	   ldr      %r8,=_start            ;Load the function address and Add the size of the DLM header
	   ldr      %r10,[%r9,-4]          ;Load the address of the DLM
	   add      %r8,%r8,%r10           ;Added to get the real address of the function
	   bx       %r8	    	           ;Branch and exchange to thumb mode
       	   .ltorg	    	           ;Put the literals here
       \n");

       # Count Number of arguments
       $x = 0;

       foreach $_ (@Public)
       {

          @NumberOfpsik = m/,/g;
          $psik = $#NumberOfpsik + 1;

          $void =  m/\(+\s*[A-Za-z0-9_]+\s*\)/g;

          if(!$void)
          {
            $psik++;
          }
          @NumberOfdot = m/\./g;
          $dot = $#NumberOfdot + 1;
          if($dot == 3)
          {
            $psik = $psik + 32;
          }

          $NumOfArgument[$x++] = $psik;
       }

       $x = 20;
       $j = 0;

       foreach $_ (@ParseFunc)
       {

printf( LIBFILE "
 ;* --------------------------------------------------------------------------
 ;*
 ;* FUNCTION NAME: $_.
 ;*
 ;* DESCRIPTION:   ?????.
 ;*
 ;* RETURN:        ?????.
 ;*
 ;* NOTES:         Build by the Pre processor.
 ;*
 ;* -------------------------------------------------------------------------
                       .global $_ \n");


printf( LIBFILE "$_:                             \n");
printf( LIBFILE "          swi      7                        \n");
printf( LIBFILE "          .short   #0                       \n");
printf( LIBFILE "          .long    DlmUserID                \n");
printf( LIBFILE "          .long    _%sEntry                 \n",$DlmName);
printf( LIBFILE "          .short   #$x                      \n");
printf( LIBFILE "          .short   #%d                      \n",$NumOfArgument[$j] <= 4 ? 0 : ($NumOfArgument[$j] - 4)*4);
printf( LIBFILE "          .long    BaseDlmIndex             \n");
printf( LIBFILE "          .long    _%sIndex                 \n",$DlmName);
$j++;

printf( OUTFILE "\n	   ;$_ Entry \n");
printf( OUTFILE "	   ldr      %r8,=$_                ;Load the function address and Add the size of the DLM header\n");
printf( OUTFILE "	   ldr      %r10,[%r9,-4]          ;Load the address of the DLM\n");
printf( OUTFILE "	   add      %r8,%r8,%r10           ;Added to get the real address of the function\n");
printf( OUTFILE "	   bx       %r8	    	           ;Branch and exchange to thumb mode\n");
printf( OUTFILE "	   .ltorg	    	           ;Put the literals here\n");
        $x+=20;

       }

printf( OUTFILE "\n           ;main function for the start up code\n");
printf( OUTFILE "	      .global main \n");
printf( OUTFILE "main:                     \n");
printf( OUTFILE "             stmfd    %%sp!,{%%lr}         ; store the LR  \n");
printf( OUTFILE "             bl       DlmMain          ; Call DlmMain  \n");
printf( OUTFILE "             ldmfd    %%sp!,{%%lr}         ; restore the LR\n");
printf( OUTFILE "             bx      %%lr               ; return to NOS \n");


}

sub BuildDlmIncFile{
 print LIBFILE "****************************************************************************\n";
 print LIBFILE "* FILE NAME:   DlmLib.src                                                  \n*";
 print LIBFILE "* Module name: DLMLIB                                                      \n*";
 print LIBFILE "* PROGRAMMER:  Lipman PreProcessor.                                        \n*";
 print LIBFILE "* DESCRIPTION: DLM Dynamic Link Lib.                                       \n*";
 print LIBFILE "* REVISION:    $DlmVer.                                                    \n*";
 print LIBFILE "* DATE:        $Fulldate.                                                  \n*";
 print LIBFILE "* NOTE:        This file is build by Lipman PreProcessor.                  *\n";
 print LIBFILE "*              it is not recommended to edit it by hand.                   *\n";
 print LIBFILE "****************************************************************************";
 print LIBFILE "\n\n
	   * ======================================= *
	   *         I N T R O D U C T I O N         *
	   * ======================================= *
	   * This is the DLM lib module \n
	   *==========================================*
	   *     A S S E M B L Y   O P T I O N S      *
	   *==========================================*
	OPT   CASE

	   *==========================================*
	   *             I N C L U D E S              *
	   *==========================================*

	   *==========================================*
	   *             S Y M B O L S                *
	   *==========================================*

	   *==========================================*
	   *     E X T E R N A L   D E F I N I O N    *
	   *==========================================*
						       \n";


 print OUTFILE "****************************************************************************\n";
 print OUTFILE "* FILE NAME:   DlmTable.src                                                 *\n";
 print OUTFILE "* Module name: DlmTable                                                     *\n";
 print OUTFILE "* PROGRAMMER:  Lipman PreProcessor.                                        *\n";
 print OUTFILE "* DESCRIPTION: DLM Dynamic Link Table.                                     *\n";
 print OUTFILE "* REVISION:    $DlmVer.                                             *\n";
 print OUTFILE "* DATE:        $Fulldate.                                             *\n";
 print OUTFILE "* NOTE:        This file is build by Lipman PreProcessor.                  *\n";
 print OUTFILE "*              it is not recommended to edit it by hand.                   *\n";
 print OUTFILE "****************************************************************************\n\n";
 print OUTFILE "
	   * ======================================= *
	   *         I N T R O D U C T I O N         *
	   * ======================================= *
	   * This is the DLM Jump Table module \n
	   *==========================================*
	   *     A S S E M B L Y   O P T I O N S      *
	   *==========================================*

	OPT   CASE

	   *==========================================*
	   *             I N C L U D E S              *
	   *==========================================*

	   *==========================================*
	   *             S Y M B O L S                *
	   *==========================================*

	   *==========================================*
	   *     E X T E R N A L   D E F I N I O N    *
	   *==========================================*
						       \n";


}
sub Write2DlmIncFile{
        printf( LIBFILE "	XREF _BaseDlmIndex\n");
        printf( LIBFILE "	XDEF _%sIndex\n",$DlmName);
        printf( LIBFILE "	XDEF _%sEntry\n",$DlmName);



        printf( LIBFILE "\n\n\tSECTION    dlms_index\n\n\n");
        printf( LIBFILE "%sIndex  DC.L  %s\n",$DlmName,$DlmName);
        printf( LIBFILE "\n\n\tSECTION  dlms_entry\n\n\n");

        printf( LIBFILE "%sEntry  DC.B  \'%s\'",$DlmName,$DlmName);
        for($i = length($DlmName) ; $i < 8 ; $i++)
        {
            printf( LIBFILE ",\$0");
        }
        printf( LIBFILE ",\'%s\'\n\n\n",$DlmVer);


        printf( LIBFILE "\tSECTION  code                                   \n\n\n");

        foreach $_ (@ParseFunc){
	        printf( LIBFILE "	XDEF \_$_\n");
	        printf( OUTFILE "	XREF \_$_\n");
        }
        printf( OUTFILE "	XDEF \_main\n");
        printf( OUTFILE "	XREF \_DlmMain\n");
        printf( LIBFILE "
	   *==========================================*
	   *    P U B L I C     F U N C T I O N S     *
	   *==========================================*\n");

        printf( OUTFILE "
	   *==========================================*
	   *    P U B L I C     F U N C T I O N S     *
	   *==========================================*\n");

        printf( OUTFILE "\t\tSECTION  jump_table                                   \n\n\n");
       # Count Number of arguments
       $x = 0;
       foreach $_ (@Public)
       {

          @NumberOfpsik = m/,/g;
          $psik = $#NumberOfpsik + 1;

          $void =  m/\(+\s*[A-Za-z0-9_]+\s*\)/g;

          if(!$void)
          {
            $psik++;
          }
          $NumOfArgument[$x++] = $psik;
       }

       $x = 0;
       $j = 0;
       foreach $_ (@ParseFunc)
       {
printf( LIBFILE "
 * --------------------------------------------------------------------------
 *
 * FUNCTION NAME: _$_.
 *
 * DESCRIPTION:   ?????.
 *
 * RETURN:        ?????.
 *
 * NOTES:         Build by the Pre processor.
 *
 * -------------------------------------------------------------------------
");
printf( LIBFILE "\_$_:                             \n");
printf( LIBFILE "          * Replace Static Base pointer *    \n");

printf( LIBFILE "          TRAP     #7                        \n");
printf( LIBFILE "          DC.L     _DlmUserID                \n");
printf( LIBFILE "          DC.L     _%sEntry                  \n",$DlmName);
printf( LIBFILE "          DC.S     #$x                       \n");
printf( LIBFILE "          DC.S     #%d                       \n",$NumOfArgument[$j++]);
printf( LIBFILE "          DC.L     _BaseDlmIndex             \n");
printf( LIBFILE "          DC.L     _%sIndex                  \n",$DlmName);


printf( OUTFILE "	   JMP         \_$_(pc)	    	      \n");

       $x+=4;
       }

printf( OUTFILE "\n           *main function for the init code\n");
printf( OUTFILE "_main:                                                 \n");
printf( OUTFILE "             JSR      _DlmMain          *Call DlmMain  \n");
printf( OUTFILE "             RTS                                       \n");

       print LIBFILE "END";
       print OUTFILE "END";




}
sub CheckReturnValueExist{
   my($function) = @_;
   $_ = $function;
   @token = split;

   $_ = $token[0];
   m/[A-Za-z0-9_]+\s*\(/g;
   if($&)
   {
     $IsSog = m/\(/;

   }
   if($IsSog){
     print "$token[0] Not func \n";
     return 0;
   }
   return 1;
}