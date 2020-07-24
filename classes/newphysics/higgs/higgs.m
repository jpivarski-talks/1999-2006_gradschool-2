This was done in SM, Unitary Gauge.
The x axis is always from 60 to 600 in 101 points.
Y axis is always width in GeV.

total = ReadList["total.txt", Real];
mupair = ReadList["mupair.txt", Real];
taupair = ReadList["taupair.txt", Real];
spair = ReadList["s_sbar.txt", Real];
cpair = ReadList["c_cbar.txt", Real];
bpair = ReadList["b_bbar.txt", Real];
tpair = ReadList["t_tbar.txt", Real];
wpair = ReadList["ww.txt", Real];
zpair = ReadList["zz.txt", Real];


PseudoLog[x_] := If[x == 0, -100, Log[10, x]];
xLabel = Range[60, 600, (600-60)/100];
gmupair = Table[{xLabel[[i]], PseudoLog[mupair[[i]]]}, {i, 1, Length[total]}];
gtaupair = Table[{xLabel[[i]], PseudoLog[taupair[[i]]]}, {i, 1, Length[total]}];
gspair = Table[{xLabel[[i]], PseudoLog[spair[[i]]]}, {i, 1, Length[total]}];
gcpair = Table[{xLabel[[i]], PseudoLog[cpair[[i]]]}, {i, 1, Length[total]}];
gbpair = Table[{xLabel[[i]], PseudoLog[bpair[[i]]]}, {i, 1, Length[total]}];
gtpair = Table[{xLabel[[i]], PseudoLog[tpair[[i]]]}, {i, 1, Length[total]}];
gwpair = Table[{xLabel[[i]], PseudoLog[wpair[[i]]]}, {i, 1, Length[total]}];
gzpair = Table[{xLabel[[i]], PseudoLog[zpair[[i]]]}, {i, 1, Length[total]}];
gtotal = Table[{xLabel[[i]], PseudoLog[total[[i]]]}, {i, 1, Length[total]}];

BoxWord[word_, point_, style_, space_] :=
    {RGBColor[1,1,1],
     Rectangle[{point[[1]]-space, point[[2]]-0.15}, {point[[1]]+space, point[[2]]+0.15}],
     style,
     Text[word, point]};
