/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                                  !  b     c                         
                      c     b  /==!==>==@==>==                       
                    ==>==@==>==/  !  P4 |  P1                        
                      P1 |  P4    !   W+|-P8                         
                       W+|P6      !  B  4                            
                         1  W+   /!==<==@                            
                         @-3>---\|!  P5 |                            
                         |  P3  ||!    u|-P9                         
                        A|P7    ||!  W+ |  B                         
                      B  2  B   \+!-->3-@==<==                       
                    ==<==@==<====/!  P3    P2                        
                      P2    P5    !                                  
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F916;
double F916(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[68];double S[7];double tmp[5];                              
     
if(calcCoef[8])
{
S[0]=va[13]*va[13]*va[13]*va[13];
C[0]=+S[0];
S[1]=va[13]*va[13];
S[2]=va[9]*va[9];
C[1]=+5*S[1]*S[2];
C[2]=+8*S[0]*S[2];
C[3]=+S[0]*(2*(S[1]-S[2]));
C[4]=+3*S[0];
C[5]=+12*S[0];
C[6]=+6*S[0];
C[7]=+5*S[1];
C[8]=+S[1]*(4*S[1]+8*S[2]);
C[9]=+10*S[1];
C[10]=+2*S[0];
C[11]=+S[0]*(S[2]*(4*(S[1]+S[2])));
C[12]=+S[2]*(S[1]*(6*S[1]-2*S[2]));
C[13]=+S[1]*(S[2]*(12*S[1]+2*S[2])+2*S[0]);
C[14]=+S[2]*(-2*S[1]-S[2])+3*S[0];
C[15]=+S[1]*(4*(S[1]+S[2]));
C[16]=+S[2]*(S[1]-S[2]);
C[17]=+3*S[2];
C[18]=+8*S[1];
C[19]=+S[1];
C[20]=+6*S[1];
C[21]=+S[0]*(S[1]-S[2]);
C[22]=+8*S[1]+4*S[2];
C[23]=+6*(S[1]+S[2]);
C[24]=+S[2]*(S[1]*(S[1]-S[2]));
C[25]=+4*S[0];
C[26]=+4*S[1];
C[27]=+S[2]*(S[1]*(2*(S[1]+S[2])));
C[28]=+S[2]*(S[1]*(4*(S[1]+S[2])));
C[29]=+S[2]*(6*S[1]+S[2])+S[0];
C[30]=+S[2]*(12*S[1]+2*S[2])+2*S[0];
C[31]=+S[0]*(S[2]*(2*(S[1]+S[2])));
C[32]=+S[1]*(S[2]*(6*S[1]+S[2])+S[0]);
C[33]=+S[2]*(S[1]*(2*(S[1]-S[2])));
C[34]=+S[1]*S[2];
C[35]=+S[2]*(2*(S[1]-S[2]));
C[36]=+S[2];
C[37]=+S[1]*(2*S[1]+10*S[2]);
C[38]=+6*S[1]+4*S[2];
C[39]=+S[1]*(2*(S[1]-S[2]));
C[40]=+12*S[0]*S[2];
C[41]=+4*(S[1]-S[2]);
C[42]=+S[1]*(6*(S[1]+S[2]));
C[43]=+6*S[0]*S[2];
C[44]=+S[1]-S[2];
C[45]=+S[1]*(S[1]-S[2]);
C[46]=+12*S[1]*S[2];
C[47]=+2*(S[1]-S[2]);
C[48]=+S[1]*(3*(S[1]+S[2]));
C[49]=+2*S[1];
C[50]=+8*S[1]*S[2];
C[51]=+8*S[2];
C[52]=+4*(S[1]+S[2]);
C[53]=+6*S[1]*S[2];
C[54]=+6*S[2];
C[55]=+3*(S[1]+S[2]);
C[56]=+4*S[0]*S[2];
C[57]=+S[1]*(2*(S[1]+S[2]));
C[58]=+2*S[0]*S[2];
C[59]=+2*S[1]*S[2];
C[60]=+2*S[2];
C[61]=+4*S[1]*S[2];
C[62]=+4*S[2];
C[63]=+S[1]*(S[1]+S[2]);
C[64]=+S[1]+S[2];
C[65]=+2*(S[1]+S[2]);
S[3]=va[2]*va[2]*va[2]*va[2];
C[66]=+6*S[3];
S[4]=va[24]*va[24];
S[5]=va[21]*va[21];
S[6]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[67]=+S[4]*S[5]*S[6];
}
TOTNUM=+C[67];
S[0]=va[28]*va[28]*va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[66]*S[0];
S[1]=va[28]*va[28];
tmp[0]=+DP[5]*(S[1]*(DP[6]*(C[18]+2*DP[0]-6*DP[7])+DP[3]*(4*DP[7]-C[20])+
 C[1]-C[26]*DP[1]-C[17]*DP[7]-4*DP[9]*DP[0])+DP[0]*(C[49]*(-DP[1]-DP[8])+
 C[63]-C[55]*DP[7]+C[44]*DP[9])+DP[6]*(C[55]*DP[7]-C[48]-C[49]*DP[5]+C[26]*
 DP[8])+DP[3]*(C[44]*DP[7]-C[45]-C[49]*DP[8])+DP[9]*(C[53]+C[49]*DP[1]-
 C[54]*DP[7])+C[24]+C[15]*DP[1]-C[61]*DP[5]-C[16]*DP[7]+C[59]*DP[8])+DP[0]*(
 DP[9]*(S[1]*(2*S[1]-C[49])+C[42]+C[47]*DP[0]-C[44]*DP[1]-C[52]*DP[7]-C[64]*
 DP[8])+DP[7]*(C[39]+C[20]*DP[1]-C[47]*DP[3]+C[18]*DP[6])+DP[8]*(C[19]*S[1]-
 C[20]*DP[0]+C[49]*DP[6])+C[6]*DP[0]-C[3]-C[0]*S[1]-C[10]*DP[1]+C[39]*DP[3]-
 C[5]*DP[6])+DP[3]*(DP[7]*(S[1]*(-C[60]-2*S[1])+C[65]*(-DP[3]-DP[8])+C[44]*
 DP[1]-C[14]+C[52]*DP[7])+S[1]*(C[49]*(-DP[1]-DP[6])+C[59]+C[26]*S[1])+
 C[39]*(DP[6]+DP[9])+C[57]*DP[3]-C[32]-C[45]*DP[1])+DP[1]*(DP[7]*(C[55]*
 DP[9]-C[45]-C[19]*S[1]-C[20]*DP[6])+S[1]*(C[4]-C[49]*DP[9])+C[21]-C[25]*
 DP[1]+C[6]*DP[6]-C[48]*DP[9])+S[1]*(DP[6]*(C[4]-C[49]*DP[9])+C[61]*DP[7]-
 C[56]-C[34]*DP[9])+DP[6]*(C[57]*DP[9]-C[3]-C[10]*DP[6])+DP[7]*(C[12]-C[50]*
 DP[7]+C[61]*DP[8])+DP[9]*(-C[33]-C[59]*DP[9])+C[31];
S[2]=DP[8]*DP[8];
S[3]=DP[9]*DP[9];
S[4]=DP[4]*DP[4];
tmp[1]=+DP[1]*(C[45]*(DP[5]*(-DP[0]-DP[4]-DP[6]-DP[9])+DP[1]*(DP[4]+DP[9]))+
 DP[7]*(C[53]*(DP[4]-DP[0]+DP[6]-DP[9]))+DP[8]*(C[21]+C[25]*DP[6]-C[57]*
 DP[9])+C[58]*(DP[0]-DP[4])+C[43]*(DP[9]-DP[6])+C[56]*DP[1]-C[2]*DP[5])+
 DP[5]*(DP[6]*(C[43]+C[45]*DP[5]-C[53]*DP[7]-C[57]*DP[8])+DP[0]*(C[45]*
 DP[5]-C[58]+C[53]*DP[7])+DP[9]*(C[53]*DP[7]-C[43]+C[61]*DP[8])+DP[4]*(
 C[58]-C[53]*DP[7])+C[56]*DP[5]+C[24]*DP[8])+DP[0]*(DP[8]*(C[59]*(DP[9]-
 DP[6])+C[53]*DP[0]-C[46]*DP[4])+C[40]*(DP[4]+DP[6]-DP[9])+DP[7]*(C[50]*(
 DP[9]-DP[6]))-C[43]*DP[0])+DP[4]*(DP[6]*(C[50]*DP[7]-C[40]+C[59]*DP[8])+
 DP[9]*(C[40]-C[50]*DP[7]-C[59]*DP[8])+DP[4]*(C[53]*DP[8]-C[43]))+DP[7]*(
 C[28]*DP[7]-C[11]-C[27]*DP[8])+DP[6]*(C[58]*DP[6]-C[56]*DP[9])+C[58]*S[3]-
 C[56]*S[2];
tmp[2]=+DP[3]*(DP[7]*(C[55]*(DP[1]*(DP[0]-DP[4]-DP[6]+DP[9])+DP[5]*(DP[4]-
 DP[0]+DP[6]-DP[9]))+C[52]*(DP[0]*(DP[6]-DP[9])+DP[2]*(DP[2]-DP[8])+DP[4]*(
 DP[9]-DP[6])+DP[7]*DP[3])+DP[2]*(C[47]*(DP[1]+DP[5])+C[29]-C[65]*DP[3])+
 DP[3]*(-C[15]-C[65]*DP[8])+C[13]-C[30]*DP[7]+C[29]*DP[8])+DP[2]*(DP[6]*(
 C[64]*(DP[4]-DP[0]-DP[6])+C[52]*(DP[1]-DP[5])+C[65]*DP[9])+DP[9]*(C[64]*(
 DP[0]-DP[4]-DP[9])+C[52]*(DP[5]-DP[1]))+DP[8]*(C[52]*DP[3]-C[30])+C[45]*(-
 DP[1]-DP[5])-C[57]*DP[2])+DP[0]*(DP[8]*(C[64]*(DP[6]-DP[9])+C[23]*DP[4]-
 C[55]*DP[0])+C[42]*(DP[9]-DP[4]-DP[6])+C[63]*(DP[5]-DP[1])+C[48]*DP[0])+
 DP[4]*(DP[8]*(C[64]*(DP[9]-DP[6])-C[55]*DP[4])+C[63]*(DP[1]-DP[5])+C[42]*(
 DP[6]-DP[9])+C[48]*DP[4])+DP[1]*(C[48]*(DP[6]-DP[9])+C[15]*DP[5]-C[57]*
 DP[1]-C[45]*DP[8])+DP[5]*(C[48]*(DP[9]-DP[6])-C[57]*DP[5]-C[45]*DP[8])+
 DP[6]*(C[57]*DP[9]-C[63]*DP[6])+C[57]*S[2]-C[63]*S[3]);
tmp[3]=+S[1]*(DP[4]*(S[1]*(DP[6]*(2*(DP[5]-S[1]-DP[1]+DP[8])+8*DP[7]-C[9]-6*
 DP[2]-4*DP[4])+DP[0]*(C[20]-6*DP[8]+4*DP[9])+DP[1]*(6*DP[7]-C[49]+2*DP[9])+
 DP[3]*(C[20]-4*DP[7]-2*DP[8])+C[62]*DP[7]-C[1]+C[36]*DP[8])+DP[2]*(4*(
 DP[6]*(DP[2]-DP[1]+DP[5]-DP[8])+DP[1]*(DP[7]-DP[9])+DP[8]*(DP[3]-DP[0]))+
 C[60]*(-DP[8]-DP[9])+C[64]*DP[6]-C[26]*DP[1])+DP[6]*(C[47]*(DP[4]-DP[0])+
 C[44]*(DP[1]-DP[5])+C[42]-C[52]*DP[7]-C[64]*DP[8])+DP[7]*(C[35]-C[55]*
 DP[1]-C[47]*DP[3]+C[54]*DP[5]+C[51]*DP[9])+DP[8]*(C[23]*DP[0]+C[49]*DP[1]-
 C[54]*DP[4]+C[60]*DP[9])+DP[0]*(-C[42]-C[47]*DP[9])+DP[1]*(C[63]+C[49]*
 DP[1])+C[39]*DP[3]-C[33]+C[53]*DP[4]-C[59]*DP[5]-C[46]*DP[9])+DP[2]*(DP[6]*
 (S[1]*(6*DP[3]-C[7]+8*DP[5]-2*DP[9])+4*(DP[2]*(DP[9]-DP[3])+DP[5]*(DP[0]-
 DP[7]))+C[49]*(DP[2]-DP[0]-DP[6])+C[39]+C[18]*DP[1]-C[47]*DP[3]-C[38]*
 DP[5]+C[65]*DP[9])+DP[9]*(S[1]*(4*DP[0]-C[36])+C[60]*(DP[2]-DP[9])+C[35]+
 C[64]*DP[0]-C[38]*DP[1]-C[47]*DP[3]+C[51]*DP[5])+DP[3]*(S[1]*(C[49]-4*
 DP[7])+C[49]*DP[1]-C[26]*DP[2]-C[65]*DP[7]+C[22]*DP[8])+DP[7]*(C[61]+C[49]*
 DP[1]-C[60]*DP[5])+DP[0]*(C[26]*DP[5]-C[49]*DP[8])-C[10]*DP[1]-C[50]*
 DP[8])+tmp[0]);
tmp[4]=+DP[2]*(DP[3]*(C[65]*(DP[7]*(DP[1]*(DP[0]-DP[4]-DP[6]+DP[9])+DP[5]*(
 DP[4]-DP[0]+DP[6]-DP[9]))+DP[2]*(DP[6]*(DP[0]-DP[4]+DP[6])+DP[9]*(DP[4]-
 DP[0]+DP[9]))+DP[8]*(DP[0]*(DP[9]-DP[0]-DP[6])+DP[4]*(DP[6]-DP[4]-DP[9])))+
 DP[2]*(DP[3]*(C[52]*DP[7]-C[57])+C[32]-C[30]*DP[7]-C[52]*DP[9]*DP[6])+
 C[57]*(DP[1]*(DP[9]-DP[6])+DP[5]*(DP[6]-DP[9]))+DP[8]*(DP[7]*(C[30]-C[52]*
 DP[3])+C[52]*DP[4]*DP[0]))+C[61]*(DP[7]*(DP[1]*(DP[4]-DP[0]+DP[6]-DP[9])+
 DP[5]*(DP[0]-DP[4]-DP[6]+DP[9]))+DP[2]*(DP[6]*(DP[4]-DP[0]-DP[6])+DP[9]*(
 DP[0]-DP[4]-DP[9]))+DP[8]*(DP[0]*(DP[0]+DP[6]-DP[9])+DP[4]*(DP[4]-DP[6]+
 DP[9])))+C[56]*(DP[1]*(DP[6]-DP[9])+DP[5]*(DP[9]-DP[6]))+DP[2]*(C[28]*
 DP[7]-C[31]+C[50]*DP[9]*DP[6])+DP[8]*(-C[50]*DP[4]*DP[0]-C[28]*DP[7]))+
 DP[8]*(DP[3]*(C[57]*(DP[1]*(DP[6]-DP[9])+DP[5]*(DP[9]-DP[6])+DP[8]*DP[3])-
 C[32]*DP[8])+C[56]*(DP[1]*(DP[9]-DP[6])+DP[5]*(DP[6]-DP[9]))+C[31]*DP[8]);
RNUM=+S[1]*(DP[2]*(DP[6]*(DP[4]*(C[47]*(-DP[1]-DP[5])+C[65]*(DP[8]-DP[2])-
 C[59])+DP[0]*(C[26]*(DP[2]-DP[8])+C[59]+C[41]*DP[5])+DP[1]*(-C[8]-C[26]*
 DP[7])+DP[2]*(C[26]*DP[6]-C[52]*DP[9])+DP[5]*(C[37]+C[65]*DP[7])+C[59]*
 DP[6]-C[61]*DP[9])+DP[9]*(DP[0]*(C[47]*(-DP[1]-DP[5])+C[65]*(DP[8]-DP[2])-
 C[59])+DP[4]*(C[62]*(DP[2]-DP[8])+C[59]+C[41]*DP[1])+DP[1]*(C[37]+C[65]*
 DP[7])+DP[5]*(-C[46]-C[62]*DP[7])+DP[9]*(C[59]+C[62]*DP[2]))+DP[7]*(DP[1]*(
 C[26]*DP[0]-C[39]-C[65]*DP[4])+DP[5]*(C[62]*DP[4]-C[35]-C[65]*DP[0])+C[50]*
 (DP[8]-DP[2])-C[27])+DP[8]*(DP[0]*(C[52]*DP[4]-C[26]*DP[0])+C[28]-C[62]*
 S[4])+C[21]*DP[1]+C[56]*DP[2]+C[24]*DP[5])+tmp[1]+tmp[2]+tmp[3])+tmp[4];
result=RNUM*(TOTNUM/TOTDEN)*Q2[10]*Q1[6]*Q1[11]*Q0[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[1] += result*(1)/(1);
 }
 return result;
}
