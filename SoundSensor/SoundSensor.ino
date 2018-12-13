#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

// #### Pins Setup #### //

const int Sensor = D2; //AO
int SensorRead =  0;  //value of Sensor
char* CarSwitch = " ";

// #### MQTT Server connection Setup - Raspberry Pi Broker #### //
char* mqtt_server = "192.168.43.40";  
int mqtt_port = 1883;  
char* topic = "Sound_Sensor";

WiFiClient Wifi;            //Setup Wifi object 
PubSubClient client(Wifi);  //Object that gives you all the MQTT functionality, access objects in PubSubClient Library

// ##### Wifi Connection Setup #### //
char WifiName[] = "Verizon-SM-G935V";            //SSID
char Password[] = "password";

void Msg_rcv(char* topic, byte* payload, unsigned int length){     //Unsigned int = Positive numbers (more range)
  Serial.println ("Message Received");
}

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);

client.setServer(mqtt_server, mqtt_port);           
  client.setCallback(Msg_rcv);                   //Send payload to function (Msg_rcv)

  // ### Begin Connection to Wifi ### //
  WiFi.begin(WifiName,Password);
  while (WiFi.status() !=WL_CONNECTED){          //If not connected to Wifi, delay until connected
    delay (2000);
    Serial.println("Finding a Connection...");
  }

  Serial.println("Connection Started");         //Begin Connection to Wifi
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());               //IP assigned to Server by host wifi

  while(!client.connect("Motion_Sensor")){          //LED_board is name of Wemos/arduino connected to code. Waiting to connect to Broker.
    Serial.println("Finding a Connection...");
  }
  client.subscribe(topic); //Publisher?
  Serial.println(topic);
}

void loop() {
  // put your main code here, to run repeatedly:
SensorRead = analogRead(Sensor);
client.loop();

  if(!client.connected()){
    client.connect("Motion_Sensor");
    client.publish(topic, "Reconnected");
  }
  
  if (SensorRead > 850){
      Serial.println("Car alarm is going off");
      CarSwitch = "off";
      delay (100);
    }
  else{
    Serial.println("Car alarm is on");
    CarSwitch = "on";
    delay (100);
  }
   client.publish(topic, CarSwitch);
}

// ### SOURCES ### //
//https://tkkrlab.nl/wiki/Arduino_KY-037_Sensitive_microphone_sensor_module
