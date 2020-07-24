jim = (463 + 281)/250;
jimerr = 76/250;
laura = (375 + 230)/250;
lauraerr = Sqrt[(375 + 230)]/250;
onesig = FullForm[ParametricPlot[
    {jim + jimerr*Cos[t], laura + lauraerr*Sin[t]}, {t, 0, 2*Pi},
    DisplayFunction -> Identity]][[1,1,1,1,1]];
twosig = FullForm[ParametricPlot[
    {jim + 2*jimerr*Cos[t], laura + 2*lauraerr*Sin[t]}, {t, 0, 2*Pi},
    DisplayFunction -> Identity]][[1,1,1,1,1]];
threesig = FullForm[ParametricPlot[
    {jim + 3*jimerr*Cos[t], laura + 3*lauraerr*Sin[t]}, {t, 0, 2*Pi},
    DisplayFunction -> Identity]][[1,1,1,1,1]];
redll = 0.03296;
purpll = 0.01345;
redjj = 0.026704;
purpjj = 0.011;
mat = {{redll, purpll}, {redjj, purpjj}};
invmat = Inverse[mat];

centroid = {56.2, 83.5};
Show[Graphics[{RGBColor[0.9,0.9,1], Polygon[(invmat . #)& /@ threesig], GrayLevel[0], Line[(invmat . #)& /@ threesig],
	       RGBColor[0.6,0.6,1], Polygon[(invmat . #)& /@ twosig], GrayLevel[0], Line[(invmat . #)& /@ twosig],
	       RGBColor[0.3,0.3,1], Polygon[(invmat . #)& /@ onesig], GrayLevel[0], Line[(invmat . #)& /@ onesig],
	       Line[{centroid + {-5, 0}, centroid + {5, 0}}],

	       Line[{centroid + {0, -5}, centroid + {0, 5}}]
	      }]
     , PlotRange -> {{0, 100}, {0, 100}}
     , Frame -> True
     , AspectRatio -> 1];


