#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/CameraInfo.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gototf");
  ros::NodeHandle n_;

  

  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    printf("hola\n");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
