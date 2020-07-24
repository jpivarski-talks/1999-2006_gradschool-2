module sel ../build_SunOS/shlib/HbookHistogramModule
hbook file align.rzn
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
file add pdschain ../pds/r200733.pds event
file add pdschain ../pds/r200734.pds event
file add pdschain ../pds/r200746.pds event
file add pdschain ../pds/r200750.pds event
file add pdschain ../pds/r200797.pds event
file add pdschain ../pds/r200798.pds event
file add pdschain ../pds/r200801.pds event
file add pdschain ../pds/r200802.pds event
file add pdschain ../pds/r200805.pds event
file add pdschain ../pds/r200806.pds event
file add pdschain ../pds/r200826.pds event
file add pdschain ../pds/r200829.pds event
file add pdschain ../pds/r200832.pds event
file add pdschain ../pds/r200833.pds event
file add pdschain ../pds/r200835.pds event
file add pdschain ../pds/r200847.pds event
file add pdschain ../pds/r200851.pds event
file add pdschain ../pds/r200976.pds event
file add pdschain ../pds/r200978.pds event
file add pdschain ../pds/r200979.pds event
file add pdschain ../pds/r201002.pds event
file add pdschain ../pds/r201003.pds event
file add pdschain ../pds/r201004.pds event
file add pdschain ../pds/r201013.pds event
file add pdschain ../pds/r201014.pds event
file add pdschain ../pds/r201016.pds event
file add pdschain ../pds/r201017.pds event
file add pdschain ../pds/r201019.pds event
file add pdschain ../pds/r201021.pds event
file add pdschain ../pds/r201023.pds event
file add pdschain ../pds/r201024.pds event
file add pdschain ../pds/r201026.pds event
file add pdschain ../pds/r201027.pds event
file add pdschain ../pds/r201029.pds event
file add pdschain ../pds/r201030.pds event
file add pdschain ../pds/r201035.pds event
file add pdschain ../pds/r201037.pds event
file add pdschain ../pds/r201039.pds event
file add pdschain ../pds/r201040.pds event
file add pdschain ../pds/r201105.pds event
file add pdschain ../pds/r201145.pds event
file add pdschain ../pds/r201148.pds event
file add pdschain ../pds/r201151.pds event
file add pdschain ../pds/r201154.pds event
file add pdschain ../pds/r201157.pds event
file add pdschain ../pds/r201158.pds event
file add pdschain ../pds/r201174.pds event

module sel ../build_SunOS/shlib/ZDAlignmentMod

report level WARNING
