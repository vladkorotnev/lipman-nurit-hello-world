# ****************************************************************************
# * FILE NAME:   expand.pl
# * MODULE NAME: expand
# * PROGRAMMER:  Oren Sokoler
# * DESCRIPTION: Expand macros on input file 
# * REVISION:    01.00 26/01/01.
# ****************************************************************************

unless (open(MACROS,$ARGV[0])) {
     print STDERR "Can't open $ARGV[0]: $!\n";
     exit(1);
}

unless (open(INFILE,$ARGV[1])) {
     print STDERR "Can't open $ARGV[1]: $!\n";
     close(MACROS);           
     exit(1);
}

unless (open(OUTFILE,">$ARGV[2]")) {
     print STDERR "Can't open $ARGV[2]: $!\n";
     close(MACROS);           
     close(INFILE);
     exit(1);
}

@InFile = <INFILE>;
close INFILE;

#
# Read all macro definitions
#
while ( $line = <MACROS> ) {
  if ( $line =~ /\s*(\S+)\s*=\s*(\S+)/ ) {
    $hash{$1}=$2;
  }
}
close MACROS;

$InFile = join(/ /,@InFile);

#
# Expand all macros
#
while ( ($Key,$Value) = each (%hash) ) {
  $InFile =~ s/\$\($Key\)/$Value/g;
}

print OUTFILE $InFile;

close OUTFILE;
