default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/findlambdas_tau$env(USER_DB).rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnPass2.tcl

module sel DBModule
database in /nfs/cleo3/database/data$env(USER_DB)/db event startrun beginrun endrun
database read_collection pass2 tau

proc sel ../build_SunOS/shlib/FindLambdas

go
