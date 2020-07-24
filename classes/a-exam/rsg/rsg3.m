<< Graphics`Graphics`
<< Graphics`MultipleListPlot`

Show[
    Plot[ Sqrt[en^2 - 10558^2]/en^2, {en, 10558, 11020},
	  PlotRange -> All,
	  DisplayFunction -> Identity ],
    Graphics[{Line[{{10580,0},{10580,0.000030}}],
	      Line[{{10865,0},{10865,0.000030}}],
	      Line[{{11019,0},{11019,0.000030}}]
	     }],
    DisplayFunction -> $DisplayFunction ];

D[ Sqrt[en^2 - 10558^2]/en^2, en ] /. en -> 10580 // N

                   -7
Out[15]= 1.37451 10

D[ Sqrt[en^2 - 10558^2]/en^2, en ] /. en -> 10865 // N

                 -8
Out[16]= 3.189 10

D[ Sqrt[en^2 - 10558^2]/en^2, en ] /. en -> 11019 // N

                   -8
Out[17]= 2.40601 10

Out[16]/Out[15]

Out[18]= 0.23201 deriv of 5S over deriv of 4S

Out[17]/Out[15]

Out[19]= 0.175045 deriv of 6S over deriv of 4S

kf = t*f^(t-1)*(1 + alpha/Pi*(Pi^(2/3) - 1/2) + (3/4)*t
		- t^2/24 * (1/2 * Log[s/me^2] + 2*Pi^2 - 37/4))
    - t*(1 - f/2)
    + t^2/8 * (4 * (2-f) * Log[1/f]
	       - ((1 + 3*(1-f)^2) / f) * Log[1 - f] - 6 + f)
    /. {t -> 0.04, f -> x/10580, s -> 10580, me -> 0.511, alpha -> 1/137};

kf // Expand

                    301.696             -6                      x
Out[159]= -0.0412 + ------- + 1.90926 10   x + 0.0012 Log[1 - -----] - 
                      0.96                                    10580
                     x
 
                     x
     8.464 Log[1 - -----]
                   10580              -8             x
>    -------------------- - 5.67108 10   x Log[1 - -----] + 
              x                                    10580
 
                10580              -8       10580
>    0.0016 Log[-----] - 7.56144 10   x Log[-----]
                  x                           x

kfTrans[t_,inf_] := NIntegrate[ Expand[kf * Exp[I*x*t]], {x, 0, inf}, MaxRecursion -> 1000 ];

ListPlot[Table[Abs[kfTrans[t,1000]], {t, -0.2, 0.2, 0.01}], PlotRange -> All];


kfTrans[0,1000]

Out[139]= 9908.6 + 0. I

kfTrans[0,10000]

Out[140]= 10605.9 + 0. I

kfTrans[0,100000]

Out[141]= 17528.9 - 603.463 I

kfTrans[0,1000000]

Out[142]= 963873. - 85462.2 I



kfTrans[0.01,1000]

Out[143]= 8838.84 + 585.742 I

kfTrans[0.01,10000]

Out[144]= 8854.03 + 552.002 I




kfTrans[0.001,1000]

Out[148]= 9820.66 + 345.296 I

kfTrans[0.001,10000]

Out[149]= 9700.2 + 593.997 I

kfTrans[0.001,10000]

Out[150]= 9700.2 + 593.997 I




kfTrans[0.0001,10000]

Out[153]= 10544.6 + 269.858 I

kfTrans[0.00001,10000]

Out[154]= 10605.2 + 28.2792 I

kfTrans[0.000001,10000]

Out[155]= 10605.9 + 2.82925 I

kfTrans[0.0000001,10000]

Out[156]= 10605.9 + 0.282926 I

kfTrans[0.00000001,10000]

Out[157]= 10605.9 + 0.0282926 I




kfTrans[0.00000001,100000]

Out[158]= 17529.4 - 598.602 I

I'll need to be very careful with the way I calculate this!




gTrans[t_] := Exp[-2 Pi^2 4^2 t^2] / 2 / 4^2;

lTrans[t_] := Exp[-14 Pi Abs[t]];

ListPlot[Table[Abs[gTrans[t]], {t, -0.2, 0.2, 0.01}], PlotRange -> All];

