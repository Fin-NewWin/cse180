#include <rclcpp/rclcpp.hpp>
#include <turtlesim/msg/pose.hpp>
#include <geometry_msgs/msg/pose.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/msg/twist.hpp>

float x;
float y;
float theta;
float linear_velocity;
float angular_velocity;
bool valid;

rclcpp::Node::SharedPtr nodeh;
geometry_msgs::msg::Twist pioneer_vel;


void poseReceived(const turtlesim::msg::Pose::SharedPtr msg) {
	x = msg->x;
	y = msg->y;
	linear_velocity = msg->linear_velocity;
	angular_velocity = msg->angular_velocity;
	theta = msg->theta;
	valid = true;

	// RCLCPP_INFO(nodeh->get_logger(),"pose (%f, %f) at %f", x, y, theta);
}

int main(int argc,char ** argv) {

	rclcpp::init(argc,argv);
	nodeh = rclcpp::Node::make_shared("posesensor");

	auto sub = nodeh->create_subscription<turtlesim::msg::Pose>
		("/turtle1/pose",10,&poseReceived);
	auto pub = nodeh->create_publisher<geometry_msgs::msg::Twist>("/p2dx/cmd_vel",1000);

	// tf2::Quaternion q;
	// valid = false;

	while (rclcpp::ok()) {
	 	rclcpp::spin_some(nodeh);
	 	if (valid) {
			if(linear_velocity != 0.0){
				angular_velocity = 0.0;
			} else if(angular_velocity != 0.0){
				linear_velocity = 0.0;
			}
			pioneer_vel.linear.x = linear_velocity * 1000.0;
			pioneer_vel.linear.y = 0.0;
			pioneer_vel.linear.z = 0.0;
			pioneer_vel.angular.x = 0.0;
			pioneer_vel.angular.y = 0.0;
			pioneer_vel.angular.z = angular_velocity;
			pub->publish(pioneer_vel);
	 		valid = false;
	 	}
	}
}
