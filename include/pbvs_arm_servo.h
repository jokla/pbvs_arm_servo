#include <ros/ros.h>

#include <sensor_msgs/JointState.h>
#include <sensor_msgs/SetCameraInfo.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Bool.h>

#include <tf/transform_broadcaster.h>

#include <visp3/core/vpHomogeneousMatrix.h>
#include <visp3/core/vpMatrix.h>
#include <visp3/core/vpQuaternionVector.h>
#include <visp/vpXmlParserCamera.h>
#include <visp/vpXmlParserHomogeneousMatrix.h>

#include <visp/vpPlot.h>

#include <visp_bridge/3dpose.h>
#include <visp_bridge/image.h>
#include <visp_bridge/camera.h>

#include <visp_naoqi/vpNaoqiRobot.h>
#include <visp_naoqi/vpNaoqiConfig.h>

#include <vpServoArm.h>

class pbvs_arm_servo
{
public:

  pbvs_arm_servo(ros::NodeHandle &nh);
  ~pbvs_arm_servo();
  void computeControlLaw();
  void spin();
  void getActualPoseCb(const geometry_msgs::PoseStampedConstPtr &msg);
  void getDesiredPoseCb(const geometry_msgs::PoseStampedConstPtr &msg);
  void getStatusPoseHandCb(const std_msgs::Int8::ConstPtr &status);
  void getStatusPoseDesiredCb(const std_msgs::Int8::ConstPtr &status);
  void getActivationCb(const std_msgs::Int8::ConstPtr &status);
  void savePoses();
  void getRobotJoints();
  void publishCmdVel(const vpColVector &q);


protected:

  // Robot
  vpNaoqiRobot robot;
  std::vector<std::string> m_jointNames_arm;
  int m_numJoints;
  std::string m_chain_name;
  vpColVector m_jointMin;
  vpColVector m_jointMax;

  // ROS
  ros::NodeHandle n;
  std::string actualPoseTopicName;
  std::string desiredPoseTopicName;
  std::string statusPoseHandTopicName;
  std::string activationTopicName;
  std::string statusPoseDesiredTopicName;
  std::string cmdVelTopicName;
  std::string m_opt_arm;
  std::string m_offsetFileName;
  std::string m_offsetName;
  std::string m_cameraFrameName;
  ros::Subscriber actualPoseSub;
  ros::Subscriber activationSub;
  ros::Subscriber desiredPoseSub;
  ros::Subscriber statusPoseHandSub;
  ros::Subscriber statusPoseDesiredSub;
  ros::Publisher cmdVelPub;
  ros::Publisher pbvsComputedPub;
  ros::Publisher poseWithOffsetPub;
  ros::Publisher desiredPosePub;
  int freq;

  // Messages
  sensor_msgs::JointState m_q_dot_msg;
  std_msgs::Bool m_computed;

  //Servo Arm
  vpServoArm m_servo_arm;
  vpColVector m_q;
  vpColVector m_q_dot;
  vpColVector m_q2_dot;

  double m_servo_time_init;
  int m_statusPoseHand;
  int m_statusPoseDesired;

  vpHomogeneousMatrix m_cMh;
  vpHomogeneousMatrix m_cMdh;
  vpHomogeneousMatrix oMe_Arm;
  vpHomogeneousMatrix m_dhMoffset;
  vpHomogeneousMatrix m_cMhr;

  //conditions
  bool m_cMh_isInitialized;
  bool m_cMdh_isInitialized;
  bool m_statusPoseDesired_isEnable;
  bool m_savePose;
  bool m_useOffset;
  bool m_init;
  bool m_plot;
  int m_activation;

  int m_compteur;
  vpPlot *plotter_arm;
  vpPlot *plotter_arm2;


};
