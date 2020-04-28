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
  BT::Optional<std::string> msg = getInput<std::string>("getpos");
  // Check if optional is valid. If not, throw its error
  if (!msg)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         msg.error() );
  }

  // use the method value() to extract the valid message.
  std::cout << "Robot says: " << msg.value() << std::endl;
  return BT::NodeStatus::SUCCESS;

  ROS_INFO("navegacion tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList navegacion::providedPorts()
{
    // This action has a single input port called "message"
    // Any port must have a name. The type is optional.
    return { BT::InputPort<std::string>("getpos") };
}

}  // namespace behavior_trees
