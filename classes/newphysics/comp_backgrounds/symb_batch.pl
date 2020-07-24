#!/usr/bin/perl -w
# v 0.1 created by Sherstnev A., date: 29/12/2002
# v 0.2 created by Sherstnev A., date: 21/01/2003
# v 0.5 created by Sherstnev A., date: 27/06/2003

use Getopt::Long;
use IPC::Open3;
use File::Copy;

help() unless (@ARGV or -e "process.dat" );

GetOptions("h", \$opt_h,
           "n=s",
	   "d=s",
	   "recovery",\$recovery,
	   "relink",\$relink,
	   "show=s",\$show,
	   "help",\$longhelp);
	  
my $filedat="process.dat";

  if($opt_h or $longhelp){help(); exit(0);}

  $comphep_dir = "/A/lns183/cdat/daf9/mccann/software/src/comphep-4.4.0";
  $s_comphep   = "$comphep_dir"."/s_comphep";
  
  if(!-e $s_comphep)
  {print "
First of all you have to create the s_comphep program in the directory
$comphep_dir. 
Launch ./configure and make commands in the directory to do that.\n";
    exit(0);
  }

  if(-e "symb_batch.log"){rename("symb_batch.log","symb_batch.log_old")}

  if(defined $recovery)
  {
    recovery();
    rename_results();
    exit(0);
  }
  if(defined $relink){relink();exit(0);}
  if(defined $show and $show eq "status"){show_status();exit(0);}
  
  $filedat=$opt_n if (defined $opt_n);

   $rslts="results";
   opendir(RST,$rslts);
   $empty=0;
   while($f=readdir(RST))
   { $empty=1 unless($f eq "Makefile" or $f eq "n_comphep" or $f eq "." or $f eq "..");}
   if((-e $rslts) and ($empty==1))
   {
     $i=1;
     $tmp_rslts="$rslts"."_old_1";
     while(-e $tmp_rslts)
     {
       $i++;
       $tmp_rslts="$rslts"."_old"."_$i";
     }
     rename($rslts,$tmp_rslts);
     mkdir($rslts,0755);
     copy("$tmp_rslts/Makefile", "$rslts/Makefile");
     copy("$tmp_rslts/n_comphep","$rslts/n_comphep");
     chmod(0744,"$rslts/n_comphep");
   }

   data_analysis();
   form_safefile();
   if(defined $show and $show eq "diagrams"){show_diagrams();}
   else                                     {run();}
  rename_results();

exit(0);

sub rename_results{

   if(defined $opt_d)
   {
     if(-e $opt_d)
     {
       $i=1;
       $old_dir=$opt_d."_old_1";
       while(-e $old_dir)
       {
         $i++;
         $old_dir=$old_dir."_old"."_$i";
       }
       rename($opt_d,$old_dir);
     }
     rename($rslts,$opt_d);
     rename($tmp_rslts,$rslts) if(defined $tmp_rslts);
   }
}


