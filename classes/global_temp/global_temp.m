(* data comes from http://www.ldeo.columbia.edu/dees/ees/climate/labs/globaltemp/ *)

(* Since the 19th Century, surface weather stations have recorded temperatures at *)
(* various locations around the world. Only the land portions of the globe are *)
(* sampled in this way, and the density of stations is greatest in the *)
(* industrialized nations. Since about 1867, the number and distribution of *)
(* stations has been large enough to provide an adequate (though not perfect; the *)
(* sampling error is about 0.07 degrees C) sample of global surface temperature *)
(* variations from year to year. This record provides the best documentation of *)
(* recent global climate change and is at the center of the debate over *)
(* humankind's potential to modify Earth's climate. Satellites, with their global *)
(* coverage, have been recording a truer estimate of global temperature (but in *)
(* the lower troposphere, not at the surface) in recent years. However, satellite *)
(* data exist only since 1980 and are not included in this lab. *)

(* In this lab you will analyze the global temperature record from 1867 to the *)
(* present. You will evaluate long-term trends and shorter-term fluctuations, and *)
(* you will look for evidence of the impact of climate forcings and mechanisms of *)
(* natural variability on the global surface temperature. The ultimate goal is to *)
(* give you a sense of the difficulty faced by scientists in trying to predict *)
(* the future based on limited current evidence. *)

(* ------------------------------------------------------------------------------ *)

(* Reading List *)

(*    o Hansen, J., and S. Lebedeff. 1987. Global trends of measured surface air *)
(*      temperature, J. Geophys. Res. 92, 13,345-13,372. *)
(*    o Hansen, J., and S. Lebedeff. 1988. Global surface airtemperatures: Update *)
(*      through 1987. Geophys. Res. Lett. 15, 323-326. *)
(*    o Hansen, J., and H. Wilson. 1993. Commentary on the significance of global *)
(*      temperature records. Climatic Change 25, 185-191. *)
(*    o Hansen, J., H. Wilson, M. Sato, R. Ruedy, K. Shah, and E. Hansen. In *)
(*      press. Satellite and surface temperature data at odds? Climatic Change. *)
(* ------------------------------------------------------------------------------ *)

<< Statistics`DescriptiveStatistics`;
<< Graphics`MultipleListPlot`;

SetDirectory[ "/home/mccann/tmp" ];
months = Range[ 0, 11/12, 1/12 ];
raw = ReadList[ "global_temp.tsv", { Number, (* year *)
				     Number, (* jan *)
				     Number, (* feb *)
				     Number, (* mar *)
				     Number, (* apr *)
				     Number, (* may *)
				     Number, (* jun *)
				     Number, (* jul *)
				     Number, (* aug *)
				     Number, (* sep *)
				     Number, (* oct *)
				     Number, (* nov *)
				     Number, (* dec *)
				     Number, (* annual *)
				     Number, (* djf *)
				     Number, (* mam *)
				     Number, (* jja *)
				     Number, (* son *)
				     Number (* year (again) *)
				   } ];

monthbymonth = Join @@ ( Table[ {#[[1]] + months[[i]], #[[1+i]]}, {i,1,12} ]& /@ raw );
yearbyyear = { { #[[1]], Mean[ #[[Range[2,13]]] ] },
	       ErrorBar[ RootMeanSquare[ #[[Range[2,13]]]
					 - Mean[ #[[Range[2,13]]] ] ] / Sqrt[12]
		       ] }& /@ raw;

tmp = Partition[monthbymonth, 12*5];
xes = (#[[1]]& /@ #)& /@ tmp;
xmeans = N[Mean[#]]& /@ xes;
ys = (#[[2]]& /@ #)& /@ tmp;
ymeans = N[Mean[#]]& /@ ys;
yerrs = N[RootMeanSquare[#-Mean[#]]/Sqrt[60]]& /@ ys;
by5year = Table[ { { xmeans[[i]], ymeans[[i]] }, ErrorBar[ 2.46, yerrs[[i]] ] },
		 {i,1,Length[xmeans]} ];

monthbymonth = Join @@ ( Table[ {#[[1]] + months[[i]], #[[1+i]]}, {i,1,12} ]& /@ raw );

januarys = { #[[1]], #[[2]] }& /@ raw;
julys = { #[[1]] + 0.5, #[[8]] }& /@ raw;

(* Major eruptions
 1883 Krakatau        1902 Santa Maria 1968 Fernandina Island 
                                                              
 1890 Unidentified    1912 Katmai      1982 El Chichon        
                                                              
 1902 Soufriere/Pelee 1963 Agung       1991 Pinatubo          
*)

eruptions = { 1883, 1890, 1902, 1912, 1963, 1968, 1982, 1991 };

(* El-Nino Southern oscillations *)
ensos = { 1951, 1953, 1957, 1963, 1965, 1969, 1973, 1977, 1983, 1987, 1991, 1997 };

Show[ { Graphics[ { RGBColor[.5,.5,1], Dashing[{0.01,0.01}], Line[{{#,13.5},{#,16}}]& /@ eruptions } ],
	Graphics[ { RGBColor[1,.5,.5], Dashing[{0.01,0.01}], Line[{{#,13.5},{#,16}}]& /@ ensos } ],
	Graphics[ { RGBColor[0,0,1], Text["Major Volcanic Eruptions in blue",{1905,13.7}] } ],
	Graphics[ { RGBColor[1,0,0], Text["Recent El Nino Southern Oscillations in red",{1905,13.6}] } ],
	ListPlot[ monthbymonth, DisplayFunction -> Identity ]
      },
      Axes -> False, Frame -> True,
      FrameLabel -> {"Year", "Degrees Centigrade", "Globally-Averaged Temperature by Month", None},
      ImageSize -> 72 * 7,
      PlotRange -> { { 1860, 2000 }, { 13.5, 16 } },
      DisplayFunction -> ( Display["global_temp_month.eps",#,"EPS"]& )
    ];
Run[ "kill -9 `ps -fu mccann | grep psrender | grep -v grep | awk '{print $2}'`" ];

Show[ { ListPlot[ januarys, DisplayFunction -> Identity, PlotStyle -> { RGBColor[0,0,1] } ],
	ListPlot[ julys, DisplayFunction -> Identity, PlotStyle -> { RGBColor[1,0,0] } ],
	Graphics[ { RGBColor[0,0,1], Text["Januarys in blue",{1960,14}] } ],
	Graphics[ { RGBColor[1,0,0], Text["Julys in red",{1960,13.8}] } ]
      },
      Axes -> False, Frame -> True,
      FrameLabel -> {"Year", "Degrees Centigrade", "Globally-Averaged Temperature Januaries and Julys", None},
      ImageSize -> 72 * 7,
      PlotRange -> { { 1860, 2000 }, { 13.5, 16 } },
      DisplayFunction -> ( Display["global_temp_jan_jul.eps",#,"EPS"]& )
    ];
Run[ "kill -9 `ps -fu mccann | grep psrender | grep -v grep | awk '{print $2}'`" ];

Show[ { Graphics[ { RGBColor[.5,.5,1], Dashing[{0.01,0.01}], Line[{{#,13.5},{#,16}}]& /@ eruptions } ],
	Graphics[ { RGBColor[1,.5,.5], Dashing[{0.01,0.01}], Line[{{#,13.5},{#,16}}]& /@ ensos } ],
	Graphics[ { RGBColor[0,0,1], Text["Major Volcanic Eruptions in blue",{1905,13.7}] } ],
	Graphics[ { RGBColor[1,0,0], Text["Recent El Nino Southern Oscillations in red",{1905,13.6}] } ],
	MultipleListPlot[ yearbyyear, DisplayFunction -> Identity ]
      },
      Axes -> False, Frame -> True,
      FrameLabel -> {"Year", "Degrees Centigrade", "Globally-Averaged Temperature by Year", None},
      ImageSize -> 72 * 7,
      PlotRange -> { { 1860, 2000 }, { 13.5, 16 } },
      DisplayFunction -> ( Display["global_temp_year.eps",#,"EPS"]& )
    ];
Run[ "kill -9 `ps -fu mccann | grep psrender | grep -v grep | awk '{print $2}'`" ];

Show[ { Graphics[ { RGBColor[.5,.5,1], Dashing[{0.01,0.01}], Line[{{#,13.5},{#,16}}]& /@ eruptions } ],
	Graphics[ { RGBColor[1,.5,.5], Dashing[{0.01,0.01}], Line[{{#,13.5},{#,16}}]& /@ ensos } ],
	Graphics[ { RGBColor[0,0,1], Text["Major Volcanic Eruptions in blue",{1905,13.7}] } ],
	Graphics[ { RGBColor[1,0,0], Text["Recent El Nino Southern Oscillations in red",{1905,13.6}] } ],
	MultipleListPlot[ by5year, DisplayFunction -> Identity ]
      },
      Axes -> False, Frame -> True,
      FrameLabel -> {"Year", "Degrees Centigrade", "Globally-Averaged Temperature by 5-Year Blocks", None},
      ImageSize -> 72 * 7,
      PlotRange -> { { 1860, 2000 }, { 13.5, 16 } },
      DisplayFunction -> ( Display["global_temp_5year.eps",#,"EPS"]& )
    ];
Run[ "kill -9 `ps -fu mccann | grep psrender | grep -v grep | awk '{print $2}'`" ];

