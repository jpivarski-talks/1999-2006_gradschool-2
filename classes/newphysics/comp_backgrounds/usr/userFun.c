/* Copyright (C) 1997, Alexander Pukhov 
   with example by V.Ilyin              */
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "num/include/4_vector.h"
#include "userFun.h"

double 
userFunction (char *name)
{
/*
    The following commented line is a example of use userFunction.
    It define user variable "UMtAv" that calculate in the process
    of MC integration. This variable can use in the cut-table.
    More details see in Manual :-)
    
*/
/*
  double pt3, pt4, pt5, pt6, qsc;

  pt3 = pvect[8 + 1] * pvect[8 + 1] + pvect[8 + 2] * pvect[8 + 2];
  pt4 = pvect[12 + 1] * pvect[12 + 1] + pvect[12 + 2] * pvect[12 + 2];
  pt5 = pvect[16 + 1] * pvect[16 + 1] + pvect[16 + 2] * pvect[16 + 2];
  pt6 = pvect[20 + 1] * pvect[20 + 1] + pvect[20 + 2] * pvect[20 + 2];
  qsc = sqrt ((175.0 * 175.0) + (pt3 + pt4 + pt5 + pt6) / 4.0);

  if (strcmp (name, "MtAv") == 0)
    {
      if (!finite (qsc))
	fprintf (stdout, " uvar= %18.15g\n", qsc);
      return qsc;
    }
*/

  fprintf (stdout, " ***** userFunction: not defined: %s\n", name);
  exit (10);
  return 0.;
}
