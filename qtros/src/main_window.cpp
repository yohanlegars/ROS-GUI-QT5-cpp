/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date June 2022
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/qtros/main_window.hpp"
#include <QPixmap>
#include <QProcess>
#include <signal.h>
#include <highgui.h>
#include <QFileDialog>





/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qtros {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
    , qnode(argc,argv), ac_("move_base", true)
{
    ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QObject::connect(ui.actionAbout_Qt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt())); // qApp is a global variable for the application	

    /****************************setting up clients******************/
    this->load_points_client_ = n_.serviceClient<std_srvs::Empty>("/point_manager/load_points", this);
    this->spawn_point_of_interest_client_ = n_.serviceClient<point_mgmt_msgs::SimpleMarker>("/point_manager/spawn_point_of_interest",this);
    this->spawn_waypoint_client_ = n_.serviceClient<point_mgmt_msgs::SimpleMarker>("/point_manager/spawn_waypoint",this);
    this->kill_point_of_interest_client_ = n_.serviceClient<point_mgmt_msgs::SimpleMarker>("/point_manager/kill_point_of_interest",this);
    this->kill_waypoint_client_ = n_.serviceClient<point_mgmt_msgs::SimpleMarker>("/point_manager/kill_waypoint",this);
    this->save_points_client_ = n_.serviceClient<std_srvs::Empty>("/point_manager/save_points", this);
    this->get_waypoint_names_client_ = n_.serviceClient<point_mgmt_msgs::MarkerNames>("/point_manager/get_waypoint_names", this);
    this->get_point_of_interest_names_client_ = n_.serviceClient<point_mgmt_msgs::MarkerNames>("/point_manager/get_point_of_interest_names", this);
    this->get_waypoint_loc_client_ = n_.serviceClient<point_mgmt_msgs::MarkerCoord>("/point_manager/get_waypoint_location", this);
    
    this->stop_base_ = n_.advertiseService("cancel_goal", &MainWindow::stopBaseService, this);
    this->human_detected_ = n_.advertiseService("human_detected", &MainWindow::HumandetectedService, this);
    ReadSettings();
    setWindowIcon(QIcon(":/images/icon.png"));
    ui.tab_manager->setCurrentIndex(0); // ensure the first tab is showing - qt-designer should have this already hardwired, but often loses it (settings?).
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    
    /*********************
    ** Logging
    **********************/

    QObject::connect(&qnode, SIGNAL(imageSignal(cv::Mat)),this,SLOT(displayMat(cv::Mat)));
    QObject::connect(&qnode, SIGNAL(lidar(sensor_msgs::PointCloud2)), this, SLOT(alert_operator(sensor_msgs::PointCloud2)));


    /********************Camera buttons**********************/
     

    QObject::connect(ui.startvideo, SIGNAL(clicked()), this, SLOT(start_cam_1()));
    QObject::connect(ui.suspendvideo, SIGNAL(clicked()), this, SLOT(stop_cam_1()));
    QObject::connect(ui.snapshot, SIGNAL(clicked()), this, SLOT(snapshot_cam_1()));
    QObject::connect(ui.pushButton_go, SIGNAL(clicked()), this, SLOT(husky_go()));
    QObject::connect(ui.pushButton_charge, SIGNAL(clicked()), this, SLOT(husky_charge()));
    QObject::connect(ui.pushButton_refresh, SIGNAL(clicked()), this, SLOT(refresh_markers()));

    // QObject::connect(ui.pushButton_lin_up, SIGNAL(clicked()), this, SLOT(camera_lin_up()));
    //QObject::connect(ui.pushButton_lin_down, SIGNAL(clicked()), this, SLOT(camera_lin_down()));
    // QObject::connect(ui.pushButton_lin_right, SIGNAL(clicked()), this, SLOT(camera_lin_right()));
    // QObject::connect(ui.pushButton_lin_left, SIGNAL(clicked()), this, SLOT(camera_lin_left()));

    // QObject::connect(ui.pushButton_ori_up, SIGNAL(clicked()), this, SLOT(camera_ori_up()));
    //QObject::connect(ui.pushButton_ori_down, SIGNAL(clicked()), this, SLOT(camera_ori_down()));
    // QObject::connect(ui.pushButton_ori_right, SIGNAL(clicked()), this, SLOT(camera_ori_right()));
    // QObject::connect(ui.pushButton_ori_left, SIGNAL(clicked()), this, SLOT(camera_ori_left()));

    /*******************MARKERS***********************************/
    
    QObject::connect(ui.pushButton_load, SIGNAL(clicked()), this, SLOT(load_markers()));
     
    QObject::connect(ui.pushButton_create_POI, SIGNAL(clicked()), this, SLOT(create_POI()));
    QObject::connect(ui.pushButton_delete_POI, SIGNAL(clicked()), this, SLOT(delete_POI()));
    QObject::connect(ui.pushButton_create_wpt, SIGNAL(clicked()), this, SLOT(create_WPT()));
    QObject::connect(ui.pushButton_delete_wpt, SIGNAL(clicked()), this, SLOT(delete_WPT()));
   
    QObject::connect(ui.pushButton_save, SIGNAL(clicked()), this, SLOT(save_markers(sensor_msgs::PointCloud2)));
     
    // ac_ = MainWindow::ac_("move_base", true);
    

    

    

    /*****************Battery Buttons*********************************/

    // QObject::connect(&qnode, SIGNAL(updateMap(QImage)), m_roboItem, SLOT(paintMaps(QImage)));
    // QObject::connect(&qnode, SIGNAL(plannerPath(QPolygonF)), m_roboItem, SLOT(paintPlannerPath(QPolygonF)));
    // QObject::connect(&qnode, SIGNAL(updateRoboPose(RobotPose)), m_roboItem, SLOT(paintRoboPos(RobotPose)));
    // QObject::connect(&qn=ode, SIGNAL(updateLaserScan(QPolygonF)), m_roboItem, SLOT(paintLaserScan(QPolygonF)));
    // QObject::connect(m_roboItem, SIGNAL(cursorPos(QPointF)), this, SLOT(slot_updateCursorPos(QPointF)));

    // QObject::connect(m_roboItem, SIGNAL(signalPub2DPos(RobotPose)), &qnode,SLOT(slot_pub2DPos(RobotPose)));
    // QObject::connect(m_roboItem, SIGNAL(signalPub2DGoal(RobotPose)), &qnode,SLOT(slot_pub2DGoal(RobotPose)));
    // QObject::connect(this, SIGNAL(signalSet2DPose()), m_roboItem, SLOT(slot_set2DPos()));
    // QObject::connect(this, SIGNAL(signalSet2DGoal()), m_roboItem, SLOT(slot_set2DGoal()));
    // QObject::connect(this, SIGNAL(signalSetMoveCamera()), m_roboItem,SLOT(slot_setMoveCamera()));
  
   
  

    /*********************
    ** Auto Start
    **********************/
    if ( ui.checkbox_remember_settings->isChecked() ) {
        on_button_connect_clicked(true);
    }
}

