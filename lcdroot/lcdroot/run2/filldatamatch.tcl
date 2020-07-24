module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file datamatch.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/Np2c10c30_FMCSD.root

prod sel ../build_Linux2/shlib/LCDTrackClusterMatchingProd
param LCDTrackClusterMatchingProd trackMatchDistCM 15.
param LCDTrackClusterMatchingProd clusterIsolateDistCM 15.
proc sel ../build_Linux2/shlib/LCDTwoLeptonsProc
proc sel HistogramViewerProc

# proc sel SpExtractLCDMcPartProc
# proc sel SpExtractLCDTrackProc
# proc sel SpExtractLCDClusterProc
# proc sel SpViewerProc

go
