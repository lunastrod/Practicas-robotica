#ifndef BEHAVIOR_TREES_ELIGEBOLSA_H
#define BEHAVIOR_TREES_ELIGEBOLSA_H

#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include <string>

namespace behavior_trees
{

class eligebolsa : public BT::ActionNodeBase
{
  public:
    explicit eligebolsa(const std::string& name);

    void halt();

    BT::NodeStatus tick();

  private:
    bool terminado=false;
    std::string bolsa;//debería ser un objeto que darknet reconozca
};

}  // namespace behavior_trees

#endif  // BEHAVIOR_TREES_ELIGEBOLSA_H
