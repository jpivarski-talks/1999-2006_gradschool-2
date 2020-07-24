#!/usr/local/bin/perl

%f = {};
$f{1} = ["/cdat/linux/tem/kme/lc/data/slac/simd24204_FMCSD.root"];
$f{2} = ["/cdat/linux/tem/kme/lc/data/slac/simd24229_FMCSD.root"];
$f{3} = ["/cdat/linux/tem/rcg24/proc_slac/simd24329_FMCSD.root"];
$f{4} = ["/cdat/linux/tem/kme/lc/data/slac/simd24227_FMCSD.root"];
$f{5} = ["/cdat/linux/tem/rcg24/proc_slac/simd24327_FMCSD.root"];
$f{6} = ["/cdat/linux/tem/kme/lc/data/slac/simd24211_FMCSD.root"];
$f{7} = ["/cdat/linux/tem/kme/lc/data/slac/simd24275_FMCSD.root",
	 "/cdat/linux/tem/rcg24/proc_slac/simd24370_FMCSD.root"];
$f{8} = ["/cdat/linux/tem/kme/lc/data/slac/simd24270_FMCSD.root",
	 "/cdat/linux/tem/rcg24/proc_slac/simd24311_FMCSD.root"];
$f{9} = ["/cdat/linux/tem/rcg24/proc_slac/simd24304_FMCSD.root",
	 "/cdat/linux/tem/kme/lc/data/slac/simd24248_FMCSD.root",
	 "/cdat/linux/tem/kme/lc/data/slac/simd24261_FMCSD.root",
	 "/cdat/linux/tem/rcg24/proc_slac/simd24348_FMCSD.root"];
$f{10} = ["/cdat/linux/tem/rcg24/proc_slac/simd24364_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24314_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24214_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24324_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24224_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24241_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24217_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24317_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24361_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24225_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24325_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24260_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24313_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24213_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24366_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24266_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24375_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24367_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24267_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24273_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24363_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24223_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24312_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24244_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24212_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24365_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24323_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24302_FMCSD.root"];
$f{11} = ["/cdat/linux/tem/rcg24/proc_slac/simd24374_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24274_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24216_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24316_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24322_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24242_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24276_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24222_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24243_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24240_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24201_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24239_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24228_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24377_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24277_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24369_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24269_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24362_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24376_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24306_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24301_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24238_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24206_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24330_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24230_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24308_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24341_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24209_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24247_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24309_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24210_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24207_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24347_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24205_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24307_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24328_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24310_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24208_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24203_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24258_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24305_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24360_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24342_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24303_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24368_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24268_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24344_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24343_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24226_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24326_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24340_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24373_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24332_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24232_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24333_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24233_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24338_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24335_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24235_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24339_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24278_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24378_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24336_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24236_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24358_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24271_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24331_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24231_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24255_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24371_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24252_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24372_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24272_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24237_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24256_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24337_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24354_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24352_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24353_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24334_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24234_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24359_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24357_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24356_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24355_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24351_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24350_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24349_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24346_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24345_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24321_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24320_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24319_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24318_FMCSD.root",
	  "/cdat/linux/tem/rcg24/proc_slac/simd24315_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24265_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24264_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24263_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24262_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24259_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24257_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24254_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24253_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24251_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24250_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24249_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24246_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24245_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24221_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24220_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24219_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24218_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24215_FMCSD.root",
	  "/cdat/linux/tem/kme/lc/data/slac/simd24202_FMCSD.root"];

foreach $n (1..11) {
    open(FILE, "> anewer_sm$n.tcl");
    print FILE "module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_sm$n.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

";
    foreach $file (@{ $f{$n} }) {
	if ($file =~ /simd242([0-9]{2})_FMCSD/) {
	    $number = -$1;
	}
	elsif ($file =~ /simd243([0-9]{2})_FMCSD/) {
	    $number = $1;
	}
	print FILE "file in $file
param LCDExampleProc mcfile $number
go

";
    }
    print FILE "hbook terminate
exit
";
}
