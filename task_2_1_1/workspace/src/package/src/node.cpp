#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Int32.h"


int main(int argc, char** argv) {
  ros::init(argc, argv, "node");
  ros::NodeHandle handle;
  ros::Publisher publisher = handle.advertise<std_msgs::Int32>("/topic", 1000);

  ros::Duration(1).sleep();

  ros::Rate loop_rate(10);
  std_msgs::Int32 value;
  while (std::cin) {
    std::cin >> value.data;
    publisher.publish(value);
    loop_rate.sleep();
  }
  ros::spinOnce();
}
