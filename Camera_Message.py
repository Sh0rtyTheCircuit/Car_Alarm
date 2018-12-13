import os
import paho.mqtt.client as mqtt
from time import sleep
import socket
import select
import sys
import threading
from slackclient import SlackClient

#Channel
Camera_Message = "Camera_Message"

#Connect to the OG MQTT Broker
mqtt_broker= "192.168.43.40"
mqtt_port = 1883

Accept_IP = "192.168.43."

#read Slack Token
file = open("slack_token.txt","r")
slack_token = file.read()
slack_token = slack_token.rstrip()
file.close()
sc = SlackClient(slack_token)

#Define functions

def msg_rcv(client, user_data, msg):   #Interpret Msgs (Loops)
        print "Car alarm is going " + str(msg.payload)
        if (str(msg.payload) == "off"):		#Send msg through slack
                sc.api_call("chat.postMessage",channel="car_alarm",text="Car alarm going off!")
                for i in range (10):
                        os.system("raspistill -o image%d.jpg"%i)	#%d replaced with i from "%i"
                        sleep (10)
				sc.api_call("chat.postMessage",channel="car_alarm",text="Car alarm going off!")
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