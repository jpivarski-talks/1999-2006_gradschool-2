module sel ../build_SunOS/shlib/HbookHistogramModule
hbook file ../rzn/batch_$env(USER_RUN).rzn
hbook init

module sel CorbaModule
corba init
module sel ConstantsModule
constants in $env(C3_CONST) standard CLEO3default streams superconductingquad magfudge basegeometry zdweight2layerdriftentang zdweight2layertheta zdweight2layerphi zddaqcellidmap zdwirequality zdadc2charge zdadcpedestal zdt0card zdt0channel zdt0hvcard
source_format sel AsciiSourceFormat
file in $env(C3_DATA)/material.asc material
module sel RunStatisticsSourceModule
runstatistics in

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
file in /cdat/sol406/disk1/drcal/Constants/ZDDriftDatav10.zddriftdata
source_format sel ZDt0globalFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDt0global_v3.zdt0global
source_format sel ZDt0crateFileSourceFormat
file in /cdat/sol406/disk1/drcal/Constants/ZDt0crate_v2.zdt0crate

emptysource def zdalignment zdalignment

prod sel AZDGeomProd
prod sel ZDGeomProd
prod sel ZDDriftFunctionProd
prod sel ZDHitCorrectorProd
prod sel MagFieldProd
prod sel NavigationProd
prod sel TrackDeliveryProd
prod sel DetectorConfigurationProd
param DetectorConfigurationProd Override true;
param DetectorConfigurationProd UseZDnotSI true;

source_format sel PDSSourceFormat
file in ../pds/r$env(USER_RUN).pds event

module sel ../build_SunOS/shlib/ZDAlignmentMod
param ZDAlignmentMod geom pretty_good.zdgeomalignment
param ZDAlignmentMod showPlots false
param ZDAlignmentMod interactive false

report level WARNING
iterator go
exit
