#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>


int main(int argc, char** argv){
   ros::init(argc, argv, "query_arm");

   ros::NodeHandle node;

   tf::TransformBroadcaster br;
   tf::TransformListener    listener;
   tf::Transform            hand_goal_in_world;

   hand_goal_in_world.setOrigin( tf::Vector3(0.0, 0.0, 0.101) );
   hand_goal_in_world.setRotation( tf::Quaternion( tf::Vector3(0,0,1), 1.0) );

   ros::Rate rate(10.0);
   while (node.ok()){
      br.sendTransform( tf::StampedTransform( hand_goal_in_world, ros::Time::now(), "world", "hand_goal_pose" ) );
      tf::StampedTransform transform;
      try{
	 listener.lookupTransform("/world", "/armtip_goal_pose",  ros::Time(0), transform);
      }
      catch (tf::TransformException ex){
	 ROS_ERROR("%s",ex.what());
	 ros::Duration(0.1).sleep();
      }

      rate.sleep();
   }
   return 0;
};
