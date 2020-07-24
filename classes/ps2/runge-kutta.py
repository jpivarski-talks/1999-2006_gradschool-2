import math

def rk4( y, dydx, n, x, h, derivs ):
    hh = h / 2.
    h6 = h / 6.
    xh = x + hh

    yt = range(n)
    for i in range(n):
        yt[i] = y[i] + hh * dydx[i]

    dyt = derivs( xh, yt )

    for i in range(n):
        yt[i] = y[i] + hh * dyt[i]

    dym = derivs( xh, yt )

    for i in range(n):
        yt[i] = y[i] + h * dym[i]
        dym[i] = dym[i] + dyt[i]

    dyt = derivs( x+h, yt )

    yout = range(n)
    for i in range(n):
        yout[i] = y[i] + h6 * ( dydx[i] + dyt[i] + 2. * dym[i] )

    return yout


y = [ 0, 1 ]
for x in range(10):
    print 'y( ' + `x` + ' ) = ' + `y`
    y = rk4( y, derivs( x, y ), 2, x, 1., derivs )
