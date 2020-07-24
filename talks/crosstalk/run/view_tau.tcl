default prompt off
exception continueEventLoop on

module select LoadGeantModule
module select LoadHbookModule
module sel HbookHistogramModule
hbook file ../rzn/view_tau.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/CcRunGain.tcl
run_file $env(C3_SCRIPTS)/BeamSpot.tcl

source_format sel AsciiSourceFormat
sink_format sel AsciiSinkFormat
prod sel MutrReconProd
prod sel MuConsProd
run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
prod sel DBRunHeaderProd

source_format sel BinarySourceFormat
file in /cdat/sol191/disk1/cleo3/data/r114141.bin event beginrun startrun endrun

prod sel TrkmanProd
prod sel TrkmanSelectionProd

proc sel ../build_SunOS/shlib/FindTaus

prod sel CesrBeamEnergyProd
prod sel TrackShowerMatchingProd
prod sel EventPropertiesProd
prod sel EventTypeProd
proc sel EventTypeFilterProc
param EventTypeFilterProc Tau1vN true

run_file $env(C3_SCRIPTS)/viewTrackFitter.tcl

go
