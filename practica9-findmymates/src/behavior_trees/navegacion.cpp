#include <string>

#include "behavior_trees/navegacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

navegacion::navegacion(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}

void navegacion::halt()
{
  ROS_INFO("navegacion halt");
}

BT::NodeStatus navegacion::tick()
{
  BT::Optional<std::string> pos = getInput<std::string>("getpos");
  if (!pos)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         pos.error() );
  }

  std::cout << "Robot says: " << pos.value() << std::endl;
  return BT::NodeStatus::SUCCESS;

  ROS_INFO("navegacion tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList navegacion::providedPorts()
{
    return { BT::InputPort<std::string>("getpos") };
}

}  // namespace behavior_trees
