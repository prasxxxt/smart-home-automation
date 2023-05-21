#include <ESP8266WiFi.h>


// Change these
const char* ssid     = "SSID";
const char* password = "Password";

WiFiServer server(80);

String header;

String State0 = "off";
String State1 = "off";
String State2 = "off";
String State3 = "off";
String State4 = "off";
String State5 = "off";
String State6 = "off";
String State7 = "off";
String State8 = "off";
String State9 = "off";

const int R0 = 16;
const int R1 = 5;
const int R2 = 4;
const int R3 = 0;
const int R4 = 2;
const int R5 = 14;
const int R6 = 12;
const int R7 = 13;
const int R8 = 15;
const int R9 = 1;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000; 

void setup() {
  
  Serial.begin(115200);
  
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);

  digitalWrite(R0, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(R3, LOW);
  digitalWrite(R4, LOW);
  digitalWrite(R5, LOW);
  digitalWrite(R6, LOW);
  digitalWrite(R7, LOW);
  digitalWrite(R8, LOW);
  digitalWrite(R9, LOW);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /0/on") >= 0) {
              Serial.println("R0 is on");
              State0 = "on";
              digitalWrite(R0, HIGH);
            } else if (header.indexOf("GET /0/off") >= 0) {
              Serial.println("R0 is off");
              State0 = "off";
              digitalWrite(R0, LOW);
            } else if (header.indexOf("GET /1/on") >= 0) {
              Serial.println("R1 is on");
              State1 = "on";
              digitalWrite(R1, HIGH);
            } else if (header.indexOf("GET /1/off") >= 0) {
              Serial.println("R1 is off");
              State1 = "off";
              digitalWrite(R1, LOW);
            } else if (header.indexOf("GET /2/on") >= 0) {
              Serial.println("R2 is on");
              State2 = "on";
              digitalWrite(R2, HIGH);
            } else if (header.indexOf("GET /2/off") >= 0) {
              Serial.println("R2 is off");
              State2 = "off";
              digitalWrite(R2, LOW);
            } else if (header.indexOf("GET /3/on") >= 0) {
              Serial.println("R3 is on");
              State3 = "on";
              digitalWrite(R3, HIGH);
            } else if (header.indexOf("GET /3/off") >= 0) {
              Serial.println("R3 is off");
              State3 = "off";
              digitalWrite(R3, LOW);
            }else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("R4 is on");
              State4 = "on";
              digitalWrite(R4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("R4 is off");
              State4 = "off";
              digitalWrite(R4, LOW);
            } else if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("R5 is on");
              State5 = "on";
              digitalWrite(R5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("R5 is off");
              State5 = "off";
              digitalWrite(R5, LOW);
            } else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("R6 is on");
              State6 = "on";
              digitalWrite(R6, HIGH);
              delay(1000);
              digitalWrite(R7, HIGH);
              delay(500);
              digitalWrite(R7, LOW);
            } else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("R6 is off");
              State6 = "off";
              digitalWrite(R6, LOW);
            } else if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("R8 is on");
              State8 = "on";
              digitalWrite(R8, HIGH);
              delay(400);
              digitalWrite(R8, LOW);
            } else if (header.indexOf("GET /8/off") >= 0) {
              Serial.println("R8 is off");
              State8 = "off";
              digitalWrite(R9, HIGH);
              delay(400);
              digitalWrite(R9, LOW);
            }       

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println("body {background-color:black;}");
            client.println("h2 {color: white;}");
            client.println(".button { background-color: #13AF00; border: none; color: white; padding: 16px 40px; width:160px; text-align:center;");
            client.println("text-decoration: none; font-size: 24px; margin: 6px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            client.println("<body><h2>Smart home automation</h2>");
            
            if (State0=="off") {
              client.println("<p><a href=\"/0/on\"><button class=\"button button2\">Switch 1</button></a>");
            } else {
              client.println("<p><a href=\"/0/off\"><button class=\"button\">Switch 1</button></a>");
            } 
            
            if (State1=="off") {
              client.println("<a href=\"/1/on\"><button class=\"button button2\">Switch 2</button></a></p>");
            } else {
              client.println("<a href=\"/1/off\"><button class=\"button\">Switch 2</button></a></p>");
            }
            
            if (State2=="off") {
              client.println("<p><a href=\"/2/on\"><button class=\"button button2\">Switch 3</button></a>");
            } else {
              client.println("<p><a href=\"/2/off\"><button class=\"button\">Switch 3</button></a>");
            } 
            
            if (State3=="off") {
              client.println("<a href=\"/3/on\"><button class=\"button button2\">Switch 4</button></a></p>");
            } else {
              client.println("<a href=\"/3/off\"><button class=\"button\">Switch 4</button></a></p>");
            }
            
            if (State4=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button button2\">Switch 5</button></a>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button\">Switch 5</button></a>");
            }
            
            if (State5=="off") {
              client.println("<a href=\"/5/on\"><button class=\"button button2\">Switch 6</button></a></p>");
            } else {
              client.println("<a href=\"/5/off\"><button class=\"button\">Switch 6</button></a></p>");
            }
            
            if (State6=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button button2\">Switch 7</button></a>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button\">Switch 7</button></a>");
            }
            
            if (State8=="off") {
              client.println("<a href=\"/8/on\"><button class=\"button button2\">Switch 8</button></a></p>");
            } else {
              client.println("<a href=\"/8/off\"><button class=\"button\">Switch 8</button></a></p>");
            }
            
            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}