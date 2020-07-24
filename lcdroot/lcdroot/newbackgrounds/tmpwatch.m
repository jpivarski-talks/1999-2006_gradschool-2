<< Statistics`ContinuousDistributions`;

<< /home/mccann/lcdroot/newbackgrounds/fake3_13.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_14.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_15.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_16.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_17.mx;

<< /home/mccann/lcdroot/newbackgrounds/fake3_00.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_01.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_02.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_03.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_04.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_05.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_06.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_07.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_08.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_09.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_10.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_11.mx;
<< /home/mccann/lcdroot/newbackgrounds/fake3_12.mx;
bowl18 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl19 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl20 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl21 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl22 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl23 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl24 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl25 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl26 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl27 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl28 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl29 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl30 = Table[30*ndof, {mc, 159.417 - 15, 159.417 + 15, 1}];
bowl = {bowl00, bowl01, bowl02, bowl03, bowl04, bowl05, bowl06,
	bowl07, bowl08, bowl09, bowl10, bowl11, bowl12, bowl13,
	bowl14, bowl15, bowl16, bowl17, bowl18, bowl19, bowl20,
	bowl21, bowl22, bowl23, bowl24, bowl25, bowl26, bowl27,
	bowl28, bowl29, bowl30};
mini = Min[Flatten[bowl]];
ndof = 966;

Solve[CDF[ChiSquareDistribution[ndof],x] == 0.68269, x]

Solve[CDF[ChiSquareDistribution[ndof],x] == 0.95, x]

Solve[CDF[ChiSquareDistribution[ndof],x] == 0.99, x]

ListContourPlot[bowl,
		Frame -> True,
		FrameLabel -> {"Mass of chargino (GeV)", "Mass of LSP (GeV)", "Confidence Intervals with zeta = 0.9", None},
		PlotRange -> {Automatic, Automatic, {0, ndof*5}},
		Contours -> {990.408, 1043.57, 1075.4},
		ColorFunction -> (RGBColor[#, #, 1]&),
		FrameTicks -> {{{1, "-15"}, {6, "-10"}, {11, "-5"}, {16, "0"}, {21, "+5"}, {26, "+10"}, {31, "+15"}},
			       {{1, "-15"}, {6, "-10"}, {11, "-5"}, {16, "0"}, {21, "+5"}, {26, "+10"}, {31, "+15"}}, None, None}
		, ContourSmoothing -> False
	       ];

