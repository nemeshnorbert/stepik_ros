#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Int32.h"


void recieve(const std_msgs::Int32& value) {
  std::cout << ros::this_node::getName() << ": data: " << value.data << "\n";
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "subscriber");
  ros::NodeHandle handle;
  ros::Subscriber subscriber = handle.subscribe("/topic", 1000, recieve);
  ros::spin();
  return 0;
}
