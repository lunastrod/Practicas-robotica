#ifndef BEHAVIOR_TREES_COGEBOLSA_H
#define BEHAVIOR_TREES_COGEBOLSA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "servicios/busqueda.h"

namespace behavior_trees
{

class cogebolsa : public BT::ActionNodeBase
{
  public:
    explicit cogebolsa(const std::string& name);

    void bolsa_callback(const std_msgs::String& msg);
    void running_callback(const std_msgs::Bool& running);

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Subscriber sub_bolsa;
    std::string bolsa;
    ros::Publisher pub_goal;
    geometry_msgs::Point goal;
    ros::Subscriber sub_running;
    ros::ServiceClient srv_busqueda;
    servicios::busqueda msg_busqueda;

    bool goalsent=false;
    bool esperando=true;
    bool buscando=false;
    bool navegando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_COGEBOLSA_H
