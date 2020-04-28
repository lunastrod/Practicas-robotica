#include "behavior_trees/busca.h"
#include "behavior_trees/dialogo.h"
#include "behavior_trees/informacion.h"
#include "behavior_trees/navegacion.h"
#include "behavior_trees/saludo.h"
#include "behavior_trees/vuelve.h"

#include "ros/ros.h"
#include "behaviortree_cpp_v3/behavior_tree.h"
#include "behaviortree_cpp_v3/bt_factory.h"

#include "sound_play/sound_play.h"

#include "ros/package.h"

/*
  saludo: dialog navegacion
    -viaja a la posicion del operador (guardada en constants.h)
    -espera a que el operador arranque
  secuencia busqueda
  {
      busca: dialog
        -recibe la posicion que dice el operador
        ejemplo: habitacion, salon, cocina
        outputs: pos

      navegacion: navigation y darknet
        -va a la posicion que ha dicho el operador
        inputs: getpos

      dialogo: dialog
        -habla con la persona que está en la posicion
        -recoge informacion de la persona
        outputs: personname color

      vuelve: navigation y darknet
        -vuelve al operador (guardada en constants.h)

      informacion: dialog
        -habla con el operador
        input: getpersonname getcolor
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

  std::string pkgpath = ros::package::getPath("practica9-findmymates");
  std::string xml_file = pkgpath + "/trees/findmymates.xml";

  BT::Tree tree = factory.createTreeFromFile(xml_file);

  ros::Rate loop_rate(1);

  bool finish = false;
  while (ros::ok() && !finish)
  {
    finish = tree.root_node->executeTick() == BT::NodeStatus::SUCCESS;
    //sleepok(2, n);
    //ROS_INFO("aaa");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
