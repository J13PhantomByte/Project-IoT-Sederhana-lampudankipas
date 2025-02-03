#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char* ssid = "Masukan Nama WIfi Kalian ";
const char* password = "Masukan Password Wifi Kalian ";
const int relayPin = D0; //pin untuk kontrol relay pada NODEMCU

ESP8266WebServer server(80);

void setup(){

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  Serial.begin(9600);

  connectToWiFi();

  server.on("/", handleRoot);
  server.begin();
  Serial.print("HTTP server started");
}

void loop(){
server.handleClient();}
  
void connectToWiFi(){
    
Serial.print("\n\nConnecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

while (WiFi.status() !=WL_CONNECTED){
delay(500);
Serial.print(".");}

Serial.println("nWiFiconnected");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());}

void handleRoot() {
  Serial.println("Got a Request");

  if (server.hasArg("a")) { // Pastikan ada parameter "a"
    if (server.arg("a") == "1") {
      digitalWrite(relayPin, LOW); // Nyalakan relay
      Serial.println("Relay ON");
    } else {
      digitalWrite(relayPin, HIGH); // Matikan relay
      Serial.println("Relay OFF");
    }
  }

  String msg = "";
  msg += "<html><body>\n";
  msg += "<head>";
  msg += "<center><h1>Control Relay By WEB</h1></center>";
  msg += "<center><h2><a href='/?a=1'><button>Lampu Menyala ON</button></a></h2></center>";
  msg += "<center><h2><a href='/?a=0'><button>Lampu Mati OFF</button></a></h2></center>";
  msg += "</body></html>";

  server.send(200, "text/html", msg);
}
