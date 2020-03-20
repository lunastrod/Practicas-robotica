#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <tf/transform_listener.h>
#include "softarq_msgs/Distance.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<softarq_msgs::Distance>("detecta_obj");
  softarq_msgs::Distance srv;

  ros::Rate loop_rate(5);
  while (ros::ok())
  {
    client.call(srv);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
