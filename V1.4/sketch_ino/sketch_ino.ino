
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
const char* ssid     = "wifi ";
const char* password = "password";
const char* ssid_ap     = "Wambo_ap";
const char* password_ap = "password";
const int pin = 5 ;
float RemT = 100;
// Current time
double CT = millis();
String GotData;
float from;
float For;
int T = 0; //h*24*60*60*1000+m*60*1000
String header;
float ProgPerc = 0;
const String ok = "<Html><head><title><Sent></title><head><body bgcolor=\"#4AFF6D\"></body></html>";
// html
//ABOUT PAGE
const char Abt[] PROGMEM = R"rawliteral(
<title>
About
</title>
  <link rel="preconnect" href="https://fonts.googleapis.com">
  <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
  <link href="https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&family=Rubik:wght@300&family=Ubuntu:wght@500&display=swap" rel="stylesheet">
  <meta name="viewport" content="width=device-width, initial-scale=1">
<style>
body{
margin:0px;
background-color:rgba(255,185,185,10%);
font-family:arial;
overflow:hidden;
}
.hdder{
background-color:rgba(25,255,255,65%); 
padding:15px; 
margin:0; 
box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
}
.hdderWrapper{
font-family: 'Roboto Slab', arial,serif;
color:rgba(80,120,120);
font-size:35px;
text-align:center;
}
.shadowLight{
  box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
}
.genericText{
font-size:20px;
font-family:'Rubik',sans-serif;
display:inline-block;
}
</style>
</head>
<body>
  <div class="hdder">
  <h2 class="hdderWrapper">WamBo</h2></div> 
  <br>
  <br>
  <br>
  <p>
    <em><h3 class="shadowLight genericText hdderWrapper">About</h3></em>
  </p>
    <h3><pre class="genericText shadowLight hdderWrapper">
        <u><i>Motive</i></u>&nbsp;:  To&nbsp;save&nbsp;Power through reducing on time of wifi router <br>
        <u><i>Methodology</i></u>&nbsp;:  Cut off power when user determines or through triggers in scheduled timetable<br>
        <u><i>Supplimentry</i></u>&nbsp;:  <ul class="genericText"style="list-style-type:none"><li>E-memo and schedule&nbsp;table,</li><li>Reports&nbsp;and&nbsp;visualisation for tracking overall power saved based on static constants, </li><li>To update firmware wirelessly</li></ul>
    </pre></h3>
<body>
</body>
</html>
)rawliteral";
//SiteMap PAGE
const char sm[] PROGMEM =R"rawliteral(
<html>
  <head>
    <title>
      SiteMap
    </title>
    <style>
      #map{margin-left:40%;padding:100px}
    </style>
    <link rel="stylesheet" type="text/css" href="index.css">
  </head>
  <body>
  <ul id="map" class="genericText" style="color:red;font-style:italic;">
    <li><a href="/">&#47;</a></li>
    <br>
    <li><a href="/sm">&#47;sm&#47;</a></li>
    <br>
    <li><a href="/raw">&#47;raw&#47;</a></li>
    <br>
    <li><a href="/msg/">&#47;msg&#47;</a></li>
    <br>
    <li><a href="/upd">&#47; upd&#47;</a></li>
    <br>
    <li><a href="#">&#47; wambo&#47;</a></li>
    <br>
    <li><a href="/a/report">&#47;report&#47;</a></li>
    <br>
    <li><a href="/fromp">&#47;fromp&#47;</a></li>
    <br>
    <li><a href="/abt">&#47;abt&#47;</a></li>
  </ul>
  </body>
