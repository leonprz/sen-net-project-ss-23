import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient
from datetime import datetime
import json
import base64


mqtt_server: str = '10.20.111.210'
mqtt_port: int = 1883
mqtt_user: str = 'group02'
mqtt_password: str = None  # will be read from file 'mqtt-password.txt'
mqtt_topic: str = 'v3/sennet@ttn/devices/+/up'  # the MQTT topic to subscribe to


def on_connect(client: mqtt.Client, userdata, flags: dict, rc: int):
    if rc == 0:
        print('Connected to MQTT Broker!')
        client.subscribe(mqtt_topic)
    else:
        print(f'Failed to connect, return code {rc}')

def on_message(client: mqtt.Client, userdata, msg: mqtt.MQTTMessage):
    json_msg = json.loads(msg.payload.decode())
    print(f'Received Msg in `{msg.topic}` topic: {json.dumps(json_msg, indent=2)}')

    device_id = json_msg['end_device_ids']['device_id']
    f_port = json_msg['uplink_message']['f_port']
    print(f'Device ID: {device_id} Port: {f_port}')

    frm_payload = json_msg['uplink_message']['frm_payload']
    print(f'Received payload: {frm_payload}')


try:
    with open('mqtt-password.txt', 'r') as f:
        mqtt_password = f.read().rstrip()
except IOError:
    print('Could not read MQTT password file.')
    exit(1)

client = mqtt.Client()
client.username_pw_set(mqtt_user, mqtt_password)
client.on_connect = on_connect
client.on_message = on_message
client.connect(mqtt_server, mqtt_port)
client.loop_forever()
