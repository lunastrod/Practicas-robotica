#include "stdio.h"

#include "ros/ros.h"
//#include <tf/transform_listener.h>
//#include "actionlib/client/simple_action_server.h"
#include "sensor_msgs/CameraInfo.h"
#include "darknet_ros_msgs/BoundingBoxes.h"

class camara{
public:
  camara(){
    ros::NodeHandle n_;
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &camara::boxesCallBack, this);
    //sub_camera_ = n_.subscribe("/camera/rgb/camera_info", 1, &camara::cameraCallBack, this);
  }
  /*
  void cameraCallBack(const sensor_msgs::CameraInfo& msg){
    image_width = msg.width;
    image_height = msg.height;
  }
  */
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    objeto_detectado_ = false;
    if(!msg.bounding_boxes[0].Class.compare(tipo_objeto)){
      centrox = (msg.bounding_boxes[0].xmin + msg.bounding_boxes[0].xmax) / 2;
      centroy = (msg.bounding_boxes[0].ymin + msg.bounding_boxes[0].ymax) / 2;
      objeto_detectado_ = true;
      ROS_INFO("objeto detectado en (%d,%d)\n",centrox,centroy);
    }
  }
private:
  const std::string tipo_objeto = "person";
  //int image_width = 640;
  //int image_height = 480;
  int centrox;
  int centroy;
  bool objeto_detectado_ = false;
  ros::Subscriber sub_objetos_;
  ros::Subscriber sub_camera_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "busquedap6");
  camara cam;
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
