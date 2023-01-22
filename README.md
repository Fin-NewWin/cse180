# Introduction

CSE-180 Robotics \n
I don't use ubuntu but another distribution which has dependency issues with building ros2 from source therefore created
this docker image to fix that. Should work for other Linux distro. If there are issues, make a new issue.

# Installation

Install docker and build the docker image
```bash
docker build -t <name-of-image> .
docker image ls
```
Check if image is built

Use the shell script to setup the docker container with name `gui1`

```bash
chmod +x setup.bash`
```

Enter docker container
```bash
docker exec -it gui1
```

# Testing

Turtlesim for testing
```bash
source /opt/ros/foxy/setup.bash
ros2 run turtlesim turtlesim_node
```
If GUI, shows up good.
