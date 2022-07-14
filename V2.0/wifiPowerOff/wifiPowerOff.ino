
// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
  IPAddress staticIP(192, 168, 0, 184);
  IPAddress subnet(255, 255, 0, 0);
 String ssid     = "M 2.4G ";
 String password = "helloWorld11";
const char* ssid_ap   = "Wambo_ap";
const char* password_ap = "244466666";
String GotData;
float from;
float For;
int T = 0; //h*24*60*60*1000+m*60*1000
const String Index = "<html> <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> <title> * wambo </title> <link href=\"https://fonts.googleapis.com/css2?family=Roboto+Slab:wght@700&family=Rubik:wght@300&family=Ubuntu:wght@500&display=swap\" rel=\"stylesheet\"> <style> #container table{display:inline-block;border-radius:6px; background-color:rgba(155,130,240,30%);padding:10px;align:center;margin:0px 20px; box-shadow: 3px 3px 5px lightblue;} #updi{height:28px;width:30px ;float:right;background-color:rgb(240,240,255);border:2px dotted gray;border-radius:5px;} #container table td {border-width:3px;border-color:rgba(195,175,220,80%);border-radius:6px;background-color:white;} #container2{background-color:rgba(150,255,235,35%);margin:0px;box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);} #input{border-color:rgba(21,152,252,80%);border-radius:3px;padding:5px; margin:15px auto; margin-top:0px;background-color:rgba(255,235,150,55%); margin:auto;} #input td{border-width:2px;border-color:rgba(203,152,255,80%);border-radius:3px;padding:3px;background-color:rgba(213,243,162,70%);background-size: 30px 30px;background-image: url('https://github.com/manishxzaviour/wambo/blob/2.0/zigzag-0.2s-1084px.png?raw=true');} #forIP,#fromIP{background-color:rgba(78,255,250,30%);color:rgba(130,55,255,80%);text-align:center;font-size:20px} #send{background-color:rgba(187,250,78,60%); border-radius:2px; border-color:rgba(176,230,198); color:rgb(90,30,90);width:60px;height:30px;background-size: 100% 100%;background-image: url('https://github.com/manishxzaviour/wambo/blob/2.0/Screenshot%202022-07-10%20184220.jpg?raw=true');} #T{width:235px;color:gray;background-color:aqua;border:2px dotted;border-radius:5px;float:right;padding:0px;margin-right:10%;px;} body{ margin:0px; font-family:arial; background-image: url('https://github.com/manishxzaviour/wambo/blob/2.0/zigzag-1s-1084px%20(1).png?raw=true'); background-size: 30px 30px; } .hdder{ background-color:rgba(25,255,255,70%); padding:15px; margin:0; box-shadow:0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); } .hdderWrapper{ font-family: 'Roboto Slab', arial,serif; color:rgba(80,120,120); font-size:35px; text-align:center; } .shadowLight{ box-shadow:0 4px 5px 0 rgba(100, 100, 100, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19); } .genericText{ font-size:20px; font-family:'Rubik',sans-serif; } </style> </head> <body> <form action=\"/response\" method=\"post\" name=\"f1\" id=\"f1\"> <div class=\"hdder\"> <h2 class=\"hdderWrapper\">WamBo</h2> </div> <fieldset style=\"margin-top:1%;background-color:#fceaea\"> <div id=\"container2\"> <table id=\"input\" border=\"3px\" class=\"shadowLight genericText\" width=\"300px\"> <tr> <th> <label>From:&nbsp;</label><input list=\"selF\" type=\"text\"name=\"from1\" id=\"fromIP\" maxlength=\"6\"style=\"width:50%;\" placeholder=\"0.0\" value=\"0.0\"> <datalist id=\"selF\" > <option value=0.0></option> <option value=0.3></option> <option value=1.0></option> <option value=1.3></option> <option value=2.0></option> <option value=2.3></option> <option value=3.0></option> <option value=4.0></option> <option value=6.0></option> <option value=7.0></option> <option value=8.0></option> <option value=10.0></option> </datalist> </th></tr> <tr><td>&nbsp;</td><td><input type=\"submit\" value=\"&nbsp;&nbsp;&nbsp;>&nbsp;&nbsp;&nbsp;\" id=\"send\"></td></tr> <tr><th><label>&nbsp;For:&nbsp;&nbsp;&nbsp;</label><input list=\"selF\" type=\"text\"name=\"for2\" maxlength=\"6\" id=\"forIP\" placeholder=\"8.0\" style=\"width:50%;\" value=\"8.0\"></th></tr> </table> <input name=\"Time\" id=\"T\" class=\"shadowLight genericText\"></input> <image src=\"https://raw.githubusercontent.com/manishxzaviour/wambo/v1.3/UPD.png\" id=\"updi\" title=\"UPDATE\" class=\"shadowLight\"> <ul style=\"display:block\"> <li><label class=\"genericText\">SSID:</label><input type=\"text\" name=\"SSID\" id=\"ssid\"value=\"000\" maxlength=\"25\"></li> <li><label class=\"genericText\">PWD:</label><input type=\"text\"name=\"PWD\" id=\"pwd\" value=\"000\" maxlength=\"12\"></li> </ul> <script language=\"javascript\"> var dateTime= new Date(); document.getElementById(\"T\").value=dateTime; function refT() { var ref=String(new Date()); document.getElementById(\"T\").value=ref.substring(0,24); } setInterval(refT,1000); var sendB=document.getElementById(\"send\"); function sendC(){ document.getElementById(\"input\").style=\"background-color:#00ff00\"; } var frm=document.getElementById(\"fromIP\"); var till=document.getElementById(\"forIP\"); frm.onfocus=function(){ frm.value=''; } till.onfocus=function(){ till.value=''; } var SSID_I=document.getElementById(\"ssid\"); var PWD_I=document.getElementById(\"pwd\"); function x(){ SSID_I.value=SSID_I.value.trim(); PWD_I.value=PWD_I.value.trim(); console.log(SSID_I.value+\"\n\"+PWD_I.value); } SSID_I.onblur=x; PWD_I.onblur=x; </script> </form> </body> </html>";
ESP8266WebServer server(80);

