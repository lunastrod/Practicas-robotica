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

busca::busca(const std::string& name): BT::ActionNodeBase(name, {})
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

  if(esperando){
    ROS_INFO("esperando una ubicacion");

    forwarder.listen();
    ros::spinOnce();
    str = forwarder.getintentfound();
    respuesta = forwarder.getresponse();
    lugar = forwarder.getobject();
    ROS_INFO("[Robot]: detectado %s", str.c_str());
    ROS_INFO("[Robot]: Lugar %s", lugar.c_str());
    if(!str.compare("Find my mates")){
      ros::spinOnce();
      ROS_INFO("[Robot]: a por %s!", lugar.c_str());
      msg_lugar.data = lugar;
      esperando=false;//TODO:temporal
    }
    return BT::NodeStatus::RUNNING;
  }
  if(hablando){//TODO: dialog flow intent

    ROS_INFO("hablando");
    return BT::NodeStatus::RUNNING;
  }


//  ROS_INFO("[Robot]: objeto %s", objeto.c_str());

  pub_lugar.publish(msg_lugar);
  ros::spinOnce();
  ROS_INFO("lugar elegido: %s\n",msg_lugar.data.c_str());
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
