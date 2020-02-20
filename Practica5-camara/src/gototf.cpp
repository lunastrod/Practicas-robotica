#include "ros/ros.h"

#include <algorithm>

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <tf/transform_listener.h>

const double MAX_V=0.1;
const double MIN_V=-0.0;
const double MAX_W=0.1;
const double MIN_W=0;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gototf");
  ros::NodeHandle n_;
  ros::Publisher motor_pub = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
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

    double angle=atan2(transform.getOrigin().y(),transform.getOrigin().x());
    double distance=sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));

    geometry_msgs::Twist motor;
    motor.linear.y = 0;
    motor.linear.z = 0;
    motor.angular.x =0;
    motor.angular.y =0;

    motor.angular.z = std::min(std::max(angle,MIN_W),MAX_W);
    motor.linear.x = std::min(std::max(distance,MIN_V),MAX_V);

    printf("d=%fa=%f\n", distance, angle);

    motor_pub.publish(motor);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
