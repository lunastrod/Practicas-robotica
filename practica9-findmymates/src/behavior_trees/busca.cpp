#include <string>

#include "behavior_trees/busca.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

namespace behavior_trees
{

busca::busca(const std::string& name, const BT::NodeConfiguration& config)
  : SyncActionNode(name, config)
{

}
/*
void busca::halt()
{
  ROS_INFO("busca halt");
}
*/
BT::NodeStatus busca::tick()
{
  BT::Optional<std::string> msg = getInput<std::string>("posicion");
  // Check if optional is valid. If not, throw its error
  if (!msg)
  {
    throw BT::RuntimeError("missing required input [message]: ",
                         msg.error() );
  }

  // use the method value() to extract the valid message.
  std::cout << "Robot says: " << msg.value() << std::endl;
  return BT::NodeStatus::SUCCESS;


  setOutput("posicion", "cocina" );
  ROS_INFO("busca tick");
  return BT::NodeStatus::RUNNING;
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList busca::providedPorts()
{
    // This action has a single input port called "message"
    // Any port must have a name. The type is optional.
    return { BT::OutputPort<std::string>("posicion") };
}

}  // namespace behavior_trees
