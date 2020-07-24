default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/tmp.rzn
hbook init

# run_file $env(C3_SCRIPTS)/runOnNewPass2.tcl

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/CcRunGain.tcl
run_file $env(C3_SCRIPTS)/BeamSpot.tcl
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel TrackShowerMatchingProd
# prod sel EventPropertiesProd
# prod sel EventTypeProd
# proc sel EventTypeFilterProc
# param EventTypeFilterProc LoPtLoose true

prod sel TrkmanProd
prod sel TrkmanSelectionProd

source_format sel BinarySourceFormat
file in /cdat/sol191/disk1/cleo3/data/r114141.bin event beginrun startrun endrun

# module sel DBModule
# database in /nfs/objy/data16/db event startrun beginrun endrun
# database read_collection pass2 hadron

proc sel ../build_SunOS/shlib/FindTwoPhoton

run_file $env(C3_SCRIPTS)/viewTrackFitter.tcl
# run_file $env(C3_SCRIPTS)/viewPass2.tcl

go
