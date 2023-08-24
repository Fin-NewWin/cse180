FROM ubuntu:20.04

ENV DEBIAN_FRONTEND noninteractive
ENV DEBIAN_FRONTEND teletype


RUN apt update
RUN apt-get install curl apt-utils -y
RUN apt-get install software-properties-common -y
# RUN apt-add-repository universe
# RUN apt-get install software-properties-common && add-apt-repository universe



# ROS2 Foxy Install
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null
RUN apt-get update -y && apt-get upgrade -y
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt install ros-foxy-desktop python3-argcomplete -y
RUN apt install ros-dev-tools -y

# Gazebo Install
RUN apt install ros-foxy-gazebo-* -y

# Colcon Install
RUN sh -c 'echo "deb [arch=amd64,arm64] http://repo.ros2.org/ubuntu/main `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | apt-key add -
RUN apt update
RUN apt install python3-colcon-common-extensions -y


# Optional ROS2 packages

RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN apt update
RUN RTI_NC_LICENSE_ACCEPTED=yes apt install ros-foxy-* -y

# Text Editor
RUN apt install neovim -y
RUN echo '\nsource /opt/ros/foxy/setup.bash' >> /etc/bash.bashrc


# Clone https://github.com/stefanocarpin/MRTP
# Example for some
WORKDIR /root
RUN git clone https://github.com/stefanocarpin/MRTP

RUN apt install ros-foxy-turtlebot3* -y
# WORKDIR /root/MRTP
# RUN colcon build
