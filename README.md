# Smart City: Sensorik und Netze - Projekt Luftqualität

- [Anwendung](#anwendung)
- [Installation](#installation)
  - [Voraussetzungen](#voraussetzungen)
  - [Firmware](#firmware)
  - [MQTT Client](#mqtt-client)
- [Software](#software)
  - [Payload Format](#payload-format)
  - [The Things Network (Fair Use Policy)](#the-things-network-fair-use-policy)
  - [Grafana](#grafana)

---

## Anwendung

Im Rahmen des Moduls "Smart City: Sensorik und Netze" haben wir, als beispielhaften Anwendungsfall, ein System zur Überwachung der Luftqualität entwickelt. Dazu erfolgt die Messung der Temperatur, Luftfeuchtigkeit, Luftdruck und Lichteinstrahlung mittels verschiedener Sensoren.

Für eine Erklärung auf welche Weise die einzelnen Messwerte Einfluss auf die Luftqualität haben, siehe [usecase.md](./usecase.md).

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
    - für technische Details der Sensoren, siehe [sensor_details.md](./sensor_details.md)
- The Things Stack (<https://thethingsindustries.com/stack>)
- MQTT Broker (z.B. Eclipse Mosquitto <https://mosquitto.org>)
- Python 3.9+ (<https://python.org>)
- PlatformIO (<https://platformio.org>)
- InfluxDB (<https://influxdata.com>)
- Grafana (<https://grafana.com>)

### Firmware

Die Firmware für das WisBlock System wird mit PlatformIO erstellt. Dazu muss das Repository geklont werden und die PlatformIO CLI installiert sein. Anschließend muss die Firmware erstellt und auf das WisBlock System geflasht werden.

```bash
pio run --target upload
```

### MQTT Client

Als MQTT Client dient das Python Script [sennet-mqtt.py](./mqtt-client/sennet-mqtt.py), welches die [TTN](https://thethingsnetwork.org) Nachrichten des MQTT Brokers entgegennimmt, verarbeitet und die extrahierten Daten in die Datenbank (InfluxDB) schreibt. Das Script setzt die Installation der in [requirements.txt](./mqtt-client/requirements.txt) gelisteten Pakete voraus.

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

Da der MQTT Client kontinuierlich laufen muss, existiert die 'systemd service unit'-Datei [sennet.service](./mqtt-client/sennet.service). Dort muss folgendes nutzerspezifisch angepasst werden:

```ini
[Service]
# path to directory containing the mqtt-client python script
WorkingDirectory=/root/sennet-mqtt/
```

## Software

### Payload Format

Über LoRaWAN werden die Messwerte der Sensoren als Payload übertragen. Diese werden über TTN an den MQTT Broker gepublisht. Der MQTT Client extrahiert die Daten aus dem Payload und schreibt sie in die Datenbank.

Es werden insgesamt 7 Bytes übertragen:

| Bytes | Daten | Encoding |
|-------|-------|--------------|
| 1. - 3. | Lichteinstrahlung | Nachkommastellen entfernt; 3 Bytes Messwert |
| 4. | Temperatur | eine binäre Nachkommastelle im MSB; 7 Bits abgerundeter Messwert |
| 5. | Luftfeuchtigkeit | eine binäre Nachkommastelle im MSB; 7 Bits abgerundeter Messwert |
| 6. + 7. | Luftdruck | 2 Bytes Messwert |

### The Things Network (Fair Use Policy)

<https://www.thethingsnetwork.org/docs/lorawan/duty-cycle/#fair-use-policy>

> On The Things Network's public community network a Fair Use Policy applies which limits the uplink airtime to 30 seconds per day (24 hours) per node and the downlink messages to 10 messages per day (24 hours) per node. If you use a private network, these limits do not apply, but you still have to be compliant with the governmental and LoRaWAN limits.

Um diesem Limit zu entsprechen, wird die Übertragung der Daten auf eine Nachricht pro 5 Minuten beschränkt.

Die Wartezeit zwischen den Nachrichten kann mit folgender Webseite berechnet werden:
<https://avbentem.github.io/airtime-calculator/ttn/eu868/7>

### Grafana

Die Daten werden in Grafana visualisiert. Dazu muss eine InfluxDB Datenquelle angelegt werden. Anschließend können die Daten in einem Dashboard visualisiert werden. Das Dashboard ist in [grafana-dashboard.json](./grafana-dashboard.json) zu finden.
