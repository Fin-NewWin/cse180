#!/bin/bash


sudo docker rm -f ros2
sudo docker build -t ros2_foxy . --build-arg 'ACCEPT_EULA=Y'
echo "======================================"
echo "              Build image             "
echo "======================================"

sudo docker run -idt \
    --name=ros2\
    --env="DISPLAY=$DISPLAY"\
    --env="QT_X11_NO_MITSHM=1"\
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw"\
    --env="XAUTHORITY=$XAUTH"\
    --net=host \
    --privileged \
    ros2_foxy \
    bash

echo "======================================"
echo "          Create container            "
echo "======================================"


echo "Done"
