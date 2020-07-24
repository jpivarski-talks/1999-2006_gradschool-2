/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                   S           W+    !  W+    S                      
                 ==<==@-------1>-----!-->1-@==<==                    
                   P1 |        P3    !  P3 |  P1                     
                      |              !    u|-P8                      
                      |        B     !  B  |                         
                     u|P6   /==<=====!==<==@                         
                      |     |  P5    !  P5 |                         
                      |     |        !   W+|-P9                      
                   u  |  Z  |  b     !  b  3  u                      
                 ==>==@-2---@==>=====!==>==@==>==                    
                   P2    P7    P4    !  P4    P2                     
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F975;
double F975(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[58];double S[11];double tmp[1];                             
     
if(calcCoef[9])
{
S[0]=va[2]*va[2];
S[1]=va[10]*va[10];
S[2]=va[6]*va[6];
S[3]=va[13]*va[13]*va[13]*va[13];
C[0]=+S[3]*(S[1]*(S[0]*(S[2]*(16*S[0]-36)+12*S[1])+18*S[2]-9*S[1]));
S[4]=va[13]*va[13];
C[1]=+S[4]*(S[0]*(S[2]*(S[0]*(32*S[1]-16*S[4])+36*S[4]-24*S[1])+24*S[4]*
 S[1])+S[4]*(18*(-S[1]-S[2])));
C[2]=+S[4]*(S[0]*(S[2]*(24-32*S[0])+12*S[4])-9*S[4]);
C[3]=+S[3]*(S[0]*(S[2]*(64*S[0]-144)+48*S[1])+72*S[2]-36*S[1]);
C[4]=+S[3]*(S[2]*(S[0]*(64*S[0]-144)+72));
C[5]=+S[3]*(S[2]*(S[1]*(S[0]*(32*S[0]-72)+36)));
C[6]=+S[3]*(S[1]*(S[0]*(S[2]*(72-32*S[0])+24*S[1])-18*S[1]-36*S[2]));
C[7]=+S[4]*(S[0]*(S[2]*(S[0]*(64*(S[4]-S[1]))+48*S[1]-144*S[4])+48*S[4]*
 S[1])+S[4]*(72*S[2]-36*S[1]));
C[8]=+S[4]*(S[0]*(S[2]*(128*S[0]-96)+24*S[4])-18*S[4]);
C[9]=+S[3]*(S[1]*(96*S[0]-72));
C[10]=+S[3]*(96*S[0]-72);
S[5]=va[10]*va[10]*va[10]*va[10];
C[11]=+S[5]*(S[4]*(S[0]*(S[2]*(32*S[0]-24)+12*S[4])-9*S[4]));
C[12]=+S[1]*(S[4]*(S[0]*(S[2]*(32*S[0]-24)+12*S[4]-24*S[1])+18*S[1]-9*
 S[4]));
C[13]=+S[1]*(S[4]*(S[0]*(S[2]*(160*S[0]-120)+60*S[4])-45*S[4]));
C[14]=+S[4]*(S[0]*(S[2]*(96*S[0]-72)+36*S[4]-120*S[1])+90*S[1]-27*S[4]);
C[15]=+S[1]*(S[4]*(S[0]*(S[2]*(64*S[0]-48)+24*S[4])-18*S[4]));
C[16]=+S[4]*(S[0]*(S[2]*(256*S[0]-192)+96*S[4]-48*S[1])+36*S[1]-72*S[4]);
C[17]=+S[4]*(S[0]*(S[2]*(128*S[0]-96)+48*S[4])-36*S[4]);
C[18]=+S[3]*(S[1]*(12*S[0]-9));
C[19]=+S[4]*(S[0]*(12*S[4]-24*S[1])+18*S[1]-9*S[4]);
C[20]=+S[3]*(S[1]*(24*S[0]-18));
C[21]=+S[3]*(48*S[0]-36);
C[22]=+S[1]*(S[4]*(S[0]*(S[2]*(32*S[0]-24)+12*S[1])-9*S[1]));
C[23]=+S[4]*(S[0]*(S[2]*(24-32*S[0])+24*S[1])-18*S[1]);
C[24]=+S[0]*(S[2]*(S[4]*(128*S[0]-96)));
C[25]=+S[5]*(S[4]*(S[0]*(S[2]*(16*S[0]-36)+12*S[4])+18*S[2]-9*S[4]));
C[26]=+S[1]*(S[4]*(S[0]*(S[2]*(16*S[0]-36)+12*S[4]-24*S[1])+18*(S[1]+S[2])-
 9*S[4]));
C[27]=+S[1]*(S[4]*(S[0]*(S[2]*(80*S[0]-180)+60*S[4])+90*S[2]-45*S[4]));
C[28]=+S[4]*(S[0]*(S[2]*(48*S[0]-108)+36*S[4]-120*S[1])+90*S[1]-27*S[4]+54*
 S[2]);
C[29]=+S[4]*(72*S[0]-54);
C[30]=+S[1]*(S[4]*(S[0]*(S[2]*(32*S[0]-72)+24*S[4])+36*S[2]-18*S[4]));
C[31]=+S[4]*(S[0]*(S[2]*(128*S[0]-288)+96*S[4]-48*S[1])+36*S[1]-72*S[4]+144*
 S[2]);
C[32]=+S[4]*(192*S[0]-144);
C[33]=+S[4]*(S[0]*(S[2]*(64*S[0]-144)+48*S[4])+72*S[2]-36*S[4]);
C[34]=+S[1]*(S[0]*(S[2]*(144-64*S[0])+24*S[4])-18*S[4]-72*S[2]);
C[35]=+S[0]*(S[2]*(64*S[0]-144)+12*S[4])+72*S[2]-9*S[4];
C[36]=+S[0]*(S[2]*(576-256*S[0])+48*S[4])-36*S[4]-288*S[2];
C[37]=+S[2]*(S[1]*(S[0]*(128*S[0]-288)+144));
C[38]=+S[1]*(S[0]*(S[2]*(128*S[0]-288)+48*S[4])+144*S[2]-36*S[4]);
C[39]=+S[0]*(S[2]*(576-256*S[0])+24*S[4])-18*S[4]-288*S[2];
C[40]=+S[1]*(S[4]*(S[0]*(S[2]*(36-16*S[0])+12*S[4])-9*S[4]-18*S[2]));
C[41]=+S[4]*(S[0]*(S[2]*(36-16*S[0])+12*S[4]-24*S[1])+18*(S[1]-S[2])-9*
 S[4]);
C[42]=+S[1]*(S[4]*(S[0]*(S[2]*(72-32*S[0])+24*S[4])-18*S[4]-36*S[2]));
C[43]=+S[4]*(S[0]*(S[2]*(144-64*S[0])+48*S[4])-36*S[4]-72*S[2]);
C[44]=+S[0]*(S[2]*(S[1]*(S[4]*(64*S[0]-48))));
C[45]=+S[1]*(S[4]*(S[0]*(S[2]*(48-64*S[0])+24*S[1])-18*S[1]));
C[46]=+S[4]*(S[0]*(S[2]*(128*S[0]-96)+48*S[1])-36*S[1]);
C[47]=+S[5]*(S[4]*(12*S[0]-9));
C[48]=+S[1]*(S[4]*(24*S[0]-18));
C[49]=+S[4]*(12*S[0]-9);
C[50]=+S[4]*(48*S[0]-36);
C[51]=+S[5]*(S[4]*(24*S[0]-18));
C[52]=+S[1]*(S[4]*(48*S[0]-36));
C[53]=+S[4]*(24*S[0]-18);
C[54]=+S[1]*(S[4]*(96*S[0]-72));
C[55]=+S[4]*(96*S[0]-72);
S[6]=va[15]*va[15];
S[7]=va[2]*va[2]*va[2]*va[2]*va[2]*va[2];
C[56]=+432*S[6]*S[2]*S[7];
S[8]=va[21]*va[21];
S[9]=va[20]*va[20];
S[10]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[57]=+S[8]*S[9]*S[10];
}
TOTNUM=-C[57];
S[0]=va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[56]*S[0];
S[1]=va[28]*va[28];
tmp[0]=+S[1]*(DP[1]*(DP[1]*(C[55]*(DP[2]*(-DP[3]-DP[6]-DP[9])+DP[0]*(DP[5]+
 DP[8])+DP[1]*(-DP[4]-DP[7])+DP[7]*DP[5]-DP[8]*DP[4])+DP[4]*(C[32]*S[1]-
 C[16]+C[50]*DP[6])+DP[7]*(C[32]*S[1]-C[31]-C[36]*DP[3])+DP[0]*(C[17]+C[50]*
 DP[9])-C[10]*DP[2])+S[1]*(DP[4]*(C[14]-C[29]*S[1]-C[50]*DP[6]+C[53]*DP[8])+
 DP[7]*(C[28]-C[29]*S[1]+C[36]*DP[3]-C[39]*DP[5])+DP[0]*(-C[17]-C[50]*
 DP[9])+DP[2]*(C[8]+C[53]*DP[9]))+C[52]*(DP[0]*(-DP[5]-DP[8]-DP[9])+DP[2]*(
 DP[3]+DP[6]+DP[9])+DP[7]*DP[3])+DP[4]*(C[46]*(DP[8]-DP[6])+C[13])+DP[7]*(
 C[27]-C[38]*DP[5])+C[7]*DP[2]-C[3]*DP[0])+S[1]*(S[1]*(DP[0]*(C[53]*(-DP[5]-
 DP[8])+C[2]+C[49]*DP[9])+DP[2]*(C[53]*(DP[3]+DP[6]))+DP[4]*(C[48]+C[49]*
 DP[6])+DP[7]*(C[48]-C[35]*DP[3]))+DP[0]*(C[1]+C[19]*DP[5]+C[41]*DP[8]+
 C[48]*DP[9])+DP[2]*(-C[44]-C[19]*DP[3]-C[41]*DP[6])+DP[7]*(-C[26]-C[34]*
 DP[3]-C[37]*DP[5])+DP[4]*(C[23]*DP[6]-C[12]))+DP[0]*(C[0]+C[18]*DP[5]+
 C[40]*DP[8]+C[47]*DP[9])+DP[2]*(-C[5]-C[18]*DP[3]-C[40]*DP[6])+DP[4]*(
 C[22]*DP[6]-C[11]-C[44]*DP[8])+DP[7]*(-C[25]-C[47]*DP[3]));
RNUM=+DP[1]*(DP[1]*(DP[1]*(C[55]*(DP[8]*DP[4]-DP[7]*DP[5]+DP[9]*DP[2])+
 C[10]*DP[2]+C[17]*DP[4]+C[33]*DP[7])+DP[2]*(C[21]*DP[3]-C[9]+C[43]*DP[6]-
 C[54]*DP[9])+DP[0]*(C[4]-C[21]*DP[5]-C[43]*DP[8])+DP[4]*(C[24]*DP[6]-C[15]-
 C[54]*DP[8])+DP[7]*(C[54]*DP[5]-C[30]))+DP[2]*(C[6]-C[20]*DP[3]-C[42]*
 DP[6]+C[51]*DP[9])+DP[0]*(C[20]*DP[5]+C[42]*DP[8])+C[45]*DP[8]*DP[4]-C[51]*
 DP[7]*DP[5])+tmp[0];
result=RNUM*(TOTNUM/TOTDEN)*Q2[4]*Q1[1]*Q1[6]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
 }
 return result;
}