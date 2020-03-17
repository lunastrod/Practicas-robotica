#include "stdio.h"

#include "ros/ros.h"
//#include <tf/transform_listener.h>
//#include "actionlib/client/simple_action_server.h"
#include "sensor_msgs/CameraInfo.h"

#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/point_field_conversion.h>

#include "darknet_ros_msgs/BoundingBoxes.h"
#include <geometry_msgs/Point.h>
#include "sensor_msgs/PointCloud2.h"

///camera/depth_registered/points
//Type: sensor_msgs/PointCloud2


class camara{
public:
  camara(){
    ros::NodeHandle n_;
    sub_objetos_ = n_.subscribe("/darknet_ros/bounding_boxes", 1, &camara::boxesCallBack, this);
    //sub_camera_ = n_.subscribe("/camera/rgb/camera_info", 1, &camara::cameraCallBack, this);
    sub_point_cloud_ = n_.subscribe("/camera/depth_registered/points",1,&camara::pointcloudCallBack,this);
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
    geometry_msgs::Point p;
    pixelTo3DPoint(msg,0,0,p);
		ROS_INFO("point:(%f,%f,%f)\n", p.x, p.y, p.z);
	}
private:
  void pixelTo3DPoint(const sensor_msgs::PointCloud2 &pCloud, const int u, const int v, geometry_msgs::Point &p)
    {
      /*
      https://answers.ros.org/question/191265/pointcloud2-access-data/
      Function to convert 2D pixel point to 3D point by extracting point
      from PointCloud2 corresponding to input pixel coordinate. This function
      can be used to get the X,Y,Z coordinates of a feature using an
      RGBD camera.
      */
      // get width and height of 2D point cloud data
      int width = pCloud.width;
      int height = pCloud.height;

      // Convert from u (column / width), v (row/height) to position in array
      // where X,Y,Z data starts
      int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;

      // compute position in array where x,y,z data start
      int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X has an offset of 0
      int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y has an offset of 4
      int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z has an offset of 8

      float X = 0.0;
      float Y = 0.0;
      float Z = 0.0;

      memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
      memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
      memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));

     // put data into the point p
      p.x = X;
      p.y = Y;
      p.z = Z;

    }
  const std::string tipo_objeto = "person";
  /*
  int image_width;
  int image_height;
  */
  int centrox;
  int centroy;
  bool objeto_detectado_ = false;
  ros::Subscriber sub_objetos_;
  //ros::Subscriber sub_camera_;
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
