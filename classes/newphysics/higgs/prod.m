xVals = Range[212, 500, (500-212)/100];
yVals = ReadList["prod_zh.txt", Real];
xy = Table[{xVals[[i]], yVals[[i]]}, {i, 1, Length[yVals]}];

ListPlot[xy,
	 Axes -> False,
	 Frame -> True,
	 FrameLabel -> {"e+e- Center of Mass Energy",
			"Cross-Section in pb",
			"e+e- to Z Higgs", None},
	 PlotJoined -> True,
	 DisplayFunction -> (Display["prod_zh.eps", #, "EPS"]&)
	];
