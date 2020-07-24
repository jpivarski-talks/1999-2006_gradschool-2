module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file hist.rzn
hbook init

source_format sel RootLCDEventSourceFormat
file in /cdat/dafa/kme/lc/gen/data/L9p2c1+c1-.0_FMCSD.root

proc sel ../build_Linux/shlib/Clean

go 1000
exit