</html>
)rawliteral";
//From_Progress page
const String Progr1 = "<html> <head> <META HTTP-EQUIV=\"Refresh\" CONTENT=5> <style> body{margin:0px;background-color:rgba(0,140,255,0.4);} #fp{border-radius:20px;background-color:rgba(255,255,200,0.45);box-shadow: 0px 1px 10px silver;height:";
const String Progr2 = ";width:100%} </style> </head> <body> <div id=\"fp\" title=\"From countdown\"> </div> </body> </html>";
// Update PAGE
const char Upd[] PROGMEM = R"rawliteral(
<html>
  <head>
    <title>
      Update Scedule
    </title>
    <meta name="viewport" content="width=device-width, initial-scale=1"><!---edit for mobile compatible-->
  <link rel="stylesheet" type="text/css" href="index.css">
  </head>
  <body>
  <div class="hdder">
  <h2 class="hdderWrapper">WamBo</h2></div>
  <br>
  <br>
  <div align="center">
  <p class="genericText">
    <em><h3>Update</h3></em>
  </p>
  <form action="/upd/a" method="post"><table border="3px" border-color="silver" align="center" class="genericText shadowLight">
              <tr><td><input type="button" id="rst" value="RESET"></td><td id="day" style="text-align:center">Schedule</td></tr>
              <tr><td>4_6</td><td class="sced"><input type="text" value="***************" id="4_6"  name="4_6"><td><input type="button" value="^" id="u4_6"></td></td></tr>
              <tr><td>6_8</td><td class="sced"><input type="text" value="***************" id="6_8" name="6_8"><td><input type="button" value="^" id="u6_8"></td></td></tr>
              <tr><td>8_10</td><td class="sced"><input type="text" value="***************" id="8_10" name="8_10"><td><input type="button" value="^" id="u8_10"></td></td></td></tr>
              <tr><td>10_12</td><td class="sced"><input type="text" value="***************" id="10_12" name="10_12"><td><input type="button" value="^" id="u10_12"></td></td></tr>
              <tr><td>12_14</td><td class="sced"><input type="text" value="***************" id="12_14" name="12_14"><td><input type="button" value="^" id="u12_14"></td></td></tr>
              <tr><td>14_16</td><td class="sced"><input type="text" value="***************" id="14_16" name="14_16"><td><input type="button" value="^" id="u14_16"></td></td><td><input type="submit" value="UPDATE" id="upd" name="*upd"></td></tr>
              <form><tr><td>16_18</td><td class="sced"><input type="text" value="***************" id="16_18" name="16_18"></td><td><input type="button" value="^" id="u16_18"></td><td><input type="submit" value="PAUSE" id="pus" name="*pause"></td></tr></form>
              <tr><td>18_20</td><td class="sced"><input type="text" value="***************" id="18_20" name="18_20"><td><input type="button" value="^" id="u18_20"></td></td></tr>
              <tr><td>20_22</td><td class="sced"><input type="text" value="***************" id="20_22" name="20_22"><td><input type="button" value="^" id="u20_22"></td></td></tr>
              <tr><td>22_24</td><td class="sced"><input type="text" value="***************" id="22_24" name="22_24"><td><input type="button" value="^" id="u22_24"></td></td></tr>
              <tr><td>24_2</td><td class="sced"><input type="text" value="***************" id="24_2" name="24_2"><td><input type="button" value="^" id="u24_2"></td></td></tr>
            </table>
        <div class="hdderWrapper genericText shadowLight">
        <input type="text" name="*Check" id="x" style="display:none" value="0000">
        <input type="text" placeholder="Price per KwH" name="ElecticPrice" onchange="ud()">
        <br>
        <br>
        <input type="text" placeholder="SSID"name="*SSID" onchange="ud()"><input type="password" placeholder="Password" name="*ElecticPrice" onchange="ud()">
        <br>
        <br>
        <label>Reset?&nbsp;&nbsp;</label>Y:<input type="radio" name="reset" value="Yes">N:<input type="radio" name="reset" value="No" checked>
        </div>
  </form>
  </div>
    <script lang="javascript">
    function updt(a){
        a.value=prompt("two hours scedule","***************");
       }
       function rst(){
       document.getElementById("4_6").value="***************";
       document.getElementById("6_8").value="***************";
       document.getElementById("8_10").value="***************";
       document.getElementById("10_12").value="***************";
       document.getElementById("12_14").value="***************";
       document.getElementById("14_16").value="***************";
       document.getElementById("16_18").value="***************";
       document.getElementById("18_20").value="***************";
       document.getElementById("20_22").value="***************";
       document.getElementById("22_24").value="***************";
       document.getElementById("24_2").value="***************";
       }
       document.getElementById("u4_6").onclick=function(){updt(document.getElementById("4_6"));};
       document.getElementById("u6_8").onclick=function(){updt(document.getElementById("6_8"));};
       document.getElementById("u8_10").onclick=function(){updt(document.getElementById("8_10"));};
       document.getElementById("u10_12").onclick=function(){updt(document.getElementById("10_12"));};
       document.getElementById("u12_14").onclick=function(){updt(document.getElementById("12_14"));};
       document.getElementById("u14_16").onclick=function(){updt(document.getElementById("14_16"));};
       document.getElementById("u16_18").onclick=function(){updt(document.getElementById("16_18"));};
       document.getElementById("u18_20").onclick=function(){updt(document.getElementById("18_20"));};
       document.getElementById("u20_22").onclick=function(){updt(document.getElementById("20_22"));};
       document.getElementById("u22_24").onclick=function(){updt(document.getElementById("22_24"));};
       document.getElementById("u24_2").onclick=function(){updt(document.getElementById("24_2"));};
       document.getElementById("rst").onclick=function(){rst();};
       function ud(){
         document.getElementById("x").value="1111";
       }
    </script>
  </body>
