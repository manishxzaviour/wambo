/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/

// Load Wi-Fi library

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
const char* ssid     = "M 2.4G ";
const char* password = "helloWorld11";
// Replace with your network credentials

String GotData;
float from;
float For;
int T = 0; //h*24*60*60*1000+m*60*1000

const String Html1 = "<html><head><title>* Keep-Off-For</title></head><body bgcolor=\"#e7f5f5\"><form action=\"/a1\" method=\"post\" ><fieldset style=\"border-radius:5px;margin-top:5%;background-color:#d9f4fc\"><div style=\"display:block;margin-left: auto; margin-right: auto; width:145px\"><legend style=\"font-size:18px;font-style:bold\">Keep-Off-For<input type=\"submit\" style=\"font-size:14px; border-radius:8px; border-color:#2e0000;background-color:#fbeaf2;";
const String Html2="\"value=\"{o}\"></input></legend></div></fieldset> <fieldset style=\"margin-top:1%;background-color:#fceaea\"><div style=\"display: block;background-color:#e8c1e8; color:#002e00;margin-left: auto;margin-right: auto;width: 115px;padding:8px;border-radius:3px\"><label>from</label><input list=\"selF\" name=\"from1\" id=\"fromIP\"style=\"width:48px;\" placeholder=\"00\"></input><datalist id=\"selF\" ><option value=0.0></option><option value=0.3></option><option value=1.0></option><option value=1.3></option><option value=2.0></option><option value=2.3></option><option value=3.0></option><option value=4.0></option></datalist><button id=\"from\"style=\"color:#ffe552; background-color:#d600d6\"><</button></div>";
const String progress = "<div style=\"margin-left: auto; margin-right: auto; border-radius:15px; width:230px; background-color:#969696 ; margin-top:7px\"><div style=\"border-radius:15px; width:";
const String Html3 = "<div style=\"display: block;background-color:#eadbc8;color:#002e00;margin-left: auto;margin-right: auto;width: 100px;padding:3px;margin-top:7px\"><label>for</label><input list=\"forL\" name=\"for2\" id=\"forIP\"style=\"width:48px;\" placeholder=\"00\"></input><datalist id=\"forL\" ><option value=8.0></option><option value=7.0></option><option value=6.0></option><option value=1.3></option><option value=2.0></option><option value=2.3></option><option value=3.0></option><option value=4.0></option></datalist><button id=\"from\"style=\"color:#ebebeb; background-color:#00d6d6\">></button></div></input></fieldset><input type=\"time\" name=\"Time\" id=\"T\"></input><script>var a= new  Date();document.getElementById(\"T\").value = a.getHours()+\":\"+a.getMinutes();</script></form></body></html>";
String header;

// Auxiliar variables to store the current output state
ESP8266WebServer server(80);
void Blink(){
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(500);                       
  digitalWrite(LED_BUILTIN, LOW);    
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
const int pin = 5 ;
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
  IPAddress staticIP(192, 168, 0, 184);
  IPAddress gateway(192, 168, 0, 101);
  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}}
void root() {
  Serial.println("Served");
  server.send(200, "text/html", Html1+Html2 + progress + 100 + "%" + "; background-color:#52ff52; color:#52ff52\">.</div></div>" + Html3);
}
void GOT() {
  if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
    server.send(200, "text/html","<Html><head><title><Sent></title><head><body bgcolor=\"#4AFF6D\"></body></html>");
    from = GotData.substring(GotData.indexOf("1=") + 2, GotData.indexOf("&")).toFloat(); //from1=00&for2=00
    For = GotData.substring(GotData.indexOf("2=") + 2, GotData.indexOf("&T")).toFloat(); //from1=00&for2=00   //from1=00&for2=00&Time=16%3A36
    Serial.println(GotData);
    T = GotData.substring(GotData.indexOf("e=") + 2, GotData.indexOf('%')).toInt() * 60 * 60 * 1000 + GotData.substring(GotData.indexOf('A') + 1).toInt() * 60 * 1000; //h*60*60*1000+m*60*1000
    //Serial.println("from ="+String(from));
    ////Serial.println("T ="+String(T));
     // Serial.println("for ="+String(For));
     delay(1000);
    set();
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH); 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  IPAddress staticIP(192, 168, 0, 184);
  IPAddress gateway(192, 168, 0, 101);
  IPAddress subnet(255, 255, 0, 0);
  IPAddress primaryDNS(8, 8, 8, 8);   //optional
  IPAddress secondaryDNS(8, 8, 4, 4);
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
  server.begin();
  server.on("/", root);
  server.on("/a1", GOT);
  server.onNotFound(handleNotFound);
}

void loop() {
  server.handleClient();
  digitalWrite(pin, HIGH);  
     ArduinoOTA.handle();
}
