module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_sm9.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

file in /cdat/linux/tem/rcg24/proc_slac/simd24304_FMCSD.root
param LCDExampleProc mcfile 04
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24248_FMCSD.root
param LCDExampleProc mcfile -48
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24261_FMCSD.root
param LCDExampleProc mcfile -61
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24348_FMCSD.root
param LCDExampleProc mcfile 48
go

hbook terminate
exit
