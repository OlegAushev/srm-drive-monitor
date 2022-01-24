#!/bin/bash
#
if ip addr ls dev can0 > /dev/null 2>&1
then
	echo "CAN device found."
	if ip link set can0 down
	then
		ip link set can0 type can bitrate 125000
		ip link set can0 up
		echo "SocketCAN interface enabled."
		exit 0
	else
		echo "Configuring and enabling SocketCAN interface failed."
		exit 1
	fi
else
	echo "CAN device not found."
	exit 1
fi
