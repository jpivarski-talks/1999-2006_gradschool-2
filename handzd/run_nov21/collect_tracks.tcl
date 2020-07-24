default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../pds/r$env(USER_RUN).rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl
exclude_constants_streams {drdriftdatav2 drt0card drt0channelv2 drt0crate drt0global drt0hvcard zddriftdata zdt0global zdt0crate drgarfield_distancecorrection}

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

run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
prod sel AZDGeomProd
prod sel ZDGeomProd
prod sel CalibratedZDHitProd
prod sel ZDDriftFunctionProd
prod sel ZDHitCorrectorProd
prod sel CesrBeamEnergyProd
prod sel TrackShowerMatchingProd

run_file $env(C3_SCRIPTS)/CcP2.tcl

param DetectorConfigurationProd Override true
param DetectorConfigurationProd UseZDnotSI true
param DRHitCorrectorProd ApplyEntranceAngleCorr true
param DRHitCorrectorProd ApplyStandardCorrections true
param KalmanProd HyposToFit pion
param KalmanProd ForceZDFittingWeight true
param KalmanProd ZDFittingWeight 1e-10

source_format sel BinarySourceFormat
file in /cdat/sol191/disk1/cleo-c/r$env(USER_RUN).bin event beginrun startrun endrun

sink_format sel PDSSinkFormat
file out ../pds/r$env(USER_RUN).pds {event{DBEventHeader DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality> FATable<TRSeedTrack> FATable<TRSeedTrackQuality> SeedTrackZDHitLattice PionFitZDHitLattice FATable<CalibratedZDHit> BunchDecision FATable<CollatedRawZDHit>}}

proc sel ../build_SunOS/shlib/TracskCollector
go
