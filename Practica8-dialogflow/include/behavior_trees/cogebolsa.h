#ifndef BEHAVIOR_TREES_COGEBOLSA_H
#define BEHAVIOR_TREES_COGEBOLSA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

class cogebolsa : public BT::ActionNodeBase
{
  public:
    explicit cogebolsa(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    bool terminado;
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_COGEBOLSA_H
