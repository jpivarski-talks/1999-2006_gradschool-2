/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                S           W+    !  W+          S                   
              ==<==@-------1>-----!-->1-------@==<==                 
                P1 |        P3    !  P3       |  P1                  
                   |              !           |                      
                   |        B     !  B        |                      
                  u|P6   /==<=====!==<==\    u|-P8                   
                   |     |  P5    !  P5 |     |                      
                   |     |        !     |     |                      
                u  |  Z  |  b     !  b  |  Z  |  u                   
              ==>==@-2---@==>=====!==>==@---3-@==>==                 
                P2    P7    P4    !  P4   -P9    P2                  
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F974;
double F974(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[26];double S[10];                                           
     
if(calcCoef[9])
{
S[0]=va[2]*va[2];
S[1]=va[13]*va[13];
S[2]=va[6]*va[6];
S[3]=va[13]*va[13]*va[13]*va[13];
S[4]=va[10]*va[10];
C[0]=+S[4]*(S[1]*(S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(192-64*S[0])-180)-144*S[1])+
 216*S[1]+54*S[2])+S[3]*(144*S[0]-216))+S[1]*(81*(S[1]-S[2]))));
C[1]=+S[1]*(S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(192-64*S[0])-180)-144*S[1])+216*
 S[1]+54*S[2])+S[3]*(144*S[0]-216))+S[1]*(81*(S[1]-S[2])));
C[2]=+S[4]*(S[1]*(S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(384-128*S[0])-360)-288*
 S[1])+432*S[1]+108*S[2])+S[3]*(288*S[0]-432))+S[1]*(162*(S[1]-S[2]))));
C[3]=+S[1]*(S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(768-256*S[0])-720)-576*S[1])+864*
 S[1]+216*S[2])+S[3]*(576*S[0]-864))+S[1]*(324*(S[1]-S[2])));
C[4]=+S[4]*(S[0]*(S[0]*(S[2]*(S[2]*(S[0]*(64*S[0]-96)+36)-144*S[1])+144*
 S[3])+S[1]*(216*(S[2]-S[1])))+S[1]*(81*(S[1]-S[2])));
C[5]=+S[0]*(S[0]*(S[2]*(S[2]*(S[0]*(64*S[0]-96)+36)-144*S[1])+144*S[3])+
 S[1]*(216*(S[2]-S[1])))+S[1]*(81*(S[1]-S[2]));
C[6]=+S[4]*(S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(64*S[0]-288)+468)-144*S[1])+216*
 S[1]-324*S[2])+S[3]*(144*S[0]-216))+81*(S[2]*(S[2]-S[1])+S[3]));
C[7]=+S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(64*S[0]-288)+468)-144*S[1])+216*S[1]-
 324*S[2])+S[3]*(144*S[0]-216))+81*(S[2]*(S[2]-S[1])+S[3]);
C[8]=+S[4]*(S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(128*S[0]-576)+936)-288*S[1])+432*
 S[1]-648*S[2])+S[3]*(288*S[0]-432))+162*(S[2]*(S[2]-S[1])+S[3]));
C[9]=+S[0]*(S[2]*(S[0]*(S[2]*(S[0]*(256*S[0]-1152)+1872)-576*S[1])+864*S[1]-
 1296*S[2])+S[3]*(576*S[0]-864))+324*(S[2]*(S[2]-S[1])+S[3]);
C[10]=+S[4]*(S[1]*(S[0]*(S[0]*(144*(S[1]-S[2]))+216*(S[2]-S[1]))+81*(S[1]-
 S[2])));
C[11]=+S[1]*(S[0]*(S[0]*(144*(S[1]-S[2]))+216*(S[2]-S[1]))+81*(S[1]-S[2]));
C[12]=+S[4]*(S[0]*(S[0]*(S[2]*(S[2]*(S[0]*(128*S[0]-192)+72)-288*S[1])+288*
 S[3])+S[1]*(432*(S[2]-S[1])))+S[1]*(162*(S[1]-S[2])));
C[13]=+S[0]*(S[0]*(S[2]*(S[2]*(S[0]*(256*S[0]-384)+144)-576*S[1])+576*S[3])+
 S[1]*(864*(S[2]-S[1])))+S[1]*(324*(S[1]-S[2]));
C[14]=+S[4]*(S[1]*(S[0]*(S[0]*(288*(S[1]-S[2]))+432*(S[2]-S[1]))+162*(S[1]-
 S[2])));
