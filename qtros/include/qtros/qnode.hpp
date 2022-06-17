/**
 * @file /include/qtros/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date May 2019
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qtros_QNODE_HPP_
#define qtros_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <nav_msgs/Path.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <QPixmap>
#include <QSettings>
#include <string>
#include <std_msgs/Float64.h>
#include <QThread>
#include <QStringListModel>
#include <map>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/Path.h>
#include <QImage>
#include <sensor_msgs/BatteryState.h>
#include <sensor_msgs/PointCloud2.h>


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtros {


/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();
	void myCallback(const sensor_msgs::ImageConstPtr& msg);
    void batteryCallback(const sensor_msgs::BatteryState &message);
	void alertCallback(const sensor_msgs::PointCloud2 &msgs);
    cv::Mat img;
	//sensor_msgs::PointCloud2 data;

   

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

Q_SIGNALS:

    void rosShutdown();
    void imageSignal(cv::Mat);
	void batteryState(sensor_msgs::BatteryState);
	void lidar(sensor_msgs::PointCloud2);
	


private:
    image_transport::Subscriber image_sub_1;//cam1
	ros::Subscriber battery_sub;
	ros::Subscriber subscribe_lidar;
   

	int init_argc;
	char** init_argv;
	ros::Subscriber chatter_subscriber;
	ros::Subscriber map_sub;
    QStringListModel logging_model;
    QStringListModel logging;
	QString batteryState_topic;
	





};

}  // namespace qtros

#endif /* qtros_QNODE_HPP_ */
