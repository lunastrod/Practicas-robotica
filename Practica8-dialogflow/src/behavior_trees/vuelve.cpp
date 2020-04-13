#include <string>

#include "behavior_trees/vuelve.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

vuelve::vuelve(const std::string& name): BT::ActionNodeBase(name, {})
{
  sub_running = n.subscribe("/navigator/isrunning",1,&vuelve::running_callback, this);
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
  inicio.x=0;
  inicio.y=0;
  inicio.z=0;
}

void vuelve::running_callback(const std_msgs::Bool& running){
  if(navegando && !running.data){
    ROS_INFO("he llegado al inicio\n");
    navegando=false;
  }
}

void vuelve::halt()
{
  ROS_INFO("vuelve halt");
}

BT::NodeStatus vuelve::tick()
{
  navegando=true;
  if(navegando){
    if(!goalsent){
      ROS_INFO("volviendo a la posicion inicial");
      pub_goal.publish(inicio);
      goalsent=true;
    }
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("terminado");
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
