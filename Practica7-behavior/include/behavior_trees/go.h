#ifndef BEHAVIOR_TREES_GO_H
#define BEHAVIOR_TREES_GO_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

class go : public BT::ActionNodeBase
{
  public:
    explicit go(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    int counter_;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_GO_H
