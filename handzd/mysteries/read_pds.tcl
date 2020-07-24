module sel HbookHistogramModule
hbook file ../rzn/read_pds.rzn
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
file in ../run/after_dan_before_crash.zdgeomalignment

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

prod sel CesrBeamEnergyProd

proc sel ../build_SunOS/shlib/MisterEos

source_format sel PDSSourceFormat
file in ../pds/goodcuts_200976.pds event; go
source rm goodcuts_200976
file in ../pds/goodcuts_200978.pds event; go
source rm goodcuts_200978
file in ../pds/goodcuts_200979.pds event; go
source rm goodcuts_200979
file in ../pds/goodcuts_200981.pds event; go
source rm goodcuts_200981
file in ../pds/goodcuts_200983.pds event; go
source rm goodcuts_200983
file in ../pds/goodcuts_200984.pds event; go
source rm goodcuts_200984
file in ../pds/goodcuts_201001.pds event; go
source rm goodcuts_201001
file in ../pds/goodcuts_201002.pds event; go
source rm goodcuts_201002
file in ../pds/goodcuts_201003.pds event; go
source rm goodcuts_201003
file in ../pds/goodcuts_201004.pds event; go
source rm goodcuts_201004
file in ../pds/goodcuts_201013.pds event; go
source rm goodcuts_201013
file in ../pds/goodcuts_201014.pds event; go
source rm goodcuts_201014
file in ../pds/goodcuts_201016.pds event; go
source rm goodcuts_201016
file in ../pds/goodcuts_201017.pds event; go
source rm goodcuts_201017
file in ../pds/goodcuts_201018.pds event; go
source rm goodcuts_201018
file in ../pds/goodcuts_201019.pds event; go
source rm goodcuts_201019
file in ../pds/goodcuts_201021.pds event; go
source rm goodcuts_201021
file in ../pds/goodcuts_201023.pds event; go
source rm goodcuts_201023
file in ../pds/goodcuts_201024.pds event; go
source rm goodcuts_201024
file in ../pds/goodcuts_201026.pds event; go
source rm goodcuts_201026
file in ../pds/goodcuts_201027.pds event; go
source rm goodcuts_201027
file in ../pds/goodcuts_201028.pds event; go
source rm goodcuts_201028
file in ../pds/goodcuts_201029.pds event; go
source rm goodcuts_201029
file in ../pds/goodcuts_201030.pds event; go
source rm goodcuts_201030
file in ../pds/goodcuts_201031.pds event; go
source rm goodcuts_201031
file in ../pds/goodcuts_201035.pds event; go
source rm goodcuts_201035
file in ../pds/goodcuts_201037.pds event; go
source rm goodcuts_201037
file in ../pds/goodcuts_201039.pds event; go
source rm goodcuts_201039
file in ../pds/goodcuts_201040.pds event; go
source rm goodcuts_201040
file in ../pds/goodcuts_201041.pds event; go
source rm goodcuts_201041
file in ../pds/goodcuts_201042.pds event; go
source rm goodcuts_201042
file in ../pds/goodcuts_201043.pds event; go
source rm goodcuts_201043
file in ../pds/goodcuts_201095.pds event; go
source rm goodcuts_201095
file in ../pds/goodcuts_201097.pds event; go
source rm goodcuts_201097
file in ../pds/goodcuts_201102.pds event; go
source rm goodcuts_201102
file in ../pds/goodcuts_201103.pds event; go
source rm goodcuts_201103
file in ../pds/goodcuts_201104.pds event; go
source rm goodcuts_201104
file in ../pds/goodcuts_201105.pds event; go
source rm goodcuts_201105
file in ../pds/goodcuts_201106.pds event; go
source rm goodcuts_201106
file in ../pds/goodcuts_201107.pds event; go
source rm goodcuts_201107
file in ../pds/goodcuts_201108.pds event; go
source rm goodcuts_201108
file in ../pds/goodcuts_201135.pds event; go
source rm goodcuts_201135
file in ../pds/goodcuts_201142.pds event; go
source rm goodcuts_201142
file in ../pds/goodcuts_201144.pds event; go
source rm goodcuts_201144
file in ../pds/goodcuts_201145.pds event; go
source rm goodcuts_201145
file in ../pds/goodcuts_201146.pds event; go
source rm goodcuts_201146
file in ../pds/goodcuts_201147.pds event; go
source rm goodcuts_201147
file in ../pds/goodcuts_201148.pds event; go
source rm goodcuts_201148
file in ../pds/goodcuts_201150.pds event; go
source rm goodcuts_201150
file in ../pds/goodcuts_201151.pds event; go
source rm goodcuts_201151
file in ../pds/goodcuts_201152.pds event; go
source rm goodcuts_201152
file in ../pds/goodcuts_201153.pds event; go
source rm goodcuts_201153
file in ../pds/goodcuts_201154.pds event; go
source rm goodcuts_201154
file in ../pds/goodcuts_201155.pds event; go
source rm goodcuts_201155
file in ../pds/goodcuts_201156.pds event; go
source rm goodcuts_201156
file in ../pds/goodcuts_201157.pds event; go
source rm goodcuts_201157
file in ../pds/goodcuts_201158.pds event; go
source rm goodcuts_201158
file in ../pds/goodcuts_201160.pds event; go
source rm goodcuts_201160
file in ../pds/goodcuts_201164.pds event; go
source rm goodcuts_201164
file in ../pds/goodcuts_201165.pds event; go
source rm goodcuts_201165
file in ../pds/goodcuts_201171.pds event; go
source rm goodcuts_201171
file in ../pds/goodcuts_201172.pds event; go
source rm goodcuts_201172
file in ../pds/goodcuts_201173.pds event; go
source rm goodcuts_201173
file in ../pds/goodcuts_201174.pds event; go
source rm goodcuts_201174
file in ../pds/goodcuts_201175.pds event; go
source rm goodcuts_201175
file in ../pds/goodcuts_201176.pds event; go
source rm goodcuts_201176
file in ../pds/goodcuts_201179.pds event; go
source rm goodcuts_201179
file in ../pds/goodcuts_201180.pds event; go
source rm goodcuts_201180
file in ../pds/goodcuts_201181.pds event; go
source rm goodcuts_201181
file in ../pds/goodcuts_201184.pds event; go
source rm goodcuts_201184
file in ../pds/goodcuts_201186.pds event; go
source rm goodcuts_201186
file in ../pds/goodcuts_201188.pds event; go
source rm goodcuts_201188
file in ../pds/goodcuts_201189.pds event; go
source rm goodcuts_201189
file in ../pds/goodcuts_201190.pds event; go
source rm goodcuts_201190
file in ../pds/goodcuts_201192.pds event; go
source rm goodcuts_201192
file in ../pds/goodcuts_201194.pds event; go
source rm goodcuts_201194
file in ../pds/goodcuts_201195.pds event; go
source rm goodcuts_201195
file in ../pds/goodcuts_201196.pds event; go
source rm goodcuts_201196
file in ../pds/goodcuts_201197.pds event; go
source rm goodcuts_201197
file in ../pds/goodcuts_201198.pds event; go
source rm goodcuts_201198
file in ../pds/goodcuts_201199.pds event; go
source rm goodcuts_201199
file in ../pds/goodcuts_201201.pds event; go
source rm goodcuts_201201
file in ../pds/goodcuts_201202.pds event; go
source rm goodcuts_201202
file in ../pds/goodcuts_201203.pds event; go
source rm goodcuts_201203
file in ../pds/goodcuts_201204.pds event; go
source rm goodcuts_201204
file in ../pds/goodcuts_201205.pds event; go
source rm goodcuts_201205
file in ../pds/goodcuts_201206.pds event; go
source rm goodcuts_201206
file in ../pds/goodcuts_201213.pds event; go
source rm goodcuts_201213
file in ../pds/goodcuts_201277.pds event; go
source rm goodcuts_201277
file in ../pds/goodcuts_201285.pds event; go
source rm goodcuts_201285
file in ../pds/goodcuts_201301.pds event; go
source rm goodcuts_201301
file in ../pds/goodcuts_201302.pds event; go
source rm goodcuts_201302
file in ../pds/goodcuts_201303.pds event; go
source rm goodcuts_201303
file in ../pds/goodcuts_201318.pds event; go
source rm goodcuts_201318
file in ../pds/goodcuts_201319.pds event; go
source rm goodcuts_201319
file in ../pds/goodcuts_201352.pds event; go
source rm goodcuts_201352
file in ../pds/goodcuts.pds event; go
source rm goodcuts
file in ../pds/goodcuts_201366.pds event; go
source rm goodcuts_201366
file in ../pds/goodcuts_201385.pds event; go
source rm goodcuts_201385
file in ../pds/goodcuts_201387.pds event; go
source rm goodcuts_201387
file in ../pds/goodcuts_201390.pds event; go
source rm goodcuts_201390
file in ../pds/goodcuts_201429.pds event; go
source rm goodcuts_201429
file in ../pds/goodcuts_201431.pds event; go
source rm goodcuts_201431
file in ../pds/goodcuts_201434.pds event; go
source rm goodcuts_201434
file in ../pds/goodcuts_201439.pds event; go
source rm goodcuts_201439
file in ../pds/goodcuts_201441.pds event; go
source rm goodcuts_201441
file in ../pds/goodcuts_201443.pds event; go
source rm goodcuts_201443
file in ../pds/goodcuts_201444.pds event; go
source rm goodcuts_201444
file in ../pds/goodcuts_201447.pds event; go
source rm goodcuts_201447
file in ../pds/goodcuts_201450.pds event; go
source rm goodcuts_201450
file in ../pds/goodcuts_201464.pds event; go
source rm goodcuts_201464
file in ../pds/goodcuts_201466.pds event; go
source rm goodcuts_201466
file in ../pds/goodcuts_201473.pds event; go
source rm goodcuts_201473
file in ../pds/goodcuts_201479.pds event; go
source rm goodcuts_201479
