module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/stuff.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/tem/cdj/lcdroot/data/pythialcc2_fastMC.root
proc sel ../build_Linux/shlib/LCDExampleProc

# proc sel SpExtractLCDMcPartProc
# proc sel SpExtractLCDTrackProc
# proc sel SpExtractLCDClusterProc
# proc sel SpViewerProc

go
