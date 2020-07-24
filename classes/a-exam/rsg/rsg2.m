kf = t*f^(t-1)*(1 + alpha/Pi*(Pi^(2/3) - 1/2) + (3/4)*t
		- t^2/24 * (1/2 * Log[s/me^2] + 2*Pi^2 - 37/4))
    - t*(1 - f/2)
    + t^2/8 * (4 * (2-f) * Log[1/f]
	       - ((1 + 3*(1-f)^2) / f) * Log[1 - f] - 6 + f)

                                                                                                                                                            s
                                                                                                                                                       Log[---]
                                                   2                                                                                                         2
                         2           (1 + 3 (1 - f) ) Log[1 - f]                 1                             1      2/3           2    37        2       me
                        t  (-6 + f - --------------------------- + 4 (2 - f) Log[-])                  alpha (-(-) + Pi   )         t  (-(--) + 2 Pi  + --------)
                f                                 f                              f      -1 + t                 2             3 t         4                2
Out[16]= -((1 - -) t) + ------------------------------------------------------------ + f       t (1 + -------------------- + --- - -----------------------------)
                2                                    8                                                         Pi             4                 24


f is the fraction of energy taken by the initial state photon, so x =
f / (s + f) or f / s. The difference between the two choices is order
0.01% in the worst case--- use whichever is convenient.

100 / 9000 - 100 / 9100 // N

Out[37]= 0.0001221

t is 2 * alpha/Pi * (Log[s/me^2] - 1), which ranges so little over a
resonance that it can be considered constant for each resonance.

ttemp = 2 * alpha/Pi * (Log[s/me^2] - 1) /. me -> 0.511;
( (ttemp /. s -> 9000) - (ttemp /. s -> 9100) ) / (ttemp /. s -> 9000)

Out[38]= -0.00116957

ttemp = 2 * alpha/Pi * (Log[s/me^2] - 1) /. me -> 0.511;
( (ttemp /. s -> 11000) - (ttemp /. s -> 11100) ) / (ttemp /. s -> 11000)

Out[39]= -0.00093796

t is approximately 0.04, so f^(t-1) is a singularity.

kf1 = t*f^(t-1)*(1 + alpha/Pi*(Pi^(2/3) - 1/2) + (3/4)*t
		 - t^2/24*(1/2 * Log[s/me^2] + 2*Pi^2 - 37/4));                   (* substitute p = f^t, f = p^(1/t)    *)
kf2 = t^2 * Log[1/f] - t^2/2 * f * Log[1/f];                                      (* substitute q = 1/f, f = 1/q        *)
kf3 = -t*(1 - f/2) - t^2/8 * ((1 + 3*(1-f)^2) * Log[1 - f]/f - 6 - f) - 3*t^2/2;  (* no singularities, no substitutions *)
kf1 + kf2 + kf3 == kf // Simplify

Out[51]= True

(* Let's calm that numerical singularity at f=0 for the no
substitution case. Since f is small, this is actually overkill. *)
Series[ Log[1 - f]/f, {f, 0, 10} ]

                   2    3    4    5    6    7    8    9    10
              f   f    f    f    f    f    f    f    f    f         11
Out[49]= -1 - - - -- - -- - -- - -- - -- - -- - -- - -- - --- + O[f]
              2   3    4    5    6    7    8    9    10   11

kf3 = -t*(1 - f/2) - t^2/8 * ((1 + 3*(1-f)^2) *
			      (-1 - f/2 - f^2/3 - f^3/4 - f^4/5 - f^5/6) - 6 - f) - 3*t^2/2;

Each of these is going to appear in an integral. When you do a
substitution, you need to replace the bounds and the measure.

int_0^infinity kf1(f) * bwg(f-f0) df
    + int_0^infinity kf2(f) * bwg(f-f0) df
    + int_0^infinity kf3(f) * bwg(f-f0) df                 becomes

