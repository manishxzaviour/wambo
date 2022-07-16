//header
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//global var
IPAddress staticIP(192, 168, 0, 184);
IPAddress subnet(255, 255, 0, 0);
String ssid     = "M 2.4G ";
String password = "helloWorld11";
const char* ssid_ap   = "Wambo_ap";
const int pin = 5 ;
const int btn = 14;
const int led =12;
float RemT = 100;
double CT = millis();
float from;
float For;
int T = 0; //h*24*60*60*1000+m*60*1000
String GotData;
ESP8266WebServer server(80);

void Blink(){
  digitalWrite(led,   HIGH);   
  delay(500);                       
  digitalWrite(led, LOW);    
  delay(500);
}
void wifi(){
	WiFi.config(staticIP,staticIP,subnet);
	WiFi.begin(ssid,password);
	 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
	}
	 Serial.println(WiFi.localIP());
	 Blink();
}
void ap(){
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(staticIP, staticIP, subnet);
	WiFi.softAP(ssid_ap);
	Serial.println("AP_mode:");
	Serial.print(WiFi.localIP());
	Blink();
	Blink();
}
void ota(){
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
  ArduinoOTA.begin();
}
void rFile(char* f,int a){   //file name  0,1,2,3 <html,css,js,xml>
	  File file = SPIFFS.open(f, "r");
	  if (file){
  String s;
  while (file.available()){
            s += char(file.read());
          }
  switch(a){
	case 0:
		server.send(200, "text/html", s);
		break;
	case 1:
		server.send(200, "text/css", s);
		break;
	case 2:
		server.send(200, "text/javascript", s);
		break;
	case 3:
		server.send(200, "text/xml", s);
		break;
  }
  }
  else {
      server.send(200, "text/html", "Error: File does not exist");
  }
}
void hIndex(){
	rFile("/Index.html",0);
	Blink();
	Serial.println("Index");
}
void hSM(){
	rFile("/map.html",0);
	Serial.println("SM");
}
void hAbt(){
	rFile("/abt.html",0);
	Serial.println("abt");
}
void hRaw(){
	rFile("/Data.xml",3);
  Serial.println("RData");
}
void hMsg(){
	rFile("/Memmo.html",0);
	Serial.println("memmo");
}
void hMsgGot(){ // msg got  write to a xml and view it ?
}
void set(){ // handle set pause and resume function
}
void hGot(){
	Blink();
  if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
    rFile("/Ok.html",0);
    from = GotData.substring(GotData.indexOf("1=") + 2, GotData.indexOf("&")).toFloat(); //from1=00&for2=00
    For = GotData.substring(GotData.indexOf("2=") + 2, GotData.indexOf("&T")).toFloat();  //from1=0.0&for2=8.0&Time
    // handle date as well
    //from1=0.0&for2=8.0&t*=Fri+Jul+15+2022+14%3A11%3A57
    // Fri Jul 15 2022 14:16:58 : %3A
    Serial.println(GotData);
     delay(1000);
    set();
  }
}
void hReport(){
	rFile("/Report.html",0);
	Serial.println("Report");
}
void hReportGot(){ // handle weather
  
}
void hFromP(){
	rFile("/FromP.html",0);
}
void hUpd(){
	rFile("/Upd.html",0);
	Serial.println("Upd");
}
void hUpdGot(){ // upd got  js module
}
void hCss(){
	rFile("/index.css",1);
	Serial.println("css");
}
void hProgCss(){
	rFile("/Prog.css",1);
}
void hSced(){
	rFile("/Sced.js",2);
	Serial.println("js");
}
void hViz(){
	rFile("/viz.js",2);
	Serial.println("js");
}
void hNF(){
	server.send(404,"text/plain","404:FNF");
	Serial.println(404);
}
void handleRequest(){
    server.begin();
	server.on("/",hIndex);
	server.on("/sm/",hSM);
	server.on("/abt/",hAbt);
	server.on("/raw/",hRaw);
	server.on("/msg/",hMsg);
	server.on("/msg/a",hMsgGot);
	server.on("/wambo",hGot);
	server.on("/report/",hReport);
  server.on("/ref",hReportGot);
	server.on("/fromp/",hFromP);
	server.on("/upd/",hUpd);
	server.on("/css",hCss);
	server.on("/progcss",hProgCss);
	server.on("/scd",hSced);
	server.on("/viz",hViz);
	server.on("/upd/a",hUpdGot);
	server.onNotFound(hNF);
}
void setup() { 
	pinMode(pin,OUTPUT);
	pinMode(led,OUTPUT);
	pinMode(btn,INPUT);
	digitalWrite(pin, HIGH); 
	Serial.begin(115200);
	SPIFFS.begin();
	if(digitalRead(btn)==HIGH){
		ap();
	}
	else{wifi();}
	handleRequest();
	ota();
}
void loop() {
  server.handleClient();
  ArduinoOTA.handle();
  digitalWrite(pin, HIGH);  
}
