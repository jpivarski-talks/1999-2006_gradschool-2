# We don't like it asking us questions
default prompt off

# Load a histogram manager.  This is the simple old-fashioned one.
module sel HbookHistogramModule
hbook file myhistograms.rzn
hbook init

# Get pass2'ed events (no hits, but much faster!)
module sel EventStoreModule
eventstore in 20050316 physics all

# Setup standard analysis + Event Display
setup_analysis
run_file $env(C3_SCRIPTS)/view_command.tcl

# Our very own processor
# proc sel MyThirdProc
# param MyThirdProc wantCosmics true
# proc sel MySecondProc

proc sel MyFourthProc

# Actually invoke the Event Display, and also cute histogram viewer
view -display_only Pass2
proc sel HistogramViewerProc

# No boring messages, and go go go!
report level ERROR
go
