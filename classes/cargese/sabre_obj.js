// WINDOWPANE FUNCTION
// OPENS A NEW WINDOW BASED ON SPECIFIC CRITERIA PASSED TO THE FUNCTION
// url = REQUIRED; THE URL TO SEND TO THE NEW WINDOW
// x, y = OPTIONAL; THE PIXEL SIZES OF THE NEW WINDOW
// modal = REQUIRED; BOOLEAN INDICATING THE TYPE OF WINDOW TO OPEN;
//          true= SAME SIZED WINDOW
//          false = SMALLER WINDOW
//
function windowpane(url, x, y, modal)
{

   if (url == "")
      return false;

   // "RANDOMIZES" WINDOW NAME TO ALLOW MULTIPLE DAUGHTER WINDOWS
   i = Math.random() * 1000;
   winName = Math.round(i) + "window";

   // SMALLER WINDOW
   if (!modal)
   {
      if (x == null)
         x = 600;

      if (y == null)
         y = 350;
   }

   // OPEN WINDOW WITH STRIPPED CHROME
   window.open(url,winName,'directories=no,width=' + x + ',height=' + y + ',hotkeys=no,location=no,menubar=no,scrollbars=yes,resizable=yes,status=yes,toolbar=yes');

   // return true;
}

// writes out section ads in reservation page
//
function section_ads(USEAREA,AREA,ADDSPACE)
{
  document.write("<td width='88'  height='31'>");
  if(USEAREA == 1)
  {
    document.write("<a href=javascript:windowpane(\""+ad_click+AREA+ad_tag+"&"+ranNum+"\",\"\",\"\",true);>");
    document.write("<img src="+ad_img+AREA+ad_tag+"&"+ranNum+" width='88' height='31' border='0'></a></td>");
  }
  else
  {
    document.write("<img src=/ng/spacer.gif width='1' height='1'></td>");
  }
  if(ADDSPACE == 1)
  {
    document.write("<td width='5'><img src=/ng/spacer.gif width='1' height='1'></td>");
  }
}

var ad_click="http://sabre.adbureau.net/adclick";

var ad_img="https://sabre-s.adbureau.net/iserver";

function openAd(clcksvr,imgsvr,info,width,height){
//alert(clcksvr);
//alert(imgsvr);
//alert(info);

 var value = adtags_amp;
 
 
 var click = clcksvr + info + value;
// alert(click);
 var imag = imgsvr + info + value;
// alert(imag);
 
// alert("start");
// alert("<a href=javascript:windowpane('"+ click + "\',\'650\',\"500\",true);>");
// alert("<img src="+imag+" width=\""+width +"\" height=\""+height+"\" border='0'></a>");
 document.writeln('<a href=javascript:windowpane("'+ click + '","650","500",true);>');
 document.write("<img src="+imag+" width=\""+width +"\" height=\""+height+"\" border='0'></a>");
// alert("Finish");
}

function reg_finali(){
       var allcookies = document.cookie;
       
       var pos = allcookies.indexOf("TPExits=");

       var date = (new Date()).getDate();
       var month =  + ((new Date()).getMonth() + 1);
       var year = (new String((new Date()).getYear())).substring(1,3);
       var expire_yr = new Date();

           expire_yr.setFullYear(expire_yr.getFullYear() + 1);

       if(date < 10)
        {
         temp = '0'+ date;
         date = temp;
        }

       if(month < 10)
        {
         temp = '0'+month;
         month = temp;
        }
        
 	   if(pos != -1)
		{
			var start = pos + 8;
			var end  = allcookies.indexOf(';',start);
			if(end == -1) end = allcookies.length;
			var value = allcookies.substring(start,end);
			value = unescape(value);

            if(value == 'TRUE')
            {
             var newcookie = 'TPExits=TRUE|userid|rmsEmail|0|toFinaliDate|remEmail|';
                 newcookie += '; expires=' + expire_yr.toGMTString();
                 newcookie += '; path=/';
            //     newcookie += '; domain=' + 'localhost:7001';

            }
            else if(value.length > 4)
            {
				var indx = value.indexOf('|');
				var front = value.slice(0,indx);
				var temp = value.slice(indx+1);

				indx = temp.indexOf('|');
				var login = temp.slice(0,indx);

				temp = temp.slice(indx+1);
				indx = temp.indexOf('|');
				var email1 = temp.slice(0,indx);

				temp = temp.slice(indx+1);
				indx = temp.indexOf('|');
				var counter = temp.slice(0,indx);

				temp = temp.slice(indx+1);
				indx = temp.indexOf('|');
				var date = temp.slice(0,indx);

				temp = temp.slice(indx+1);
				indx = temp.indexOf('|');
				var email2 = temp.slice(0,indx);

				var newcookie =  'TPExits=TRUE|'+ login+'|'+email1+'|'+counter+'|'+date+'|'+email2+'|';
				    newcookie += '; expires=' + expire_yr.toGMTString();
				    newcookie += '; path=/';
		//		    newcookie += '; domain=' + 'localhost:7001';
				    
			}
       }
       else
       {
        var newcookie = 'TPExits=TRUE|userid|rmsEmail|0|toFinaliDate|remEmail|';
            newcookie += '; expires=' + expire_yr.toGMTString();
            newcookie += '; path=/';
            //newcookie += '; domain=' + 'localhost:7001';
       }
       
   if(newcookie)
      document.cookie = newcookie;
      
}

