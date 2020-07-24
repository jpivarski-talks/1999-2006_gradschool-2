module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_chi12left.rzn
hbook init

source_format sel RootLCDEventSourceFormat
source create pdschain
file add pdschain /cdat/dafa/kme/lc/gen/data/L9p2c1+c2-_FMCSD.root
file add pdschain /cdat/dafa/kme/lc/gen/data/L9p2c1+c2-.0_FMCSD.root

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

go
