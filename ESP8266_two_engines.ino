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
//********************************************
int PWM1 = 16; // XEnable
int xPhase1 = 14; // Drive, revers
int PWM2 = 5; // XEnable
int xPhase2 = 4; // Drive, revers

int mode = 12; // mode + LED Green
//*******************************************
int intens = 500;

void setup(void){
  //the HTML of the web page
 page = "<!DOCTYPE HTML>";
 page = "<html>";
 page = "<head>";
 page = "<style>";
 page = ".button {";
 page = "     background-color: #4CAF50;";
 page = "     border: none;";
 page = "     color: white;";
 page = "     padding: 60px 128px;";
 page = "     text-align: center;";
 page = "     text-decoration: none;";
 page = "     display: inline-block;";
 page = "     font-size: 16px;";
 page = "     margin: 4px 2px;";
 page = "    cursor: pointer;";
 page = "}";
 page = ".button3 {background-color: #f44336;} /* Red */";
 page = "</style>";
 page = "</head>";
 page = "<body>";

 page = "<h1>Simple NodeMCU Web Server</h1>";
 page = "<p><a class="button" href=\"LEDOn\"><button>ON</button></a>&nbsp;<a class="button" href=\"LEDOff\"><button>OFF</button></a></p>";
 page = "<p><a class="button" href=\"Drive\"><button>Drive</button></a>&nbsp;<a class="button" href=\"Reverse\"><button>Reverse</button></a>&nbsp;<a class="button button3" href=\"Stop\"><button>Stop</button></a></p>";
 page = "<p><a class="button" href=\"Faster\"><button>Faster</button></a>&nbsp;<a class="button" href=\"Slower\"><button>Slower</button></a></p>";
 page = "<p><a class="button"href=\"Left\"><button>Left</button></a>&nbsp;<a class="button" href=\"Right\"><button>Right</button></a></p>";

//  page = "<h1>Simple NodeMCU Web Server</h1>";
//  page += "<p><a href=\"LEDOn\"><button>ON</button></a>&nbsp;<a href=\"LEDOff\"><button>OFF</button></a></p>";
//  page += "<p><a href=\"Drive\"><button>Drive</button></a>&nbsp;<a href=\"Reverse\"><button>Reverse</button></a>&nbsp;<a href=\"Stop\"><button>Stop</button></a></p>";
//  page += "<p><a href=\"Faster\"><button>Faster</button></a>&nbsp;<a href=\"Slower\"><button>Slower</button></a></p>";
 // page += "<p><a href=\"Left\"><button>Left</button></a>&nbsp;<a href=\"Right\"><button>Right</button></a></p>";
  //configure GPIO
  pinMode(PWM1, OUTPUT);
  pinMode(xPhase1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(xPhase2, OUTPUT);
  
  pinMode(mode, OUTPUT);
  digitalWrite(mode, HIGH);
  pinMode(ledR, OUTPUT);
   
  delay(1000);
  
  WiFi.begin(ssid, password); //begin WiFi connection
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
          analogWrite(ledPin, 1);
      delay(200);
      analogWrite(ledPin, 1024);
      delay(200);
  }
analogWrite(ledPin, 1010);

void stop()
{
    analogWrite(PWM1, 0);
}

void stopDelay()
{
    delay(1000);
    stop();
}
  
  server.on("/", [](){
    server.send(200, "text/html", page);
  });
  server.on("/Drive", [](){
    server.send(200, "text/html", page);
    digitalWrite(xPhase1, HIGH);
    analogWrite(PWM1, 500);
    digitalWrite(xPhase2, HIGH);
    analogWrite(PWM2, 500);
    stopDelay();
    delay(1000);
  });
  server.on("/Reverse", [](){
    server.send(200, "text/html", page);
    digitalWrite(xPhase1, LOW);
    analogWrite(PWM1, 500);
    digitalWrite(xPhase2, LOW);
    analogWrite(PWM2, 500);
    stopDelay();
    delay(1000);
  });
  server.on("/Faster", [](){
    server.send(200, "text/html", page);
    intens += 100;
    analogWrite(PWM1, intens);
    analogWrite(PWM2, intens);
    stopDelay();
    delay(1000);
  });
  server.on("/Slower", [](){
    server.send(200, "text/html", page);
    intens -= 100;
    analogWrite(PWM1, intens);
    analogWrite(PWM2, intens);
    stopDelay();
    delay(1000);
  });
  server.on("/Left", [](){
    server.send(200, "text/html", page);
    analogWrite(PWM1, intens-100);
    analogWrite(PWM2, intens+100);
    stopDelay();
    delay(1000);
  });
  server.on("/Right", [](){
    server.send(200, "text/html", page);
    analogWrite(PWM1, intens+100);
    analogWrite(PWM2, intens-100);
    stopDelay();
    delay(1000);
  });
  server.on("/Stop", [](){
    server.send(200, "text/html", page);
    stop();
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
