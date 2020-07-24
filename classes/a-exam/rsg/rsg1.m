WeightedMean[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] := Module[
    { xoversig2sum, oneoversig2sum },
    xoversig2sum = Plus @@ ( ( #[[1]] / #[[2]]^2 )& /@ points );
    oneoversig2sum = Plus @@ ( ( 1 / #[[2]]^2 )& /@ points );
    If[ oneoversig2sum == 0, { 0, 0 },
        { xoversig2sum / oneoversig2sum, Sqrt[ 1 / oneoversig2sum ] } ] ];

Y1s mean mass, rms mass and sigma

mass = 9.46040099683862      +/-   3.256249447448489*^-005 GeV
wide = 3.87873981675892      +/-   2.238290407357293*^-002 MeV

mass = 9.46034679215116      +/-   2.534894619296433*^-005 GeV
wide = 3.91305553478331      +/-   2.065464742637901*^-002 MeV

mass = 9.46022373306234      +/-   3.067058747107630*^-005 GeV
wide = 3.90153816639143      +/-   2.321277679335641*^-002 MeV

mass = 9.46000548013409      +/-   3.679344165770287*^-005 GeV
wide = 3.84751710758281      +/-   2.749053495277575*^-002 MeV

mass = 9.46014216298125      +/-   4.410886322284765*^-005 GeV
wide = 3.89619920436313      +/-   2.900182352909300*^-002 MeV

mass = 9.45981460184117      +/-   4.545648524323812*^-005 GeV
wide = 3.99646853862200      +/-   3.741969616417032*^-002 MeV

mass = 9.45980300642493      +/-   2.092560943965562*^-005 GeV
wide = 3.81493724363358      +/-   1.868184226189960*^-002 MeV

y1sMass = WeightedMean[ {
    {9.46040099683862, 3.256249447448489*^-005},
    {9.46034679215116, 2.534894619296433*^-005},
    {9.46022373306234, 3.067058747107630*^-005},
    {9.46000548013409, 3.679344165770287*^-005},
    {9.46014216298125, 4.410886322284765*^-005},
    {9.45981460184117, 4.545648524323812*^-005},
    {9.45980300642493, 2.092560943965562*^-005}
                        } ]

Out[2]= {9.46009, 0.0000114838}

y1sWide = WeightedMean[ {
    {3.87873981675892, 2.238290407357293*^-002},
    {3.91305553478331, 2.065464742637901*^-002},
    {3.90153816639143, 2.321277679335641*^-002},
    {3.84751710758281, 2.749053495277575*^-002},
    {3.89619920436313, 2.900182352909300*^-002},
    {3.99646853862200, 3.741969616417032*^-002},
    {3.81493724363358, 1.868184226189960*^-002}
                        } ]

Out[3]= {3.87902, 0.00902129}

Y2s mean mass, rms mass and sigma

mass = 10.0246158426987      +/-   5.186169032013737*^-005 GeV
wide = 4.15041823577207      +/-   8.373654585934931*^-002 MeV

mass = 10.0244956397198      +/-   3.751419610874711*^-005 GeV
wide = 4.28652726021513      +/-   4.154660645794238*^-002 MeV

mass = 10.0243920127610      +/-   3.564625682872852*^-005 GeV
wide = 4.27196662776114      +/-   5.903821350954819*^-002 MeV

mass = 10.0240620431931      +/-   6.525813016213964*^-005 GeV
wide = 4.15814343506467      +/-   4.006187408332972*^-002 MeV

y2sMass = WeightedMean[ {
    {10.0246158426987, 5.186169032013737*^-005},
    {10.0244956397198, 3.751419610874711*^-005},
    {10.0243920127610, 3.564625682872852*^-005},
    {10.0240620431931, 6.525813016213964*^-005}
              } ]

Out[4]= {10.0244, 0.0000218001}

y2sWide = WeightedMean[ {
    {4.15041823577207, 8.373654585934931*^-002},
    {4.28652726021513, 4.154660645794238*^-002},
    {4.27196662776114, 5.903821350954819*^-002},
    {4.15814343506467, 4.006187408332972*^-002}
              } ]

Out[5]= {4.22306, 0.0247543}

Y3s mean mass, rms mass and sigma

mass = 10.3587573240278      +/-   8.650453759038591*^-005 GeV
wide = 4.57908405145130      +/-   7.346443098781938*^-002 MeV

mass = 10.3590401340337      +/-   8.343803420376312*^-005 GeV
wide = 4.59569616444977      +/-   7.908035507126444*^-002 MeV

mass = 10.3582679727764      +/-   1.022406318795555*^-004 GeV
wide = 4.63810240013466      +/-   2.670782521433786*^-002 MeV

mass = 10.3580791342935      +/-   1.010740549282410*^-004 GeV
wide = 4.60539155374842      +/-   8.884827917177220*^-002 MeV

mass = 10.3580572606527      +/-   6.860187276749588*^-005 GeV
wide = 4.68338758878447      +/-   1.112859325254276*^-002 MeV

mass = 10.3580600167044      +/-   8.897519743023776*^-005 GeV
wide = 4.62315319319341      +/-   6.846542272265113*^-002 MeV

mass = 10.3582515269087      +/-   1.196628347212454*^-004 GeV
wide = 4.82972479965125      +/-   9.659519899902380*^-002 MeV

y3sMass = WeightedMean[ {
    {10.3587573240278, 8.650453759038591*^-005},
    {10.3590401340337, 8.343803420376312*^-005},
    {10.3582679727764, 1.022406318795555*^-004},
    {10.3580791342935, 1.010740549282410*^-004},
    {10.3580572606527, 6.860187276749588*^-005},
    {10.3580600167044, 8.897519743023776*^-005},
    {10.3582515269087, 1.196628347212454*^-004}
              } ]

Out[6]= {10.3584, 0.0000337203}

y3sWide = WeightedMean[ {
    {4.57908405145130, 7.346443098781938*^-002},
    {4.59569616444977, 7.908035507126444*^-002},
    {4.63810240013466, 2.670782521433786*^-002},
    {4.60539155374842, 8.884827917177220*^-002},
    {4.68338758878447, 1.112859325254276*^-002},
    {4.62315319319341, 6.846542272265113*^-002},
    {4.82972479965125, 9.659519899902380*^-002}
              } ]

Out[7]= {4.67327, 0.00986822}

interp = Interpolation[ { {y1sMass[[1]], y1sWide[[1]]},
                          {y2sMass[[1]], y2sWide[[1]]},
                          {y3sMass[[1]], y3sWide[[1]]} } ]

Interpolation::inhr: 
   Requested order is too high; order has been reduced to {2}.

Out[8]= InterpolatingFunction[{{9.46009, 10.3584}}, <>]

sigma = interp[10.580] / 1000 (* put sigma in GeV as well *)

InterpolatingFunction::dmval: 
   Input value {10.58} lies outside the range of data in the interpolating function. Extrapolation
     will be used.

Out[223]= 0.00507333

<< Statistics`DescriptiveStatistics`



y1sSpread = StandardDeviation[ {9.46040099683862, 9.46034679215116,
				9.46022373306234, 9.46000548013409,
				9.46014216298125, 9.45981460184117,
				9.45980300642493} ]

Out[15]= 0.000240483

y2sSpread = StandardDeviation[ {10.0246158426987, 10.0244956397198,
				10.0243920127610, 10.0240620431931} ]

Out[16]= 0.000237849

y3sSpread = StandardDeviation[ {10.3587573240278, 10.3590401340337,
				10.3582679727764, 10.3580791342935,
				10.3580572606527, 10.3580600167044,
				10.3582515269087} ]

Out[17]= 0.000387557

spread = Mean[ {y1sSpread, y2sSpread, y3sSpread} ]

Out[18]= 0.00028863

bbarThresh = 2.*5.2794;
bbarThresh2 = bbarThresh^2;

y4sMass = 10.5800;

(* pure phase space *)
Solve[ const*Sqrt[s/4 - 5.2794^2]/(s/4) == 0.010 /. s -> y4sMass^2, const ];
gamma[s_] := Module[{g = 0.836052 * Sqrt[s/4 - 5.2794^2]/(s/4)}, If[ Im[g] == 0 && g > 0, g, 0 ] ];
Plot[ gamma[s], {s, bbarThresh^2, y4sMass^2} ];

dgamds = D[ 0.836052 * Sqrt[s/4 - 5.2794^2]/(s/4), s ] /. s -> y4sMass^2

Out[244]= 0.0110678

Integrate[ 0.836052 * Sqrt[theS/4 - 5.2794^2]/(theS/4)
	   * (1/(y4sMass^2-sprime) - 1/(theS-sprime)), sprime ] // InputForm

integral = (3.344208*Sqrt[-27.87206436 + theS/4]*
	    (-Log[Abs[111.9364 - 1.*sprime]] + Log[Abs[sprime - theS]]))/theS;
renormMass2[s_] := y4sMass^2 + y4sMass
    * ((integral /. {sprime -> 100000^2, theS -> s})
       - (integral /. {sprime -> bbarThresh2, theS -> s})) / Pi

Plot[Sqrt[renormMass2[s]], {s, (y4sMass-0.020)^2, (y4sMass+0.020)^2}];

Table[ {i, Sqrt[renormMass2[(y4sMass+i)^2]]}, {i, -0.021, 0.019, 0.005} ] // TableForm

Out[175]//TableForm= -0.021   10.5807

                     -0.016   10.5811

                     -0.011   10.5808

                     -0.006   10.5804

                     -0.001   10.5801

                     0.004    10.5797

                     0.009    10.5793

                     0.014    10.579

                     0.019    10.5786

Might as well put in the mass shifts. They account for about an MeV on
the scale I'm interested in (4 * beam energy spread).

hxsOverGammaEE[s_] := 12 Pi gamma[s] / ((s - renormMass2[s])^2 + y4sMass^2 * gamma[s]^2);
Plot[ hxsOverGammaEE[en^2]//Chop, {en, y4sMass-3*sigma, y4sMass+3*sigma}, 
      PlotRange -> All ];

Table[ {i, hxsOverGammaEE[(y4sMass+i)^2]}, {i, -0.021, 0.019, 0.005} ] // TableForm

Out[219]//TableForm= -0.021   0.174144

                     -0.016   1.40046

                     -0.011   3.86436

                     -0.006   11.988

                     -0.001   32.901

                     0.004    19.0426

                     0.009    7.77085

                     0.014    4.04249

                     0.019    2.49115

beamEnergySpread[en_] := Exp[-(en)^2/2/sigma^2]/Sqrt[2 Pi]/sigma;
Plot[ beamEnergySpread[en], {en, -3*sigma, 3*sigma}, 
      PlotRange -> All ];

conv[en_] := NIntegrate[ hxsOverGammaEE[x^2] * beamEnergySpread[en - x],
			 {x, y4sMass-3*sigma, y4sMass+3*sigma} ] / 2 / Pi;

Table[ {en, conv[en]},
       {en, y4sMass-3*sigma, y4sMass+3*sigma, sigma/1.5} ] // TableForm

Out[235]//TableForm= 10.5648   0.394166

                     10.5682   0.873397

                     10.5715   1.64171

                     10.5749   2.57001

                     10.5783   3.25087

                     10.5817   3.27353

                     10.5851   2.6538

                     10.5885   1.7939

                     10.5918   1.04988

                     10.5952   0.532472

phaseSpaceConvs = Table[ conv[en], {en, y4sMass-3*spread, y4sMass+3*spread, spread/1.5} ]

Out[261]= {3.34226, 3.35209, 3.3595, 3.36448, 3.36702, 3.36711, 3.36475, 3.35994, 3.35271, 3.34306}

(* peak is almost centered! well how about that! *)
Plot[ conv[en], {en, y4sMass - 5 * spread, y4sMass + 5 * spread}, PlotPoints -> 10 ];
{hxcMinusPeak, enSub} = FindMinimum[ -conv[en], {en, y4sMass+0.00001, 0.00002} ]

Out[314]= {-3.35665, {en -> 10.5801}}

Note: spread = 0.28863 MeV.

(* worst systematic due to unknown beam energy calibration *)
( -hxcMinusPeak - conv[(en/.enSub) + 5 * spread] ) / -hxcMinusPeak

Out[318]= 0.020339

which is 2%.

(* What if... *)
( -hxcMinusPeak - conv[(en/.enSub) + 10 * spread] ) / -hxcMinusPeak

Out[319]= 0.0778987

now we have 7.8%.

In order to get up to the Argus uncertainty of 18%, we need to have an
energy systematic uncertainty of 4.57 MeV. Which we don't.

( -hxcMinusPeak - conv[(en/.enSub) + 0.00457] ) / -hxcMinusPeak

Out[325]= 0.180615

    *    *    *

But the KF part of the convolution also shifts the peak, perhaps I
should put that shifting in by hand. It shifts it by about 0.5 MeV.

(* worst systematic due to unknown beam energy calibration *)
( conv[y4sMass+0.0005] - conv[y4sMass+0.0005 + 5 * spread] ) / conv[y4sMass+0.0005]

Out[328]= 0.0314237

Now we're looking at 3%.

(* what if... *)
( conv[y4sMass+0.0005] - conv[y4sMass+0.0005 + 10 * spread] ) / conv[y4sMass+0.0005]

Out[329]= 0.0981449

10% !!!

(* worst systematic due to unknown beam energy calibration *)
( conv[y4sMass+0.0005] - conv[y4sMass+0.0005 + 0.00418] ) / conv[y4sMass+0.0005]

Out[337]= 0.180254

But you still need 4.18 MeV to get up to the 18% level.

    *    *    *

Let me find a worst case for KF convolutions:

(* worst systematic due to unknown beam energy calibration *)
( conv[y4sMass+0.010] - conv[y4sMass+0.010 + 5 * spread] ) / conv[y4sMass+0.010]

Out[347]= 0.211983  (KF shifts 10 MeV)
Out[346]= 0.198687  (KF shifts 9 MeV)
Out[345]= 0.184845  (KF shifts 8 MeV)
Out[344]= 0.169972  (KF shifts 7 MeV)
Out[343]= 0.153673  (KF shifts 6 MeV)
Out[342]= 0.135668  (KF shifts 5 MeV)
Out[341]= 0.115793  (KF shifts 4 MeV)
Out[340]= 0.0939891 (KF shifts 3 MeV)
Out[339]= 0.0702885 (KF shifts 2 MeV)
Out[338]= 0.0447946 (KF shifts 1 MeV)

So it matters very much how the KF convolution moves things. Someday,
I'll need to do a full three-way convolution.

     *     *     *

If I'm wrong about the beam energy spread by about 1%, what does this
do to the peak measurement?

beamEnergySpread[en_,sig_] := Exp[-(en)^2/2/sig^2]/Sqrt[2 Pi]/sig;
conv[en_,sig_] := NIntegrate[ hxsOverGammaEE[x^2] * beamEnergySpread[en - x],
			      {x, y4sMass-3*sig, y4sMass+3*sig} ] / 2 / Pi;

(* not much for 1%. *)
( conv[y4sMass+0.0001, sigma] - conv[y4sMass+0.0001, 0.99*sigma] ) / conv[y4sMass+0.0001, sigma]

Out[353]= 0.0000354116

(* not much for 10%. *)
( conv[y4sMass+0.0001, sigma] - conv[y4sMass+0.0001, 0.90*sigma] ) / conv[y4sMass+0.0001, sigma]

Out[354]= 0.000600413

(* still just 4% uncertainty if I'm wrong about the beam energy spread by a factor of 2. *)
( conv[y4sMass+0.0001, sigma] - conv[y4sMass+0.0001, 0.50*sigma] ) / conv[y4sMass+0.0001, sigma]

Out[355]= 0.0397932

(* even the other way *)
( conv[y4sMass+0.0001, sigma] - conv[y4sMass+0.0001, 1.50*sigma] ) / conv[y4sMass+0.0001, sigma]

Out[357]= -0.000286563







(* ************ NE'ER YOU MIND OF THIS ******************* *)

(* a linear approximation (near the mass) *)
(* to connect up with bbarThresh, slope = 0.0223143 *)
slope = dgamds;
gamma[s_] := Module[{g = (s - y4sMass^2) * slope + 0.010}, If[ g > 0, g, 0 ] ];
straightConvs = Table[ conv[en], {en, y4sMass-3*spread, y4sMass+3*spread, spread/1.5} ]

Out[262]= {3.32898, 3.3399, 3.34837, 3.35439, 3.35795, 3.35905, 3.35768, 3.35386, 3.34761, 3.33894}

slope = 2 * dgamds;
gamma[s_] := Module[{g = (s - y4sMass^2) * slope + 0.010}, If[ g > 0, g, 0 ] ];
doubleConvs = Table[ conv[en], {en, y4sMass-3*spread, y4sMass+3*spread, spread/1.5} ]

Out[263]= {3.29671, 3.30909, 3.31899, 3.32638, 3.33126, 3.33364, 3.33351, 3.33091, 3.32584, 3.31833}

slope = dgamds / 2;
gamma[s_] := Module[{g = (s - y4sMass^2) * slope + 0.010}, If[ g > 0, g, 0 ] ];
halfConvs = Table[ conv[en], {en, y4sMass-3*spread, y4sMass+3*spread, spread/1.5} ]

Out[264]= {3.33816, 3.34845, 3.35632, 3.36175, 3.36473, 3.36526, 3.36333, 3.35896, 3.35216, 3.34295}

slope = 10 * dgamds;
gamma[s_] := Module[{g = (s - y4sMass^2) * slope + 0.010}, If[ g > 0, g, 0 ] ];
tenConvs = Table[ conv[en], {en, y4sMass-3*spread, y4sMass+3*spread, spread/1.5} ]

NIntegrate::ncvb: NIntegrate failed to converge to prescribed accuracy after 7 recursive bisections in x near x = 10.5758.

NIntegrate::ncvb: NIntegrate failed to converge to prescribed accuracy after 7 recursive bisections in x near x = 10.5758.

NIntegrate::ncvb: NIntegrate failed to converge to prescribed accuracy after 7 recursive bisections in x near x = 10.5758.

General::stop: Further output of NIntegrate::ncvb will be suppressed during this calculation.

Out[265]= {2.69039, 2.71392, 2.73488, 2.75325, 2.76899, 2.78209, 2.79254, 2.80035, 2.80553, 2.8081}

slope = dgamds / 10;
gamma[s_] := Module[{g = (s - y4sMass^2) * slope + 0.010}, If[ g > 0, g, 0 ] ];
tenthConvs = Table[ conv[en], {en, y4sMass-3*spread, y4sMass+3*spread, spread/1.5} ]

Out[266]= {3.34226, 3.35209, 3.3595, 3.36448, 3.36702, 3.36711, 3.36475, 3.35994, 3.35271, 3.34306}

<< Graphics`MultipleListPlot`

MultipleListPlot[ {
    straightConvs / phaseSpaceConvs
(*    doubleConvs / phaseSpaceConvs, *)
(*    halfConvs / phaseSpaceConvs *)
(*    tenConvs / phaseSpaceConvs *)
(*    tenthConvs / phaseSpaceConvs *)
		  } , PlotJoined -> True ];




