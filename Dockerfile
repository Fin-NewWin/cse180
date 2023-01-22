FROM ubuntu:20.04

RUN apt update
RUN apt-get install curl -y
RUN apt-get install software-properties-common -y
# RUN apt-add-repository universe
# RUN apt-get install software-properties-common && add-apt-repository universe



# Installing ros2-foxy
RUN curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | tee /etc/apt/sources.list.d/ros2.list > /dev/null
RUN apt-get update -y && apt-get upgrade -y
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt install ros-foxy-desktop python3-argcomplete -y
RUN apt install ros-dev-tools -y

# Installing gazebo
RUN apt install ros-foxy-gazebo-* -y
