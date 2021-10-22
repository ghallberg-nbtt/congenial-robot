/*
  API Access and output to OLED

  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-robot/blob/main/LICENSE
*/

#include "WiFi.h"
#include "Arduino_JSON.h"
#include "Wire.h"
#include "Adafruit_SSD1306.h"

const char* ssid = "your_ssid";
const char* password = "your_password";

const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1; //uses Arduino reset button

//API Elements
const char SERVER[] = "api.openweathermap.org";
const char HOST_STRING[] = "HOST: api.openweathermap.org";
const String API_KEY = "24e04a92cec8113039d9bff85ac5f478";
const String LOCATION = "Edinburgh"; //swap with your location
const String UNITS = "C";

WiFiClient client; //ESP32 will be the client
//Set OLED width and height and attach to I2C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
  Serial.println();

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay(); //clear display
  display.display(); //print blank screen
  display.setTextColor(SSD1306_WHITE); // Draw white text
  getTemperature(); //get temperature first time round
}

void loop() {
  delay (60000); //delay 1 minute
  getTemperature();
}

void getTemperature() {
  display.clearDisplay(); //clear display
  display.setTextSize(1);
  display.setCursor(0, 0); //moves curser
  display.print(LOCATION);
  //Prepare the API request
  String apiUnits = "metric";
  if (UNITS == "F") {
    apiUnits = "imperial";
  }
  String request = "GET /data/2.5/weather?units=" + apiUnits + "&q=" + LOCATION + "&appid=" + API_KEY + " HTTP/1.1";
  //Connect to the server and send request
  if (client.connect(SERVER, 80)) {
    Serial.println ("Sending request..");
    Serial.println (request);
    Serial.println ("");
    client.println (request);
    client.println (HOST_STRING);
    client.println ("Connection : close");
    client.println ();
  }

  //Now wait for the reply
  while (!client.available());
  //Discard data until we receive an open bracket '{'
  while (true) {
    char header = client.read();
    if (header == '{') break; //break out of loop here
    Serial.print (header); //debug to serial monitor
  }

  //'{' means JSON data found
  String jsonData = " {";
  do {
    char c = client.read(); //read data
    jsonData += c;
  } while (client.connected());
  client.stop();
  //process JSON response
  JSONVar apiObject = JSON.parse(jsonData);
  Serial.println ("JSON response");
  Serial.println (apiObject);
  double temperature = (double) apiObject ["main"]["temp"];
  Serial.print ("The temperature is ");
  Serial.print (temperature);
  Serial.println (UNITS);
  display.setTextSize(3);
  display.setCursor(0, 20); //moves curser
  display.print(temperature, 1); //print to 1 decimal place
  display.print (UNITS);
  display.display();
}