sub data_analysis{
  
  open(DAT,"<$filedat") or die "\n*** there are no $filedat file";
  while($res=<DAT>)
  {
    next if( $res=~/^#/ or $res=~/^\s+/ );
    if ($res=~/[:]/)
    {
      $s=$';
      chomp $s;
      if ($`=~/(\s*)model(\s*)number(\s*)/)   {$mdlnum =$s;}
      if ($`=~/(\s*)process(\s*)/)            {$process=$s;}
      if ($`=~/(\s*)energy(\s*)\(GeV\)(\s*)/) {$energy =$s;}
      if ($`=~/(\s*)exclude(\s*)diagrams(\s*)with(\s*)/)     {$exclde=$s;}
      if ($`=~/(\s*)keep(\s*)diagrams(\s*)with(\s*)/)     {$keep=$s;}
      if ($`=~/(\s*)make(\s*)symbolic(\s*)calculations(\s*)\(yes\/no\)/){$smake =$s;}
      if ($`=~/(\s*)make(\s*)n_comphep(\s*)generator(\s*)\(yes\/no\)/)  {$nmake =$s;}
    }
  }
  close DAT;

  if(!defined $mdlnum) {print "Error: model number is not defined\n;";exit(0);}
  if(!defined $process){print "Error: process is not entered\n;";exit(0);}
  if(!defined $energy) {print "Error: energy is not defined\n;";exit(0);}
}


sub form_safefile{
  $sffl="safe_tmp";
  if(-e $sffl)
  {
    print "Warning! File $sffl exists, it is renamed to $sffl._old\n";
    rename($sffl,$sffl."_old");
  }
  open(SAF,"+>$sffl") or die "I can not open safe_open file ($!)";
  print SAF "#Model $mdlnum\n";
  print SAF "#nIn 0\n";
  print SAF "#nOut 0\n";
  print SAF "#Process $process\n";
  print SAF "#SQRT(S) $energy\n";
  print SAF "#Remove_Virtual $exclde\n";
  print SAF "#Keep_Virtual $keep\n";
  print SAF "#nSubproc(ampl) 0\n";
  print SAF "#nSubproc(squared) 0\n";
  print SAF "#ConservationLaw 1\n";
  print SAF "#Nc==inf  0\n";
  print SAF "#ExitCode 0\n";
  close SAF;
  rename($sffl,"tmp/safe");
}


sub help{
 print
" The symb_batch.pl usage:\n
$0 [-h] [--help]
$0 [-d dir] [-n file] [-show diagrams]
$0 [-d dir] -recovery
$0 [-d dir] -relink
$0 -show status

-h    - print this message.
-help - print a long help message.

-d dir  - use directory dir instead of results directory
          for storing of n_comphep.
-n filename - use data from the filename file instead process.dat.
-recovery - recovery script work in case of s_comphep
            crash during symbolic calculation of squared diagrams.
-relink   - with this option the script relink n_comphep.exe. 
            It is necessary in case of changes in userFun.c
-show
      diagrams - launch s_comphep in graphic mode for feynman
                 diagrams review and analysis.
      status   - show current status of the script work 
                 (in not implemented yet).\n";

if (defined $longhelp)
{
  print 
"*******************************************************************
  The main goal of the script is to launch the symbolic part of the
  CompHEP generator in non-GUI mode. This allows the reuse of the script,
  avoiding typing mistakes, and also should facilitate using farms.
  
  First you have to install CompHEP on your system (e.g. in a directory
  {your_home_dir}/comphep_4.2.0).
  
  A default data file for the script is process.dat. Detailed instructions
  and explanations for the changes are contained in the file itself. 
  After that you can launch the script with no options. 
  The final result is a n_comphep.exe program in the directory `results'.
  
  You can set another names for the data file or the results directory
  by the -n and -d options respectively. If the directory results
  is not empty before the script launching, it is renamed to results_old_0
  and the script creates a new results directory.
  
  Some extra script options:
  -recovery If the s_comphep program crashed during calculations of
            squared diagrams, you can launch the script with the
	    recovery option and s_comphep resumes the computation
	    from the last calculated diagram.
	    
  -relink  If you have changed userFun.c file one should relink the n_comphep
           program. You can launch the script with the
	   relink option and s_comphep relink the n_comphep program and
	   save all details of the relinking to the symb_batch.log file.
  
  -show diagrams - this option is applied if you'd like to exclude
                   by hand some diagrams from all those set by 
		   the program. The script launches s_comphep in GUI
		   mode in the feynman diagrams menu. After reviewing
		   the diagrams you have to finish the GUI session and
		   the script will go on.
		   
  -show status - show the current working status of the script.
                 (i.e. what the script is doing now, how many diagrams
	          have been calculated already, etc.) IS NOT IMPLEMENTED YET!\n";}
 }


sub run{
  my $argv="}}";
  if($smake =~ /yes/)
  {
    $argv=$argv."]}]}";
    if ($nmake =~ /yes/){$argv=$argv."}}]}"};
  }
  $argv=$argv."9";
  $err=system("./comphep","-blind",$argv);
  print "err = $err\n" if $err;
  print "\n*** n_comphep creation details have been written to symb_batch.log (make stdout/stderr)\n"
}


sub show_diagrams{

  $err=system("./comphep","-blind","}}9");
  print "err = $err\n" if $err;
  $err=system("./comphep");
  print "err = $err\n" if $err;

  my $argv="";
  if($smake =~ /yes/)
  {
    $argv=$argv."]}]}";
    if ($nmake =~ /yes/){$argv=$argv."}]]]}]}"};
  }
  $argv=$argv."9";
  $err=system("./comphep","-blind",$argv);
  print "err = $err\n" if $err;
}


sub recovery{
  my $rslts="results";
  open(SAFE,"<tmp/safe") or die "I can not open tmp/safe file";
  while($str=<SAFE>)
  {
    next unless $str =~ /#ExitCode\s+(\d)\s+/;
    if($1!=6) {print "recovery is imposible!\n";exit(0);}
  }
  close(SAFE);
  opendir(RST,$rslts)or die "I can not open $rslts dir ($!)";;
  $empty=0;
  while($f=readdir(RST))
  {
    $empty=1 unless ($f eq "Makefile" or $f eq "." or $f eq "..");
  }

  if($empty){ $argv="]}}]]]}]}9";}
  else      { $argv=" ]}]]]}]}9";}
  $err=system("./comphep","-blind",$argv);
  print "err = $err\n" if $err;
  print "\n*** n_comphep creation details have been written to symb_batch.log (make stdout/stderr)\n"
}


sub relink{
  $opt_d="results" unless defined $opt_d;
  if(!-d $opt_d) {print "I can not open $opt_d dir ($!)";exit(0);}
  
  open(FOUT,">symb_batch.log") or die "I can not open symb_batch.log file";
  open(OUT,"make -C $opt_d blindlink 2>&1 |") or die " Can not run program: $!\n";
  while($str=<OUT>) {print FOUT $str;}
  close(FOUT);

  print "*** Error during link of n_comphep! err = $err.\n" if $err;
  print "\n*** n_comphep creation details have been written to symb_batch.log (make stdout/stderr)\n"
}


sub show_status{
   my $argv="";
   $err=system("./comphep","-status",$argv);
}
