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
                |        B  |  !  B                 S                
               u|P6   /==<==+==!==<==\           /==<==              
                |     |  P5 |  !  P5 |           |  P1               
                |     |     |  !     |           |                   
             u  |  A  |  b  |  !  b  |  A     W+ |  u                
           ==>==@-2---@==>==+==!==>==@---4-@-->3-@==>==              
             P2    P7    P4 |  !  P4   -P9 | -P8    P2               
                            |  !           |                         
                            |  !  W+       |                         
                            \--!-->1-------/                         
                               !  P3                                 
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F965;
double F965(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[18];double S[6];double tmp[1];                              
     
if(calcCoef[9])
{
S[0]=va[13]*va[13];
C[0]=+6*S[0];
C[1]=+S[0];
S[1]=va[10]*va[10];
C[2]=+5*S[0]*S[1];
C[3]=+S[0]*S[1];
C[4]=+7*S[0];
C[5]=+2*S[0];
C[6]=+4*S[0]*S[1];
C[7]=+2*S[0]*S[1];
C[8]=+4*S[0];
S[2]=va[10]*va[10]*va[10]*va[10];
C[9]=+S[0]*S[2];
C[10]=+3*S[0]*S[1];
C[11]=+4*S[1];
C[12]=+3*S[1];
C[13]=+2*S[1];
C[14]=+S[2];
C[15]=+S[1];
S[3]=va[2]*va[2];
C[16]=+27*S[3];
S[4]=va[20]*va[20];
S[5]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[17]=+4*S[4]*S[5];
}
TOTNUM=-C[17];
S[0]=va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[16]*S[0];
S[1]=va[28]*va[28];
tmp[0]=+DP[1]*(2*(DP[3]*(DP[7]*(-DP[1]-DP[2]-DP[5]-DP[8])-DP[8]*DP[0]-DP[9]*
 DP[2])+DP[4]*(DP[6]*(-DP[1]-DP[2]-DP[5]-DP[8])-DP[8]*DP[0]-DP[9]*DP[1])+
 DP[0]*(DP[5]*(-DP[6]-DP[7]))+DP[9]*(-DP[6]*DP[2]-DP[7]*DP[1]))+DP[4]*(
 DP[1]*(4*DP[7]-C[5])+DP[8]*(C[12]+4*DP[3])-C[3]-C[13]*DP[6]-C[15]*DP[9])+
 DP[2]*(DP[3]*(4*DP[6]-C[5])+C[7]-C[8]*DP[0]-C[5]*DP[6]-C[13]*DP[9])+DP[7]*(
 DP[5]*(C[12]+4*DP[6])-C[3]-C[5]*DP[1]-C[13]*DP[3]-C[15]*DP[9])+DP[0]*(C[8]*
 (-DP[1]-DP[5]-DP[8])-C[7]))+DP[2]*(DP[9]*(C[15]*(DP[5]-DP[3]-DP[6]+DP[8])+
 C[13]*(-DP[4]-DP[7])-C[14])+C[10]*(DP[5]-DP[3]-DP[6]+DP[8])+DP[4]*(C[11]*
 DP[8]-C[6]-C[13]*DP[6])+DP[7]*(C[11]*DP[5]-C[6]-C[13]*DP[3])+C[15]*(DP[6]*
 DP[5]+DP[8]*DP[3])+C[6]*DP[2]-C[9]-C[7]*DP[0])+C[15]*(DP[4]*(DP[6]*(DP[4]-
 DP[3]+DP[5]+DP[6]-DP[7]-DP[8])+DP[8]*(DP[8]-DP[5])-DP[7]*DP[3])+DP[7]*(
 DP[3]*(DP[3]-DP[5]-DP[6]+DP[7]+DP[8])+DP[5]*(DP[5]-DP[8])))+DP[0]*(C[7]*(
 DP[3]+DP[4]+DP[6]+DP[7])-C[13]*DP[8]*DP[5])+C[14]*(DP[4]*(DP[8]+DP[9])+
 DP[7]*(DP[5]+DP[9]))+C[9]*(DP[4]+DP[7]);
RNUM=+S[1]*(S[1]*(DP[0]*(DP[9]*(2*(S[1]+DP[3]-DP[5]+DP[6]-DP[8])+4*DP[1])+
 C[8]*(S[1]+DP[0]-DP[5]-DP[8])+3*(DP[5]*(-DP[6]-DP[7])+DP[8]*(-DP[3]-
 DP[4]))+C[0]*(DP[1]+DP[3]+DP[6])+4*(DP[6]*DP[4]+DP[7]*DP[3])+C[7]-C[5]*
 DP[2])+DP[4]*(DP[6]*(2*(DP[6]-DP[3])+C[12]+DP[1]+DP[2]+DP[5]-DP[8])+DP[1]*(
 C[4]-2*DP[7]-4*DP[8]+3*DP[9])-C[2]-C[13]*DP[7]-C[15]*DP[9])+DP[7]*(DP[3]*(
 2*(DP[3]-DP[6])+C[12]+DP[1]+DP[2]-DP[5]+DP[8])+DP[1]*(C[4]-4*DP[5]+3*
 DP[9])-C[2]-C[15]*DP[9])+DP[2]*(DP[3]*(C[1]+6*DP[6]+DP[9])+DP[6]*(C[1]+
 DP[9])-C[10]-C[8]*DP[1]-C[12]*DP[9]))+tmp[0])+C[15]*(DP[5]*(DP[6]*(DP[2]*(
 DP[3]-DP[6]-DP[7])+DP[0]*(DP[8]-DP[5])+DP[1]*(DP[4]-DP[7]))+DP[7]*(DP[0]*(
 DP[8]-DP[5])+DP[1]*(DP[4]-DP[7])+DP[3]*DP[2])+DP[0]*(DP[8]*(DP[3]+DP[4])))+
 DP[8]*(DP[3]*(DP[2]*(DP[6]-DP[3]-DP[4])+DP[1]*(DP[7]-DP[4])-DP[8]*DP[0])+
 DP[4]*(DP[1]*(DP[7]-DP[4])+DP[6]*DP[2]-DP[8]*DP[0])))+DP[2]*(DP[1]*(DP[9]*(
 C[13]*(DP[3]+DP[4]+DP[6]+DP[7]))+C[7]*(DP[3]+DP[4]+DP[6]+DP[7]))+DP[5]*(-
 C[9]-C[14]*DP[9])+DP[8]*(-C[9]-C[14]*DP[9]));
result=RNUM*(TOTNUM/TOTDEN)*Q1[4]*Q2[5]*Q1[2]*Q0[1]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
