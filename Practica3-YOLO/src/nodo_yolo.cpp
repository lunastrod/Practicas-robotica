#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/LaserScan.h"
//TODO: estos 2 dan problemas
//#include "darknet_ros_msgs/BoundingBoxes.h"
//#include "darknet_ros_msgs/BoundingBox.h"

class Robot{
public:
  Robot(){
    ros::NodeHandle n_;
    //TODO: no estoy seguro de si es /scan, es posible que no
    sub_laser_  = n_.subscribe("/scan", 1, &Robot::laserCallBack, this);
    //TODO: tampoco estoy seguro de que sea /bounding_boxes
    //aun no funciona, resolver el TODO de los includes
    //sub_objetos_= n_.subscribe("/bounding_boxes", 1, &Robot::boxesCallBack, this);

    pub_vel_    = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  }
  void laserCallBack(const sensor_msgs::LaserScan& msg){
    //TODO:cuando se reciba un mensaje laser (rellenar esta funcion)
  }
  /*//aun no funciona, hay que resolver el TODO de los include
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    //TODO:cuando se reciba un mensaje de bounding_boxes (rellenar esta funcion)
  }
  */
  void step(){
    //Funcion que se ejecuta a cada pasada del bucle en main
    geometry_msgs::Twist motor;
    motor.linear.y = 0;
    motor.linear.z = 0;
    motor.angular.x =0;
    motor.angular.y =0;
    /*
    PSEUDOCODIGO
    if (darknet no recibe ninguna persona){
      return //no te muevas
    }
    if (laser == demasiado cerca) {
      motor.linear.x = -SPEED;//hacia detrás
    }
    else{
      motor.linear.x = SPEED;//hacia delante
    }
    if(persona a la derecha de la camara){
      motor.angular.z = -TURNING_SPEED;//gira a la derecha
    }
    else if(persona a la izquierda de la camara){
      motor.angular.z = TURNING_SPEED;//gira a la izquierda
    }
    else{
      motor.angular.z = 0;//no gires
    }
    */
    pub_vel_.publish(motor);
  }
private:
  const double SPEED = 0.2;
  const double TURNING_SPEED = 0.5;
  ros::Subscriber sub_objetos_;
  ros::Subscriber sub_laser_;
  ros::Publisher pub_vel_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "bumpgo");
  Robot robot;
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    robot.step();
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
