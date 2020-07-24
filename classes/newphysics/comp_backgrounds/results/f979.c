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
                |              !  b  |  c     W+ |  u                
                |        B    /!==>==@==>==@-->3-@==>==              
               u|P6   /==<===\|!  P4   -P9 | -P8    P2               
                |     |  P5  ||!           |                         
                |     |      ||!  B        |                         
             u  |  Z  |  b   \+!==<========/                         
           ==>==@-2---@==>====/!  P5                                 
             P2    P7    P4    !                                     
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F979;
double F979(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[63];double S[11];double tmp[3];                             
     
if(calcCoef[9])
{
S[0]=va[2]*va[2];
S[1]=va[13]*va[13];
S[2]=va[6]*va[6];
S[3]=va[10]*va[10];
C[0]=+S[3]*(S[1]*(S[0]*(S[2]*(6-8*S[0])+24*S[1])-18*S[1]));
S[4]=va[10]*va[10]*va[10]*va[10];
C[1]=+S[4]*(S[1]*(S[0]*(S[2]*(18-24*S[0])+24*S[1])-18*S[1]));
S[5]=va[13]*va[13]*va[13]*va[13];
C[2]=+S[5]*(S[3]*(36*S[0]-27));
C[3]=+S[1]*(S[0]*(S[2]*(48-64*S[0])+96*S[1])-72*S[1]);
C[4]=+S[3]*(S[1]*(S[0]*(S[2]*(18-24*S[0])+24*S[1])-18*S[1]));
C[5]=+S[1]*(S[0]*(S[2]*(36-48*S[0])+72*S[1])-54*S[1]);
C[6]=+S[5]*(S[3]*(24*S[0]-18));
C[7]=+S[4]*(S[1]*(S[0]*(S[2]*(6-8*S[0])+12*S[1])-9*S[1]));
C[8]=+S[3]*(S[1]*(S[0]*(S[2]*(12-16*S[0])+36*S[1])-27*S[1]));
C[9]=+S[3]*(S[1]*(S[0]*(S[2]*(6-8*S[0])+12*S[1])-9*S[1]));
C[10]=+S[0]*(S[2]*(S[1]*(16*S[0]-12)));
C[11]=+S[0]*(S[2]*(S[1]*(32*S[0]-24)));
C[12]=+S[3]*(S[1]*(S[0]*(S[2]*(24-32*S[0])+36*S[1])-27*S[1]));
C[13]=+S[0]*(S[2]*(S[3]*(S[1]*(16*S[0]-12))));
C[14]=+S[0]*(S[2]*(S[3]*(S[1]*(8*S[0]-6))));
C[15]=+S[1]*(S[0]*(S[2]*(12-16*S[0])+24*S[1])-18*S[1]);
C[16]=+S[1]*(S[0]*(S[2]*(24-32*S[0])+48*S[1])-36*S[1]);
C[17]=+S[4]*(S[1]*(S[0]*(S[2]*(12-16*S[0])+12*S[1])-9*S[1]));
C[18]=+S[3]*(S[1]*(S[0]*(S[2]*(24-32*S[0])+48*S[1])-36*S[1]));
C[19]=+S[3]*(S[1]*(S[0]*(S[2]*(12-16*S[0])+24*S[1])-18*S[1]));
C[20]=+S[5]*(S[3]*(12*S[0]-9));
C[21]=+S[2]*(S[3]*(S[1]*(S[0]*(8*S[0]-18)+9)));
C[22]=+S[2]*(S[3]*(S[1]*(S[0]*(16*S[0]-36)+18)));
C[23]=+S[3]*(S[0]*(S[2]*(32*S[0]-72)+60*S[1])+36*S[2]-45*S[1]);
C[24]=+S[4]*(S[1]*(S[0]*(S[2]*(8*S[0]-18)+12*S[1])+9*(S[2]-S[1])));
C[25]=+S[3]*(S[1]*(S[0]*(S[2]*(8*S[0]-18)+12*S[1])+9*(S[2]-S[1])));
C[26]=+S[1]*(S[0]*(S[2]*(32*S[0]-72)+24*S[1])+36*S[2]-18*S[1]);
C[27]=+S[1]*(S[0]*(S[2]*(64*S[0]-144)+48*S[1])+72*S[2]-36*S[1]);
C[28]=+S[3]*(S[1]*(S[0]*(S[2]*(16*S[0]-36)+12*S[1])+18*S[2]-9*S[1]));
C[29]=+S[3]*(S[1]*(S[0]*(S[2]*(32*S[0]-72)+24*S[1])+36*S[2]-18*S[1]));
C[30]=+S[3]*(S[0]*(S[2]*(8*S[0]-18)+12*S[1])+9*(S[2]-S[1]));
C[31]=+S[0]*(S[2]*(32*S[0]-72)+24*S[1])+36*S[2]-18*S[1];
C[32]=+S[3]*(S[0]*(S[2]*(48*S[0]-108)+36*S[1])+54*S[2]-27*S[1]);
C[33]=+S[3]*(S[0]*(S[2]*(16*S[0]-36)+24*S[1])+18*(S[2]-S[1]));
C[34]=+S[3]*(S[0]*(S[2]*(64*S[0]-144)+60*S[1])+72*S[2]-45*S[1]);
C[35]=+S[0]*(S[2]*(64*S[0]-144)+48*S[1])+72*S[2]-36*S[1];
C[36]=+S[0]*(S[2]*(128*S[0]-288)+96*S[1])+144*S[2]-72*S[1];
C[37]=+S[3]*(S[0]*(S[2]*(32*S[0]-72)+12*S[1])+36*S[2]-9*S[1]);
C[38]=+S[3]*(S[0]*(S[2]*(64*S[0]-144)+48*S[1])+72*S[2]-36*S[1]);
C[39]=+S[3]*(S[0]*(S[2]*(32*S[0]-72)+24*S[1])+36*S[2]-18*S[1]);
C[40]=+S[3]*(S[1]*(S[0]*(S[2]*(8*S[0]-18)+24*S[1])+9*S[2]-18*S[1]));
C[41]=+S[3]*(S[1]*(S[0]*(S[2]*(16*S[0]-36)+24*S[1])+18*(S[2]-S[1])));
C[42]=+S[4]*(S[5]*(12*S[0]-9));
C[43]=+S[3]*(S[0]*(S[2]*(16*S[0]-36)+12*S[1])+18*S[2]-9*S[1]);
C[44]=+S[4]*(S[2]*(S[0]*(8*S[0]-18)+9));
C[45]=+S[3]*(S[0]*(S[2]*(32*S[0]-72)+48*S[1])+36*(S[2]-S[1]));
C[46]=+S[4]*(S[0]*(S[2]*(16*S[0]-36)+12*S[1])+18*S[2]-9*S[1]);
C[47]=+S[3]*(S[0]*(S[2]*(8*S[0]-18)+24*S[1])+9*S[2]-18*S[1]);
C[48]=+S[4]*(S[0]*(S[2]*(18-8*S[0])+24*S[1])-18*S[1]-9*S[2]);
C[49]=+S[3]*(S[0]*(S[2]*(32*S[0]-72)+36*S[1])+36*S[2]-27*S[1]);
C[50]=+S[1]*(96*S[0]-72);
C[51]=+S[1]*(72*S[0]-54);
C[52]=+S[3]*(S[1]*(36*S[0]-27));
C[53]=+S[2]*(S[3]*(S[0]*(16*S[0]-36)+18));
C[54]=+S[4]*(S[0]*(S[2]*(36-16*S[0])+12*S[1])-9*S[1]-18*S[2]);
C[55]=+S[3]*(S[1]*(48*S[0]-36));
C[56]=+S[1]*(24*S[0]-18);
C[57]=+S[1]*(48*S[0]-36);
C[58]=+S[3]*(S[1]*(12*S[0]-9));
C[59]=+S[3]*(S[1]*(24*S[0]-18));
C[60]=+S[4]*(S[1]*(12*S[0]-9));
S[6]=va[15]*va[15];
S[7]=va[2]*va[2]*va[2]*va[2]*va[2]*va[2];
C[61]=+72*S[6]*S[2]*S[7];
S[8]=va[24]*va[24];
S[9]=va[20]*va[20];
S[10]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[62]=+S[8]*S[9]*S[10];
}
TOTNUM=+C[62];
S[0]=va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[61]*S[0];
S[1]=va[28]*va[28];
S[2]=DP[6]*DP[6];
tmp[0]=+DP[0]*(DP[9]*(S[1]*(C[56]*(S[1]+DP[5])+C[57]*DP[1]-C[47]+C[50]*
 DP[3])+DP[5]*(C[53]-C[57]*DP[1])+C[59]*DP[8]-C[55]*DP[2]-C[49]*DP[3]-C[58]*
 DP[6])+DP[5]*(C[58]*(-DP[3]-DP[6])+C[14]+C[15]*S[1]-C[16]*DP[1]+C[59]*
 DP[5]+C[45]*DP[8])+S[1]*(C[15]*S[1]-C[0]+C[16]*DP[1]+C[3]*DP[3])+DP[8]*(
 C[40]-C[43]*DP[3]-C[58]*DP[6]+C[59]*DP[8])-C[18]*DP[2]-C[2]*DP[3]-C[20]*
 DP[6])+DP[2]*(DP[3]*(DP[9]*(C[59]-C[51]*S[1]-C[57]*DP[1])+C[59]*(-DP[5]-
 DP[8])+C[4]-C[5]*S[1]-C[16]*DP[1]+C[58]*DP[3]+C[33]*DP[6])+DP[9]*(C[55]*(
 DP[1]+DP[2]+DP[5])+S[1]*(C[59]-C[50]*DP[1])-C[48])+DP[6]*(C[58]*DP[6]-
 C[21]-C[39]*DP[5]-C[59]*DP[8])+C[18]*(DP[1]+DP[2]+DP[5])+S[1]*(C[19]-C[3]*
 DP[1])-C[1]);
tmp[1]=+DP[4]*(S[1]*(DP[3]*(C[57]*(DP[5]-DP[1])+C[50]*(-DP[3]-DP[6])+C[58]-
 C[56]*S[1]+C[51]*DP[8])+DP[1]*(C[50]*(DP[5]+DP[8])+C[10]-C[57]*DP[6])+
 DP[6]*(C[56]*(-S[1]-DP[5])+C[30])+C[59]*(-DP[5]-DP[8])+C[13]+C[58]*DP[4]+
 C[33]*DP[7])+DP[1]*(C[58]*(DP[3]-DP[4]+DP[6]+DP[9])+DP[5]*(C[50]*DP[3]-
 C[59]+C[57]*DP[6])+DP[8]*(C[57]*DP[3]-C[59])+C[9]-C[11]*DP[1]-C[33]*DP[7])+
 C[52]*(DP[2]*(DP[3]+DP[6]+DP[9])+DP[8]*(-DP[3]-DP[4]-DP[7])+DP[6]*(DP[4]+
 DP[7])-DP[9]*DP[0])+DP[5]*(C[55]*(-DP[2]-DP[5]-DP[8])+C[59]*(-DP[3]-DP[4])+
 C[58]*DP[0]-C[43]*DP[6]-C[37]*DP[7])+DP[3]*(C[55]*(DP[3]+DP[4])+C[23]*
 DP[6]+C[34]*DP[7])+DP[8]*(C[58]*DP[0]-C[44]-C[55]*DP[2]-C[59]*DP[6])+C[12]*
 DP[2]-C[7]-C[8]*DP[0]+C[58]*S[2]-C[60]*DP[9]);
S[3]=DP[8]*DP[8];
tmp[2]=+DP[5]*(C[59]*(DP[0]*(DP[4]*(DP[5]+DP[8])+DP[5]*DP[3]+DP[8]*DP[7]-
 DP[9]*DP[2])+DP[1]*(DP[4]*(-DP[3]-DP[4])+DP[7]*(-DP[6]-DP[7]))+DP[2]*(
 DP[3]*(-DP[3]-DP[4])))+DP[7]*(DP[1]*(C[45]*(-DP[3]-DP[4]))+DP[5]*(C[46]+
 C[39]*DP[0])+C[60]*DP[8]-C[39]*DP[3]*DP[2])+DP[2]*(-C[17]-C[19]*DP[0]-
 C[39]*DP[6]*DP[3]-C[54]*DP[9])+DP[8]*(C[45]*DP[3]*DP[0]-C[46]*DP[4]))+
 DP[2]*(DP[3]*(C[59]*(DP[8]*(-DP[3]-DP[4]-DP[6]-DP[7])+DP[9]*(DP[1]+DP[2]))+
 C[6]*DP[1]+C[19]*DP[2])+DP[1]*(DP[7]*(C[29]+C[59]*DP[9])+C[13]*DP[4]+C[22]*
 DP[6])+DP[8]*(C[42]+C[60]*DP[9]))+DP[1]*(DP[8]*(C[59]*(DP[6]*DP[4]-DP[7]*
 DP[3]-DP[9]*DP[0])-C[41]*DP[0])+DP[1]*(DP[7]*(C[41]+C[59]*DP[9])))+S[3]*(
 C[59]*DP[3]*DP[0]-C[60]*DP[4]);
RNUM=+S[1]*(DP[7]*(S[1]*(DP[3]*(C[35]*(DP[5]-DP[1])+C[30]-C[31]*S[1]-C[36]*
 DP[3]-C[50]*DP[6]+C[51]*DP[8])+DP[1]*(C[26]+C[36]*DP[5]-C[57]*DP[6]+C[50]*
 DP[8]+C[56]*DP[9])+DP[6]*(C[56]*(-S[1]-DP[5])+C[58])+C[59]*(DP[9]-DP[8])+
 C[29]-C[39]*DP[5]+C[58]*DP[7])+DP[1]*(DP[3]*(C[43]+C[36]*DP[5]+C[57]*
 DP[8])+C[58]*(DP[6]-DP[7]-DP[9])+DP[1]*(-C[27]-C[57]*DP[9])+DP[5]*(C[57]*
 DP[6]-C[39])-C[25]-C[59]*DP[8])+DP[5]*(C[38]*(-DP[2]-DP[5])+C[58]*(DP[6]+
 DP[7])+C[44]+C[43]*DP[0]-C[53]*DP[3]-C[55]*DP[8])+DP[2]*(C[32]*DP[3]-C[28]+
 C[52]*DP[6]-C[55]*DP[8]-C[58]*DP[9])+DP[3]*(C[58]*(DP[7]-DP[8])+C[49]*
 DP[3]+C[52]*DP[6])+DP[0]*(C[58]*(DP[8]-DP[9])-C[28])-C[24]-C[60]*DP[9])+
 tmp[0]+tmp[1])+tmp[2];
result=RNUM*(TOTNUM/TOTDEN)*Q1[4]*Q1[1]*Q1[2]*Q1[11]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
