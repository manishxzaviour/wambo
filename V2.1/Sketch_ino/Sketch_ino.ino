//spiffs test
#include <FS.h>
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
ESP8266WebServer server(80);
void wifi(){
	WiFi.config(staticIP,staticIP,subnet);
	WiFi.begin(ssid,password);
	 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println(WiFi.localIP());
  }
}
void rFile(char* f){
	  File file = SPIFFS.open(f, "r");
	  if (file){
  String s;
  while (file.available()){
            s += char(file.read());
          }
  server.send(200, "text/html", s);
  }
  else {
      server.send(200, "text/html", "Error: File does not exist");
  }
}
void hIndex(){
	rFile("/Index.html");
}
void hNF(){
	server.send(200,"text/html","404:FNF");
}
void handleRequest(){
    server.begin();
	server.on("/",hIndex);
	server.on("/sm/",hSM);
	server.on("/abt/",hAbt);
	server.on("/raw/",hRaw);
	server.on("/raw/tonn",hRawOn);
	server.on("/raw/toff",hRawOff);
	server.on("/raw/tempr",hRawTemp);
	server.on("/msg/",hMsg);
	server.on("/msg/a",hMsgGot);
	server.on("/wambo",hGot);
	server.on("/report/",hReport);
	server.on("/fromp/",hFromP);
	server.on("/upd/",hUpd);
	server.on("/upd/a",hUpdGot);
	server.onNotFound(hNF);
}
void setup() { 
	Serial.begin(115200);
	SPIFFS.begin();
	wifi();
	handleRequest();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
