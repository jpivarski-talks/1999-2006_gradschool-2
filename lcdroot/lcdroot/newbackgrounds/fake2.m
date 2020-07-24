<< Graphics`Graphics`;
<< Graphics`MultipleListPlot`;

(* << Statistics`ContinuousDistributions` *)
(* rands = Table[Random[NormalDistribution[0,1]], {35}, {15}]; *)
rands =
{{-0.47855183840496246, 0.06546681385594097, 0.1458221716313335, 0.8303667365349716, 0.4807983035527738, 0.613077472619825, 
  0.6492505322478611, 0.1557417353021459, -0.5164047425748226, -1.712156561744614, 0.17687935722209347, 0.815864460776203, 
  0.39733731199751754, 0.7171346341734129, 0.5127790176286255}, {0.15958462666926754, 1.5969724931093598, -1.0248861366688382, 
  0.1953234217098768, -0.10921968428046963, 0.6811900405521939, 0.33958877676930155, 0.4802338249883066, 0.022448296716902395, 
  0.36475344339754273, 0.6471249125303881, 0.8031938166669903, 1.3369955758390062, 0.0366089673944282, -0.9390412414736102}, 
 {1.6153155217495032, 0.23484028316292369, 1.2385056239816057, -0.427507945384594, 0.8002142882151909, -0.504757896222111, 
  0.6517628302676327, -0.035846477801367106, -0.2467088528852006, -0.4439989027254613, -1.0839112567936735, 1.5710573094009144, 
  -0.8803629776284608, 0.25293260152538755, -0.4063526114697184}, {-0.5223757835149044, -0.04958941140012443, 0.36946814612768347, 
  0.7852828924624301, 2.0320531948062217, 1.8502762502332228, -1.7815242995300709, -1.0008078800020876, -0.4232147620335985, 
  1.120655454711022, -0.660449615533055, 0.10791792636416682, -0.21876580594239786, -1.3423725012479162, -1.4837130101000497}, 
 {-0.22039847117162648, -1.5544450025939753, -0.3727759338523542, 2.3982274468923896, 1.3461144219576562, -1.9817713687449325, 
  2.5761433377492287, 0.0826605435832612, 0.542433340932442, -1.2089124318395987, -1.184011697454046, 1.9516213877723037, 
  -0.5946657233717849, -0.4106308912393333, 0.44060058542287}, {-0.39933782706178783, -0.0708233111421134, 0.4467117793912075, 
  0.15850277444961114, -0.405848268083736, -1.1332564129794294, 0.9936051578210747, 1.5241840989544946, 1.2150180892417917, 
  -1.1422588820159676, -0.5534838998467436, 0.15351812701160994, -0.44883240057888985, 1.3510553332178044, -0.805837785500396}, 
 {-0.7904110248448419, 0.28091357586479704, -0.4011481168298849, -0.30380504703050965, 0.16573495620027645, -1.401787160487024, 
  0.6888445449668285, 0.21418883710560263, -0.14772144506419954, -0.9979558266848635, 0.7609168535325539, 0.46761054971196214, 
  0.6789698748730967, -0.07612903965110435, 1.8540351979559417}, {-1.1020939746705247, -0.34837522644606445, 1.8465594816890112, 
  0.3778167530165225, 1.3636072669481931, 1.3523803433695396, -0.8287726554427387, -0.06512646226744648, -0.3813324553348779, 
  0.9285466835090224, 0.25034127107978155, 0.76632940338225, -1.1658364376335053, -1.9396722594046722, -1.4917957903494499}, 
 {-1.3167640569080976, -1.9891336456238995, -2.0159940592571135, 1.1479360889366717, 0.37268262336539787, -1.1939654524818335, 
  0.42428143791892603, -0.8607778328722151, 1.5023515152095877, 1.5207060890592334, -1.5850134637734348, -0.33095245321069366, 
  0.4168642311122391, 0.7120149241719076, -0.6756991731283486}, {1.6133436635324252, -0.47356649526880734, -0.7009300870999733, 
  0.5091593419625804, 1.452485721175901, 0.7885741525976749, 0.24010402840105902, -1.9914787500173439, 1.0757771475365243, 
  -1.4550798462266945, 0.6910052601012993, 1.1390117106506705, 1.1242105883363458, 0.11612030547114269, -0.7349767754374231}, 
 {-0.9485035795864366, -1.149722477221064, -2.1773848892679277, 0.11170950958409825, 1.6770658730075612, -0.2440735845604857, 
  0.02121077222584808, -0.82615546526951, 0.710270449373634, -0.18712132916887184, -0.45043182840302076, -0.09547434724437301, 
  -0.566093746678339, -0.06258459995633085, 0.28006055081510867}, {2.794502556134249, -1.224836419174168, -0.7445163644583082, 
  1.2229643315468202, -1.7719365630272141, 0.8812706417594539, 1.003661668636909, -1.375406575375645, -0.6759967458172894, 
  0.7277176901148695, 1.1626598981833556, -0.0604336116069984, 1.3118797709471308, -0.9928531657524022, -1.696977452689929}, 
 {-0.14786798573777615, 2.165473472612431, -0.1971942629628998, 0.9016316810871646, -0.9631849364073598, -0.14555463451008477, 
  -0.5195231284612358, -0.7989356287016239, 1.7689286288743364, -0.737878367831269, -0.805366452415503, 1.4433500240506623, 
  -0.11908172958072913, 1.45437038253848, 2.1503587116234546}, {1.0098197229713566, -0.6310397888699153, -0.8398990868673789, 
  -0.6779320589602289, 0.43805249998986856, 0.1875986039890846, -0.8990365899426491, -0.3861854305793058, -0.7584206699458895, 
  0.9975844342125324, 0.03223276206352732, 1.1538902880991573, 0.5228248563247093, -0.35654833715416784, -0.5593935828851527}, 
 {0.5333479122066658, -0.44244204465149717, 0.2496637233858234, 0.6252892563399329, 0.34080301766213017, 1.0452421052306953, 
  0.7357785090798141, -1.1288470180645003, 0.23015631054882932, -0.5523536180491255, 0.386857005770904, 1.5132010428170692, 
  0.02903090706401036, -0.5859791008690614, 1.9856070755040305}, {0.5511768129741955, -0.26725528942417653, -0.168321523693496, 
  -2.0907861760198134, -1.0386945096868838, -0.6074050810374862, 0.4564332224397958, -0.9757388881446283, -0.744294172803251, 
  -0.36992012965968596, 1.6520280845570698, 0.2817998342028687, 1.0143961489952191, 1.3836195152001083, -0.08353033439091596}, 
 {-1.725198089141211, 0.8029500427619132, 0.20311992241276322, 0.5589074872082339, -0.19818400500048577, -0.40123572320347867, 
  1.061154255742478, -0.7765581249010443, -0.0031141933712390394, -1.8193858325982495, 0.3826729032140131, 1.2398366730346766, 
  -0.754462340559853, 0.8310946180521396, -0.8502989557755284}, {1.7395030362068493, -0.2760469880543396, -1.3899938863368786, 
  -0.14448297015444722, 0.5478794659900458, -0.0843404626724059, -0.8098522932574113, 0.15494746180710475, 0.3555215555561029, 
  -0.392867980793468, 0.710322649120902, 1.1004008759450243, 0.6687163302171917, -0.7001804412575197, -0.09980343631446523}, 
 {0.03816032758247691, 0.6786728233136162, -0.38920028325926925, -1.387031557439589, 0.9882541552063155, -0.9956060172933574, 
  -1.1006516727038458, 0.013394233604060713, -1.1908019948193211, 0.3314662331511382, 1.0416756621032075, -0.5996666644607566, 
  0.19237358445687439, -0.36995022893273305, 2.0308972675284114}, {0.825940709360582, 0.009337622493437855, -1.1893506574739636, 
  0.41689119188049895, -0.07116970579581806, 0.4030679088526441, 0.5118380311971918, 1.3076730079537402, 0.8053525509455248, 
  -0.6937560247361716, -0.9590716325239874, 0.47693780029828764, -0.45466477097304153, 0.6219199252140424, 1.1403311110934913}, 
 {0.3434428679955932, -0.8678441146782401, 2.5443476534820135, -1.1038634638528917, 0.3796328201299779, -0.09632249003796747, 
  -1.1473231864020914, 0.6768390049496498, -1.2199033796148047, -0.5835842452678279, -1.2566813699233177, -0.4365101923737845, 
  0.11757163751620545, 0.7747156214610714, 0.17003198756405494}, {-0.6755203732305711, -0.5592671917273585, 1.136758405482406, 
  0.6588746750730065, 0.7753753403863939, -2.621694003471824, -0.939294434111319, 0.784110373702196, -2.4190663196515216, 
  0.7644703828275957, -1.4255349980168515, -0.753420617489153, 1.0409509010319307, 0.1414370199075775, -0.14604597245687942}, 
 {-0.4202659142480171, -0.349314598985565, 0.5076468572542269, -2.3541861208494157, 1.7316735223628186, 0.6116508069402905, 
  0.0840483266033701, -0.05582770597061469, -1.4847069307471865, -1.0100024761617405, -0.353641853308795, -0.16239185924876814, 
  0.8080740096003866, 1.1956899331869915, 0.7784151275355299}, {-0.9443105202762171, 1.345296295271702, 0.5774009505231094, 
  0.5840610212925909, -0.5633113634982369, -0.6737710928202438, 0.9570446111788754, 0.7772924542652733, -0.8011895772743203, 
  0.8062613147375046, -1.6459212214495273, -0.13476126756076404, 0.32572883804617264, -0.7108215341384309, 1.7311032508460333}, 
 {-1.7755778306852734, -1.1737733384682179, -0.046907701809610666, -0.28470377218571497, -0.007845090836633536, 0.755335716413042, 
  1.9240212588906531, -1.4774693867066477, 0.6241393607665512, -0.7908051160910116, -0.834270050412869, -0.9765227440658133, 
  0.9868430698827169, 0.06306036858893499, -0.8510822207890034}, {0.523914980462045, -0.36153636023287083, 1.0725402112321523, 
  -0.20057517637428252, -0.93425214723412, -0.9495628344690722, 0.9656637865438339, 0.28179842519729204, -1.4593776620987282, 
  0.7787119386863969, 0.4702469762839807, -2.01829714645847, -0.03757236400173227, 1.4774577130884685, 1.6101651930297303}, 
 {0.27751276287209203, -0.5659224250955128, -0.16057513997526776, -1.5221832065358587, 0.06853278913417006, 3.050485418370919, 
  1.2555913984637948, 0.3338579716853361, -1.4441523903399582, -1.4837329878469125, -0.23077506162018271, -1.3513094180217176, 
  -0.11021983879598171, 1.15175837601374, -0.5436497262026498}, {-1.9151729963447606, 0.5121466924725747, -1.904001499972304, 
  0.5586057789430623, -0.7987425957802997, -1.099633103261702, 1.6770614207621222, 1.0643976781416735, -0.2091114456350338, 
  -0.03322334463531241, 0.08797431417680471, 0.9128324779077898, -0.30420782596999746, -1.822115313223946, 0.803827735320252}, 
 {-1.4902990085929377, 0.3346717213592614, 0.6771945082119039, 0.8437884739790631, 1.684436554332858, -0.7317056458422407, 
  -0.6648171663216151, -0.9713877673728024, 1.3279757005633894, -0.33406543406848754, -0.036898767658435756, -0.7834783854799103, 
  0.08427561497973428, -0.198687155642124, 0.11004778973485675}, {-0.25885428591358833, 0.44608971264236447, 0.5831096238247164, 
  0.6575859934879136, 0.34718597230245535, -0.4184115779097988, 0.5397617123921362, 1.4785194613245962, -0.11343798137923616, 
  -0.18384995674893023, 0.41697695277844504, -0.9454901852265414, -0.8003057721681497, -0.29687656070047685, 0.056500741219054344}, 
 {-1.2850361440945826, -1.2520704139601333, 1.0467659168892995, -0.08155365850670053, 0.5035010546147876, -2.9810343113486533, 
  1.1085347887465646, -1.980354874744869, -0.782427686015614, 0.8465173465540006, -0.027542597603115202, 0.45307314941061166, 
  -0.24242398530007972, -1.235871992281558, 1.6044058454269654}, {0.738699704518765, 1.3417554908362077, -1.008384169081009, 
  1.3547515572296494, 0.9838172740396256, -0.08573769925051847, 0.712158268225423, 3.010597964811999, 1.2932987647741903, 
  -0.13628336011306721, 0.11372283859042394, -0.6756379885449748, -1.3542432053783398, -0.9163311171508965, 0.8975044989993184}, 
 {-2.3409758988164904, 1.3772398569792417, 0.4889214408834377, 0.8257255358091574, 0.5768872127886929, -0.4099322267502102, 
  0.8236772266981977, 0.4963337568595179, -0.32790042038419354, -0.23171507814313416, 0.38291193645305394, -0.05810098589225925, 
  -0.1745321763656268, -0.3746683178714189, -1.661158698454912}, {-1.5786585781139508, -0.32640469289327545, 0.0918412132981731, 
  -1.5583079661528547, 0.25247119579486826, 1.373190444209203, -1.7018534248335924, 0.011580710833016013, -0.5848490065529685, 
  0.1711826415194368, 1.3779753149295346, -0.7674124009484334, -2.174657701449289, 0.27005883752069465, -0.22290384322328546}, 
 {-0.2661254265583553, 0.9493203468375213, 0.25092090512467713, -0.8085130790112635, 0.8402129325353257, 2.1858233327946253, 
  0.8240368307320377, 0.7268377419873208, -0.2594843386972589, -0.8573859296355066, -1.1842482969357155, 0.9124277208992917, 
  -0.8647717896839399, 0.5173421475359573, 1.259131570027526}};
