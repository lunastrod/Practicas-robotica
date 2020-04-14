#include <string>

#include "behavior_trees/siguepersona.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/ros.h"

#include "ejemploDF.h"

namespace behavior_trees
{

siguepersona::siguepersona(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
  sub_running = n.subscribe("/navigator/isrunning",1,&siguepersona::running_callback, this);
  srv_busqueda = n.serviceClient<servicios::busqueda>("detecta_obj");
}

void siguepersona::halt()
{
  ROS_INFO("siguepersona halt");
}

void siguepersona::running_callback(const std_msgs::Bool& running){
  if(navegando && !running.data){
    ROS_INFO("he llegado a la persona\n");
    navegando=false;
    hablando=false;
    buscando=true;
  }
}

BT::NodeStatus siguepersona::tick()
{
  if(hablando){
    ROS_INFO("iniciando despedida");
    navegando=false;
    buscando=false;
    hablando=false;//TODO:temp
    return BT::NodeStatus::RUNNING;
  }
  if(buscando){
    goalsent=false;
    ROS_INFO("buscando personas");
    msg_busqueda.request.object.data="person";
    srv_busqueda.call(msg_busqueda);
    buscando=!msg_busqueda.response.found.data;//sigue buscando hasta que lo encuentres
    if(msg_busqueda.response.found.data){
      goal=msg_busqueda.response.position;
    }

    navegando=!buscando;
    return BT::NodeStatus::RUNNING;
  }
  if(navegando){
    if(!goalsent){
      ROS_INFO("navegando a persona");//TODO:posicion
      pub_goal.publish(goal);
      goalsent=true;
    }
    gb_dialog::ExampleDF forwarder;
    forwarder.listen();
    ros::spinOnce();
    std::string respuesta = forwarder.getresponse();
    std::string str = forwarder.getintentfound();
    if(!str.compare("Job is done")){
      ROS_INFO("[Robot]: %s", respuesta.c_str());
      hablando=true;//TODO:temporal
    }
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("despedida completada\n");
  return BT::NodeStatus::SUCCESS;

}

}  // namespace behavior_trees
