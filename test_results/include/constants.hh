#ifndef __CONSTANTS_HH___
#define __CONSTANTS_HH___

#include <tf/LinearMath/Transform.h>

//eyeballed approximation -- FIXME
const tf::Matrix3x3 ARMTIP2HAND_ROTATE(
				     0.939692621, 0.342020143, 0,
				      0.342020143, 0.939692621, 0,
				     0, 0, 1
				     
  );
const tf::Vector3   ARMTIP2HAND_TRANSLATE(
					.0, .0, -.1451580
);
// almost no rotation, and only a -0.1 meters translation in Z
const tf::Transform ARMTIP2HAND_TRANSFORM( ARMTIP2HAND_ROTATE, ARMTIP2HAND_TRANSLATE ); 



const tf::Matrix3x3 ARMBASE2W_ROTATE(
				   // World2Arm
				    0.99982835, -0.0136405 , -0.01253785,
				    0.01370125,  0.99989474,  0.0047725 ,
				    0.01247143, -0.00494347,  0.99991001
				   );
const tf::Vector3   ARMBASE2W_TRANSLATE(  0.50038048,  0.4289552,  0.33142623);
				      

// almost no rotation, and only a -0.1 meters translation in Z
const tf::Transform ARMBASE2W_TRANSFORM( ARMBASE2W_ROTATE, ARMBASE2W_TRANSLATE ); 


////////////////////////////////////////////////////hao's new calibration
const tf::Matrix3x3 WORLD_IN_ROBOT_R(
	0.9997, -0.0232, 0.0070,
                         0.0232, 0.9997, -0.0014,
                         -0.007, 0.0015, 1.0
);

const tf::Vector3 WORLD_IN_ROBOT_T(-0.70591, -0.03778, -0.38045);

const tf::Transform WORLD_IN_ROBOT(WORLD_IN_ROBOT_R, WORLD_IN_ROBOT_T);

const tf::Matrix3x3 HAND_IN_END_R(
1,0,0,
0,1,0,
0,0,1);

const tf::Vector3 HAND_IN_END_T(
0,0,0.149);

const tf::Transform HAND_IN_END(HAND_IN_END_R, HAND_IN_END_T);

const tf::Matrix3x3 LIGHT_IN_FLASH_R(
0.707100000000000,	0,	-0.707100000000000,
0,	1,	0,
0.707100000000000,	0,	0.707100000000000);

const tf::Vector3 LIGHT_IN_FLASH_T(-0.0603000000000000,-0.00160000000000000,0.137800000000000);

const tf::Transform LIGHT_IN_FLASH(LIGHT_IN_FLASH_R, LIGHT_IN_FLASH_T);
#endif