int_infinity^0 kf1(p) * bwg(f(p)-f0) (df/dp) dp
    + int_infinity^0 kf2(q) * bwg(f(q)-f0) (df/dq) dq
    + int_0^infinity kf3(f) * bwg(f-f0) df.


dfdp = D[ p^(1/t), p ];
dfdq = D[ 1/q, q ];

          -1 + 1/t
         p
Out[54]= ---------
             t

           -2
Out[55]= -q


kf1dfdp = Simplify[ kf1 * dfdp /. f -> p^(1/t) ]

                                                                   2            2          s
                                              1      2/3          t  (-37 + 8 Pi  + 2 Log[---])
                                     alpha (-(-) + Pi   )                                   2
          -1 + 1/t   1/t -1 + t               2             3 t                           me
Out[57]= p         (p   )       (1 + -------------------- + --- - -----------------------------)
                                              Pi             4                 96

-1 + 1/t + 1/t*(t-1) // Simplify

Out[60]= 0

so

(* final expression *)
kf1dfdp = 1 + (alpha*(-1/2 + Pi^(2/3)))/Pi + (3*t)/4 - (t^2*(-37 + 8*Pi^2 + 2*Log[s/me^2]))/96;

                                           2            2          s
                      1      2/3          t  (-37 + 8 Pi  + 2 Log[---])
             alpha (-(-) + Pi   )                                   2
                      2             3 t                           me
Out[63]= 1 + -------------------- + --- - -----------------------------
                      Pi             4                 96

This is a constant with respect to the p integration. This is good
because I'm integrating against a normalized (or at least
normalizable) function.



LOOK AT THIS: this is really easy to integrate... it varies almost not
at all with s (0.04%). The value of t gives a cut-off, I don't know if
the height is controlled by anything.


pgauss[f0_, wide_, s_] := Exp[-(p^(1/t) - f0)^2/2/wide^2] / Sqrt[2 Pi] / wide
    /. t -> (2 * 1/137.0359997650/Pi * (Log[s/0.51099890221^2] - 1));

Plot[ NIntegrate[ pgauss[x, 0.0040, 10000], {p, 0, 1} ], {x, 0, 0.0120} ];






Next,

kf2dfdq = Simplify[ kf2 * dfdq /. f -> 1/q ]

                    2
         (1 - 2 q) t  Log[q]
Out[70]= -------------------
                   3
                2 q

In other words,

(* final expression *)
kf2dfdq = ((1 - 2*q)*t^2*Log[q])/(2*q^3);

This one has a singularity at q -> 0, but this is all right because
q -> 0 is the limit of infinitely hard photons. I'll be integrating
this against a Breit-Wigner-ish * Gaussian, and the exponential in the
Gaussian will surely kill the log / q^3 divergence. The integration
will be stable (I hope the multiplication is).

<< Graphics`Graphics`

Plot[ (kf2dfdq /. t -> 0.04) * Exp[(1/q-0.1)^2], {q, 100, 1000}, PlotRange -> All ];

Plot[ (kf2 /. t -> 0.04), {f, 0, 0.0000001} ];





LOOK AT THIS: numerically, only kf1 contributes. This is independant
of your choice of t.

kf1values = kf1 /. {t -> 0.04, alpha -> 1/137, s -> 10000, me -> 0.511};
kf2values = kf2 /. {t -> 0.04, alpha -> 1/137, s -> 10000, me -> 0.511};
kf3values = kf3 /. {t -> 0.04, alpha -> 1/137, s -> 10000, me -> 0.511};

LogPlot[ {kf1values, kf2values, -kf3values}, {f, 0, 0.01}
	 , PlotStyle -> {RGBColor[0,0,0], RGBColor[1,0,0], RGBColor[0,0,1]}
       ];

{kf1values/kf1values, kf2values/kf1values, -kf3values/kf1values} /. f -> 0.01

Out[216]= {1., 0.00213366, 0.0117011}

