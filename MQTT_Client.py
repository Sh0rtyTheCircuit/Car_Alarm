#import os
import paho.mqtt.client as mqtt
import time

#Channel Topic
Sound_Sensor = "Sound_Sensor"
Camera_Message = "Camera_Message"

#ip of localhost
mqtt_broker= "192.168.43.40"
mqtt_port = 1883

#Set up MQTT Client object (access to MQTT functions in the library)
#client = mqtt.Client()
#print "MQTT client object is set up"

#Define functions

def msg_rcv(Sound_Sensor, user_data, msg):   #Interpret Msgs (Loops)
        print "Thief is " + str(msg.payload)
        if (str(msg.payload) == "off"):
				Car_Alarm = "off"
        else:
                Car_Alarm = "on"
        Camera_Message.publish (Car_Alarm, payload = Car_Alarm, qos=0, retain=False) #(channel, msg to publish)
        print (Car_Alarm)

def run_broker(client, user_data, flags, rc):                   #Subscribe to topics (Once)
        print "In the broker function"
        client.subscribe(Sound_Sensor)                       #Listen to the Sensors channel
        print "Subscribed to "
        print (Sound_Sensor)

client = mqtt.Client()

#When message is received, run msg_rcv function
client.on_message = msg_rcv

#When connected to Broker, run run_broker function
client.on_connect = run_broker

#Begin connection to MQTT Broker
client.connect(mqtt_broker,mqtt_port)
print "connection to broker started"

#while not client.connect(mqtt_broker,mqtt_port):
#       print "Finding a connection"
#       time.sleep(.5)

#Predefined functions
client.loop_forever()   #Client will keep itself alive
client.disconnect()     #Disconnect before dying (cntrl C or kill)