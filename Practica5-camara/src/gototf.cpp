#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <tf/transform_listener.h>



int main(int argc, char **argv)
{
  ros::init(argc, argv, "gototf");
  ros::NodeHandle n_;
  tf::TransformListener tfListener_;


  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    tf::StampedTransform transform;
    try{
      tfListener_.lookupTransform("/base_footprint", "/object/0", ros::Time(0), transform);
    }
    catch (tf::TransformException ex){
      ROS_ERROR("%s",ex.what());
    }
    printf("ang=%f\n", atan2(transform.getOrigin().y(),transform.getOrigin().x()));
    printf("dist=%f\n",sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2)));


    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
