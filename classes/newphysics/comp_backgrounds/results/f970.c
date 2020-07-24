/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                   S           W+    !  W+    S                      
                 ==<==@-------1>-----!-->1-@==<==                    
                   P1 |        P3    !  P3 |  P1                     
                      |              !    c|-P8                      
                      |        B     !  B  |                         
                     u|P6   /==<=====!==<==@                         
                      |     |  P5    !  P5 |                         
                      |     |        !   W+|-P9                      
                   u  |  A  |  b     !  b  3  u                      
                 ==>==@-2---@==>=====!==>==@==>==                    
                   P2    P7    P4    !  P4    P2                     
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F970;
double F970(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[23];double S[6];                                            
     
if(calcCoef[9])
{
S[0]=va[13]*va[13]*va[13]*va[13];
S[1]=va[10]*va[10];
C[0]=+S[0]*S[1];
S[2]=va[13]*va[13];
C[1]=+S[2]*(S[2]-2*S[1]);
C[2]=+4*S[0];
C[3]=+2*S[0]*S[1];
C[4]=+S[2]*(4*(S[2]-S[1]));
S[3]=va[10]*va[10]*va[10]*va[10];
C[5]=+2*S[2]*S[3];
C[6]=+10*S[2]*S[1];
C[7]=+6*S[2];
C[8]=+16*S[2];
C[9]=+2*S[2];
C[10]=+S[2]*S[3];
C[11]=+5*S[2]*S[1];
C[12]=+3*S[2];
C[13]=+4*S[1];
C[14]=+8*S[1];
C[15]=+S[2]*S[1];
C[16]=+S[2];
C[17]=+2*S[2]*S[1];
C[18]=+4*S[2];
C[19]=+4*S[2]*S[1];
C[20]=+8*S[2];
S[4]=va[2]*va[2]*va[2]*va[2];
C[21]=+27*S[4];
S[5]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[22]=+va[24]*va[23]*va[21]*va[20]*S[5];
}
TOTNUM=-C[22];
S[0]=va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[21]*S[0];
S[1]=va[28]*va[28];
RNUM=+S[1]*(S[1]*(DP[7]*(DP[1]*(16*(DP[5]-DP[3])+C[12])+DP[3]*(C[13]-4*
 S[1])-C[15]-C[14]*DP[5])+DP[0]*(-C[1]-C[9]*S[1]-C[20]*DP[1]-C[16]*DP[8])+
 DP[2]*(C[20]*DP[1]-C[19]+C[16]*DP[6])+DP[4]*(C[7]*DP[1]-C[17]-C[9]*DP[6]))+
 DP[1]*(DP[1]*(DP[7]*(16*DP[3]-C[20])+C[20]*DP[0]-C[8]*DP[4])+DP[4]*(C[20]*(
 DP[8]-DP[6])+C[6])+DP[7]*(C[11]-C[14]*DP[5])+C[4]*DP[2]-C[2]*DP[0])+DP[4]*(
 C[17]*DP[6]-C[5]-C[19]*DP[8])+DP[0]*(C[0]-C[15]*DP[8])+DP[2]*(C[15]*DP[6]-
 C[3])-C[10]*DP[7])+DP[1]*(DP[1]*(DP[4]*(C[20]*(DP[1]+DP[6])-C[19])+C[18]*(
 DP[7]*DP[1]-DP[6]*DP[2]+DP[8]*DP[0])+C[2]*DP[0]-C[17]*DP[7])+DP[2]*(C[17]*
 DP[6]-C[3])+DP[8]*(-C[17]*DP[0]-C[19]*DP[4]));
result=RNUM*(TOTNUM/TOTDEN)*Q1[4]*Q1[5]*Q1[7]*Q1[6]*Q0[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
 }
 return result;
}
