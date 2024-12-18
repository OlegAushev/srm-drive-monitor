#!/bin/bash
#
ip link delete vcan0
ip link delete vcan1
ip link add dev vcan0 type vcan
ip link add dev vcan1 type vcan
ip link set up vcan0
ip link set up vcan1
modprobe can-gw
cangw -A -s vcan0 -d vcan1 -e
cangw -A -s vcan1 -d vcan0 -e
echo "Virtual SocketCAN interfaces vcan0, vcan1 enabled."
exit 0
