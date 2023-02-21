# Introduction

CSE-180 Robotics

<br />

I don't use ubuntu but another distribution which has dependency issues with building ros2 from source therefore created
this docker image to fix that. Should work for other Linux distro. File an issue if there are bugs. I will be updating the class
regularly for the 2023 spring semester.

<br />

If you have any question, file an issue for this repo.
As long as I'm not dead, I should be able to respond.

# Installation

Install docker and build the docker image.
Running the script should build the image for you
``` bash
./build.sh
docker image ls
```

Check if image is built


Enter docker container
``` bash
./run.sh
```

# Testing

Turtlesim for testing
``` bash
ros2 run turtlesim turtlesim_node
```
If GUI, shows up good.
