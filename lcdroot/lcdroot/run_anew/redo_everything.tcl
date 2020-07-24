module sel LoadHbook4MModule
module sel HbookHistogramModule
hbook file ../rzn/redo_$env(USER_NAME).rzn
hbook init

proc sel ../build_Linux/shlib/Clean

source_format sel RootLCDEventSourceFormat
file in $env(USER_FILE)
param Clean mcfile $env(USER_MCFILE)
go

hbook terminate
exit