C[15]=+S[1]*(S[0]*(S[0]*(576*(S[1]-S[2]))+864*(S[2]-S[1]))+324*(S[1]-S[2]));
C[16]=+S[4]*(S[1]*(S[0]*(S[0]*(288*S[1]-144*S[2])+216*S[2]-432*S[1])+162*
 S[1]-81*S[2]));
C[17]=+S[1]*(S[0]*(S[0]*(288*S[1]-144*S[2])+216*S[2]-432*S[1])+162*S[1]-81*
 S[2]);
C[18]=+S[4]*(S[1]*(S[0]*(S[0]*(576*S[1]-288*S[2])+432*S[2]-864*S[1])+324*
 S[1]-162*S[2]));
C[19]=+S[1]*(S[0]*(S[0]*(1152*S[1]-576*S[2])+864*S[2]-1728*S[1])+648*S[1]-
 324*S[2]);
C[20]=+S[4]*(S[1]*(S[0]*(144*S[0]-216)+81));
C[21]=+S[1]*(S[0]*(144*S[0]-216)+81);
C[22]=+S[4]*(S[1]*(S[0]*(288*S[0]-432)+162));
C[23]=+S[1]*(S[0]*(576*S[0]-864)+324);
S[5]=va[15]*va[15]*va[15]*va[15];
S[6]=va[6]*va[6]*va[6]*va[6];
S[7]=va[2]*va[2]*va[2]*va[2]*va[2]*va[2];
C[24]=+648*S[5]*S[6]*S[7];
S[8]=va[20]*va[20];
S[9]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[25]=+S[8]*S[9];
}
TOTNUM=-C[25];
S[0]=va[28]*va[28];
TOTDEN=+C[24]*S[0];
RNUM=+S[0]*(DP[9]*(DP[1]*(C[23]*(DP[4]*(DP[3]-DP[5]+DP[6]-DP[8])+DP[7]*(
 DP[3]-DP[5]+DP[6]-DP[8])+DP[9]*(DP[2]-DP[0]))+C[19]*(DP[2]-DP[0]))+S[0]*(
 C[21]*(DP[3]*(DP[4]+DP[7])+DP[6]*(DP[4]+DP[7])-DP[9]*DP[0])-C[17]*DP[0])+
 C[20]*(DP[3]*(-DP[4]-DP[7])+DP[6]*(-DP[4]-DP[7])+DP[9]*DP[0])+C[22]*(DP[4]*
 (DP[5]+DP[8])+DP[7]*(DP[5]+DP[8])-DP[9]*DP[2])+C[16]*DP[0]-C[18]*DP[2])+
 DP[1]*(DP[4]*(C[15]*(DP[3]-DP[5])+C[13]*(DP[6]-DP[8]))+DP[7]*(C[9]*(DP[3]-
 DP[5])+C[15]*(DP[6]-DP[8]))+C[3]*(DP[2]-DP[0]))+DP[4]*(S[0]*(C[11]*DP[3]+
 C[5]*DP[6])+C[14]*DP[5]-C[10]*DP[3]-C[4]*DP[6]+C[12]*DP[8])+DP[7]*(S[0]*(
 C[7]*DP[3]+C[11]*DP[6])+C[8]*DP[5]-C[6]*DP[3]-C[10]*DP[6]+C[14]*DP[8])+
 DP[0]*(C[0]-C[1]*S[0])-C[2]*DP[2])+DP[1]*(DP[9]*(DP[1]*(C[23]*(DP[3]*(-
 DP[4]-DP[7])+DP[6]*(-DP[4]-DP[7])+DP[9]*DP[0])+C[19]*DP[0])+C[22]*(DP[4]*(
 DP[5]+DP[8])+DP[7]*(DP[5]+DP[8])-DP[9]*DP[2])-C[18]*DP[2])+DP[1]*(DP[3]*(-
 C[15]*DP[4]-C[9]*DP[7])+DP[6]*(-C[13]*DP[4]-C[15]*DP[7])+C[3]*DP[0])+DP[4]*
 (C[14]*DP[5]+C[12]*DP[8])+DP[7]*(C[8]*DP[5]+C[14]*DP[8])-C[2]*DP[2]);
result=RNUM*(TOTNUM/TOTDEN)*Q2[4]*Q2[1]*Q0[2]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
  color_weights[0] += result*(1)/(1);
 }
 return result;
}
