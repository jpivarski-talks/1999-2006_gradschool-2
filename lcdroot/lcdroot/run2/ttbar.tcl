module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn2/ttbar.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/ttbar_FMCSD.root

prod sel ../build_Linux2/shlib/LCDTrackClusterMatchingProd
param LCDTrackClusterMatchingProd trackMatchDistCM 0.2
param LCDTrackClusterMatchingProd clusterIsolateDistCM 5.
proc sel ../build_Linux2/shlib/LCProc

go
