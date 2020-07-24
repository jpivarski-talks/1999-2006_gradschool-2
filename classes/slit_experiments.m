distToScreen[holex_] := Sqrt[D^2 + (x-holex)^2];
amplitudeFromHole[holex_] := Sin[t + distToScreen[holex]]/distToScreen[holex]^2;
twoslits = Integrate[(amplitudeFromHole[-10] +
		      amplitudeFromHole[10])^2 /. D -> 1000, {t, 0, 2*Pi}];
fourslits = Integrate[(amplitudeFromHole[-10-q] +
		       amplitudeFromHole[-10] +
		       amplitudeFromHole[10] +
		       amplitudeFromHole[10+q])^2 /. D -> 1000, {t, 0, 2*Pi}];

fs = fourslits /. q -> 5;
Plot[twoslits, {x, -2000, 2000},
     PlotRange -> {0, 1.5*10^-11}, PlotPoints -> 1000];
Plot[fourslits, {x, -2000, 2000},
     PlotRange -> {0, 6*10^-11}, PlotPoints -> 1000];

fs = fourslits /. q -> 5;
Plot[{twoslits, fs}, {x, -2000, 2000},
     PlotRange -> {0, 6*10^-11}, PlotPoints -> 1000,
     PlotStyle -> {RGBColor[0,0,1], RGBColor[1,0,0]}];
