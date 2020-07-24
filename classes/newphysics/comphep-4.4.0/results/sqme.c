/************************************************
*    CompHEP version 4.4.0      *
*------------------------------------------------
* Copyright (C) 2001-2003, CompHEP Collaboration*
************************************************/
#include<math.h>
extern double va[24];
#include"out_int.h"
#include"out_ext.h"
#include"../src/num/include/alphas2.h"
#include"../src/num/include/strfun.h"
#include"../src/num/include/q_kin.h"
char  processch[] = "pb,pb -> j3, j3, H";
double DP[45];
static double xstr0,xstr1;
static int strfun_calc;
extern DNN d_1,d_2,d_3,d_4,d_5,d_6,d_7,d_8,d_9,d_10,d_11,d_12,d_13,d_14,
 d_15,d_16,d_17,d_18,d_19,d_20,d_21,d_22,d_23,d_24,d_25,d_26,d_27,d_28,d_29,
 d_30,d_31,d_32,d_33,d_34,d_35,d_36,d_37,d_38,d_39,d_40,d_41,d_42,d_43,d_44,
 d_45,d_46,d_47,d_48,d_49,d_50,d_51,d_52,d_53,d_54,d_55,d_56,d_57,d_58,d_59,
 d_60,d_61,d_62,d_63,d_64,d_65,d_66,d_67,d_68,d_69,d_70,d_71,d_72,d_73,d_74,
 d_75,d_76,d_77,d_78,d_79,d_80,d_81,d_82,d_83,d_84,d_85,d_86,d_87,d_88,d_89,
 d_90,d_91,d_92,d_93,d_94,d_95,d_96,d_97,d_98,d_99,d_100,d_101,d_102,d_103,
 d_104,d_105,d_106,d_107,d_108,d_109,d_110,d_111,d_112,d_113,d_114,d_115,
 d_116,d_117,d_118,d_119,d_120,d_121,d_122,d_123,d_124,d_125,d_126,d_127,
 d_128,d_129,d_130,d_131,d_132,d_133,d_134,d_135,d_136,d_137,d_138,d_139,
 d_140,d_141,d_142,d_143,d_144,d_145,d_146,d_147,d_148,d_149,d_150,d_151,
 d_152,d_153,d_154,d_155,d_156,d_157,d_158,d_159,d_160,d_161,d_162,d_163,
 d_164,d_165,d_166,d_167,d_168,d_169,d_170,d_171,d_172,d_173,d_174,d_175,
 d_176,d_177,d_178,d_179,d_180,d_181,d_182,d_183,d_184,d_185,d_186,d_187,
 d_188,d_189,d_190,d_191,d_192,d_193,d_194,d_195,d_196,d_197,d_198,d_199,
 d_200,d_201,d_202,d_203,d_204,d_205,d_206,d_207,d_208,d_209,d_210,d_211,
 d_212,d_213,d_214,d_215,d_216,d_217,d_218,d_219,d_220,d_221,d_222,d_223,
 d_224,d_225,d_226,d_227,d_228,d_229,d_230,d_231,d_232,d_233,d_234,d_235,
 d_236,d_237,d_238,d_239,d_240,d_241,d_242,d_243,d_244,d_245,d_246,d_247,
 d_248,d_249,d_250,d_251,d_252,d_253,d_254,d_255,d_256,d_257,d_258,d_259,
 d_260,d_261,d_262,d_263,d_264,d_265,d_266,d_267,d_268,d_269,d_270,d_271,
 d_272,d_273,d_274,d_275,d_276,d_277,d_278,d_279,d_280,d_281,d_282,d_283,
 d_284,d_285,d_286,d_287,d_288,d_289,d_290,d_291,d_292,d_293,d_294,d_295,
 d_296,d_297,d_298,d_299,d_300,d_301,d_302,d_303,d_304,d_305,d_306,d_307,
 d_308,d_309,d_310,d_311,d_312,d_313,d_314,d_315,d_316,d_317,d_318,d_319,
 d_320,d_321,d_322,d_323,d_324,d_325,d_326,d_327,d_328,d_329,d_330,d_331,
 d_332,d_333,d_334,d_335,d_336,d_337,d_338,d_339,d_340,d_341,d_342,d_343,
 d_344,d_345,d_346,d_347,d_348,d_349,d_350,d_351,d_352,d_353,d_354,d_355,
 d_356,d_357,d_358,d_359,d_360,d_361,d_362,d_363,d_364,d_365,d_366,d_367,
 d_368,d_369,d_370,d_371,d_372,d_373,d_374,d_375,d_376,d_377,d_378,d_379,
 d_380,d_381,d_382,d_383,d_384,d_385,d_386,d_387,d_388,d_389,d_390,d_391,
 d_392,d_393,d_394,d_395,d_396,d_397,d_398,d_399,d_400,d_401,d_402,d_403,
 d_404,d_405,d_406,d_407,d_408,d_409,d_410,d_411,d_412,d_413,d_414,d_415,
 d_416,d_417,d_418,d_419,d_420,d_421,d_422,d_423,d_424,d_425,d_426,d_427,
 d_428,d_429,d_430,d_431,d_432,d_433,d_434,d_435,d_436,d_437,d_438,d_439,
 d_440,d_441,d_442,d_443,d_444,d_445,d_446,d_447,d_448,d_449,d_450,d_451,
 d_452,d_453,d_454,d_455,d_456,d_457,d_458,d_459,d_460,d_461,d_462,d_463,
 d_464,d_465,d_466,d_467,d_468,d_469,d_470,d_471,d_472,d_473,d_474,d_475,
 d_476,d_477,d_478,d_479,d_480,d_481,d_482,d_483,d_484,d_485,d_486,d_487,
 d_488,d_489,d_490,d_491,d_492,d_493,d_494,d_495,d_496,d_497,d_498,d_499,
 d_500;
