#include "ros/ros.h"
#include <std_msgs/Int8.h>

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "softarq_msgs/Distance.h"

#include "tf2/transform_datatypes.h"
#include "tf2/LinearMath/Transform.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
#include "tf2/convert.h"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"

#include <time.h>
#include <math.h>

enum{
  GOING_TF,
  SEARCH
};

class Mainp6
{
public:
  Mainp6(): state_(GOING_TF)
  {
    ros::NodeHandle n;
    pub_std_msgs_ = n.advertise<std_msgs::Int8>("navigator_goals", 1);
    pub_vel_ =  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

    client = n.serviceClient<softarq_msgs::Distance>("detecta_obj");

  }

  void step()
  {
    geometry_msgs::Twist motor;
    motor.linear.x = 0;
    motor.linear.y = 0;
    motor.linear.z = 0;
    motor.angular.x =0;
    motor.angular.y =0;

    switch (state_)
    {
    case GOING_TF:
      motor.angular.z = 0;
      wp.data = count;
      count++;
      break;
    case SEARCH:
      motor.angular.z = 0.2;
      client.call(srv);
      break;
    }

    pub_vel_.publish(motor);
    pub_std_msgs_.publish(wp);
  }

private:
  ros::NodeHandle n;

  ros::Publisher pub_std_msgs_;
  ros::Publisher pub_vel_;
  ros::ServiceClient client;
  softarq_msgs::Distance srv;

  int state_ = 0;
  int count = 0;
  std_msgs::Int8 wp;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");

  Mainp6 p6;
  ros::Rate loop_rate(5);
  while (ros::ok())
  {
    p6.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
