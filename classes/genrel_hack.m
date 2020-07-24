der[f_, mu_] :=
    D[f, {t, r, theta, phi}[[mu]]];

(metric = DiagonalMatrix[{-1, a[t]^2/(1-k*r), a[t]^2*r^2, a[t]^2*r^2*Sin[theta]^2}]) // TableForm

Out[5]//TableForm= -1   0         0          0

                             2
                         a[t]
                        -------
                   0    1 - k r   0          0

                                   2     2
                   0    0         r  a[t]    0

                                              2     2           2
                   0    0         0          r  a[t]  Sin[theta]

(metinv = Inverse[metric]) // TableForm

Out[6]//TableForm= -1   0         0          0

                        1 - k r
                        -------
                             2
                   0     a[t]     0          0

                                     1
                                  --------
                                   2     2
                   0    0         r  a[t]    0

                                                       2
                                             Csc[theta]
                                             -----------
                                               2     2
                   0    0         0           r  a[t]


g[mu_,nu_] := metric[[mu,nu]];
ginv[mu_,nu_] := metinv[[mu,nu]];

christoffel[alpha_, mu_, nu_] :=
    Sum[(1/2)*ginv[alpha,beta] * (der[g[beta,mu],nu] + der[g[beta,nu],mu] - der[g[mu,nu],beta]), {beta, 4}];

TableForm[Table[christoffel[alpha, mu, nu], {alpha, 1, 4}, {mu, 1, 4}, {nu, 1, 4}]]

Out[16]//TableForm= 0       0             0                0
                            a[t] a'[t]
                            ----------
                    0        1 - k r      0                0
                                           2
                    0       0             r  a[t] a'[t]    0
                                                            2                2
                    0       0             0                r  a[t] Sin[theta]  a'[t]

                            a'[t]
                            -----
                    0       a[t]          0                0
                    a'[t]        k
                    -----   -----------
                    a[t]    2 (1 - k r)   0                0
                    0       0             -(r (1 - k r))   0
                                                                                   2
                    0       0             0                -(r (1 - k r) Sin[theta] )

                                          a'[t]
                                          -----
                    0       0             a[t]             0
                                          1
                                          -
                    0       0             r                0
                    a'[t]   1
                    -----   -
                    a[t]    r             0                0
                    0       0             0                -(Cos[theta] Sin[theta])

                                                           a'[t]
                                                           -----
                    0       0             0                a[t]
                                                           1
                                                           -
                    0       0             0                r
                    0       0             0                Cot[theta]
                    a'[t]   1
                    -----   -
                    a[t]    r             Cot[theta]       0


tensorCder[tensor_, alpha_, beta_, gamma_] :=
    Sum[der[tensor[alpha,beta],gamma] + christoffel[alpha,mu,gamma] * tensor[mu,beta] + christoffel[beta,mu,gamma] * tensor[alpha,mu], {mu, 4}];

einstein[alpha_, beta_] := G[alpha, beta, t, r, theta, phi];

Table[Sum[tensorCder[einstein, alpha, beta, beta], {beta, 4}], {alpha, 1, 4}]

          2 G[1, 2, t, r, theta, phi]   k G[1, 2, t, r, theta, phi]                                          3 G[1, 1, t, r, theta, phi] a'[t]
