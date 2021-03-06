/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
/*
                                        !  b     c                   
                c                 B   /=!==>==@==>==                 
              ==>==\           /==<==\| !  P4 |  P1                  
                P1 |           |  P5 || !   W+|-P8                   
                   |           |     || !  B  4                      
                B  |  W+    A  |  b  \+=!==<==@                      
              ==<==@-1>--@-3---@==>===/ !  P5 |                      
                P2    P6 |  P7    P4    !    t|-P9                   
                         |              !  W+ |  B                   
                         |        W+   /!-->2-@==<==                 
                         \-------2>----/!  P3    P2                  
                                  P3    !                            
*/
#include<math.h>
extern double *Q0, *Q1, *Q2;
extern double va[29];
#include"out_ext.h"
#include"out_int.h"
FNN F911;
double F911(void)
{
double TOTNUM,TOTDEN,RNUM,result;
static double C[166];double S[9];double tmp[7];                             
     
if(calcCoef[8])
{
S[0]=va[13]*va[13];
S[1]=va[9]*va[9];
S[2]=va[13]*va[13]*va[13]*va[13]*va[13]*va[13];
C[0]=+S[2]*(S[1]*(6*S[0]+2*S[1]));
C[1]=+6*S[2]*S[1];
S[3]=va[13]*va[13]*va[13]*va[13];
C[2]=+S[3]*(6*S[0]-4*S[1]);
C[3]=+S[2]*(S[0]+3*S[1]);
C[4]=+S[3]*(5*S[0]+4*S[1]);
C[5]=+6*S[3];
C[6]=+4*S[2];
C[7]=+S[1]*(S[0]*(20*S[0]+S[1]));
C[8]=+S[0]*(14*S[0]-18*S[1]);
C[9]=+S[3]*(2*S[0]+4*S[1]);
C[10]=+S[1]*(S[0]*(8*S[0]+2*S[1]));
C[11]=+14*S[0]*S[1];
C[12]=+S[0]*(4*S[0]-8*S[1]);
C[13]=+S[2]*(2*S[0]+6*S[1]);
C[14]=+S[3]*(11*S[0]-8*S[1]);
C[15]=+13*S[3];
C[16]=+S[0]*(4*S[0]-3*S[1]);
C[17]=+S[3]*(S[0]-2*S[1]);
C[18]=+S[3]*(S[0]-8*S[1]);
C[19]=+S[0]*(17*S[0]-10*S[1]);
C[20]=+14*S[0];
C[21]=+S[3]*(S[1]*(6*S[0]-2*S[1]));
C[22]=+S[1]*(S[0]*(16*S[0]-S[1]));
C[23]=+S[0]*(10*S[0]+S[1]);
C[24]=+S[3]*(2*S[0]-S[1]);
C[25]=+S[0]*(7*S[0]-2*S[1]);
C[26]=+S[1]*(S[0]*(5*S[0]-4*S[1]));
C[27]=+18*S[0]*S[1];
C[28]=+S[1]*(S[0]*(3*S[0]-S[1]));
C[29]=+4*S[2]*S[1];
C[30]=+S[3]*(3*S[0]-6*S[1]);
C[31]=+15*S[3];
C[32]=+S[3]*(S[0]-6*S[1]);
C[33]=+S[0]*(3*S[0]-6*S[1]);
C[34]=+S[0]*(4*S[0]+2*S[1]);
C[35]=+12*S[0]-S[1];
C[36]=+8*S[0]-2*S[1];
C[37]=+S[0]*(2*S[0]-7*S[1]);
C[38]=+S[0]*(5*S[0]-4*S[1]);
C[39]=+16*S[0];
C[40]=+S[0]*(3*(S[0]+S[1]));
C[41]=+10*S[0]+2*S[1];
C[42]=+S[0]*(2*S[0]+S[1]);
C[43]=+8*S[2]*S[1];
C[44]=+S[1]*(S[0]*(4*S[0]+S[1]));
C[45]=+S[0]*(12*S[0]-S[1]);
C[46]=+10*S[0];
C[47]=+S[3]*(2*S[0]-3*S[1]);
C[48]=+S[0]*(3*S[0]+4*S[1]);
C[49]=+16*S[0]*S[1];
C[50]=+2*S[2];
C[51]=+S[0]*(2*S[0]-4*S[1]);
C[52]=+S[0]*(5*S[0]-3*S[1]);
C[53]=+4*S[0]-S[1];
C[54]=+S[0]*(4*S[0]+S[1]);
C[55]=+2*S[0]+4*S[1];
C[56]=+S[1]*(S[0]*(4*(S[0]-S[1])));
C[57]=+12*S[0]*S[1];
C[58]=+6*S[0]-8*S[1];
C[59]=+S[1]*(2*S[0]+S[1]);
C[60]=+6*S[0]-4*S[1];
C[61]=+2*S[0]+6*S[1];
C[62]=+S[1]*(8*S[0]-2*S[1]);
C[63]=+S[0]*(2*S[0]+3*S[1]);
C[64]=+2*S[0]-S[1];
C[65]=+6*S[0]-3*S[1];
C[66]=+9*S[3]*S[1];
C[67]=+S[0]*(S[0]+8*S[1]);
C[68]=+S[2]*(S[0]-S[1]);
C[69]=+S[3]*(2*(S[0]-S[1]));
C[70]=+S[3]*(S[1]*(S[0]-S[1]));
C[71]=+S[1]*(S[0]*(15*S[0]+S[1]));
C[72]=+12*S[0];
C[73]=+S[1]*(S[0]*(2*(S[0]+S[1])));
C[74]=+S[2];
C[75]=+S[0]*(S[0]+4*S[1]);
C[76]=+6*S[0]+2*S[1];
C[77]=+S[3]*(4*(S[0]+S[1]));
C[78]=+S[0]*(9*S[0]+S[1]);
C[79]=+6*S[0]*S[1];
C[80]=+8*S[3];
C[81]=+S[0]*(2*S[0]+6*S[1]);
C[82]=+12*S[0]-4*S[1];
C[83]=+S[1]*(4*S[0]+S[1]);
C[84]=+S[3]*(3*S[0]+5*S[1]);
S[4]=va[9]*va[9]*va[9]*va[9];
C[85]=+2*S[4];
C[86]=+S[0]*(6*S[0]+2*S[1]);
C[87]=+8*S[0]*S[1];
C[88]=+4*(S[0]+S[1]);
C[89]=+8*S[3]*S[1];
C[90]=+S[1]*(S[0]*(3*S[0]+S[1]));
C[91]=+S[1]*(S[0]-S[1]);
C[92]=+3*S[3]*S[1];
C[93]=+S[3]*(S[0]+S[1]);
C[94]=+S[0]*(3*S[0]-S[1]);
C[95]=+4*S[3];
C[96]=+8*S[0];
C[97]=+S[0]*(S[0]-2*S[1]);
C[98]=+4*S[0]-2*S[1];
C[99]=+S[1]*(S[0]*(2*S[0]-S[1]));
C[100]=+S[1]*(S[0]*(4*S[0]+2*S[1]));
C[101]=+S[0]*(2*S[0]+4*S[1]);
C[102]=+8*S[0]-6*S[1];
C[103]=+S[3]*(S[1]*(3*S[0]+S[1]));
C[104]=+S[3]*(S[0]+3*S[1]);
C[105]=+S[0]*(4*(S[0]-S[1]));
C[106]=+S[0]*(2*(S[0]+S[1]));
C[107]=+S[1]*(2*(S[0]-S[1]));
C[108]=+S[3]*(S[1]*(6*S[0]+2*S[1]));
C[109]=+6*S[3]*S[1];
C[110]=+5*S[0]*S[1];
C[111]=+S[3]*(2*S[0]+6*S[1]);
C[112]=+S[0]*(8*S[0]-2*S[1]);
C[113]=+4*S[0]-5*S[1];
C[114]=+S[0]*(5*S[0]-2*S[1]);
C[115]=+S[1]*(S[0]*(7*S[0]+S[1]));
C[116]=+S[1]*(14*S[0]+S[1]);
C[117]=+S[0]*(4*(S[0]+S[1]));
C[118]=+16*S[0]-12*S[1];
C[119]=+S[1]*(4*S[0]+2*S[1]);
C[120]=+12*S[1];
C[121]=+S[3]*(2*(S[0]+S[1]));
C[122]=+S[0]*(2*S[0]-S[1]);
C[123]=+2*S[0]-3*S[1];
C[124]=+3*S[3];
C[125]=+S[0]*(2*S[0]+7*S[1]);
C[126]=+6*S[0]-2*S[1];
C[127]=+6*S[1];
C[128]=+4*(S[0]-S[1]);
C[129]=+S[1]*(S[0]*(2*(S[0]-S[1])));
C[130]=+S[1]*(11*S[0]-2*S[1]);
C[131]=+2*S[0]+3*S[1];
C[132]=+S[0]*(S[0]+2*S[1]);
C[133]=+2*S[0];
C[134]=+S[1]*(5*S[0]-4*S[1]);
C[135]=+10*S[1];
C[136]=+2*(S[0]+S[1]);
C[137]=+S[0]*(2*(S[0]-S[1]));
C[138]=+S[1]*(5*S[0]-S[1]);
C[139]=+S[0]*(4*S[0]-S[1]);
C[140]=+S[0]*(S[0]-S[1]);
C[141]=+2*S[0]+S[1];
C[142]=+6*S[0];
C[143]=+4*S[0]+2*S[1];
C[144]=+4*S[0];
C[145]=+4*S[3]*S[1];
C[146]=+S[0]*S[1];
C[147]=+S[0]*(S[0]+3*S[1]);
C[148]=+2*S[0]+5*S[1];
C[149]=+S[3];
C[150]=+3*S[0]*S[1];
C[151]=+2*S[3];
C[152]=+2*S[3]*S[1];
C[153]=+4*S[0]*S[1];
C[154]=+S[0]*(S[0]+S[1]);
C[155]=+2*(S[0]-S[1]);
C[156]=+S[3]*(S[0]-S[1]);
C[157]=+2*S[0]*S[1];
C[158]=+S[1]*(S[0]*(S[0]-S[1]));
C[159]=+S[1]*(7*S[0]-S[1]);
C[160]=+2*S[1];
C[161]=+S[1]*(2*(S[0]+S[1]));
C[162]=+8*S[1];
C[163]=+4*S[1];
S[5]=va[2]*va[2]*va[2]*va[2];
C[164]=+36*S[5];
S[6]=va[27]*va[27];
S[7]=va[24]*va[24];
S[8]=va[1]*va[1]*va[1]*va[1]*va[1]*va[1];
C[165]=+S[6]*S[7]*S[8];
}
TOTNUM=-C[165];
S[0]=va[28]*va[28]*va[28]*va[28]*va[28]*va[28];
TOTDEN=+C[164]*S[0];
S[1]=va[28]*va[28];
tmp[0]=+DP[7]*(DP[3]*(C[155]*(DP[8]-DP[1])+C[64]*(DP[6]-DP[3])+C[123]*DP[4]-
 C[52]-C[96]*DP[0]+C[163]*DP[5]-C[65]*DP[7])+DP[5]*(C[160]*(DP[4]-DP[5]+
 DP[7])+C[60]*DP[0]-C[59]-C[61]*DP[1]+C[143]*DP[6])+DP[1]*(C[48]+C[133]*
 DP[1]-C[58]*DP[4]+C[163]*DP[9])+DP[4]*(C[57]+C[65]*DP[6]-C[160]*DP[8])+
 DP[0]*(-C[45]-C[148]*DP[9])+C[110]*DP[7]-C[44]-C[140]*DP[6]-C[157]*DP[8]-
 C[146]*DP[9])+DP[4]*(DP[6]*(C[64]*(DP[3]-DP[6])+C[36]*DP[1]-C[94]-C[123]*
 DP[4]+C[98]*DP[5]-C[142]*DP[8])+DP[8]*(C[160]*(DP[5]-DP[4])-C[83]-C[163]*
 DP[0]-C[155]*DP[1]-C[143]*DP[3])+DP[9]*(C[133]*DP[1]-C[130]-C[131]*DP[0])+
 C[25]*DP[1]-C[22]-C[23]*DP[0]-C[140]*DP[3]+C[110]*DP[4]-C[157]*DP[5])+
 DP[0]*(DP[8]*(C[76]*DP[3]-C[67]-C[133]*DP[1]+C[88]*DP[5]+C[155]*DP[9])+
 DP[9]*(C[112]+C[123]*DP[3]+C[136]*DP[5]-C[141]*DP[6])+DP[5]*(C[124]+C[160]*
 DP[6])+C[2]-C[95]*DP[0]+C[86]*DP[1]+C[16]*DP[3]-C[42]*DP[6])+DP[6]*(DP[5]*(
 C[133]*(DP[3]+DP[6])-C[38]-C[39]*DP[1]-C[144]*DP[5])+DP[1]*(C[80]+C[142]*
 DP[9])+DP[3]*(C[95]-C[133]*DP[8])+C[30]+C[149]*DP[6]-C[139]*DP[9])+DP[1]*(
 DP[9]*(C[114]+C[133]*DP[3]-C[144]*DP[5])+C[80]*(-DP[1]-DP[5])+C[4]+C[151]*
 DP[3]-C[95]*DP[8])+DP[3]*(DP[8]*(C[75]-C[133]*DP[3]+C[144]*DP[5])+C[14]+
 C[149]*DP[3]+C[122]*DP[9])+DP[5]*(C[92]+C[87]*DP[8]+C[153]*DP[9])+DP[8]*(-
 C[66]-C[153]*DP[9])-C[1]-C[109]*DP[9];
tmp[1]=+DP[2]*(DP[6]*(8*(DP[4]*(DP[1]+DP[2]+DP[5]+DP[8])+DP[2]*(DP[9]-
 DP[3])+DP[5]*(DP[0]-DP[7]))+S[1]*(12*(-DP[4]-DP[9])+4*DP[3]-C[39]+16*
 DP[5])+C[133]*(DP[3]-DP[1])+C[144]*(DP[7]-DP[8])+C[39]*DP[4]-C[33]-C[96]*
 DP[0]-C[41]*DP[5]+C[143]*DP[9])+DP[9]*(S[1]*(-C[135]-8*DP[0])+DP[1]*(
 C[144]+8*DP[4])+C[160]*(DP[5]+DP[7])+C[116]-C[118]*DP[0]+C[120]*DP[2]-
 C[126]*DP[3]+C[135]*DP[4]+C[163]*DP[8])+DP[3]*(S[1]*(8*DP[7]-C[133])+DP[4]*
 (C[144]-8*DP[8])-C[19]-C[72]*DP[0]-C[20]*DP[2]-C[144]*DP[5]-C[55]*DP[7]-
 C[155]*DP[8])+DP[0]*(DP[8]*(C[72]+8*DP[4])+C[96]*(DP[1]+DP[2])+C[46]*DP[5]-
 C[8]-C[72]*S[1]+C[144]*DP[7])+DP[1]*(DP[4]*(C[142]-8*DP[7])+C[96]*S[1]-
 C[157])+DP[7]*(C[49]+C[163]*DP[4]-C[120]*DP[5])+C[7]-C[49]*S[1]+C[11]*
 DP[2]+C[27]*DP[4]-C[157]*DP[5]-C[153]*DP[8]);
tmp[2]=+DP[4]*(DP[6]*(C[160]*(DP[4]-DP[6]-DP[7])+C[163]*(DP[1]+DP[2])+C[37]-
 C[143]*DP[5]-C[98]*DP[8])+DP[8]*(C[163]*(DP[4]-DP[5]-DP[7])+C[85]+C[128]*
 DP[1]-C[162]*DP[2])+DP[1]*(C[144]*(-DP[2]-DP[7]-DP[9])+C[157])+DP[9]*(
 C[134]-C[160]*DP[0]-C[163]*DP[2])+C[157]*(DP[0]-DP[4]-DP[5])+C[26]-C[163]*
 DP[7]*DP[5])+DP[2]*(DP[9]*(C[163]*(-DP[0]-DP[5]-DP[6]-DP[7])-C[119]-C[162]*
 DP[8])+DP[6]*(C[151]+C[144]*DP[1]+C[128]*DP[5]+C[96]*DP[8])+C[153]*(-DP[1]-
 DP[2]-DP[5]-DP[7])+DP[0]*(C[12]+C[144]*DP[5]+C[96]*DP[8])-C[10]-C[87]*
 DP[8])+DP[7]*(DP[5]*(C[128]*(-DP[1]-DP[6])+C[163]*(DP[5]+DP[7])+C[144]*
 DP[0]-C[62])+C[157]*(DP[0]-DP[7]-DP[8])+DP[1]*(C[51]-C[144]*DP[1])+DP[9]*(
 C[150]+C[160]*DP[0])+C[92]-C[63]*DP[6])+DP[0]*(DP[9]*(C[160]*(DP[5]+DP[6]+
 DP[8])-C[117])+DP[1]*(C[105]+C[144]*DP[8])+DP[6]*(C[153]-C[163]*DP[5])+
 C[81]*DP[8]-C[121])+DP[6]*(DP[1]*(-C[151]-C[144]*DP[9])+C[150]*DP[9]-C[32]-
 C[40]*DP[5]-C[42]*DP[6]-C[94]*DP[8])+DP[9]*(C[151]*DP[1]-C[115]+C[138]*
 DP[5]+C[159]*DP[8])+C[28]*DP[5]-C[103]-C[9]*DP[1]+C[71]*DP[8];
tmp[3]=+DP[0]*(DP[5]*(DP[8]*(C[144]*(-DP[3]-DP[7])+C[160]*(-DP[4]-DP[6]))+
 DP[5]*(C[144]*DP[6]-C[154]+C[160]*DP[7])+C[150]*(-DP[3]-DP[7])+C[146]*(-
 DP[4]-DP[6])-C[152]-C[157]*DP[0]-C[154]*DP[9])+DP[8]*(DP[8]*(C[160]*DP[3]-
 C[154]+C[144]*DP[4])+C[146]*(-DP[3]-DP[7])+C[150]*(-DP[4]-DP[6])+C[152]+
 C[157]*DP[0]+C[154]*DP[9])+DP[9]*(C[147]*(-DP[3]-DP[7])+C[140]*(DP[4]+
 DP[6])+C[111])+DP[3]*(C[153]*DP[4]-C[84]+C[87]*DP[7])+DP[6]*(C[153]*DP[7]-
 C[104])+C[13]-C[104]*DP[4]-C[84]*DP[7])+DP[3]*(DP[7]*(C[140]*(DP[4]-DP[3]+
 DP[6]-DP[7])+C[84]-C[149]*DP[5]+C[122]*DP[8])+DP[8]*(C[149]*(DP[3]+DP[6])+
 C[154]*DP[4]-C[74]-C[106]*DP[5]-C[105]*DP[8])+DP[6]*(C[69]+C[140]*DP[4]-
 C[149]*DP[5])+C[156]*DP[3]-C[13]+C[104]*DP[4]-C[92]*DP[5]-C[121]*DP[9])+
 DP[4]*(DP[6]*(C[140]*(DP[7]-DP[4]-DP[6])-C[156]-C[146]*DP[5]-C[97]*DP[8])+
 DP[8]*(C[146]*(DP[4]+DP[7])+C[91]*DP[5]-C[92]+C[138]*DP[8])+DP[5]*(-C[99]-
 C[146]*DP[7])+C[129]*(DP[4]-DP[9])+C[56]*DP[7]-C[21])+DP[5]*(DP[6]*(C[106]*
 DP[5]-C[74]-C[149]*DP[6]-C[154]*DP[7]+C[105]*DP[8])+DP[7]*(-C[92]-C[91]*
 DP[5]-C[146]*DP[7]-C[138]*DP[8])+C[145]*DP[8]-C[70]-C[152]*DP[9])+DP[7]*(
 C[104]*DP[6]-C[43]+C[129]*DP[7]-C[99]*DP[8]-C[145]*DP[9])+DP[6]*(C[156]*
 DP[6]-C[29]-C[92]*DP[8])+DP[8]*(C[70]+C[152]*DP[9])+C[0]+C[108]*DP[9];
tmp[4]=+DP[2]*(DP[3]*(DP[7]*(C[160]*(DP[6]-DP[3]-DP[4]+DP[7])+C[128]*(DP[1]+
 DP[2])+C[144]*DP[5]-C[122]+C[102]*DP[8])+DP[2]*(C[144]*(DP[2]-DP[6])+
 C[112]+C[96]*DP[5]+C[82]*DP[8]+C[128]*DP[9])+DP[8]*(C[128]*DP[0]-C[78]+
 C[98]*DP[3]+C[160]*DP[4])+DP[6]*(C[160]*DP[4]-C[34]-C[98]*DP[5])+DP[9]*(
 C[125]+C[127]*DP[0]-C[144]*DP[1])+C[87]*DP[0]-C[18]+C[34]*DP[1]-C[42]*
 DP[3]-C[63]*DP[4]-C[94]*DP[5])+tmp[2])+DP[1]*(DP[4]*(DP[8]*(C[160]*(DP[3]+
 DP[4])-C[140]-C[98]*DP[6]-C[144]*DP[7])+DP[5]*(C[154]-C[144]*DP[6]-C[160]*
 DP[7])+C[146]*(DP[3]+DP[4]+DP[6])+C[157]*(DP[0]-DP[1])+C[24]+C[79]*DP[7]+
 C[132]*DP[9])+DP[7]*(DP[5]*(C[144]*(DP[6]+DP[7])+C[140]+C[98]*DP[3])+DP[3]*
 (C[54]-C[160]*DP[8])+C[146]*(DP[6]+DP[7])+C[47]-C[157]*DP[0]+C[151]*DP[1]+
 C[154]*DP[8]+C[149]*DP[9])+DP[8]*(C[151]*(DP[6]-DP[0])-C[69]-C[95]*DP[3]-
 C[157]*DP[9])+DP[5]*(C[152]+C[157]*DP[0]+C[151]*DP[3]+C[137]*DP[9])+DP[9]*(
 C[156]+C[124]*DP[3]+C[149]*DP[6])+C[3]+C[121]*DP[0]-C[6]*DP[1]+C[17]*DP[3]+
 C[74]*DP[6])+tmp[3];
tmp[5]=+DP[5]*(DP[7]*(DP[1]*(C[163]*(DP[3]+DP[4])+C[137])+DP[0]*(C[79]-
 C[163]*DP[5])+C[157]*(DP[7]-DP[4])+C[100]-C[151]*DP[3]-C[161]*DP[5]+C[106]*
 DP[6])+DP[2]*(DP[6]*(C[163]*(-DP[3]-DP[4])-C[137])+DP[0]*(C[153]+C[163]*
 DP[9])+C[73]-C[106]*DP[3]-C[153]*DP[4]+C[161]*DP[9])+DP[6]*(C[157]*(DP[0]+
 DP[3])+C[151]*(DP[4]+DP[6])+C[93])+DP[0]*(C[157]*(DP[4]-DP[3])+C[106]*
 DP[5])+DP[1]*(-C[95]*DP[3]-C[106]*DP[4])+C[70]+C[93]*DP[3]+C[100]*DP[4]+
 C[145]*DP[5]+C[158]*DP[9])+C[157]*(DP[2]*(DP[3]*(DP[3]+DP[4]+DP[7]-DP[9])+
 DP[6]*(DP[4]+DP[6]+DP[7]-DP[9])+DP[9]*(-DP[4]-DP[7]))+DP[1]*(DP[4]*(-DP[3]-
 DP[4]-DP[6])+DP[7]*(-DP[3]-DP[6]-DP[7])))+DP[1]*(DP[9]*(C[151]*(-DP[3]-
 DP[4]-DP[6]-DP[7]))+C[50]*(-DP[3]-DP[4]-DP[6]-DP[7])-C[153]*DP[7]*DP[4])+
 DP[2]*(C[152]*(-DP[3]-DP[4]-DP[6]-DP[7])+C[153]*DP[6]*DP[3]);
tmp[6]=+DP[2]*(DP[8]*(DP[4]*(C[163]*(DP[1]*(-DP[3]-DP[4]-DP[6])+DP[2]*(
 DP[3]-DP[6])+DP[5]*DP[0])+C[157]*(DP[4]-DP[0]+DP[6]-DP[7])+C[100]-C[86]*
 DP[1]-C[87]*DP[2]+C[161]*DP[5]-C[107]*DP[8])+DP[3]*(C[163]*(DP[2]*(DP[3]+
 DP[7])+DP[7]*DP[1]-DP[8]*DP[0])+C[93]-C[79]*DP[0]-C[80]*DP[1]-C[81]*DP[2]-
 C[157]*DP[3]-C[151]*DP[6]-C[101]*DP[7]-C[153]*DP[8])+DP[0]*(DP[2]*(C[153]+
 C[163]*DP[9])+DP[5]*(C[117]+C[163]*DP[6])+C[157]*(DP[7]-DP[6])+C[106]*
 DP[8])+DP[2]*(C[73]-C[106]*DP[6]-C[153]*DP[7]+C[161]*DP[9])+DP[5]*(C[89]+
 C[153]*DP[6]+C[107]*DP[7])+DP[1]*(-C[95]*DP[6]-C[106]*DP[7])+C[70]+C[93]*
 DP[6]+C[100]*DP[7]+C[145]*DP[8]+C[158]*DP[9])+tmp[5])+DP[8]*(DP[1]*(DP[4]*(
 C[106]*(DP[3]+DP[4]+DP[6])+C[84])+DP[3]*(C[77]-C[106]*DP[7])+C[68]+C[121]*
 DP[6]+C[104]*DP[7]+C[156]*DP[9])+DP[5]*(DP[0]*(C[106]*(-DP[4]-DP[6])-
 C[111])+C[156]*DP[3]-C[108]-C[90]*DP[4]-C[104]*DP[6]-C[158]*DP[7])+DP[8]*(
 DP[0]*(C[106]*DP[3]-C[104])+C[104]*DP[3]-C[103]+C[158]*DP[4]))+DP[5]*(
 DP[1]*(DP[7]*(C[106]*(-DP[3]-DP[4])-C[156])+C[68]+C[121]*DP[3]+C[104]*
 DP[4]+C[156]*DP[9])+DP[5]*(DP[0]*(C[106]*DP[7]-C[104])+C[90]*DP[7]-C[103]-
 C[156]*DP[6]));
RNUM=+S[1]*(S[1]*(S[1]*(DP[4]*(DP[6]*(4*(DP[5]-S[1]-DP[1]+DP[8])-C[35]-16*
 DP[0]-8*DP[4])+DP[0]*(12*DP[8]-C[39]-8*DP[9])+DP[1]*(-C[133]-12*DP[7]-4*
 DP[9])+DP[3]*(8*DP[7]-C[133]+4*DP[8])+C[160]*DP[7]-C[146]+C[127]*DP[8]-
 C[163]*DP[9])+DP[0]*(DP[5]*(C[46]+12*DP[6]+8*DP[9])+S[1]*(-C[96]-4*DP[9])+
 C[144]*(DP[1]+DP[6])+C[142]*DP[3]-C[125]-C[96]*DP[0]-C[46]*DP[7]+C[113]*
 DP[9])+DP[7]*(DP[3]*(4*S[1]-C[53]-8*DP[5])+DP[5]*(-C[160]-4*DP[6])+C[146]-
 C[133]*DP[6]+C[160]*DP[9])+DP[6]*(C[144]*(DP[3]+DP[9])+C[31]+C[142]*DP[5])+
 DP[1]*(C[5]+C[142]*DP[9])+DP[3]*(C[15]-C[142]*DP[8])-C[92]-C[110]*DP[9])+
 tmp[0]+tmp[1])+tmp[4])+tmp[6];
result=RNUM*(TOTNUM/TOTDEN)*Q1[2]*Q1[5]*Q1[10]*Q1[12]*Q0[1]*Q0[3];
 if(result>Fmax) Fmax=result; else if(result<-Fmax) Fmax=-result;
 if(color_weights)
 {
 }
 return result;
}
