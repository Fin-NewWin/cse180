/*
   Copyright 2023 Stefano Carpin

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unlss required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <rclcpp/rclcpp.hpp> // needed for basic functions
#include <std_msgs/msg/int32.hpp> // to publish integers
#include <std_msgs/msg/string.hpp> // to publish strings

int main(int argc,char **argv) {

	rclcpp::init(argc,argv); // initialize the ROS subsystem

	rclcpp::Node::SharedPtr nodeh;
	rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr pubi;
	rclcpp::Rate rate(2);

	nodeh = rclcpp::Node::make_shared("intpublisher"); // create node
	// create publisher to topic "intm" of integers
	pubi = nodeh->create_publisher<std_msgs::msg::Int32>("inttopic",1);

	int value=0;
	std_msgs::msg::Int32 intToSend; // integer message to send

	while (rclcpp::ok()) {
		intToSend.data = value; // update message to send
		pubi->publish(intToSend); // publish the integer message
		rclcpp::spin_some(nodeh); // handle pending messages
		RCLCPP_INFO(nodeh->get_logger(),"publishing %d",value);    	
		value++;
		rate.sleep(); // wait
	}
	rclcpp::shutdown(); // unreachable in the current form
	return 0;

}
