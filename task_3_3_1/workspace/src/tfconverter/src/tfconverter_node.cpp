#include <ros/ros.h>
#include <tf/transform_listener.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/PointStamped.h"


class ProcessorNode {
  public:
    ProcessorNode()
      : handle_()
      , publisher_()
      , subscriber_()
      , listener_()
    {
      publisher_ = handle_.advertise<geometry_msgs::Point>("/output", 1);
      subscriber_ = handle_.subscribe(
          "/input", 1, &ProcessorNode::subscriberCallback, this);
    }

  private:
    void subscriberCallback(const geometry_msgs::PointStamped& point) {
      try {
        geometry_msgs::PointStamped core_point;
        listener_.transformPoint("core_frame", point, core_point);
        publisher_.publish(core_point.point);
      } catch (const  tf::TransformException& error) {
        ROS_ERROR("Got exception while processing point: %s", error.what());
      }
    }

    ros::NodeHandle handle_;
    ros::Publisher publisher_;
    ros::Subscriber subscriber_;
    tf::TransformListener listener_;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "tfconverter_node");
  ProcessorNode node;
  ros::spin();
  return 0;
}
