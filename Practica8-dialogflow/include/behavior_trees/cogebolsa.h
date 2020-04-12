#ifndef BEHAVIOR_TREES_COGEBOLSA_H
#define BEHAVIOR_TREES_COGEBOLSA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "std_msgs/String.h"

namespace behavior_trees
{

class cogebolsa : public BT::ActionNodeBase
{
  public:
    explicit cogebolsa(const std::string& name);

    void bolsa_callback(const std_msgs::String& msg);

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Subscriber sub_bolsa;
    std::string bolsa;
    ros::Publisher pub_goal;
    geometry_msgs::Point goal;

    bool esperando=true;
    bool buscando=false;
    bool navegando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_COGEBOLSA_H
