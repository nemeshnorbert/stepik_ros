#include <ros/ros.h>
#include "geometry_msgs/Point.h"
#include "visualization_msgs/Marker.h"


visualization_msgs::Marker buildMarker(
    const std::vector<geometry_msgs::Point>& points) {
  visualization_msgs::Marker marker;
  marker.header.frame_id = "/point_on_map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "there_is_point";
  marker.id = 0;
  marker.action = visualization_msgs::Marker::ADD;
  marker.type = visualization_msgs::Marker::POINTS;
  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  marker.color.a = 1.0;
  marker.points = points;
  return marker;
}

class ProcessorNode {
  public:
    ProcessorNode(size_t queue_size)
      : handle_()
      , publisher_()
      , subscriber_()
      , points_()
      , queue_size_(queue_size)
    {
      publisher_ = handle_.advertise<visualization_msgs::Marker>("/output", 1);
      subscriber_ = handle_.subscribe(
          "/input", 1, &ProcessorNode::subscriberCallback, this);
    }

  private:
    void subscriberCallback(const geometry_msgs::Point& point) {
      if (points_.size() < queue_size_) {
        points_.push_back(point);
        return;
      }
      points_.clear();
      publisher_.publish(buildMarker(points_));
    }

    ros::NodeHandle handle_;
    ros::Publisher publisher_;
    ros::Subscriber subscriber_;
    std::vector<geometry_msgs::Point> points_;
    size_t queue_size_;
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "answer");
  ProcessorNode node(5);
  ros::spin();
  return 0;
}
