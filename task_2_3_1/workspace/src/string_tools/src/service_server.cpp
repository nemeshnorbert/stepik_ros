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

  ros::ServiceServer service = handle.advertiseService("concat_strings", concat);
  ros::spin();

  return 0;
}
