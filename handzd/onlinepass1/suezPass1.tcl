#!/usr/local/bin/tclsh
#=================================================================
# suezPass1.tcl
# updated by Billy M. (Marty) Bilich in coordination with Dave 
#   Kreinick, Chris Jones and Martin Lohner (both Offline Processing) 
#   and Hubert Schwarthoff (Online Processing) 
#=================================================================
# NOTE TO USER:  this file is meant to be the tcl scripting 
#   language prototype SUEZPASS1 online and offline processing 	
#   command file.  Hopefully, the suez user should only need
#   to make his changes to this file only.  This file before
#   embedding should be suitable for SUEZPASS1 stage1 processing
#   (offline, nonembedded, dynamic) if the two commented out 
#   lines at the bottom of these initial comments that set the  
#   option flags SUEZPASS1_OFFLINE and CONSTANTS_FROM_DB are 
#   uncommented. Thereafter this file should be immediately 
#   executable from any unix prompt as >suez -f suezPass1.tcl 
#   or from a suez prompt as suez>tcl_source suezPass1.tcl.
#=================================================================
#   After embedding this command file should also be suitable
#   for SUEZPASS1 stage2 processing (offline, embedded, local)
#   and also for SUEZPASS1 stage3 processing (online, embedded,
#   local).  This embedding would take place via an initial 
#   execution of gmake. It will be assumed that the flag 
#   CONSTANTS_FROM_DB = 1 always (to be able to minimize the 
#   number of cases that we will be working with). There will then
#   be two separate packages to deal with the stage 2 offline 
#   SUEZPASS1_OFFLINE = 1 (true) case and the stage 3 online 
#   SUEZPASS1_OFFLINE = 0 (false) case.  Each case will reside in 
#   its own cvs module package (stage 2 belongs to cvs module 
#   SuezPass1Offline (containing its own offline makefile plus the 
#   files suezPass1.tcl, suezPass1.cc, suezParser.tcl and 
#   suezEmbedded.h) and stage 3 belongs to cvs module  
#   SuezPass1Online (containing only its own online makefile)). 
#   NO use will be made of -D C preprocessor flags. Suez pass 1 
#   stage 2 offline will be implemented within the SuezPass1Offline 
#   module at a unix prompt as:
#      >gmake 
#   Suez pass 1 stage 3 online will be implemented within the 
#   SuezPass1Online module at a unix prompt as:
#      >gmake MT=y    (multithreaded = yes)
#   Thereafter, to proceed with stage 2 or stage 3 processing
#   execution would continue via the execution of suezPass1.cc
#   Note that the library modules are accessed according to the
#   setting of the $C3_SHLIB environmental variable. 
#================================================================
#   For offline processing when asked to enter a test file
#   try one of the two below test files:
#   1) /a/sol402/cdat/sol402/disk2/cleo3/data/r107239.bin
#   2) /a/sol303/cdat/sol303/disk6/cleo3/data/r106740.bin
#================================================================
# Modifications List
# 6/19/00 - BMB - moved embedded tcl from suezPass1.cc to
#    initially create this file which should be suitable for
#    suez stage 1 unembedded processing as is.  
#==================================================================
# USER NOTE:to run suezPass1.tcl for stage 1 processing remove the 
# commenting from the below two lines of code, but to run for stage
# 2 and stage 3 make sure the below two lines are commented out
#===COMMENT OUT THE BELOW TWO LINES FOR STAGE 2 & 3 PROCESSING ====
set SUEZPASS1_OFFLINE 1
set CONSTANTS_FROM_DB 1
#================================================================
# NOTE TO USER:change the below processing flags to 1 (true) or 
#  to 0 (false) depending on how you wish the suezPass1 
#  processing to proceed.  
#================================================================
#
### Reentrant Pass1 script
#
# EMERGENCY, ALERT, CRITICAL, ERROR, WARNING, NOTICE, INFO, VERIFY, DEBUG
set reportLevel WARNING
report level $reportLevel
#
if [ catch {
# report file open /nfs/online/cleo31/Logs/suezPass1Dynamic.log
echo "++++++++++++++++++ Starting up Pass1 process +++++++++++++++++++++"
#
# Set default values for detector specifics
set noCC false
set noDR false
set noDRCA false
set noRICH false
set noTRIG false
set noMU false
set noDEDX false
set havePi0Proc false
set nonBlocking false
set runEventNumber false
set ccEventSelector false
set withRichResolution false
set copyRawData false
set synchWithRunControl false
set level3Kill false
# default Offline bootfile
set constants_boot /nfs/cleo3/constants/db/Codi
set constants_bootOffline false
#

if {$SUEZPASS1_OFFLINE} {  
  set defaultSampling 0
  puts -nonewline "Please enter input run number, e.g. 123456:  " 
  flush stdout
  set runnumber 201365
  puts "Run number is:  $runnumber  input file is:  r$runnumber.bin"
}
if {!$SUEZPASS1_OFFLINE} {
  set defaultSampling 1
# Default Online bootfile
  set constants_boot /cdat/solon2/disk3/DataBases/Constants
# Command line option to override bootfile
  runtime_switch_opt --constants_bootOffline constants_bootOffline
  if { "$constants_bootOffline" == "true" } {
    set constants_boot /nfs/cleo3/constants/db/Codi
  }
  runtime_value_opt --constants_boot constants_boot

  echo Pass1 arguments($argc): $argv

# Report level option
  runtime_value_opt --reportLevel reportLevel
# Special option to switch on debug
  set debugSwitch false
  runtime_switch_opt --debug debugSwitch
  if { "$debugSwitch" == "true" } {
    set reportLevel DEBUG
  } else {
    report level $reportLevel
  }
  echo "Pass1 report level: $reportLevel."

# Option for level3 killing
  runtime_switch_opt --level3Kill level3Kill

  runtime_switch_opt --noCC noCC
  runtime_switch_opt --noDR noDR
  runtime_switch_opt --noDRCA noDRCA
  runtime_switch_opt --noTRIG noTRIG
  runtime_switch_opt --noMU noMU
  runtime_switch_opt --noRICH noRICH
  runtime_switch_opt --noDEDX noDEDX
  runtime_switch_opt --nonBlocking nonBlocking
  runtime_switch_opt --runEventNumber runEventNumber
  runtime_switch_opt --ccEventSelector ccEventSelector
  runtime_switch_opt --withRichResolution withRichResolution
  runtime_switch_opt --havePi0Proc havePi0Proc
  runtime_switch_opt --copyRawData copyRawData
  runtime_switch_opt --synchWithRunControl synchWithRunControl

}

echo Pass1 constants bootfile is $constants_boot

# Set up general conditions
# After a data access exception, continue with the next event
exception continueEventLoop on
# If there are alternate modules or sources, always use the first,
#  don't demand interactive choice by user
default prompt off
#
# Producers and sources needed by all
#
source_format sel AsciiSourceFormat 
source_format sel BinarySourceFormat 
if {$SUEZPASS1_OFFLINE} {
  module sel CorbaModule
  corba init
  module sel HbookHistogramModule
  hbook file hist_$runnumber.rzn
  hbook init
}

if {!$SUEZPASS1_OFFLINE} { 
# Initial setup for Online SUEZ process
  module sel CorbaModule
#   corba args "-logNoDate"
# Pass on log stream setup
# Must happen before "corba init"
  set logSocket 0
  runtime_value_opt -logSocket logSocket
  set logStartup 0
  runtime_value_opt -logStartup logStartup
  if { $logSocket != 0 && $logStartup != 0 } {
    echo Setup logSocket = $logSocket, logStartup = $logStartup
    corba args "-logSocket $logSocket -logStartup $logStartup"
  }
  corba init

  module sel OnlineComponentModule
  online name Pass1
# Special Online modules
  module sel AlarmModule
  AlarmModule init
  module sel OnlineInformationSink
  OnlineInformationSink period 1000000
  module sel DatabaseHistogramModule
  dbhist init
  dbhist mode Online
  dbhist component Pass1
# Start Online report logging, set standard suez report threshold very high,
# and set user report level for OnlineReportModule
  module sel OnlineReportModule
  report level error
#  report level debug
  OnlineReportModule level $reportLevel

}
#
# Constants definitions
#
if {$CONSTANTS_FROM_DB} {
# Constants from database
  module sel ConstantsModule
  echo "Load Pass1 db constants with tag CLEO3default"
  constants in $constants_boot standard CLEO3default exclude_streams richmargins
}
# Basegeom is needed by several procs
if {!$SUEZPASS1_OFFLINE} {
  file in /nfs/online/cleo31/SuezOnline/Pass1/SuezPass1OnlineProduction/material.asc material
#  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/current2/data/material.asc material
# dummy streams just in case someone tries to synch on them
#  emptysource def Test drcalibration ccalignment
} else {
  file in /nfs/cleo3/Offline/rel/current/data/material.asc material
# dummy streams just in case someone tries to synch on them
  emptysource def Test dralignment 
}

#
# Begin defining processors and producers
#

# Debug to show proxies for startrun
#proc sel RecordContentsProc
#param RecordContentsProc record startrun

proc sel L1CesrOffsetsMonProc

# Online likes the runEventNumberProc to keep RunSummary apprised 
if { "$runEventNumber" == "true" } {
  echo "Pass1: have RunEventNumberProc"
  proc sel RunEventNumberProc
} else {
  echo "Pass1: no RunEventNumberProc"
}
# Interpret the raw data format
prod sel RawDataProd 
# Do the data integrity monitoring first
proc sel P1IntegrityMonProc
# The following detector specific sections consist of a part that is
# always selected and a part that is only selected when the
# corresponding component is not switched off through a command line
# option.
# CC
prod sel CcGeomProd 
prod sel C3ccProd
param C3ccProd RequireRunGainsHotList false
prod sel C3ccConProd
prod sel C3ccReconProd 
#prod sel CcfcReconProd
prod sel CcP2ReconProd
if { "$noDR" == "false" } {
  # Convert Solo seed tracks to a fit
  prod sel SeedTrackToFit
  prod sel SeedToTRTrackProd
  prod sel TrackDeliveryProd
  prod sel TrackShowerMatchingProd
  prod sel PhotonDecaysProd
}
if {!$CONSTANTS_FROM_DB} {
# For ASCII constants, need source formats and file definitions
  source_format sel  CCECalChannelFileSourceFormat 
  source_format sel  CCBBCalCrystalFileSourceFormat 
  source_format sel  CCBBCalOverallGainFileSourceFormat 
  source_format sel  CCDaqPeelMapFileSourceFormat 
  source_format sel  CCFBUSChannelFileSourceFormat
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/cleo3_103812.ccfbuschannel ccfbuschannel 
  source_format sel  CCNbrListFileSourceFormat 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/cleo2_75001.ccnbrlist ccnbrlist 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/cleo3_103224.ccecalchannel ccecalchannel 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/cleo3_102776.ccbbcaloverallgain ccbbcaloverallgain 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/cleo3_102776.ccbbcalcrystal ccbbcalcrystal 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/cleo3_104102.ccdaqpeelmap ccdaqpeelmap
}
if { "$noCC" == "false" } {
  echo "Pass1: have CC" 
  proc sel P1CrystalMonProc 
  proc sel P1LumiMonProc
  if { $havePi0Proc == 1 } {
    if { $noDR == 0 } {
      echo "Pass1: Run Pi0Proc"
      proc sel P1Pi0Proc
    } else {
      echo "Pass1: no DR, cannot do pi0 study"
    }
  }
} else { 
  echo "Pass1: no CC"
}

# CC overflow filter
#proc sel CcOvFlowFilterProc

# If requested, turn on CC event filter.
# Could speed up Pass1 by ca. 15% by aborting event processing
# early on, before tracking is run. Based on CC information.
if { "$ccEventSelector" == "true" } {
  echo "Pass1: have CcEventSelectProc"
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
} else {
  echo "Pass1: no CcEventSelectProc"
}

# DR
prod sel CDOffCal  
param CDOffCal MaximumTime 10000000
param CDOffCal MinimumTime -20000000
prod sel DRGeom
if { $CONSTANTS_FROM_DB == 0 } {
  source_format sel ADRGeomWireSurveyFileSourceFormat 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/dr3.adrgeomwiresurvey basegeometry 
  source_format sel ADRGeomLayerFileSourceFormat 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/dr3.adrgeomlayer 
  source_format sel DRGeomAlignmentFileSourceFormat 
  file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/test.drgeomalignment
} 
prod sel ADRGeomProd
prod sel CESR
prod sel PreliminaryDRHitProd
prod sel CalibratedDRHitProd
prod sel TriggerPhaseForDataProd
prod sel TrackletBunchFinder
prod sel DetectorConfigurationProd
# Manually turn on ZD setup instead of SVX
param DetectorConfigurationProd Override true
param DetectorConfigurationProd UseZDnotSI true

prod sel DRElecMapProd
if { "$noDR" == "false" } { 
   echo "Pass1: have DR" 
   proc sel P1TrackMonProc
   param P1TrackMonProc online true

   prod sel EmptyMuTrackProd
   prod sel EventPropertiesProd
   prod sel DRHitCorrectorProd
   param DRHitCorrectorProd ApplyEntranceAngleCorr false           
   param DRHitCorrectorProd ApplyStandardCorrections false   
   prod sel ChisqFitProd
   param ChisqFitProd UseDRCathode false
   param ChisqFitProd UseSVRPhi false
   param ChisqFitProd UseSVZ false
   proc sel SemiLepProc

} else {
   echo "Pass1: no DR" 
}
# ZD

source_format sel ZDWeightDriftFileSourceFormat
file in /nfs/online/cleo31/SuezOnline/Pass1/SuezPass1OnlineProduction/test.zdweightdrift
source_format sel ZDWeightLayerFileSourceFormat
file in /nfs/online/cleo31/SuezOnline/Pass1/SuezPass1OnlineProduction/test.zdweightlayer
source_format sel ZDWeightPhiFileSourceFormat
file in /nfs/online/cleo31/SuezOnline/Pass1/SuezPass1OnlineProduction/test.zdweightphi
source_format sel ZDWeightThetaFileSourceFormat
file in /nfs/online/cleo31/SuezOnline/Pass1/SuezPass1OnlineProduction/test.zdweighttheta

prod sel ZDGeomProd
prod sel AZDGeomProd
prod sel ZDWireLayerProd
prod sel ZDDriftFunctionProd
prod sel CalibratedZDHitProd
prod sel ZDHitCorrectorProd
param ZDHitCorrectorProd ApplyEntranceAngleCorr false           
param ZDHitCorrectorProd ApplyStandardCorrections false   

# DRCA
prod sel DRCACorrectHitProd
#prod sel CalibratedCathodeHitProd
prod sel DRCAClusterProd
if { "$noDRCA" == "false" } {
  echo "Pass1: have DRCA"
  proc sel P1DRCAMonProc
} else {
    echo "Pass1: no DRCA"
}
# RICH
if { "$noRICH" == "false" } {
  echo "Pass1: have RICH"

  if { "$withRichResolution" == "true" } {
    echo "Pass1: have RichResolutionProc"

    prod sel RichCalibratedHits
    prod sel RichClustering
    prod sel RichClustChamberCoord
    prod sel RichTracksFromRichProd
# Loosens back-to-back requirement for low energy running
    param RichTracksFromRichProd Acollinearity 0.93
    prod sel RichTrackClusterMatchProd
    prod sel RichPhotonsProd
    param RichPhotonsProd BumpPulseHeightMax 700

    prod sel RichImprovedTracksProd
    param RichImprovedTracksProd TrackImprovementID 0

    prod sel RichAnglesProd
    param RichAnglesProd Pexact 200000.0

    prod sel RichAverageAnglesProd
    proc sel RichResolutionProc
#    param RichResolutionProc RichTrackEventSelectionFlag -0.9

#    source_format sel RICHMarginsFileSourceFormat
#    file in /cdat/solon2/disk4/cleo31/SuezOnline/rel/clib/data/passall.richmargins richmargins
    constants in $constants_boot standard RICHMarginsDummy streams richmargins

  } else {
    echo "Pass1: no RichResolutionProc"
  }

  proc sel RichRawDataMonProc
  if { "$noCC" == "true" } {
    echo "Pass1: RICH selected but no CC"
    echo "Pass1: Run RICH proc with CCEventSelectionFlag 0"
    param RichRawDataMonProc CCEventSelectionFlag 0
  } else {
    echo "Pass1: Run RICH proc with CCEventSelectionFlag 1"
    param RichRawDataMonProc CCEventSelectionFlag 1
  }
  param RichRawDataMonProc ChannelsToMonitor -2 -1
} else {
  echo "Pass1: no RICH"
}
# TRIG
prod sel TriggerDataProd
param TriggerDataProd DoNotUseDeadWires true
if { "$noTRIG" == "false" } {
   echo "Pass1: have TRIG" 
   prod sel TriggerDataProd
   prod sel TriggerL1DataProd
   proc sel P1TriggerMonProc 
} else {
   echo "Pass1: no TRIG" 
}
# MU
if { "$noMU" == "false" } { 
   echo "Pass1: have MU"
#   proc sel P1MuonMonProc
   proc sel P1MuMonProc
} else {
   echo "Pass1: no MU"
}

# DEDX
if { "$noDEDX" == "false" } {
  echo "Pass1: have DEDX"
  prod sel DedxConstProd
  prod sel DedxReconOnlineProd
  prod sel DedxInfoProd
  param DedxInfoProd ApplyRunCorr false
  proc sel P1DedxMonProc
} else {
  echo "Pass1: no DEDX"
}
# Other
prod sel MagFieldProd
#param MagFieldProd alwaysUseDefault true # this always uses some default value
param MagFieldProd useDefaultForMissingReadings true
prod sel NavigationProd
prod sel DBEventHeaderProd
prod sel CesrBeamEnergyProd
prod sel EventTypeProd
# Tracking

#prod sel DoitFastProd
#param DoitFastProd ContinueIfHitsMissing true
prod sel DoitProd
param DoitProd ContinueIfHitsMissing true
param DoitProd UseSilicon false
# Run Doit in mode 1, i.e. DoitFast
# Mode 38 is default, meaning full Doit.
param DoitProd DoitModeNumber 1

#prod sel SoloProd
#param SoloProd ContinueIfHitsMissing true

#
# Online connection
#
if {!$SUEZPASS1_OFFLINE} {
   module sel OnlineSourceModule
   if { "$nonBlocking" == "true" } { 
      echo "Pass1: Online source will be non blocking" 
      onlineSource bufferedOutput nonBlocking
   } else { 
      echo "Pass1: Online source will be blocking"
   }
   if { "$defaultSampling" == "false" } {
      onlineSource samplingRate $samplingRate
      echo "Pass1: Sampling rate will be $samplingRate."
   } else {
      echo "Pass1: Will use default sampling rate."
   }
   if { "$copyRawData" == "true" } {
     echo "Pass1: Source make copy of raw data for frame."
     onlineSource copyRawData true
   } else {
     echo "Pass1: No copy of raw data is made."
   }
   if { "$synchWithRunControl" == "true" } {
     echo "Pass1: Source synchronizes with Online RunControl."
     onlineSource synchWithRunControl true
   } else {
     echo "Pass1: No synchronization with Online RunControl."
   }
   if { "$level3Kill" == "true" } {
     echo "Pass1: Level3 killing ON."
     onlineSource addL3AcceptSelection EBalance 100
     onlineSource addL3AcceptSelection TotalE 100
     onlineSource addL3AcceptSelection Hadron 100
     onlineSource addL3AcceptSelection MuPair 100
     onlineSource addL3AcceptSelection Multiplicity 100

# L3 acceptance codes:
#  0  N/A            Event was rejected.  You should never see this offline.
#  1  EBalance       Accepted for balanced energy deposition (1.75 GeV total,
#                    and at least 0.1 GeV on each side of the centerline in Z)
#  2  TotalE         Accepted for total energy ( 2.25 GeV )
#  3  Hadron         Hadron -- as identified by crystals
#  4  MuPair         Mu pair
#  5  Multiplicity   Accepted for track multiplicity
#  6  Random         Random trigger accepted automatically
#  7  Prescale       Prescale trigger accepted automatically
#  8  Garbage        Garbage.  Rejected event written out in a 1/16 sample.

   } else {
     echo "Pass1: Level3 killing OFF."
   }
}
echo [proc lss]
echo [prod lss]

#
# Finally connect to the input event stream
#
if {!$SUEZPASS1_OFFLINE} {
   onlineSource runTypeSelection normal
# Connection to EventBuilder
   echo "Pass1: connect now"
   onlineSource connect Global|EventBuilder event beginrun startrun endrun
   echo "Pass1: Loading done."
} else {
    echo "good things"
   file in r$runnumber.bin beginrun event endrun  startrun
}

# RunStatistics
# MUST be after the event data source selection
module sel RunStatisticsSourceModule
# This connects to default stream beginrun
runstatistics in

} resultString ] {
  echo "Pass1: Error loading."
  puts "$resultString"
}
echo "+++++++++++++++++++++++++++++ Pass1 Go ++++++++++++++++++++++++++++++++"

if [ catch {
    proc sel HistogramViewerProc
  go 1
  echo "Pass1 after one event:"
  echo [source status]
  echo [source ls]
  go
} resultString ] {
  echo "Pass1: Error running."
}
echo "Pass1: Check source status"
echo [ source status ]
set regResult [ regexp RunStatistics [ source status ] ]
if { "$regResult" == "0" } {
  echo "Pass1: ERROR!! RunStat source NOT found."
  echo "Pass1: RunStatisticsDBServer not running. Please restart."
#  AlarmModule send ERROR "RunStatisticsDBServer not running. Please restart server and Pass1."
} else {
  echo "Pass1: RunStat source found"
}
echo "Pass1: exit now"
exit
# end of suezPass1.tcl
