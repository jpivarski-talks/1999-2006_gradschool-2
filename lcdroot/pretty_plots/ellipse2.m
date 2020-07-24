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

(* +-3000 in n1n3, +-7500 in n2n3: completely not useful *)

(* centroid = {56.2, 83.5}; *)
(* Show[Graphics[{RGBColor[0.9,0.9,1], Polygon[(invmat . #)& /@ threesig], GrayLevel[0], Line[(invmat . #)& /@ threesig], *)
(*                RGBColor[0.6,0.6,1], Polygon[(invmat . #)& /@ twosig], GrayLevel[0], Line[(invmat . #)& /@ twosig], *)
(*                RGBColor[0.3,0.3,1], Polygon[(invmat . #)& /@ onesig], GrayLevel[0], Line[(invmat . #)& /@ onesig], *)
(*                Line[{centroid + {-5, 0}, centroid + {5, 0}}], *)
(*                Line[{centroid + {0, -5}, centroid + {0, 5}}] *)
(*               }] *)
(*      , PlotRange -> {{0, 120}, {0, 120}} *)
(*      , Frame -> True *)
(*      , AspectRatio -> 1]; *)
(* Select[(invmat . #)& /@ onesig, (Abs[#[[2]] - 120] < 0.9)& ] *)
(* Out[44]= {{44.513, 120.288}, {37.4965, 120.711}} *)
(* Out[39]= {{48.5659, 118.754}, {34.4822, 119.721}} *)
(* Out[36]= {{51.1793, 120.718}, {30.1882, 121.842}} *)
(* Out[35]= {{101.231, -0.946297}, {80.2218, 0.223214}} *)
(* Out[33]= {{97.8789, -1.11687}, {83.8589, -0.299908}} *)
(* Out[17]= {{93.3699, 1.52447}, {86.1181, 2.52732}} *)
(* InputForm[x /. FindMinimum[(Interpolation[{{80.2218, 0.223214}, {30.1882, 121.842}}, InterpolationOrder -> 1][x] - 0)^2, {x, 60}][[2,1]]] *)

<< Statistics`ContinuousDistributions`

?Plot3D

Plot3D[f, {x, xmin, xmax}, {y, ymin, ymax}] generates a three-dimensional plot
   of f as a function of x and y. Plot3D[{f, s}, {x, xmin, xmax}, {y, ymin,
   ymax}] generates a three-dimensional plot in which the height of the
   surface is specified by f, and the shading is specified by s.

ContourPlot      ListPlot3D       Plot3Matrix      PlotPoints
DensityPlot      ParametricPlot   PlotDivision     PlotRange
ListContourPlot  ParametricPlot3D PlotJoined       PlotRegion
ListDensityPlot  Plot             PlotLabel        PlotStyle
ListPlot         Plot3D

(* Solve[{(y == m*x+b /. {x -> (93.99703594268375+87.15785728384833)/2, y -> 0}), *)
(* (y == m*x+b /. {x -> (44.631477340644885+37.789010417682064)/2, y -> 120})}, {m, b}] *)

(* Out[105]= {{m -> -2.43076, b -> 220.172}} *)

(* Solve[y == m*x+b /. Out[105], x] *)

(* Out[107]= {{x -> -0.411393 (-220.172 + y)}} *)

jimlaura = PDF[NormalDistribution[-0.411393 (-220.172 + y), (44.631477340644885-37.789010417682064)], x]/0.0583034;
rich = PDF[NormalDistribution[83.5, 3], y]/0.132981;

(* DensityPlot[jimlaura*rich, {x, 41, 71}, {y, 68, 98} *)
(* 	    , PlotPoints -> 50 *)
(* 	    , Mesh -> False *)
(* 	    , PlotRange -> {0, 1} *)
(* 	   ]; *)

superplot = ContourPlot[jimlaura*rich, {x, centroid[[1]]-25, centroid[[1]]+25}, {y, centroid[[2]]-12, centroid[[2]]+12}
	    , PlotPoints -> 100
	    , PlotRange -> {0, 1}
	    , ColorFunction -> 
	    (If[#<1-0.9974, GrayLevel[1],
		If[#<1-0.9546, RGBColor[0.9,1,0.9],
		   If[#<1-0.68269, RGBColor[0.6,1,0.6],
		      RGBColor[0.3,1,0.3]]]]&)
	    , Contours -> {1-0.682689, 1-0.9545, 1-0.9973}
			, Frame -> False
	   ];

(* yes, they're defined backward *)
onesigma = {{100.8417011282455, 0}, {51.47467934699117, 120}, {30.945993217899755, 120}, {80.31362956315975, 0}, {100.8417011282455, 0}};
twosigma = {{97.41943716044604, 0}, {48.053315099264736, 120}, {34.367419171146416, 120}, {83.73551760279634, 0}, {97.41943716044604, 0}};
threesigma = {{93.99703594268375, 0}, {44.631477340644885, 120}, {37.789010417682064, 120}, {87.15785728384833, 0}, {93.99703594268375, 0}};

richone = {{0, 83.5+3}, {120, 83.5+3}, {120, 83.5-3}, {0, 83.5-3}, {0, 83.5+3}};
richtwo = {{0, 83.5+2*3}, {120, 83.5+2*3}, {120, 83.5-2*3}, {0, 83.5-2*3}, {0, 83.5+2*3}};
richthree = {{0, 83.5+3*3}, {120, 83.5+3*3}, {120, 83.5-3*3}, {0, 83.5-3*3}, {0, 83.5+3*3}};

centroid = {56.2, 83.5};
Display["workplot.eps", Show[Graphics[{
    RGBColor[0.9,0.9,1], Polygon[onesigma], GrayLevel[0], Line[onesigma],
    RGBColor[0.6,0.6,1], Polygon[twosigma], GrayLevel[0], Line[twosigma],
    RGBColor[0.3,0.3,1], Polygon[threesigma], GrayLevel[0], Line[threesigma],
    RGBColor[1,0.9,0.9], Polygon[richthree], GrayLevel[0], Line[richthree],
    RGBColor[0.9,0.7,0.6], Polygon[richtwo], GrayLevel[0], Line[richtwo],
    RGBColor[0.85,0.65,0.3], Polygon[richone], GrayLevel[0], Line[richone],
    Line[{centroid + {-5, 0}, centroid + {5, 0}}],
    Line[{centroid + {0, -5}, centroid + {0, 5}}]
              }], superplot
     , FrameLabel -> {"n1n3 cross-section (fb)", "n2n3 cross-section (fb)"}
     , PlotRange -> {{0, 120}, {0, 120}}
     , Frame -> True
     , AspectRatio -> 1
     , ImageSize -> 72*4
    ], "EPS"];


