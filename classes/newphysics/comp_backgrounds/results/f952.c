/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                            !  W+                c                   
                           /!-->2-\           /==>==                 
                           |!  P3 |           |  P1                  
                           |!     |           |                      
                c     b    |!  b  |  t     W+ |  B                   
              ==>==@==>====+!==>==@==>==@-->3-@==<==                 
                P1 |  P4   |!  P4   -P9 | -P8    P2                  
                 W+|P6     |!           |                            
                   1  B    |!  B        |                            
                   @==<====+!==<========/                            
                   |  P5   |!  P5                                    
                  c|P7     |!                                        
                B  |  W+   |!                                        
              ==<==@-2>----/!                                        
                P2    P3    !                                        
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F952;
double F952(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[62];double S[9];double tmp[2];                              
     
if(calcCoef[8])
{
S[0]=va[13]*va[13]*va[13]*va[13]*va[13]*va[13]*va[13]*va[13];
S[1]=va[9]*va[9];
C[0]=+2*S[0]*S[1];
C[1]=+6*S[0];
S[2]=va[13]*va[13]*va[13]*va[13]*va[13]*va[13];
C[2]=+10*S[2];
S[3]=va[13]*va[13];
C[3]=+S[2]*(S[3]+S[1]);
S[4]=va[13]*va[13]*va[13]*va[13];
C[4]=+6*S[4]*S[1];
C[5]=+S[3]*(12*S[3]-6*S[1]);
C[6]=+8*S[2]*S[1];
C[7]=+10*S[4]*S[1];
C[8]=+S[4]*(2*S[3]+6*S[1]);
C[9]=+2*S[0];
C[10]=+12*S[2];
C[11]=+4*S[2]*S[1];
C[12]=+S[3]*(4*S[3]-8*S[1]);
C[13]=+16*S[3]*S[1];
C[14]=+16*S[4]*S[1];
C[15]=+S[3]*(4*S[3]+8*S[1]);
C[16]=+S[2]*(S[3]-3*S[1]);
C[17]=+S[2];
C[18]=+7*S[4];
C[19]=+S[3]*(12*S[3]-S[1]);
C[20]=+12*S[3]-S[1];
C[21]=+S[4]*(S[3]-S[1]);
C[22]=+14*S[3];
C[23]=+12*S[3]-2*S[1];
C[24]=+28*S[3];
C[25]=+S[2]*(2*(S[3]+S[1]));
C[26]=+8*S[2];
C[27]=+S[4]*(2*(S[3]+S[1]));
C[28]=+12*S[4]*S[1];
C[29]=+6*S[3]*S[1];
C[30]=+2*S[1];
C[31]=+4*S[2];
C[32]=+4*S[4];
C[33]=+8*S[4]*S[1];
C[34]=+8*S[4];
C[35]=+8*S[3]-4*S[1];
C[36]=+12*S[3]*S[1];
C[37]=+8*S[3]+4*S[1];
C[38]=+2*S[2]*S[1];
C[39]=+S[4]*S[1];
C[40]=+S[4]*(S[3]+S[1]);
C[41]=+S[3]*S[1];
C[42]=+S[1];
C[43]=+S[4]*(3*S[3]+S[1]);
C[44]=+2*S[4];
C[45]=+2*S[3];
C[46]=+10*S[3]*S[1];
C[47]=+4*S[3]+2*S[1];
C[48]=+2*S[2];
C[49]=+8*S[3]*S[1];
C[50]=+8*S[1];
C[51]=+16*S[1];
C[52]=+4*S[4]*S[1];
C[53]=+2*S[3]*S[1];
C[54]=+4*S[3]-2*S[1];
C[55]=+4*S[3];
C[56]=+2*S[4]*S[1];
C[57]=+4*S[3]*S[1];
C[58]=+4*S[1];
C[59]=+8*S[3];
S[5]=va[2]*va[2]*va[2]*va[2]*va[2]*va[2];
C[60]=+24*S[5];
S[6]=va[27]*va[27];
S[7]=va[24]*va[24]*va[24]*va[24];
S[8]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[61]=+S[6]*S[7]*S[8];
}
TOTNUM=-C[61];
S[0]=va[28]*va[28]*va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[60]*S[0];
S[1]=va[28]*va[28];
tmp[0]=+S[1]*(DP[4]*(S[1]*(DP[6]*(16*(DP[5]-DP[2])+C[20]-8*S[1]-32*DP[4])+
 C[50]*(DP[7]-DP[9])+C[57]+C[58]*DP[8])+DP[2]*(DP[6]*(32*DP[5]-C[23])+C[49]-
 C[50]*DP[8]+C[51]*DP[9])+DP[5]*(C[23]*DP[6]-C[49]+C[51]*DP[7]+C[50]*DP[8])+
 DP[1]*(C[5]-C[30]*DP[8])+C[34]*(DP[3]-DP[0])+C[49]*(DP[7]-DP[9])+C[13]*
 DP[4]-C[56]+C[19]*DP[6]+C[57]*DP[8])+DP[2]*(DP[6]*(S[1]*(C[22]+32*DP[5])+
 C[34]-C[24]*DP[2])+DP[9]*(C[51]*DP[2]-C[46]-C[50]*S[1]-C[47]*DP[0])+DP[3]*(
 C[29]+C[54]*DP[7]+C[30]*DP[8])+DP[0]*(C[55]*DP[8]-C[32])+DP[1]*(C[34]-
 C[55]*DP[7])-C[7]-C[13]*DP[5]-C[53]*DP[7]-C[29]*DP[8])+DP[5]*(DP[7]*(C[47]*
 DP[3]-C[46]-C[50]*S[1]-C[51]*DP[5])+DP[0]*(C[29]+C[30]*DP[8]-C[54]*DP[9])+
 DP[6]*(-C[34]-C[22]*S[1]-C[24]*DP[5])+DP[1]*(-C[34]-C[55]*DP[9])+DP[3]*(
 C[55]*DP[8]-C[32])+C[7]+C[29]*DP[8]-C[53]*DP[9])+S[1]*(C[45]*(DP[1]*(DP[7]-
 DP[9])+DP[8]*(DP[3]-DP[0]))+DP[0]*(C[42]*DP[9]-C[44])+DP[3]*(C[44]+C[42]*
 DP[7])+C[41]*(DP[7]-DP[9])+C[18]*DP[6])+C[44]*(DP[1]*(DP[7]-DP[8]-DP[9])+
 DP[8]*(DP[3]-DP[0]))+DP[0]*(C[41]*DP[9]-C[21])+DP[3]*(C[21]+C[41]*DP[7])+
 C[39]*(DP[7]-DP[9])-C[38]-C[2]*DP[1]-C[17]*DP[6]);
tmp[1]=+S[1]*(DP[2]*(DP[5]*(DP[8]*(C[35]*(DP[0]-DP[3])-C[49]-C[51]*DP[4])+
 C[58]*(DP[6]*DP[4]-DP[7]*DP[3]-DP[9]*DP[0])+DP[1]*(C[59]*(DP[9]-DP[7]))+
 C[12]*(DP[0]-DP[3])+C[32]*DP[6]-C[14]-C[13]*DP[4])+DP[8]*(DP[1]*(C[32]+
 C[58]*DP[4])+DP[2]*(C[36]-C[37]*DP[3])+C[49]*DP[3]-C[28]-C[57]*DP[4])+
 DP[2]*(DP[9]*(C[57]+C[59]*DP[1])+C[14]-C[15]*DP[3])+DP[3]*(C[57]*(DP[9]-
 DP[7])+C[8])+DP[1]*(C[10]+C[15]*DP[4])+C[56]*(DP[4]-DP[0])+C[52]*(DP[7]-
 DP[9])+C[21]*DP[6]-C[6])+DP[5]*(DP[8]*(DP[0]*(C[49]+C[37]*DP[5])+DP[1]*(-
 C[32]-C[58]*DP[4])+C[28]+C[57]*DP[4]+C[36]*DP[5])+DP[0]*(C[57]*(DP[9]-
 DP[7])+C[8]+C[15]*DP[5])+DP[1]*(-C[10]-C[15]*DP[4]-C[59]*DP[7]*DP[5])+
 DP[5]*(C[14]-C[57]*DP[7])+C[56]*(-DP[3]-DP[4])+C[52]*(DP[9]-DP[7])+C[6]-
 C[21]*DP[6])+DP[4]*(C[57]*(DP[1]*(DP[7]-DP[9])+DP[7]*DP[3]-DP[6]*DP[4]+
 DP[9]*DP[0])+DP[1]*(-C[4]-C[49]*DP[8])-C[38]-C[40]*DP[6]-C[56]*DP[8])+
 DP[0]*(C[40]*(DP[8]+DP[9])+C[3]-C[52]*DP[7])+DP[1]*(C[43]*(DP[7]-DP[9])-
 C[1]-C[26]*DP[8])+DP[3]*(C[40]*(DP[7]-DP[8])-C[3]-C[52]*DP[9])+C[38]*(
 DP[8]-DP[7]+DP[9])+C[0]-C[16]*DP[6]+tmp[0]);
RNUM=+DP[2]*(DP[5]*(DP[8]*(C[50]*(DP[4]*DP[1]-DP[3]*DP[2]-DP[5]*DP[0])+
 C[57]*(DP[3]-DP[0])+C[49]*(DP[2]-DP[5])+C[34]*DP[1]-C[33])+C[56]*(DP[3]-
 DP[0]+DP[7]-DP[9])+C[49]*(DP[4]*DP[1]-DP[3]*DP[2]-DP[5]*DP[0])+C[57]*(
 DP[6]*DP[4]-DP[7]*DP[3]-DP[9]*DP[0])+C[33]*(DP[2]-DP[5])+C[26]*DP[1]-
 C[11])+DP[8]*(C[56]*(DP[0]+DP[3]-DP[4])+DP[1]*(C[31]+C[57]*DP[4])+DP[2]*(
 C[52]-C[57]*DP[3])-C[38])+C[56]*(DP[2]*(DP[9]-DP[3]-DP[6])+DP[1]*(DP[4]+
 DP[7]))+DP[1]*(C[9]+C[48]*DP[9])+C[38]*DP[2])+DP[5]*(DP[8]*(C[56]*(DP[0]+
 DP[3]+DP[4])+DP[1]*(-C[31]-C[57]*DP[4])+DP[5]*(C[52]+C[57]*DP[0])+C[38])+
 C[56]*(DP[5]*(DP[0]-DP[6]-DP[7])+DP[1]*(DP[9]-DP[4]))+DP[1]*(C[48]*DP[7]-
 C[9])+C[38]*DP[5])+DP[1]*(DP[8]*(-C[25]-C[27]*DP[4]))+tmp[1];
result=RNUM*(TOTNUM/TOTDEN)*Q1[10]*Q1[4]*Q1[2]*Q1[3]*Q0[1];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
 }
 return result;
}