LogPlot[ {0.01, kf2values/kf1values, -kf3values/kf1values}, {f, 0, 0.01}
	 , PlotStyle -> {RGBColor[0,0,0], RGBColor[1,0,0], RGBColor[0,0,1]}
       ];


Okay, maybe the blue one (kf3) matters at the 1% level.

But that one is easy. It's a polynomial, convoluting it with a
Gaussian is not that difficult.



(* Now for the modified BW from last time. Make sure you don't confuse
MeV with GeV!!! *)

bbarThresh = 2.*5.2794;
bbarThresh2 = bbarThresh^2;

y4sMass = 10.5800;

(* pure phase space *)
Solve[ const*Sqrt[s/4 - 5.2794^2]/(s/4) == 0.010 /. s -> y4sMass^2, const ];
gamma[s_] := Module[{g = 0.836052 * Sqrt[s/4 - 5.2794^2]/(s/4)}, If[ Im[g] == 0 && g > 0, g, 0 ] ];
Plot[ gamma[s], {s, bbarThresh^2, y4sMass^2} ];

integral = (3.344208*Sqrt[-27.87206436 + theS/4]*
	    (-Log[Abs[111.9364 - 1.*sprime]] + Log[Abs[sprime - theS]]))/theS;
renormMass2[s_] := y4sMass^2 + y4sMass
    * ((integral /. {sprime -> 100000^2, theS -> s})
       - (integral /. {sprime -> bbarThresh2, theS -> s})) / Pi

Plot[Sqrt[renormMass2[s]], {s, (y4sMass-0.020)^2, (y4sMass+0.020)^2}];

sigma = 0.00507333;
spread = 0.00028863;

hxsOverGammaEE[s_] := 12 Pi gamma[s] / ((s - renormMass2[s])^2 + y4sMass^2 * gamma[s]^2);
Plot[ hxsOverGammaEE[en^2]//Chop, {en, y4sMass-3*sigma, y4sMass+3*sigma}, 
      PlotRange -> All ];


beamEnergySpread[en_] := Exp[-(en)^2/2/sigma^2]/Sqrt[2 Pi]/sigma;
Plot[ beamEnergySpread[en], {en, -3*sigma, 3*sigma}, 
      PlotRange -> All ];

conv[en_] := NIntegrate[ hxsOverGammaEE[x^2] * beamEnergySpread[en - x],
			 {x, y4sMass-3*sigma, y4sMass+3*sigma} ] / 2 / Pi;
Plot[ conv[en], {en, y4sMass - 5 * spread, y4sMass + 5 * spread}, PlotPoints -> 10 ];

(* get a definite t *)
tsubs = 2 * alpha/Pi * (Log[s/me^2] - 1) /. {me -> 0.511, s -> y4sMass, alpha -> 1/137.0359997650};
kf1dfdp /. {alpha -> 1/137.0359997650, s -> y4sMass, me -> 0.51099890221, t -> tsubs};
en[p_] := s*(p^(1/tsubs)+1) /. s -> y4sMass;
Plot[ en[p], {p, 0, 0.97}, PlotRange -> All ];

                    THIS WAS A REALLY BAD IDEA.

Table[ {en[p], conv[en[p]]}, {p, 0, 0.97, 0.02} ] // TableForm

Out[285]//TableForm= 10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35634

                     10.58     3.35635

                     10.58     3.3564

                     10.5801   3.35661

                     10.5804   3.35358

                     10.5824   3.18769

                     10.5938   0.724675

                                         -34
                     10.6565   4.31889 10

                                                  -310
                     10.9892   6.97970914118964 10




tsubs = 2 * alpha/Pi * (Log[s/me^2] - 1) /. {me -> 0.511, s -> y4sMass, alpha -> 1/137.0359997650};
kfsubs = If[ en > y4sMass, ( kf /. {alpha -> 1/137.0359997650, s -> y4sMass, me -> 0.51099890221, t -> tsubs, f -> (en-10)/10} ), 0 ];

