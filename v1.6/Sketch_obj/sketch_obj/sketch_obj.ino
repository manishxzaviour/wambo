#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
const char* ssid  = "M 2.4G ";
const char* password  = "helloWorld11";
const char* ssid_ap   = "Wambo_ap";
const char* password_ap = "244466666";
const int pin = 5 ;
const int btn = 14;
const int led =12;
 IPAddress staticIP(192, 168, 0, 184);
 IPAddress gateway(192, 168, 0, 101);
 IPAddress subnet(255, 255, 0, 0);
ESP8266WebServer server(80);

const char* prog1 PROGMEM={"<html> <head> <META HTTP-EQUIV=\"Refresh\" CONTENT=5> <style> body{margin:0px;background-color:rgba(0,140,255,0.4);} #fp{border-radius:20px;background-color:rgba(255,255,200,0.45);box-shadow: 0px 1px 10px silver;height:"};
int progPerc=10;
const char* prog2 PROGMEM={"%;width:100%} </style> </head> <body> <div id=\"fp\" title=\"From countdown\"> </div> </body> </html>"};
const char* index1 PROGMEM={"<html> <head> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&family=Rubik:wght@300&family=Ubuntu:wght@500&display=swap\" rel=\"stylesheet\"> <title>wambo</title> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <style> #titlle {float:right;margin:0px 10px;background-color:rgba(255,185,25,80%);border-radius:15px;padding:7px;} #titlle li{display:inline-block; padding:0px 5px;padding-top:4px;} #msg_i{height:20px;width:37px} #logo{height:55px;width:55px;} #updi{height:28px;width:30px ;float:right;background-color:rgb(240,240,255);border:2px dotted gray;border-radius:5px;} #subt{background-color:rgba(68,255,200,35%);margin-top:0px;margin-bottom:0px;padding:15px} #subt li{display:inline-block; padding:8px;background-color:rgba(25,255,255,95%);border-radius:15px;border:3px solid rgba(255,160,30,35%) ; font-size:17px;} #container table{display:inline-block;border-radius:6px; background-color:rgba(155,130,240,30%);padding:10px;align:center;margin:0px 20px; box-shadow: 3px 3px 5px lightblue;} #container table td {border-width:3px;border-color:rgba(195,175,220,80%);border-radius:6px;background-color:white;} #container2{background-color:rgba(150,255,235,35%);margin:0px;box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);} #input{border-color:rgba(21,152,252,80%);border-radius:3px;padding:5px; margin:15px auto; margin-top:0px;background-color:rgba(255,235,150,55%); } #input td{border-width:2px;border-color:rgba(203,152,255,80%);border-radius:3px;padding:3px;background-color:rgba(213,243,162,70%);} #till,#from{background-color:rgba(78,255,250,30%);color:rgba(130,55,255,80%);text-align:center;font-size:20px} #send{background-color:rgba(187,250,78,60%); border-radius:2px; border-color:rgba(176,230,198); color:rgb(90,30,90);} #container iframe{display:inline-block; border-radius:10px; box-shadow: 3px 3px 5px lightblue;} #time{width:235px;color:gray;background-color:aqua;border:2px dotted;border-radius:5px;float:right;padding:0px;margin-right:10%;px;} .fromp{display:inline-block;border:1px dotted black;border-radius:20px;background-color:rgba(0,140,255,0.4);box-shadow: 2px 3px 10px lightblue;float:right} #fp{border-radius:20px;background-color:rgba(255,255,200,0.45);box-shadow: 0px 1px 10px silver; float:right} #p1{position:relative;top:-120px;margin:0px 20px 0px 0px;} #p2{margin:0px;} #prev,#next{margin:0px 15px;} body{ margin:0px; background-color:rgba(255,185,185,10%); font-family:arial;} .hdder{ background-color:rgba(25,255,255,65%); padding:15px; margin:0; box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); } .hdderWrapper{ font-family: 'Roboto Slab', arial,serif; color:rgba(80,120,120); font-size:35px; text-align:center; } .shadowLight{ box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); } .genericText{ font-size:20px; font-family:'Rubik',sans-serif; display:inline-block; } </style> </head> <body id=\"bdy\"> <div class=\"hdder\"> <h2 class=\"hdderWrapper\">WamBo</h2> <ul id=\"titlle\" class=\"shadowLight\"> <li id=\"mp\"><a href=\"/sm/\"style=\"width:37px;height:20px;position:relative;top:-20px\">SiteMap</a></li> <li><a href='/abt/'><image src=\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/LOGO.png\" id=\"logo\" title=\"logo\"></li> </ul> </div> <div id=\"wrapper\"> <ul id=\"subt\"> <li class=\"shadowLight\"><a href=\"/raw/\">RAW</a></li> <li class=\"shadowLight\"><a id=\"msg\" href=\"/msg/\"><image src =\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/MSGG.png\" id=\"msg_i\" title=\"stored memo\"></a></li> </ul> </div> <div id=\"container2\"> <form name=\"f1\" action=\"/wambo\"onsubmit=\"return check()\" method=\"post\"> <table id=\"input\" border=\"3px\" class=\"shadowLight\"> <tr> <th> <label>From:&nbsp;</label><input list=\"selF\" type=\"text\" maxlength=\"3\"name=\"from*\" id=\"from\" style=\"width:50%;\" placeholder=\"0.0\" value=\"0.0\"> <datalist id=\"selF\" > <option value=0.0></option> <option value=0.3></option> <option value=1.0></option> <option value=1.3></option> <option value=2.0></option> <option value=2.3></option> <option value=3.0></option> <option value=4.0></option> <option value=6.0></option> <option value=7.0></option> <option value=8.0></option> <option value=10.0></option> </datalist> </th></tr> <tr><td>&nbsp;</td><td><input type=\"submit\" value=\"&nbsp;&nbsp;&nbsp;>>&nbsp;&nbsp;&nbsp;\" id=\"send\"></td></tr> <tr><th><label>&nbsp;For:&nbsp;&nbsp;&nbsp;</label><input list=\"selF\" type=\"text\"name=\"for*\" id=\"till\" placeholder=\"8.0\" maxlength=\"3\" style=\"width:50%;\" value=\"8.0\"></th></tr> </table> <div id=\"container\" align=\"center\"> <table border=\"2px\" border-color=\"silver\"style=\"border-style: dotted\" class=\"genericText\"> <tr><td></td><td id=\"day\" style=\"text-align:center\">Schedule</td></tr> <tr><td>4_6</td><td class=\"sced\"><p id=\"a\"></p></td></tr> <tr><td>6_8</td><td class=\"sced\"><p id=\"b\" ></p></td></tr> <tr><td>8_10</td><td class=\"sced\"><p id=\"c\"></p></td></tr> <tr><td>10_12</td><td class=\"sced\"><p id=\"d\"></p></td></tr> <tr><td>12_14</td><td class=\"sced\"><p id=\"e\"></p></td></tr> <tr><td>14_16</td><td class=\"sced\"><p id=\"f\"></p></td></tr> <tr><td>16_18</td><td class=\"sced\"><p id=\"g\"></p></td></tr> <tr><td>18_20</td><td class=\"sced\"><p id=\"h\"></p></td></tr> <tr><td>20_22</td><td class=\"sced\"><p id=\"i\"></p></td></tr> <tr><td>22_24</td><td class=\"sced\"><p id=\"j\"></p></td></tr> <tr><td>24_2</td><td class=\"sced\"><p id=\"k\"></p></tr> </table> <iframe src=\"/report/\" title=\"report\" height=\"300px\" width=\"400px\" style=\"border:2px dotted rgba(240,130,235); \" id=\"rep\"></iframe> <iframe src=\"/fromp/\" class=\"fromP\" id=\"p1\"style=\"width:24px;height:400px;\"></iframe> </div> <input id=\"time\" type=\"text\" name=\"t*\" class=\"shadowLight genericText\"> <a href=\"/upd/\"><image src=\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/UPD.png\" id=\"updi\" title=\"UPDATE\" class=\"shadowLight\"></a> </form> </div><script language=\"javascript\"> var dateTime= new Date(); document.getElementById(\"time\").value=dateTime; function refT() { var ref=String(new Date()); document.getElementById(\"time\").value=ref.substring(0,24); } setInterval(refT,1000); var sendB=document.getElementById(\"send\"); function sendC(){ document.getElementById(\"input\").style=\"background-color:#00ff00\"; } var frm=document.getElementById(\"from\"); var till=document.getElementById(\"till\"); function check(){ let x = document.forms[\"f1\"][\"from*\"].value; let y = document.forms[\"f1\"][\"till*\"].value; sendC(); if (isNaN(parseFloat(x))||isNan(parseFloat(y))) { alert(\"input should be a number\"); return false; } } frm.onfocus=function(){ frm.value=''; } till.onfocus=function(){ till.value=''; };var scedule=[\"*******\",\"*******\",\"*******\",\"*******\",\"*******\",\"*******\",\"*******\",\"*******\",\"*******\",\"*******\",\"*******\"]; function Scedule(){ var slot=['a','b','c','d','e','f','g','h','i','j','k']; for(let i=0;i<11;i++){ var x=document.getElementById(slot[i]); x.textContent=scedule[i]; } } window.onload=Scedule; </script> </body> </html>"};
//const char* rep PROGMEM={"<!DOCTYPE html> <html> <head> <script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&display=swap\" rel=\"stylesheet\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script> <style> html{scroll-behavior:smooth} body{background-color:rgba(255,250,250);overflow:hidden} #tDist{box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);} #info{color:rgba(125,100,135,0.7);font-size:20px;text-align:center;font-family: 'Roboto Slab', serif;} #container{display:flex;overflow-x:auto;overflow-y:hidden;box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.1), 0 6px 20px 0 rgba(0, 0, 0, 0.1);} .item{border-right:2px dotted grey;height:200px} ::-webkit-scrollbar {width: 10px;} ::-webkit-scrollbar-track { background: #f1f1f1; border-radius:5px;} ::-webkit-scrollbar-thumb {background: #888; border-radius:5px;} ::-webkit-scrollbar-thumb:hover {background: #555; } </style> <title>Report</title> </head> <body> <section id=\"container\"> <div id=\"d1\" class=\"item\"></div> <div id=\"d2\" class=\"item\"></div> <div id=\"d3\" class=\"item\"></div> <div id=\"d4\" class=\"item\"></div> <div id=\"d5\" class=\"item\"></div> </div> </section> <p id=\"info\"> REPORT </p> <p id=\"status\"></p> </div> <script> google.charts.load('current',{packages:['corechart']}); google.charts.load('current', {'packages':['table']}); google.charts.setOnLoadCallback(drawPie); google.charts.setOnLoadCallback(drawLine); google.charts.setOnLoadCallback(drawScatter); google.charts.setOnLoadCallback(drawBar); function drawPie(){ var onT=16; var offT=8; var pieD = google.visualization.arrayToDataTable([ ['distribution','duration'], ['onTime', onT], ['offTime',offT], ]); var pieOpt= { title:'Distribution', is3D:true }; var pie = new google.visualization.PieChart(document.getElementById('d1')); pie.draw(pieD, pieOpt); } var EleD=[ ['wh', 'period'], [50,7],[60,8],[70,8],[80,9],[90,9],[100,9], [110,10],[120,11],[130,14],[140,14],[150,15]]; var UsageD=[['Activation-Time', 'Day'], [50,7],[60,8],[70,8],[80,9],[90,9],[100,9], [110,10],[120,11],[130,14],[140,14],[150,15]]; var SavingsD=[['Month', 'Savings in wH','Temperature(Avg)'], ['Italy', 55,24], ['France', 49,22], ['Spain', 44,20.9], ['USA', 24,19], ['Argentina', 15,18] ]; function drawLine(){ var lineD = google.visualization.arrayToDataTable(EleD); var lineOpt = { title: 'Electricity saved vs offTime', hAxis: {title: 'Period-Day'}, vAxis: {title: 'Electricity-wH'}, legend: 'none' }; var line = new google.visualization.LineChart(document.getElementById('d2')); line.draw(lineD, lineOpt); } function drawScatter(){ var pointD = google.visualization.arrayToDataTable(UsageD); var pointOpt = { title: 'Activation-Time vs Day', hAxis: {title: 'Period-Day'}, vAxis: {title: 'Time-24H'}, legend: 'none' }; var point = new google.visualization.ScatterChart(document.getElementById('d3')); point.draw(pointD, pointOpt); } function drawBar(){ var barD = google.visualization.arrayToDataTable(SavingsD); var barOpt = { title: 'Savings' }; var bar = new google.visualization.BarChart(document.getElementById('d4')); bar.draw(barD, barOpt); } function drawTable() { var tableD = new google.visualization.DataTable(); tableD.addColumn ('string', 'YYYY-MM-DD'); tableD.addColumn('string', 'Temperature'); tableD.addRows([[\"Date\",\"Celcius\"]]); tableD.addRows(wetherDF); var table = new google.visualization.Table(document.getElementById('d5')); tableD.allowHtml=true tableD.setProperty(3,1,\"one\",{style: 'font-style:bold; font-size:20px;'}); table.draw(tableD, {showRowNumber: true, width: '100%', height: '100%'}); send(); } let wetherPune=\"https://api.tomorrow.io/v4/timelines?location=18.5204303,73.8567437&fields=temperature&units=metric&timesteps=1d&apikey=4eN1LmVG8PWXsdiUiAqVGqDZmV94LQbY\" let wetherD=\"\"; let wetherDF=[]; format(); $(document).ready(function(){ try{$.get(wetherPune, function(data, status){ wetherD=JSON.stringify(data); console.log(\"Data: \" + wetherD + \"&#92;nStatus: \" + status); format() ; send(); });} catch(err){ console.log(err.message); } }); function send(){ var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() { if (this.readyState == 4 && this.status == 200) { console.log(this.responseText); } }; xhttp.open(\"POST\", \"&#92;report&#92;temp\", true); xhttp.send(wetherDF); xhttp.send(wetherDF); } function format(){ let format=wetherD.substring(0,119); wetherD=wetherD.substring(119,wetherD.length-4) for(let i=0;i<=wetherD.length;i++){ if(wetherD[i]=='{'){ let a=wetherD.slice(wetherD[i],wetherD.indexOf(\"}}\")+2); wetherDF.push(a); i=wetherD.indexOf(\"}}\")+2; wetherD=wetherD.slice(wetherD.indexOf(\"}}\")+2,wetherD.length); } } console.log(wetherDF); let tempDF=[]; for(let i=0;i<=wetherDF.length;i++){ let a=[]; let b=String(wetherDF[i]); a.push(b.slice(b.indexOf("};
//const char* rep2 PROGMEM={"\"\\\"startTime\\\":\\\"\")+13,b.indexOf(\"\\\",\\\"\")-10));a.push(b.slice(b.indexOf(\"\\\"temperature\\\":\")+14,b.indexOf(\"}}\"))); "};
//const char* rep3 PROGMEM={"tempDF.push(a); } tempDF.pop(\"['', '{v:}']\") console.log(tempDF); wetherDF=tempDF; google.charts.setOnLoadCallback(drawTable); } </script> </body> </html>"};
const char* rep1 PROGMEM={"<!DOCTYPE html> <html> <head> <script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script> <link rel=\"preconnect\" href=\"https://fonts.googleapis.com\"> <link rel=\"preconnect\" href=\"https://fonts.gstatic.com\" crossorigin> <link href=\"https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&display=swap\" rel=\"stylesheet\"> <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js\"></script> <style> html{scroll-behavior:smooth} body{background-color:rgba(255,250,250);overflow:hidden} #tDist{box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);} #info{color:rgba(125,100,135,0.7);font-size:20px;text-align:center;font-family: 'Roboto Slab', serif;} #container{display:flex;overflow-x:auto;overflow-y:hidden;box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.1), 0 6px 20px 0 rgba(0, 0, 0, 0.1);} .item{border-right:2px dotted grey;height:200px} ::-webkit-scrollbar {width: 10px;} ::-webkit-scrollbar-track { background: #f1f1f1; border-radius:5px;} ::-webkit-scrollbar-thumb {background: #888; border-radius:5px;} ::-webkit-scrollbar-thumb:hover {background: #555; } </style> <title>Report</title> </head> <body> <section id=\"container\"> <div id=\"d1\" class=\"item\"></div> <div id=\"d2\" class=\"item\"></div> <div id=\"d3\" class=\"item\"></div> <div id=\"d4\" class=\"item\"></div> </div> </section> <p id=\"info\"> REPORT </p> <p id=\"status\"></p> </div> <script> google.charts.load('current',{packages:['corechart']}); google.charts.setOnLoadCallback(drawPie); google.charts.setOnLoadCallback(drawLine); google.charts.setOnLoadCallback(drawScatter); google.charts.setOnLoadCallback(drawBar); function drawPie(){ var onT=16; var offT=8; var pieD = google.visualization.arrayToDataTable([ ['distribution','duration'], ['onTime', onT], ['offTime',offT], ]); var pieOpt= { title:'Distribution', is3D:true }; var pie = new google.visualization.PieChart(document.getElementById('d1')); pie.draw(pieD, pieOpt); } var EleD=[ ['wh', 'period'], [50,7],[60,8],[70,8],[80,9],[90,9],[100,9], [110,10],[120,11],[130,14],[140,14],[150,15]]; var UsageD=[['Activation-Time', 'Day'], [50,7],[60,8],[70,8],[80,9],[90,9],[100,9], [110,10],[120,11],[130,14],[140,14],[150,15]]; var SavingsD=[['Month', 'Savings in wH','Temperature(Avg)'], ['Italy', 55,24], ['France', 49,22], ['Spain', 44,20.9], ['USA', 24,19], ['Argentina', 15,18] ]; function drawLine(){ var lineD = google.visualization.arrayToDataTable(EleD); var lineOpt = { title: 'Electricity saved vs offTime', hAxis: {title: 'Period-Day'}, vAxis: {title: 'Electricity-wH'}, legend: 'none' }; var line = new google.visualization.LineChart(document.getElementById('d2')); line.draw(lineD, lineOpt); } function drawScatter(){ var pointD = google.visualization.arrayToDataTable(UsageD); var pointOpt = { title: 'Activation-Time vs Day', hAxis: {title: 'Period-Day'}, vAxis: {title: 'Time-24H'}, legend: 'none' }; var point = new google.visualization.ScatterChart(document.getElementById('d3')); point.draw(pointD, pointOpt); } function drawBar(){ var barD = google.visualization.arrayToDataTable(SavingsD); var barOpt = { title: 'Savings' }; var bar = new google.visualization.BarChart(document.getElementById('d4')); bar.draw(barD, barOpt); } </script> </body> </html>"};
void Blink(){
  digitalWrite(led,   HIGH);   
  delay(500);                       
  digitalWrite(led, LOW);    
  delay(500);
}
void Ota(){
  ArduinoOTA.onStart([]() {
    Serial.println("Update Start");
    Blink();
  });
ArduinoOTA.onEnd([]() {
    Serial.println("Update \nEnd");
  });
 ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
}
void wifi(){
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  }
void ap(){
  Blink();
  Blink();
  Blink();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid_ap, password_ap);
  WiFi.softAPConfig(staticIP, gateway, subnet);
  }
void Index(){ 
  Blink();
  server.send(200,"text/html",index1);
  //server.send(200,"text/html",);
  Serial.println("Served Index");
}
void Report(){//check rem
  server.send(200,"text/html",rep1);//String(rep)+String(rep2)+String(rep3)); 
  Serial.println("Served report");
}
void Fromp(){
  server.send(200,"text/html",prog1+String(progPerc)+prog2);
  //server.send(200,"text/html",);
  //server.send(200,"text/html",prog2); 
}
void handleNotFound(){
  server.send(404, "text/plain", "404");
    Serial.println(404);
}
void Serv(){
  server.begin();
  server.on("/", Index);//
   server.on("/report/", Report);//
   server.on("/fromp/", Fromp);//
  server.onNotFound(handleNotFound);//
}  
void setup() {
  // put your setup code here, to run once:
 pinMode(pin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(pin, HIGH);
  pinMode(btn, INPUT);
  Serial.begin(74880);
  //wifii();
   Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  if(digitalRead(btn)==HIGH){
    ap();
    }
  else{wifi();} // manage sram plz
  Serv();
  Ota();
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
     ArduinoOTA.handle();
     digitalWrite(pin, HIGH);
     delay(200);
}
