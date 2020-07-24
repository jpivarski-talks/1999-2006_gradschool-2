#!/usr/bin/perl -w 
##!/usr/products/perl/IRIX-6/v5_006_1a/bin/perl -w
# v. 0.1 created by L.Dudko (dudko@lev.art.ru)
# v. 0.2  19.02.2002
# v. 0.3  06.03.2002
# v. 0.5.1  23.06.2002 run in PBS and LSF systems

use Getopt::Long;
use File::Path;
use File::Copy;


help() unless (@ARGV or !-e "results/batch.dat" );

# Take the input options
GetOptions( "h", \$opt_h, "l", \$opt_l, "d=s", 
           "run:s", \$run,
	   "proc=s", \$proc,
           "add_ses2bat:s" => \$ses2bat,
	   "help",\$longhelp,
	   "nses=i",\$insession,
	   "ginv",\$ginv,
	   "pbs:s",\$pbs,
	   "lsf:s",\$lsf,
	   "lcs",\$lcs,
	   "combine",\$opt_combine,
	   "nocombine",\$opt_nocombine);
	  
my $fileses='session.dat';
my $filebat='batch.dat';
my $Nproc = 0;
my $Nproc_current = 0;
my $Nsession = 1;

list_cs(@ARGV) if defined $lcs;

if($opt_h or $longhelp){help(); exit(0);} # Print help message

# Use "results" or another defined (-d dir) directory for the  
# numerical calculations. The n_comphep file must be there.
     $opt_d="results" unless defined $opt_d;
     chdir $opt_d or die "There are no $opt_d dir: $!\n";

if(!-e "./n_comphep"){
   print "
   First of all you have to create the n_comphep generator
   in directory $opt_d. Use comphep symbolic part to do that.";
            exit(0);}

if(-e "LOCK"){ unlink "LOCK";}
   
#Print the list of available processes in the
#n_comphep generator in the directory [dir] (or results).   
     list() if defined $opt_l;
       
# Parameters from the exist session.dat file will keep
#in new batch.dat file. The current session number will
#set from the exist session.dat file or to unit if it is absent.
     old_ses($fileses) if -s $fileses ;

#Create batch.dat file in [dir] for the all available processes
#if it is absent.
     create_batch_dat() if !-s $filebat;

# With the option --add_ses2bat [file] 
#Include the parameters from session.dat (or [file])
#to exist batch.dat file.
     if (defined $ses2bat)
       {old_ses($ses2bat) unless ($ses2bat eq $fileses or $ses2bat eq "")}

   combine() if defined $opt_combine;
      
#print $run , $proc,"\n";
run() if defined $run;

exit(0);

