default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/view_tau.rzn
hbook init

run_file $env(C3_SCRIPTS)/runOnNewPass2.tcl

module sel DBModule
database in /nfs/cleo3/database/data21/db event startrun beginrun endrun
database read_collection pass2 tau

run_file $env(C3_SCRIPTS)/viewPass2.tcl

prod sel EventTypeProd
proc sel EventTypeFilterProc
param EventTypeFilterProc TauLoBgd true

go
