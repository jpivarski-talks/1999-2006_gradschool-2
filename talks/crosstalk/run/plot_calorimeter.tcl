default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/plot_calorimeter.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

module sel DBModule
database in /nfs/cleo3/database/data14/db event startrun beginrun endrun
database read_collection pass2 radlep

proc sel ../build_SunOS/shlib/PlotCalorimeter

proc sel HistogramViewerProc

go
