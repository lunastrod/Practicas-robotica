#include <string>

#include "behavior_trees/navegacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

navegacion::navegacion(const std::string& name, const BT::NodeConfiguration& config)
  : SyncActionNode(name, config)
{

}
/*
void navegacion::halt()
{
  ROS_INFO("navegacion halt");
}
*/
BT::NodeStatus navegacion::tick()
{
  setOutput("posicion", "cocina" );
  return BT::NodeStatus::SUCCESS;


  ROS_INFO("navegacion tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList navegacion::providedPorts()
{
    // This action has a single input port called "message"
    // Any port must have a name. The type is optional.
    return { BT::InputPort<std::string>("posicion") };
}

}  // namespace behavior_trees
