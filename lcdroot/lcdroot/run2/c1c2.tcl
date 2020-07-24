module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn2/c1c2.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/Np2c1+c2-_FMCSD.root

prod sel ../build_Linux2/shlib/LCDTrackClusterMatchingProd
param LCDTrackClusterMatchingProd trackMatchDistCM 0.2
param LCDTrackClusterMatchingProd clusterIsolateDistCM 5.
proc sel ../build_Linux2/shlib/LCProc

go
