#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"



int main(int argc, char **argv)
{
  ros::init(argc, argv, "bumpgo");
  ros::NodeHandle n_;
  ros::Rate loop_rate(20);
  while (ros::ok())
  {

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
