module sel LoadHbook4MModule
module sel ../build_SunOS/shlib/HbookHistogramModule
hbook file ../rzn/$env(USER_ALIGNMENT)_driftsign_drgood.rzn
hbook init

module sel CorbaModule
corba init
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge basegeometry zdweight2layerdriftentang zdweight2layertheta zdweight2layerphi zddaqcellidmap zdwirequality zdadc2charge zdadcpedestal zdt0card zdt0channel zdt0hvcard
source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc material
module sel RunStatisticsSourceModule
runstatistics in

source_format sel ZDDriftDataFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDDriftDatav12.zddriftdata
source_format sel ZDt0globalFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDt0global_v3.zdt0global
source_format sel ZDt0crateFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDt0crate_v2.zdt0crate

emptysource def zdalignment zdalignment

prod sel AZDGeomProd
prod sel ZDGeomProd
prod sel ZDDriftFunctionProd
prod sel MagFieldProd
prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel DetectorConfigurationProd
param DetectorConfigurationProd Override true;
param DetectorConfigurationProd UseZDnotSI true;
prod sel ZDHitCorrectorProd
param ZDHitCorrectorProd DisableAllCorrections false
param ZDHitCorrectorProd ApplyStandardCorrections false
param ZDHitCorrectorProd ApplyEntranceAngleCorr false
param ZDHitCorrectorProd ApplyPulseHeightCorr false
param ZDHitCorrectorProd ApplySignalPropagationCorr true
param ZDHitCorrectorProd ApplyTimeOfFlightCorr true

source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../pds/drgood/r200733.pds event
file add pdschain ../pds/drgood/r200734.pds event
file add pdschain ../pds/drgood/r200746.pds event
file add pdschain ../pds/drgood/r200750.pds event
file add pdschain ../pds/drgood/r200797.pds event
file add pdschain ../pds/drgood/r200798.pds event
file add pdschain ../pds/drgood/r200801.pds event
file add pdschain ../pds/drgood/r200802.pds event
file add pdschain ../pds/drgood/r200805.pds event
file add pdschain ../pds/drgood/r200806.pds event
file add pdschain ../pds/drgood/r200824.pds event
file add pdschain ../pds/drgood/r200825.pds event
file add pdschain ../pds/drgood/r200826.pds event
file add pdschain ../pds/drgood/r200828.pds event
file add pdschain ../pds/drgood/r200829.pds event
file add pdschain ../pds/drgood/r200832.pds event
file add pdschain ../pds/drgood/r200833.pds event
file add pdschain ../pds/drgood/r200834.pds event
file add pdschain ../pds/drgood/r200835.pds event
file add pdschain ../pds/drgood/r200847.pds event
file add pdschain ../pds/drgood/r200851.pds event
file add pdschain ../pds/drgood/r200853.pds event

module sel ../build_SunOS/shlib/ZDAlignmentMod
param ZDAlignmentMod geom $env(USER_ALIGNMENT).zdgeomalignment
param ZDAlignmentMod minDrift 0.
param ZDAlignmentMod maxDrift 10.
param ZDAlignmentMod showPlots false
param ZDAlignmentMod interactive false
param ZDAlignmentMod ntuple true

report level WARNING
iterator go
exit