Out[23]= {--------------------------- + --------------------------- + Cot[theta] G[1, 3, t, r, theta, phi] + --------------------------------- + 
                       r                        2 (1 - k r)                                                                a[t]
 
      a[t] G[2, 2, t, r, theta, phi] a'[t]    2                                         2                                          2
>     ------------------------------------ + r  a[t] G[3, 3, t, r, theta, phi] a'[t] + r  a[t] G[4, 4, t, r, theta, phi] Sin[theta]  a'[t] + 
                    1 - k r
 
         (0,0,0,0,0,1)                              (0,0,0,0,1,0)                              (0,0,0,1,0,0)
>     4 G             [1, 4, t, r, theta, phi] + 4 G             [1, 3, t, r, theta, phi] + 4 G             [1, 2, t, r, theta, phi] + 
 
         (0,0,1,0,0,0)                          2 G[2, 2, t, r, theta, phi]   k G[2, 2, t, r, theta, phi]
>     4 G             [1, 1, t, r, theta, phi], --------------------------- + --------------------------- + Cot[theta] G[2, 3, t, r, theta, phi] - 
                                                             r                          1 - k r
 
                                                                                              2   G[1, 2, t, r, theta, phi] a'[t]   4 G[2, 1, t, r, theta, phi] a'[t]
>     r (1 - k r) G[3, 3, t, r, theta, phi] - r (1 - k r) G[4, 4, t, r, theta, phi] Sin[theta]  + ------------------------------- + --------------------------------- + 
                                                                                                               a[t]                               a[t]
 
         (0,0,0,0,0,1)                              (0,0,0,0,1,0)                              (0,0,0,1,0,0)
>     4 G             [2, 4, t, r, theta, phi] + 4 G             [2, 3, t, r, theta, phi] + 4 G             [2, 2, t, r, theta, phi] + 
 
         (0,0,1,0,0,0)                          G[2, 3, t, r, theta, phi]   3 G[3, 2, t, r, theta, phi]   k G[3, 2, t, r, theta, phi]
>     4 G             [2, 1, t, r, theta, phi], ------------------------- + --------------------------- + --------------------------- + 
                                                            r                            r                        2 (1 - k r)
 
                                                                                               G[1, 3, t, r, theta, phi] a'[t]   4 G[3, 1, t, r, theta, phi] a'[t]
>     Cot[theta] G[3, 3, t, r, theta, phi] - Cos[theta] G[4, 4, t, r, theta, phi] Sin[theta] + ------------------------------- + --------------------------------- + 
                                                                                                            a[t]                               a[t]
 
         (0,0,0,0,0,1)                              (0,0,0,0,1,0)                              (0,0,0,1,0,0)
>     4 G             [3, 4, t, r, theta, phi] + 4 G             [3, 3, t, r, theta, phi] + 4 G             [3, 2, t, r, theta, phi] + 
 
         (0,0,1,0,0,0)                          G[2, 4, t, r, theta, phi]                                          3 G[4, 2, t, r, theta, phi]
>     4 G             [3, 1, t, r, theta, phi], ------------------------- + Cot[theta] G[3, 4, t, r, theta, phi] + --------------------------- + 
                                                            r                                                                   r
 
      k G[4, 2, t, r, theta, phi]                                            G[1, 4, t, r, theta, phi] a'[t]   4 G[4, 1, t, r, theta, phi] a'[t]
>     --------------------------- + 2 Cot[theta] G[4, 3, t, r, theta, phi] + ------------------------------- + --------------------------------- + 
              2 (1 - k r)                                                                 a[t]                               a[t]
 
         (0,0,0,0,0,1)                              (0,0,0,0,1,0)                              (0,0,0,1,0,0)
>     4 G             [4, 4, t, r, theta, phi] + 4 G             [4, 3, t, r, theta, phi] + 4 G             [4, 2, t, r, theta, phi] + 
 
         (0,0,1,0,0,0)
>     4 G             [4, 1, t, r, theta, phi]}

Sum[tensorCder[einstein, 1, beta, beta], {beta, 4}] == 0

         2 G[1, 2, t, r, theta, phi]   k G[1, 2, t, r, theta, phi]                                          3 G[1, 1, t, r, theta, phi] a'[t]
Out[26]= --------------------------- + --------------------------- + Cot[theta] G[1, 3, t, r, theta, phi] + --------------------------------- + 
                      r                        2 (1 - k r)                                                                a[t]
 
      a[t] G[2, 2, t, r, theta, phi] a'[t]    2                                         2                                          2
>     ------------------------------------ + r  a[t] G[3, 3, t, r, theta, phi] a'[t] + r  a[t] G[4, 4, t, r, theta, phi] Sin[theta]  a'[t] + 
                    1 - k r
 
         (0,0,0,0,0,1)                              (0,0,0,0,1,0)                              (0,0,0,1,0,0)
>     4 G             [1, 4, t, r, theta, phi] + 4 G             [1, 3, t, r, theta, phi] + 4 G             [1, 2, t, r, theta, phi] + 
 
         (0,0,1,0,0,0)
>     4 G             [1, 1, t, r, theta, phi] == 0




(metric = DiagonalMatrix[{-1, a[t]^2, a[t]^2, a[t]^2}]) // TableForm

Out[32]//TableForm= -1   0       0       0

                             2
                    0    a[t]    0       0

                                     2
                    0    0       a[t]    0

                                             2
                    0    0       0       a[t]

(metinv = Inverse[metric]) // TableForm

Out[33]//TableForm= -1   0        0        0

                             -2
                    0    a[t]     0        0

                                      -2
                    0    0        a[t]     0

                                               -2
                    0    0        0        a[t]

stressEnergy[alpha_, beta_] := DiagonalMatrix[{rho[t], p[t], p[t], p[t]}][[alpha, beta]];

Table[Sum[tensorCder[stressEnergy, alpha, beta, beta], {beta, 4}], {alpha, 1, 4}]

                              3 rho[t] a'[t]
Out[41]= {3 a[t] p[t] a'[t] + -------------- + 4 rho'[t], 0, 0, 0}
                                   a[t]

