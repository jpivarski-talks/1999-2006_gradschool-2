/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                S           W+    !                                  
              ==<==@-------1>--\  !                                  
                P1 |        P3 |  !                                  
                   |           |  !                                  
                   |        B  |  !  B                               
                  u|P6   /==<==+==!==<==\                            
                   |     |  P5 |  !  P5 |                            
                   |     |     |  !     |                            
                u  |  G  |  b  |  !  b  |  G     S                   
              ==>==@-2---@==>==+==!==>==@---3-@==<==                 
                P2    P7    P4 |  !  P4   -P9 |  P1                  
                               |  !          s|-P8                   
                               |  !  W+       |  u                   
                               \--!-->1-------@==>==                 
                                  !  P3          P2                  
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F960;
double F960(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[10];double S[5];                                            
     
if(calcCoef[9])
{
S[0]=va[13]*va[13];
C[0]=+3*S[0];
S[1]=va[10]*va[10];
C[1]=+S[0]*S[1];
C[2]=+2*S[0];
C[3]=+4*S[0];
C[4]=+2*S[0]*S[1];
C[5]=+4*S[1];
C[6]=+S[1];
C[7]=+2*S[1];
S[2]=va[2]*va[2];
C[8]=+9*S[2];
S[3]=va[20]*va[20];
S[4]=va[1]*va[1];
C[9]=+8*S[3]*S[4];
}
S[0]=va[14]*va[14]*va[14]*va[14];
TOTNUM=-C[9]*S[0];
S[1]=va[28]*va[28];
TOTDEN=+C[8]*S[1];
RNUM=+S[1]*(DP[0]*(2*(DP[5]*(DP[6]+DP[7])+DP[8]*(DP[3]+DP[4])-DP[9]*S[1])+
 C[2]*(DP[1]+DP[2])+4*(-DP[6]*DP[4]-DP[7]*DP[3])-C[4]-C[0]*S[1]-C[3]*DP[0]-
 C[6]*DP[9])+DP[4]*(DP[6]*(S[1]-C[6])+DP[7]*(C[5]-4*DP[1])+C[6]*DP[8])+
 DP[2]*(C[1]-4*DP[6]*DP[3]+C[6]*DP[9])+DP[7]*(DP[3]*(S[1]-C[6])+C[6]*
 DP[5]))+DP[2]*(DP[1]*(4*(DP[6]*DP[4]+DP[7]*DP[3])+C[4]+C[3]*DP[0]+C[7]*
 DP[9])+DP[5]*(-C[6]*DP[6]-C[7]*DP[7])+DP[8]*(-C[6]*DP[3]-C[7]*DP[4])-C[4]*
 DP[2])+DP[1]*(C[6]*(-DP[7]*DP[5]-DP[8]*DP[4]))+C[7]*DP[8]*DP[5]*DP[0];
result=RNUM*(TOTNUM/TOTDEN)*Q1[4]*Q2[5]*Q1[8]*Q0[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[1] += result*(9)/(8);
 }
 return result;
}
