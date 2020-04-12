#include <string>

#include "behavior_trees/siguepersona.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

siguepersona::siguepersona(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
}

void siguepersona::halt()
{
  ROS_INFO("siguepersona halt");
}

BT::NodeStatus siguepersona::tick()
{
  if(hablando){
    buscando=false;
    navegando=false;
    ROS_INFO("iniciando despedida");
    hablando=false;//TODO:temp
    return BT::NodeStatus::RUNNING;
  }
  if(buscando){
    ROS_INFO("buscando personas");
    buscando=false;//TODO:temp
    navegando=true;
    return BT::NodeStatus::RUNNING;
  }
  if(navegando){
    ROS_INFO("navegando a persona en la posicion:");//TODO:posicion
    navegando=false;//TODO:temp
    buscando=true;
    hablando=true;
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("despedida completada\n");
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
