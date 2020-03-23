#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <std_msgs/Int8.h>
#include "std_msgs/Bool.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"

#include <sensor_msgs/PointCloud2.h>

/*---
header:
  seq: 5
  stamp:
    secs: 398
    nsecs:  60000000
  frame_id: "base_footprint"
point:
  x: -3.468282938
  y: 4.47962141037
  z: 0.00229167938232
---
header:
  seq: 6
  stamp:
    secs: 400
    nsecs: 920000000
  frame_id: "base_footprint"
point:
  x: -1.44922804832
  y: 3.49580216408
  z: 0.00138425827026
---
header:
  seq: 7
  stamp:
    secs: 407
    nsecs: 960000000
  frame_id: "base_footprint"
point:
  x: 1.91096591949
  y: 5.34825706482
  z: 0.0033073425293
---
*/

class Navigator
{
  public:
    Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", false), goal_sent_(false)
    {
      navigator_running_pub = nh_.advertise<std_msgs::Bool>("/navigator/isrunning", 1);
      navigator_goals_sub = nh_.subscribe("/navigator/goals", 1, &Navigator::goalscallback, this);
      POSITION[0].x=0;
      POSITION[0].y=0;
      POSITION[0].z=0;

      POSITION[1].x=3.39439487457;
      POSITION[1].y=-0.1;
      POSITION[1].z=0;

      POSITION[2].x=3.2910990715;
      POSITION[2].y=1.9;
      POSITION[2].z=0;

      POSITION[3].x=1.27405560017;
      POSITION[3].y=5.48847675323;
      POSITION[3].z=0;
    }

    void goalscallback(const std_msgs::Int8& msg){
      if(msg.data<NUMBER_GOALS && current_goal!=msg.data){
        current_goal=msg.data;
        ROS_INFO("[navigate_to_wp] msg recieved, current goal: %d",msg.data);
        goal_recieved_ = true;
      }
    }

    void step()
    {
      gotogoal();
      if (goal_sent_)
      {
        bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
        actionlib::SimpleClientGoalState state = action_client_.getState();
        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = action_client_.getState();
          if (state == actionlib::SimpleClientGoalState::SUCCEEDED){
            ROS_INFO("[navigate_to_wp] Goal Reached!");
            std_msgs::Bool running;
            running.data=false;
            navigator_running_pub.publish(running);
          }
          else
            ROS_INFO("[navigate_to_wp] Something bad happened!");
          goal_sent_ = false;
        }
      }
    }

    void gotogoal()
    {
      if(goal_recieved_){
        geometry_msgs::PoseStamped goal_pose_;
        goal_pose_.pose.position=POSITION[current_goal];
        goal_pose_.pose.orientation.x=0;
        goal_pose_.pose.orientation.y=0;
        goal_pose_.pose.orientation.z=0;
        goal_pose_.pose.orientation.w=1;

        ROS_INFO("[navigate_to_wp] Commanding to (%f %f)", goal_pose_.pose.position.x, goal_pose_.pose.position.y);

        move_base_msgs::MoveBaseGoal goal;
        goal.target_pose = goal_pose_;
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();
        action_client_.sendGoal(goal);
        goal_recieved_=false;
        goal_sent_ = true;
        std_msgs::Bool running;
        running.data=true;
        navigator_running_pub.publish(running);
      }
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    ros::Subscriber navigator_goals_sub;
    ros::Publisher navigator_running_pub;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;

    bool goal_sent_=false;
    bool goal_recieved_=false;
    int current_goal=-1;

    static const int NUMBER_GOALS=4;
    geometry_msgs::Point POSITION[NUMBER_GOALS];


};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");
  ros::NodeHandle nh("~");
  Navigator navigator(nh);
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    navigator.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