Plot[ kfsubs, {en, y4sMass-2, y4sMass+2} ];

( tab = Table[ {where, NIntegrate[ kfsubs * conv[en-where], {en, y4sMass, y4sMass+0.010, y4sMass+0.050, 20, 1000} ]},
	       {where, y4sMass-2, y4sMass+2, 0.2} ] ) // TableForm

General::spell1: Possible spelling error: new symbol name "tab" is similar to existing symbol "Tab".

General::unfl: Underflow occurred in computation.

General::unfl: Underflow occurred in computation.

General::unfl: Underflow occurred in computation.

General::stop: Further output of General::unfl will be suppressed during this calculation.

NIntegrate::ploss: Numerical integration stopping due to loss of precision. Achieved neither the requested PrecisionGoal nor AccuracyGoal; suspect one of the
    following: highly oscillatory integrand or the true value of the integral is 0. If your integrand is oscillatory try using the option Method->Oscillatory in
    NIntegrate.

NIntegrate::ploss: Numerical integration stopping due to loss of precision. Achieved neither the requested PrecisionGoal nor AccuracyGoal; suspect one of the
    following: highly oscillatory integrand or the true value of the integral is 0. If your integrand is oscillatory try using the option Method->Oscillatory in
    NIntegrate.

NIntegrate::ploss: Numerical integration stopping due to loss of precision. Achieved neither the requested PrecisionGoal nor AccuracyGoal; suspect one of the
    following: highly oscillatory integrand or the true value of the integral is 0. If your integrand is oscillatory try using the option Method->Oscillatory in
    NIntegrate.

General::stop: Further output of NIntegrate::ploss will be suppressed during this calculation.

NIntegrate::slwcon: Numerical integration converging too slowly; suspect one of the following: singularity, value of the integration being 0, oscillatory
    integrand, or insufficient WorkingPrecision. If your integrand is oscillatory try using the option Method->Oscillatory in NIntegrate.

NIntegrate::ncvb: NIntegrate failed to converge to prescribed accuracy after 7 recursive bisections in x near x = 10.5658.

NIntegrate::slwcon: Numerical integration converging too slowly; suspect one of the following: singularity, value of the integration being 0, oscillatory
    integrand, or insufficient WorkingPrecision. If your integrand is oscillatory try using the option Method->Oscillatory in NIntegrate.

NIntegrate::ncvb: NIntegrate failed to converge to prescribed accuracy after 7 recursive bisections in x near x = 10.5936.

NIntegrate::slwcon: Numerical integration converging too slowly; suspect one of the following: singularity, value of the integration being 0, oscillatory
    integrand, or insufficient WorkingPrecision. If your integrand is oscillatory try using the option Method->Oscillatory in NIntegrate.

General::stop: Further output of NIntegrate::slwcon will be suppressed during this calculation.

NIntegrate::ncvb: NIntegrate failed to converge to prescribed accuracy after 7 recursive bisections in x near x = 10.594.

General::stop: Further output of NIntegrate::ncvb will be suppressed during this calculation.

Out[298]//TableForm= 8.58    0. + 0. I

                                       -65
                     8.78    3.95833 10    + 0. I

                                       -128
                     8.98    2.18974 10     + 0. I

                     9.18    0.000412621 + 0. I

                     9.38    0.000406368 + 0. I

                     9.58    0. + 0. I

                     9.78    0. + 0. I

                     9.98    0. + 0. I

                     10.18   0. + 0. I

                     10.38   0. + 0. I

                     10.58   0. + 0. I

                     10.78   0. + 0. I

                     10.98   0. + 0. I

                     11.18   0. + 0. I

                     11.38   0. + 0. I

                     11.58   0. + 0. I

                     11.78   0. + 0. I

                     11.98   0. + 0. I

                     12.18   0. + 0. I

                     12.38   0. + 0. I

                     12.58   0. + 0. I

Exit

[Mathematica finished.]
