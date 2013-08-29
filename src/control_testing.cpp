#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#include "constants.hh"

int main(int argc, char** argv){
   ros::init(argc, argv, "hand_arm_tf_broadcaster");
   ros::NodeHandle node;

   double yaw, pitch, roll;
   TESTING_EULER.getEulerYPR(yaw, pitch, roll);
   ROS_INFO( "%lf %lf %lf", roll, pitch, yaw );
   // -roll -pitch -yaw = Rx Ry Rz  for staubli

   return 0;
};

