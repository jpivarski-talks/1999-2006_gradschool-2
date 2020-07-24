module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_chi2030left.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/L9p2c20c30_FMCSD.root

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

go
