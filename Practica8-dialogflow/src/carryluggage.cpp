

/*
1. El robot comienza en una habitación en una posición conocida.
2. Existen dos bolsas, y el operador señala una de ellas
3. El robot coge una de ellas
4. El operador comienza a andar y sale de la casa a una posición
desconocida
5. El operador le indica al robot que ha llegado, y agradece al robot
que le haya acompañado.
6. El robot vuelve a la habitación de origen

pseudocodigo:
    saluda -> intent de dialog
        habla
        devuelve running hasta que termine el saludo
        guarda la posicion actual conocida
    eligebolsa -> intent de dialog
        habla
        devuelve running hasta que sepas a qué bolsa acercarte
        guarda la bolsa a la que se tiene que acercar en /bolsa_elegida
    cogebolsa -> navigation y darknet
        busca el objeto que ha dicho el operador y va hacia él
        devuelve running hasta llegar al objeto
    siguepersona-> dialog, navigation y darknet
        busca personas y va hacia ellas hasta que se inicia la despedida, después habla
        devuelve running hasta que la persona se despida
    vuelve -> navigation
        va a la posicion inicial
        devuelve running hasta llegar a la posicion inicial

    navp8:
        recive un geometry_msgs::Point por navigator/goals
    busquedap8:
        recibe un string para buscar con darknet y saca un geometry_msgs::Point por un servicio
*/
#include "behavior_trees/saluda.h"
#include "behavior_trees/eligebolsa.h"
#include "behavior_trees/cogebolsa.h"
#include "behavior_trees/siguepersona.h"
#include "behavior_trees/vuelve.h"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "behavior_tree");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<behavior_trees::saluda>("saluda");
  factory.registerNodeType<behavior_trees::eligebolsa>("eligebolsa");
  factory.registerNodeType<behavior_trees::cogebolsa>("cogebolsa");
  factory.registerNodeType<behavior_trees::siguepersona>("siguepersona");
  factory.registerNodeType<behavior_trees::vuelve>("vuelve");

  std::string pkgpath = ros::package::getPath("practica8-dialogflow");
  std::string xml_file = pkgpath + "/trees/carryluggage.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(5);

  int count = 0;

  bool finish = false;
  while (ros::ok() && !finish)
  {
    finish = tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;

    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
