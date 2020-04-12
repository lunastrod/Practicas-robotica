#include <string>

#include "behavior_trees/vuelve.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

vuelve::vuelve(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
}

void vuelve::halt()
{
  ROS_INFO("vuelve halt");
}

BT::NodeStatus vuelve::tick()
{
  if(navegando){
    ROS_INFO("volviendo a la posicion inicial");
    navegando=false;//TODO:temp
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("terminado");
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
