module sel HbookHistogramModule
hbook file simplethings.rzn
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

source_format sel ZDGeomAlignmentFileSourceFormat
file in after_dan_before_crash.zdgeomalignment

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
file add pdschain ../pds/drgood/r200854.pds event
file add pdschain ../pds/drgood/r200976.pds event
file add pdschain ../pds/drgood/r200978.pds event
file add pdschain ../pds/drgood/r200979.pds event
file add pdschain ../pds/drgood/r200981.pds event
file add pdschain ../pds/drgood/r200983.pds event
file add pdschain ../pds/drgood/r200984.pds event
file add pdschain ../pds/drgood/r201001.pds event
file add pdschain ../pds/drgood/r201002.pds event
file add pdschain ../pds/drgood/r201003.pds event
file add pdschain ../pds/drgood/r201004.pds event
file add pdschain ../pds/drgood/r201013.pds event
file add pdschain ../pds/drgood/r201014.pds event
file add pdschain ../pds/drgood/r201016.pds event
file add pdschain ../pds/drgood/r201017.pds event
file add pdschain ../pds/drgood/r201018.pds event
file add pdschain ../pds/drgood/r201019.pds event
file add pdschain ../pds/drgood/r201021.pds event
file add pdschain ../pds/drgood/r201023.pds event
file add pdschain ../pds/drgood/r201024.pds event
file add pdschain ../pds/drgood/r201026.pds event
file add pdschain ../pds/drgood/r201027.pds event
file add pdschain ../pds/drgood/r201028.pds event
file add pdschain ../pds/drgood/r201029.pds event
file add pdschain ../pds/drgood/r201030.pds event
file add pdschain ../pds/drgood/r201031.pds event
file add pdschain ../pds/drgood/r201035.pds event
file add pdschain ../pds/drgood/r201037.pds event
file add pdschain ../pds/drgood/r201039.pds event
file add pdschain ../pds/drgood/r201040.pds event
file add pdschain ../pds/drgood/r201041.pds event
file add pdschain ../pds/drgood/r201042.pds event
file add pdschain ../pds/drgood/r201043.pds event
file add pdschain ../pds/drgood/r201095.pds event
file add pdschain ../pds/drgood/r201097.pds event
file add pdschain ../pds/drgood/r201102.pds event
file add pdschain ../pds/drgood/r201103.pds event
file add pdschain ../pds/drgood/r201104.pds event
file add pdschain ../pds/drgood/r201105.pds event
file add pdschain ../pds/drgood/r201106.pds event
file add pdschain ../pds/drgood/r201107.pds event
file add pdschain ../pds/drgood/r201108.pds event
file add pdschain ../pds/drgood/r201135.pds event
file add pdschain ../pds/drgood/r201142.pds event
file add pdschain ../pds/drgood/r201144.pds event
file add pdschain ../pds/drgood/r201145.pds event
file add pdschain ../pds/drgood/r201146.pds event
file add pdschain ../pds/drgood/r201147.pds event
file add pdschain ../pds/drgood/r201148.pds event
file add pdschain ../pds/drgood/r201150.pds event
file add pdschain ../pds/drgood/r201151.pds event
file add pdschain ../pds/drgood/r201152.pds event
file add pdschain ../pds/drgood/r201153.pds event
file add pdschain ../pds/drgood/r201154.pds event
file add pdschain ../pds/drgood/r201155.pds event
file add pdschain ../pds/drgood/r201156.pds event
file add pdschain ../pds/drgood/r201157.pds event
file add pdschain ../pds/drgood/r201158.pds event
file add pdschain ../pds/drgood/r201160.pds event
file add pdschain ../pds/drgood/r201164.pds event
file add pdschain ../pds/drgood/r201165.pds event
file add pdschain ../pds/drgood/r201166.pds event
file add pdschain ../pds/drgood/r201167.pds event
file add pdschain ../pds/drgood/r201170.pds event
file add pdschain ../pds/drgood/r201171.pds event
file add pdschain ../pds/drgood/r201172.pds event
file add pdschain ../pds/drgood/r201173.pds event
file add pdschain ../pds/drgood/r201174.pds event
file add pdschain ../pds/drgood/r201175.pds event
file add pdschain ../pds/drgood/r201176.pds event
file add pdschain ../pds/drgood/r201179.pds event
file add pdschain ../pds/drgood/r201180.pds event
file add pdschain ../pds/drgood/r201181.pds event
file add pdschain ../pds/drgood/r201184.pds event
file add pdschain ../pds/drgood/r201186.pds event
file add pdschain ../pds/drgood/r201188.pds event
file add pdschain ../pds/drgood/r201189.pds event
file add pdschain ../pds/drgood/r201190.pds event
file add pdschain ../pds/drgood/r201192.pds event
file add pdschain ../pds/drgood/r201193.pds event
file add pdschain ../pds/drgood/r201194.pds event
file add pdschain ../pds/drgood/r201195.pds event
file add pdschain ../pds/drgood/r201196.pds event
file add pdschain ../pds/drgood/r201197.pds event
file add pdschain ../pds/drgood/r201198.pds event
file add pdschain ../pds/drgood/r201199.pds event
file add pdschain ../pds/drgood/r201201.pds event
file add pdschain ../pds/drgood/r201202.pds event
file add pdschain ../pds/drgood/r201203.pds event
file add pdschain ../pds/drgood/r201204.pds event
file add pdschain ../pds/drgood/r201205.pds event
file add pdschain ../pds/drgood/r201206.pds event
file add pdschain ../pds/drgood/r201213.pds event
file add pdschain ../pds/drgood/r201277.pds event
file add pdschain ../pds/drgood/r201285.pds event
file add pdschain ../pds/drgood/r201301.pds event
file add pdschain ../pds/drgood/r201302.pds event
file add pdschain ../pds/drgood/r201303.pds event
file add pdschain ../pds/drgood/r201318.pds event
file add pdschain ../pds/drgood/r201319.pds event
file add pdschain ../pds/drgood/r201352.pds event
file add pdschain ../pds/drgood/r201365.pds event
file add pdschain ../pds/drgood/r201366.pds event
file add pdschain ../pds/drgood/r201385.pds event
file add pdschain ../pds/drgood/r201387.pds event

proc sel ../build_SunOS/shlib/SimpleThings
proc sel HistogramViewerProc
go
