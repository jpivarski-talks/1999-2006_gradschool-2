module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/anewer_sm10.rzn
hbook init

module sel RandomModule
random randomInit

source_format sel RootLCDEventSourceFormat

prod sel ../build_Linux/shlib/LCDTrackClusterMatchingProd
proc sel ../build_Linux/shlib/LCDExampleProc

file in /cdat/linux/tem/rcg24/proc_slac/simd24364_FMCSD.root
param LCDExampleProc mcfile 64
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24314_FMCSD.root
param LCDExampleProc mcfile 14
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24214_FMCSD.root
param LCDExampleProc mcfile -14
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24324_FMCSD.root
param LCDExampleProc mcfile 24
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24224_FMCSD.root
param LCDExampleProc mcfile -24
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24241_FMCSD.root
param LCDExampleProc mcfile -41
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24217_FMCSD.root
param LCDExampleProc mcfile -17
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24317_FMCSD.root
param LCDExampleProc mcfile 17
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24361_FMCSD.root
param LCDExampleProc mcfile 61
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24225_FMCSD.root
param LCDExampleProc mcfile -25
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24325_FMCSD.root
param LCDExampleProc mcfile 25
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24260_FMCSD.root
param LCDExampleProc mcfile -60
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24313_FMCSD.root
param LCDExampleProc mcfile 13
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24213_FMCSD.root
param LCDExampleProc mcfile -13
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24366_FMCSD.root
param LCDExampleProc mcfile 66
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24266_FMCSD.root
param LCDExampleProc mcfile -66
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24375_FMCSD.root
param LCDExampleProc mcfile 75
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24367_FMCSD.root
param LCDExampleProc mcfile 67
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24267_FMCSD.root
param LCDExampleProc mcfile -67
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24273_FMCSD.root
param LCDExampleProc mcfile -73
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24363_FMCSD.root
param LCDExampleProc mcfile 63
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24223_FMCSD.root
param LCDExampleProc mcfile -23
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24312_FMCSD.root
param LCDExampleProc mcfile 12
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24244_FMCSD.root
param LCDExampleProc mcfile -44
go

file in /cdat/linux/tem/kme/lc/data/slac/simd24212_FMCSD.root
param LCDExampleProc mcfile -12
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24365_FMCSD.root
param LCDExampleProc mcfile 65
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24323_FMCSD.root
param LCDExampleProc mcfile 23
go

file in /cdat/linux/tem/rcg24/proc_slac/simd24302_FMCSD.root
param LCDExampleProc mcfile 02
go

hbook terminate
exit
