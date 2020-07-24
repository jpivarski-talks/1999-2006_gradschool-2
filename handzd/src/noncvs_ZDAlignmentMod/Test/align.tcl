module sel HbookHistogramModule
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

# The source pds files are the ones you generated with ZDAlignmentBhabhaFilterProc
source_format sel PDSSourceFormat
source create pdschain
file add pdschain ../pds/run200700.pds event
file add pdschain ../pds/run200709.pds event
file add pdschain ../pds/run200712.pds event
file add pdschain ../pds/run200716.pds event
# ... as many runs as you like: 4 runs takes about 10 sec/iteration

module sel ZDAlignmentMod
param ZDAlignmentMod geom starting_geometry_file.zdgeomalignment
report level WARNING
iterator go
