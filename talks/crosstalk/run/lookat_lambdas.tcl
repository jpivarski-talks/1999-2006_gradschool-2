default prompt off
exception continueEventLoop on

module sel HbookHistogramModule
hbook file ../rzn/lookat_lambdas.rzn
hbook init

run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
run_file $env(C3_SCRIPTS)/CcP2.tcl
run_file $env(C3_SCRIPTS)/CcHotList.tcl
run_file $env(C3_SCRIPTS)/CcRunGain.tcl

source_format sel BinarySourceFormat
file in /cdat/sol191/disk3/cleo3/data/r112260.bin event beginrun startrun endrun

proc sel ../build_SunOS/shlib/FindLambdas2

run_file $env(C3_SCRIPTS)/viewTrackFitter.tcl

goto   112260        713
go 1
goto   112260       1335
go 1
goto   112260       3875
go 1
goto   112260       7521
go 1
goto   112260      16223
go 1
goto   112260      16678
go 1
goto   112260      17271
go 1
goto   112260      17530
go 1
goto   112260      18857
go 1
goto   112260      23315
go 1
goto   112260      25672
go 1
goto   112260      26193
go 1
goto   112260      27218
go 1
goto   112260      32526
go 1
goto   112260      33012
go 1
goto   112260      34652
go 1
goto   112260      34978
go 1
goto   112260      38701
go 1
goto   112260      38717
go 1
goto   112260      40950
go 1
goto   112260      42000
go 1
goto   112260      44154
go 1
goto   112260      45192
go 1
goto   112260      49512
go 1
goto   112260      51948
go 1
goto   112260      52867
go 1
goto   112260      53550
go 1
goto   112260      57633
go 1
goto   112260      60815
go 1
goto   112260      61494
go 1
goto   112260      64639
go 1
goto   112260      65748
go 1
goto   112260      68634
go 1
goto   112260      68639
go 1
goto   112260      70942
go 1
goto   112260      76449
go 1
goto   112260      77807
go 1
goto   112260      78695
go 1
goto   112260      80846
go 1
goto   112260      80874
go 1
goto   112260      83233
go 1
goto   112260      83342
go 1
goto   112260      84972
go 1
goto   112260      87463
go 1
goto   112260      94568
go 1
goto   112260      97501
go 1
goto   112260      98910
go 1
goto   112260     100610
go 1
goto   112260     101019
go 1
goto   112260     103332
go 1
goto   112260     103696
go 1
goto   112260     108126
go 1
goto   112260     110289
go 1
goto   112260     112789
go 1
goto   112260     116570
go 1
goto   112260     117878
go 1
goto   112260     118433
go 1
goto   112260     118516
go 1
goto   112260     119618
go 1
goto   112260     124138
go 1
goto   112260     129457
go 1
goto   112260     129929
go 1
goto   112260     130708
go 1
goto   112260     132346
go 1
goto   112260     133030
go 1
goto   112260     133319
go 1
goto   112260     134875
go 1
goto   112260     139577
go 1
goto   112260     141116
go 1
goto   112260     141133
go 1
goto   112260     141860
go 1
goto   112260     143491
go 1
goto   112260     145528
go 1
goto   112260     147736
go 1
goto   112260     150253
go 1
goto   112260     150731
go 1
goto   112260     156324
go 1
goto   112260     163494
go 1
goto   112260     165724
go 1
goto   112260     166143
go 1
goto   112260     166716
go 1
goto   112260     168165
go 1
goto   112260     171061
go 1
goto   112260     171815
go 1
goto   112260     172149
go 1
goto   112260     175862
go 1
goto   112260     176348
go 1
goto   112260     179200
go 1
goto   112260     180427
go 1
goto   112260     180508
go 1
goto   112260     183382
go 1
goto   112260     184526
go 1
goto   112260     190806
go 1
goto   112260     190812
go 1
goto   112260     193611
go 1
goto   112260     195766
go 1
goto   112260     195936
go 1
goto   112260     201942
go 1
goto   112260     202011
go 1
goto   112260     203058
go 1
