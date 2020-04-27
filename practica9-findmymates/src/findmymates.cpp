#include "behavior_trees/busca.h"
#include "behavior_trees/dialogo.h"
#include "behavior_trees/informacion.h"
#include "behavior_trees/navegacion.h"
#include "behavior_trees/saludo.h"
#include "behavior_trees/vuelve.h"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "ros/package.h"

/*
  saludo: dialog navegacion
    -viaja a la posicion inicial
    -espera a que el operador arranque
    guarda la posicion inicial en variable de clase
    outputs: posicion inicial
  secuencia busqueda
  {
      busca: dialog
        -recibe la posicion que dice el operador
        ejemplo: habitacion, salon, cocina
        outputs: posicion objetivo

      navegacion: navigation y darknet
        -va a la posicion que ha dicho el operador
        inputs: posicion objetivo

      dialogo: dialog
        -habla con la persona que está en la posicion
        -recoge informacion de la persona
        ejemplo: nombre, descripcion...
        outputs: informacion personal?

      vuelve: navigation y darknet
        -vuelve al operador
        input:posicion inicial

      informacion: dialog
        -habla con el operador
        input: informacion personal?
        devuelve la informacion recogida al operador
  }

*/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "behavior_tree");
  ros::NodeHandle n;

  BT::BehaviorTreeFactory factory;

  factory.registerNodeType<behavior_trees::busca>("busca");
  factory.registerNodeType<behavior_trees::dialogo>("dialogo");
  factory.registerNodeType<behavior_trees::informacion>("informacion");
  factory.registerNodeType<behavior_trees::navegacion>("navegacion");
  factory.registerNodeType<behavior_trees::saludo>("saludo");
  factory.registerNodeType<behavior_trees::vuelve>("vuelve");

/*
  BT::PortsList say_something_ports = { BT::InputPort<std::string>("posicion") };
  factory.registerSimpleAction("SaySomething2", SaySomethingSimple,
                               say_something_ports );
*/
  std::string pkgpath = ros::package::getPath("practica9-findmymates");
  std::string xml_file = pkgpath + "/trees/findmymates.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(1);

  bool finish = false;
  while (ros::ok() && !finish)
  {
    finish = tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;
    //ROS_INFO("aaa");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
