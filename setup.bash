#!/bin/bash

xhost local:root
XAUTH=/tmp/.docker.XAUTH

docker run -idt \
    --name=gui1\
    --env="DISPLAY=$DISPLAY"\
    --env="QT_X11_NO_MITSHM=1"\
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw"\
    --env="XAUTHORITY=$XAUTH"\
    --net=host \
    --privileged \
    hello \
    bash

echo "Done"