MainWindow::~MainWindow() {}



    

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/

/************ Camera-1 Buttons******************/
int on=0,off=0;

void MainWindow::start_cam_1()
{
    on=1;

}

void MainWindow::stop_cam_1()
{
    off=1;
}



void MainWindow::showNoMasterMessage() {
    QMessageBox msgBox;
    msgBox.setText("Couldn't find the ros master.");
    msgBox.exec();
    close();
}

void MainWindow::alert_operator(sensor_msgs::PointCloud2 sensor){
    if (sensor.row_step < 1 )
    {
    QMessageBox msgBox;
    msgBox.setText("Something went wrong with the topic connections");
    msgBox.exec();
    close();
    }

}

/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */

void MainWindow::on_button_connect_clicked(bool check ) {

    if ( ui.checkbox_use_environment->isChecked() ) {
        if ( !qnode.init() ) {
            showNoMasterMessage();
        } else {
            ui.button_connect->setEnabled(false);
        }
    } else {
        if ( ! qnode.init(ui.line_edit_master->text().toStdString(),
                   ui.line_edit_host->text().toStdString()) ) {
            showNoMasterMessage();
        } else {
            ui.button_connect->setEnabled(false);
            ui.line_edit_master->setReadOnly(true);
            ui.line_edit_host->setReadOnly(true);
            ui.line_edit_topic->setReadOnly(true);
        }
    }
    
}




