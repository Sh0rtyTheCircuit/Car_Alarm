#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>


// #### Pins Setup #### //

//const int Sensor = D2;

//int SensorRead =  0;

// #### MQTT Server connection Setup - Raspberry Pi Broker #### //
char* mqtt_server = "192.168.43.40";  
int mqtt_port = 1883;  
char* topic = "Camera_Message";

WiFiClient Wifi;            //Setup Wifi object 
PubSubClient client(Wifi);  //Object that gives you all the MQTT functionality, access objects in PubSubClient Library

// ##### Wifi Connection Setup #### //
char WifiName[] = "Verizon-SM-G935V";            //SSID
char Password[] = "password";

void Send_Msg(){
  //digitalWrite(GREEN,HIGH);
  //delay (200);
}

void Take_Pics(){
  //digitalWrite(GREEN,HIGH);
  //delay (200);
}

void Msg_rcv(char* topic, byte* payload, unsigned int length){  
Serial.println((char)payload[1]);
  if ((char) payload[0] == 'o'){
    if ((char) payload[1] == 'f'){    //Equal to "off"
      //Take pictures and send message
    }
    else{
      //Don't do anything
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode (Sensor, INPUT);
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

  while(!client.connect("MQTT")){          //LED_board is name of Wemos/arduino connected to code. Waiting to connect to Broker.
    Serial.println("Finding a Connection...");
  }
  client.subscribe(topic);
  Serial.println(topic);
}

void loop() {
  // put your main code here, to run repeatedly:

  client.loop();
  if(!client.connected()){
    client.connect("Camera_Message");
    client.publish(topic, "Reconnected");
  }
  
  //Turn_color();
}
