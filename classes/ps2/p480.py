import math

def trapint( f, r, dr, N, lowend=1, highend=1 ):
    h = 1. / N
    sum = 0

    for i in range( 1, N ):
        u = i * h
        sum = sum + f[i] * dr[i]

    if lowend:
        sum = sum + f[0] * dr[i] / 2.
    if highend:
        sum = sum + f[N] * dr[N] / 2.

    return sum * h

def simpint( f, r, dr, N, lowend=1, highend=1 ):
    h = 1. / N
    sum = 0

    for i in range( 1, N, 2 ):
        u = i * h
        sum = sum + 4. * f[i] * dr[i]
    for i in range( 2, N, 2 ):
        u = i * h
        sum = sum + 2. * f[i] * dr[i]

    if lowend:
        sum = sum + f[0] * dr[0]

    if highend:
        sum = sum + f[N] * dr[N]

    return sum * h / 3.

for p in range(5):
    N = 2*10**p

    r = range(N+1)
    dr = range(N+1)
    f = range(N+1)
    for i in range(N+1):
        u = i / N
        r[i] = math.tan( math.pi / 2. * u ) / ( math.pi / 2. )
        dr[i] = 1. / math.cos( math.pi / 2. * u )**2

        f[i] = ( math.exp( -2.*r[i] ) / math.pi *
                 ( 1 - math.exp( -2.*r[i] ) - r[i] * math.exp( -2.*r[i] ) ) *
                 ( -4. * math.pi * r[i] ) )
#        f[i] = 1. / ( 1 + r[i]**2 )**2 / ( 0.25 + 0.125 * math.pi )

    print '%5d: %20.16f %20.16f' % (
        N, trapint( f, r, dr, N ), simpint( f, r, dr, N ) )
