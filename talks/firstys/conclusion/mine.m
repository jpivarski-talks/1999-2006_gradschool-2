<< Graphics`MultipleListPlot`

f[x_] := Erf[x/100]

(0.447746+0.43625400000000003)/2

0.442 * 0.6/100

Out[9]= 0.002652

{0.442 + 0.002652,
0.442 - 0.002652}

Out[10]= {0.444652, 0.439348}

Show[
    MultipleListPlot[
	{{{{f[15.8], 0.650618488788 * 0.890823828845}, ErrorBar[0.0265962315525 * 0.890823828845]},
	 {{f[32.8], 0.64529200528 * 0.890823828845}, ErrorBar[0.0259500723162 * 0.890823828845]},
	 {{f[84.0], 0.747903901394 * 0.890823828845}, ErrorBar[0.0203592119095 * 0.890823828845]},
	 {{f[14.1], 0.654511894343 * 0.890823828845}, ErrorBar[0.0457400346664 * 0.890823828845]},
	 {{1., 0.896161708865 * 0.890823828845}, ErrorBar[0.0148523010462 * 0.890823828845]}}},
	SymbolStyle -> {RGBColor[0,0,0]},
	DisplayFunction -> Identity
		    ],
    Graphics[
	{Thickness[0.002],
	 RGBColor[1, 0, 0],
	 Line[{Offset[{3.0, 0}, {f[2.0], 0.444652 * 0.890823828845}],
	       Offset[{-3.0, 0}, {f[2.0], 0.444652 * 0.890823828845}]}],
	 Line[{Offset[{3.0, 0}, {f[2.0],  0.439348* 0.890823828845}],
	       Offset[{-3.0, 0}, {f[2.0], 0.439348 * 0.890823828845}]}],
	 Thickness[0.002],
	 RGBColor[0, 0, 1],
	 Line[{{f[2.0], 0.4704668162545 * 0.890823828845}, {f[2.0], 0.4135331837455 * 0.890823828845}}], 
	 Line[{Offset[{1.5, 0}, {f[2.0], 0.4704668162545 * 0.890823828845}], 
	       Offset[{-1.5, 0}, {f[2.0], 0.4704668162545 * 0.890823828845}]}], 
	 Line[{Offset[{1.5, 0}, {f[2.0], 0.4135331837455 * 0.890823828845}], 
	       Offset[{-1.5, 0}, {f[2.0], 0.4135331837455 * 0.890823828845}]}],
	 Thickness[0.0001],
	 PointSize[0.01], 
	 Polygon[{Offset[0.5*{-1.875, 0}, {f[2.0], 0.442 * 0.890823828845}], 
		  Offset[0.5*{0, 2.5}, {f[2.0], 0.442 * 0.890823828845}],
		  Offset[0.5*{1.875, 0}, {f[2.0], 0.442 * 0.890823828845}], 
		  Offset[0.5*{0, -2.5}, {f[2.0], 0.442 * 0.890823828845}],
		  Offset[0.5*{-1.875, 0}, {f[2.0], 0.442 * 0.890823828845}]}]
	}
		 ],
    Axes -> False,
    Frame -> True,
(*    FrameLabel -> {"Mass of Light Quarks in MeV", "Gamma_ee(2S)/Gamma_ee(1S)"}, *)
    FrameTicks -> {Join[{f[#], "", {0.005, 0}}& /@ Range[0, 300, 2],
			{f[#], "", {0.01, 0}}& /@ Range[0, 300, 10],
			{f[#], ToString[#], {0.01, 0}}& /@ {0, 10, 20, 30, 40, 50, 60, 70, 80, 100},
			{{1, "Infinity", {0.01, 0}}}],
		   Join[{#, "", {0.005, 0}}& /@ Range[0.3, 0.9, 0.02],
			{#, ToString[#], {0.01, 0}}& /@ Range[0.3, 0.9, 0.1]
		       ], None, None},
    PlotRange -> {{-0.05, 1.05}, {0.29, 0.83}},
    AspectRatio -> 1/3,
    ImageSize -> 4 * 72,
(*    DisplayFunction -> $DisplayFunction *)
    DisplayFunction -> (Display["mine.eps", #, "EPS"]&)
    ];



(0.4704668162545 - 0.4135331837455) / (0.4704668162545 + 0.4135331837455)

Out[121]= 0.0644046

Out[120]= 0.128809

Out[119]= 0.0569336

0.0284668162545 / 0.442

Out[122]= 0.0644046

Exit

[Mathematica finished.]

[Mathematica finished.]
