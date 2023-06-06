#!/bin/bash

DIR="$(dirname "$0")"
HOST='root@10.20.111.212'

sftp "$HOST" <<EOF
	lcd "$DIR"
	mkdir /root/sennet-mqtt/
	cd /root/sennet-mqtt/
	put sennet-mqtt.py
	put requirements.txt
	cd /etc/systemd/system/
	put sennet.service
	quit
EOF

ssh "$HOST" 'systemctl daemon-reload'
