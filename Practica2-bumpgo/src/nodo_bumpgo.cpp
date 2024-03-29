#include "ros/ros.h"

#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

#define TURNING_TIME 4.0
#define BACKING_TIME 3.0

enum{
  RIGHT_BUMPER=2,
  CENTER_BUMPER=1,
  LEFT_BUMPER=0
};

class BumpGo
{
public:
  BumpGo(): state_(GOING_FORWARD), pressed_(false)
  {
    ros::NodeHandle n_;
    sub_bumber_ = n.subscribe("/mobile_base/events/bumper", 1, &BumpGo::bumperCallback, this);
    pub_vel_ =  n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  }

  void bumperCallback(const kobuki_msgs::BumperEvent& msg)
  {
    if(msg.state==0){
      pressed_=false;
    }
    else{
      pressed_=true;
      bumper_pressed_=msg.bumper;
    }
  }

  void step()
  {
    geometry_msgs::Twist motor;
    motor.linear.y = 0;
    motor.linear.z = 0;
    motor.angular.x =0;
    motor.angular.y =0;

    switch (state_)
    {
    case GOING_FORWARD:
      motor.linear.x = SPEED;
      motor.angular.z = 0;
      if (pressed_)
      {
        press_ts_ = ros::Time::now();
        state_ = GOING_BACK;
        ROS_INFO("GOING_FORWARD -> GOING_BACK");
      }
      break;

    case GOING_BACK:
      motor.linear.x = - SPEED;
      motor.angular.z = 0;

      if ((ros::Time::now() - press_ts_).toSec() > BACKING_TIME )
      {
        turn_ts_ = ros::Time::now();
        state_ = TURNING;
        ROS_INFO("GOING_BACK -> TURNING");
      }
      break;

    case TURNING:
      motor.linear.x = 0;

      if(bumper_pressed_ == RIGHT_BUMPER){
        motor.angular.z = TURNING_SPEED;
      }
      else{
        motor.angular.z = -TURNING_SPEED;
      }

      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING -> GOING_FORWARD");
      }
      break;
    }

    pub_vel_.publish(motor);
  }

private:
  static const int GOING_FORWARD   = 0;
  static const int GOING_BACK   = 1;
  static const int TURNING     = 2;
  const double SPEED = 0.2;
  const double TURNING_SPEED = 0.5;

  int state_;
  int bumper_pressed_;
  bool pressed_;

  ros::Time press_ts_;
  ros::Time turn_ts_;

  ros::NodeHandle n;

  ros::Subscriber sub_bumber_;
  ros::Publisher pub_vel_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bumpgo");

  BumpGo bumpgo;

  ros::Rate loop_rate(20);

  while (ros::ok())
  {
    bumpgo.step();

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
