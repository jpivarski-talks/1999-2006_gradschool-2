import math

def trapint( f, r, dr, N, lowend=1, highend=1 ):
    h = 1. / N
    sum = 0

    for i in range( 1, N ):
        u = i * h
        sum = sum + f(r(u)) * dr(u)

    if lowend:
        sum = sum + f(r(0)) * dr(0) / 2.
    if highend:
        sum = sum + f(r(1)) * dr(1) / 2.

    return sum * h

def simpint( f, r, dr, N, lowend=1, highend=1 ):
    h = 1. / N
    sum = 0

    for i in range( 1, N, 2 ):
        u = i * h
        sum = sum + 4. * f(r(u)) * dr(u)
    for i in range( 2, N, 2 ):
        u = i * h
        sum = sum + 2. * f(r(u)) * dr(u)

    if lowend:
        sum = sum + f(r(0)) * dr(0)

    if highend:
        sum = sum + f(r(1)) * dr(1)

    return sum * h / 3.

def test( r ): return 1. / ( 1. + r**2 )**2 / ( 0.25 + 0.125 * math.pi )
def unitgauss( r ):
    if abs( r ) > 10:
        return 0
    else:
        return math.exp( -r**2 / 2. ) / math.sqrt( 2. * math.pi )

def linear_transform( u, low, high ): return low + ( high - low ) * u
def linear_measure( u, low, high ): return high - low

def semiinf_transform( u ):
    return math.tan( math.pi / 2. * u ) / ( math.pi / 2. )
def semiinf_measure( u ):
    return 1. / math.cos( math.pi / 2. * u )**2

def inf_transform( u ):
    return math.tan( math.pi / 2. * ( 2. * u - 1. ) ) / ( math.pi / 2. )
def inf_measure( u ):
    return 2. / math.cos( math.pi / 2. * ( 2. * u - 1. ) )**2

# old #$*%@ version of Python keeps me from my lambda expressions
#  def r(u): return linear_transform( u, 0, 1 )
#  def dr(u): return linear_measure( u, 0, 1 )
#  def r(u): return semiinf_transform( u )
#  def dr(u): return semiinf_measure( u )
#  def r(u): return inf_transform( u )
#  def dr(u): return inf_measure( u )

# testing code
#  for i in range(5):
#      N = 2*10**i
#      print '%5d: %20.16f %20.16f' % (
#          N,
#          trapint( unitgauss, r, dr, N, 1, 1 ),
#          simpint( unitgauss, r, dr, N, 1, 1 ) )

