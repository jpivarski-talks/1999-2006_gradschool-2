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
             u  |  Z  |  b  |  !  b  |  A     W+ |  u                
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
FNN F976;
double F976(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[70];double S[8];double tmp[2];                              
     
if(calcCoef[9])
{
S[0]=va[2]*va[2];
S[1]=va[13]*va[13];
C[0]=+S[1]*(S[0]*(96*S[0]-144)+54);
C[1]=+S[1]*(S[0]*(32*S[0]-48)+18);
S[2]=va[10]*va[10];
C[2]=+S[2]*(S[1]*(S[0]*(64*S[0]-96)+36));
C[3]=+S[1]*(S[0]*(96*S[0]-168)+72);
C[4]=+S[1]*(S[0]*(16*S[0]-36)+18);
S[3]=va[10]*va[10]*va[10]*va[10];
C[5]=+S[3]*(S[0]*(S[1]*(16*S[0]-12)));
C[6]=+S[2]*(S[1]*(S[0]*(80*S[0]-108)+36));
C[7]=+S[0]*(S[2]*(S[1]*(16*S[0]-12)));
C[8]=+S[1]*(S[0]*(112*S[0]-132)+36);
C[9]=+S[2]*(S[1]*(S[0]*(64*S[0]-84)+27));
C[10]=+S[1]*(S[0]*(64*S[0]-120)+54);
C[11]=+S[2]*(S[1]*(S[0]*(48*S[0]-84)+36));
C[12]=+S[2]*(S[1]*(S[0]*(32*S[0]-36)+9));
C[13]=+S[1]*(S[0]*(96*S[0]-120)+36);
C[14]=+S[2]*(S[1]*(S[0]*(48*S[0]-72)+27));
C[15]=+S[0]*(S[1]*(16*S[0]-12));
C[16]=+S[0]*(S[1]*(32*S[0]-24));
C[17]=+S[0]*(96*S[0]-144)+54;
C[18]=+S[0]*(S[2]*(48*S[0]-36));
C[19]=+S[0]*(16*S[0]+36)-36;
C[20]=+S[0]*(S[2]*(32*S[0]-24));
C[21]=+S[0]*(16*S[0]-60)+36;
C[22]=+S[3]*(S[1]*(S[0]*(16*S[0]-36)+18));
C[23]=+S[2]*(S[1]*(S[0]*(80*S[0]-132)+54));
C[24]=+S[2]*(S[1]*(S[0]*(32*S[0]-60)+27));
C[25]=+S[2]*(S[1]*(S[0]*(16*S[0]-36)+18));
C[26]=+S[1]*(S[0]*(112*S[0]-204)+90);
C[27]=+S[1]*(S[0]*(32*S[0]-72)+36);
C[28]=+S[2]*(S[1]*(S[0]*(64*S[0]-108)+45));
C[29]=+S[2]*(S[1]*(S[0]*(32*S[0]-48)+18));
C[30]=+S[2]*(S[0]*(48*S[0]-108)+54);
C[31]=+S[0]*(16*S[0]-84)+54;
C[32]=+S[2]*(S[0]*(32*S[0]-72)+36);
C[33]=+S[2]*(S[0]*(48*S[0]-84)+36);
C[34]=+S[0]*(64*S[0]-144)+72;
C[35]=+S[2]*(S[0]*(64*S[0]-144)+72);
C[36]=+S[2]*(S[1]*(12*S[0]-9));
C[37]=+S[1]*(S[0]*(64*S[0]-72)+18);
C[38]=+S[1]*(S[0]*(64*S[0]-96)+36);
C[39]=+S[3]*(S[1]*(S[0]*(16*S[0]-24)+9));
C[40]=+S[2]*(S[1]*(S[0]*(48*S[0]-60)+18));
C[41]=+S[2]*(36*S[0]-27);
C[42]=+S[2]*(S[0]*(48*S[0]-60)+18);
C[43]=+S[0]*(64*S[0]-48);
C[44]=+S[0]*(S[2]*(64*S[0]-48));
C[45]=+24*S[0]-18;
C[46]=+S[0]*(16*S[0]+12)-18;
C[47]=+S[2]*(24*S[0]-18);
C[48]=+S[3]*(12*S[0]-9);
C[49]=+S[0]*(32*S[0]-48)+18;
C[50]=+S[0]*(64*S[0]-96)+36;
C[51]=+S[2]*(S[0]*(48*S[0]-72)+27);
C[52]=+S[0]*(16*S[0]-36)+18;
C[53]=+S[3]*(S[0]*(16*S[0]-12));
C[54]=+S[0]*(48*S[0]-36);
C[55]=+S[2]*(S[0]*(32*S[0]-36)+9);
C[56]=+S[2]*(S[0]*(16*S[0]-24)+9);
C[57]=+S[0]*(16*S[0]-12);
C[58]=+S[3]*(S[0]*(16*S[0]-36)+18);
C[59]=+S[2]*(S[0]*(16*S[0]-36)+18);
C[60]=+S[0]*(48*S[0]-108)+54;
C[61]=+S[0]*(32*S[0]-72)+36;
C[62]=+S[2]*(S[0]*(32*S[0]-60)+27);
C[63]=+S[2]*(S[0]*(32*S[0]-48)+18);
C[64]=+S[2]*(12*S[0]-9);
C[65]=+S[0]*(32*S[0]-24);
C[66]=+S[3]*(S[0]*(16*S[0]-24)+9);
C[67]=+S[0]*(S[2]*(16*S[0]-12));
S[4]=va[15]*va[15];
S[5]=va[2]*va[2]*va[2]*va[2];
C[68]=+108*S[4]*S[5];
S[6]=va[20]*va[20];
S[7]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[69]=+S[6]*S[7];
}
TOTNUM=-C[69];
S[0]=va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[68]*S[0];
S[1]=va[28]*va[28];
tmp[0]=+DP[1]*(DP[4]*(C[65]*(DP[6]*(-DP[1]-DP[2]-DP[5]-DP[8])-DP[8]*DP[0]-
 DP[9]*DP[1])+DP[1]*(C[50]*DP[7]-C[16])+DP[8]*(C[42]+C[50]*DP[3])-C[7]-
 C[20]*DP[6]-C[67]*DP[9])+DP[7]*(C[61]*(DP[3]*(-DP[1]-DP[2]-DP[5]-DP[8])-
 DP[5]*DP[0]-DP[9]*DP[1])+DP[5]*(C[33]+C[50]*DP[6])-C[25]-C[27]*DP[1]-C[32]*
 DP[3]-C[59]*DP[9])+DP[2]*(DP[3]*(C[50]*DP[6]-C[27]-C[61]*DP[9])+DP[6]*(-
 C[16]-C[65]*DP[9])+C[29]-C[38]*DP[0]-C[63]*DP[9])+DP[0]*(C[38]*(-DP[1]-
 DP[5]-DP[8])-C[29]-C[65]*DP[6]*DP[5]-C[61]*DP[8]*DP[3]))+DP[2]*(DP[9]*(
 C[56]*(-DP[3]-DP[6])+C[59]*DP[5]-C[66]-C[55]*DP[4]-C[62]*DP[7]+C[67]*
 DP[8])+DP[3]*(C[67]*DP[8]-C[14]-C[32]*DP[7])+DP[4]*(C[44]*DP[8]-C[9]-C[20]*
 DP[6])+DP[5]*(C[11]+C[59]*DP[6]+C[35]*DP[7])+C[2]*DP[2]-C[39]-C[29]*DP[0]-
 C[14]*DP[6]-C[28]*DP[7]+C[40]*DP[8])+DP[4]*(DP[8]*(C[64]*(-DP[3]-DP[4]-
 DP[7])+C[67]*(DP[8]-DP[6])+C[66]-C[59]*DP[5])+C[56]*(DP[6]*(DP[4]-DP[3]+
 DP[5]+DP[6]-DP[7])-DP[7]*DP[3])+DP[0]*(C[12]+C[64]*DP[9])+C[5]+C[64]*DP[7]*
 DP[5]+C[53]*DP[9])+DP[7]*(DP[5]*(C[59]*(DP[5]-DP[3])+C[64]*(DP[6]+DP[7])+
 C[66]-C[67]*DP[8])+DP[3]*(C[56]*(DP[3]-DP[6]+DP[7]+DP[8]))+DP[0]*(C[24]-
 C[64]*DP[9])+C[22]+C[58]*DP[9])+DP[0]*(DP[9]*(C[64]*(DP[5]-DP[3]+DP[6]-
 DP[8]))+DP[5]*(C[36]-C[63]*DP[8])+C[24]*DP[3]+C[12]*DP[6]-C[36]*DP[8]);
tmp[1]=+S[1]*(S[1]*(DP[0]*(DP[9]*(C[61]*(DP[3]-DP[5])+C[65]*(DP[6]-DP[8])+
 C[49]*S[1]+C[50]*DP[1])+DP[3]*(C[3]+C[34]*DP[7]-C[60]*DP[8])+DP[5]*(-C[10]-
 C[54]*DP[6]-C[60]*DP[7])+DP[4]*(C[43]*DP[6]-C[54]*DP[8])+C[38]*(S[1]+
 DP[0])+C[29]+C[0]*DP[1]-C[1]*DP[2]+C[13]*DP[6]-C[37]*DP[8])+DP[4]*(DP[6]*(
 C[57]*(DP[2]-DP[8])+C[18]+C[45]*S[1]+C[19]*DP[1]-C[61]*DP[3]+C[21]*DP[5]+
 C[65]*DP[6])+DP[1]*(C[8]-C[49]*DP[7]-C[43]*DP[8]+C[54]*DP[9])+DP[8]*(C[45]*
 DP[3]-C[41])-C[6]-C[63]*DP[7]-C[67]*DP[9])+DP[7]*(DP[3]*(C[52]*(DP[2]-
 DP[5])+C[30]-C[45]*S[1]+C[31]*DP[1]+C[61]*DP[3]-C[65]*DP[6]+C[46]*DP[8])+
 DP[1]*(C[26]-C[34]*DP[5]+C[60]*DP[9])+DP[5]*(C[41]-C[45]*DP[6])-C[23]-
 C[59]*DP[9])+DP[2]*(DP[3]*(C[4]+C[17]*DP[6]+C[52]*DP[9])+DP[6]*(C[15]+
 C[57]*DP[9])-C[14]-C[38]*DP[1]-C[51]*DP[9]))+tmp[0]);
RNUM=+DP[2]*(DP[1]*(DP[9]*(C[63]*(DP[3]+DP[4]+DP[6]+DP[7]))+C[29]*(DP[3]+
 DP[4]+DP[6]+DP[7]))+DP[5]*(DP[6]*(C[59]*(-DP[6]-DP[7])+C[67]*DP[3]+C[47]*
 DP[4])+C[59]*DP[7]*DP[3]-C[39]-C[66]*DP[9])+DP[8]*(DP[3]*(C[67]*(-DP[3]-
 DP[4])+C[59]*DP[6]-C[47]*DP[7])+C[67]*DP[6]*DP[4]-C[39]-C[66]*DP[9]))+
 DP[5]*(DP[7]*(DP[1]*(C[67]*(-DP[6]-DP[7])+C[59]*DP[4]-C[47]*DP[3])+DP[0]*(
 C[67]*DP[8]-C[59]*DP[5])+C[48]*(DP[5]+DP[8]))+DP[0]*(DP[8]*(C[59]*(DP[4]+
 DP[6])+C[67]*DP[3])-C[67]*DP[6]*DP[5])+DP[4]*(C[67]*DP[6]*DP[1]-C[48]*
 DP[8]))+DP[8]*(DP[4]*(DP[1]*(C[59]*(-DP[3]-DP[4])+C[47]*DP[6]+C[67]*DP[7])+
 DP[8]*(-C[48]-C[67]*DP[0]))+DP[3]*(C[59]*(DP[7]*DP[1]-DP[8]*DP[0])))+
 tmp[1];
result=RNUM*(TOTNUM/TOTDEN)*Q1[4]*Q1[1]*Q1[2]*Q1[5]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
