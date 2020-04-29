#include <string>

#include "behavior_trees/saludo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ejemploDF.h"
#include "ros/ros.h"



namespace behavior_trees
{

saludo::saludo(const std::string& name): BT::ActionNodeBase(name, {})
{

}

void saludo::halt()
{
  ROS_INFO("saluda halt");
}

BT::NodeStatus saludo::tick()
{
  //return BT::NodeStatus::SUCCESS;//TODO:temp

  if(esperando){
    ROS_INFO("esperando saludo");
    gb_dialog::ExampleDF forwarder;
    //forwarder.setintent("Default Welcome Intent");
    forwarder.listen();
    ros::spinOnce();
    std::string respuesta = forwarder.getresponse();
    std::string str = forwarder.getintentfound();
    if(!str.compare("Default Welcome Intent")){
      ROS_INFO("[Robot]: %s", respuesta.c_str());
      esperando=false;//TODO:temporal
    }
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("saludo terminado\n");
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
