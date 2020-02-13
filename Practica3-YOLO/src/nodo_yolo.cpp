#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/CameraInfo.h"
#include "darknet_ros_msgs/BoundingBoxes.h"


class Robot{
public:
  Robot(){
    ros::NodeHandle n_;
    //TODO: no estoy seguro de si es /scan, es posible que no
    sub_laser_  = n_.subscribe("/scan", 1, &Robot::laserCallBack, this);
    //TODO: tampoco estoy seguro de que sea /bounding_boxes
    //aun no funciona, resolver el TODO de los includes
    //sub_objetos_= n_.subscribe("/bounding_boxes", 1, &Robot::boxesCallBack, this);
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &Robot::boxesCallBack, this);
    sub_camera_ = n_.subscribe("/camera/rgb/camera_info", 1, &Robot::cameraCallBack, this);
    //Para comprobar las dimensiones de las imagenes, con llamar una vez al principio vale

    pub_vel_    = n_.advertise<geometry_msgs::Twist>("/mobile_base/commands/velocity", 1);
  }
  void laserCallBack(const sensor_msgs::LaserScan& msg){
    //TODO:cuando se reciba un mensaje laser (rellenar esta funcion)
    double temp = msg.ranges[sizeof(msg.ranges)/sizeof(double)/2];
    if(temp<=20.0){
      distancia = temp;
    }
    //printf("ranges: %lf\n",distancia);
    //printf("%lf\n",msg.intensities[180]);
  }


  void cameraCallBack(const sensor_msgs::CameraInfo& msg){
    //image_height = msg.height;
    image_width = msg.width;
  }

  //aun no funciona, hay que resolver el TODO de los include
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    //TODO:cuando se reciba un mensaje de bounding_boxes (rellenar esta funcion)
    persona_detectada_ = false;
    if(!msg.bounding_boxes[0].Class.compare("person")){
      centrox = (msg.bounding_boxes[0].xmin + msg.bounding_boxes[0].xmax) / 2;
      //printf("%d",msg.Class.compare("chair"));
      persona_detectada_ = true;
      /*ROS_INFO("person");
    } else {
      ROS_INFO("not person");*/
    }
    //printf("xMax: %ld\n",msg.bounding_boxes[0].xmax);
    //ROS_INFO(msg.bounding_boxes[0].xmax);

  }

  void step(){
    //Funcion que se ejecuta a cada pasada del bucle en main
    geometry_msgs::Twist motor;
    motor.linear.y = 0;
    motor.linear.z = 0;
    motor.angular.x =0;
    motor.angular.y =0;

    //PSEUDOCODIGO
    ROS_INFO("%lf\n",distancia);
    if (!persona_detectada_){
      motor.angular.z = 0;
      motor.linear.x = 0;
      pub_vel_.publish(motor);
      return; //no te muevas
    }
    if (distancia <= DIST_MIN) {
      ROS_INFO("demasiado cerca: %lf\n",distancia);
      motor.linear.x = -SPEED;//hacia detrás
    }
    else if(distancia >= DIST_MAX){
      ROS_INFO("demasiado lejos: %lf\n",distancia);
      motor.linear.x = SPEED;//hacia delante
    }
    else{
      ROS_INFO("estoy bien: %lf\n",distancia);
      motor.linear.x = 0;
    }
    if(centrox <= image_width/3){
      motor.angular.z = TURNING_SPEED;//gira a la derecha
      motor.linear.x = 0;
    }
    else if(centrox >= (image_width/3)*2){
      motor.angular.z = -TURNING_SPEED;//gira a la izquierda
      motor.linear.x = 0;
    }
    else{
      motor.angular.z = 0;//no gires
      if (distancia <= DIST_MIN) {
        ROS_INFO("demasiado cerca: %lf\n",distancia);
        motor.linear.x = -SPEED;//hacia detrás
      }
      else if(distancia >= DIST_MAX){
        ROS_INFO("demasiado lejos: %lf\n",distancia);
        motor.linear.x = SPEED;//hacia delante
      }
      else{
        ROS_INFO("estoy bien: %lf\n",distancia);
        motor.linear.x = 0;
      }
    }

    pub_vel_.publish(motor);
  }

private:
  const double DIST_MIN = 0.7;
  const double DIST_MAX = 1.5;
  const double SPEED = 0.1;
  const double TURNING_SPEED = 0.3;
  int image_width = 640;
  double distancia = 1;
  int centrox;
  bool persona_detectada_ = false;
  ros::Subscriber sub_objetos_;
  ros::Subscriber sub_laser_;
  ros::Subscriber sub_camera_;
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
    printf("Main\n");
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
