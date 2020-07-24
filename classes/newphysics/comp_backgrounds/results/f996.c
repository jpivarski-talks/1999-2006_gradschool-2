/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
          S                 B     !  B                 S             
        ==<==\           /==<=====!==<==\           /==<==           
          P1 |           |  P5    !  P5 |           |  P1            
             |           |        !     |           |                
          u  |  W+    A  |  b     !  b  |  A     W+ |  u             
        ==>==@-1>--@-3---@==>=====!==>==@---5-@-->4-@==>==           
          P2    P6 |  P7    P4    !  P4   -P9 | -P8    P2            
                   |              !           |                      
                   |        W+    !  W+       |                      
                   \-------2>-----!-->2-------/                      
                            P3    !  P3                              
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F996;
double F996(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[29];double S[10];double tmp[4];                             
     
if(calcCoef[9])
{
S[0]=va[13]*va[13]*va[13]*va[13];
S[1]=va[10]*va[10]*va[10]*va[10];
C[0]=+2*S[0]*S[1];
S[2]=va[13]*va[13];
S[3]=va[10]*va[10];
C[1]=+S[3]*(S[2]*(4*S[2]-S[3]));
C[2]=+S[2]*(10*S[2]+7*S[3]);
C[3]=+4*S[0]*S[3];
C[4]=+4*S[2];
C[5]=+16*S[2]*S[3];
C[6]=+6*S[2]*S[3];
C[7]=+3*S[2]*S[3];
C[8]=+8*S[2];
C[9]=+6*S[2];
C[10]=+2*(S[2]-S[3]);
C[11]=+2*S[2]*S[1];
C[12]=+S[3]*(4*S[2]-2*S[3]);
C[13]=+4*S[2]*S[3];
C[14]=+S[2]*S[1];
C[15]=+2*S[2];
C[16]=+2*S[2]*S[3];
C[17]=+4*S[2]*S[1];
C[18]=+S[3]*(8*S[2]-S[3]);
C[19]=+12*S[2]+5*S[3];
C[20]=+8*S[2]*S[3];
C[21]=+8*S[3];
C[22]=+S[3];
C[23]=+S[1];
C[24]=+2*S[3];
C[25]=+2*S[1];
C[26]=+4*S[3];
S[4]=va[2]*va[2];
C[27]=+9*S[4];
S[5]=va[20]*va[20];
S[6]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[28]=+S[5]*S[6];
}
TOTNUM=+C[28];
S[0]=va[28]*va[28]*va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[27]*S[0];
S[1]=va[28]*va[28];
S[2]=DP[1]*DP[1];
S[3]=DP[2]*DP[2];
tmp[0]=+DP[7]*(DP[3]*(2*(S[1]*(DP[6]-DP[3]-DP[7]-DP[9])+DP[5]*DP[2]+DP[8]*
 DP[1])+C[24]*(DP[3]-DP[6]-DP[7]+DP[9])+4*(DP[2]*DP[1]+DP[8]*DP[5])+C[15]*
 S[1]-C[16])+DP[1]*(DP[5]*(2*(S[1]-DP[6]+DP[7]+DP[9])+C[10])+DP[9]*(C[26]-4*
 S[1]+2*DP[8])+C[20]-C[8]*S[1]+C[15]*DP[8])+DP[6]*(S[1]*(C[9]+2*DP[9])+
 DP[5]*(-2*DP[2]-4*DP[5])-C[6]-C[24]*DP[9])+DP[9]*(C[24]*(-S[1]-DP[7])+
 C[25]+C[21]*DP[2])+DP[5]*(C[24]*S[1]-C[25]-C[26]*DP[2])+C[11]-C[16]*S[1]+
 C[5]*DP[2]-C[6]*DP[7])+DP[2]*(DP[3]*(2*(DP[8]*(S[1]+DP[3]-DP[6]+DP[9])+
 DP[5]*(DP[9]-DP[6]))+S[1]*(-C[8]-4*DP[9])+C[20]+C[15]*DP[5]-4*DP[6]*DP[2]+
 C[10]*DP[8]+C[26]*DP[9])+DP[6]*(DP[5]*(2*(S[1]+DP[6]+DP[9])+C[10])+DP[9]*(
 C[26]-4*S[1]+2*DP[8])+C[20]-C[8]*S[1]+C[15]*DP[8])+DP[9]*(C[24]*(DP[2]-
 S[1]+DP[5]+DP[8])+C[25])+C[16]*(DP[5]-S[1]-DP[2]+DP[8])+DP[1]*(C[4]*S[1]-
 C[13])+C[11]);
tmp[1]=+DP[0]*(S[1]*(DP[9]*(2*(-S[1]-DP[0]-DP[3]-DP[4]-DP[6]-DP[7]-DP[9])+4*
 (DP[5]-DP[1]-DP[2]+DP[8])-C[19])+C[9]*(-DP[0]-DP[3]-DP[4]-DP[6]-DP[7])+2*(
 DP[3]*(DP[6]-DP[7])+DP[4]*(DP[7]-DP[6]))+4*(DP[5]*(DP[6]+DP[7])+DP[8]*(
 DP[3]+DP[4]))+C[4]*(-S[1]-DP[1]-DP[2])+C[8]*(DP[5]+DP[8])-C[2])+DP[9]*(
 C[24]*(DP[0]-DP[1]+DP[2]-DP[3]+DP[4]-DP[6]+DP[7])+2*(DP[1]*(DP[5]+DP[8])+
 DP[2]*(DP[5]+DP[8]))+4*(-DP[2]*DP[1]-DP[8]*DP[5])-C[18]-C[26]*DP[9])+DP[5]*
 (2*(DP[1]*(DP[6]+DP[7])+DP[2]*(DP[6]+DP[7]))+C[9]*(DP[1]+DP[2])+C[24]*(
 DP[6]-DP[7])+C[15]*DP[5]+C[26]*DP[8])+DP[8]*(2*(DP[1]*(DP[3]+DP[4])+DP[2]*(
 DP[3]+DP[4]))+C[9]*(DP[1]+DP[2])+C[24]*(DP[3]-DP[4])+C[15]*DP[8])+C[16]*(
 DP[0]-DP[1]+DP[2]-DP[3]+DP[4]-DP[6]+DP[7])+C[15]*(S[2]+S[3])-C[1]);
S[4]=DP[3]*DP[3];
S[5]=DP[4]*DP[4];
S[6]=DP[6]*DP[6];
S[7]=DP[7]*DP[7];
S[8]=DP[5]*DP[5];
S[9]=DP[8]*DP[8];
tmp[2]=+DP[0]*(DP[9]*(C[24]*(DP[3]*(DP[4]-DP[6]-DP[7])+DP[5]*(DP[1]-DP[2]+
 DP[5])+DP[8]*(DP[1]-DP[2]+DP[8])+DP[4]*(-DP[6]-DP[7])+DP[7]*DP[6])+C[26]*(
 DP[1]*(-DP[3]-DP[4]-DP[6]-DP[7])+DP[2]*(-DP[3]-DP[4]-DP[6]-DP[7])+DP[8]*
 DP[5]+DP[9]*DP[0])+C[22]*(S[4]+S[5]+S[6]+S[7])+C[17]+C[20]*DP[0]+C[25]*
 DP[9])+DP[1]*(C[20]*(-DP[3]-DP[4]-DP[6]-DP[7])+C[24]*(DP[5]*(DP[6]+DP[7])+
 DP[8]*(DP[3]+DP[4]))+C[16]*(DP[1]+DP[5]+DP[8])+C[13]*DP[2])+DP[2]*(C[20]*(-
 DP[3]-DP[4]-DP[6]-DP[7])+C[24]*(DP[5]*(DP[6]+DP[7])+DP[8]*(DP[3]+DP[4]))+
 C[16]*(DP[2]-DP[5]-DP[8]))+C[16]*(DP[3]*(DP[6]+DP[7])+DP[4]*(DP[6]+DP[7])+
 S[8]+S[9])+C[7]*(S[4]+S[5]+S[6]+S[7])+DP[0]*(C[3]-C[26]*DP[8]*DP[5])+C[6]*(
 DP[4]*DP[3]+DP[7]*DP[6])+C[0]+C[12]*DP[8]*DP[5]);
tmp[3]=+S[1]*(S[1]*(DP[4]*(2*(S[1]*(DP[6]*(DP[3]-DP[4]-DP[6]+DP[7]-DP[9])+
 DP[3]*(DP[7]+DP[9])+DP[8]*DP[1])+DP[1]*(DP[8]*(DP[4]-DP[3]-DP[7]+DP[9])+
 DP[5]*(DP[6]-DP[7]+DP[9]))+DP[2]*(DP[8]*(DP[6]-DP[3])))+C[24]*(DP[6]*(
 DP[6]-DP[3]-DP[4]+DP[7]+DP[9])+DP[9]*(-S[1]-DP[3]-DP[4])+DP[7]*DP[3]+DP[8]*
 S[1])+DP[1]*(4*(DP[6]*DP[2]-DP[7]*DP[1]-DP[9]*S[1])+C[20]-C[8]*S[1]+C[15]*
 DP[5]+C[10]*DP[8]+C[26]*DP[9])+S[1]*(C[9]*DP[3]-C[16]+C[15]*DP[6]+C[26]*
 DP[7])+DP[8]*(4*(DP[6]*DP[5]-DP[8]*DP[3])-C[25]-C[26]*DP[2])+DP[9]*(C[25]+
 C[21]*DP[2]+C[26]*DP[7])+C[6]*(-DP[3]-DP[4])+C[11]+C[5]*DP[2]-C[16]*DP[6]-
 C[13]*DP[7])+tmp[0]+tmp[1])+DP[2]*(DP[5]*(C[24]*(DP[6]*(DP[3]-DP[6]-DP[7]-
 DP[9])+DP[3]*(DP[7]-DP[9]))+DP[9]*(C[26]*(-DP[4]-DP[7])-C[25])+C[16]*(-
 DP[3]-DP[6])+C[13]*(-DP[4]-DP[7])-C[11])+DP[8]*(C[24]*(DP[3]*(DP[6]-DP[3]-
 DP[4]-DP[9])+DP[6]*(DP[4]-DP[9]))+DP[9]*(C[26]*(-DP[4]-DP[7])-C[25])+C[16]*
 (-DP[3]-DP[6])+C[13]*(-DP[4]-DP[7])-C[11]))+DP[1]*(C[24]*(DP[4]*(DP[8]*(
 DP[3]+DP[4]-DP[7]-DP[9])+DP[5]*(-DP[6]-DP[7]-DP[9]))+DP[7]*(DP[5]*(DP[6]+
 DP[7]-DP[9])+DP[8]*(-DP[3]-DP[9])))+C[16]*(DP[4]*(-DP[5]-DP[8])+DP[7]*(-
 DP[5]-DP[8])))+C[26]*(DP[5]*(DP[7]*(DP[5]*(DP[6]+DP[7])-DP[8]*DP[3])-DP[8]*
 DP[6]*DP[4])+S[9]*(DP[4]*(DP[3]+DP[4])))-C[21]*DP[8]*DP[7]*DP[5]*DP[4]+
 tmp[2]);
RNUM=+DP[0]*(DP[5]*(DP[9]*(C[24]*(DP[1]*(DP[3]+DP[4]+DP[6]+DP[7])+DP[2]*(
 DP[3]+DP[4]+DP[6]+DP[7])-DP[5]*DP[0])+DP[8]*(-C[25]-C[26]*DP[0])-C[23]*
 DP[5])+C[16]*(DP[1]*(DP[3]+DP[4]+DP[6]+DP[7])+DP[2]*(DP[3]+DP[4]+DP[6]+
 DP[7])-DP[5]*DP[0])+DP[8]*(C[26]*(DP[3]*(DP[6]+DP[7])+DP[4]*(DP[6]+DP[7]))-
 C[11]-C[13]*DP[0])+DP[5]*(DP[6]*(-C[24]*DP[6]-C[26]*DP[7])-C[14]-C[24]*
 S[7]))+DP[8]*(C[24]*(DP[9]*(DP[1]*(DP[3]+DP[4]+DP[6]+DP[7])+DP[2]*(DP[3]+
 DP[4]+DP[6]+DP[7])-DP[8]*DP[0])+DP[8]*(-S[4]-S[5]))+C[16]*(DP[1]*(DP[3]+
 DP[4]+DP[6]+DP[7])+DP[2]*(DP[3]+DP[4]+DP[6]+DP[7])-DP[8]*DP[0])+DP[8]*(-
 C[14]-C[26]*DP[4]*DP[3]-C[23]*DP[9])))+tmp[3];
result=RNUM*(TOTNUM/TOTDEN)*Q2[2]*Q2[5]*Q0[1]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
