/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                               !  W+                S                
             S           W+ /--!-->1-\           /==<==              
           ==<==@-------1>--/  !  P3 |           |  P1               
             P1 |        P3    !     |           |                   
                |              !  b  |  t     W+ |  u                
                |        B    /!==>==@==>==@-->3-@==>==              
               u|P6   /==<===\|!  P4   -P9 | -P8    P2               
                |     |  P5  ||!           |                         
                |     |      ||!  B        |                         
             u  |  A  |  b   \+!==<========/                         
           ==>==@-2---@==>====/!  P5                                 
             P2    P7    P4    !                                     
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F969;
double F969(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[20];double S[7];                                            
     
if(calcCoef[9])
{
S[0]=va[13]*va[13];
S[1]=va[10]*va[10]*va[10]*va[10];
C[0]=+3*S[0]*S[1];
S[2]=va[10]*va[10];
C[1]=+3*S[0]*S[2];
C[2]=+6*S[0];
C[3]=+2*S[0];
C[4]=+2*S[0]*S[1];
C[5]=+S[0]*S[1];
C[6]=+4*S[0];
C[7]=+8*S[0];
C[8]=+4*S[0]*S[2];
C[9]=+6*S[2];
C[10]=+8*S[2];
C[11]=+S[0]*S[2];
C[12]=+2*S[0]*S[2];
C[13]=+S[2];
C[14]=+S[1];
C[15]=+4*S[2];
C[16]=+2*S[2];
C[17]=+2*S[1];
S[3]=va[2]*va[2]*va[2]*va[2];
C[18]=+9*S[3];
S[4]=va[27]*va[27];
S[5]=va[20]*va[20];
S[6]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[19]=+S[4]*S[5]*S[6];
}
TOTNUM=+C[19];
S[0]=va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[18]*S[0];
S[1]=va[28]*va[28];
S[2]=DP[2]*DP[2];
RNUM=+S[1]*(DP[7]*(DP[3]*(S[1]*(8*(DP[5]-DP[1])+C[13]-4*S[1]-16*DP[3])+
 DP[1]*(C[16]+16*DP[5])+C[9]*DP[2]+C[15]*DP[3]+C[10]*DP[4]-C[16]*DP[5])+
 DP[5]*(C[15]*(-S[1]-DP[1]-DP[4])+C[10]*(-DP[2]-DP[5])+C[14]+C[16]*DP[0]+16*
 DP[1]*S[1])+DP[1]*(C[6]*S[1]-C[11]-C[7]*DP[1]-C[16]*DP[4])+S[1]*(C[8]+
 C[16]*DP[4])+C[12]*(-DP[0]-DP[2])-C[5])+DP[0]*(S[1]*(C[3]*(-S[1]-DP[5])+
 C[11]-C[6]*DP[1]-C[7]*DP[3]-C[13]*DP[9])+DP[5]*(C[11]+C[6]*DP[1]+C[15]*
 DP[8]+C[16]*DP[9])+DP[3]*(-C[16]*DP[8]-C[15]*DP[9])+C[8]*DP[2]+C[12]*DP[4]+
 C[11]*DP[8])+DP[2]*(DP[3]*(C[2]*S[1]-C[1]+C[6]*DP[1]+C[16]*DP[6])+C[8]*(-
 DP[1]-DP[2]-DP[4]-DP[5])+S[1]*(C[7]*DP[1]-C[12])+DP[6]*(-C[11]-C[15]*
 DP[5])+C[0]+C[14]*DP[9])+DP[4]*(S[1]*(C[12]+C[3]*DP[1]+C[13]*DP[6])+DP[1]*
 (-C[11]-C[6]*DP[1])+DP[6]*(C[15]*DP[3]-C[16]*DP[5])+C[5]-C[14]*DP[8]))+
 DP[5]*(C[15]*(DP[3]*(DP[2]*(-DP[6]-DP[7])+DP[8]*DP[0]-DP[7]*DP[1])+DP[7]*(
 DP[5]*DP[0]-DP[4]*DP[1]))+DP[2]*(C[4]+C[12]*DP[0]+C[17]*DP[9])+C[17]*(
 DP[7]*DP[5]-DP[8]*DP[4]))+DP[1]*(C[12]*(DP[2]*(DP[4]+DP[6])+DP[7]*DP[1]-
 DP[8]*DP[0])+C[8]*DP[7]*DP[2])-C[12]*DP[3]*S[2];
result=RNUM*(TOTNUM/TOTDEN)*Q1[4]*Q1[5]*Q1[2]*Q1[3]*Q0[1];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