sub old_ses { 
  local $/="\n#";
  open(SES,"<$_[0]") or die "there are no $_[0] in $opt_d ($!)";
  @old_session = <SES>;

# Take the session number from the session.dat file
   if ($_[0] eq $fileses){$old_session[2] =~/\s(\d+)\s/g;
                          $Nsession=$1;}
  close SES;

# Add parameters from session.dat (or --add_session2bat [file]) file
# to batch.dat file
  if(defined $ses2bat and -e $filebat and ($_[0] eq $ses2bat or $ses2bat eq ""))
    {
     open(BATCH, "+<$filebat") or die "Can't open $filebat for read/write: $!\n";
      local $/="++++++++++++++\n";
      my $tmp = "";
      while (<BATCH>)
       {@blocks = split(/\n#/);
        $blocks[1] =~/\s(\d+)\s/g;
        $Nproc_current = $1;

         if( $old_session[1] eq  $blocks[1]."\n#")
	     {$tmp .= join("",@old_session)."++++++++++++++\n";
	     print "          The exist $ses2bat file is included to 
	      batch.dat file for the process $Nproc_current.\n"
	      }
	     else
	      {$tmp .= $_ }
	}
       seek(BATCH,0,0);
       print BATCH $tmp;
       truncate (BATCH,tell(BATCH));
      close BATCH;
     }
}

 sub create_batch_dat  {  
     open(BATCH, "+>$filebat") or die "Can't open $filebat for read/write: $!\n";
     system ("./n_comphep", "-blind", "}}9}") ;
             die "Can't run n_comphep:$@" if $@;
      my $string="}";
     print "You can calculate the processes as follow:\n";
      $/="\n#";
     for (;;)
     {   
      open(SES,"<$fileses") or die "there are no session.dat in $opt_d ($!)";
       @block = <SES>;
       $block[1] =~/\s(\d+)\s/g;
       $Nproc_current = $1;
       if($Nproc_current > $Nproc+1){$string=$string.")";goto COMP;}
       last if $Nproc_current == $Nproc;
	
         $Nproc=$Nproc_current;
          if( $old_session[1] and $old_session[1] eq  $block[1])
	     {print BATCH @old_session;
	      print "     The exist session.dat file parameters are included to new
	    batch.dat file for the process $Nproc_current.\n"
	      }
	     else
	     {print BATCH @block }
         print BATCH "++++++++++++++\n";
         $block[1]=~ s/(\n\#)/\n/ ;
	 print $block[1];
         close(SES);
	 $string=$string."]";
COMP:	 system ("./n_comphep", "-blind", "$string.'}9}'");
	  die "Can't run n_comphep:$@" if $@;
      }
     print "File results/batch.dat is created.\n";
     close BATCH;
    } 
 
 sub help  
 {print 
"Usage: \n 
$0 [-hl] [--help]
$0 [-d dir] [--add_ses2bat [file]] 
            [-run [vegas,max,evnt,cleanstat,cleangrid,clean]] [-proc 1,5-10,24] [-nses n] 

-l - print the list of available processes
-h - print this message
-d dir - use directory dir instead of results
         for this batch calculations
--add_ses2bat [file]  - add parameters from exist session.dat 
			file (or [file])  to batch.dat file in [dir]
-run [vegas,max,evnt] - run vegas or maximum search or event generation,
                        run all steps by default with -run
-run [cleanstat,cleangrid,clean] - clean statistic or grid or clean both 
-proc n1,n2-n3,n4...  - run only these processes
-nses n - n is the number of the first session, it is calculated
                         automatically by default 
-ginv                 - gauge invariance ON (See CompHEP manual);			
-pbs [pbs prefix] (e.g. qsub)  - run calculations in parallel with PBS batch system
-lsf [lsf prefix] (e.g. bsub -I)  - run calculations in parallel with LSF batch system
-nocombine            - do not combine automatically the results of
                       PBS (LSF) calculations from the temporary subdirectories
		       you can do that later with -combine option
-combine              - combine the results of previouse calculations from the
                       temporary PBS directories (you need it only if you used
		       -nocombine option before) 		       
-lcs  LIST            - option to sum the results from prt_* files.
                        LIST is the list of prt files (e.g. prt_* or prt_1 prt_2 ...)
--help                - print the long help message \n";

if (defined $longhelp)
{print 
" 

1. Introduction.

      Numerical batch mode is useful to calculate the large number of 
  subprocesses and perform the large scale calculations even the
  calculations on MC farms (PBS and LSF systems).
  
    This mode can help user after the symbolic calculations and preparing
  the n_comphep.exe numerical generator in directory 'results'.


2. Configuration of the batch calculations.


    The first step is to configure the parameters (PDFs, cuts, regularisations etc.)
  use the GUI interface to do that 
  
  cd results
  ./n_comphep
  
       Set the required parameters for the first process, check the vegas menu
   and step back.
  
   run batch script to create the configuration file (results/batch.dat) with 
   the same parameters for all of the subprocesses as you inserted for the 
   first one. From the CompHEP Working Directory (CWDIR):
   
   ./num_batch.pl
   
   By default the results directory will use by this script to find and run 
   the generator n_comphep.exe. If one need to use another directory
   add option -d new_dir for all of the commands where need a reference
   to n_comphep.exe generator e.g.:
   
   ./num_batch.pl -d new_dir 
   
   if you want to change some of the parameters for the particular subprocess
   you can edit the results/batch.dat file or use GUI:
   choose the required subprocess in GUI, change the parameters, 
   check the vegas menu and step back to the main menu (need to save the parameters
   to session.dat file). After that insert new parameters for this subprocess
   to the results/batch.dat file (add session.dat to batch.dat) by command:
   
   ./num_batch.pl --add_ses2bat
   
   
3.   How to start the calculations.


      After you have finished the configuration of your calculations you are
   ready to start calculations:

   ./num_batch.pl  -run
   
   this command will calculate cross sections, maximums and generate events
   for all of the subprocesses. To calculate cross sections only run:
   
   ./num_batch.pl  -run vegas
   
     There are some more instructions with option -run:
   ./num_batch.pl  -run max     #to calculate maximums
   ./num_batch.pl  -run evnt    #to generate events, use it only after
                                #the vegas and max calculations

    ./num_batch.pl  -run cleanstat   #to clean the vegas statistic
    ./num_batch.pl  -run cleangrid   #to clean the vegas grid
    ./num_batch.pl  -run clean   #to clean the vegas grid and statistic


       One can add option -proc n1,n2-n6  to calculate some of the 
   subprocesses:
   
   ./num_batch.pl  -run -proc 1,3-5,7,2
   
    or
       
   ./num_batch.pl -d new_dir -run vegas -proc 1,3-5,7,2
   

   By default the number of the new session will be the next after the
   last protocol number you have in the results directory (or new_dir with -d)
   User can change it by option -nses e.g.:
   
   ./num_batch.pl -d new_dir -run vegas -proc 1,3-5,7,2 -nses 1
   
   The protocol files will start from the prt_1 despite the existing prt_
   files in your dir (it will append it)
   

4.   How to use LSF or PBS systems and how to calculate the subprocesses
    in parallel.
    

   All of the commands above provide the consecutive calculations of subprocesses.
   But if you have more CPUs or want to run in BATCH systems (LSF or PBS)
   you can use the parallel calculations of subprocesses.
   There are two options -lsf and -pbs which are doing almost the same things
   but with different (LSF or PBS) systems (different default prefixes and options)
   
   ./num_batch.pl  -run vegas -pbs
   
   will create temporary subdirectories for each of the subprocess
   and run the PBS batch job for each of subprocess with PBS command:
   qsub -I run.sh
   
   or for LSF system 
   ./num_batch.pl  -run vegas -lsf
    will submit 
    bsub -I run.sh
    
    these temporary subdirectories will be automatically removed and the results
    are saved in usual places. 
    
        In case your PBS or LSF system do not provide you interactive
    option ( -I ) one should add the -nocombine option.
   
   ./num_batch.pl  -run vegas -lsf  -nocombine
   
      This command will submit the LSF jobs and exit immediately.
    Therefore after all of the submitted jobs will finished user need to
    combine results from the temporary subdirectories by additional
    command:
    
    ./num_batch.pl  -combine
    
   
    If user want to change the default prefix to submit the jobs it is possible
    to run something like:

   ./num_batch.pl  -run vegas -lsf 'bsub -I -q large -N -B -o log.out'
   
   
   In case user do not want to use BATCH system but want to calculate
   the subprocesses in parallel use the empty prefix to overwrite the default one:
   
   ./num_batch.pl  -run vegas -lsf ' '
   
     Will start calculations of the subprocesses in parallel and combine the
    results at the end.


5.   How to present the results.

   There is the special option -lcs to summarize the cross sections and errors
   from the protocol files for different subprocesses. The example of the command:
   
   ./num_batch.pl  -lcs  prt_1 prt_2 prt_5
   
   or

   ./num_batch.pl  -lcs  results/prt_*
   
   

   
\n";}
 }  
 sub list
 {  
  open(BATCH, "<$filebat") or die "Can't open $filebat for read: $!\n";
  local $/="++++++++++++++\n";

  print "List of available subprocesses:\n";
  while (<BATCH>)
   {
    @blocks=split(/\n#/,$_,3) ;
    print "$blocks[1] \n";
   }
  close(BATCH);
 }
 
 sub run
{ 

# Fill the steps to run from input options
  if($run eq ""){$run_p{"vegas"}=1;$run_p{"max"}=1;$run_p{"evnt"}=1;}
  foreach (split(/,/,$run)) { $run_p{$_}=1;}

my $nginv="";
$nginv="}}{" if defined $ginv;

my $batch_options='';
my $comphep='';
$comphep="COMPHEP=".$ENV{"COMPHEP"}." \n export COMPHEP\n" if defined $ENV{"COMPHEP"};
print "$comphep\n";
# Set the PBS (LSF) run script

 if(defined $pbs or defined $lsf )
   {
    my ($vegas,$max,$event)=('','',''); 
       $vegas = '#' if !defined $run_p{"vegas"}; 
       $max   = '#' if !defined $run_p{"max"};
       $event = '#' if !defined $run_p{"evnt"};

       $count = 0;
     if (defined $pbs)
        {
        $batch_options = qq~
#PBS -I
##PBS -l nodes=1:farm
~;
       $pbs eq '' ? $b_prefix = "qsub" : $b_prefix = $pbs;
	} 
       elsif (defined $lsf)
        {
         $batch_options = qq~
#LSF -I
~;
       $lsf eq '' ? $b_prefix = "bsub" : $b_prefix = $lsf;
        }

	
     $shell_scrpt=qq~#!/bin/sh
$batch_options
$comphep
${vegas}./n_comphep -blind ]]]]]$nginv]]]]}]]]}9}
${max}./n_comphep -blind ]]]]]$nginv]]]]}]]]]]]]}]]]}9}
${event}./n_comphep -blind ]]]]]$nginv]]]]}]]]]]]]}]]}9}
~;

  }


  local $/="++++++++++++++\n";
  open(BATCH, "+<$filebat") or die "Can't open $filebat for read: $!\n";
  my @batch = <BATCH>;
  close BATCH;

