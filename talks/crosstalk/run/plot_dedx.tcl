default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/plot_dedx.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnNewPass2.tcl

module sel DBModule
database in /nfs/cleo3/database/data14/db event startrun beginrun endrun
database read_collection pass2 hadron

prod sel TrkmanProd
prod sel TrkmanSelectionProd

proc sel ../build_SunOS/shlib/PlotDedx

go
