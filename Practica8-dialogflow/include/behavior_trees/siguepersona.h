#ifndef BEHAVIOR_TREES_SIGUEPERSONA_H
#define BEHAVIOR_TREES_SIGUEPERSONA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "geometry_msgs/Twist.h"
#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/Bool.h"
#include "servicios/busqueda.h"


namespace behavior_trees
{

class siguepersona : public BT::ActionNodeBase
{
  public:
    explicit siguepersona(const std::string& name);
    void running_callback(const std_msgs::Bool& running);
    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher pub_goal;
    ros::Publisher pub_vel_;
    ros::Subscriber sub_running;
    geometry_msgs::Point goal;
    ros::ServiceClient srv_busqueda;
    servicios::busqueda msg_busqueda;
    geometry_msgs::Twist motor;

    bool goalsent=false;
    bool buscando=true;
    bool navegando=false;
    bool hablando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_SIGUEPERSONA_H
