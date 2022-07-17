
	#include <FS.h>
	#include <ESP8266WiFi.h>
	#include <WiFiClient.h>
	#include <ESP8266WebServer.h>
	#include <ESP8266mDNS.h>
	#include <WiFiUdp.h>
	#include <ArduinoOTA.h>
IPAddress staticIP(192, 168, 0, 184);
IPAddress subnet(255, 255, 0, 0);
String ssid;
String password ;
const char* ssid_ap   = "Wambo_ap";
const int pin = 5 ;
const int btn = 14;
const int led =12;
float RemT = 0;
double CT = millis();
float from;
float For;
String date;
String timeH;
int T = 0; //h*24*60*60*1000+m*60*1000
int scedule[]={0,0,0,0,0,0,0,0,0,0,0};
String GotData;
int EleRate;
int EleSupply;
String xS="<";
String xC=">";
String xE="</";
String xPC="</data>";
String weather;
int ton=0;
int toff=0;
float savedE=0;
float savedM=0;
char xCh[][10]={"D","from","for","ton","toff","rate","supply","savedE","savedM","date","weather"};
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
    Serial.println(ssid);
  Serial.println(password);
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
void rFile(char* f,int a){   //file name  0,1,2,3,4 <html,css,js,xml,text>
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
		server.send(200, "text/xml", s+xPC);
		break;
	case 4:
		server.send(200, "text/plain", s);
		break;
  }
  file.close();
  }
  else {
      server.send(200, "text/html", "Error: File does not exist");
  }
}
void wFile(int m, String d){	// write file f d 0,1,2, xml txt js
	switch (m){
  case 0:
    {
	//save without closing root sent seperate closing root tag
	File file=SPIFFS.open("/Data.xml", "a");
	file.println(xS+xCh[0]+xC);
	file.println(xS+xCh[1]+xC);file.print(from);file.print(xE+xCh[1]+xC);
	file.println(xS+xCh[2]+xC);file.print(For);file.print(xE+xCh[2]+xC);
	file.println(xS+xCh[3]+xC);file.print(ton);file.print(xE+xCh[3]+xC);
	file.println(xS+xCh[4]+xC);file.print(toff);file.print(xE+xCh[4]+xC);
	file.println(xS+xCh[5]+xC);file.print(EleRate);file.print(xE+xCh[5]+xC);
	file.println(xS+xCh[6]+xC);file.print(EleSupply);file.print(xE+xCh[6]+xC);
	file.println(xS+xCh[7]+xC);file.print(savedE);file.print(xE+xCh[7]+xC);
	file.println(xS+xCh[8]+xC);file.print(savedM);file.print(xE+xCh[8]+xC);
	file.println(xS+xCh[9]+xC);file.print(date);file.print(xE+xCh[9]+xC);
	file.println(xS+xCh[10]+xC);file.print(weather);file.print(xE+xCh[10]+xC);
	file.println(xE+xCh[0]+xC);
	file.close();
    break;}
  case 1:
    {File file = SPIFFS.open("/memmo.txt", "w");
    file.print(d);
    file.close();
    break;}
	case 2:
	  {File file = SPIFFS.open("/Sced.js", "w");
	  file.print("var scedule=[");
    for(int x=0;x<11;x++){
      file.print(scedule[x]);
      file.print(',');
    }
    file.print("];");
	  file.println("export default scedule;");
	  file.close();
		break;}
	}
}
void hIndex(){
	rFile("/Index.html",0);
	Blink();
	Serial.println("Index");
}
void hIndexJs(){
	rFile("/index.js",2);
}
void hScedJs(){
	rFile("/Sced.js",2);
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
void hMsgGot(){ 
	if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
    rFile("/Ok.html",0);
	//memmo=manish+%0D%0Apatil%0D%0A+++++pqrst
	//< > . , [ ] { } ! @ # $ % ^ & * ( ) - _ + / \ ` ~
	//%3C %3E . %2C %5B %5D %7B %7D %21 %40 %23 %24 %25 %5E %26 * %28 %29 - _ %2B %2F %5C %60 %7E
	char to[][25]={"<",">",",","[","]","{","}","!","@","#","$","%","^","&","(",")","+","/","\\","`","~","\"","\'","=",":"};
	char frm[][25]={"%3C","%3E","%2C","%5B","%5D","%7B","%7D","%21","%40","%23","%24","%25","%5E","%26","%28","%29","%2B","%2F","%5C","%60","%7E","%22","%27","%3D","%3A"};
	GotData=GotData.substring(6,GotData.length());
  GotData.replace('+',' ');
	for(int x=0;x<25;x++){GotData.replace(frm[x],to[x]);}
	GotData.replace("%0D%0A","\n");
    Serial.println(GotData);
    wFile(1,GotData);	
  }
}
void hMsgC(){
	rFile("/memmo.txt",4);
}
void set(){ 
  double x = from * 60 * 60 * 1000;
  Serial.println(x);
  CT = millis();
   digitalWrite(pin, HIGH); 
	WiFi.mode(WIFI_OFF);
  for ( uint32_t tStart = millis();  (millis() - tStart) < x;) {
    RemT = ((millis() - CT) / x) * 100;
      Serial.println(RemT);
  }
  x = For * 60 * 60 * 1000;
  Serial.println(x);
  CT = millis();  
  for ( uint32_t tStart = millis();  (millis() - tStart) < x;) {
    RemT = ((millis() - CT) / x) * 100;
    Serial.println(RemT);
    digitalWrite(pin, LOW); 
  }
 digitalWrite(pin, HIGH); 
  WiFi.mode(WIFI_STA);  
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, staticIP, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
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
    //from1=0.0&for2=8.0&d=16-06-2022&t=Sat+Jul+16+2022+15%3A10%3A02
    // Fri Jul 15 2022 14:16:58 : %3A
	date=GotData.substring(GotData.indexOf("&d=")+3,GotData.indexOf("&t"));
	timeH=GotData.substring(GotData.length()-12,GotData.length());
	timeH.replace("%3A",":");
    Serial.println(GotData);
	wFile(0," ");
    set();
  }
}
void hReport(){
	rFile("/Report.html",0);
	Serial.println("Report");
}
void hTonToff(){
	rFile("/tontoff.js",2);
}
void hUsageData(){
	rFile("/UsageData.js",2);
}
void hSavingsData(){
	rFile("/SavingsData.js",2);
}
void hSend(){
	rFile("/send.js",2);
}
void hDraw(){
	rFile("/draw.js",2);
}
void hReportGot(){ 
  if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
    Serial.println(GotData);
	  server.send(200,"text/plain","got weather");
	  weather=(GotData=="")?"no internet":GotData;
  }
}
void hUpd(){
	rFile("/Upd.html",0);
	Serial.println("Upd");
}
void hUpdGot(){ 
if (server.method() != HTTP_POST) {
    Serial.println(405);
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else {
    Serial.println("GOT");
    GotData = server.arg("plain");
	//04_06=on&06_08=on&08_10=on&10_12=on&12_14=on&14_16=on&16_18=on&18_20=on&20_22=on&22_24=on&24_02=on&*Check=1111&ElectricPrice=10&ElectricSupply=20&SSID=000&PWD=12345678&reset=N
    char s[][12]={"04_06","06_08","08_10","10_12","12_14","14_16","16_18","18_20","20_22","22_24","24_02","*Check"};
	for(int x=0;x<11;x++){
		if(GotData.substring(GotData.indexOf(s[x])+6,GotData.indexOf(s[x+1])-1)=="on"){ 
			scedule[x]=1;
		}
		else{scedule[x]=0;}	
	}
	if(GotData.substring(GotData.indexOf("reset")+6,GotData.length())=="Y"){
		File file = SPIFFS.open("/Data.xml", "w");
		file.print("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
		file.println("<data>");
		file.close();
		Serial.println("Reset");
	}
	if(GotData.substring(GotData.indexOf("Check")+6,GotData.indexOf("ElectricPrice")-1)=="1111"){
		 EleRate=GotData.substring(GotData.indexOf("Price")+6,GotData.indexOf("ElectricSupply")-1).toInt();
		 EleSupply=GotData.substring(GotData.indexOf("Supply")+7,GotData.indexOf("SSID")-1).toInt();
		String z=GotData.substring(GotData.indexOf("SSID")+5,GotData.indexOf("PWD")-1);
		String w=GotData.substring(GotData.indexOf("PWD")+4,GotData.indexOf("reset")-1);
		File file = SPIFFS.open("/const.txt", "w");
		if(!w<8){
			file.print("//ssid//");
			file.print(z);
			file.print("//pwd//");
			file.print(w);
			file.print("//end");
			};
		file.print("//EleR//");
		file.print(EleRate);
		file.print("//EleSuply//");
		file.print(EleSupply);
		file.print("//eend");
      	file.close();
	}
  	Serial.println(GotData.substring(GotData.indexOf("Check")+6,GotData.indexOf("ElectricPrice")-1));
	Serial.println(GotData);
  	//for(int x=0;x<11;x++){Serial.print(scedule[x]);}
	wFile(2," ");
	rFile("/Ok.html",0);	
  }
}
void hCss(){
	rFile("/index.css",1);
	Serial.println("css");
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
	server.on("/indexjs",hIndexJs);
	server.on("/Sced",hScedJs);
	server.on("/sm/",hSM);
	server.on("/abt/",hAbt);
	server.on("/raw/",hRaw);
	server.on("/msg/",hMsg);
	server.on("/msg/a",hMsgGot);
	server.on("/memmo",hMsgC);
	server.on("/wambo",hGot);
	server.on("/report/",hReport);
	server.on("/tontoff",hTonToff);
	server.on("/UsageData",hUsageData);
	server.on("/SavingsData",hSavingsData);
	server.on("/draw",hDraw);
	server.on("/send",hSend);
 	server.on("/ref",hReportGot);
	server.on("/upd/",hUpd);
	server.on("/css",hCss);
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
	File file = SPIFFS.open("/const.txt", "r");
	String s;
  	while (file.available()){
            s += char(file.read());
          }
	ssid=s.substring(s.indexOf("ssid//")+6,s.indexOf("//pwd"));
	password=s.substring(s.indexOf("pwd//")+5,s.indexOf("//end"));
	EleRate=s.substring(s.indexOf("EleR//")+6,s.indexOf("//EleSuply"));
	EleSupply=s.substring(s.indexOf("EleSuply//")+10,s.indexOf("//eend"));
  file.close();
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
