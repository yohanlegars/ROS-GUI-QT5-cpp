/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date June 2022
 **/

/*****************************************************************************
** Includes
*****************************************************************************/
#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include <QSettings>
#include "../include/qtros/qnode.hpp"
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>


/*****************************************************************************
** Namespaces
*****************************************************************************/
namespace qtros {

/*****************************************************************************
** Implementation
*****************************************************************************/
QNode::QNode(int argc, char** argv ) :init_argc(argc), init_argv(argv)
	{
    QSettings topic_setting("qtros", "settings");
    batteryState_topic = topic_setting.value("topic/topic_power", "battery_state").toString();
    qRegisterMetaType<sensor_msgs::BatteryState>("sensor_msgs::BatteryState");
    }

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {ros::init(init_argc,init_argv,"qtros");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle nh;
    // Add your ros communications here.
    /****camera ***/
    image_transport::ImageTransport it_1(nh);
    image_transport::Subscriber image_sub_1;
    image_sub_1 = it_1.subscribe("/stream_video/camera_kinova/color/image_raw", 1, &QNode::myCallback,this);   ///stream_video/camera_kinova/image_raw"
    subscribe_lidar = nh.subscribe("/velodyne_points", 1, &QNode::alertCallback, this);
    
    
    start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"qtros");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
    ros::NodeHandle nh;
	// Add your ros communications here.
    /****camera ***/
    image_transport::ImageTransport it_1(nh);
    image_transport::Subscriber image_sub_1;
    image_sub_1 = it_1.subscribe("/stream_video/camera_kinova/color/image_raw", 1, &QNode::myCallback,this);
    subscribe_lidar = nh.subscribe("/velodyne_points", 1, &QNode::alertCallback, this);
   
    start();
	return true;
}

void QNode::run() {
ros::NodeHandle nh;
ros::NodeHandle n;
/****camera 1***/
image_transport::ImageTransport it_1(nh);
image_transport::Subscriber image_sub_1;
image_sub_1 = it_1.subscribe("/stream_video/camera_kinova/color/image_raw", 1, &QNode::myCallback,this);
battery_sub = n.subscribe(batteryState_topic.toStdString(), 200, &QNode::batteryCallback, this);
subscribe_lidar = nh.subscribe("/velodyne_points", 1, &QNode::alertCallback, this);
ros::spin();
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::myCallback(const sensor_msgs::ImageConstPtr& msg)
{
   cv_bridge::CvImagePtr cv_ptr;
         try
           {
             cv_ptr = cv_bridge::toCvCopy(msg);
             img = cv_ptr->image;
             //cv::normalize(img,img,0.,255.,cv::NORM_MINMAX,CV_8U);  //Convert from 16 bit to 8 bit per pixel
             Q_EMIT imageSignal(img);

           }
           catch (cv_bridge::Exception& e)
           {
             ROS_ERROR("cv_bridge exception: %s", e.what());
             return;
           }
              /**************************************/
   }

void QNode::alertCallback(const sensor_msgs::PointCloud2& msgs)
  {
    emit lidar(msgs);
  }



void QNode::batteryCallback(const sensor_msgs::BatteryState& message) {
  emit batteryState(message);
}



}   // namespace qtros

