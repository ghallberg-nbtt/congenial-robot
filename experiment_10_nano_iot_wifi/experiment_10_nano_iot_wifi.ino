#include <WiFiNINA.h>

//please enter your sensitive data in the Secret tab
char ssid[] = "your_SSID";      // your network SSID (name)
char pass[] = "your_password";   // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;    // the Wi-Fi radio's status


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
    ;

  // set the LED as output
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  // attempt to connect to Wi-Fi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  Serial.println("---------------------------------------");
  digitalWrite(LED_BUILTIN, HIGH);  // turn on LED when connected
}

void loop() {
  Serial.println("Board Information:");
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print your network's SSID:
  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);
  Serial.println("---------------------------------------");
  delay (20000);
}