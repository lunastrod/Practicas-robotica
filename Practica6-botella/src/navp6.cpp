#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <tf/transform_listener.h>
#include "actionlib/client/simple_action_client.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    printf("Main\n");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
