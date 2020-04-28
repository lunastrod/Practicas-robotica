#include <string>
#include "ros/ros.h"

#include "behavior_trees/dialogo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ejemploDF.h"


#include <sstream>

namespace behavior_trees
{

dialogo::dialogo(const std::string& name, const BT::NodeConfiguration& config)
  : ActionNodeBase(name, config)
{

}

void dialogo::halt()
{
  ROS_INFO("dialogo halt");
}

BT::NodeStatus dialogo::tick()
{
  gb_dialog::ExampleDF forwarder;
  std::string respuesta;
  std::string nombre;
  std::string color;
  std::string param_name;
  std::string str;



  nombre="myname";
  color="red";
  setOutput("color", color );
  setOutput("personname", nombre );
  return BT::NodeStatus::SUCCESS;//TODO:temp

  if(esperando){
    ROS_INFO("esperando un nombre y color de camiseta");

    forwarder.listen();
    ros::spinOnce();
    str = forwarder.getintentfound();
    respuesta = forwarder.getresponse();
    param_name = forwarder.getparamname();

    ROS_INFO("[Robot]: detectado %s", str.c_str());
    if(!str.compare("dialogo")){
      if(!param_name.compare("given-name")){
        nombre = forwarder.getobject();
      }
      else if(!param_name.compare("color")){
        color = forwarder.getobject();
      }
      ros::spinOnce();
      esperando=false;//TODO:temporal
    }else
    return BT::NodeStatus::RUNNING;
  }
  if(hablando){//TODO: dialog flow intent

    ROS_INFO("hablando");
    return BT::NodeStatus::RUNNING;
  }


//  ROS_INFO("[Robot]: objeto %s", objeto.c_str());
  setOutput("color", color );
  setOutput("personname", nombre );
  ros::spinOnce();
  //ROS_INFO("lugar elegido: %s\n",msg_lugar.data.c_str());
  return BT::NodeStatus::SUCCESS;
}

BT::PortsList dialogo::providedPorts()
{
    return {
      BT::OutputPort<std::string>("color"),
      BT::OutputPort<std::string>("personname")
    };
}

}  // namespace behavior_trees
