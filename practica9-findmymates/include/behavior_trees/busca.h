#ifndef BEHAVIOR_TREES_BUSCA_H
#define BEHAVIOR_TREES_BUSCA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

class busca : public BT::SyncActionNode
{
  public:
    busca(const std::string& name, const BT::NodeConfiguration& config);

    static BT::PortsList providedPorts();

    //void halt();
    BT::NodeStatus tick();
  private:
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_BUSCA_H
