const String index1 ="<html> <head> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&family=Rubik:wght@300&family=Ubuntu:wght@500&display=swap\" rel=\"stylesheet\"> <title>wambo</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style> #titlle {float:right;margin:0px 10px;background-color:rgba(255,185,25,80%);border-radius:15px;padding:7px;} #titlle li{display:inline-block; padding:0px 5px;padding-top:4px;} #msg_i{height:20px;width:37px} #logo{height:55px;width:55px;} #updi{height:28px;width:30px ;float:right;background-color:rgb(240,240,255);border:2px dotted gray;border-radius:5px;} #subt{background-color:rgba(68,255,200,35%);margin-top:0px;margin-bottom:0px;padding:15px} #subt li{display:inline-block; padding:8px;background-color:rgba(25,255,255,95%);border-radius:15px;border:3px solid rgba(255,160,30,35%) ; font-size:17px;} #container table{display:inline-block;border-radius:6px; background-color:rgba(155,130,240,30%);padding:10px;align:center;margin:0px 20px; box-shadow: 3px 3px 5px lightblue;} #container table td {border-width:3px;border-color:rgba(195,175,220,80%);border-radius:6px;background-color:white;} #container2{background-color:rgba(150,255,235,35%);margin:0px;box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);} #input{border-color:rgba(21,152,252,80%);border-radius:3px;padding:5px; margin:15px auto; margin-top:0px;background-color:rgba(255,235,150,55%); } #input td{border-width:2px;border-color:rgba(203,152,255,80%);border-radius:3px;padding:3px;background-color:rgba(213,243,162,70%);} #till,#from{background-color:rgba(78,255,250,30%);color:rgba(130,55,255,80%);text-align:center;font-size:20px} #send{background-color:rgba(187,250,78,60%); border-radius:2px; border-color:rgba(176,230,198); color:rgb(90,30,90);} #container iframe{display:inline-block; border-radius:10px; box-shadow: 3px 3px 5px lightblue;} #time{width:235px;color:gray;background-color:aqua;border:2px dotted;border-radius:5px;float:right;padding:0px;margin-right:10%;px;} .fromp{display:inline-block;border:1px dotted black;border-radius:20px;background-color:rgba(0,140,255,0.4);box-shadow: 2px 3px 10px lightblue;float:right} #fp{border-radius:20px;background-color:rgba(255,255,200,0.45);box-shadow: 0px 1px 10px silver; float:right} #p1{position:relative;top:-120px;margin:0px 20px 0px 0px;} #p2{margin:0px;} #prev,#next{margin:0px 15px;} body{ margin:0px; background-color:rgba(255,185,185,10%); font-family:arial; overflow:hidden; } .hdder{ background-color:rgba(25,255,255,65%); padding:15px; margin:0; box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); } .hdderWrapper{ font-family: 'Roboto Slab', arial,serif; color:rgba(80,120,120); font-size:35px; text-align:center; } .shadowLight{ box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); } .genericText{ font-size:20px; font-family:'Rubik',sans-serif; display:inline-block; } </style> </head> <body id=\"bdy\"> <div class=\"hdder\"> <h2 class=\"hdderWrapper\">WamBo</h2> <ul id=\"titlle\" class=\"shadowLight\"> <li id=\"mp\"><a href=\"/sm/\"style=\"width:37px;height:20px;position:relative;top:-20px\">SiteMap</a></li> <li><a href='/abt/'><image src=\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/LOGO.png\" id=\"logo\" title=\"logo\"></li> </ul> </div> <div id=\"wrapper\"> <ul id=\"subt\"> <li class=\"shadowLight\"><a href=\"/raw/\">RAW</a></li> <li class=\"shadowLight\"><a id=\"msg\" href=\"/msg/\"><image src =\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/MSGG.png\" id=\"msg_i\" title=\"stored memo\"></a></li> </ul> </div> <div id=\"container2\"> <form name=\"f1\" action=\"/wambo\"onsubmit=\"return check()\" method=\"post\"> <table id=\"input\" border=\"3px\" class=\"shadowLight\"> <tr> <th> <label>From:&nbsp;</label><input list=\"selF\" type=\"text\" maxlength=\"3\"name=\"from*\" id=\"from\" style=\"width:50%;\" placeholder=\"0.0\" value=\"0.0\"> <datalist id=\"selF\" > <option value=0.0></option> <option value=0.3></option> <option value=1.0></option> <option value=1.3></option> <option value=2.0></option> <option value=2.3></option> <option value=3.0></option> <option value=4.0></option> <option value=6.0></option> <option value=7.0></option> <option value=8.0></option> <option value=10.0></option> </datalist> </th></tr> <tr><td>&nbsp;</td><td><input type=\"submit\" value=\"&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;\" id=\"send\"></td></tr> <tr><th><label>&nbsp;For:&nbsp;&nbsp;&nbsp;</label><input list=\"selF\" type=\"text\"name=\"for*\" id=\"till\" placeholder=\"8.0\" maxlength=\"3\" style=\"width:50%;\" value=\"8.0\"></th></tr> </table> <div id=\"container\" align=\"center\"> <table border=\"2px\" border-color=\"silver\"style=\"border-style: dotted\" class=\"genericText\"> <tr><td></td><td id=\"day\" style=\"text-align:center\">Schedule</td></tr> <tr><td>4_6</td><td class=\"sced\"><p id=\"a\"></p></td></tr> <tr><td>6_8</td><td class=\"sced\"><p id=\"b\" ></p></td></tr> <tr><td>8_10</td><td class=\"sced\"><p id=\"c\"></p></td></tr> <tr><td>10_12</td><td class=\"sced\"><p id=\"d\"></p></td></tr> <tr><td>12_14</td><td class=\"sced\"><p id=\"e\"></p></td></tr> <tr><td>14_16</td><td class=\"sced\"><p id=\"f\"></p></td></tr> <tr><td>16_18</td><td class=\"sced\"><p id=\"g\"></p></td></tr> <tr><td>18_20</td><td class=\"sced\"><p id=\"h\"></p></td></tr> <tr><td>20_22</td><td class=\"sced\"><p id=\"i\"></p></td></tr> <tr><td>22_24</td><td class=\"sced\"><p id=\"j\"></p></td></tr> <tr><td>24_2</td><td class=\"sced\"><p id=\"k\"></p></tr> </table> <iframe src=\"/report/\" title=\"report\" height=\"300px\" width=\"400px\" style=\"border:2px dotted rgba(240,130,235); \" id=\"rep\"></iframe> <iframe src=\"/fromp/\" class=\"fromP\" id=\"p1\"style=\"width:24px;height:400px;\"></iframe> </div> <input id=\"time\" type=\"text\" name=\"t*\" class=\"shadowLight genericText\"> <a href=\"/upd/\"><image src=\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/UPD.png\" id=\"updi\" title=\"UPDATE\" class=\"shadowLight\"></a> </form> </div> <iframe src=\"/fromp/\" class=\"fromP\" id=\"p2\" style=\"width:24px;height:200px;transform:rotate(90deg);\"></iframe> <script language=\"javascript\"> var dateTime= new Date(); document.getElementById(\"time\").value=dateTime; function refT() { var ref=String(new Date()); document.getElementById(\"time\").value=ref.substring(0,24); } setInterval(refT,1000); var sendB=document.getElementById(\"send\"); function sendC(){ document.getElementById(\"input\").style=\"background-color:#00ff00\"; } var frm=document.getElementById(\"from\"); var till=document.getElementById(\"till\"); function check(){ let x = document.forms[\"f1\"][\"from*\"].value; let y = document.forms[\"f1\"][\"till*\"].value; sendC(); if (isNaN(parseFloat(x))||isNan(parseFloat(y)) { alert(\"input should be a number\"); return false; } } frm.onfocus=function(){ frm.value=''; } till.onfocus=function(){ till.value=''; } if(/Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent)){ document.getElementById('bdy').style=\"overflow:auto; overflow-x: hidden;\"; document.getElementById('p1').style=\"display:none\"; }else{ document.getElementById('p2').style=\"display:none\" } var scedule=[";
String h="hello world";
#include <Wire.h>

#define ADDR_Ax 0b000 //A2, A1, A0
#define ADDR (0b1010 << 3) + ADDR_Ax

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  for(int i=0;i<h.length();i++){
  writeI2CByte(0,h[i]);}
}

void loop() {
  // put your main code here, to run repeatedly:
  for(byte i=0;i<(byte)h.length();i++){
  Serial.print((char)readI2CByte(i));
  }
Serial.println();  
}

void writeI2CByte(byte data_addr, byte data){
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte readI2CByte(byte data_addr){
  byte data = NULL;
  Wire.beginTransmission(ADDR);
  Wire.write(data_addr);
  Wire.endTransmission();
  Wire.requestFrom(ADDR, 1); //retrieve 1 returned byte
  delay(1);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}
