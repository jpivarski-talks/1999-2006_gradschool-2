/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                      S     W+    !  W+    S                         
                    ==<==@-1>-----!-->1-@==<==                       
                      P1 |  P3    !  P3 |  P1                        
                        u|P6      !    u|-P8                         
                         |  B     !  B  |                            
                         @==<=====!==<==@                            
                         |  P5    !  P5 |                            
                       W+|P7      !   W+|-P9                         
                      u  2  b     !  b  3  u                         
                    ==>==@==>=====!==>==@==>==                       
                      P2    P4    !  P4    P2                        
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F985;
double F985(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[17];double S[7];                                            
     
if(calcCoef[9])
{
S[0]=va[13]*va[13]*va[13]*va[13];
S[1]=va[10]*va[10];
C[0]=+S[0]*S[1];
S[2]=va[13]*va[13];
C[1]=+S[2]*(S[2]+2*S[1]);
C[2]=+4*S[0];
C[3]=+4*S[2];
C[4]=+8*S[2]*S[1];
C[5]=+16*S[2];
C[6]=+2*S[2]+4*S[1];
C[7]=+8*S[1];
C[8]=+8*(S[2]+S[1]);
C[9]=+2*S[0]*S[1];
C[10]=+S[2]*(4*(S[2]+S[1]));
C[11]=+2*S[2]*S[1];
C[12]=+2*S[2];
C[13]=+4*S[2]*S[1];
C[14]=+8*S[2];
S[3]=va[2]*va[2]*va[2]*va[2]*va[2]*va[2];
C[15]=+8*S[3];
S[4]=va[21]*va[21]*va[21]*va[21];
S[5]=va[20]*va[20];
S[6]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[16]=+S[4]*S[5]*S[6];
}
TOTNUM=+C[16];
S[0]=va[28]*va[28]*va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[15]*S[0];
S[1]=va[28]*va[28];
RNUM=+S[1]*(DP[4]*(DP[1]*(C[14]*(DP[7]*(DP[2]-DP[0]+DP[3]-DP[5])+DP[9]*(
 DP[0]-DP[2]-DP[3]+DP[5])+DP[6]*(DP[1]-S[1]-DP[4])+DP[8]*(S[1]+DP[4]))+C[2]*
 DP[6]-C[10]*DP[8])+S[1]*(C[12]*(DP[0]*(DP[9]-DP[7])+DP[3]*(DP[7]-DP[9])+
 DP[6]*(-S[1]-DP[4]))+C[1]*DP[6]-C[13]*DP[8])+C[11]*(DP[0]*(DP[7]-DP[9])+
 DP[3]*(DP[9]-DP[7])+DP[6]*DP[4])+C[13]*(DP[2]*(DP[9]-DP[7])+DP[5]*(DP[7]-
 DP[9])-DP[8]*DP[4])+C[9]*DP[8]-C[0]*DP[6])+S[1]*(DP[7]*(DP[1]*(DP[3]*(16*(
 DP[1]-S[1])+C[14])+DP[5]*(16*S[1]-C[8])+C[5]*(DP[2]-DP[0]))+S[1]*(DP[3]*(
 C[6]-4*S[1])-C[3]*DP[0]-C[7]*DP[5])+C[13]*(DP[0]+DP[5])-C[4]*DP[2]-C[11]*
 DP[3])+DP[9]*(DP[0]*(C[12]*S[1]-C[11]+C[14]*DP[1])+DP[2]*(C[13]-C[14]*
 DP[1])))+DP[1]*(DP[7]*(DP[1]*(C[5]*DP[0]-C[14]*DP[3])+C[13]*DP[5]-C[4]*
 DP[2])+DP[9]*(C[13]*DP[2]-C[14]*DP[1]*DP[0])))+DP[1]*(DP[4]*(DP[1]*(C[14]*(
 DP[0]*(DP[7]-DP[9])+DP[3]*(DP[9]-DP[7])+DP[6]*DP[4])-C[2]*DP[6])+C[13]*(
 DP[2]*(DP[9]-DP[7])+DP[5]*(DP[7]-DP[9])-DP[8]*DP[4])+C[9]*DP[8]));
result=RNUM*(TOTNUM/TOTDEN)*Q2[4]*Q2[6]*Q0[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[1] += result*(1)/(1);
 }
 return result;
}
