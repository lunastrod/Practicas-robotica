#include "ros/ros.h"

#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "actionlib/client/simple_action_client.h"
#include "move_base_msgs/MoveBaseAction.h"
#include "geometry_msgs/PoseStamped.h"


class Navigator
{
  public:
    Navigator(ros::NodeHandle& nh) : nh_(nh), action_client_("/move_base", false), goal_sended_(false)
    {
      POSITION[0].x=1;
      POSITION[0].y=0;
      POSITION[0].z=0;
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

    void gotogoal(int n)
    {
      geometry_msgs::PoseStamped goal_pose_;
      goal_pose_.pose.position=POSITION[0];
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
      goal_sended_ = true;
    }

  private:
    ros::NodeHandle nh_;
    ros::Subscriber wp_sub_;
    bool goal_sended_;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client_;

    geometry_msgs::Point POSITION[4];


};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "navp6");
  ros::NodeHandle nh("~");
  Navigator navigator(nh);
  ros::Rate loop_rate(1);
  while (ros::ok())
  {
    navigator.gotogoal(0);
    navigator.step();
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
