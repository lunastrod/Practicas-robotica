#include <string>

#include "behavior_trees/saluda.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"



namespace behavior_trees
{

saluda::saluda(const std::string& name): BT::ActionNodeBase(name, {})
{
  inicio.x=0;//TODO: guardar la posicion inicial (maybe esta?)
  inicio.y=0;
  inicio.z=0;
}

void saluda::halt()
{
  ROS_INFO("saluda halt");
}

BT::NodeStatus saluda::tick()
{
  ROS_INFO("saluda tick");
  if(false){//TODO: dialog flow intent saludo
    return BT::NodeStatus::RUNNING;
  }
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
