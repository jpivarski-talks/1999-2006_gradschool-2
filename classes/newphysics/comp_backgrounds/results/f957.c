/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                S           W+    !  W+          S                   
              ==<==@-------1>-----!-->1-------@==<==                 
                P1 |        P3    !  P3       |  P1                  
                   |              !           |                      
                   |        B     !  B        |                      
                  u|P6   /==<=====!==<==\    u|-P8                   
                   |     |  P5    !  P5 |     |                      
                   |     |        !     |     |                      
                u  |  G  |  b     !  b  |  G  |  u                   
              ==>==@-2---@==>=====!==>==@---3-@==>==                 
                P2    P7    P4    !  P4   -P9    P2                  
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F957;
double F957(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[8];double S[5];                                             
     
if(calcCoef[9])
{
S[0]=va[13]*va[13];
S[1]=va[10]*va[10];
C[0]=+S[0]*S[1];
C[1]=+S[0];
C[2]=+2*S[0]*S[1];
C[3]=+4*S[0];
C[4]=+S[1];
C[5]=+2*S[1];
S[2]=va[2]*va[2];
C[6]=+9*S[2];
S[3]=va[20]*va[20];
S[4]=va[1]*va[1];
C[7]=+4*S[3]*S[4];
}
S[0]=va[14]*va[14]*va[14]*va[14];
TOTNUM=+C[7]*S[0];
S[1]=va[28]*va[28];
TOTDEN=+C[6]*S[1];
RNUM=+S[1]*(DP[1]*(4*(DP[4]*(DP[8]-DP[6])+DP[7]*(DP[5]-DP[3]))+C[3]*(DP[2]-
 DP[0]))+S[1]*(-C[1]*DP[0]-DP[6]*DP[4]-DP[7]*DP[3])+DP[4]*(C[4]*DP[6]-C[5]*
 DP[8])+DP[7]*(C[4]*DP[3]-C[5]*DP[5])+C[0]*DP[0]-C[2]*DP[2])+DP[1]*(DP[1]*(
 4*(DP[6]*DP[4]+DP[7]*DP[3])+C[3]*DP[0])+C[5]*(-DP[7]*DP[5]-DP[8]*DP[4])-
 C[2]*DP[2]);
result=RNUM*(TOTNUM/TOTDEN)*Q2[4]*Q2[5]*Q0[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[1] += result*(9)/(8);
 }
 return result;
}
