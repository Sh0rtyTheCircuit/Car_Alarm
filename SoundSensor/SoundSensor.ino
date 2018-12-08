#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// #### Pins Setup #### //

const int Sensor = D2;

int SensorRead =  0;

// ##### Wifi Connection Setup #### //
char WifiName[] = "Verizon-SM-G935V";            //SSID
char Password[] = "password";

void setup() {
  // put your setup code here, to run once:
pinMode (Sensor, INPUT);

Serial.begin (9600);

}

void loop() {
  // put your main code here, to run repeatedly:
SensorRead = analogRead(Sensor);
  if (SensorRead >850);

}

// ### SOURCES ### //
//https://www.instructables.com/id/Simple-FC-04-Sound-Sensor-Demo/
