#ifndef POINT_MGR_H_
#define POINT_MGR_H_


#include <ros/ros.h>						// ROS
#include <interactive_markers/interactive_marker_server.h>	// Interactive markers for RViz
#include <string>						// String library
#include <fstream>						// for saving txt files
#include <ros/package.h>					// For package paths
#include <tf/tf.h>						// for reference frames in RViz and ROS
#include <map>
#include <std_msgs/ColorRGBA.h>
#include <std_srvs/Empty.h>
#include "point_mgmt_msgs/SimpleMarker.h"
#include "point_mgmt_msgs/MarkerCoord.h"
#include "point_mgmt_msgs/MarkerNames.h"

// For understanding and help:
// http://wiki.ros.org/rviz/Tutorials/Interactive%20Markers%3A%20Getting%20Started


class PointMGR
{
	private:
		ros::NodeHandle n_;
		
		// services can be called from anywhere (ie, by the GUI)
		ros::ServiceServer spawn_waypoint_server_;
		ros::ServiceServer spawn_point_of_interest_server_;
		ros::ServiceServer kill_waypoint_server_;
		ros::ServiceServer kill_point_of_interest_server_;
		ros::ServiceServer save_points_server_;
		ros::ServiceServer load_points_server_;
		ros::ServiceServer points_summary_server_;
		ros::ServiceServer get_waypoint_loc_server_;
		ros::ServiceServer get_point_of_interest_loc_server_;
		ros::ServiceServer get_waypoint_names_server_;
		ros::ServiceServer get_point_of_interest_names_server_;

		boost::shared_ptr<interactive_markers::InteractiveMarkerServer> server_;		// The server object for handling the RViz side of things

		std::string save_file_name_;								// path of the file where points are saved
		std::string save_sep_;									// separator used for the file
		std::map<std::string, std::array<float, 2>> waypoints_;					// Waypoint names correspdond to 2D coordinates on the ground plane
		std::map<std::string, std::array<float, 3>> points_of_interest_;			// Points of interest names correspond to 3D coordinates in space
		std::string base_tf_frameid_;

		void processWayPointFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
		void processPointOfInterestFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback);
		void makeWayPoint(const std::string name);
		void makePointOfInterest(const std::string name);
		void addWayPoint(const std::string name, const std::array<float, 2> position);
		void addPointOfInterest(const std::string name, const std::array<float, 3> position);
		void removeWayPoint(const std::string name);
		void removePointOfInterest(const std::string name);
		void refreshAllPoints();
		void savePoints();
		void loadPoints();
		std::vector<std::string> parseLine(std::string line, std::string delimiter);
		void summarizePoints();

	public:
		PointMGR();
/*		PointMGR(boost::shared_ptr<interactive_markers::InteractiveMarkerServer> const& server);*/

		void serverReset();

		bool spawnWayPointService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res);
		bool spawnPOIService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res);
		bool killWayPointService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res);
		bool killPOIService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res);
		bool savePointsService(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);
		bool loadPointsService(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);
		bool getPointsSummary(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res);
		bool WayPointLocService(point_mgmt_msgs::MarkerCoord::Request &req, point_mgmt_msgs::MarkerCoord::Response &res);
		bool POILocService(point_mgmt_msgs::MarkerCoord::Request &req, point_mgmt_msgs::MarkerCoord::Response &res);
		bool WayPointNamesService(point_mgmt_msgs::MarkerNames::Request &req, point_mgmt_msgs::MarkerNames::Response &res);
		bool POINamesService(point_mgmt_msgs::MarkerNames::Request &req, point_mgmt_msgs::MarkerNames::Response &res);
};




#endif /* POINT_MGR_H_ */

