module sel HbookHistogramModule
hbook file ../rzn/myst_pass1cuts.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl
exclude_constants_streams {drdriftdatav2 drt0card drt0channelv2 drt0crate drt0global drt0hvcard zddriftdata zdt0global zdt0crate drgarfield_distancecorrection zdweight2layerdriftentang zdgeomalignment}

source_format sel DRGarfield_DistanceCorrectionFSF
file in /cdat/lnssb2/disk2/dubrovin/cleo3/test_tuning/build/EA_COR/d130016.drgarfield_distancecorrection

source_format sel DRDriftDatav2FileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/DRDriftDatav2.drdriftdatav2
source_format sel DRt0cardFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/DRt0card.drt0card
source_format sel DRt0channelv2FileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/DRt0channelv2.drt0channelv2
source_format sel DRt0crateFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/DRt0crate.drt0crate
source_format sel DRt0globalFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/DRt0global.drt0global
source_format sel DRt0hvcardFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/DRt0hvcard.drt0hvcard

source_format sel ZDDriftDataFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDDriftDatav12.zddriftdata
source_format sel ZDt0globalFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDt0global_v3.zdt0global
source_format sel ZDt0crateFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDt0crate_v2.zdt0crate

source_format sel ZDWeight2LayerDriftEntAngFileSourceFormat
file in dropall.zdweight2layerdriftentang

source_format sel ZDGeomAlignmentFileSourceFormat
file in ../run/after_dan_before_crash.zdgeomalignment

run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
prod sel AZDGeomProd
prod sel ZDGeomProd
prod sel CalibratedZDHitProd
prod sel ZDDriftFunctionProd
prod sel ZDHitCorrectorProd
prod sel CesrBeamEnergyProd
prod sel TrackShowerMatchingProd

run_file $env(C3_SCRIPTS)/CcP2.tcl

param DetectorConfigurationProd Override true;
param DetectorConfigurationProd UseZDnotSI true;

param DRHitCorrectorProd DisableAllCorrections false
param DRHitCorrectorProd ApplyStandardCorrections true
param DRHitCorrectorProd ApplyEntranceAngleCorr true
param DRHitCorrectorProd ApplyPulseHeightCorr true
param DRHitCorrectorProd ApplySignalPropagationCorr true
param DRHitCorrectorProd ApplyTimeOfFlightCorr true

param ZDHitCorrectorProd DisableAllCorrections false
param ZDHitCorrectorProd ApplyStandardCorrections false
param ZDHitCorrectorProd ApplyEntranceAngleCorr false
param ZDHitCorrectorProd ApplyPulseHeightCorr false
param ZDHitCorrectorProd ApplySignalPropagationCorr true
param ZDHitCorrectorProd ApplyTimeOfFlightCorr true

param KalmanProd HyposToFit pion

source_format sel BinarySourceFormat
file in /cdat/sol191/disk1/cleo-c/r$env(USER_RUN).bin beginrun startrun event endrun

# prod sel EventPropertiesProd
# prod sel EventTypeProd
# proc sel EventTypeFilterProc
# param EventTypeFilterProc BhabhaTight true

prod sel DRElecMapProd
proc sel CcEventSelectProc
  param CcEventSelectProc BhabhaKeep          true
  param CcEventSelectProc GamGamKeep          true
  param CcEventSelectProc HadronKeep          true
  param CcEventSelectProc HadronLooseKeep     true
  param CcEventSelectProc MuPairKeep          true    
  param CcEventSelectProc BarrelBhabhaKeep    true
  param CcEventSelectProc BarrelGamGamKeep    true
  param CcEventSelectProc EndcapBhabhaKeep    true
  param CcEventSelectProc EndcapGamgamKeep    true
  param CcEventSelectProc BarrelRadBhaGamKeep true
  param CcEventSelectProc EndcapRadBhaGamKeep true
  param CcEventSelectProc EeZMissKeep         true
  param CcEventSelectProc MmZMissKeep         true
proc sel P1IntegrityMonProc
proc sel P1TrackMonProc

proc sel ../build_SunOS/shlib/Mysterious
proc sel HistogramViewerProc
go 210
hbook terminate
exit


