#!/bin/sh


xhost local:root
XAUTH=/tmp/.docker.XAUTH

sudo docker start ros2

sudo docker exec -it ros2 bash
