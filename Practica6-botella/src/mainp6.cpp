#include "ros/ros.h"
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>

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
    pub_std_msgs_ = n.advertise<std_msgs::Int8>("navigator/goals", 1);
    pub_vel_ =  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

    sub_nav_ = n.subscribe("/navigator/isrunning", 1, &Mainp6::isrunningCallback, this);
    client = n.serviceClient<softarq_msgs::Distance>("detecta_obj");

  }

  void isrunningCallback(const std_msgs::Bool& msg)
  {
    running_=msg.data;
  }

  void step()
  {
    geometry_msgs::Twist motor;
    switch (state_)
    {
    case GOING_TF:
      wp.data = count;
      ROS_INFO("[botella] goint to the next goal");
      if(running_ == false){
        count++;
        state_ = SEARCH;
      }
      break;
    case SEARCH:
      motor.linear.x = 0;
      motor.linear.y = 0;
      motor.linear.z = 0;
      motor.angular.x =0;
      motor.angular.y =0;
      motor.angular.z = TURNING_SPEED;
      client.call(srv);
      ROS_INFO("[botella] searching...");
      if ((ros::Time::now() - turn_ts_).toSec() > TURNING_TIME )
      {
        turn_ts_ = ros::Time::now();
        state_ = GOING_TF;
      }
      pub_vel_.publish(motor);
      break;
    }


    pub_std_msgs_.publish(wp);
  }

private:
  double TURNING_SPEED = 0.2;
  double TURNING_TIME = 1/TURNING_SPEED;
  ros::NodeHandle n;

  ros::Subscriber sub_nav_;
  ros::Publisher pub_std_msgs_;
  ros::Publisher pub_vel_;
  ros::ServiceClient client;
  softarq_msgs::Distance srv;

  ros::Time turn_ts_;

  int state_;
  int count = 1;
  bool running_;
  std_msgs::Int8 wp;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mainp6");

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
