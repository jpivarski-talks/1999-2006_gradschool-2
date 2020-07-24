/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
#include<math.h>
#include"out_int.h"
#include"out_ext.h"
int gwidth=0;
 double va[29] ={2.000000E+03
,3.134500E-01
,4.807600E-01
,2.229000E-01
,4.120000E-02
,3.600000E-03
,9.118760E+01
,2.436310E+00
,2.027980E+00
,1.650000E+00
,1.170000E-01
,1.743000E+02
,1.546880E+00
,4.850000E+00
,1.213580E+00
,8.768522E-01
,9.748413E-01
,9.991509E-01
,9.999935E-01
,9.748350E-01
,2.228986E-01
,3.600000E-03
,-2.228553E-01
,9.739805E-01
,4.119973E-02
,5.677031E-03
,-4.096522E-02
,9.991444E-01
,7.995805E+01};
const int nin_ = 2;

const int nout_ = 3;

const int nprc_ = 12;

int pinf_(int nsub,int nprtcl,char* pname, double* pmass)
{
int n;
char names[12][5][7]={
 {"u","D","W+","b","B"},
 {"u","S","W+","b","B"},
 {"u","B","W+","b","B"},
 {"D","u","W+","b","B"},
 {"D","c","W+","b","B"},
 {"c","D","W+","b","B"},
 {"c","S","W+","b","B"},
 {"c","B","W+","b","B"},
 {"S","u","W+","b","B"},
 {"S","c","W+","b","B"},
 {"B","u","W+","b","B"},
 {"B","c","W+","b","B"}
};
int nvalue[12][5]={
 {0,0,28,13,13,},
 {0,10,28,13,13,},
 {0,13,28,13,13,},
 {0,0,28,13,13,},
 {0,9,28,13,13,},
 {9,0,28,13,13,},
 {9,10,28,13,13,},
 {9,13,28,13,13,},
 {10,0,28,13,13,},
 {10,9,28,13,13,},
 {13,0,28,13,13,},
 {13,9,28,13,13},
};
if  (nsub<0 ||nsub>12||nprtcl<0||nprtcl>5) return 1;
if(pname) strcpy(pname,names[nsub-1][nprtcl-1]);
if(pmass)
{
  n=nvalue[nsub-1][nprtcl-1];
if (n>14) if (calcFunc()) return FUCTION_ERROR;
if (n==0) *pmass=0; else *pmass=va[n];
if (*pmass<0) (*pmass)=-(*pmass);
}
return 0;
}
const int nvar_ = 14;

const int nfunc_ = 14;

int vinf_(int numvar,char * name, double * val)
{
char names[29][10]={"Sqrt(S)"
,"EE"
,"SW"
,"s12"
,"s23"
,"s13"
,"MZ"
,"wZ"
,"wW"
,"Mc"
,"Ms"
,"Mtop"
,"wtop"
,"Mb"
,"GG"
,"CW"
,"c12"
,"c23"
,"c13"
,"Vud"
,"Vus"
,"Vub"
,"Vcd"
,"Vcs"
,"Vcb"
,"Vtd"
,"Vts"
,"Vtb"
,"MW"};
   if(numvar<0||numvar>28  ) return 1;
   if(name) strcpy(name,names[numvar]);
   if(val) *val=va[numvar];
   return 0;
}

int asgn_(int numvar,double newval)
{
  if(numvar < 0|| numvar>14) return 1;
   va[numvar]=newval;
   return 0;
}

void cStrings(int nsub,int *nC, int * power, int **  chains)
{
   switch(nsub)
   {
   case 1 : 
     { static int cc[8]=
       {
        1,2, 5,4,
        1,4, 5,2
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 2 : 
     { static int cc[8]=
       {
        1,2, 5,4,
        1,4, 5,2
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 3 : 
     { static int cc[8]=
       {
        1,2, 5,4,
        1,4, 5,2
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 4 : 
     { static int cc[8]=
       {
        2,1, 5,4,
        2,4, 5,1
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 5 : 
     { static int cc[8]=
       {
        2,1, 5,4,
        2,4, 5,1
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 6 : 
     { static int cc[8]=
       {
        1,2, 5,4,
        1,4, 5,2
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 7 : 
     { static int cc[8]=
       {
        1,2, 5,4,
        1,4, 5,2
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 8 : 
     { static int cc[8]=
       {
        1,2, 5,4,
        1,4, 5,2
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 9 : 
     { static int cc[8]=
       {
        2,1, 5,4,
        2,4, 5,1
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 10 : 
     { static int cc[8]=
       {
        2,1, 5,4,
        2,4, 5,1
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 11 : 
     { static int cc[8]=
       {
        2,1, 5,4,
        2,4, 5,1
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   case 12 : 
     { static int cc[8]=
       {
        2,1, 5,4,
        2,4, 5,1
       };
       *nC=2; *power=2; *chains=cc;
     }
     break;
   default: *nC=0; *power=0; *chains=NULL;
   }
}

#include"extern.h"
int calcFunc(void)
{
int err=0;
   va[15]=sqrt((double)1-pow(va[2],(double)2));
   if(!finite(va[15])) return FUCTION_ERROR;
   va[16]=sqrt((double)1-pow(va[3],(double)2));
   if(!finite(va[16])) return FUCTION_ERROR;
   va[17]=sqrt((double)1-pow(va[4],(double)2));
   if(!finite(va[17])) return FUCTION_ERROR;
   va[18]=sqrt((double)1-pow(va[5],(double)2));
   if(!finite(va[18])) return FUCTION_ERROR;
   va[19]=va[16]*va[18];
   if(!finite(va[19])) return FUCTION_ERROR;
   va[20]=va[3]*va[18];
   if(!finite(va[20])) return FUCTION_ERROR;
   va[21]=va[5];
   if(!finite(va[21])) return FUCTION_ERROR;
   va[22]=-va[16]*va[4]*va[5]-va[3]*va[17];
   if(!finite(va[22])) return FUCTION_ERROR;
   va[23]=va[16]*va[17]-va[3]*va[4]*va[5];
   if(!finite(va[23])) return FUCTION_ERROR;
   va[24]=va[4]*va[18];
   if(!finite(va[24])) return FUCTION_ERROR;
   va[25]=va[3]*va[4]-va[16]*va[17]*va[5];
   if(!finite(va[25])) return FUCTION_ERROR;
   va[26]=-va[3]*va[17]*va[5]-va[16]*va[4];
   if(!finite(va[26])) return FUCTION_ERROR;
   va[27]=va[17]*va[18];
   if(!finite(va[27])) return FUCTION_ERROR;
   va[28]=va[6]*va[15];
   if(!finite(va[28])) return FUCTION_ERROR;
if(err) return 1; else return 0;
}
