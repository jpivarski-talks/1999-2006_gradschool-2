module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_sm4.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

file in /cdat/linux/tem/kme/lc/data/slac/simd24227_FMCSD.root
param LCDExampleProc mcfile -27
go

hbook terminate
exit
