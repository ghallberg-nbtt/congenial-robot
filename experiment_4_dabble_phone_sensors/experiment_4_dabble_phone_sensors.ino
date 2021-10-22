/*
   Accelerometer block of Phone sensor module allows you to access your smartphone's accelerometer values.

   You can reduce the size of library compiled by enabling only those modules that you wan to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/phone-sensors-module/
*/
/*
  Additions by Gary Hallberg
  Dabble Phone Sensor
  Licensed under MIT https://github.com/ghallberg-nbtt/congenial-robot/blob/main/LICENSE
*/

#define CUSTOM_SETTINGS
#define INCLUDE_SENSOR_MODULE
#include <DabbleESP32.h>

const int FREQ = 5000;
const int RED_LED_CHANNEL = 0;
const int GREEN_LED_CHANNEL = 1;
const int BLUE_LED_CHANNEL = 2;
const int RESOLUTION = 8;

const int RED_LED = 27; //GPIO27 for red LED
const int GREEN_LED = 32; //GPIO32 for green LED
const int BLUE_LED = 33; //GPIO33 for blue LED

void setup() {
  Serial.begin(115200);    // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("MyEsp32");   //set bluetooth name of your device

  // configure LED PWM functionalitites
  ledcSetup(RED_LED_CHANNEL, FREQ, RESOLUTION);
  ledcSetup(GREEN_LED_CHANNEL, FREQ, RESOLUTION);
  ledcSetup(BLUE_LED_CHANNEL, FREQ, RESOLUTION);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(RED_LED, RED_LED_CHANNEL);
  ledcAttachPin(GREEN_LED, GREEN_LED_CHANNEL);
  ledcAttachPin(BLUE_LED, BLUE_LED_CHANNEL);

  //turn off all LEDS
  ledcWrite(RED_LED, 0);
  ledcWrite(GREEN_LED, 0);
  ledcWrite(BLUE_LED, 0);
}

void loop() {
  Dabble.processInput();
  print_Accelerometer_data();

  float valRed = Sensor.getAccelerometerXaxis(); // X axis will trigger red LED
  float valGreen = Sensor.getAccelerometerYaxis(); // Y axis will trigger green LED
  float valBlue = Sensor.getAccelerometerZaxis(); // Z axis will trigger blue LED

  int valRed_int = (int) valRed; //convert to integer
  int valGreen_int = (int) valGreen; //convert to integer
  int valBlue_int = (int) valBlue; //convert to integer

  valRed_int = map(valRed_int, -5, 5, 0, 255); //convert to PWM value
  valGreen_int = map(valGreen_int, -5, 5, 0, 255); //convert to PWM value
  valBlue_int = map(valBlue_int, -5, 5, 0, 255); //convert to PWM value

  valRed_int = constrain (valRed_int, 0, 255); //constrain PWM range
  valGreen_int = constrain (valGreen_int, 0, 255); //constrain PWM range
  valBlue_int - constrain (valBlue_int, 0, 255); //constrain PWM range

  ledcWrite(RED_LED_CHANNEL, valRed_int);  //write value to LED
  ledcWrite(GREEN_LED_CHANNEL, valGreen_int);  //write value to LED
  ledcWrite(BLUE_LED, valBlue_int);  //write value to LED

  delay (15);
}

void print_Accelerometer_data()
{
  Serial.print("X_axis: ");
  Serial.print(Sensor.getAccelerometerXaxis(), 4);
  Serial.print('\t');
  Serial.print("Y_axis: ");
  Serial.print(Sensor.getAccelerometerYaxis(), 4);
  Serial.print('\t');
  Serial.print("Z_axis: ");
  Serial.println(Sensor.getAccelerometerZaxis(), 4);
  Serial.println();

}
