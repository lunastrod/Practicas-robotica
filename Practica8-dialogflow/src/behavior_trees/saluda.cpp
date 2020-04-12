#include <string>

#include "behavior_trees/saluda.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"



namespace behavior_trees
{

saluda::saluda(const std::string& name): BT::ActionNodeBase(name, {})
{
  
}

void saluda::halt()
{
  ROS_INFO("saluda halt");
}

BT::NodeStatus saluda::tick()
{
  if(esperando){
    ROS_INFO("esperando saludo");
    esperando=false;//TODO:temporal
    return BT::NodeStatus::RUNNING;
  }
  if(hablando){//TODO: dialog flow intent saludo
    ROS_INFO("saludando");
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("saludo terminado\n");
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