Show[
    ListPlot[gmupair, PlotJoined -> True, PlotStyle -> {Dashing[{0.01, 0.01}], RGBColor[0,0,1]}, DisplayFunction -> Identity],
    ListPlot[gtaupair, PlotJoined -> True, PlotStyle -> {RGBColor[0,0,1]}, DisplayFunction -> Identity],
    ListPlot[gspair, PlotJoined -> True, PlotStyle -> {Dashing[{0.005, 0.005}], RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[gcpair, PlotJoined -> True, PlotStyle -> {Dashing[{0.0075, 0.0075}], RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[gbpair, PlotJoined -> True, PlotStyle -> {Dashing[{0.01, 0.01}], RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[gtpair, PlotJoined -> True, PlotStyle -> {RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[gwpair, PlotJoined -> True, PlotStyle -> {Dashing[{0.01, 0.01}]}, DisplayFunction -> Identity],
    ListPlot[gzpair, PlotJoined -> True, PlotStyle -> {}, DisplayFunction -> Identity],
    ListPlot[gtotal, PlotJoined -> True, PlotStyle -> {Thickness[0.005]}, DisplayFunction -> Identity],
    Graphics[{
 	BoxWord["mu", gmupair[[40]], RGBColor[0,0,1], 10],
 	BoxWord["tau", gtaupair[[40]], RGBColor[0,0,1], 15],
 	BoxWord["ss", gspair[[40]], RGBColor[1,0,0], 10],
 	BoxWord["cc", gcpair[[40]], RGBColor[1,0,0], 10],
 	BoxWord["bb", gbpair[[40]], RGBColor[1,0,0], 10],
 	BoxWord["tt", gtpair[[60]], RGBColor[1,0,0], 20],
 	BoxWord["Z Z", gzpair[[40]], RGBColor[0,0,0], 15],
 	BoxWord["", gwpair[[45]] + {17, 0}, RGBColor[0,0,0], 16],
 	BoxWord["W+ W-", gwpair[[45]] + {20, 0}, RGBColor[0,0,0], 16],
 	BoxWord["Total", gtotal[[50]] + {0, 0.3}, RGBColor[0,0,0], 0]
	     }],
    AspectRatio -> 1.3,
    PlotRange -> {{100, 400}, {-7.1, 2.1}},
    Axes -> False,
    Frame -> True,
    FrameLabel -> {"Higgs Mass (GeV)", "Partial Width", "", ""},
    FrameTicks -> {Automatic, 
		   {{-7, "100 eV"}, {-6, "1 keV"}, {-5, "10 keV"}, {-4, "100 keV"}, {-3, "1 MeV"}, 
		    {-2, "10 MeV"}, {-1, "100 MeV"}, {0, "1 GeV"}, {1, "10 GeV"}, {2, "100 GeV"}},
		   None, None},
(*    DisplayFunction -> $DisplayFunction *)
    ImageSize -> 72*5,
    DisplayFunction -> (Display["higgs_gamma.eps", #, "EPS"]&)
    ];






(* This checks out okay. *)
total - (mupair + taupair + spair + cpair + bpair + tpair + wpair + zpair)

PseudoLog[x_] := If[x == 0, -6, Log[10, x]];
xLabel = Range[60, 600, (600-60)/100];
bmupair = Table[{xLabel[[i]], PseudoLog[mupair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
btaupair = Table[{xLabel[[i]], PseudoLog[taupair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
bspair = Table[{xLabel[[i]], PseudoLog[spair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
bcpair = Table[{xLabel[[i]], PseudoLog[cpair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
bbpair = Table[{xLabel[[i]], PseudoLog[bpair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
btpair = Table[{xLabel[[i]], PseudoLog[tpair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
bwpair = Table[{xLabel[[i]], PseudoLog[wpair[[i]]/total[[i]]]}, {i, 1, Length[total]}];
bzpair = Table[{xLabel[[i]], PseudoLog[zpair[[i]]/total[[i]]]}, {i, 1, Length[total]}];

BoxWord[word_, point_, style_, space_] :=
    {RGBColor[1,1,1],
     Rectangle[{point[[1]]-space, point[[2]]-0.08}, {point[[1]]+space, point[[2]]+0.08}],
     style,
     Text[word, point]};
Show[
    ListPlot[bmupair, PlotJoined -> True, PlotStyle -> {Dashing[{0.01, 0.01}], RGBColor[0,0,1]}, DisplayFunction -> Identity],
    ListPlot[btaupair, PlotJoined -> True, PlotStyle -> {RGBColor[0,0,1]}, DisplayFunction -> Identity],
    ListPlot[bspair, PlotJoined -> True, PlotStyle -> {Dashing[{0.005, 0.005}], RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[bcpair, PlotJoined -> True, PlotStyle -> {Dashing[{0.0075, 0.0075}], RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[bbpair, PlotJoined -> True, PlotStyle -> {Dashing[{0.01, 0.01}], RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[btpair, PlotJoined -> True, PlotStyle -> {RGBColor[1,0,0]}, DisplayFunction -> Identity],
    ListPlot[bwpair, PlotJoined -> True, PlotStyle -> {Dashing[{0.01, 0.01}]}, DisplayFunction -> Identity],
    ListPlot[bzpair, PlotJoined -> True, PlotStyle -> {}, DisplayFunction -> Identity],
    Graphics[{
	BoxWord["mu", bmupair[[10]], RGBColor[0,0,1], 20],
	BoxWord["tau", btaupair[[10]], RGBColor[0,0,1], 30],
	BoxWord["ss", bspair[[10]], RGBColor[1,0,0], 20],
	BoxWord["cc", bcpair[[10]], RGBColor[1,0,0], 20],
	BoxWord["bb", bbpair[[10]], RGBColor[1,0,0], 20],
	BoxWord["tau", btaupair[[70]], RGBColor[0,0,1], 40],
	BoxWord["cc", bcpair[[80]], RGBColor[1,0,0], 25],
	BoxWord["bb", bbpair[[80]], RGBColor[1,0,0], 25],
	BoxWord["tt", btpair[[80]], RGBColor[1,0,0], 30],
	BoxWord["W+W-", bwpair[[90]], RGBColor[0,0,0], 40],
	BoxWord["Z Z", bzpair[[90]], RGBColor[0,0,0], 30]
	     }],
    AspectRatio -> 0.9,
    PlotRange -> {{60, 600}, {-5.1, 0.1}},
    Axes -> False,
    Frame -> True,
    FrameLabel -> {"Higgs Mass (GeV)", "Branching Ratio", "", ""},
    FrameTicks -> {Automatic, {#, N[10^#]}& /@ Range[-5, 0], None, None},
(*    DisplayFunction -> $DisplayFunction *)
    ImageSize -> 72*4,
    DisplayFunction -> (Display["higgs.eps", #, "EPS"]&)
    ];

