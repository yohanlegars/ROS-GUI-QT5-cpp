/**
 * @file /include/qtros/main_window.hpp
 *
 * @brief Qt based gui for qtros.
 *
 * @date June 2022
 **/
#ifndef qtros_MAIN_WINDOW_H
#define qtros_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtWidgets/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"
#include "QProcess"
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h> 
#include "point_mgmt_msgs/SimpleMarker.h"
#include "point_mgmt_msgs/MarkerCoord.h"
#include "point_mgmt_msgs/MarkerNames.h"
#include <std_srvs/Empty.h>
#include <std_srvs/Trigger.h>
#include "point_mgmt/point_mgr.h"
#include <string>
#include <sensor_msgs/PointCloud2.h>
#include <moveit/moveit_cpp/moveit_cpp.h>
#include <moveit/moveit_cpp/planning_component.h>
#include <moveit/robot_state/conversions.h>
#include <moveit/move_group_interface/move_group_interface.h>


/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qtros {


/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

private:
	Ui::MainWindowDesign ui;
	QNode qnode;

    	ros::NodeHandle n_;

        ros::ServiceServer stop_base_;
        ros::ServiceServer human_detected_;



    	ros::ServiceClient load_points_client_;
        ros::ServiceClient spawn_point_of_interest_client_;
        ros::ServiceClient spawn_waypoint_client_;
        ros::ServiceClient kill_point_of_interest_client_;
        ros::ServiceClient kill_waypoint_client_;
        ros::ServiceClient save_points_client_;
        ros::ServiceClient get_waypoint_names_client_;
	    ros::ServiceClient get_point_of_interest_names_client_;
        ros::ServiceClient get_waypoint_loc_client_;

        typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
        MoveBaseClient ac_;
   
       


public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

	void ReadSettings(); // Load up qt program settings at startup
	void WriteSettings(); // Save qt program settings when closing

	void closeEvent(QCloseEvent *event); // Overloaded function
	void showNoMasterMessage();
   

   


public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
	void on_actionAbout_triggered();
	void on_button_connect_clicked(bool check );
	void on_checkbox_use_environment_stateChanged(int state);


    void start_cam_1();
    void stop_cam_1();
    void snapshot_cam_1();
    void husky_go();
    void husky_charge();
    // void camera_lin_up();
    // void camera_lin_down();
    // void camera_lin_right();
    // void camera_lin_left();
    // void camera_ori_up();
    // void camera_ori_down();
    // void camera_ori_right();
    // void camera_ori_left();
    void load_markers();
    void create_POI();
    void delete_POI();
    void create_WPT();
    void delete_WPT();
    void save_markers();
    void refresh_markers();
    //void camera_lin_down();
    
    bool stopBaseService(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);
    bool HumandetectedService(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res);
    
   



  

    
    /******************************************
    ** Manual connections
    *******************************************/

    void displayMat(cv::Mat image);
    void alert_operator(sensor_msgs::PointCloud2 sensor);
   


private slots:

    void on_startvideo_clicked();
    void on_suspendvideo_clicked();

    // void on_startvideo_2_clicked();
    // void on_suspendvideo_2_clicked();





};

}  // namespace qtros

#endif // qtros_MAIN_WINDOW_H
