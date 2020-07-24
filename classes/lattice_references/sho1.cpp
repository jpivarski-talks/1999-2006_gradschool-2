double px[10];
   
const double PI = 3.1415926;
const double a = 0.5;
const int N = 5;
const double m = 1.;
const double A = pow( ( m / 2 / PI / a ), ( N / 2 ) );
const double T = a * N;

double potential( double x )
{
   return x * x / 2.;
}

double S_lat( double* x )
{
   double S = 0.;
   for ( int j = 0;  j < N;  j++ )
   {
      double KE = ( m / 2 / a ) * pow( x[j+1] - x[j], 2 );
      double PE = a * potential( x[j] );
      S += KE + PE;
   }
   return S;
}

double integrate( double* x, int i, int final )
{
   const double dx = 0.1;
   const double lower = -2.;
   const double upper = 2.;

//     printf( "    int " );
//     for ( int q = 0;  q < N+1;  q++ )
//        printf( "x_%d = %g;  ", q, x[q] );
//     printf( "\n" );

   double tot = 0.;
   if ( i == final )
      for ( x[i] = lower;  x[i] < upper;  x[i] += dx )
	 tot += exp( -S_lat( x ) ) * dx;
   else
      for ( x[i] = lower;  x[i] < upper;  x[i] += dx )
	 tot += integrate( x, i + 1, final ) * dx;

   return tot;
}

double psi( double x_ )
{
   double x[N+1];  // from 0 to N
   x[0] = x[N] = x_;

   printf( "Calculating psi(%g)...\n", x_ );

   return A * integrate( x, 1, N-1 );
}

void sho1()
{
   double nconst = 0.;
   double x_ = 0.;

   for ( int k = 0;  k < 10;  k++ )
   {
      x_ += 0.2;
      double psix = psi( x_ );
      printf( "  unnormalized |psi(%g)|^2 = %g\n", x_, psix );
      nconst += psix;
      px[k] = psix;
   }
   printf( "\n" );

   for ( int k = 0;  k < 10;  k++ )
   {
      px[k] /= nconst;
      px[k] = sqrt( px[k] );
   }

   printf( "normalized psi = " );
   for ( int k = 0;  k < 10;  k++ )
      printf( "%g ", px[k] );
   printf( "\n" );

   double E0 = -log( nconst/10 ) / T;
   printf( "E_0 = %g\n", E0 );
}
