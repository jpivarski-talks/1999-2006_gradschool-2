/*
  Main program for PS#1
  Tests Simpson and Trapezoid integration routines
 */


/* Standard C header for using I/O and math libraries */
#include <stdio.h>
#include <math.h>

const double pi = 3.1415926535897932384626433832795028841971694;

extern double trapint( double f[], double r[], double dr[], int N );
extern double simpint( double f[], double r[], double dr[], int N );
extern double integrate( double (* func)( double ), double low, double high, int N );
extern double integrate_zero_to_inf( double (* func)( double ), int N );
extern double integrate_inf_to_inf( double (* func)( double ), int N );

/* I wish I wish I wish c implemented lambda functions! */

double testfunc( double x ) { return exp( -x*x/2. ); }
double radial_prob_1s( double r ) { return exp( -2.*r ) / pi * ( 4.*pi*r*r ); }
double radial_nuc_1s( double r ) { return exp( -2.*r ) / pi * ( -4.*pi*r ); }
double radial_elec_1s( double r ) { return exp( -2.*r ) / pi *
				       ( 1. - exp(-2.*r) - r * exp(-2.*r) ) *
				       ( -4.*pi*r ); }

/* Maximum size of N for integrations */
#define Nmx 200000
main()
{
  /* Declare space for arrays, remember that there are N+1 points! */
  /* Double precision for accurate numerical work... */
  double r[Nmx+1], dr[Nmx+1], f[Nmx+1];

  /* Declare working variables */
  int i, N;
  double u;

  /* Loop over sizes 2, 20, 200, 2000, ..., Nmx */
  for ( N = 2;  N <= Nmx;  N *= 10 ) {
    /* For each size, fill in arrays */
    for ( i = 0;  i <= N;  i++ ) {
      /* Let u be equally spaced between 0 and 1, -inclusive- */
      u = ((double) i) / ((double) N);

      /* Define change of variables */
      r[i] = u;
      dr[i] = 1.;

      /* Specify function */
      f[i] = 1 / (1+r[i]*r[i]) / (1+r[i]*r[i]) / (0.25+0.125*pi);
    }

    /* Special cases at end points (reasons for this will become clear...) */
    f[0] = f[0];
    r[0] = r[0];
    dr[0] = dr[0];

    f[N] = f[N];
    r[N] = r[N];
    dr[N] = dr[N];

    /* Call integration routines and output results... */
    printf("Trap, Simp: %7d %20.14f, %20.14f\n",
	   N, trapint(f,r,dr,N), simpint(f,r,dr,N) );
  }

  printf( "%40s = %20.14f\n", "int_0^1 exp( -x^2 / 2. )",
	  integrate( testfunc, 0., 1., 2000 ) );
  printf( "%40s = %20.14f\n\n", "int_1^2 exp( -x^2 / 2. )",
	  integrate( testfunc, 1., 2., 2000 ) );
  printf( "%40s = %20.14f\n", "int_-5^5 exp( -x^2 / 2. )",
	  integrate( testfunc, -5., 5., 2000 ) );
  printf( "%40s = %20.14f\n", "int_0^\\infty exp( -x^2 / 2. )",
	  integrate_zero_to_inf( testfunc, 2000 ) );
  printf( "%40s = %20.14f\n", "int_{-\\infty}^\\infty exp( -x^2 / 2. )",
	  integrate_inf_to_inf( testfunc, 2000 ) );
  printf( "%40s = %20.14f\n\n", "sqrt( 2 \\pi )",
	  sqrt( 2. * pi ) );

  printf( "Problem 2.1:\n" );
  printf( "%50s = %20.14f\n\n", "int_0^\\infty \\psi_{1s}^2(r) 4 \\pi r^2",
	  integrate_zero_to_inf( radial_prob_1s, 2000 ) );

  printf( "Problem 2.2:\n" );
  printf( "%50s = %20.14f\n\n", "int_0^\\infty \\psi_{1s}^2(r) (-1/r) 4 \\pi r^2",
	  integrate_zero_to_inf( radial_nuc_1s, 2000 ) );

  printf( "Problem 2.3:\n" );
  printf( "%50s\n%50s = %20.14f\n",
	  "int_0^\\infty \\psi_{1s}^2(r) *              ",
	  "* ( 1 - e^{-2r} - r e^{-2r} )/r 4 \\pi r^2",
	  integrate_zero_to_inf( radial_elec_1s, 2000 ) );
}