const int pin = 5 ;
const int btn = 14;
const int led =12;
float RemT = 100;
// Current time
double CT = millis();
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(404);
}
void set() {
  double x = from * 60 * 60 * 1000;
  Serial.println(x);
  CT = millis();
   digitalWrite(pin, HIGH); 
  for ( uint32_t tStart = millis();  (millis() - tStart) < x;) {
    RemT = ((millis() - CT) / x) * 100;
    //Serial.println(millis()-CT);
      Serial.println(RemT);
      //server.send(200, "text/html", Html1+"display:none;"+Html2 + progress + String((100 - RemT)) + "%" + "; background-color:#52ff52; color:white; Text-align:center\">" + String(RemT) + "</div></div>" + Html3);
  }
  x = For * 60 * 60 * 1000;
  Serial.println(x);
  CT = millis();  
  WiFi.mode(WIFI_OFF);
  for ( uint32_t tStart = millis();  (millis() - tStart) < x;) {
    RemT = ((millis() - CT) / x) * 100;
    // Serial.println(millis()-CT);
      Serial.println(RemT);
    //server.send(200, "text/html", Html1+Html2 + progress + String(RemT) + "%" + "; background-color:#52ff52; color:#white; Text-align:center\">"+String(RemT) + "</div></div>" + Html3);
    digitalWrite(pin, LOW); 
  }
 digitalWrite(pin, HIGH); 
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, staticIP, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}}
void Blink(){
  digitalWrite(led,   HIGH);   
  delay(500);                       
  digitalWrite(led, LOW);    
  delay(500);
}
void root() {
  Serial.println("Served");
  server.send(200, "text/html", Index);
}
void GOT() {
    Blink();
  if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
    server.send(200, "text/html","<Html><head><title><Sent></title><head><body bgcolor=\"#4AFF6D\"></body></html>");
    from = GotData.substring(GotData.indexOf("1=") + 2, GotData.indexOf("&")).toFloat(); //from1=00&for2=00
    For = GotData.substring(GotData.indexOf("2=") + 2, GotData.indexOf("&T")).toFloat(); //from1=00&for2=00   //from1=0.0&for2=8.0&Time=&SSID=000&PWD=000
    Serial.println(GotData);
    String Ssid=GotData.substring(GotData.indexOf("SSID=") + 5, GotData.indexOf("&PWD"));
    String Pwd=GotData.substring(GotData.indexOf("PWD=") + 4, GotData.length());
    Serial.println(Ssid);    Serial.println(Pwd);
    //Serial.println("from ="+String(from));
    //Serial.println("T ="+String(T));
     // Serial.println("for ="+String(For));
     delay(1000);
    set();
  }
}
void Ota(){
  ArduinoOTA.onStart([]() {
    Serial.println("Update Start");
    Blink();
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("Update \nEnd");
    Blink();
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
  ArduinoOTA.begin();}
 void wifi(){
    Serial.println(ssid);
      WiFi.config(staticIP, staticIP, subnet);
  WiFi.begin(ssid, password);
  WiFi.setAutoReconnect(true);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  }
  void ap(){
    delay(1000);
  Blink();
  Blink();
  Blink();
  Serial.println("AP_mode");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(staticIP, staticIP, subnet);
  WiFi.softAP(ssid_ap, password_ap);
  }
void setup() {
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
    pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
  digitalWrite(pin, HIGH); 
  Serial.print("Connecting to ");
  if(digitalRead(btn)==HIGH){ap();}
  else{wifi();}
  Serial.println(WiFi.localIP());
  server.begin();
  server.on("/", root);
  server.on("/response", GOT);
  server.onNotFound(handleNotFound);
  Ota();
}

void loop() {
  server.handleClient();
   ArduinoOTA.handle();
  digitalWrite(pin, HIGH);  
}