ListPlot[Table[Abs[lTrans[t]], {t, -0.2, 0.2, 0.01}], PlotRange -> All];





WeightedMean[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] := Module[
    { xoversig2sum, oneoversig2sum },
    xoversig2sum = Plus @@ ( ( #[[1]] / #[[2]]^2 )& /@ points );
    oneoversig2sum = Plus @@ ( ( 1 / #[[2]]^2 )& /@ points );
    If[ oneoversig2sum == 0, { 0, 0 },
	{ xoversig2sum / oneoversig2sum, Sqrt[ 1 / oneoversig2sum ] } ] ];

WeightedMean[ { {3.41, 0.27}, {3.27, 0.06}, {3.04, 0.06}, {3.31, 0.05}, {3.34, 0.05},
		{3.31, 0.05}, {3.39, 0.05}, {3.27, 0.06}, {3.34, 0.06} } ]

WeightedMean[ {
    {3.28, 0.05}, {3.16, 0.05}, {3.23, 0.05}, {3.16, 0.05}, {3.24, 0.08},
    {3.16, 0.07}, {3.26, 0.15}, {3.23, 0.06}, {3.10, 0.10}, {3.54, 0.21},
    {3.14, 0.05}, {3.17, 0.05}, {3.29, 0.05}, {3.19, 0.05}, {3.31, 0.09}
	      } ]

WeightedMean[ {
    {7.04, 0.17}, {7.00, 0.09}, {7.02, 0.32}, {7.09, 0.16}, {6.95, 0.08},
    {6.83, 0.07}, {7.10, 0.13}, {6.93, 0.07}, {6.95, 0.07}, {7.07, 0.07},
    {7.03, 0.08}, {6.93, 0.07}, {7.01, 0.07}, {7.01, 0.07}, {6.61, 0.22},
    {6.89, 0.10}, {7.01, 0.08}, {7.00, 0.07}, {7.15, 0.27}, {6.95, 0.14},
    {7.00, 0.07}, {6.97, 0.07}, {6.82, 0.14}, {7.09, 0.13}, {7.10, 0.11},
    {6.88, 0.09}, {6.89, 0.07}, {6.98, 0.07}, {6.90, 0.07}, {7.03, 0.10},
    {6.94, 0.11}, {6.95, 0.10}, {6.97, 0.07}, {6.92, 0.07}, {6.99, 0.07},
    {6.83, 0.07}, {7.00, 0.09}, {6.81, 0.11}, {6.99, 0.12}, {6.93, 0.08},
    {6.90, 0.10}, {6.56, 0.28}, {6.81, 0.24}, {6.83, 0.07}, {6.91, 0.07}
	      } ]


WeightedMean[ { {5.71, 0.10}, {5.94, 0.09} } ]

data = {
    {2000*5.17730, 5.83707, 0.0668965},
    {2000*5.18241, 4.95, 0.07},
    {2000*5.19036, 3.41, 0.06},
    {2000*5.17244, 3.18, 0.05},
    {2000*5.18783, 3.43, 0.06},
    {2000*5.18536, 3.63, 0.06},
    {2000*5.17451, 3.66, 0.08},
    {2000*5.19968, 3.29403, 0.0191571},
    {2000*5.16516, 3.20687, 0.015563},
    {2000*5.17945, 6.95064, 0.0129547}
       };

datasub = Sort[ {#[[1]]-10358, #[[2]] - 3.20687, #[[3]]}& /@ data,  (* additional error is systematic *)
		(#1[[1]] < #2[[1]])& ];

datasub2 = Join[ datasub, {{11+10580-10358, 0, 0}} ];

MultipleListPlot[ {{#[[1]], #[[2]]}, ErrorBar[#[[3]]]}& /@ datasub2, PlotRange -> All, PlotJoined -> True ];

area = Sum[ (x[i+1] - x[i])(y[i] + y[i+1])/2, {i, 1, Length[datasub2]-1} ];
areaft[t_] := Sum[ (x[i+1] - x[i])(y[i]*Exp[I*x[i]*t] + y[i+1]*Exp[I*x[i+1]*t])/2, {i, 1, Length[datasub2]-1} ];

Table[ Simplify[ daready[i] = D[area, y[i]] ], {i, 1, Length[datasub2]} ];
Table[ ( dftdy[i_,t_] := D[areaft[t], y[i]] ), {i, 1, Length[datasub2]} ];

sig2area = Sum[ daready[i]^2 * sig2y[i], {i, 1, Length[datasub2]} ];
sig2ft[t_] := Sum[ dftdy[i,t]^2 * sig2y[i], {i, 1, Length[datasub2]} ];

subs = Flatten[ Table[ {x[i] -> datasub2[[i,1]],
			y[i] -> datasub2[[i,2]],
			sig2y[i] -> datasub2[[i,3]]^2}, {i, 1, Length[datasub2]} ] ];

area /. subs

Out[129]= 59.3568

Sqrt[sig2area /. subs]

Out[130]= 2.32927




dataft[t_] := {areaft[t] /. subs, Sqrt[sig2ft[t] /. subs]};

dataft[0]

Out[132]= {59.3568, 2.32927}

dataft[1]

Out[133]= {-1.08877 + 15.9233 I, 1.90485 + 1.05061 I}

ListPlot[Table[Abs[dataft[t][[1]]], {t, -0.2, 0.2, 0.01}], PlotRange -> All];

ListPlot[Table[Abs[dataft[t][[1]]], {t, -2.0, 2.0, 0.01}], PlotRange -> All, PlotJoined -> True];

MultipleListPlot[Table[{{t,
			 Abs[dataft[t][[1]]]},
			ErrorBar[Abs[dataft[t][[2]]]]},
		       {t, -5.0, 5.0, 0.01}],
		 PlotRange -> All, AspectRatio -> 1/4];

ListPlot[Table[{t, Abs[kfTrans[t,10000]]}, {t, -5.0, 5.0, 0.01}],
	 PlotRange -> All, AspectRatio -> 1/4];

Out[158]= $Aborted







gTrans3s[t_] := Exp[-2 Pi^2 4.6^2 t^2] / 2 / 4.6^2;

lTrans3s[t_] := Exp[-0.0263 Pi Abs[t]];

ListPlot[Table[Abs[gTrans3s[t]], {t, -0.2, 0.2, 0.01}], PlotRange -> All];

ListPlot[Table[Abs[lTrans3s[t]], {t, -0.2, 0.2, 0.01}], PlotRange -> All];



MultipleListPlot[{Table[Abs[dataft[t][[1]]], {t, -0.2, 0.2, 0.01}],
		  2500*Table[Abs[gTrans3s[t]], {t, -0.2, 0.2, 0.01}]}, PlotRange -> All];




NEW START


Plot[ {
    Re[kf*Exp[2*Pi*I*x*0.00]],
    Re[kf*Exp[2*Pi*I*x*0.01]],
    Re[kf*Exp[2*Pi*I*x*0.02]],
    Re[kf*Exp[2*Pi*I*x*0.03]],
    Re[kf*Exp[2*Pi*I*x*0.04]],
    Re[kf*Exp[2*Pi*I*x*0.05]]
      } , {x, 0, 10} ];



Integrate[ Exp[I*x*t]/x, {x, 1, Infinity}, Assumptions -> {Im[t]==0} ]

                                          2
                                     Log[t ]   I
Out[182]= -CosIntegral[t] + Log[t] - ------- + - Pi Sign[t] - I SinIntegral[t]
                                        2      2

ListPlot[ Table[Abs[Out[182]], {t, 0.1, 1, 0.1}] ];

Plot[ Abs[Out[182]], {t, 0, 0.1} ];


Integrate[ Exp[I*x*t]/x^2, {x, 1, Infinity}, Assumptions -> {Im[t]==0} ]

                                                                     2
                                                      1     1  1   -t
Out[196]= I t - I EulerGamma t + HypergeometricPFQ[{-(-)}, {-, -}, ---] - 
                                                      2     2  2    4
 
     I        2    Pi t Sign[t]
>    - t Log[t ] - ------------ + 
     2                  2
 
>    I (-t + EulerGamma t - t CosIntegral[t] + t Log[t] + Sin[t])

Plot[ Abs[Out[196]], {t, 0, 0.1} ];



Exit

[Mathematica finished.]

