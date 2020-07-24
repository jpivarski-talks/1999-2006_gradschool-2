default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file cuts.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/exclude_constants_streams.tcl

??? load your own constants ???

prod sel ChisqFitProd
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
prod desel KalmanProd

prod sel AZDGeomProd
prod sel ZDGeomProd
prod sel CalibratedZDHitProd
prod sel ZDDriftFunctionProd
prod sel ZDHitCorrectorProd
prod sel CesrBeamEnergyProd
prod sel DBEventHeaderProd

param DetectorConfigurationProd Override true
param DetectorConfigurationProd UseZDnotSI true
param DRHitCorrectorProd ApplyEntranceAngleCorr true
param DRHitCorrectorProd ApplyStandardCorrections true
param ChisqFitProd HyposToFit pion
# Deweight the ZD!
param ChisqFitProd ForceZDFittingWeight true
param ChisqFitProd ZDFittingWeight 1e-10

source_format sel BinarySourceFormat
file in /cdat/linux/tem/drcal/cleoc/run??????.bin event beginrun startrun endrun

sink_format sel PDSSinkFormat
file out ../pds/run$env(USER_RUN).pds {event{DBEventHeader DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> FATable<TRPionQuality> FATable<TRSeedTrack> FATable<TRSeedTrackQuality> SeedTrackZDHitLattice PionFitZDHitLattice FATable<CalibratedZDHit> BunchDecision FATable<CollatedRawZDHit>}}

proc sel ZDAlignmentBhabhaFilterProc
go
hbook terminate
exit
