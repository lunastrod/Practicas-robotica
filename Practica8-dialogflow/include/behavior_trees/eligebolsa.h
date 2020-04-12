#ifndef BEHAVIOR_TREES_ELIGEBOLSA_H
#define BEHAVIOR_TREES_ELIGEBOLSA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

#include "ros/ros.h"
#include "std_msgs/String.h"

namespace behavior_trees
{

class eligebolsa : public BT::ActionNodeBase
{
  public:
    explicit eligebolsa(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    ros::NodeHandle n;
    ros::Publisher pub_bolsa;
    std_msgs::String msg_bolsa;
    
    bool esperando=true;
    bool hablando=false;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_ELIGEBOLSA_H