function finali_change_date()
{
        var allcookies = document.cookie;
	var pos = allcookies.indexOf("TPExits=");

	var date = (new Date()).getDate();
	var month =  + ((new Date()).getMonth() + 1);
	var year = (new String((new Date()).getYear())).substring(1,3);
	var expire_yr = new Date();

	expire_yr.setFullYear(expire_yr.getFullYear() + 1);

	if(date < 10)
	{
		temp = '0'+ date;
		date = temp;
	}

	if(month < 10)
	{
		temp = '0'+month;
		month = temp;
	}

	if(pos != -1)
	{
	var start = pos + 8;
	var end  = allcookies.indexOf(';',start);
	if(end == -1) end = allcookies.length;
	var value = allcookies.substring(start,end);
	value = unescape(value);

	var indx = value.indexOf('|');
	var front = value.slice(0,indx);
	var temp = value.slice(indx+1);

	indx = temp.indexOf('|');
	var login = temp.slice(0,indx);

	temp = temp.slice(indx+1);
	indx = temp.indexOf('|');
	var email1 = temp.slice(0,indx);

	temp = temp.slice(indx+1);
	indx = temp.indexOf('|');
	var counter = temp.slice(0,indx);

	temp = temp.slice(indx+1);
	indx = temp.indexOf('|');
	var finali_date = temp.slice(0,indx);

	temp = temp.slice(indx+1);
	indx = temp.indexOf('|');
	var email2 = temp.slice(0,indx);

	var newcookie =  'TPExits='+ front +'|'+ login +'|'+email1+'|'+counter+'|'+date+month+year+'|'+email2+'|';
	newcookie += '; expires=' + expire_yr.toGMTString();
	newcookie += '; path=/';
	//		    newcookie += '; domain=' + 'localhost:7001';
	}
	else
	{
	var newcookie = 'TPExits=TRUE|userid|rmsEmail|0|'+date+month+year+'|remEmail|';
	newcookie += '; expires=' + expire_yr.toGMTString();
	newcookie += '; path=/';
	//newcookie += '; domain=' + 'localhost:7001';
	}

	if(newcookie)
	document.cookie = newcookie;
}

<!--
function getCurrentFormObjectArray(formObject){
if(formObject==null){
return;
}
var str = "";
for(var j = 0; j < formObject.length; j++){
if(formObject[j]!=null){
str += new String;
str += "<INPUT TYPE=\"" +  formObject[j].type + "\" ";
str += "NAME=\"" + formObject[j].name + "\" ";
str += "VALUE=\"" + formObject[j].value + "\">";
str += "\r\n";
}
}
return str;
}

function onClick() {
var formid;
var str;
str = "window.document.InfotrieverInfo";
window.document.forms[1].elements[1].value = getCurrentFormObjectArray(eval(str)).toString();
setTimeout ("document.forms[1].submit ();",1000);
}
// -->

// WINDOWPANE FUNCTION
// OPENS A NEW WINDOW BASED ON SPECIFIC CRITERIA PASSED TO THE FUNCTION
// url = REQUIRED; THE URL TO SEND TO THE NEW WINDOW
// winName = NAME OF WINDOW
// x, y = OPTIONAL; THE PIXEL SIZES OF THE NEW WINDOW
//
function windowNamed(url, winName, x, y)
{

   if (url == "")
      return false;

   // SMALLER WINDOW
   if (x == null)
       x = 600;

   if (y == null)
       y = 350;

   // OPEN WINDOW WITH STRIPPED CHROME
   win = window.open(url, winName,'directories=no,width=' + x + ',height=' + y + ',hotkeys=no,location=no,menubar=no,scrollbars=yes,resizable=yes,status=yes,toolbar=yes');
   win.focus();

   // return true;
}

// NEW WINDOW FUNCTION, CENTERED ON SCREEN, NO TOOLBARS
// USED FOR COPYRIGHT INFO
var win= null;
function windowpaneNew(mypage,myname,w,h,scroll){
  var winl = (screen.width-w)/2;
  var wint = (screen.height-h)/2;
  var settings  ='height='+h+',';
      settings +='width='+w+',';
      settings +='top='+wint+',';
      settings +='left='+winl+',';
      settings +='scrollbars='+scroll+',';
      settings +='resizable=yes';
  win=window.open(mypage,myname,settings);
  if(parseInt(navigator.appVersion) >= 4){win.window.focus();}
}
