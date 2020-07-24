module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_sm3.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

file in /cdat/linux/tem/rcg24/proc_slac/simd24329_FMCSD.root
param LCDExampleProc mcfile 29
go

hbook terminate
exit