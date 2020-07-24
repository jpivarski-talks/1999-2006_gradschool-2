module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file mcmatch.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/Np2c10c30_FMCSD.root

prod sel ../build_Linux2/shlib/LCDPerfectTrackClusterMatchingProd
proc sel ../build_Linux2/shlib/LCDTwoLeptonsProc
proc sel HistogramViewerProc

# proc sel SpExtractLCDMcPartProc
# proc sel SpExtractLCDTrackProc
# proc sel SpExtractLCDClusterProc
# proc sel SpViewerProc

go
