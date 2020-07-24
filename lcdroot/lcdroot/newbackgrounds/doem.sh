#!/bin/sh

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24201.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 01 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24203.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 03 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24204.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 04 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24205.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 05 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24206.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 06 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24207.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 07 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24208.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 08 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24209.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 09 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24210.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 10 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24211.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 11 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24212.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 12 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24213.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 13 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24214.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 14 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24215.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 15 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24216.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 16 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24217.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 17 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24218.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 18 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24219.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 19 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24220.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 20 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24221.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 21 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24222.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 22 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24223.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 23 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24224.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 24 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24225.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 25 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24226.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 26 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24227.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 27 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24228.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 28 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24229.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 29 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24230.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 30 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24231.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 31 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24232.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 32 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24233.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 33 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24234.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 34 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24235.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 35 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24236.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 36 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24237.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 37 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24238.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 38 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24239.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 39 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24240.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 40 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24241.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 41 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24242.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 42 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24243.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 43 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24244.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 44 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24245.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 45 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24246.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 46 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24247.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 47 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24248.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 48 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24249.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 49 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24250.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 50 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24251.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 51 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24252.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 52 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24253.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 53 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24254.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 54 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24255.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 55 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24256.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 56 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24257.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 57 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24258.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 58 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24259.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 59 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24260.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 60 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24261.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 61 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24262.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 62 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24263.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 63 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24264.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 64 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24265.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 65 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24266.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 66 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24267.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 67 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24268.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 68 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24269.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 69 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24270.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 70 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24271.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 71 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24272.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 72 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24273.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 73 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24274.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 74 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24275.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 75 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24276.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 76 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24277.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 77 \$HINFO(100,'SUM')
exit
EOF

/nfs/cern/pro/bin/pawX11 << EOF
1
nt/chain sml ../rzn/redo_simd24278.rzn
nt/cuts \$2 (500.-(hade+eme)>300.)&&(sqrt(cpx**2+cpy**2)>15.)&&(tracks>10.)&&((minsep/3.1415926*180.)>30.)&&(mse>15.)&&(abs(mspz)/sqrt(mspx**2+mspy**2+mspz**2)<0.8)&&(abs(cpz-mspz)/sqrt((cpx-mspx)**2+(cpy-mspy)**2+(cpz-mspz)**2)<0.8)&&((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2>0.)&&(sqrt((hade+eme-mse)**2-(cpx-mspx)**2-(cpy-mspy)**2-(cpz-mspz)**2)<70.)
nt/plot //sml/clean/1.scale (scale*250.)*(\$2) ! ! ! ! 100
message 78 \$HINFO(100,'SUM')
exit
EOF
