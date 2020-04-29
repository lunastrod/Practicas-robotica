#include <string>

#include "behavior_trees/saludo.h"

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"
#include "ejemploDF.h"
#include "ros/ros.h"

#include "constants.h"

namespace behavior_trees
{

saludo::saludo(const std::string& name): BT::ActionNodeBase(name, {})
{
  pub_goal=n.advertise<geometry_msgs::Point>("/navigator/goals",1);
  sub_running = n.subscribe("/navigator/isrunning",1,&saludo::running_callback, this);
}

void saludo::running_callback(const std_msgs::Bool& running){
  if(active && !running.data){
    ROS_INFO("he llegado al objetivo\n");
    navegando=false;
  }
}

void saludo::halt()
{
  ROS_INFO("saluda halt");
}

BT::NodeStatus saludo::tick()
{
  active=true;
  if(navegando){
    goal.x=inicio[0];
    goal.y=inicio[1];
    goal.z=0;

    pub_goal.publish(goal);
    ros::spinOnce();
    ROS_INFO("%f,%f,%f", goal.x, goal.y, goal.z);
    esperando=true;
    return BT::NodeStatus::RUNNING;
  }
  if(esperando){
    ROS_INFO("esperando saludo");
    gb_dialog::ExampleDF forwarder;
    forwarder.listen();
    ros::spinOnce();
    std::string respuesta = forwarder.getresponse();
    std::string str = forwarder.getintentfound();
    if(!str.compare("Default Welcome Intent")){
      ROS_INFO("[Robot]: %s", respuesta.c_str());
      esperando=false;
    }
    return BT::NodeStatus::RUNNING;
  }
  ROS_INFO("saludo terminado\n");
  active=false;
  return BT::NodeStatus::SUCCESS;
}

}  // namespace behavior_trees
