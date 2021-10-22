/*
  Control LEDs from a Browser
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-robot/blob/main/LICENSE
*/

#include "WiFi.h"

const char* ssid = "your_ssid";
const char* password = "your_password";
const int OUTPUT33 = 33;
const int OUTPUT32 = 32;

WiFiServer server(80);

String header;
String output33State = "off";
String output32State = "off";

void setup() {

  Serial.begin(115200);
  pinMode(OUTPUT33, OUTPUT);
  pinMode(OUTPUT32, OUTPUT);
  //turn off LEDS
  digitalWrite(OUTPUT33, LOW);
  digitalWrite(OUTPUT32, LOW);

  WiFi.begin(ssid, password); //Try to connect to WiFi

  // Loop until connection established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
  IPAddress ip = WiFi.localIP();
  Serial.print ("The IP of this ESP32 is ");
  Serial.println (ip);
  server.begin(); //turn on Web server
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients

  if (client) {  // If a new client connects
    Serial.println("New Client.");
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) {  // loop while the client is connected
      if (client.available()) { // if there are text bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);  // print it out the serial monitor
        header += c; //append each 'c' onot header
        if (c == '\n') { // if the byte is a newline character
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
            if (header.indexOf("GET /33/on") >= 0) {
              Serial.println("GPIO 33 on");
              output33State = "on";
              digitalWrite(OUTPUT33, HIGH);
            } else if (header.indexOf("GET /33/off") >= 0) {
              Serial.println("GPIO 33 off");
              output33State = "off";
              digitalWrite(OUTPUT33, LOW);
            }
            if (header.indexOf("GET /32/on") >= 0) {
              Serial.println("GPIO 32 on");
              output32State = "on";
              digitalWrite(OUTPUT32, HIGH);
            } else if (header.indexOf("GET /32/off") >= 0) {
              Serial.println("GPIO 32 off");
              output32State = "off";
              digitalWrite(OUTPUT32, LOW);
            }
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head></head>");
            client.println("<body>");
            client.println("<h1>ESP32 LED Control</h1>");
            client.println("<h2>Lights Controller</h2>");

            // Display current state, and ON/OFF buttons for GPIO 33
            client.println("<p>GPIO 33 - State " + output33State + "</p>");
            // If the output33 State is off, it displays the ON button
            if (output33State == "off") {
              client.println("<p><a href=\"/33/on\"><button>ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/33/off\"><button>OFF</button></a></p>");
            }
            // Display current state, and ON/OFF buttons for GPIO 32
            client.println("<p>GPIO 32 - State " + output32State + "</p>");
            // If the output32 State is off, it displays the ON button
            if (output32State == "off") {
              client.println("<p><a href=\"/32/on\"><button>ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/32/off\"><button>OFF</button></a></p>");
            }
            client.println("</body></html>");
            header = "";
            client.stop();
            Serial.println("Client disconnected.");
            Serial.println("");
          }
        }
      }
    }
  }
}
