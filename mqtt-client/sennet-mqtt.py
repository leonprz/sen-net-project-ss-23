import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient
from typing import Any
import json
import base64
import sys


if (3, 9) >= sys.version_info >= (4,):
    raise Exception('Python 3.9 or a more recent version is required.')

if sys.version_info >= (3, 10):
    Userdata = dict[str, InfluxDBClient | Any]
else:
    from typing import Dict, Union
    Userdata = Dict[str, Union[InfluxDBClient, Any]]


mqtt_server: str = '10.20.111.210'
mqtt_port: int = 1883
mqtt_user: str = 'group02'
mqtt_password: str = None  # will be read from file 'mqtt-password.txt'
mqtt_topic: str = 'v3/sennet@ttn/devices/+/up'  # the MQTT topic to subscribe to

influx_host: str = 'localhost'
influx_port: int = 8086
influx_user : str = 'root'
influx_password: str = ''
influx_database: str = 'sennet'


def on_connect(client: mqtt.Client, userdata, flags: dict, rc: int) -> None:
    if rc == 0:
        print('Connected to MQTT Broker!')
        client.subscribe(mqtt_topic)
    else:
        print(f'Failed to connect, return code {rc}')

def on_disconnect(client: mqtt.Client, userdata, rc: int) -> None:
    print('Disconnecting...')

    if rc == 0:
        print(f'Disconnected OK, return code {rc}')
    else:
        print(f'Disconnected INVALID, return code {rc}')

def on_message(client: mqtt.Client, userdata: Userdata, msg: mqtt.MQTTMessage) -> None:
    json_msg = json.loads(msg.payload.decode())
    #print(f'Received Msg in `{msg.topic}` topic: {json.dumps(json_msg, indent=2)}')

    device_id = json_msg['end_device_ids']['device_id']
    f_port = json_msg['uplink_message']['f_port']
    #print(f'Device ID: {device_id} Port: {f_port}')

    frm_payload = json_msg['uplink_message']['frm_payload']
    #print(f'Received payload: {frm_payload}')

    db_data = [
        {
            'measurement': 'sensor',
            'time': json_msg['received_at'],
            'tags': {
                'device_id': device_id,
            },
            'fields': decode_payload(frm_payload),
        },
    ]
    print(db_data)

    try:
        userdata['influx_client'].write_points(db_data)
    except Exception:
        print("Couldn't write to InfluxDB")

def decode_payload(frm_payload: str) -> dict[str, Any]:
    payload: bytes = base64.b64decode(frm_payload)

    lux = decode_ambLight(payload[0:3])
    envSensor = decode_envSensor(payload[3:35])

    return {
        'lux': lux,
        'temperature': envSensor[0],
        'humidity': envSensor[1],
        'pressure': envSensor[2],
    }

def decode_ambLight(payload: bytes) -> int:
    return int.from_bytes(payload, byteorder='little', signed=False)

def decode_envSensor(payload: bytes) -> (float, float, int):
    temp = payload[0] & 0b0111_1111
    if (payload[0] & 0b1000_0000):
        temp += .5

    hum = payload[1] & 0b0111_1111
    if (payload[1] & 0b1000_0000):
        hum += .5
    
    pres = int.from_bytes(payload[2:4], byteorder='little', signed=False)

    return (float(temp), float(hum), pres)

try:
    with open('mqtt-password.txt', 'r') as f:
        mqtt_password = f.read().rstrip()
except IOError:
    print('Could not read MQTT password file.')
    exit(1)

client = mqtt.Client(userdata={
    'influx_client': InfluxDBClient(
        host=influx_host,
        port=influx_port,
        username=influx_user,
        password=influx_password,
        database=influx_database
    ),
})
client.username_pw_set(mqtt_user, mqtt_password)
client.on_connect = on_connect
client.on_message = on_message
client.connect(mqtt_server, mqtt_port)
client.loop_forever()
