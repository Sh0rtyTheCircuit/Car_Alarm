import paho.mqtt.client as mqtt
import time
import socket
import select
import sys
import threading

#Channel Topic
Sound_Sensor = "Sound_Sensor"
Camera_Message = "Camera_Message"

#ip of localhost
mqtt_broker= "192.168.43.40"
mqtt_port = 1883

Accept_IP = "192.168.43."

#Define functions

def msg_rcv(sensors, user_data, msg):   #Interpret Msgs (Loops)
        print "Car alarm is going " + str(msg.payload)
        if (str(msg.payload) == "off"):
                Car_Alarm = "off"
        else:
                Car_Alarm = "on"
        client.publish (Camera_Message, payload = Car_Alarm, qos=0, retain=False) #(channel, msg to pub$        print (Car_Alarm)

def run_broker(client, user_data, flags, rc):                   #Subscribe to topics (Once)
        print "In the broker function"
        client.subscribe(Camera_Message)                       #Listen to the Sensors channel
        print "Subscribed to " + topic
        client.subscribe(Sound_Sensor)

client = mqtt.Client()

#When message is received, run msg_rcv function
client.on_message = msg_rcv

#When connected to Broker, run run_broker function
client.on_connect = run_broker

#Begin connection to MQTT Broker
client.connect(mqtt_broker,mqtt_port)
print "connection to broker started"

while True:
        client.loop()
#Predefined functions
client.loop_forever()   #Client will keep itself alive
client.disconnect()     #Disconnect before dying (cntrl C or kill)