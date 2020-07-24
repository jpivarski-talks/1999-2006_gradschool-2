module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_right1.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/R9p2c1+c1-_FMCSD.root

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

go
