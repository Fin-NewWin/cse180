#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>

float x;
float y;
double roll, pitch, yaw;
bool valid;

rclcpp::Node::SharedPtr nodeh;
geometry_msgs::msg::Twist pioneer_vel;

tf2::Quaternion q;

void odomReceived(const nav_msgs::msg::Odometry::SharedPtr msg) {
	tf2::convert(msg->pose.pose.orientation,q);
	tf2::Matrix3x3 m(q);
	m.getRPY(roll, pitch, yaw);

	x = msg->pose.pose.position.x;
	y = msg->pose.pose.position.y;

	valid = true;

	RCLCPP_INFO(nodeh->get_logger(),"pose (%f, %f) at %f", x, y, yaw);
}

int main(int argc,char ** argv) {

	rclcpp::init(argc,argv);
	nodeh = rclcpp::Node::make_shared("drawsquarefb");

	auto sub = nodeh->create_subscription<nav_msgs::msg::Odometry> ("/p2dx/odom",10,&odomReceived);
	auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>("/p2dx/cmd_vel",1000);

	double DIRS[] = {0,M_PI/2,M_PI,-M_PI/2};
	int size = 2; // size of square
	int dirCase = 0;


	while (rclcpp::ok()) {
	 	rclcpp::spin_some(nodeh);
	 	if (valid) {
			switch (dirCase){
				case 0:
					if(size > x){
						pioneer_vel.linear.x = .25;
					} else {
						pioneer_vel.linear.x = 0;
						if(yaw < DIRS[1]){
							pioneer_vel.angular.z = M_PI/8;
						} else {
							dirCase += 1;
							pioneer_vel.angular.z = 0;
						}
							
					} 
					break;
				case 1:
					if(size > y){
						pioneer_vel.linear.x = .25;
					} else {
						pioneer_vel.linear.x = 0;
						if(yaw < DIRS[2] && yaw > 0){
							pioneer_vel.angular.z = M_PI/8;
						} else {
							dirCase += 1;
							pioneer_vel.angular.z = 0;
						}
							
					} 
					break;
				case 2:
					if(0 < x){
						pioneer_vel.linear.x = .25;
					} else {
						pioneer_vel.linear.x = 0;
						if(yaw < DIRS[3] && yaw < 0){
							pioneer_vel.angular.z = M_PI/8;
						} else {
							dirCase += 1;
							pioneer_vel.angular.z = 0;
						}
							
					} 
					break;
				case 3:
					if(0 < y){
						pioneer_vel.linear.x = .25;
					} else {
						pioneer_vel.linear.x = 0;
						if(yaw < DIRS[0] && yaw < 0){
							pioneer_vel.angular.z = M_PI/8;
						} else {
							dirCase = 0;
							pioneer_vel.angular.z = 0;
						}
							
					} 
					break;


			}
			pub->publish(pioneer_vel);
			valid = false;

	 	}
	}
} 
