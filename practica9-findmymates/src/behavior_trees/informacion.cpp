#include <string>

#include "behavior_trees/informacion.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

informacion::informacion(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}

void informacion::halt()
{
  ROS_INFO("informacion halt");
}

BT::NodeStatus informacion::tick()
{

  BT::Optional<std::string> color = getInput<std::string>("getcolor");
  if (!color)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         color.error() );
  }
  BT::Optional<std::string> name = getInput<std::string>("getpersonname");
  if (!name)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         name.error() );
  }

  std::cout << "Robot says: " << color.value() << std::endl;
  std::cout << "Robot says: " << name.value() << std::endl;

  ROS_INFO("informacion tick");
  //return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList informacion::providedPorts()
{
    return {
      BT::InputPort<std::string>("getcolor"),
      BT::InputPort<std::string>("getpersonname")
    };
}

}  // namespace behavior_trees