extern FNN F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,F14,F15,F16,F17,F18,
 F19,F20,F21,F22,F23,F24,F25,F26,F27,F28,F29,F30,F31,F32,F33,F34,F35,F36,
 F37,F38,F39,F40,F41,F42,F43,F44,F45,F46,F47,F48,F49,F50,F51,F52,F53,F54,
 F55,F56,F57,F58,F59,F60,F61,F62,F63,F64,F65,F66,F67,F68,F69,F70,F71,F72,
 F73,F74,F75,F76,F77,F78,F79,F80,F81,F82,F83,F84,F85,F86,F87,F88,F89,F90,
 F91,F92,F93,F94,F95,F96,F97,F98,F99,F100,F101,F102,F103,F104,F105,F106,
 F107,F108,F109,F110,F111,F112,F113,F114,F115,F116,F117,F118,F119,F120,F121,
 F122,F123,F124,F125,F126,F127,F128,F129,F130,F131,F132,F133,F134,F135,F136,
 F137,F138,F139,F140,F141,F142,F143,F144,F145,F146,F147,F148,F149,F150,F151,
 F152,F153,F154,F155,F156,F157,F158,F159,F160,F161,F162,F163,F164,F165,F166,
 F167,F168,F169,F170,F171,F172,F173,F174,F175,F176,F177,F178,F179,F180,F181,
 F182,F183,F184,F185,F186,F187,F188,F189,F190,F191,F192,F193,F194,F195,F196,
 F197,F198,F199,F200,F201,F202,F203,F204,F205,F206,F207,F208,F209,F210,F211,
 F212,F213,F214,F215,F216,F217,F218,F219,F220,F221,F222,F223,F224,F225,F226,
 F227,F228,F229,F230,F231,F232,F233,F234,F235,F236,F237,F238,F239,F240,F241,
 F242,F243,F244,F245,F246,F247,F248,F249,F250,F251,F252,F253,F254,F255,F256,
 F257,F258,F259,F260,F261,F262,F263,F264,F265,F266,F267,F268,F269,F270,F271,
 F272,F273,F274,F275,F276,F277,F278,F279,F280,F281,F282,F283,F284,F285,F286,
 F287,F288,F289,F290,F291,F292,F293,F294,F295,F296,F297,F298,F299,F300,F301,
 F302,F303,F304,F305,F306,F307,F308,F309,F310,F311,F312,F313,F314,F315,F316,
 F317,F318,F319,F320,F321,F322,F323,F324,F325,F326,F327,F328,F329,F330,F331,
 F332,F333,F334,F335,F336,F337,F338,F339,F340,F341,F342,F343,F344,F345,F346,
 F347,F348,F349,F350,F351,F352,F353,F354,F355,F356,F357,F358,F359,F360,F361,
 F362,F363,F364,F365,F366,F367,F368,F369,F370,F371,F372,F373,F374,F375,F376,
 F377,F378,F379,F380,F381,F382,F383,F384,F385,F386,F387,F388,F389,F390,F391,
 F392,F393,F394,F395,F396,F397,F398,F399,F400,F401,F402,F403,F404,F405,F406,
 F407,F408,F409,F410,F411,F412,F413,F414,F415,F416,F417,F418,F419,F420,F421,
 F422,F423,F424,F425,F426,F427,F428,F429,F430,F431,F432,F433,F434,F435,F436,
 F437,F438,F439,F440,F441,F442,F443,F444,F445,F446,F447,F448,F449,F450,F451,
 F452,F453,F454,F455,F456,F457,F458,F459,F460,F461,F462,F463,F464,F465,F466,
 F467,F468,F469,F470,F471,F472,F473,F474,F475,F476,F477,F478,F479,F480,F481,
 F482,F483,F484,F485,F486,F487,F488,F489,F490,F491,F492,F493,F494,F495,F496,
 F497,F498,F499,F500,F501,F502,F503,F504,F505,F506,F507,F508,F509,F510,F511,
 F512,F513,F514,F515,F516,F517,F518,F519,F520,F521,F522,F523,F524,F525,F526,
 F527,F528,F529,F530,F531,F532,F533,F534,F535,F536,F537,F538,F539,F540,F541,
 F542,F543,F544,F545,F546,F547,F548,F549,F550,F551,F552,F553,F554,F555,F556,
 F557,F558,F559,F560,F561,F562,F563,F564,F565,F566,F567,F568,F569,F570,F571,
 F572,F573,F574,F575,F576,F577,F578,F579,F580,F581,F582,F583,F584,F585,F586,
 F587,F588,F589,F590,F591,F592,F593,F594,F595,F596,F597,F598,F599,F600,F601,
 F602,F603,F604,F605,F606,F607,F608,F609,F610,F611,F612,F613,F614,F615,F616,
 F617,F618,F619,F620,F621,F622,F623,F624,F625,F626,F627,F628,F629,F630,F631,
 F632,F633,F634,F635,F636,F637,F638,F639,F640,F641,F642,F643,F644,F645,F646,
 F647,F648,F649,F650,F651,F652,F653,F654,F655,F656,F657,F658,F659,F660,F661,
 F662,F663,F664,F665,F666,F667,F668,F669,F670,F671,F672,F673,F674;
static void sprod_(double*);

