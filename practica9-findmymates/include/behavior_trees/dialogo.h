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
    dialogo(const std::string& name, const BT::NodeConfiguration& config);

    static BT::PortsList providedPorts();

    void halt() override;
    BT::NodeStatus tick() override;
  private:
    //ros::NodeHandle n;
    std::string msg_color;
    std::string msg_nombre;

    bool nombre_conseguido = false;
    bool color_conseguido = false;
    bool esperando=true;
    bool hablando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_DIALOGO_H
