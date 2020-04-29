#include <string>

#include "behavior_trees/busca.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ejemploDF.h"

#include "std_msgs/String.h"
#include <sstream>

#include "ros/ros.h"

namespace behavior_trees
{

busca::busca(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}

void busca::halt()
{
  ROS_INFO("busca halt");
}

BT::NodeStatus busca::tick()
{
  gb_dialog::ExampleDF forwarder;
  std::string respuesta;
  std::string lugar;
  std::string str;
  std::string intnt_buscado = "Find my mates";
/*
  lugar="kitchen";
  setOutput("pos", lugar );
  return BT::NodeStatus::SUCCESS;//TODO:temp
*/

  if(esperando){
    //ROS_INFO("esperando una ubicacion");
    forwarder.setintent(intnt_buscado);
    forwarder.listen();
    ros::spinOnce();

    str = forwarder.getintentfound();
    respuesta = forwarder.getresponse();
    lugar = forwarder.getobject();
    //ROS_INFO("[Robot]: detectado %s", str.c_str());
    ROS_INFO("[Robot]: De camino a %s", lugar.c_str());
    if(!str.compare("Find my mates")){
      ros::spinOnce();
      setOutput("pos", lugar );
      esperando=false;//TODO:temporal
    }
    return BT::NodeStatus::RUNNING;
  }
  if(hablando){//TODO: dialog flow intent
    return BT::NodeStatus::RUNNING;
  }
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList busca::providedPorts()
{
    // This action has a single input port called "message"
    // Any port must have a name. The type is optional.
    return { BT::OutputPort<std::string>("pos") };
}

}  // namespace behavior_trees
