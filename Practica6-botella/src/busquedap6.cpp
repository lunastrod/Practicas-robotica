#include "ros/ros.h"

//#include <tf/transform_listener.h>
//#include "actionlib/client/simple_action_server.h"
#include "sensor_msgs/CameraInfo.h"
#include "darknet_ros_msgs/BoundingBoxes.h"

class camera{
public:
  camera(){
    ros::NodeHandle n_;
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &camara::boxesCallBack, this);
    sub_camera_ = n_.subscribe("/camera/rgb/camera_info", 1, &camara::cameraCallBack, this);

  }
  void cameraCallBack(const sensor_msgs::CameraInfo& msg){
    image_width = msg.width;
  }
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    objeto_detectado_ = false;
    if(!msg.bounding_boxes[0].Class.compare("person")){
      centrox = (msg.bounding_boxes[0].xmin + msg.bounding_boxes[0].xmax) / 2;
      objeto_detectado_ = true;
    }
  }
private:
  int image_width = 640;
  int centrox;
  bool objeto_detectado_ = false;
  ros::Subscriber sub_objetos_;
  ros::Subscriber sub_camera_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "busquedap6");
  camera c;
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    printf("Main\n");
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
