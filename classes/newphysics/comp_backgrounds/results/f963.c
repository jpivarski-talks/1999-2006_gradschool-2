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
                u  |  A  |  b     !  b  |  Z  |  u                   
              ==>==@-2---@==>=====!==>==@---3-@==>==                 
                P2    P7    P4    !  P4   -P9    P2                  
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F963;
double F963(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[14];double S[7];                                            
     
if(calcCoef[9])
{
S[0]=va[2]*va[2];
S[1]=va[13]*va[13];
S[2]=va[10]*va[10];
C[0]=+S[2]*(S[1]*(S[0]*(16*S[0]-24)+9));
C[1]=+S[1]*(S[0]*(16*S[0]-24)+9);
C[2]=+S[2]*(S[1]*(S[0]*(32*S[0]-48)+18));
C[3]=+S[1]*(S[0]*(64*S[0]-96)+36);
C[4]=+S[0]*(S[2]*(16*S[0]-12));
C[5]=+S[0]*(16*S[0]-12);
C[6]=+S[2]*(S[0]*(16*S[0]-36)+18);
C[7]=+S[0]*(16*S[0]-36)+18;
C[8]=+S[2]*(S[0]*(32*S[0]-72)+36);
C[9]=+S[0]*(64*S[0]-144)+72;
C[10]=+S[0]*(S[2]*(32*S[0]-24));
C[11]=+S[0]*(64*S[0]-48);
S[3]=va[15]*va[15];
S[4]=va[2]*va[2]*va[2]*va[2];
C[12]=+81*S[3]*S[4];
S[5]=va[20]*va[20];
S[6]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[13]=+S[5]*S[6];
}
TOTNUM=+C[13];
S[0]=va[28]*va[28];
TOTDEN=+C[12]*S[0];
RNUM=+S[0]*(DP[1]*(DP[4]*(C[11]*(DP[8]-DP[6]))+DP[7]*(C[9]*(DP[5]-DP[3]))+
 C[3]*(DP[2]-DP[0]))+S[0]*(-C[1]*DP[0]-C[5]*DP[6]*DP[4]-C[7]*DP[7]*DP[3])+
 DP[4]*(C[4]*DP[6]-C[10]*DP[8])+DP[7]*(C[6]*DP[3]-C[8]*DP[5])+C[0]*DP[0]-
 C[2]*DP[2])+DP[1]*(DP[1]*(C[3]*DP[0]+C[11]*DP[6]*DP[4]+C[9]*DP[7]*DP[3])-
 C[2]*DP[2]-C[8]*DP[7]*DP[5]-C[10]*DP[8]*DP[4]);
result=RNUM*(TOTNUM/TOTDEN)*Q2[4]*Q1[5]*Q1[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
