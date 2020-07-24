<< Graphics`Graphics`

bw[x_,mean_,gam_] := (gam/2) / Pi / ( (x - mean)^2 + (gam/2)^2 );

hxc[x_] := 90*(0.248*bw[x,10580,14] + 0.31*bw[x,10865,110] + 0.130*bw[x,11019,79])
    + 1.5*10500^2/x^2;

hxcsub[x_] := 90*(0.248*bw[x,10580,14] + 0.31*bw[x,10865,110] + 0.130*bw[x,11019,79]);

Plot[ hxc[x], {x, 10500, 11200}, PlotRange -> {0,2.5} ];

Show[
    Graphics[{
	GrayLevel[0.75],
	Polygon[Join[ Table[{x,hxcsub[x]}, {x,10530,10558,0.1}],
		      {{10558,0},{10530,0}}
		    ]],
	GrayLevel[0],
	Dashing[{0.01,0.01}],
	Line[{{10558,0},{10558,1}}],
	Dashing[{}],
	Line[{{10530,0.2},{10530,0},{10560,0}}]
	     }]
    , Plot[hxcsub[x], {x,10530,10580}, DisplayFunction -> Identity]
    , Frame -> True
    , FrameLabel -> {"Energy in MeV",
		     "Hadronic Cross-Section (nb)", None, None}
    , FrameStyle -> {{GrayLevel[0]},{GrayLevel[0]},{GrayLevel[1]},{GrayLevel[1]}}
    , FrameTicks -> {Automatic, Automatic, None, None}
    , PlotRange -> {{10529.99999,10580},{-0.000001,1}}
    , ImageSize -> 5*72
    , DisplayFunction -> (Display["bb_thresh_plot.eps",#,"EPS"]&)
(*    , DisplayFunction -> $DisplayFunction *)
    ];



Show[
    Graphics[{
	     }]
    , DisplayFunction -> $DisplayFunction
    ];



    Plot[hxcsub[x], {x,10530,10580}
	 , Frame -> True
	 , PlotStyle -> {Thickness[0],}
	 , FrameLabel -> {"Energy in MeV",
			  "Hadronic Cross-Section (nb)", None, None}
	 , FrameStyle -> {{GrayLevel[0]},{GrayLevel[0]},{GrayLevel[1]},{GrayLevel[1]}}
	 , FrameTicks -> {Automatic, Automatic, None, None}
	 , PlotRange -> {-0.000001,1}
	];


Show[
    Plot[ hxcsub[x], {x, 10500, 11200}
	  , Frame -> True
	  , FrameLabel -> {"Energy in MeV",
			   "Hadronic Cross-Section (nb)", None, None}
	  , FrameStyle -> {{GrayLevel[0]},{GrayLevel[0]},{GrayLevel[1]},{GrayLevel[1]}}
	  , FrameTicks -> {Automatic, Automatic, None, None}
	  , PlotLabel -> "Widths and Masses of Upsilon 4S, 10860 and 11020"
	  , DisplayFunction -> Identity ]
    , Graphics[{
	Text["U(4S)", {10650,0.3}],
	Text["U(10860)", {10865,0.2}],
	Text["U(11020)", {11019,0.15}],
	Text["another", {10700,0.075}],
	Text["peak???", {10700,0.050}]
	       }]
    , AspectRatio -> 1
    , ImageSize -> 5*72
    , DisplayFunction -> (Display["theopeaks.eps",#,"EPS"]&)
(*    , DisplayFunction -> $DisplayFunction *)
    ];

sighxc[x_,lumi_] := hxc[x] * Sqrt[1/hxc[x]/lumi + 0.0759/lumi];

Plot[ sighxc[x,100], {x, 10500, 11200}, PlotRange -> {0,sighxc[10580,10]} ];


sighxc[10580,10]/sighxc[10500,10]

Out[35]= 1.32815

sighxc[10580,100]/sighxc[10500,100]

Out[36]= 1.32815

sighxc[10580,1000]/sighxc[10500,1000]

Out[37]= 1.32815

sighxc[10580,10000]/sighxc[10500,10000]

Out[38]= 1.32815

sighxc[10580,100000]/sighxc[10500,100000]

Out[39]= 1.32815

sighxc[10580,lumi]/sighxc[10500,lumi]

Out[40]= 1.32815

sighxc[10500,lumi]

                      1
Out[41]= 1.2982 Sqrt[----]
                     lumi

Plot[hxcsub[x], {x, 10500, 11200}, PlotRange -> All];

hxcsub[10580]

Out[46]= 1.02151

hxcsub[10865]

Out[47]= 0.167902

hxcsub[11019]

Out[48]= 0.112808


1.2982^2 / 1



2*( (((1/#) + 0.0759) / (x/100)^2)& /@ {3} ) / 1000 /. x->2

Out[284]= {2.04617}

Out[283]= {32.7387}









uk = 2*( (((1/#) + 0.0759) / (x/100)^2)& /@ {1.02151, 0.167902, 0.112808} ) / 1000

           21.0969  120.635  178.81
Out[278]= {-------, -------, ------}
              2        2        2
             x        x        x

           10.5484  60.3176  89.4052
Out[262]= {-------, -------, -------}
              2        2        2
             x        x        x

uk[[3]] /. x -> 30

Out[269]= 0.0993391

Out[264]= 0.0670195



uk = { 450 * (3.2/x)^2, 45000 * (0.95/x)^2, 45000 * (1.88/x)^2 }

           4608.  40612.5  159048.
Out[316]= {-----, -------, -------}
             2       2        2
            x       x        x


		    {{0.0001,0.0001}, {0.0002,""}, {0.0003,""}, {0.0004,""}, {0.0005,""}, {0.0006,""}, {0.0007,""}, {0.0008,""}, {0.0009,""},
		     {0.001,0.001}, {0.002,""}, {0.003,""}, {0.004,""}, {0.005,""}, {0.006,""}, {0.007,""}, {0.008,""}, {0.009,""},
		     {0.01,0.01}, {0.02,""}, {0.03,""}, {0.04,""}, {0.05,""}, {0.06,""}, {0.07,""}, {0.08,""}, {0.09,""},




Show[
    LogLogPlot[ {uk[[1]], uk[[2]], uk[[3]]}, {x, 0.004*100, 0.3*100}
		, PlotStyle -> {Dashing[{}], Dashing[{0.04,0.04}], Dashing[{0.01,0.01}]}
		, PlotRange -> {{0.004*100,0.8*100},{0.09,1000000}}
		, Frame -> True
		, FrameLabel -> {"Desired Statistical Precision (percent)",
				 "Needed Luminosity (pb^-1)", None, None}
		, FrameStyle -> {{GrayLevel[0]},{GrayLevel[0]},{GrayLevel[1]},{GrayLevel[1]}}
		, FrameTicks -> {
		    {{0.5,0.5}, {0.6,""}, {0.7,""}, {0.8,""}, {0.9,""},
		     {1,1}, {2,2}, {3,""}, {4,""}, {5,5}, {6,""}, {7,""}, {8,""}, {9,""},
		     {10,10}, {20,20}, {30,""}, {40,""}, {50,50}, {60,""}, {70,""}, {80,""}, {90,""}
		    },
		    {{0.1,0.1}, {0.2,""}, {0.3,""}, {0.4,""}, {0.5,""}, {0.6,""}, {0.7,""}, {0.8,""}, {0.9,""},
		     {1,1}, {2,""}, {3,""}, {4,""}, {5,""}, {6,""}, {7,""}, {8,""}, {9,""},
		     {10,10}, {20,""}, {30,""}, {40,""}, {50,""}, {60,""}, {70,""}, {80,""}, {90,""},
		     {100,100}, {200,""}, {300,""}, {400,""}, {500,""}, {600,""}, {700,""}, {800,""}, {900,""},
		     {1000,"1,000"}, {2000,""}, {3000,""}, {4000,""}, {5000,""}, {6000,""}, {7000,""}, {8000,""}, {9000,""},
		     {10000,"10,000"}, {20000,""}, {30000,""}, {40000,""}, {50000,""}, {60000,""}, {70000,""}, {80000,""}, {90000,""},
		     {100000,"100,000"}, {200000,""}, {300000,""}, {400000,""}, {500000,""}, {600000,""}, {700000,""}, {800000,""}, {900000,""},
		     {1000000,"1,000,000"}
		    },
		    None, None}
		, DisplayFunction -> Identity
	      ],
    Graphics[{
	Text["U(4S)",{Log[10,0.35*100], Log[10, uk[[1]] /. x -> 0.3*100]}, {-1,0}],
	Text["U(10860)",{Log[10,0.35*100], Log[10, uk[[2]] /. x -> 0.3*100]}, {-1,0}],
	Text["U(11020)",{Log[10,0.35*100], Log[10, uk[[3]] /. x -> 0.3*100]}, {-1,0}],
	GrayLevel[0.5],
	Line[Log[10,#]& /@ {{1,0.09},{1,800000}}],
	Line[Log[10,#]& /@ {{5,0.09},{5,50000}}],
	Line[Log[10,#]& /@ {{13,0.09},{13,uk[[1]] /. x -> 13}}],
	Line[Log[10,#]& /@ {{18,0.09},{18,uk[[1]] /. x -> 18}}],
	Line[Log[10,#]& /@ {{19,0.09},{19,uk[[2]] /. x -> 19}}],
	Line[Log[10,#]& /@ {{26,0.09},{26,uk[[3]] /. x -> 26}}],
	GrayLevel[0],
	Point[Log[10,#]& /@ {13,uk[[1]] /. x -> 13}],
	Point[Log[10,#]& /@ {18,uk[[1]] /. x -> 18}],
	Point[Log[10,#]& /@ {19,uk[[2]] /. x -> 19}],
	Point[Log[10,#]& /@ {26,uk[[3]] /. x -> 26}],
	Text["Luminosity Systematic", (Log[10,#]& /@ {1.1, 800000})-{0,0.2}, {-1,0}],
	Text["Maximum Fit Function", (Log[10,#]& /@ {5.5, 50000})-{0,0.2}, {-1,0}],
	Text["Systematic", (Log[10,#]& /@ {5.5, 12000})-{0,0.1}, {-1,0}],
	Text["Current best", Log[10,#]& /@ {40, 0.0016*1000}, {0,0}],
	Text["measurements", Log[10,#]& /@ {40, 0.0005*1000}, {0,0}]
	     }]
    , ImageSize -> 5*72
    , DisplayFunction -> (Display["cleo_lumi_needed.eps",#,"EPS"]&)
(*     , DisplayFunction -> $DisplayFunction *)
    ];


kf = t*f^(t-1)*(1 + alpha/Pi*(Pi^(2/3) - 1/2) + (3/4)*t
		- t^2/24 * (1/2 * Log[s/me^2] + 2*Pi^2 - 37/4))
    - t*(1 - f/2)
    + t^2/8 * (4 * (2-f) * Log[1/f]
	       - ((1 + 3*(1-f)^2) / f) * Log[1 - f] - 6 + f)
    /. {t -> 0.04, f -> x/10580, s -> 10580, me -> 0.511, alpha -> 1/137};

hxc[x_] := 90*(0.248*bw[x,10580,14] + 0.31*bw[x,10865,110] + 0.130*bw[x,11019,79])


bw[x_,mean_,gam_] := (gam/2) / Pi / ( (x - mean)^2 + (gam/2)^2 );


Show[
    GraphicsArray[{
	Plot[ If[x>10558,1.02/0.03*bw[x,10580,14/6*^-6*Sqrt[x^2 - 10558^2]/x^2],0], {x, 10520, 10700}
	      , Axes -> False
	      , Frame -> True
	      , FrameLabel -> {"Beam Energy w (MeV)", "Hadronic Cross-section (nb)", "Hadronic Cross-Section", None}
	      , FrameTicks -> {Table[i, {i,10520,10700,40}], Automatic, None, None}
	      , AspectRatio -> 1
	      , DisplayFunction -> Identity
	    ],
	Plot[ If[x>0,kf,0], {x, -90, 90}
	      , Axes -> False
	      , Frame -> True
	      , FrameLabel -> {"Beam Energy w (MeV)", "(Unitless Integration Kernel)", "Initial-State Radiation Tail", None}
	      , AspectRatio -> 1
	      , DisplayFunction -> Identity
	    ],
	Plot[ Exp[-x^2/2/4^2]/Sqrt[2 Pi]/4, {x, -90, 90}
	      , Axes -> False
	      , PlotRange -> All
	      , Frame -> True
	      , FrameLabel -> {"Beam Energy w (MeV)", "(Unitless Integration Kernel)", "Beam-Energy Spread", None}
	      , AspectRatio -> 1
	      , DisplayFunction -> Identity
	    ]
		  }]
    , ImageSize -> 10.5*72
    , DisplayFunction -> (Display["three_functions.eps",#,"EPS"]&)
(*    , DisplayFunction -> $DisplayFunction *)
    ];


1.02/0.03*bw[10558,10580,0.044]

Out[234]= 0.000491933


Plot[ If[x>10558, 14/6*^-6*Sqrt[x^2 - 10558^2]/x^2, 0], {x, 10520, 10700} ];


Plot[ If[x>10558,1.02/0.03*bw[x,10580,22/6*^-6*Sqrt[x^2 - 10558^2]/x^2],0], {x, 10520, 10700} ];

D[ Sqrt[x^2 - (2 mb)^2]/x^2, x ] // Simplify /. x -> mups

                   2    2
               8 mb  - x
Out[246]= --------------------
           3           2    2
          x  Sqrt[-4 mb  + x ]







Show[
    LogLogListPlot[{ {45,160}, {4500,18}, {450000,3.2}, {45000000,3.2} }, DisplayFunction -> Identity]
    , Plot[-x/2+3, {x,Log[10,45],Log[10,450000]}, DisplayFunction -> Identity]
    , Frame -> True
    , FrameTicks -> {Automatic, Automatic}
    , DisplayFunction -> $DisplayFunction
    ];

Show[
    LogLogListPlot[{ {45,160}, {4500,18}, {450000,3.2}}, DisplayFunction -> Identity]
    , LogLogPlot[3.2*(450000/x)^(1/2), {x,45,450000}, DisplayFunction -> Identity]
    , DisplayFunction -> $DisplayFunction
    ];

Show[
    LogLogListPlot[{ {4500,93}, {450000,9.7}, {45000000,0.95} }, DisplayFunction -> Identity]
    , LogLogPlot[0.95*(45000000/x)^(1/2), {x,45,45000000}, DisplayFunction -> Identity]
    , DisplayFunction -> $DisplayFunction
    ];


Exit

[Mathematica finished.]
