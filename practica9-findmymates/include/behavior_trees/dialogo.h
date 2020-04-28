#ifndef BEHAVIOR_TREES_DIALOGO_H
#define BEHAVIOR_TREES_DIALOGO_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

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
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_DIALOGO_H
