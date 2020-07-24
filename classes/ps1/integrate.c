/*
  Integration Routines for PS#1
 */

/* Standard C header for using I/O and math libraries */
#include <stdio.h>
#include <math.h>

const double halfpi = 1.5707963267948966192313216916397514420976432;

double trapint( double f[], double r[], double dr[], int N )
{
  int i;
  double sum, h;

  /* I'm going to assume that the u's are always equally spaced */
  h = 1. / ( (double)( N ) );

  /* This one is done intuitively. */
  sum = 0.;
  for ( i = 0;  i < N;  i++ )
    sum += ( f[i]*dr[i] + f[i+1]*dr[i+1] ) * h / 2.;

  return sum;
}

double simpint( double f[], double r[], double dr[], int N )
{
  int i;
  double sum, h;

  /* I'm going to assume that the u's are always equally spaced */
  h = 1. / ( (double)( N ) );

  /* This one is done efficiently. */
  sum = 0.;

  for ( i = 1;  i < N;  i+=2 )
    sum += 4. * f[i] * dr[i];

  for ( i = 2;  i < N;  i+=2 )
    sum += 2. * f[i] * dr[i];

  sum += f[0] * dr[0];
  sum += f[N] * dr[N];
  
  return sum * h / 3.;
}

double integrate( double (* func)( double ), double low, double high, int N )
{
   int i;
   double u;
   double r[N+1], dr[N+1], f[N+1];

   for ( i = 0;  i <= N;  i++ ) {
      /* Let u be equally spaced between 0 and 1, -inclusive- */
      u = ((double) i) / ((double) N);

      r[i] = low + ( high - low ) * u;
      dr[i] = ( high - low );

      f[i] = func( r[i] );
   }
   return simpint( f, r, dr, N );
}

double integrate_zero_to_inf( double (* func)( double ), int N )
{
   int i;
   double u;
   double r[N+1], dr[N+1], f[N+1];

   for ( i = 0;  i <= N;  i++ ) {
      /* Let u be equally spaced between 0 and 1, -inclusive- */
      u = ((double) i) / ((double) N);

      r[i] = tan( halfpi * u ) / halfpi;
      dr[i] = 1. / cos( halfpi * u );  dr[i] *= dr[i];

      f[i] = func( r[i] );
   }
   return simpint( f, r, dr, N );
}

double integrate_inf_to_inf( double (* func)( double ), int N )
{
   int i;
   double u;
   double r[N+1], dr[N+1], f[N+1];

   for ( i = 0;  i <= N;  i++ ) {
      /* Let u be equally spaced between 0 and 1, -inclusive- */
      u = ((double) i) / ((double) N);

      r[i] = tan( halfpi * ( 2. * u - 1. ) ) / halfpi;
      dr[i] = 1. / cos( halfpi * ( 2. * u - 1. ) );  dr[i] *= 2. * dr[i];

      f[i] = func( r[i] );
   }
   return simpint( f, r, dr, N );
}