vals = {{38, 49, 41, 38, 31, 38, 42, 30, 35, 19, 7, 0, 0, 0, 0},
	{44, 43, 45, 41, 51, 37, 26, 32, 37, 20, 14, 0, 0, 0, 0},
	{51, 55, 46, 49, 53, 40, 32, 39, 27, 20, 7, 0, 0, 0, 0},
	{45, 47, 48, 49, 49, 30, 45, 34, 25, 13, 8, 0, 0, 0, 0},
	{45, 38, 57, 54, 46, 58, 38, 33, 29, 20, 8, 0, 0, 0, 0},
	{65, 48, 42, 46, 49, 44, 44, 36, 27, 16, 11, 0, 0, 0, 0},
	{58, 47, 50, 53, 48, 37, 47, 37, 27, 18, 5, 0, 0, 0, 0},
	{49, 47, 47, 57, 45, 36, 47, 44, 29, 21, 6, 0, 0, 0, 0},
	{44, 56, 51, 38, 45, 46, 37, 32, 21, 14, 7, 0, 0, 0, 0},
	{50, 52, 49, 48, 47, 42, 40, 37, 40, 16, 5, 0, 0, 0, 0},
	{47, 36, 45, 52, 52, 33, 39, 38, 29, 18, 2, 0, 0, 0, 0},
	{46, 62, 59, 46, 53, 39, 43, 34, 26, 14, 0, 0, 0, 0, 0},
	{43, 45, 45, 41, 39, 36, 28, 30, 18, 7, 0, 0, 0, 0, 0},
	{36, 44, 38, 39, 42, 30, 20, 20, 15, 4, 0, 0, 0, 0, 0},
	{47, 42, 47, 33, 34, 30, 30, 22, 8, 0, 0, 0, 0, 0, 0},
	{38, 35, 18, 23, 31, 20, 12, 19, 2, 0, 0, 0, 0, 0, 0},
	{32, 32, 30, 25, 34, 28, 21, 12, 0, 0, 0, 0, 0, 0, 0},
	{37, 32, 22, 31, 24, 16, 10, 0, 0, 0, 0, 0, 0, 0, 0},
	{31, 34, 23, 30, 19, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{33, 22, 20, 20, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{13, 14, 12, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{10, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
backgrounds =
    {{0.125, 0.817829, 15.8098, 0.25, 0.25, 0.870059, 1.06783, 1.92656, 7.74009, 0.596415, 0.991036, 0.471415, 0.471415, 1.21647, 1.59977},
     {0.5, 0.846415, 0.346415, 0.596415, 0.471415, 0.75, 1.38566, 0.173207, 0.942829, 0.471415, 0.298207, 0.692829, 1.11604, 0.773645, 1.38566},
     {0.42723, 0.25, 0, 0, 0.625, 0.471415, 1.16424, 0.846415, 0.298207, 0.942829, 1.41424, 2.59081, 0.721415, 1.38566, 1.03924},
     {16.7561, 0, 0.125, 16.2561, 1.12006, 0.846415, 0.721415, 1.28924, 1.03924, 16.8851, 0.942829, 0.721415, 0.942829, 0.946852, 1.98207},
     {9.49384, 0.125, 0.821852, 0.846415, 0.125, 0, 0.375, 0.596415, 0.596415, 0.846415, 0.817829, 0.471415, 0.5, 0.471415, 1.63566},
     {0.125, 0.25, 0.125, 22.5862, 0.346415, 0.346415, 0.721415, 0.125, 0.596415, 0.692829, 1.74104, 1.89798, 0.519622, 1.33745, 26.4937},
     {16.7561, 0.25, 1.41424, 225.792, 0.773645, 12.0934, 16.8218, 0.5, 0.596415, 0.346415, 0.346415, 0.125, 0.817829, 1.19283, 26.0264},
     {0.125, 0.773645, 0.846415, 0, 0.971415, 0.548207, 0.471415, 0.721415, 0, 1.37006, 1.30156, 1.21647, 1.16424, 1.19283, 0.471415},
     {0.125, 0, 0.942829, 0.644622, 0.846415, 0.173207, 0.298207, 0.25, 0.475437, 0.644622, 0.346415, 1.16424, 42.5651, 0.721415, 1.68789},
     {1.60379, 0.5, 0.25, 0.866036, 0.25, 0.25, 0.721415, 0.971415, 1.28924, 0.596415, 0.519622, 0.25, 17.1047, 1.07588, 1.51066},
     {0.995059, 0.30223, 0.721415, 0.125, 0, 0, 0.471415, 1.16424, 0.346415, 0, 1.77298, 0.942829, 0.721415, 2.03028, 18.6634},
     {0, 0.625, 0.30223, 0.471415, 0.60446, 0.125, 0.471415, 0.17723, 0.942829, 0.648645, 0.596415, 0.125, 0.519622, 1.19283, 0.596415},
     {0, 0.17723, 0, 16.1316, 0.30223, 0.30223, 0.17723, 0.5, 0.72946, 0.596415, 0.600438, 1.17772, 0.471415, 1.24506, 0.629511},
     {1.89798, 0, 0.523645, 0.125, 0, 0.42723, 0.125, 0.471415, 0.173207, 0.773645, 0.721415, 0.769622, 0.25, 0.375, 16.7915},
     {0.596415, 0, 0.125, 0.346415, 0.35446, 0.25, 0.346415, 0.125, 0.721415, 0.625, 0.423207, 0.817829, 0.55223, 0.991036, 1.28924},
     {0.25, 0.346415, 0.125, 0, 0, 0.25, 0.25, 0, 22.2634, 0.125, 28.7368, 0.548207, 0.596415, 18.1367, 25.9039},
     {0.60446, 0.17723, 15.8098, 0.950875, 0.523645, 0.648645, 0.846415, 0.648645, 0.971415, 0.25, 0.675274, 0.125, 1.21647, 16.7915, 1.06783},
     {0.30223, 26.2263, 0, 0.30223, 0, 16.8505, 0.648645, 0.17723, 0.346415, 0.17723, 0.773645, 0.625, 1.02364, 1.06783, 2.24439},
     {21.3597, 0.17723, 0.346415, 0.25, 0, 0, 0.346415, 26.6311, 0.346415, 0.870059, 0.692829, 1.09641, 0.773645, 1.54327, 0},
     {0, 0.125, 0, 0.60446, 0.375, 0, 0.375, 0, 0.471415, 0.471415, 0.173207, 0.673207, 1.777, 0.995059, 88.355},
     {0, 0, 0.125, 0.125, 0, 0.125, 0.692829, 0.25, 0, 0.25, 0.471415, 0.25, 27.258, 1.41827, 0.42723},
     {0, 0.346415, 0, 0.30223, 0.346415, 0.817829, 0.346415, 0.375, 0.60446, 0.5, 25.9605, 1.88287, 0.644622, 23.0413, 0.870059},
     {0.125, 0, 0.17723, 0.675274, 25.4103, 0.125, 16.1137, 0.298207, 0, 0.25, 0.346415, 0.30223, 0.25, 0.173207, 0.898645},
     {0.25, 0.298207, 0, 0.25, 0, 0.42723, 0, 0, 0.596415, 0.648645, 0.125, 0.25, 0.17723, 0.25, 0.648645},
     {0, 0.30223, 0.471415, 1.42656, 0.346415, 1.77298, 0.30223, 0, 0.995059, 0.125, 26.4096, 16.1798, 0.375, 0.600438, 0.769622},
     {0, 0, 0, 0.125, 0.25, 0, 0.346415, 0.30223, 0.30223, 0, 0.721415, 0, 0.692829, 0.173207, 0.471415},
     {0.125, 0, 0, 0.30223, 0, 0.47946, 0.47946, 0.346415, 0.42723, 0.125, 0.656691, 0.25, 0, 0.817829, 3.60155},
     {0, 0.30223, 0.375, 0, 0, 0, 0, 0, 16.8218, 0, 0, 0, 16.3201, 0.995059, 0.825875},
     {0.173207, 0, 0, 0, 0.30223, 0, 0.692829, 0, 0.125, 0, 0.471415, 17.6099, 0.471415, 0.25, 0.42723},
     {0, 0, 0, 0, 0, 0, 0.17723, 0.173207, 0.30223, 17.8425, 0.42723, 0.471415, 0, 0, 1.70523},
     {0, 0.346415, 0, 0.17723, 0.30223, 0.817829, 0, 0, 16.1137, 0.471415, 0.523645, 0.25, 15.8471, 0, 0.346415},
     {0, 0, 0.125, 0, 0, 0, 0.42723, 16.4601, 0, 0, 0.25, 0.17723, 17.5884, 16.9164, 0.596415},
     {0, 0, 0, 0.125, 0.30223, 0.30223, 0.125, 0.346415, 0, 0.125, 0, 0.817829, 0.5, 0, 0.173207},
     {0.125, 0, 0.125, 0, 0, 0.17723, 0.125, 0.30223, 0.125, 0.35446, 0, 0, 0.47946, 42.74, 25.6759},
     {0, 0.471415, 0, 0, 0.125, 0, 0, 0.17723, 0, 0.471415, 0.17723, 0.125, 13.9457, 0.47946, 0}};
err2s = vals + backgrounds;
data = Table[{vals[[j,i]] + rands[[j,i]]*Sqrt[backgrounds[[j,i]]],
	      Sqrt[err2s[[j,i]]]}, {i, 1, 15}, {j, 1, 35}];
datasum = Sum[data[[i,j,1]], {i, 1, 15}, {j, 1, 35}];
dataerr = Sqrt[Sum[data[[i,j,2]]^2, {i, 1, 15}, {j, 1, 35}]];

isr[x_] = 0;
isr[1] = 8746;
isr[2] = 1855;
isr[3] = 1442;
isr[4] = 1179;
isr[5] = 1001;
isr[6] = 907;
isr[7] = 831;
isr[8] = 729;
isr[9] = 650;
isr[10] = 697;
isr[11] = 661;
isr[12] = 628;
isr[13] = 572;
isr[14] = 535;
isr[15] = 544;
isr[16] = 510;
isr[17] = 515;
isr[18] = 465;
isr[19] = 460;
isr[20] = 431;
isr[21] = 433;
isr[22] = 387;
isr[23] = 394;
isr[24] = 364;
isr[25] = 368;
isr[26] = 358;
isr[27] = 372;
isr[28] = 358;
isr[29] = 331;
isr[30] = 299;
isr[31] = 257;
isr[32] = 319;
isr[33] = 282;
isr[34] = 256;
isr[35] = 300;
isr[36] = 240;
isr[37] = 277;
isr[38] = 252;
isr[39] = 249;
isr[40] = 243;
isr[41] = 222;
isr[42] = 245;
isr[43] = 220;
isr[44] = 218;
isr[45] = 215;
isr[46] = 186;
isr[47] = 186;
isr[48] = 156;
isr[49] = 185;
isr[50] = 177;
isr[51] = 162;
isr[52] = 183;
isr[53] = 163;
isr[54] = 163;
isr[55] = 141;
isr[56] = 170;
isr[57] = 172;
isr[58] = 149;
isr[59] = 142;
isr[60] = 141;
isr[61] = 135;
isr[62] = 136;
isr[63] = 127;
isr[64] = 125;
isr[65] = 128;
isr[66] = 141;
isr[67] = 116;
isr[68] = 121;
isr[69] = 101;
isr[70] = 124;
isr[71] = 97;
isr[72] = 102;
isr[73] = 112;
isr[74] = 111;
isr[75] = 104;
isr[76] = 77;
isr[77] = 98;
isr[78] = 87;
isr[79] = 103;
isr[80] = 81;
isr[81] = 108;
isr[82] = 91;
isr[83] = 94;
isr[84] = 91;
isr[85] = 66;
isr[86] = 68;
isr[87] = 61;
isr[88] = 69;
isr[89] = 63;
isr[90] = 68;
isr[91] = 64;
isr[92] = 62;
isr[93] = 68;
isr[94] = 55;
isr[95] = 61;
isr[96] = 51;
isr[97] = 65;
isr[98] = 59;
isr[99] = 46;
isr[100] = 38;
isr[101] = 60;
isr[102] = 44;
isr[103] = 52;
isr[104] = 56;
isr[105] = 42;
isr[106] = 37;
isr[107] = 44;
isr[108] = 54;
isr[109] = 37;
isr[110] = 42;
isr[111] = 42;
isr[112] = 28;
isr[113] = 36;
isr[114] = 37;
isr[115] = 44;
isr[116] = 23;
isr[117] = 26;
isr[118] = 28;
isr[119] = 30;
isr[120] = 30;
isr[121] = 25;
isr[122] = 26;
isr[123] = 30;
isr[124] = 23;
isr[125] = 21;
isr[126] = 17;
isr[127] = 15;
isr[128] = 28;
isr[129] = 18;
isr[130] = 24;
isr[131] = 25;
isr[132] = 21;
isr[133] = 18;
isr[134] = 25;
isr[135] = 26;
isr[136] = 17;
isr[137] = 19;
isr[138] = 16;
isr[139] = 17;
isr[140] = 19;
fakeisr =
    Compile[{}, (If[Random[] < 0.196323, 1,
		    (x = Random[Integer, {2, 140}];
		     y = Random[Integer, 930];
		     While[y > isr[x],
			   (x = Random[Integer, {2, 140}];
			    y = Random[Integer, 930];)];
		     x)] - 0.5) *
	    If[Random[Integer, {0, 1}] == 1, 1, -1]
	   ];
andreasuncompiled[zeta_, mc_, mlsp_, mw_] =
 (mw * Sqrt[(mc^2-mlsp^2)^2 - 2*mw^2*(mc^2+mlsp^2) + mw^4] / (mw^2-80.425^2)^2) *
 ((mlsp^4 + mc^4 + mw^2*mc^2 - 2*mw^4 + mlsp^2*(mw^2-2*mc^2)) - 6*zeta*mw^2*mlsp*mc);
andreas =
 Compile[{{zeta, _Real}, {mc, _Real}, {mlsp, _Real}, {mw, _Real}},
	 (mw * Sqrt[(mc^2-mlsp^2)^2 - 2*mw^2*(mc^2+mlsp^2) + mw^4] / (mw^2-80.425^2)^2) *
	 ((mlsp^4 + mc^4 + mw^2*mc^2 - 2*mw^4 + mlsp^2*(mw^2-2*mc^2)) - 6*zeta*mw^2*mlsp*mc)
	 ];
topofandreas[zeta_, mc_, mlsp_] :=
    Max[andreas[zeta, mc, mlsp, #]& /@ Range[0, Floor[mc - mlsp], 1]] * 1.05;
randomandreas =
 Compile[{{zeta, _Real}, {mc, _Real}, {mlsp, _Real}, {top, _Real}},
	 (x = Random[Real, {0., (mc - mlsp)}];
	 y = Random[Real, {0., top}];
	 While[y > andreas[zeta, mc, mlsp, x],
		 (x = Random[Real, {0., (mc - mlsp)}];
		 y = Random[Real, {0., top}])];
	 x)];
randomdirection =
 Compile[{},
	 (costheta = Random[Real, {-1., 1.}];
	 sintheta = If[costheta > 0., 1., -1.] * Sqrt[1. - costheta^2];
	 phi = Random[Real, {0., 2.*Pi}];
	 {sintheta*Cos[phi], sintheta*Sin[phi], costheta}
	 )];
randomtwobody =
 Compile[{{parent, _Real, 1}, {m1, _Real}, {m2, _Real}},
	 (m0 = Sqrt[parent[[1]]^2 - parent[[2]]^2 - parent[[3]]^2 - parent[[4]]^2];
	 pmag = Sqrt[m0^4 - 2*m0^2*m1^2 + m1^4 - 2*m0^2*m2^2 - 2*m1^2*m2^2 + m2^4]/2/m0;
	 p1 = pmag*randomdirection[];
	 p1 = {Sqrt[pmag^2 + m1^2], p1[[1]], p1[[2]], p1[[3]]};
	 bx = parent[[2]]/parent[[1]];
	 by = parent[[3]]/parent[[1]];
	 bz = parent[[4]]/parent[[1]];
	 gam = 1/Sqrt[1 - bx^2 - by^2 - bz^2];
	 g2 = gam^2/(1+gam);
	 boost = {{gam, gam*bx, gam*by, gam*bz},
		 {gam*bx, 1+g2*bx^2, g2*bx*by, g2*bx*bz},
		 {gam*by, g2*bx*by, 1+g2*by^2, g2*by*bz},
		 {gam*bz, g2*bx*bz, g2*by*bz, 1+g2*bz^2}};
	 boost . p1
	 ), {{boost, _Real, 2}, {p1, _Real, 1}, {p2, _Real, 1}}];
fillhisto[m_, e_] := histo[[Floor[(m - 30)/2]+1, Floor[(e - 70)/2]+1]]++;
randomevent =
    Compile[{zeta, chmass, lspmass, top},
	    (failed = False;
	     vphoz = {500 - fakeisr[], 0, 0, 0};
	     ch1p = randomtwobody[vphoz, chmass, chmass];
	     ch1m = vphoz - ch1p;
	     wpmass = randomandreas[zeta, chmass, lspmass, top];
	     mrecon = wpmass;
	     If[mrecon < 30  ||  mrecon > 60, failed = True];
	     If[!failed, (wp = randomtwobody[ch1p, wpmass, lspmass];
			  erecon = wp[[1]];
			  If[erecon < 70  ||  erecon > 140, failed = True])];
	     If[!failed, (j1 = randomtwobody[wp, 0, 0];
			  If[Abs[j1[[4]]]/Sqrt[j1[[2]]^2+j1[[3]]^2+j1[[4]]^2] > 0.95, failed = True])];
	     If[!failed, (
		 j2 = wp - j1;
		 If[Abs[j2[[4]]]/Sqrt[j2[[2]]^2+j2[[3]]^2+j2[[4]]^2] > 0.95, failed = True]
			 )];
(* I am insensitive to any differences this would make, and it takes a long time to compute. *)
(* 	     If[!failed, ( *)
(* 		 wmmass = randomandreas[zeta, chmass, lspmass, top]; *)
(* 		 wm = randomtwobody[ch1m, wmmass, lspmass]; *)
(* 		 ell = randomtwobody[wm, 0, 0]; *)
(* 		 If[Abs[ell[[4]]]/Sqrt[ell[[2]]^2+ell[[3]]^2+ell[[4]]^2] > 0.95, failed = True] *)
(* 			 )]; *)
	     If[!failed, (
		 jsum = j1 + j2;
		 If[Sqrt[jsum[[2]]^2+jsum[[3]]^2] < 25, failed = True]
			 )];
	     If[!failed, fillhisto[mrecon, erecon]];
	     If[!failed, 1, 0]
	    )];
chisquare = 
    Compile[{{zeta, _Real}, {mc, _Real}, {mlsp, _Real}},
	    histo = Table[0, {15}, {35}];
	    thetop = topofandreas[zeta, mc, mlsp];
	    mcsum = Plus @@ Table[randomevent[zeta, mc, mlsp, thetop], {300000}];
	    histn[zeta, mc, mlsp] = datasum/mcsum*histo;
	    Sum[If[data[[i,j,2]] > 0,
		    (data[[i,j,1]] - datasum/mcsum*histo[[i,j]])^2/data[[i,j,2]]^2, 0],
		 {i, 1, 15}, {j, 1, 35}],
	   {{data, _Real, 3}, {histo, _Real, 2}}];
ndof = Sum[If[data[[i,j,2]] > 0, 1, 0], {i, 1, 15}, {j, 1, 35}] - 3;




randomdirectioncor =
    Compile[{{cor, _Real}},
	    (costheta = Random[Real, {-1., 1.}];
	     y = Random[Real, {0., 1+If[cor > 0, cor, 0]}];
	     While[y > 1 + cor*costheta^2,
		   (costheta = Random[Real, {-1., 1.}];
		    y = Random[Real, {0., 1+If[cor > 0, cor, 0]}];)];
	     sintheta = If[costheta > 0., 1., -1.] * Sqrt[1. - costheta^2];
	     phi = Random[Real, {0., 2.*Pi}];
	     {sintheta*Cos[phi], sintheta*Sin[phi], costheta}
	    )];
randomtwobodycor =
 Compile[{{parent, _Real, 1}, {m1, _Real}, {m2, _Real}, {cor, _Real}},
	 (m0 = Sqrt[parent[[1]]^2 - parent[[2]]^2 - parent[[3]]^2 - parent[[4]]^2];
	 pmag = Sqrt[m0^4 - 2*m0^2*m1^2 + m1^4 - 2*m0^2*m2^2 - 2*m1^2*m2^2 + m2^4]/2/m0;
	 p1 = pmag*randomdirectioncor[cor];
	 p1 = {Sqrt[pmag^2 + m1^2], p1[[1]], p1[[2]], p1[[3]]};
	 bx = parent[[2]]/parent[[1]];
	 by = parent[[3]]/parent[[1]];
	 bz = parent[[4]]/parent[[1]];
	 gam = 1/Sqrt[1 - bx^2 - by^2 - bz^2];
	 g2 = gam^2/(1+gam);
	 boost = {{gam, gam*bx, gam*by, gam*bz},
		 {gam*bx, 1+g2*bx^2, g2*bx*by, g2*bx*bz},
		 {gam*by, g2*bx*by, 1+g2*by^2, g2*by*bz},
		 {gam*bz, g2*bx*bz, g2*by*bz, 1+g2*bz^2}};
	 boost . p1
	 ), {{boost, _Real, 2}, {p1, _Real, 1}, {p2, _Real, 1}}];

lotsaDubya = {};
littleevent =
    Compile[{zeta, chmass, lspmass, top},
	    (failed = False;
	     theisr = fakeisr[];
	     vphoz = {500 - Abs[theisr], 0, 0, theisr};
	     ch1p = randomtwobodycor[vphoz, chmass, chmass, 0.38]; (* +- 0.01 *)
	     ch1m = vphoz - ch1p;
	     wpmass = randomandreas[zeta, chmass, lspmass, top];
	     wp = randomtwobody[ch1p, wpmass, lspmass];
	     lotsaDubya = Append[lotsaDubya, wp];
	    ), {{lotsaDubya, _Real, 2}}];
thetop = topofandreas[1., 159.417, 107.697];
Table[littleevent[1., 159.417, 107.697, thetop], {100000}];

Out[150]= $Aborted

Print /@ (#[[1]]& /@ lotsaDubya);

Print /@ (#[[2]]& /@ lotsaDubya);

Print /@ (#[[3]]& /@ lotsaDubya);

Print /@ (#[[4]]& /@ lotsaDubya);

Print /@ (Sqrt[#[[1]]^2-#[[2]]^2-#[[3]]^2-#[[4]]^2]& /@ lotsaDubya);

Print /@ (Sqrt[#[[2]]^2+#[[3]]^2]& /@ lotsaDubya);






thetop = topofandreas[1., 159.417, 107.697];
Print /@ Table[randomandreas[1., 159.417, 107.697, thetop], {10000}];






(* b1 = -chimpx/chime; *)
(* b2 = -chimpy/chime; *)
(* b3 = -chimpz/chime; *)
(* gam = 1/Sqrt[1-b1^2-b2^2-b3^2]; *)
(* bgam = gam^2/(1+gam); *)
(* boost = {{gam,    gam*b1,      gam*b2,      gam*b3     }, *)
(* 	 {gam*b1, 1+bgam*b1^2, bgam*b1*b2,  bgam*b1*b3 }, *)
(* 	 {gam*b2, bgam*b1*b2,  1+bgam*b2^2, bgam*b2*b3 }, *)
(* 	 {gam*b3, bgam*b1*b3,  bgam*b2*b3,  1+bgam*b3^2}}; *)
(* (boost . {j1e, j1px, j1py, j1pz})[[1]] // Simplify // InputForm *)






Print /@ Table[(#[[4]]/Sqrt[#[[2]]^2 + #[[3]]^2 + #[[4]]^2])&[randomchitwobody[500, 150]], {100000}];





(* histo = Table[0, {15}, {35}]; *)
(* thetop = topofandreas[1, 159.417, 107.697]; *)
(* mcsum = Plus @@ Table[randomevent[1, 159.417, 107.697, thetop], {300000}]; *)
(* histo = datasum/mcsum*histo; *)
(* MultipleListPlot[ *)
(*     {Table[{{(i-1)*2+30, Sum[data[[i,j,1]], {j, 1, 35}]}, ErrorBar[Sqrt[Sum[data[[i,j,2]]^2, {j, 1, 35}]]]}, {i, 1, 15}], *)
(*      Table[{(i-1)*2+30, Sum[histo[[i,j]], {j, 1, 35}]}, {i, 1, 15}]}, *)
(*     SymbolStyle -> {RGBColor[1,0,0], RGBColor[0,0,1]}, *)
(*     Frame -> True, *)
(*     Axes -> True, *)
(*     AxesOrigin -> {29, 0}, *)
(*     PlotRange -> {{29, 61}, {-40, 1000}}, *)
(*     FrameLabel -> {"Jet-jet invariant mass (GeV)", None, "zeta=1, mLSP, mChar", None} *)
(* 		]; *)

bowl = Flatten[Table[{zeta, mc, mlsp, chisquare[zeta, mc, mlsp]},
		     {zeta, 0.9, 1, 0.01},
		     {mc, 159.417 - 4, 159.417 + 4, 2},
		     {mlsp, 107.697 - 4, 107.697 + 4, 2}], 2];
fitbowl = Fit[bowl, {1, zeta, zeta^2, mc, mc^2, mlsp, mlsp^2, zeta*mc, zeta*mlsp, mc*mlsp}, {zeta, mc, mlsp}]

                   6                          2
Out[4]= -4.53237 10  + 28591.6 mc + 493.419 mc  + 34162.5 mlsp - 
 
                                  2
>    1534.56 mc mlsp + 880.07 mlsp  + 795723. zeta - 17267.4 mc zeta + 
 
                                    2
>    16731.5 mlsp zeta + 52425. zeta

DumpSave["fakeit2.mx", {bowl, histn, fitbowl}];

Fit[{#[[1]], #[[4]]}& /@ Select[bowl, (#[[2]] == 159.417  &&  #[[3]] == 107.697)&], {1, zeta, zeta^2}, {zeta}]

                                              2
Out[63]= 24959.6 - 48143.5 zeta + 23681.1 zeta

Solve[D[Out[63], zeta] == 0, zeta]

Out[66]= {{zeta -> 1.01649}}

Out[63] /. zeta -> 1.01649

Out[67]= 490.851

(zeta /. Solve[Out[63] == 490.851 + 1, zeta][[1]]) - 1.01649

Out[74]= -0.00649315

(zeta /. Solve[Out[63] == 490.851 + 1, zeta][[2]]) - 1.01649

Out[75]= 0.00650176

Fit[{#[[2]], #[[4]]}& /@ Select[bowl, (#[[1]] == 1  &&  #[[3]] == 107.697)&], {1, mc, mc^2}, {mc}]

                   7                          2
Out[80]= 2.10773 10  - 266924. mc + 845.021 mc

Solve[D[Out[80], mc] == 0, mc]

Out[81]= {{mc -> 157.939}}

(mc /. Solve[Out[80] == 157.939 + 1, mc][[1]]) - 157.939

Out[83]= -1.45294

(mc /. Solve[Out[80] == 157.939 + 1, mc][[2]]) - 157.939

Out[84]= 1.45342

(159.417 - 157.939)/1.45

Out[85]= 1.01931

Fit[{#[[3]], #[[4]]}& /@ Select[bowl, (#[[1]] == 1  &&  #[[2]] == 159.417)&], {1, mlsp, mlsp^2}, {mlsp}]

                   7                              2
Out[86]= 1.43438 10  - 262517. mlsp + 1200.95 mlsp

Solve[D[Out[86] == 0, mlsp], mlsp]

Out[89]= {{mlsp -> 109.296}}

(mlsp /. Solve[Out[86] == 109.296 + 1][[1]]) - 109.296

Out[90]= -1.38362

(mlsp /. Solve[Out[86] == 109.296 + 1][[2]]) - 109.296

Out[91]= 1.38318

(109.296 - 107.697)/1.38318

Out[92]= 1.15603







bowl = Flatten[Table[{zeta, mc, mlsp, chisquare[zeta, mc, mlsp]},
		     {zeta, 1, 1},
		     {mc, 159.417 - 10, 159.417 + 10, 0.5},
		     {mlsp, 107.697 - 10, 107.697 + 10, 0.5}], 2];

DumpSave["fakeit3.mx", {bowl, histn}];


tmphistn = histn;

tmpbowl = Table[{159.417 + mcstep, 107.697 + mlspstep,
		 If[ListQ[tmphistn[1., 159.417 + mcstep, 107.697 + mlspstep]],
		    Sum[If[data[[i,j,2]] > 0,
			   (data[[i,j,1]] - tmphistn[1., 159.417 + mcstep, 107.697 + mlspstep][[i,j]])^2/data[[i,j,2]]^2, 0],
			{i, 1, 15}, {j, 1, 35}],
		    REMOVEME]},
		{mcstep, -10., 10., 0.5},
		{mlspstep, -10, 10., 0.5}];
tmpbowl2 = Flatten[tmpbowl /. Indeterminate -> REMOVEME, 1];

<< fakeit2.mx;

masterlist = Join[Select[tmpbowl2, NumberQ[#[[3]]]&], {#[[2]], #[[3]], #[[4]]}& /@ Select[bowl, (#[[1]] == 1.  &&  #[[2]] > 154.917)&]];

Sort[masterlist, If[#1[[1]] == #2[[1]], #1[[2]] < #2[[2]], #1[[1]] < #2[[1]]]&]

tmpbowl2func = Interpolation[tmpbowl2, InterpolationOrder -> 0];

That didn't work!

tmpbowl2func = Interpolation[{#[[2]], #[[3]], #[[4]]}& /@ Select[bowl, (#[[1]] == 1.)&], InterpolationOrder -> 0];

tmpbowl2func = Interpolation[{#[[1]], #[[2]], If[NumberQ[#[[3]]], #[[3]], 10*ndof]}& /@ tmpbowl2, InterpolationOrder -> 0];

ContourPlot[(tmpbowl2func[mc, mlsp]), {mc, 159.417 - 4, 159.417 + 4}, {mlsp, 107.697 - 4, 107.697 + 4},
	    Frame -> True,
	    FrameLabel -> {"Mass of chargino (GeV)", "Mass of LSP (GeV)", "Confidence Intervals with zeta = 1", None},
	    PlotRange -> {{159.417 - 10, 159.417 + 10}, {107.697 - 10, 107.697 + 10},
			  {0, ndof*5}},
	    Contours -> {ndof, ndof*2, ndof*3, ndof*4},
	    PlotPoints -> 50,
	    ColorFunction -> (RGBColor[#, #, 1]&),
	    Epilog -> {Line[{{159.417 - 10, 107.697 - 10},
			     {159.417 - 10, 107.697 + 10},
			     {159.417 + 10, 107.697 + 10},
			     {159.417 + 10, 107.697 - 10},
			     {159.417 - 10, 107.697 - 10}}](* , *)
(* 		       RGBColor[1,1,0], *)
(* 		       Polygon[{{154.917 - 0.5, 107.697 - 10.}, *)
(* 				{154.917 - 0.5, 107.697 + 10.}, *)
(* 				{159.417 + 10., 107.697 + 10.}, *)
(* 				{159.417 + 10., 107.697 - 10.}, *)
(* 				{154.917 - 0.5, 107.697 - 10.} *)
(* 			       }], *)
(* 		       RGBColor[0,0,0], *)
(* 		       Line[{{154.917 - 0.5, 107.697 - 10.}, *)
(* 			     {154.917 - 0.5, 107.697 + 10.}, *)
(* 			     {159.417 + 10., 107.697 + 10.}, *)
(* 			     {159.417 + 10., 107.697 - 10.}, *)
(* 			     {154.917 - 0.5, 107.697 - 10.}}] *)
		       , RGBColor[1,1,0],
		       Rectangle[{159.417 - 10., 107.697 - 10.},
				 {159.417 - 4., 107.697 + 10.}],
		       Rectangle[{159.417 + 10., 107.697 + 10.},
				 {159.417 + 4., 107.697 - 10.}],
		       Rectangle[{159.417 - 10., 107.697 - 10.},
				 {159.417 + 10., 107.697 - 4.}],
		       Rectangle[{159.417 + 10., 107.697 + 10.},
				 {159.417 - 10., 107.697 + 4.}],
		       RGBColor[0,0,0],
		       Line[{{159.417 - 10, 107.697 - 10},
			     {159.417 - 10, 107.697 + 10},
			     {159.417 + 10, 107.697 + 10},
			     {159.417 + 10, 107.697 - 10},
			     {159.417 - 10, 107.697 - 10}}],
		       Line[{{159.417 - 4, 107.697 - 4},
			     {159.417 - 4, 107.697 + 4},
			     {159.417 + 4, 107.697 + 4},
			     {159.417 + 4, 107.697 - 4},
			     {159.417 - 4, 107.697 - 4}}]
			       },
	    ImageSize -> 72*6
(*     	    , DisplayFunction -> (Display["fakeit2_chisquare_tmpbowl2.eps", #, "EPS"]&)   *)
	   ];














Min[#[[4]]& /@ Select[bowl, (#[[1]] == 1)&]]

ContourPlot[(Interpolation[{#[[2]], #[[3]], #[[4]]}& /@ Select[bowl, (#[[1]] == 1)&], InterpolationOrder -> 0][mc, mlsp]), {mc, 159.417 - 10, 159.417 + 10}, {mlsp, 107.697 - 10, 107.697 + 10},
	    Frame -> True,
	    FrameLabel -> {"Mass of chargino (GeV)", "Mass of LSP (GeV)", "Confidence Intervals with zeta = 1", None},
	    PlotRange -> {{159.417 - 10, 159.417 + 10}, {107.697 - 10, 107.697 + 10},
			  {0, 2000}},
	    Contours -> 10,
	    PlotPoints -> 50,
	    ColorFunction -> (RGBColor[#, #, 1]&),
	    ImageSize -> 72*6
(* 	    , DisplayFunction -> (Display["fakeit2_chisquare.eps", #, "EPS"]&) *)
	   ];




histo = Table[0, {15}, {35}];
thetop = topofandreas[1, 159.417, 107.697];
mcsum = Plus @@ Table[randomevent[1, 159.417, 107.697, thetop], {3000000}];
MultipleListPlot[
    {Table[{{(i-1)*2+30, Sum[data[[i,j,1]], {j, 1, 35}]}, ErrorBar[Sqrt[Sum[data[[i,j,2]]^2, {j, 1, 35}]]]}, {i, 1, 15}],
     Table[{(i-1)*2+30, Sum[datasum/mcsum*histo[[i,j]], {j, 1, 35}]}, {i, 1, 15}]},
    PlotJoined -> {False, True},
    SymbolShape -> {PlotSymbol[Box, 1.0], PlotSymbol[Box, 0]},
    PlotStyle -> {Dashing[{}]},
    Frame -> True,
    Axes -> True,
    AxesOrigin -> {29, 0},
    PlotRange -> {{29, 61}, {-40, 1000}},
    FrameLabel -> {"Jet-jet invariant mass (GeV)", None, None, None},
    ImageSize -> 72*5
    , DisplayFunction -> (Display["fakeit2_mass.eps", #, "EPS"]&)
		];
MultipleListPlot[
    {Table[{{(j-1)*2+70, Sum[data[[i,j,1]], {i, 1, 15}]}, ErrorBar[Sqrt[Sum[data[[i,j,2]]^2, {i, 1, 15}]]]}, {j, 1, 35}],
     Table[{(j-1)*2+70, Sum[datasum/mcsum*histo[[i,j]], {i, 1, 15}]}, {j, 1, 35}]},
    PlotJoined -> {False, True},
    SymbolShape -> {PlotSymbol[Box, 1.0], PlotSymbol[Box, 0]},
    PlotStyle -> {Dashing[{}]},
    Frame -> True,
    Axes -> True,
    AxesOrigin -> {69, 0},
    PlotRange -> {{69, 141}, {-20, 500}},
    FrameLabel -> {"Two-jet total energy (GeV)", None, None, None},
    ImageSize -> 72*5
    , DisplayFunction -> (Display["fakeit2_energy.eps", #, "EPS"]&)
		];

bowl = Flatten[Table[{mc, mlsp, If[Abs[mc-mlsp-51.72] < 7,
				   chisquare[1., mc, mlsp],
				   ndof*10]},
		     {mc, 159.417 - 15, 159.417 + 15, 1},
		     {mlsp, 107.697 - 15, 107.697 + 15, 1}], 1];

DumpSave["fakeit4.mx", bowl];

ContourPlot[Interpolation[{#[[1]], #[[2]], If[NumberQ[#[[3]]], #[[3]], 10*ndof]}& /@ bowl, InterpolationOrder -> 1], {mc, 159.417 - 15, 159.417 + 15}, {mlsp, 107.697 - 15, 107.697 + 15},
	    Frame -> True,
	    FrameLabel -> {"Mass of chargino (GeV)", "Mass of LSP (GeV)", "Confidence Intervals with zeta = 1", None},
	    PlotRange -> {{159.417 - 15, 159.417 + 15}, {107.697 - 15, 107.697 + 15},
			  {0, ndof*5}},
	    Contours -> {ndof*2, ndof*3, ndof*4},
	    PlotPoints -> 1000,
	    ColorFunction -> (RGBColor[#, #, 1]&),
	    Epilog -> {Line[{{159.417 - 10, 107.697 - 10},
			     {159.417 - 10, 107.697 + 10},
			     {159.417 + 10, 107.697 + 10},
			     {159.417 + 10, 107.697 - 10},
			     {159.417 - 10, 107.697 - 10}}]
		      },
	    ImageSize -> 72*6
     	    , DisplayFunction -> (Display["fakeit2_chisquare.eps", #, "EPS"]&)
	   ];



