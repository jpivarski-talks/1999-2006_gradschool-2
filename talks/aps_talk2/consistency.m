<< Graphics`MultipleListPlot`

y1sdata = { 
    { 0.0200072, 0.0850719 },
    { -0.183287, 0.088575 },
    { 0.166648, 0.0796278 },
    { -0.0438407, 0.16944 },
    { 0.0415141, 0.134948 },
    { -0.321401, 0.214527 },
    { 0.452919, 0.236725 }
	  };

y2sdata = {
    { 0.11013, 0.0834007 }
	  };

y3sdata = {
    { -0.393052, 0.315531 },
    { 0.128763, 0.28571 },
    { 0.490961, 0.287183 },
    { 0.167204, 0.270426 },
    { -0.0790822, 0.248123 },
    { -0.27218, 0.291859 }
	  };

<< Statistics`ContinuousDistributions`

i = 0;
alldata = Join[ y1sdata, y2sdata, y3sdata ];
wrms = Sqrt[ Plus @@ ( (#[[1]]^2/#[[2]]^2)& /@ alldata ) / 
	     Plus @@ ( (1/#[[2]]^2)& /@ alldata ) * Length[alldata] / (Length[alldata]-1) ];
moment2 = Sqrt[ Plus @@ ( (#[[1]]^2 + #[[2]]^2 )& /@ alldata ) / Length[alldata] ];
Show[ 
    Graphics[{
(*	GrayLevel[0.95]
	, Rectangle[{-moment2,-23},{moment2,1}] *)
	GrayLevel[0.9]
	, Rectangle[{-wrms,-22.99},{wrms,1}]
	, GrayLevel[0]
	, Line[{{0,-23},{0,1}}]
	     }],
    MultipleListPlot[
	{ { #[[1]], i-- }, ErrorBar[#[[2]],0] }& /@ y3sdata
	, DisplayFunction -> Identity
		    ],
    MultipleListPlot[
	{ { #[[1]], i-- -1 }, ErrorBar[#[[2]],0] }& /@ y1sdata
	, DisplayFunction -> Identity
		    ],
    MultipleListPlot[
	{ { #[[1]], i-- -2 }, ErrorBar[#[[2]],0] }& /@ y2sdata
	, DisplayFunction -> Identity
		    ],
    Plot[ Plus @@ ( PDF[NormalDistribution[#[[1]],#[[2]]],x]& /@
		    alldata ) / (22/5) - 23
	  , {x,-1,1}
	  , DisplayFunction -> Identity
	],
    Graphics[{
	Dashing[{0.02,0.02}]
	, Line[{{-1,-6},{1,-6}}], Line[{{-1,-14},{1,-14}}], Line[{{-1,-16},{1,-16}}]
	, Text["Y(3s)", {-0.75,-2.5}]
	, Text["Y(1s)", {-0.75,-10}]
	, Text["Y(2s)", {-0.75,-15}]
	, Text["weighted RMS   ", {0.6,-17}]
	, Text["   = 0.18 MeV", {0.6,-17.5}]
	     }]
    , Frame -> True
    , FrameTicks -> {True,False,False,False}
    , FrameLabel -> {"Energy Calibration Drift (MeV)","","",""}
    , Axes -> True
    , AxesOrigin -> {0,-23}
    , AspectRatio -> 2
    , ImageSize -> 72 * 3.5
    , DisplayFunction -> (Display["all_consistency.eps",#,"EPS"]&)
    ];

