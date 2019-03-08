#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
// Replace with your network credentials
const char* ssid = "Vectra-WiFi-260244";//type your ssid
const char* password = "vnet278750378";//type your password
 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
 
String page = "";
int ledPin = 2; // onboard LED
int ledB = 12; // blue Led
int ledG = 13; // green Led
int ledR = 15; // red Led

int PWM = 16; // XEnable
int xPhase = 14; // Drive, revers
int mode = 5; // mode

int intens = 500;

void setup(void){
  //the HTML of the web page
  page = "<h1>Simple NodeMCU Web Server</h1>";
  page += "<p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
  page += "<p><a href=\"Drive\"><button>Drive</button></a>&nbsp;<a href=\"Reverse\"><button>Reverse</button></a>&nbsp;<a href=\"Stop\"><button>Stop</button></a></p>";
  page += "<p><a href=\"Faster\"><button>Faster</button></a>&nbsp;<a href=\"Slower\"><button>Reverse</button></a></p>";
  //configure GPIO
  pinMode(PWM, OUTPUT);
  pinMode(xPhase, OUTPUT);
  pinMode(mode, OUTPUT);
  digitalWrite(mode, HIGH);
   
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password); //begin WiFi connection
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
          analogWrite(ledPin, 1);
      delay(200);
      analogWrite(ledPin, 1024);
      delay(200);
  }
analogWrite(ledPin, 1010);
  
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/Drive", [](){
    server.send(200, "text/html", page);
    digitalWrite(xPhase, HIGH);
    analogWrite(PWM, 500);
    delay(1000);
  });
  server.on("/Reverse", [](){
    server.send(200, "text/html", page);
    digitalWrite(xPhase, LOW);
    analogWrite(PWM, 500);
    delay(1000);
  });
  server.on("/Faster", [](){
    server.send(200, "text/html", page);
    //digitalWrite(xPhase, LOW);
    intens += 100;
    analogWrite(PWM, intens);
    delay(1000);
  });
  server.on("/Slower", [](){
    server.send(200, "text/html", page);
    //digitalWrite(xPhase, LOW);
    intens -= 100;
    analogWrite(PWM, intens);
    delay(1000);
  });
  server.on("/Stop", [](){
    server.send(200, "text/html", page);
    digitalWrite(PWM, LOW);
    delay(1000);
  });
  server.on("/LEDOn", [](){
    server.send(200, "text/html", page);
    digitalWrite(ledR, HIGH);
    delay(1000);
  });
  server.on("/LEDOff", [](){
    server.send(200, "text/html", page);
    digitalWrite(ledR, LOW);
    delay(1000); 
  });
  server.begin();
}
 
void loop(void){
  server.handleClient();


}
