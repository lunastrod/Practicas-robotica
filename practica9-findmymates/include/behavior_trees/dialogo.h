#ifndef BEHAVIOR_TREES_DIALOGO_H
#define BEHAVIOR_TREES_DIALOGO_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>
#include "ros/ros.h"
#include "std_msgs/String.h"

namespace behavior_trees
{

class dialogo : public BT::ActionNodeBase
{
  public:
    explicit dialogo(const std::string& name);

    void halt();
    BT::NodeStatus tick();
  private:
    //ros::NodeHandle n;
    std_msgs::String msg_color;
    std_msgs::String msg_nombre;

    bool esperando=true;
    bool hablando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_DIALOGO_H
