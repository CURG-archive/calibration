#!/usr/bin/env python
import roslib
roslib.load_manifest("calibration")
import rospy
from tf import transformations as tr
import tf
import tf_conversions.posemath as pm
from numpy import pi, eye, dot, cross, linalg, sqrt, ceil, size
from numpy import hstack, vstack, mat, array, arange, fabs, zeros
import math
import staubli_tx60.msg
import staubli_tx60.srv
import actionlib
from std_msgs.msg import Empty
import geometry_msgs.msg

def get_staubli_cartesian_as_pose_msg():
    rospy.wait_for_service('getCartesian')
    try:
        get_cartesian = rospy.ServiceProxy( 'getCartesian', staubli_tx60.srv.GetCartesian )
        resp1 = get_cartesian()
        # make srv x y z  rx ry rz euler angle representation into pose message
        pos = geometry_msgs.msg.Point( x = resp1.x, y = resp1.y, z = resp1.z )
        q = tf.transformations.quaternion_from_euler( resp1.rx , resp1.ry, resp1.rz ,'rxyz' )
        quat =  geometry_msgs.msg.Quaternion( x = q[0], y = q[1], z = q[2], w = q[3] )
        return geometry_msgs.msg.Pose( position = pos, orientation = quat )
    except rospy.ServiceException, e:
        print "Service call failed: %s"%e
        return []

def get_staubli_cartesian_as_tran():
    current_pose = get_staubli_cartesian_as_pose_msg()
    return pm.toMatrix(pm.fromMsg(current_pose))


rospy.init_node('arm_position_publisher')
tf_publisher = tf.TransformBroadcaster()
loop = rospy.Rate(3.0)
while not rospy.is_shutdown():
    t = get_staubli_cartesian_as_tran()
    t_tf = pm.toTf(pm.fromMatrix(t))
    tf_publisher.sendTransform(t_tf[0], t_tf[1], rospy.Time.now(),"/arm","/armbase")
    loop.sleep()


 
  