static double smpl(int nsub, double * momenta,int * err)
{
 double q;
 double ans, ans0=0.0, ans1=0.0;
switch(nsub)
{
  case 1:
    *err=*err|d_1(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F1()+F2();
    break;
  case 2:
    *err=*err|d_2(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F3()+F4()+F5();
    break;
  case 3:
    *err=*err|d_3(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F6();
    break;
  case 4:
    *err=*err|d_4(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F7();
    break;
  case 5:
    *err=*err|d_5(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F8();
    break;
  case 6:
    *err=*err|d_6(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F9();
    break;
  case 7:
    *err=*err|d_7(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F10();
    break;
  case 8:
    *err=*err|d_8(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F11()+F12()+F13();
    break;
  case 9:
    *err=*err|d_9(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F14()+F15()+F16();
    break;
  case 10:
    *err=*err|d_10(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F17();
    break;
  case 11:
    *err=*err|d_11(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F18();
    break;
  case 12:
    *err=*err|d_12(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F19();
    break;
  case 13:
    *err=*err|d_13(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F20();
    break;
  case 14:
    *err=*err|d_14(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F21()+F22()+F23();
    break;
  case 15:
    *err=*err|d_15(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F24();
    break;
  case 16:
    *err=*err|d_16(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F25();
    break;
  case 17:
    *err=*err|d_17(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F26();
    break;
  case 18:
    *err=*err|d_18(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F27()+F28()+F29();
    break;
  case 19:
    *err=*err|d_19(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F30()+F31()+F32();
    break;
  case 20:
    *err=*err|d_20(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F33();
    break;
  case 21:
    *err=*err|d_21(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F34();
    break;
  case 22:
    *err=*err|d_22(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F35();
    break;
  case 23:
    *err=*err|d_23(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F36();
    break;
  case 24:
    *err=*err|d_24(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F37();
    break;
  case 25:
    *err=*err|d_25(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F38();
    break;
  case 26:
    *err=*err|d_26(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F39()+F40()+F41();
    break;
  case 27:
    *err=*err|d_27(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F42();
    break;
  case 28:
    *err=*err|d_28(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F43();
    break;
  case 29:
    *err=*err|d_29(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F44();
    break;
  case 30:
    *err=*err|d_30(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F45();
    break;
  case 31:
    *err=*err|d_31(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F46();
    break;
  case 32:
    *err=*err|d_32(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F47();
    break;
  case 33:
    *err=*err|d_33(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F48()+F49()+F50();
    break;
  case 34:
    *err=*err|d_34(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F51();
    break;
  case 35:
    *err=*err|d_35(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F52();
    break;
  case 36:
    *err=*err|d_36(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F53();
    break;
  case 37:
    *err=*err|d_37(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F54();
    break;
  case 38:
    *err=*err|d_38(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F55();
    break;
  case 39:
    *err=*err|d_39(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F56();
    break;
  case 40:
    *err=*err|d_40(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F57();
    break;
  case 41:
    *err=*err|d_41(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F58();
    break;
  case 42:
    *err=*err|d_42(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F59();
    break;
  case 43:
    *err=*err|d_43(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F60();
    break;
  case 44:
    *err=*err|d_44(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F61();
    break;
  case 45:
    *err=*err|d_45(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F62();
    break;
  case 46:
    *err=*err|d_46(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F63();
    break;
  case 47:
    *err=*err|d_47(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F64();
    break;
  case 48:
    *err=*err|d_48(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F65();
    break;
  case 49:
    *err=*err|d_49(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F66();
    break;
  case 50:
    *err=*err|d_50(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F67()+F68()+F69();
    break;
  case 51:
    *err=*err|d_51(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F70();
    break;
  case 52:
    *err=*err|d_52(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F71();
    break;
  case 53:
    *err=*err|d_53(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F72();
    break;
  case 54:
    *err=*err|d_54(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F73();
    break;
  case 55:
    *err=*err|d_55(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F74();
    break;
  case 56:
    *err=*err|d_56(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F75()+F76()+F77();
    break;
  case 57:
    *err=*err|d_57(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F78();
    break;
  case 58:
    *err=*err|d_58(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F79();
    break;
  case 59:
    *err=*err|d_59(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F80();
    break;
  case 60:
    *err=*err|d_60(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F81()+F82()+F83();
    break;
  case 61:
    *err=*err|d_61(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F84();
    break;
  case 62:
    *err=*err|d_62(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F85();
    break;
  case 63:
    *err=*err|d_63(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F86();
    break;
  case 64:
    *err=*err|d_64(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F87();
    break;
  case 65:
    *err=*err|d_65(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F88();
    break;
  case 66:
    *err=*err|d_66(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F89()+F90();
    break;
  case 67:
    *err=*err|d_67(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F91()+F92()+F93();
    break;
  case 68:
    *err=*err|d_68(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F94();
    break;
  case 69:
    *err=*err|d_69(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F95();
    break;
  case 70:
    *err=*err|d_70(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F96();
    break;
  case 71:
    *err=*err|d_71(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F97();
    break;
  case 72:
    *err=*err|d_72(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F98();
    break;
  case 73:
    *err=*err|d_73(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F99()+F100()+F101();
    break;
  case 74:
    *err=*err|d_74(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F102();
    break;
  case 75:
    *err=*err|d_75(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F103();
    break;
  case 76:
    *err=*err|d_76(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F104()+F105()+F106();
    break;
  case 77:
    *err=*err|d_77(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F107();
    break;
  case 78:
    *err=*err|d_78(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F108()+F109()+F110();
    break;
  case 79:
    *err=*err|d_79(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F111();
    break;
  case 80:
    *err=*err|d_80(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F112();
    break;
  case 81:
    *err=*err|d_81(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F113();
    break;
  case 82:
    *err=*err|d_82(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F114();
    break;
  case 83:
    *err=*err|d_83(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F115();
    break;
  case 84:
    *err=*err|d_84(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F116()+F117()+F118();
    break;
  case 85:
    *err=*err|d_85(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F119();
    break;
  case 86:
    *err=*err|d_86(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F120();
    break;
  case 87:
    *err=*err|d_87(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F121();
    break;
  case 88:
    *err=*err|d_88(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F122();
    break;
  case 89:
    *err=*err|d_89(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F123();
    break;
  case 90:
    *err=*err|d_90(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F124();
    break;
  case 91:
    *err=*err|d_91(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F125();
    break;
  case 92:
    *err=*err|d_92(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F126();
    break;
  case 93:
    *err=*err|d_93(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F127();
    break;
  case 94:
    *err=*err|d_94(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F128();
    break;
  case 95:
    *err=*err|d_95(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F129()+F130()+F131();
    break;
  case 96:
    *err=*err|d_96(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F132();
    break;
  case 97:
    *err=*err|d_97(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F133();
    break;
  case 98:
    *err=*err|d_98(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F134();
    break;
  case 99:
    *err=*err|d_99(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F135();
    break;
  case 100:
    *err=*err|d_100(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F136();
    break;
  case 101:
    *err=*err|d_101(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F137();
    break;
  case 102:
    *err=*err|d_102(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F138();
    break;
  case 103:
    *err=*err|d_103(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F139();
    break;
  case 104:
    *err=*err|d_104(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F140()+F141()+F142();
    break;
  case 105:
    *err=*err|d_105(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F143()+F144()+F145();
    break;
  case 106:
    *err=*err|d_106(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F146();
    break;
  case 107:
    *err=*err|d_107(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F147();
    break;
  case 108:
    *err=*err|d_108(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F148();
    break;
  case 109:
    *err=*err|d_109(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F149();
    break;
  case 110:
    *err=*err|d_110(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F150()+F151()+F152();
    break;
  case 111:
    *err=*err|d_111(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F153();
    break;
  case 112:
    *err=*err|d_112(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F154();
    break;
  case 113:
    *err=*err|d_113(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F155();
    break;
  case 114:
    *err=*err|d_114(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F156()+F157()+F158();
    break;
  case 115:
    *err=*err|d_115(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F159()+F160()+F161();
    break;
  case 116:
    *err=*err|d_116(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F162();
    break;
  case 117:
    *err=*err|d_117(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F163();
    break;
  case 118:
    *err=*err|d_118(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F164();
    break;
  case 119:
    *err=*err|d_119(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F165();
    break;
  case 120:
    *err=*err|d_120(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F166();
    break;
  case 121:
    *err=*err|d_121(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F167()+F168();
    break;
  case 122:
    *err=*err|d_122(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F169()+F170()+F171();
    break;
  case 123:
    *err=*err|d_123(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F172();
    break;
  case 124:
    *err=*err|d_124(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F173();
    break;
  case 125:
    *err=*err|d_125(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F174();
    break;
  case 126:
    *err=*err|d_126(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F175();
    break;
  case 127:
    *err=*err|d_127(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F176();
    break;
  case 128:
    *err=*err|d_128(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F177();
    break;
  case 129:
    *err=*err|d_129(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F178()+F179()+F180();
    break;
  case 130:
    *err=*err|d_130(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F181();
    break;
  case 131:
    *err=*err|d_131(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F182();
    break;
  case 132:
    *err=*err|d_132(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F183();
    break;
  case 133:
    *err=*err|d_133(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F184();
    break;
  case 134:
    *err=*err|d_134(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F185();
    break;
  case 135:
    *err=*err|d_135(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F186();
    break;
  case 136:
    *err=*err|d_136(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F187();
    break;
  case 137:
    *err=*err|d_137(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F188();
    break;
  case 138:
    *err=*err|d_138(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F189();
    break;
  case 139:
    *err=*err|d_139(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F190();
    break;
  case 140:
    *err=*err|d_140(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F191();
    break;
  case 141:
    *err=*err|d_141(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F192();
    break;
  case 142:
    *err=*err|d_142(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F193();
    break;
  case 143:
    *err=*err|d_143(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F194();
    break;
  case 144:
    *err=*err|d_144(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F195();
    break;
  case 145:
    *err=*err|d_145(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F196()+F197()+F198();
    break;
  case 146:
    *err=*err|d_146(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F199();
    break;
  case 147:
    *err=*err|d_147(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F200();
    break;
  case 148:
    *err=*err|d_148(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F201();
    break;
  case 149:
    *err=*err|d_149(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F202();
    break;
  case 150:
    *err=*err|d_150(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F203();
    break;
  case 151:
    *err=*err|d_151(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F204();
    break;
  case 152:
    *err=*err|d_152(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F205();
    break;
  case 153:
    *err=*err|d_153(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F206()+F207()+F208();
    break;
  case 154:
    *err=*err|d_154(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F209();
    break;
  case 155:
    *err=*err|d_155(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F210();
    break;
  case 156:
    *err=*err|d_156(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F211();
    break;
  case 157:
    *err=*err|d_157(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F212();
    break;
  case 158:
    *err=*err|d_158(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F213();
    break;
  case 159:
    *err=*err|d_159(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F214()+F215()+F216();
    break;
  case 160:
    *err=*err|d_160(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F217();
    break;
  case 161:
    *err=*err|d_161(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F218();
    break;
  case 162:
    *err=*err|d_162(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F219();
    break;
  case 163:
    *err=*err|d_163(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F220()+F221()+F222();
    break;
  case 164:
    *err=*err|d_164(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F223();
    break;
  case 165:
    *err=*err|d_165(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F224();
    break;
  case 166:
    *err=*err|d_166(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F225();
    break;
  case 167:
    *err=*err|d_167(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F226();
    break;
  case 168:
    *err=*err|d_168(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F227();
    break;
  case 169:
    *err=*err|d_169(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F228()+F229()+F230();
    break;
  case 170:
    *err=*err|d_170(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F231();
    break;
  case 171:
    *err=*err|d_171(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F232();
    break;
  case 172:
    *err=*err|d_172(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F233()+F234()+F235();
    break;
  case 173:
    *err=*err|d_173(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F236();
    break;
  case 174:
    *err=*err|d_174(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F237()+F238()+F239();
    break;
  case 175:
    *err=*err|d_175(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F240();
    break;
  case 176:
    *err=*err|d_176(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F241()+F242()+F243();
    break;
  case 177:
    *err=*err|d_177(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F244();
    break;
  case 178:
    *err=*err|d_178(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F245();
    break;
  case 179:
    *err=*err|d_179(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F246();
    break;
  case 180:
    *err=*err|d_180(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F247();
    break;
  case 181:
    *err=*err|d_181(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F248();
    break;
  case 182:
    *err=*err|d_182(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F249()+F250();
    break;
  case 183:
    *err=*err|d_183(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F251();
    break;
  case 184:
    *err=*err|d_184(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F252();
    break;
  case 185:
    *err=*err|d_185(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F253();
    break;
  case 186:
    *err=*err|d_186(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F254();
    break;
  case 187:
    *err=*err|d_187(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F255();
    break;
  case 188:
    *err=*err|d_188(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F256();
    break;
  case 189:
    *err=*err|d_189(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F257();
    break;
  case 190:
    *err=*err|d_190(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F258();
    break;
  case 191:
    *err=*err|d_191(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F259()+F260()+F261();
    break;
  case 192:
    *err=*err|d_192(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F262();
    break;
  case 193:
    *err=*err|d_193(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F263();
    break;
  case 194:
    *err=*err|d_194(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F264();
    break;
  case 195:
    *err=*err|d_195(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F265();
    break;
  case 196:
    *err=*err|d_196(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F266();
    break;
  case 197:
    *err=*err|d_197(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F267();
    break;
  case 198:
    *err=*err|d_198(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F268()+F269()+F270();
    break;
  case 199:
    *err=*err|d_199(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F271();
    break;
  case 200:
    *err=*err|d_200(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F272();
    break;
  case 201:
    *err=*err|d_201(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F273();
    break;
  case 202:
    *err=*err|d_202(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F274();
    break;
  case 203:
    *err=*err|d_203(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F275();
    break;
  case 204:
    *err=*err|d_204(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F276();
    break;
  case 205:
    *err=*err|d_205(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F277();
    break;
  case 206:
    *err=*err|d_206(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F278();
    break;
  case 207:
    *err=*err|d_207(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F279();
    break;
  case 208:
    *err=*err|d_208(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F280()+F281()+F282();
    break;
  case 209:
    *err=*err|d_209(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F283();
    break;
  case 210:
    *err=*err|d_210(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F284();
    break;
  case 211:
    *err=*err|d_211(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F285();
    break;
  case 212:
    *err=*err|d_212(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F286();
    break;
  case 213:
    *err=*err|d_213(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F287();
    break;
  case 214:
    *err=*err|d_214(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F288();
    break;
  case 215:
    *err=*err|d_215(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F289()+F290()+F291();
    break;
  case 216:
    *err=*err|d_216(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F292();
    break;
  case 217:
    *err=*err|d_217(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F293();
    break;
  case 218:
    *err=*err|d_218(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F294();
    break;
  case 219:
    *err=*err|d_219(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F295();
    break;
  case 220:
    *err=*err|d_220(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F296();
    break;
  case 221:
    *err=*err|d_221(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F297();
    break;
  case 222:
    *err=*err|d_222(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F298();
    break;
  case 223:
    *err=*err|d_223(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F299();
    break;
  case 224:
    *err=*err|d_224(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F300();
    break;
  case 225:
    *err=*err|d_225(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F301()+F302();
    break;
  case 226:
    *err=*err|d_226(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F303();
    break;
  case 227:
    *err=*err|d_227(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F304();
    break;
  case 228:
    *err=*err|d_228(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F305();
    break;
  case 229:
    *err=*err|d_229(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F306();
    break;
  case 230:
    *err=*err|d_230(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F307()+F308()+F309();
    break;
  case 231:
    *err=*err|d_231(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F310();
    break;
  case 232:
    *err=*err|d_232(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F311()+F312()+F313();
    break;
  case 233:
    *err=*err|d_233(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F314();
    break;
  case 234:
    *err=*err|d_234(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F315();
    break;
  case 235:
    *err=*err|d_235(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F316();
    break;
  case 236:
    *err=*err|d_236(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F317()+F318()+F319();
    break;
  case 237:
    *err=*err|d_237(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F320()+F321()+F322();
    break;
  case 238:
    *err=*err|d_238(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F323();
    break;
  case 239:
    *err=*err|d_239(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F324();
    break;
  case 240:
    *err=*err|d_240(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F325();
    break;
  case 241:
    *err=*err|d_241(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F326();
    break;
  case 242:
    *err=*err|d_242(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F327();
    break;
  case 243:
    *err=*err|d_243(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F328()+F329()+F330();
    break;
  case 244:
    *err=*err|d_244(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F331();
    break;
  case 245:
    *err=*err|d_245(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F332();
    break;
  case 246:
    *err=*err|d_246(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F333();
    break;
  case 247:
    *err=*err|d_247(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F334();
    break;
  case 248:
    *err=*err|d_248(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F335();
    break;
  case 249:
    *err=*err|d_249(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F336();
    break;
  case 250:
    *err=*err|d_250(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F337();
    break;
  case 251:
    *err=*err|d_251(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F338();
    break;
  case 252:
    *err=*err|d_252(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F339();
    break;
  case 253:
    *err=*err|d_253(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F340();
    break;
  case 254:
    *err=*err|d_254(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F341();
    break;
  case 255:
    *err=*err|d_255(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F342()+F343()+F344();
    break;
  case 256:
    *err=*err|d_256(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F345();
    break;
  case 257:
    *err=*err|d_257(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F346();
    break;
  case 258:
    *err=*err|d_258(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F347();
    break;
  case 259:
    *err=*err|d_259(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F348();
    break;
  case 260:
    *err=*err|d_260(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F349();
    break;
  case 261:
    *err=*err|d_261(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F350();
    break;
  case 262:
    *err=*err|d_262(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F351();
    break;
  case 263:
    *err=*err|d_263(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F352();
    break;
  case 264:
    *err=*err|d_264(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F353();
    break;
  case 265:
    *err=*err|d_265(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F354();
    break;
  case 266:
    *err=*err|d_266(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F355();
    break;
  case 267:
    *err=*err|d_267(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F356();
    break;
  case 268:
    *err=*err|d_268(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F357();
    break;
  case 269:
    *err=*err|d_269(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F358();
    break;
  case 270:
    *err=*err|d_270(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F359();
    break;
  case 271:
    *err=*err|d_271(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F360()+F361()+F362();
    break;
  case 272:
    *err=*err|d_272(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F363();
    break;
  case 273:
    *err=*err|d_273(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F364();
    break;
  case 274:
    *err=*err|d_274(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F365();
    break;
  case 275:
    *err=*err|d_275(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F366();
    break;
  case 276:
    *err=*err|d_276(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F367();
    break;
  case 277:
    *err=*err|d_277(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F368();
    break;
  case 278:
    *err=*err|d_278(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F369()+F370()+F371();
    break;
  case 279:
    *err=*err|d_279(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F372();
    break;
  case 280:
    *err=*err|d_280(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F373()+F374();
    break;
  case 281:
    *err=*err|d_281(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F375();
    break;
  case 282:
    *err=*err|d_282(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F376();
    break;
  case 283:
    *err=*err|d_283(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F377();
    break;
  case 284:
    *err=*err|d_284(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F378();
    break;
  case 285:
    *err=*err|d_285(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F379()+F380()+F381();
    break;
  case 286:
    *err=*err|d_286(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F382();
    break;
  case 287:
    *err=*err|d_287(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F383();
    break;
  case 288:
    *err=*err|d_288(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F384()+F385()+F386();
    break;
  case 289:
    *err=*err|d_289(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F387();
    break;
  case 290:
    *err=*err|d_290(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F388();
    break;
  case 291:
    *err=*err|d_291(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F389();
    break;
  case 292:
    *err=*err|d_292(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F390();
    break;
  case 293:
    *err=*err|d_293(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F391()+F392()+F393();
    break;
  case 294:
    *err=*err|d_294(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F394();
    break;
  case 295:
    *err=*err|d_295(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F395();
    break;
  case 296:
    *err=*err|d_296(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F396()+F397()+F398();
    break;
  case 297:
    *err=*err|d_297(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F399()+F400()+F401();
    break;
  case 298:
    *err=*err|d_298(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F402();
    break;
  case 299:
    *err=*err|d_299(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F403();
    break;
  case 300:
    *err=*err|d_300(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F404();
    break;
  case 301:
    *err=*err|d_301(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F405();
    break;
  case 302:
    *err=*err|d_302(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F406();
    break;
  case 303:
    *err=*err|d_303(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F407()+F408()+F409();
    break;
  case 304:
    *err=*err|d_304(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F410();
    break;
  case 305:
    *err=*err|d_305(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F411();
    break;
  case 306:
    *err=*err|d_306(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F412();
    break;
  case 307:
    *err=*err|d_307(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F413();
    break;
  case 308:
    *err=*err|d_308(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F414();
    break;
  case 309:
    *err=*err|d_309(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F415()+F416()+F417();
    break;
  case 310:
    *err=*err|d_310(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F418();
    break;
  case 311:
    *err=*err|d_311(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F419()+F420()+F421();
    break;
  case 312:
    *err=*err|d_312(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F422();
    break;
  case 313:
    *err=*err|d_313(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F423();
    break;
  case 314:
    *err=*err|d_314(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F424();
    break;
  case 315:
    *err=*err|d_315(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F425();
    break;
  case 316:
    *err=*err|d_316(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F426();
    break;
  case 317:
    *err=*err|d_317(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F427();
    break;
  case 318:
    *err=*err|d_318(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F428();
    break;
  case 319:
    *err=*err|d_319(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F429();
    break;
  case 320:
    *err=*err|d_320(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F430();
    break;
  case 321:
    *err=*err|d_321(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F431();
    break;
  case 322:
    *err=*err|d_322(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F432()+F433()+F434();
    break;
  case 323:
    *err=*err|d_323(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F435();
    break;
  case 324:
    *err=*err|d_324(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F436();
    break;
  case 325:
    *err=*err|d_325(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F437();
    break;
  case 326:
    *err=*err|d_326(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F438();
    break;
  case 327:
    *err=*err|d_327(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F439();
    break;
  case 328:
    *err=*err|d_328(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F440()+F441()+F442();
    break;
  case 329:
    *err=*err|d_329(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F443();
    break;
  case 330:
    *err=*err|d_330(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F444();
    break;
  case 331:
    *err=*err|d_331(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F445();
    break;
  case 332:
    *err=*err|d_332(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F446()+F447()+F448();
    break;
  case 333:
    *err=*err|d_333(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F449()+F450()+F451();
    break;
  case 334:
    *err=*err|d_334(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F452();
    break;
  case 335:
    *err=*err|d_335(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F453();
    break;
  case 336:
    *err=*err|d_336(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F454();
    break;
  case 337:
    *err=*err|d_337(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F455();
    break;
  case 338:
    *err=*err|d_338(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F456();
    break;
  case 339:
    *err=*err|d_339(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F457()+F458()+F459();
    break;
  case 340:
    *err=*err|d_340(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F460();
    break;
  case 341:
    *err=*err|d_341(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F461()+F462();
    break;
  case 342:
    *err=*err|d_342(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F463();
    break;
  case 343:
    *err=*err|d_343(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F464();
    break;
  case 344:
    *err=*err|d_344(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F465();
    break;
  case 345:
    *err=*err|d_345(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F466();
    break;
  case 346:
    *err=*err|d_346(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F467()+F468()+F469();
    break;
  case 347:
    *err=*err|d_347(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F470();
    break;
  case 348:
    *err=*err|d_348(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F471();
    break;
  case 349:
    *err=*err|d_349(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F472();
    break;
  case 350:
    *err=*err|d_350(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F473();
    break;
  case 351:
    *err=*err|d_351(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F474();
    break;
  case 352:
    *err=*err|d_352(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F475();
    break;
  case 353:
    *err=*err|d_353(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F476();
    break;
  case 354:
    *err=*err|d_354(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F477();
    break;
  case 355:
    *err=*err|d_355(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F478();
    break;
  case 356:
    *err=*err|d_356(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F479();
    break;
  case 357:
    *err=*err|d_357(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F480();
    break;
  case 358:
    *err=*err|d_358(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F481();
    break;
  case 359:
    *err=*err|d_359(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F482();
    break;
  case 360:
    *err=*err|d_360(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F483();
    break;
  case 361:
    *err=*err|d_361(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F484();
    break;
  case 362:
    *err=*err|d_362(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F485();
    break;
  case 363:
    *err=*err|d_363(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F486();
    break;
  case 364:
    *err=*err|d_364(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F487();
    break;
  case 365:
    *err=*err|d_365(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F488();
    break;
  case 366:
    *err=*err|d_366(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F489();
    break;
  case 367:
    *err=*err|d_367(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F490()+F491()+F492();
    break;
  case 368:
    *err=*err|d_368(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F493();
    break;
  case 369:
    *err=*err|d_369(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F494();
    break;
  case 370:
    *err=*err|d_370(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F495();
    break;
  case 371:
    *err=*err|d_371(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F496();
    break;
  case 372:
    *err=*err|d_372(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F497();
    break;
  case 373:
    *err=*err|d_373(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F498();
    break;
  case 374:
    *err=*err|d_374(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F499()+F500()+F501();
    break;
  case 375:
    *err=*err|d_375(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F502();
    break;
  case 376:
    *err=*err|d_376(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F503();
    break;
  case 377:
    *err=*err|d_377(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F504();
    break;
  case 378:
    *err=*err|d_378(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F505();
    break;
  case 379:
    *err=*err|d_379(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F506();
    break;
  case 380:
    *err=*err|d_380(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F507();
    break;
  case 381:
    *err=*err|d_381(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F508()+F509()+F510();
    break;
  case 382:
    *err=*err|d_382(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F511();
    break;
  case 383:
    *err=*err|d_383(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F512();
    break;
  case 384:
    *err=*err|d_384(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F513()+F514()+F515();
    break;
  case 385:
    *err=*err|d_385(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F516();
    break;
  case 386:
    *err=*err|d_386(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F517();
    break;
  case 387:
    *err=*err|d_387(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F518();
    break;
  case 388:
    *err=*err|d_388(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F519();
    break;
  case 389:
    *err=*err|d_389(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F520()+F521()+F522();
    break;
  case 390:
    *err=*err|d_390(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F523();
    break;
  case 391:
    *err=*err|d_391(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F524();
    break;
  case 392:
    *err=*err|d_392(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F525()+F526()+F527();
    break;
  case 393:
    *err=*err|d_393(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F528()+F529()+F530();
    break;
  case 394:
    *err=*err|d_394(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F531();
    break;
  case 395:
    *err=*err|d_395(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F532();
    break;
  case 396:
    *err=*err|d_396(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F533();
    break;
  case 397:
    *err=*err|d_397(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F534();
    break;
  case 398:
    *err=*err|d_398(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F535()+F536()+F537();
    break;
  case 399:
    *err=*err|d_399(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F538();
    break;
  case 400:
    *err=*err|d_400(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F539()+F540();
    break;
  case 401:
    *err=*err|d_401(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F541();
    break;
  case 402:
    *err=*err|d_402(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F542();
    break;
  case 403:
    *err=*err|d_403(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F543();
    break;
  case 404:
    *err=*err|d_404(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F544();
    break;
  case 405:
    *err=*err|d_405(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F545();
    break;
  case 406:
    *err=*err|d_406(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F546()+F547()+F548();
    break;
  case 407:
    *err=*err|d_407(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F549();
    break;
  case 408:
    *err=*err|d_408(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F550();
    break;
  case 409:
    *err=*err|d_409(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F551();
    break;
  case 410:
    *err=*err|d_410(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F552();
    break;
  case 411:
    *err=*err|d_411(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F553();
    break;
  case 412:
    *err=*err|d_412(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F554()+F555()+F556();
    break;
  case 413:
    *err=*err|d_413(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F557();
    break;
  case 414:
    *err=*err|d_414(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F558();
    break;
  case 415:
    *err=*err|d_415(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F559()+F560()+F561();
    break;
  case 416:
    *err=*err|d_416(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F562();
    break;
  case 417:
    *err=*err|d_417(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F563();
    break;
  case 418:
    *err=*err|d_418(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F564();
    break;
  case 419:
    *err=*err|d_419(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F565();
    break;
  case 420:
    *err=*err|d_420(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F566();
    break;
  case 421:
    *err=*err|d_421(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F567();
    break;
  case 422:
    *err=*err|d_422(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F568()+F569()+F570();
    break;
  case 423:
    *err=*err|d_423(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F571();
    break;
  case 424:
    *err=*err|d_424(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F572();
    break;
  case 425:
    *err=*err|d_425(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F573();
    break;
  case 426:
    *err=*err|d_426(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F574();
    break;
  case 427:
    *err=*err|d_427(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F575();
    break;
  case 428:
    *err=*err|d_428(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F576();
    break;
  case 429:
    *err=*err|d_429(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F577();
    break;
  case 430:
    *err=*err|d_430(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F578();
    break;
  case 431:
    *err=*err|d_431(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F579();
    break;
  case 432:
    *err=*err|d_432(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F580();
    break;
  case 433:
    *err=*err|d_433(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F581();
    break;
  case 434:
    *err=*err|d_434(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F582();
    break;
  case 435:
    *err=*err|d_435(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F583();
    break;
  case 436:
    *err=*err|d_436(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F584();
    break;
  case 437:
    *err=*err|d_437(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F585()+F586()+F587();
    break;
  case 438:
    *err=*err|d_438(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F588();
    break;
  case 439:
    *err=*err|d_439(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F589();
    break;
  case 440:
    *err=*err|d_440(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F590();
    break;
  case 441:
    *err=*err|d_441(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F591();
    break;
  case 442:
    *err=*err|d_442(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F592();
    break;
  case 443:
    *err=*err|d_443(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F593();
    break;
  case 444:
    *err=*err|d_444(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F594();
    break;
  case 445:
    *err=*err|d_445(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F595();
    break;
  case 446:
    *err=*err|d_446(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F596();
    break;
  case 447:
    *err=*err|d_447(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F597();
    break;
  case 448:
    *err=*err|d_448(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F598()+F599()+F600();
    break;
  case 449:
    *err=*err|d_449(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F601()+F602();
    break;
  case 450:
    *err=*err|d_450(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F603()+F604()+F605();
    break;
  case 451:
    *err=*err|d_451(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F606();
    break;
  case 452:
    *err=*err|d_452(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F607();
    break;
  case 453:
    *err=*err|d_453(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F608();
    break;
  case 454:
    *err=*err|d_454(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F609();
    break;
  case 455:
    *err=*err|d_455(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F610()+F611()+F612();
    break;
  case 456:
    *err=*err|d_456(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F613()+F614()+F615();
    break;
  case 457:
    *err=*err|d_457(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F616();
    break;
  case 458:
    *err=*err|d_458(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F617();
    break;
  case 459:
    *err=*err|d_459(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F618()+F619()+F620();
    break;
  case 460:
    *err=*err|d_460(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F621();
    break;
  case 461:
    *err=*err|d_461(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F622();
    break;
  case 462:
    *err=*err|d_462(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F623();
    break;
  case 463:
    *err=*err|d_463(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F624();
    break;
  case 464:
    *err=*err|d_464(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F625();
    break;
  case 465:
    *err=*err|d_465(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F626();
    break;
  case 466:
    *err=*err|d_466(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F627();
    break;
  case 467:
    *err=*err|d_467(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F628();
    break;
  case 468:
    *err=*err|d_468(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F629();
    break;
  case 469:
    *err=*err|d_469(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F630();
    break;
  case 470:
    *err=*err|d_470(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F631()+F632()+F633();
    break;
  case 471:
    *err=*err|d_471(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F634();
    break;
  case 472:
    *err=*err|d_472(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F635();
    break;
  case 473:
    *err=*err|d_473(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F636();
    break;
  case 474:
    *err=*err|d_474(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F637();
    break;
  case 475:
    *err=*err|d_475(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F638();
    break;
  case 476:
    *err=*err|d_476(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F639();
    break;
  case 477:
    *err=*err|d_477(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F640();
    break;
  case 478:
    *err=*err|d_478(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F641();
    break;
  case 479:
    *err=*err|d_479(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F642();
    break;
  case 480:
    *err=*err|d_480(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F643();
    break;
  case 481:
    *err=*err|d_481(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F644();
    break;
  case 482:
    *err=*err|d_482(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F645();
    break;
  case 483:
    *err=*err|d_483(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F646();
    break;
  case 484:
    *err=*err|d_484(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F647();
    break;
  case 485:
    *err=*err|d_485(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F648()+F649()+F650();
    break;
  case 486:
    *err=*err|d_486(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F651();
    break;
  case 487:
    *err=*err|d_487(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F652();
    break;
  case 488:
    *err=*err|d_488(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F653();
    break;
  case 489:
    *err=*err|d_489(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F654();
    break;
  case 490:
    *err=*err|d_490(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F655();
    break;
  case 491:
    *err=*err|d_491(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F656();
    break;
  case 492:
    *err=*err|d_492(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F657()+F658()+F659();
    break;
  case 493:
    *err=*err|d_493(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F660()+F661()+F662();
    break;
  case 494:
    *err=*err|d_494(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F663();
    break;
  case 495:
    *err=*err|d_495(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F664();
    break;
  case 496:
    *err=*err|d_496(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F665();
    break;
  case 497:
    *err=*err|d_497(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F666();
    break;
  case 498:
    *err=*err|d_498(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F667()+F668()+F669();
    break;
  case 499:
    *err=*err|d_499(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F670()+F671()+F672();
    break;
  case 500:
    *err=*err|d_500(momenta);
    sprod_(momenta);
    ans0=0;
    ans1=0+F673()+F674();
    break;
}
  if(!strfun_calc)
  { strfun_calc=1;
    q=scale_();
    if(ans0) xstr0=strfun_(0,xbjo[0],xbjo[1],q);
    if(ans1) xstr1=strfun_(1,xbjo[0],xbjo[1],q);
  }
  ans=ans0+ans1;
  if(!(*err) && 10000*Fmax*computer_eps>(ans>0 ? ans : -ans))*err=1;
  return ans0*xstr0+ans1*xstr1;
}
#include"sqme0.c"
