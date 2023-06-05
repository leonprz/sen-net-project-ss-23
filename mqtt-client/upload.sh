#!/bin/bash

DIR="$(dirname "$0")"
HOST='root@10.20.111.212'

scp "$DIR"/sennet-mqtt.py "$HOST":/root/sennet-mqtt.py
scp "$DIR"/requirements.txt "$HOST":/root/requirements.txt
scp "$DIR"/sennet.service "$HOST":/etc/systemd/system/sennet.service
ssh "$HOST" 'systemctl daemon-reload'