void MainWindow::on_checkbox_use_environment_stateChanged(int state) {
    bool enabled;
    if ( state == 0 ) {
        enabled = true;
    } else {
        enabled = false;
    }
    ui.line_edit_master->setEnabled(enabled);
    ui.line_edit_host->setEnabled(enabled);
    //ui.line_edit_topic->setEnabled(enabled);
}

/*****************************************************************************
** Implemenation [Slots][manually connected]
*****************************************************************************/

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About ..."),tr("<h2>Pronto_bot</h2><p>Copyright Pronto_bot team</p><p>Gui for samxl project.</p>"));
}

/*****************************************************************************
** Implementation [Configuration]
*****************************************************************************/

void MainWindow::ReadSettings() {
    QSettings settings("Qt-Ros Package", "qtros");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    QString master_url = settings.value("master_url",QString("http://ubiquityrobot.local:11311/")).toString();
    QString host_url = settings.value("host_url", QString("137.226.176.99")).toString();
    //QString topic_name = settings.value("topic_name", QString("/chatter")).toString();
    ui.line_edit_master->setText(master_url);
    ui.line_edit_host->setText(host_url);
    //ui.line_edit_topic->setText(topic_name);
    bool remember = settings.value("remember_settings", false).toBool();
    ui.checkbox_remember_settings->setChecked(remember);
    bool checked = settings.value("use_environment_variables", false).toBool();
    ui.checkbox_use_environment->setChecked(checked);
    if ( checked ) {
        ui.line_edit_master->setEnabled(false);
        ui.line_edit_host->setEnabled(false);
        //ui.line_edit_topic->setEnabled(false);
    }
}

void MainWindow::WriteSettings() {
    QSettings settings("Qt-Ros Package", "qtros");
    settings.setValue("master_url",ui.line_edit_master->text());
    settings.setValue("host_url",ui.line_edit_host->text());
    //settings.setValue("topic_name",ui.line_edit_topic->text());
    settings.setValue("use_environment_variables",QVariant(ui.checkbox_use_environment->isChecked()));
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    settings.setValue("remember_settings",QVariant(ui.checkbox_remember_settings->isChecked()));
    settings.setValue("manage_markers",ui.lineEdit_markers->text());
   
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    WriteSettings();
    QMainWindow::closeEvent(event);
}


QImage img;

void MainWindow::displayMat(cv::Mat image)
{

          img =QImage((image.data),
                       image.cols,image.rows,
                       QImage::Format_RGB888);


   if(on && !off)

   {
    
    ui.view_logging->setPixmap(QPixmap::fromImage(img));
    // ui.view_logging->resize(ui.view_logging->pixmap()->size());


     ui.view_logging->setScaledContents( true );
     ui.view_logging->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

     /*h=ui->view_logging->height;
     w=ui->view_logging->width;
     ui->view_logging->setPixmap(img.scaled(w,h,Qt::KeepAspectRatio));*/
   }

   else
     {
        on=0; off=0;
     }
 }



void MainWindow::snapshot_cam_1()
{
    /* QString imagePath = QFileDialog::getSaveFileName(this,
                                             "Save Snapshot Images",
                                             QDir::homePath(),
                                             tr("Images (*.png *.jpg)")); // in case the path is not fixed
    */

    QDateTime time = QDateTime::currentDateTime();
    QString timestamp = time.toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString name="Cam1_";
    QString path="/home/yohanros/Pictures"+name+timestamp+".jpg";


    qDebug() << "timestamp:" << timestamp;

    img.save(path);

}

void MainWindow::load_markers()
{
  std_srvs::Empty srv;
  if (load_points_client_.call(srv))
  {
      ROS_INFO_STREAM("loaded point successfully");
  }
  else 
  {
      ROS_INFO_STREAM("not working for some reason");
  }
}

 
void MainWindow::create_POI()
{
   
   std::string name ;
   point_mgmt_msgs::SimpleMarker srv;

   name = ui.lineEdit_markers->text().toStdString();
   

   srv.request.name = name;
   if (spawn_point_of_interest_client_.call(srv))
  {
      ROS_INFO_STREAM("created point of interest: " << name << " successfully");
  }
  else 
  {
      ROS_INFO_STREAM("not working for some reason");
  }
}

