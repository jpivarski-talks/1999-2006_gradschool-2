#!/usr/local/bin/perl

foreach $side ("l", "r") {
    foreach $n (1..78) {
	$number = sprintf("%02d", $n);
	if ($side eq "l") {
	    $file = "/cdat/linux/tem/kme/lc/data/slac/simd242$number\_FMCSD.root";
	}
	else {
	    $file = "/cdat/linux/tem/rcg24/proc_slac/simd243$number\_FMCSD.root";
	}
    
	open(HEY, "> sm_$side$number.run");
	print HEY "#\$ -l arch=glinux
#\$ -o /cdat/tem/mccann/sm_$side$number.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/lcdroot/run_anew/
. /nfs/cleo3/scripts/cleo3defs

c3rel Mar04_04_MC
export LCDROOT=/cdat/tem/cdj/lcdroot/v01_00_00/LCDRootApps
export LD_LIBRARY_PATH=\${LCDROOT}/lib:\${LD_LIBRARY_PATH}
export C3_SHLIB=/cdat/tem/cdj/lcdroot/v01_00_00/shlib:\${C3_SHLIB}
export USER_SIDE=$side
export USER_NUMBER=$number
export USER_FILE=$file

suez -f run_sm_anewer.tcl
rm -f core

exit
";
    }
}
