#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"


class ProcessorNode {
  public:
    ProcessorNode() {
      id_ = 0;
      publisher_ = handle_.advertise<visualization_msgs::Marker>("/output", 1);
      subscriber_ = handle_.subscribe(
          "/input", 1, &ProcessorNode::subscriberCallback, this);
    }

  private:
    void subscriberCallback(const geometry_msgs::Point& point) {
      visualization_msgs::Marker marker;
      marker.header.frame_id = "/point_on_map";
      marker.header.stamp = ros::Time::now();
      marker.ns = "there_is_point";
      marker.id = id_++;
      marker.action = visualization_msgs::Marker::ADD;
      marker.type = visualization_msgs::Marker::POINTS;
      marker.scale.x = 0.5;
      marker.scale.y = 0.5;
      marker.color.r = 1.0;
      marker.color.g = 0.0;
      marker.color.b = 0.0;
      marker.color.a = 1.0;
      marker.points.push_back(point);
      publisher_.publish(marker);
    }

    ros::Publisher publisher_;
    ros::Subscriber subscriber_;
    ros::NodeHandle handle_;
    size_t id_;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "pt_publish");
  ProcessorNode node;
  ros::spin();
  return 0;
}
