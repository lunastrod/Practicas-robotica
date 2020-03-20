#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include <tf/transform_listener.h>
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"
#include <string>

class Navigator
{
  public:
    Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", false), goal_sended_(false)
    {
      wp_sub_ = nh_.subscribe("/navigate_to", 1, &Navigator::navigateCallback, this);
    }

    void navigateCallback(geometry_msgs::PoseStamped goal_pose_)
    {
      ROS_INFO("[navigate_to_wp] Commanding to (%f %f)", goal_pose_.pose.position.x, goal_pose_.pose.position.y);
      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose = goal_pose_;
      goal.target_pose.header.frame_id = "/map";
      goal.target_pose.header.stamp = ros::Time::now();
      action_client_.sendGoal(goal);
      goal_sended_ = true;
    }

    void step()
    {
      if (goal_sended_)
      {
        bool finished_before_timeout = action_client_.waitForResult(ros::Duration(0.5));
        actionlib::SimpleClientGoalState state = action_client_.getState();
        if (finished_before_timeout)
        {
          actionlib::SimpleClientGoalState state = action_client_.getState();
          if (state == actionlib::SimpleClientGoalState::SUCCEEDED)
            ROS_INFO("[navigate_to_wp] Goal Reached!");
          else
            ROS_INFO("[navigate_to_wp] Something bad happened!");
          goal_sended_ = false;
        }
      }
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    bool goal_sended_;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");
  ros::NodeHandle nh("~");
  Navigator navigator(nh);
  ros::Rate loop_rate(20);
  while (ros::ok())
  {
    printf("Main\n");
    navigator.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
