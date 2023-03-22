#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <turtlesim/msg/pose.hpp>



class Replicate : public rclcpp::Node {
public:
	Replicate() : Node("replicate"){
	    pub = this->create_publisher<geometry_msgs::msg::Twist> ("/p2dx/cmd_vel",100);
	    sub = this->create_subscription<turtlesim::msg::Pose>
		    ("/turtle1/pose",1000,std::bind(&Replicate::repeat, this, std::placeholders::_1));

	}
	void repeat(const turtlesim::msg::Pose::SharedPtr msg){
		geometry_msgs::msg::Twist outmsg;
		outmsg.linear.x = msg->linear_velocity;
		outmsg.angular.z = msg->angular_velocity;
		pub->publish(outmsg);
	}
private:
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub;
	rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr sub;
};
// void poseCallback(const turtlesim::msg::Pose::SharedPtr msg) {
//     geometry_msgs::msg::Twist outmsg;
//     outmsg.linear.x = msg->linear_velocity;
//     outmsg.angular.z = msg->angular_velocity;
//     pub->publish(outmsg);
// }

int main(int argc,char **argv) {

    rclcpp::init(argc,argv);

    Replicate node;
    rclcpp::spin(std::make_shared<Replicate>());



    rclcpp::shutdown();
}

