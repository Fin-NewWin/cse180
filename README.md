# Introduction

CSE-180 Robotics <br />
I don't use ubuntu but another distribution which has dependency issues with building ros2 from source therefore created
this docker image to fix that. Should work for other Linux distro. File an issue if there are bugs. I will be updating the class
regularly for the 2023 spring semester.

# Installation

Install docker and build the docker image.
Running the script should build the image for you
```bash
chmod u+x setup.sh
./setup.sh
docker image ls
```
Check if image is built

Use the shell script to setup the docker container with name `gui1`

```bash
chmod +x setup.bash
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