</html>
)rawliteral";
// Raw PAGE
const char Raw[] PROGMEM =R"rawliteral(
<html>
<head>
<title>
Raw
</title>
<style>
.frame{border:3px dotted white;}
</style>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="preconnect" href="https://fonts.googleapis.com">
<link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link href="https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&family=Rubik:wght@300&family=Ubuntu:wght@500&display=swap" rel="stylesheet">
<link rel="stylesheet" type="text/css" href="index.css">
</head>
<body>
  <div class="hdder">
  <h2 class="hdderWrapper">WamBo</h2>
  </div>
  <br>
  <br>
  <br>
  <p>
    <em><h3 class="shadowLight genericText">RAW Data</h3></em>
  </p>
  <p align="center">
    <frameset cols="2">
      <iframe src="/raw/tON" title="tON" width="48%" height="50%" id="tON" class="shadowLight frame"></iframe>
      <iframe src="/raw/tOFF" title="tOFF" width="48%"height="50%" id="tOFF" class="shadowLight frame"></iframe>
    </frameset>
  </p>
  <i align="right"><h5 id="info" class="shadowLight genericText">INFO</h5></i>
<script lang="javascript">
var  ton= document.getElementById("tON");
ton.onmouseover= function(){over1()};
ton.onmouseout= function(){out()};
var  toff= document.getElementById("tOFF");
toff.onmouseover= function(){over2()};
toff.onmouseout= function(){out()};
function over1(){
info.textContent="tON";
}
function out(){
info.textContent="INFO";
}
function over2(){
info.textContent="tOFF";
}
</script>
<body>
</body>
</html>)rawliteral";

//html
ESP8266WebServer server(80);
IPAddress staticIP(192, 168, 0, 184);
IPAddress gateway(192, 168, 0, 101);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);  
IPAddress secondaryDNS(8, 8, 4, 4);
void Blink(){
  digitalWrite(LED_BUILTIN, LOW);   
  delay(500);                       
  digitalWrite(LED_BUILTIN, HIGH);    
  delay(500);
}
void Ota(){
  ArduinoOTA.onStart([]() {
    Serial.println("Update Start");
    Blink();
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
void Router(){
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
WiFi.setAutoReconnect(true);
WiFi.config(staticIP, gateway, subnet);
while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 Serial.println("");
 Serial.println("WiFi connected.");
 Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void AccesP(){
  Blink();
  Blink();
  Blink();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(staticIP, gateway, subnet);
  WiFi.softAP(ssid_ap, password_ap);
  // add code to connect as a acess Point
  //psw same as phone 244466666
}
void handleNotFound() {
  server.send(404, "text/plain", "404");
  Serial.println(404);
}
void GOT() {
  if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
    server.send(200, "text/html",ok);
    from = GotData.substring(GotData.indexOf("from*=") + 6, GotData.indexOf("&")).toFloat(); //from*=00&for*=00
    For = GotData.substring(GotData.indexOf("for*=") + 2, GotData.indexOf("&t*")).toFloat(); //from**=00&for*=00   //from1=00&for2=00&Time=16%3A36
    Serial.println(GotData);
    T = GotData.substring(GotData.indexOf("e=") + 2, GotData.indexOf('%')).toInt() * 60 * 60 * 1000 + GotData.substring(GotData.indexOf('A') + 1).toInt() * 60 * 1000; //h*60*60*1000+m*60*1000
    //Serial.println("from ="+String(from));
    ////Serial.println("T ="+String(T));
     // Serial.println("for ="+String(For));
     delay(1000);
    //set(); // add set
  }
}
void progr(){
  server.send(200, "text/html",Progr1+String(ProgPerc)+"%"+Progr2);
}
void Map(){
    Serial.println("Served : SiteMap");
    server.send(200, "text/html",sm); 
}
void abt(){
  Serial.println("Served : About");
  server.send(200, "text/html",Abt); 
}
void upd(){
  Serial.println("Served : Update");
  server.send(200, "text/html",Upd); 
}
void raw(){
  Serial.println("Served : RAW");
  server.send(200, "text/html",Raw); 
}
void Serv(){
  server.begin();
  server.on("/", Index);
  server.on("/raw/", raw);//
  //server.on("/raw/tON", rawOn);
  //server.on("/raw/tOFF", rawOff);
  //server.on("/msg/", msg);
  //server.on("/upd/a", updGOT);
  server.on("/upd/", upd);//
  //server.on("/report/", report);
  server.on("/fromp/", progr);//
  server.on("/abt/", abt);//
  server.on("/sm/", Map);//
  //server.on("/wambo/", GOT);
  server.onNotFound(handleNotFound);
}
void setup() {
pinMode(LED_BUILTIN, OUTPUT);
pinMode(14, INPUT);
Serial.begin(74880);
Ota();
if(digitalRead(14)==HIGH)
{
  AccesP();
  }
 else{
  Router();
  }
Serv();
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();
  digitalWrite(pin, HIGH);
}
