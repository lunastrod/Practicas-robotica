#include "stdio.h"

#include "ros/ros.h"
//#include <tf/transform_listener.h>
//#include "actionlib/client/simple_action_server.h"
#include "sensor_msgs/CameraInfo.h"
#include "darknet_ros_msgs/BoundingBoxes.h"
#include "sensor_msgs/PointCloud2.h"

///camera/depth_registered/points
//Type: sensor_msgs/PointCloud2


class camara{
public:
  camara(){
    ros::NodeHandle n_;
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &camara::boxesCallBack, this);
    sub_camera_ = n_.subscribe("/camera/rgb/camera_info", 1, &Robot::cameraCallBack, this);
    sub_point_cloud_ = n_.subscribe("/camera/depth_registered/points",1,&pointcloudCallBack,this);
  }
  void boxesCallBack(const darknet_ros_msgs::BoundingBoxes& msg){
    objeto_detectado_ = false;
    if(!msg.bounding_boxes[0].Class.compare(tipo_objeto)){
      centrox = (msg.bounding_boxes[0].xmin + msg.bounding_boxes[0].xmax) / 2;
      centroy = (msg.bounding_boxes[0].ymin + msg.bounding_boxes[0].ymax) / 2;
      objeto_detectado_ = true;
      ROS_INFO("objeto detectado en (%d,%d)\n",centrox,centroy);
    }
  }
  void pointcloudCallBack(const sensor_msgs::PointCloud2& msg){
    sensor_msgs::PointCloud2 * p = msg.data[msg.width*centroy+centrox];
		ROS_INFO("point: (%lf, %lf, %lf)", p->x, p->y, p->z);
	}
private:
  const std::string tipo_objeto = "person";
  /*
  int image_width;
  int image_height;
  */
  int centrox;
  int centroy;
  bool objeto_detectado_ = false;
  ros::Subscriber sub_objetos_;
  ros::Subscriber sub_point_cloud_;
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
