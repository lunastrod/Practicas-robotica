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
#include "std_msgs/Int64.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"

void messageCallback(const std_msgs::Int64::ConstPtr& msg)
{
  ROS_INFO("Data: [%ld]", msg->data);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "num_publisher");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/message", 1, messageCallback);
  ros::Publisher num_pub = n.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    geometry_msgs::Twist motor;

    motor.linear = Vector3(0.2, 0, 0)
    motor.angular = Vector3(0,  0, 0)

    msg.data = count++;

    motor_pub.publish(motor);

    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
 }
