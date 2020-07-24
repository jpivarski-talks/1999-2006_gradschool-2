default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/test_view3.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl

prod sel DBEventHeaderProd

module sel DBModule
database in /nfs/objy/data25/db event startrun beginrun endrun
database read_collection rawdata mupair

run_file $env(C3_SCRIPTS)/viewTrackFitter.tcl

go
