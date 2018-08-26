#include "ros/ros.h"
#include "string_tools/StringConcat.h"


bool concat(string_tools::StringConcat::Request& request,
            string_tools::StringConcat::Response& response) {
  response.sum = request.lhs + request.rhs;
  return true;
}


int main(int argc, char** argv) {
  ros::init(argc, argv, "concat_string_server");
  ros::NodeHandle handle;

  const std::string service_name = ros::this_node::getName() + "/concat_strings";
  ros::ServiceServer service = handle.advertiseService(service_name, concat);
  ros::spin();

  return 0;
}
