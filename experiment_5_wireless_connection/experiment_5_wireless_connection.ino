/*
  WiFi Connection
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-robot/blob/main/LICENSE
*/

#include "WiFi.h"

const char* ssid = "your_SSID";
const char* password = "your_password";

void setup() {

  Serial.begin(115200);

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
}

void loop() {
  //do nothing
}