# Set the processes to run from the input options
  if (defined $proc) 
    {@proc_n = proc_nc(); 
     print "There are only ", $#batch+1," processes, not $proc_n[$#proc_n].\n"
         unless $proc_n[$#proc_n] <= $#batch+1;
    } else {@proc_n= 1 .. $#batch+1;}

while(-e "prt_".$Nsession and ! defined $insession){$Nsession++};
$Nsession = $insession if defined $insession;

# Run numerical part of CompHEP
for ($i=0; $i<=$#proc_n;$i++)
  { last if $proc_n[$i] > $#batch+1;
     print "The current session is number $Nsession\n";
     @blocks = split(/\n#/,$batch[$proc_n[$i]-1]);
     $blocks[2] =~s/\d+/$Nsession/g;
     print "$blocks[1] \n";
     foreach (@blocks)
       { $_="\n#".$_ unless $_ eq "\n" or $_ eq "";}
    open(SES,"+>$fileses") or die "Can't create session.dat in $opt_d ($!)";
    print SES @blocks;
    close SES;

# Create subdirectories for each subprocess, setup there the session.dat
# and run run.sh in PBS or LSF batch system 
 if(defined $pbs or defined $lsf){
 my $pid;
    
		mkdir 'res_'.$Nsession,0777;
		chdir 'res_'.$Nsession;
		system("ln -s  ../n_comphep ./n_comphep");
		system("ln -s  ../n_comphep.exe ./n_comphep.exe") if -s "../n_comphep.exe";
		system("mv  ../session.dat .");


		open(FH,">run.sh");
		print FH $shell_scrpt;
		close(FH);
		chmod 0755, 'run.sh';
		$pid = fork();
		if($pid == 0)
		{
			exec("$b_prefix ./run.sh");
			exit 0;
		}
		else
		{
			$count++;
		}
		chdir "../";
                $Nsession++;


            }
 else
           {
    if (defined $run_p{"vegas"})
       {$status=system ("./n_comphep", "-blind", "]]]]]$nginv]]]]}]]]}9}") ;
	open(PRT,"<prt_$Nsession") or die "Can't open prt_$Nsession in $opt_d ($!)";
	$/="\n"; while (<PRT>){print if /\s\#IT|\s\<\s\>/}; print "\n";close PRT;}

    $status=system ("./n_comphep", "-blind", "]]]]]$nginv]]]]}]]]]]]]}]]]}9}") 
           if defined $run_p{"max"};

    $status=system ("./n_comphep", "-blind", "]]]]]$nginv]]]]}]]]]]]]}]]}9}") 
           if defined $run_p{"evnt"};

    $status=system ("./n_comphep", "-blind", "]]]]]]]]]}]]]]]]}}9}") 
           if defined $run_p{"cleangrid"};

    $status=system ("./n_comphep", "-blind", "]]]]]]]]]}]]]]]}}9}") 
           if defined $run_p{"cleanstat"};

    $status=system ("./n_comphep", "-blind", "]]]]]]]]]}]]]]]}}]}}9}") 
           if defined $run_p{"clean"};

    print "Something wrong in calculations: $status \n" if $status != 0 ;
    open(SES,"<$fileses") or die "Can't read session.dat in $opt_d ($!)";
     local undef $/;
    $batch[$proc_n[$i]-1] = <SES> if $status == 0 ;
    $batch[$proc_n[$i]-1] .= "++++++++++++++\n" if $status == 0 ;
    close SES;
    $Nsession++;
    open(BATCH, "+>$filebat") or die "Can't open $filebat for read/write: $!\n";
    print BATCH @batch;
    close BATCH;
          }
   }

# Wait until all of the subprocess to be calculated
    wait;
    
# include the new session.dat parameters to batch.dat, move prt_ and events_
#files to main results dir and remove temporary res_ directories    
    combine() if !defined $opt_nocombine;
   
exit(0);
 

}

 sub proc_nc 
{  $proc =~ s/(\d+)-(\d+)/join(',',$1 .. $2)/eg ;
 my @list = sort {$a <=> $b} split(/,/,$proc);
my %temp= (); @proc_n = grep { !$temp{$_}++ } @list;
return (@proc_n);
}

sub combine
{

my @list = <res_*>;
foreach $resdir (@list)
      {
        $resdir=~/res\_(\d+)/g;
	my $resn=$1;
	my @keepfiles;
	$ses2bat="$resdir/$fileses";
        old_ses("$resdir/$fileses") if -e "$resdir/$fileses" ;
	if (-e "$resdir/prt_$resn"){$keepfiles[0]="$resdir/prt_$resn"; 
	                          move("$resdir/prt_$resn","prt_$resn");}
	if (-e "$resdir/events_$resn.txt"){$keepfiles[1]="$resdir/events_$resn.txt"; 
	                          move("$resdir/events_$resn.txt","events_$resn.txt");}
        eval { rmtree("$resdir")};
        if ($@) {print "Can not delete directory $resdir, reason:$@";}
	else{print "The $resdir directory is removed, @keepfiles files are kept\n";}
      }
}
 
sub list_cs
{
#print "$lcs \n @ARGV \n" ;
my $tot=0;
my $tote=0;
  my ($cs,$cse);
print "\n   Cross section [pb]  Error %    nCall   chi**2\n\n";
foreach (@ARGV)
{
  open(PRT,"<$_") or die "Can't open $_ ($!)";
  $/="\n"; 
  while (<PRT>)
   {
      print if /\#Subprocess/ ;
#      print if /\s\#IT/ and $_=$ARGV[0]; 
      if(/\s\<\s\>\s+(\d+\.\d+E[+-]\d+)\s+(\d+\.\d+E[+-]\d+)\s+\d+\s+.+/)
        {
         $cs = $1;
         $cse =$2*$1/100;
#	 print "$1  $2\n";
         s/\s\<\s\>//;
	 print "$_ ";
        }
    }
#    print "$cs  +\/-  $cse \n";
    close(PRT);
    $tot=$tot+$cs;
    $tote=$tote+$cse*$cse;
}
   my $totep= sqrt($tote) *100/$tot;

    printf "\n Total CS [pb] = %1.4e   +\/- %1.2e ( %1.2e %% )\n\n",$tot,sqrt($tote),$totep;

     exit(0);  
}


 