void MainWindow::delete_POI()
{
   
   std::string name ;
   point_mgmt_msgs::SimpleMarker srv;

   name = ui.lineEdit_markers->text().toStdString();
   

   srv.request.name = name;
   if (kill_point_of_interest_client_.call(srv))
  {
      ROS_INFO_STREAM("deleted point of interest: " << name << " successfully");
  }
  else 
  {
      ROS_INFO_STREAM("not working for some reason");
  }
}

void MainWindow::create_WPT()
{
   
   std::string name ;
   point_mgmt_msgs::SimpleMarker srv;

   name = ui.lineEdit_markers->text().toStdString();
   

   srv.request.name = name;
   if (spawn_waypoint_client_.call(srv))
  {
      ROS_INFO_STREAM("created waypoint: " << name << " successfully");
  }
  else 
  {
      ROS_INFO_STREAM("not working for some reason");
  }
}

void MainWindow::delete_WPT()
{
   
   std::string name ;
   point_mgmt_msgs::SimpleMarker srv;

   name = ui.lineEdit_markers->text().toStdString();
   

   srv.request.name = name;
   if (kill_waypoint_client_.call(srv))
  {
      ROS_INFO_STREAM("deleted waypoint: " << name << " successfully");
  }
  else 
  {
      ROS_INFO_STREAM("not working for some reason");
  }
}

void MainWindow::save_markers()
{
  
  std_srvs::Empty srv;
  if (save_points_client_.call(srv))
  {
      ROS_INFO_STREAM("save point successfully");
  }
  else 
  {
      ROS_INFO_STREAM("not working for some reason");
  }

}


void MainWindow::refresh_markers()
{
    
    
    ui.listmarkers_tab4_wpt->clear();
    ui.listmarkers_tab4_poi->clear();
   // std::vector<std::string> wpt_names;
    point_mgmt_msgs::MarkerNames names_srv_wpt;
    point_mgmt_msgs::MarkerNames names_srv_poi;

    if (get_waypoint_names_client_.call(names_srv_wpt))
    {
        for(std::string name: names_srv_wpt.response.names)
        {
            ui.listmarkers_tab4_wpt->addItem(QString::fromStdString(name));
        }
    }
    
    if (get_point_of_interest_names_client_.call(names_srv_poi))
    {
         for(std::string name: names_srv_poi.response.names)
        {
            ui.listmarkers_tab4_poi->addItem(QString::fromStdString(name));
        }
    }

}

void MainWindow::husky_go()
{
  
       

    QList<QListWidgetItem*> items = ui.listmarkers_tab4_wpt->selectedItems();
    point_mgmt_msgs::MarkerCoord locations_srv_wpt;
    locations_srv_wpt.request.name = items[0]->text().toStdString(); 

    

    if (get_waypoint_loc_client_.call(locations_srv_wpt))
    {
    
        std::array<float, 7> waypoint;
        waypoint = { locations_srv_wpt.response.x, locations_srv_wpt.response.y, 0.0, 0.0, 0.0, -0.7, 0.704};
            while(!ac_.waitForServer(ros::Duration(5.0))){
            ROS_INFO("waiting for the move_base action server to come up");
        }

        
        move_base_msgs::MoveBaseGoal goal;
        //we'll send a goal to the robot to move 1 meter forward
        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        goal.target_pose.pose.position.x = waypoint[0];
        goal.target_pose.pose.position.y = waypoint[1];
        goal.target_pose.pose.position.z = waypoint[2];

        goal.target_pose.pose.orientation.x = waypoint[3];
        goal.target_pose.pose.orientation.y = waypoint[4];
        goal.target_pose.pose.orientation.z = waypoint[5];
        goal.target_pose.pose.orientation.w = waypoint[6];

        ROS_INFO("Sending goal");

        ac_.sendGoal(goal);

        if (ac_.getState() == actionlib::SimpleClientGoalState::PENDING)
        ROS_INFO("the husky is moving towards its goal");
        
        ac_.waitForResult();


        // if(ac_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        //     ROS_INFO("Hooray, the base moved  to the desired location");
        // else 
        //     ROS_INFO("The base failed to move  for some reason");
    

    }
       
}

  


