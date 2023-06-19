# Smart City: Sensorik und Netze - Projekt Luftqualität
- [Anwendung](#anwendung)
- [Installation](#installation)
- etc.
## Anwendung
txt
## Installation
### Voraussetzungen
- Hardware (RAK Wireless WisBlock Modular System)
	- Core Module: RAK4631 WisBlock LPWAN Module
	- Base Board: RAK19007 WisBlock Base Board 2nd Gen
	- Interface Module: RAK1920 WisBlock Sensor Adapter Module
	- Display Module: RAK1921 WisBlock OLED Display
	- Sensor Modules
		- RAK1903 WisBlock Ambient Light Sensor Module
		- RAK1906 WisBlock Environmental Sensor Module
- The Things Stack (https://thethingsindustries.com/stack)
- MQTT Broker (z.B. Eclipse Mosquitto <https://mosquitto.org>)
- Python 3.9+ (https://python.org)
- InfluxDB (<https://influxdata.com>)
- Grafana (<https://grafana.com>)
### MQTT Client
Als MQTT Client dient das Python Script [sennet-mqtt.py](./mqtt-client/sennet-mqtt.py), welches die TTN Nachrichten des MQTT Brokers entgegennimmt, verarbeitet und die extrahierten Daten in die Datenbank (InfluxDB) schreibt. Das Script setzt die Installation der in [requirements.txt](./mqtt-client/requirements.txt) gelisteten Pakete voraus.

Im Script müssen folgende Werte nutzerspezifisch angepasst werden:

```python
mqtt_server: str = '10.20.111.210'
mqtt_port: int = 1883
mqtt_user: str = 'group02'
mqtt_password: str = None  # if None, password will be read from file 'mqtt-password.txt'
mqtt_topic: str = 'v3/sennet@ttn/devices/+/up'  # the MQTT topic to subscribe to

influx_host: str = 'localhost'
influx_port: int = 8086
influx_user : str = 'root'
influx_password: str = None  # if None, password will be read from file 'influxdb-password.txt'
influx_database: str = 'sennet'
```

Da der MQTT Client kontinuierlich laufen muss, existiert die systemd unit file [sennet.service](./mqtt-client/sennet.service). Dort muss folgendes nutzerspezifisch angepasst werden:
```ini
[Service]
WorkingDirectory=/root/sennet-mqtt/
```
## Software
### Payload
### uint24
### ...
