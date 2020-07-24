/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
#include<math.h>
#define real double
#include"out_int.h"
#include"out_ext.h"
extern real *Q0,*Q1,*Q2;
extern double va[29];
DNN  d_4;
int d_4(real * momenta)
{int I,err=0;
real s0max=0;
 real DMASS[4],DWIDTH[4];
 if(Q0!=NULL) free(Q0);
 Q0=(real*)malloc(sizeof(real)*4);
 for(I=0;I<nin_;I++) s0max+=momenta[4*I];
s0max=computer_eps*s0max*s0max;
 if(Q1!=NULL) free(Q1);
 if(Q2!=NULL) free(Q2);
 Q1=(real*)malloc(sizeof(real)*12);
 Q2=(real*)malloc(sizeof(real)*12);
DMASS[3]=va[11];
DWIDTH[3]=va[12];
Q1[3]=va[11]*va[11]- sqrMom("\3\4",momenta);
Q1[11]=va[9]*va[9]- sqrMom("\3\4",momenta);
Q1[10]=- sqrMom("\3\4",momenta);
DMASS[2]=va[28];
DWIDTH[2]=va[8];
Q1[2]=va[28]*va[28]- sqrMom("\1\2",momenta);
DMASS[1]=va[6];
DWIDTH[1]=va[7];
Q1[1]=va[6]*va[6]- sqrMom("\4\5",momenta);
Q1[9]=va[11]*va[11]- sqrMom("\1\3",momenta);
Q1[8]=va[9]*va[9]- sqrMom("\1\3",momenta);
Q1[7]=- sqrMom("\2\3",momenta);
Q1[6]=va[28]*va[28]- sqrMom("\2\4",momenta);
Q1[5]=- sqrMom("\4\5",momenta);
Q1[4]=- sqrMom("\1\3",momenta);
for ( I=1;I<= 3;I++)
 {
  real q=Q1[I],w;
  if(gwidth==2) w=(DMASS[I]-Q1[I]/DMASS[I])*DWIDTH[I]; else w=DMASS[I]*
 DWIDTH[I];
  Q2[I]=1/(q*q+w*w);
  if (gwidth==1) Q0[I]=Q2[I]*q*q;else Q0[I]=1; 
  Q1[I]=Q2[I]*q;
 }
for ( I=4; I<=11;I++)
  {
  if((Q1[I]>0? Q1[I]:-Q1[I]) < 10*s0max) err=DENOMINATOR_ERROR;
  if(!Q1[I]) Q1[I]=s0max;
  Q1[I]=1/Q1[I];
  Q2[I]=Q1[I]*Q1[I];
}
return err;
}
