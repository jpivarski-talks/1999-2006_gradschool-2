#!/usr/local/bin/perl

%f = ();
$f{"R9p2c1+c1-"} = "/cdat/dafa/kme/lc/gen/data/R9p2c1+c1-_FMCSD.root";
$f{"L9p2c1+c1-.0"} = "/cdat/dafa/kme/lc/gen/data/L9p2c1+c1-.0_FMCSD.root";
$f{"L9p2c1+c1-.1"} = "/cdat/dafa/kme/lc/gen/data/L9p2c1+c1-.1_FMCSD.root";
$f{"R9p2c20c30"} = "/cdat/dafa/kme/lc/gen/data/R9p2c20c30_FMCSD.root";
$f{"L9p2c20c30"} = "/cdat/dafa/kme/lc/gen/data/L9p2c20c30_FMCSD.root";
$f{"R9p2c10c30"} = "/cdat/dafa/kme/lc/gen/data/R9p2c10c30_FMCSD.root";
$f{"L9p2c10c30"} = "/cdat/dafa/kme/lc/gen/data/L9p2c10c30_FMCSD.root";
$f{"R9p2c1+c2-"} = "/cdat/dafa/kme/lc/gen/data/R9p2c1+c2-_FMCSD.root";
$f{"R9p2c1+c2-.0"} = "/cdat/dafa/kme/lc/gen/data/R9p2c1+c2-.0_FMCSD.root";
$f{"L9p2c1+c2-"} = "/cdat/dafa/kme/lc/gen/data/L9p2c1+c2-_FMCSD.root";
$f{"L9p2c1+c2-.0"} = "/cdat/dafa/kme/lc/gen/data/L9p2c1+c2-.0_FMCSD.root";
$f{"simd24301"} = "/cdat/linux/tem/rcg24/proc_slac/simd24301_FMCSD.root";
$f{"simd24302"} = "/cdat/linux/tem/rcg24/proc_slac/simd24302_FMCSD.root";
$f{"simd24303"} = "/cdat/linux/tem/rcg24/proc_slac/simd24303_FMCSD.root";
$f{"simd24304"} = "/cdat/linux/tem/rcg24/proc_slac/simd24304_FMCSD.root";
$f{"simd24305"} = "/cdat/linux/tem/rcg24/proc_slac/simd24305_FMCSD.root";
$f{"simd24306"} = "/cdat/linux/tem/rcg24/proc_slac/simd24306_FMCSD.root";
$f{"simd24307"} = "/cdat/linux/tem/rcg24/proc_slac/simd24307_FMCSD.root";
$f{"simd24308"} = "/cdat/linux/tem/rcg24/proc_slac/simd24308_FMCSD.root";
$f{"simd24309"} = "/cdat/linux/tem/rcg24/proc_slac/simd24309_FMCSD.root";
$f{"simd24310"} = "/cdat/linux/tem/rcg24/proc_slac/simd24310_FMCSD.root";
$f{"simd24311"} = "/cdat/linux/tem/rcg24/proc_slac/simd24311_FMCSD.root";
$f{"simd24312"} = "/cdat/linux/tem/rcg24/proc_slac/simd24312_FMCSD.root";
$f{"simd24313"} = "/cdat/linux/tem/rcg24/proc_slac/simd24313_FMCSD.root";
$f{"simd24314"} = "/cdat/linux/tem/rcg24/proc_slac/simd24314_FMCSD.root";
$f{"simd24315"} = "/cdat/linux/tem/rcg24/proc_slac/simd24315_FMCSD.root";
$f{"simd24316"} = "/cdat/linux/tem/rcg24/proc_slac/simd24316_FMCSD.root";
$f{"simd24317"} = "/cdat/linux/tem/rcg24/proc_slac/simd24317_FMCSD.root";
$f{"simd24318"} = "/cdat/linux/tem/rcg24/proc_slac/simd24318_FMCSD.root";
$f{"simd24319"} = "/cdat/linux/tem/rcg24/proc_slac/simd24319_FMCSD.root";
$f{"simd24320"} = "/cdat/linux/tem/rcg24/proc_slac/simd24320_FMCSD.root";
$f{"simd24321"} = "/cdat/linux/tem/rcg24/proc_slac/simd24321_FMCSD.root";
$f{"simd24322"} = "/cdat/linux/tem/rcg24/proc_slac/simd24322_FMCSD.root";
$f{"simd24323"} = "/cdat/linux/tem/rcg24/proc_slac/simd24323_FMCSD.root";
$f{"simd24324"} = "/cdat/linux/tem/rcg24/proc_slac/simd24324_FMCSD.root";
$f{"simd24325"} = "/cdat/linux/tem/rcg24/proc_slac/simd24325_FMCSD.root";
$f{"simd24326"} = "/cdat/linux/tem/rcg24/proc_slac/simd24326_FMCSD.root";
$f{"simd24327"} = "/cdat/linux/tem/rcg24/proc_slac/simd24327_FMCSD.root";
$f{"simd24328"} = "/cdat/linux/tem/rcg24/proc_slac/simd24328_FMCSD.root";
$f{"simd24329"} = "/cdat/linux/tem/rcg24/proc_slac/simd24329_FMCSD.root";
$f{"simd24330"} = "/cdat/linux/tem/rcg24/proc_slac/simd24330_FMCSD.root";
$f{"simd24331"} = "/cdat/linux/tem/rcg24/proc_slac/simd24331_FMCSD.root";
$f{"simd24332"} = "/cdat/linux/tem/rcg24/proc_slac/simd24332_FMCSD.root";
$f{"simd24333"} = "/cdat/linux/tem/rcg24/proc_slac/simd24333_FMCSD.root";
$f{"simd24334"} = "/cdat/linux/tem/rcg24/proc_slac/simd24334_FMCSD.root";
$f{"simd24335"} = "/cdat/linux/tem/rcg24/proc_slac/simd24335_FMCSD.root";
$f{"simd24336"} = "/cdat/linux/tem/rcg24/proc_slac/simd24336_FMCSD.root";
$f{"simd24337"} = "/cdat/linux/tem/rcg24/proc_slac/simd24337_FMCSD.root";
$f{"simd24338"} = "/cdat/linux/tem/rcg24/proc_slac/simd24338_FMCSD.root";
$f{"simd24339"} = "/cdat/linux/tem/rcg24/proc_slac/simd24339_FMCSD.root";
$f{"simd24340"} = "/cdat/linux/tem/rcg24/proc_slac/simd24340_FMCSD.root";
$f{"simd24341"} = "/cdat/linux/tem/rcg24/proc_slac/simd24341_FMCSD.root";
$f{"simd24342"} = "/cdat/linux/tem/rcg24/proc_slac/simd24342_FMCSD.root";
$f{"simd24343"} = "/cdat/linux/tem/rcg24/proc_slac/simd24343_FMCSD.root";
$f{"simd24344"} = "/cdat/linux/tem/rcg24/proc_slac/simd24344_FMCSD.root";
$f{"simd24345"} = "/cdat/linux/tem/rcg24/proc_slac/simd24345_FMCSD.root";
$f{"simd24346"} = "/cdat/linux/tem/rcg24/proc_slac/simd24346_FMCSD.root";
$f{"simd24347"} = "/cdat/linux/tem/rcg24/proc_slac/simd24347_FMCSD.root";
$f{"simd24348"} = "/cdat/linux/tem/rcg24/proc_slac/simd24348_FMCSD.root";
$f{"simd24349"} = "/cdat/linux/tem/rcg24/proc_slac/simd24349_FMCSD.root";
$f{"simd24350"} = "/cdat/linux/tem/rcg24/proc_slac/simd24350_FMCSD.root";
$f{"simd24351"} = "/cdat/linux/tem/rcg24/proc_slac/simd24351_FMCSD.root";
$f{"simd24352"} = "/cdat/linux/tem/rcg24/proc_slac/simd24352_FMCSD.root";
$f{"simd24353"} = "/cdat/linux/tem/rcg24/proc_slac/simd24353_FMCSD.root";
$f{"simd24354"} = "/cdat/linux/tem/rcg24/proc_slac/simd24354_FMCSD.root";
$f{"simd24355"} = "/cdat/linux/tem/rcg24/proc_slac/simd24355_FMCSD.root";
$f{"simd24356"} = "/cdat/linux/tem/rcg24/proc_slac/simd24356_FMCSD.root";
$f{"simd24357"} = "/cdat/linux/tem/rcg24/proc_slac/simd24357_FMCSD.root";
$f{"simd24358"} = "/cdat/linux/tem/rcg24/proc_slac/simd24358_FMCSD.root";
$f{"simd24359"} = "/cdat/linux/tem/rcg24/proc_slac/simd24359_FMCSD.root";
$f{"simd24360"} = "/cdat/linux/tem/rcg24/proc_slac/simd24360_FMCSD.root";
$f{"simd24361"} = "/cdat/linux/tem/rcg24/proc_slac/simd24361_FMCSD.root";
$f{"simd24362"} = "/cdat/linux/tem/rcg24/proc_slac/simd24362_FMCSD.root";
$f{"simd24363"} = "/cdat/linux/tem/rcg24/proc_slac/simd24363_FMCSD.root";
$f{"simd24364"} = "/cdat/linux/tem/rcg24/proc_slac/simd24364_FMCSD.root";
$f{"simd24365"} = "/cdat/linux/tem/rcg24/proc_slac/simd24365_FMCSD.root";
$f{"simd24366"} = "/cdat/linux/tem/rcg24/proc_slac/simd24366_FMCSD.root";
$f{"simd24367"} = "/cdat/linux/tem/rcg24/proc_slac/simd24367_FMCSD.root";
$f{"simd24368"} = "/cdat/linux/tem/rcg24/proc_slac/simd24368_FMCSD.root";
$f{"simd24369"} = "/cdat/linux/tem/rcg24/proc_slac/simd24369_FMCSD.root";
$f{"simd24370"} = "/cdat/linux/tem/rcg24/proc_slac/simd24370_FMCSD.root";
$f{"simd24371"} = "/cdat/linux/tem/rcg24/proc_slac/simd24371_FMCSD.root";
$f{"simd24372"} = "/cdat/linux/tem/rcg24/proc_slac/simd24372_FMCSD.root";
$f{"simd24373"} = "/cdat/linux/tem/rcg24/proc_slac/simd24373_FMCSD.root";
$f{"simd24374"} = "/cdat/linux/tem/rcg24/proc_slac/simd24374_FMCSD.root";
$f{"simd24375"} = "/cdat/linux/tem/rcg24/proc_slac/simd24375_FMCSD.root";
$f{"simd24376"} = "/cdat/linux/tem/rcg24/proc_slac/simd24376_FMCSD.root";
$f{"simd24377"} = "/cdat/linux/tem/rcg24/proc_slac/simd24377_FMCSD.root";
$f{"simd24378"} = "/cdat/linux/tem/rcg24/proc_slac/simd24378_FMCSD.root";
$f{"simd24201"} = "/cdat/linux/tem/kme/lc/data/slac/simd24201_FMCSD.root";
$f{"simd24202"} = "/cdat/linux/tem/kme/lc/data/slac/simd24202_FMCSD.root";
$f{"simd24203"} = "/cdat/linux/tem/kme/lc/data/slac/simd24203_FMCSD.root";
$f{"simd24204"} = "/cdat/linux/tem/kme/lc/data/slac/simd24204_FMCSD.root";
$f{"simd24205"} = "/cdat/linux/tem/kme/lc/data/slac/simd24205_FMCSD.root";
$f{"simd24206"} = "/cdat/linux/tem/kme/lc/data/slac/simd24206_FMCSD.root";
$f{"simd24207"} = "/cdat/linux/tem/kme/lc/data/slac/simd24207_FMCSD.root";
$f{"simd24208"} = "/cdat/linux/tem/kme/lc/data/slac/simd24208_FMCSD.root";
$f{"simd24209"} = "/cdat/linux/tem/kme/lc/data/slac/simd24209_FMCSD.root";
$f{"simd24210"} = "/cdat/linux/tem/kme/lc/data/slac/simd24210_FMCSD.root";
$f{"simd24211"} = "/cdat/linux/tem/kme/lc/data/slac/simd24211_FMCSD.root";
$f{"simd24212"} = "/cdat/linux/tem/kme/lc/data/slac/simd24212_FMCSD.root";
$f{"simd24213"} = "/cdat/linux/tem/kme/lc/data/slac/simd24213_FMCSD.root";
$f{"simd24214"} = "/cdat/linux/tem/kme/lc/data/slac/simd24214_FMCSD.root";
$f{"simd24215"} = "/cdat/linux/tem/kme/lc/data/slac/simd24215_FMCSD.root";
$f{"simd24216"} = "/cdat/linux/tem/kme/lc/data/slac/simd24216_FMCSD.root";
$f{"simd24217"} = "/cdat/linux/tem/kme/lc/data/slac/simd24217_FMCSD.root";
$f{"simd24218"} = "/cdat/linux/tem/kme/lc/data/slac/simd24218_FMCSD.root";
$f{"simd24219"} = "/cdat/linux/tem/kme/lc/data/slac/simd24219_FMCSD.root";
$f{"simd24220"} = "/cdat/linux/tem/kme/lc/data/slac/simd24220_FMCSD.root";
$f{"simd24221"} = "/cdat/linux/tem/kme/lc/data/slac/simd24221_FMCSD.root";
$f{"simd24222"} = "/cdat/linux/tem/kme/lc/data/slac/simd24222_FMCSD.root";
$f{"simd24223"} = "/cdat/linux/tem/kme/lc/data/slac/simd24223_FMCSD.root";
$f{"simd24224"} = "/cdat/linux/tem/kme/lc/data/slac/simd24224_FMCSD.root";
$f{"simd24225"} = "/cdat/linux/tem/kme/lc/data/slac/simd24225_FMCSD.root";
$f{"simd24226"} = "/cdat/linux/tem/kme/lc/data/slac/simd24226_FMCSD.root";
$f{"simd24227"} = "/cdat/linux/tem/kme/lc/data/slac/simd24227_FMCSD.root";
$f{"simd24228"} = "/cdat/linux/tem/kme/lc/data/slac/simd24228_FMCSD.root";
$f{"simd24229"} = "/cdat/linux/tem/kme/lc/data/slac/simd24229_FMCSD.root";
$f{"simd24230"} = "/cdat/linux/tem/kme/lc/data/slac/simd24230_FMCSD.root";
$f{"simd24231"} = "/cdat/linux/tem/kme/lc/data/slac/simd24231_FMCSD.root";
$f{"simd24232"} = "/cdat/linux/tem/kme/lc/data/slac/simd24232_FMCSD.root";
$f{"simd24233"} = "/cdat/linux/tem/kme/lc/data/slac/simd24233_FMCSD.root";
$f{"simd24234"} = "/cdat/linux/tem/kme/lc/data/slac/simd24234_FMCSD.root";
$f{"simd24235"} = "/cdat/linux/tem/kme/lc/data/slac/simd24235_FMCSD.root";
$f{"simd24236"} = "/cdat/linux/tem/kme/lc/data/slac/simd24236_FMCSD.root";
$f{"simd24237"} = "/cdat/linux/tem/kme/lc/data/slac/simd24237_FMCSD.root";
$f{"simd24238"} = "/cdat/linux/tem/kme/lc/data/slac/simd24238_FMCSD.root";
$f{"simd24239"} = "/cdat/linux/tem/kme/lc/data/slac/simd24239_FMCSD.root";
$f{"simd24240"} = "/cdat/linux/tem/kme/lc/data/slac/simd24240_FMCSD.root";
$f{"simd24241"} = "/cdat/linux/tem/kme/lc/data/slac/simd24241_FMCSD.root";
$f{"simd24242"} = "/cdat/linux/tem/kme/lc/data/slac/simd24242_FMCSD.root";
$f{"simd24243"} = "/cdat/linux/tem/kme/lc/data/slac/simd24243_FMCSD.root";
$f{"simd24244"} = "/cdat/linux/tem/kme/lc/data/slac/simd24244_FMCSD.root";
$f{"simd24245"} = "/cdat/linux/tem/kme/lc/data/slac/simd24245_FMCSD.root";
$f{"simd24246"} = "/cdat/linux/tem/kme/lc/data/slac/simd24246_FMCSD.root";
$f{"simd24247"} = "/cdat/linux/tem/kme/lc/data/slac/simd24247_FMCSD.root";
$f{"simd24248"} = "/cdat/linux/tem/kme/lc/data/slac/simd24248_FMCSD.root";
$f{"simd24249"} = "/cdat/linux/tem/kme/lc/data/slac/simd24249_FMCSD.root";
$f{"simd24250"} = "/cdat/linux/tem/kme/lc/data/slac/simd24250_FMCSD.root";
$f{"simd24251"} = "/cdat/linux/tem/kme/lc/data/slac/simd24251_FMCSD.root";
$f{"simd24252"} = "/cdat/linux/tem/kme/lc/data/slac/simd24252_FMCSD.root";
$f{"simd24253"} = "/cdat/linux/tem/kme/lc/data/slac/simd24253_FMCSD.root";
$f{"simd24254"} = "/cdat/linux/tem/kme/lc/data/slac/simd24254_FMCSD.root";
$f{"simd24255"} = "/cdat/linux/tem/kme/lc/data/slac/simd24255_FMCSD.root";
$f{"simd24256"} = "/cdat/linux/tem/kme/lc/data/slac/simd24256_FMCSD.root";
$f{"simd24257"} = "/cdat/linux/tem/kme/lc/data/slac/simd24257_FMCSD.root";
$f{"simd24258"} = "/cdat/linux/tem/kme/lc/data/slac/simd24258_FMCSD.root";
$f{"simd24259"} = "/cdat/linux/tem/kme/lc/data/slac/simd24259_FMCSD.root";
$f{"simd24260"} = "/cdat/linux/tem/kme/lc/data/slac/simd24260_FMCSD.root";
$f{"simd24261"} = "/cdat/linux/tem/kme/lc/data/slac/simd24261_FMCSD.root";
$f{"simd24262"} = "/cdat/linux/tem/kme/lc/data/slac/simd24262_FMCSD.root";
$f{"simd24263"} = "/cdat/linux/tem/kme/lc/data/slac/simd24263_FMCSD.root";
$f{"simd24264"} = "/cdat/linux/tem/kme/lc/data/slac/simd24264_FMCSD.root";
$f{"simd24265"} = "/cdat/linux/tem/kme/lc/data/slac/simd24265_FMCSD.root";
$f{"simd24266"} = "/cdat/linux/tem/kme/lc/data/slac/simd24266_FMCSD.root";
$f{"simd24267"} = "/cdat/linux/tem/kme/lc/data/slac/simd24267_FMCSD.root";
$f{"simd24268"} = "/cdat/linux/tem/kme/lc/data/slac/simd24268_FMCSD.root";
$f{"simd24269"} = "/cdat/linux/tem/kme/lc/data/slac/simd24269_FMCSD.root";
$f{"simd24270"} = "/cdat/linux/tem/kme/lc/data/slac/simd24270_FMCSD.root";
$f{"simd24271"} = "/cdat/linux/tem/kme/lc/data/slac/simd24271_FMCSD.root";
$f{"simd24272"} = "/cdat/linux/tem/kme/lc/data/slac/simd24272_FMCSD.root";
$f{"simd24273"} = "/cdat/linux/tem/kme/lc/data/slac/simd24273_FMCSD.root";
$f{"simd24274"} = "/cdat/linux/tem/kme/lc/data/slac/simd24274_FMCSD.root";
$f{"simd24275"} = "/cdat/linux/tem/kme/lc/data/slac/simd24275_FMCSD.root";
$f{"simd24276"} = "/cdat/linux/tem/kme/lc/data/slac/simd24276_FMCSD.root";
$f{"simd24277"} = "/cdat/linux/tem/kme/lc/data/slac/simd24277_FMCSD.root";
$f{"simd24278"} = "/cdat/linux/tem/kme/lc/data/slac/simd24278_FMCSD.root";

foreach $n (keys %f) {
    $mcfile = 0;
    if ($n =~ /simd242([0-9]+)/) {
	$mcfile = -$1;
    }
    elsif ($n =~ /simd243([0-9]+)/) {
	$mcfile = $1;
    }

    open(HEY, "> rd_$n.scr");
    print HEY "#\$ -l arch=glinux
#\$ -o /cdat/tem/mccann/redo_$n.log
#\$ -S /bin/bash
#\$ -j y

cd /home/mccann/lcdroot/run_anew/
. /nfs/cleo3/scripts/cleo3defs

c3rel Mar04_04_MC
export LCDROOT=/cdat/tem/cdj/lcdroot/v01_00_00/LCDRootApps
export LD_LIBRARY_PATH=\${LCDROOT}/lib:\${LD_LIBRARY_PATH}
export C3_SHLIB=/cdat/tem/cdj/lcdroot/v01_00_00/shlib:\${C3_SHLIB}
export USER_NAME=$n
export USER_FILE=$f{$n}
export USER_MCFILE=$mcfile

suez -f redo_everything.tcl
rm -f core

exit
";
}

