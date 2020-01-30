// Copyright 2019 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ros/ros.h"

#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

#define TURNING_TIME 5.0
#define BACKING_TIME 3.0

class BumpGo
{
public:
  BumpGo(): state_(GOING_FORWARD), pressed_(false)
  {
    // sub_bumber_ = n_.subscribe(...);
    // pub_vel_ = n_.advertise<...>(...)
  }

  void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg)
  {
    if(msg.state==0) pressed_=false;
    else pressed_=true;
  }

  void step()
  {
    geometry_msgs::Twist cmd;
    motor.linear.y = 0;
    motor.linear.z = 0;
    motor.angular.x =0;
    motor.angular.y =0;

    switch (state_)
    {
    case GOING_FORWARD:
      motor.linear.x = VELOCITY;
      motor.angular.z =0;

      if (pressed_)
      {
        press_ts_ = ros::Time::now();
        state_ = GOING_BACK;
        ROS_INFO("GOING_FORWARD -> GOING_BACK");
      }
      break;

    case GOING_BACK:
      cmd.linear.x = -VELOCITY;
      cmd.angular.z = 0;

      if ((ros::Time::now() - press_ts_).toSec() > BACKING_TIME )
      {
        turn_ts_ = ros::Time::now();
        state_ = TURNING;
        ROS_INFO("GOING_BACK -> TURNING");
      }
      break;

    case TURNING:
      cmd.linear.x = VELOCITY;
      cmd.angular.z = 0.5;

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
  ros::NodeHandle n_;

  static const int GOING_FORWARD   = 0;
  static const int GOING_BACK   = 1;
  static const int TURNING     = 2;
  static const float VELOCITY = 0.1;

  int state_;
  bool pressed_;

  ros::Time press_ts_;
  ros::Time turn_ts_;

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
