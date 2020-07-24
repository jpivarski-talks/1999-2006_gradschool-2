module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_sm7.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

file in /cdat/linux/tem/kme/lc/data/slac/simd24275_FMCSD.root
param LCDExampleProc mcfile -75
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24370_FMCSD.root
param LCDExampleProc mcfile 70
go

hbook terminate
exit
