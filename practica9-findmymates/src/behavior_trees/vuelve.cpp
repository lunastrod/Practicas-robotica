#include <string>

#include "behavior_trees/vuelve.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

#include "constants.h"


namespace behavior_trees
{

vuelve::vuelve(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
  sub_running = n.subscribe("/navigator/isrunning",1,&vuelve::running_callback, this);
}

void vuelve::running_callback(const std_msgs::Bool& running){
  if(active && !running.data){
    ROS_INFO("he llegado al objetivo\n");
    navegando=false;
  }
}

void vuelve::halt()
{
  ROS_INFO("vuelve halt");
}

BT::NodeStatus vuelve::tick()
{
  active=true;
  if(!navegando){
    active=false;
    return BT::NodeStatus::SUCCESS;
  }
  goal.x=inicio[0];
  goal.y=inicio[1];
  goal.z=0;

  pub_goal.publish(goal);
  ros::spinOnce();
  ROS_INFO("%f,%f,%f", goal.x, goal.y, goal.z);
  return BT::NodeStatus::RUNNING;
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