void MainWindow::husky_charge()
{
  
       
    std::array<float, 7> waypoint;
    waypoint = {4.1, -1.0, 0.0, 0.0, 0.0, -0.7, 0.704};


  //wait for the action server to come up
    while(!ac_.waitForServer(ros::Duration(5.0))){
        ROS_INFO("waiting for the move_base action server to come up");
    }

    
    move_base_msgs::MoveBaseGoal goal;
    
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = waypoint[0];
    goal.target_pose.pose.position.y = waypoint[1];
    goal.target_pose.pose.position.z = waypoint[2];

    goal.target_pose.pose.orientation.x = waypoint[3];
    goal.target_pose.pose.orientation.y = waypoint[4];
    goal.target_pose.pose.orientation.z = waypoint[5];
    goal.target_pose.pose.orientation.w = waypoint[6];

    ROS_INFO("Sending goal");

    ac_.sendGoal(goal);

    ac_.waitForResult();

    if(ac_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("Hooray, the base moved  forward");
    else 
        ROS_INFO("The base failed to move forward for some reason");

           
}


bool MainWindow::stopBaseService(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
 
    ROS_INFO("Possible Human has been detected");

    ac_.cancelGoal();

   
    QMessageBox msgBox;
    msgBox.setText("A Possible human has been detected! Husky has stopped.");
    msgBox.exec();

    res.success = true;
    res.message = "The goal has been cancelled";

    return true;
   

}

bool MainWindow::HumandetectedService(std_srvs::Trigger::Request &req, std_srvs::Trigger::Response &res)
{
    ROS_INFO("Human has been detected");
    QMessageBox msgBox;
    msgBox.setText("Please, tell the detected human to leave the area");
    msgBox.exec();

    res.success = true;
    res.message = "The human has been detected and asked to leave";

    return true;



}




// void MainWindow::camera_lin_down()
// {
//     //moveit::planning_interface::MoveGroup group_r("kinova_arm");
//     moveit::planning_interface::MoveGroupInterface group_r("kinova_arm");
//     robot_state::RobotState start_state(*group_r.getCurrentState());
//     geometry_msgs::Pose start_pose;
//     start_pose.orientation.x = group_r.getCurrentPose().pose.orientation.x;
//     start_pose.orientation.y = group_r.getCurrentPose().pose.orientation.y;
//     start_pose.orientation.z = group_r.getCurrentPose().pose.orientation.z;
//     start_pose.orientation.w = group_r.getCurrentPose().pose.orientation.w;
//     start_pose.position.x = group_r.getCurrentPose().pose.position.x;
//     start_pose.position.y = group_r.getCurrentPose().pose.position.y;
//     start_pose.position.z = group_r.getCurrentPose().pose.position.z;

//     ROS_INFO_STREAM(start_pose.position.x);
//     ROS_INFO_STREAM(start_pose.position.y);
//     ROS_INFO_STREAM(start_pose.position.z);


//     group_r.setStartState(start_state);

//     moveit_msgs::OrientationConstraint ocm;

//     ocm.link_name = "kinova_arm_end_effector_link";
//     ocm.header.frame_id = "kinova_arm_base_link";
//     ocm.orientation.w = 0.0;
//     ocm.absolute_x_axis_tolerance = 0.0;
//     ocm.absolute_y_axis_tolerance = 0.0;
//     ocm.absolute_z_axis_tolerance = 0.1;
//     ocm.weight = 1.0;
//     moveit_msgs::Constraints test_constraints;
//     test_constraints.orientation_constraints.push_back(ocm);
//     group_r.setPathConstraints(test_constraints);



//     geometry_msgs::Pose next_pose = start_pose;
   
//     std::vector<geometry_msgs::Pose> waypoints;
//     next_pose.position.z -= 0.03;
//     waypoints.push_back(next_pose);  // up and out

//     moveit_msgs::RobotTrajectory trajectory;
//     double fraction = group_r.computeCartesianPath(waypoints, 0.005, 0.0, trajectory);
  

//     /* Sleep to give Rviz time to visualize the plan. */
//     sleep(5.0);
//     group_r.move();


// }







void qtros::MainWindow::on_startvideo_clicked()
{
     ui.startvideo->setStyleSheet("background-color:#9c9c9c ");
     ui.suspendvideo->setStyleSheet("  ");
}

void qtros::MainWindow::on_suspendvideo_clicked()
{
   ui.startvideo->setStyleSheet("  ");
   ui.suspendvideo->setStyleSheet(" background-color:gray;");
}



}
