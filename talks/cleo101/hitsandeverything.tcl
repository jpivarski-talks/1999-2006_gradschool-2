# We don't like it asking us questions
default prompt off

# Get raw events so we can look at hits
module sel EventStoreModule
eventstore in 20050316 daq all dataset data37

# All the things you need to process raw data
run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl

# We'll send events through MyFirstProc and the Event Display
proc sel MyFirstProc
run_file $env(C3_SCRIPTS)/view_command.tcl
view -display_only ShowerAttributes DRHits ZDHits SeedTrack KinePionFit DBEventHeader StandAloneGeom

# Ya, go!
go
