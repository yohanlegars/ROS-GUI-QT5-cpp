#include "point_mgmt/point_mgr.h"


// For understanding and help:
// http://wiki.ros.org/rviz/Tutorials/Interactive%20Markers%3A%20Getting%20Started


PointMGR::PointMGR()
{
	server_.reset( new interactive_markers::InteractiveMarkerServer("basic_controls","",false) );

	this->spawn_waypoint_server_ = n_.advertiseService("spawn_waypoint", &PointMGR::spawnWayPointService, this);
	this->spawn_point_of_interest_server_ = n_.advertiseService("spawn_point_of_interest", &PointMGR::spawnPOIService, this);
	this->kill_waypoint_server_ = n_.advertiseService("kill_waypoint", &PointMGR::killWayPointService, this);
	this->kill_point_of_interest_server_ = n_.advertiseService("kill_point_of_interest", &PointMGR::killPOIService, this);
	this->save_points_server_ = n_.advertiseService("save_points", &PointMGR::savePointsService, this);
	this->load_points_server_ = n_.advertiseService("load_points", &PointMGR::loadPointsService, this);
	this->points_summary_server_ = n_.advertiseService("summarise_points", &PointMGR::getPointsSummary, this);
	this->get_waypoint_loc_server_ = n_.advertiseService("get_waypoint_location", &PointMGR::WayPointLocService, this);
	this->get_point_of_interest_loc_server_ = n_.advertiseService("get_point_of_interest_location", &PointMGR::POILocService, this);
	this->get_waypoint_names_server_ = n_.advertiseService("get_waypoint_names", &PointMGR::WayPointNamesService, this);
	this->get_point_of_interest_names_server_ = n_.advertiseService("get_point_of_interest_names", &PointMGR::POINamesService, this);

	save_file_name_ = ros::package::getPath("point_mgmt") + "/config/points.txt";
	save_sep_ = ", ";

	base_tf_frameid_ = "/odom";
}

//PointMGR::PointMGR(boost::shared_ptr<interactive_markers::InteractiveMarkerServer> const& server): server_(server)
//{
//	this->spawn_waypoint_server_ = n_.advertiseService("spawn_waypoint", &PointMGR::spawnWayPointService, this);
//	this->spawn_point_of_interest_server_ = n_.advertiseService("spawn_point_of_interest", &PointMGR::spawnPOIService, this);
//	this->kill_waypoint_server_ = n_.advertiseService("kill_waypoint", &PointMGR::killWayPointService, this);
//	this->kill_point_of_interest_server_ = n_.advertiseService("kill_point_of_interest", &PointMGR::killPOIService, this);
//	this->save_points_server_ = n_.advertiseService("save_points", &PointMGR::savePointsService, this);
//	this->load_points_server_ = n_.advertiseService("load_points", &PointMGR::loadPointsService, this);
//	this->points_summary_server_ = n_.advertiseService("summarise_points", &PointMGR::getPointsSummary, this);

//	save_file_name_ = ros::package::getPath("point_mgmt") + "/config/points.txt";
//	save_sep_ = ", ";

//	base_tf_frameid_ = "/map";
//}

void PointMGR::processWayPointFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
{
	// This function handles feedback from the user moving waypoints in RViz

	ROS_INFO_STREAM(feedback->marker_name << " is now at:\n" <<
			feedback->pose.position.x << ", " <<
			feedback->pose.position.y << ", " <<
			feedback->pose.position.z );

	std::string name = feedback->marker_name.substr(4); // removing the "wpt_" at the start

	waypoints_[name][0] = feedback->pose.position.x;
	waypoints_[name][1] = feedback->pose.position.y;

	ROS_INFO_STREAM("WAYPOINT " << name << " IS STORED AS:" << waypoints_[name][0] << ","
								<< waypoints_[name][1]);
}

void PointMGR::processPointOfInterestFeedback(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback)
{
	// This function handles feedback from the user moving points of interest in RViz

	ROS_INFO_STREAM(feedback->marker_name << " is now at:\n" <<
			feedback->pose.position.x << ", " <<
			feedback->pose.position.y << ", " <<
			feedback->pose.position.z );

	std::string name = feedback->marker_name.substr(4); // removing the "poi_" at the start

	points_of_interest_[name][0] = feedback->pose.position.x;
	points_of_interest_[name][1] = feedback->pose.position.y;
	points_of_interest_[name][2] = feedback->pose.position.z;

	ROS_INFO_STREAM("POINT OF INTEREST " << name << " IS STORED AS:" << points_of_interest_[name][0] << ","
									 << points_of_interest_[name][1] << ","
									 << points_of_interest_[name][2]);
}

void PointMGR::makeWayPoint(const std::string name)
{
	// This function is for showing the waypoints in RViz

	// Declaring important variables
	tf::Vector3 tf_position;					// position of the marker
	visualization_msgs::InteractiveMarker marker;			// interactive marker
	visualization_msgs::Marker marker_text;				// marker description
	visualization_msgs::Marker marker_obj;				// marker object to render on RViz
	visualization_msgs::InteractiveMarkerControl text_control;	// Marker control option for the description of the object (no control enabled, but this is necessary)
	visualization_msgs::InteractiveMarkerControl free_control;	// Marker control option for sliding along the ground plane
	visualization_msgs::InteractiveMarkerControl arrow_control;	// Marker control for moving along one specific axis on the ground plane
	tf::Quaternion orien;						// orientation vector for defining some of the control options
	std_msgs::ColorRGBA color;					// color to use for the marker

	// defining the color;
	color.r = 0.0;
	color.g = 1.0;
	color.b = 0.0;
	color.a = 0.9;

	// defining the position
	tf_position = tf::Vector3(waypoints_[name][0], waypoints_[name][1], 0);

	// placing the interactive marker at its desired position, wrt the frame "base_tf_frameid_"
	marker.header.frame_id = base_tf_frameid_;
	tf::pointTFToMsg(tf_position, marker.pose.position);
	marker.scale = 0.25;
	marker.name = "wpt_" + name;

	// define the marker description
	marker_text.pose.position.z = 0.25;
	marker_text.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
	marker_text.scale.z = marker.scale;
	marker_text.color = color;
	marker_text.text = "WPT: " + name;
	text_control.always_visible = true;
	text_control.markers.push_back(marker_text);
	marker.controls.push_back(text_control);

	// define the marker object
	orien = tf::Quaternion(0.0, 1.0, 0.0, 1.0);
	orien.normalize();
	tf::quaternionTFToMsg(orien, free_control.orientation);
	free_control.always_visible = true;
	marker_obj.type = visualization_msgs::Marker::CUBE;
	marker_obj.scale.x = marker.scale * 0.45;
	marker_obj.scale.y = marker.scale * 0.45;
	marker_obj.scale.z = marker.scale * 0.45;
	marker_obj.color = color;
	free_control.markers.push_back( marker_obj );
	free_control.name = "move_plane";
	free_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_PLANE;
	free_control.orientation_mode = visualization_msgs::InteractiveMarkerControl::FIXED;
	marker.controls.push_back( free_control );

	// define individual axis controls
	arrow_control.orientation_mode = visualization_msgs::InteractiveMarkerControl::FIXED;
	orien = tf::Quaternion(1.0, 0.0, 0.0, 1.0);
	orien.normalize();
	tf::quaternionTFToMsg(orien, arrow_control.orientation);
	arrow_control.name = "move_x";
	arrow_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
	marker.controls.push_back( arrow_control );

	orien = tf::Quaternion(0.0, 0.0, 1.0, 1.0);
	orien.normalize();
	tf::quaternionTFToMsg(orien, arrow_control.orientation);
	arrow_control.name = "move_z";
	arrow_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
	marker.controls.push_back( arrow_control );

	// appending the interactive marker to the server
	server_->insert(marker);
//	server_->setCallback(marker.name, &PointMGR::processFeedback);						// NOT THIS
	server_->setCallback(marker.name, boost::bind(&PointMGR::processWayPointFeedback, this, _1));		// THIS INSTEAD. WHY??? --> https://answers.ros.org/question/331365/error-no-match-for-call-to-boost/
}

void PointMGR::makePointOfInterest(const std::string name)
{
	// This function is for showing the points of interest in RViz

	// Declaring important variables
	tf::Vector3 tf_position;					// position of the marker
	visualization_msgs::InteractiveMarker marker;			// interactive marker
	visualization_msgs::Marker marker_text;				// marker description
	visualization_msgs::Marker marker_obj;				// marker object to render on RViz
	visualization_msgs::InteractiveMarkerControl text_control;	// Marker control option for the description of the object (no control enabled, but this is necessary)
	visualization_msgs::InteractiveMarkerControl free_control;	// Marker control option for sliding along the ground plane
	visualization_msgs::InteractiveMarkerControl arrow_control;	// Marker control for moving along one specific axis on the ground plane
	tf::Quaternion orien;						// orientation vector for defining some of the control options
	std_msgs::ColorRGBA color;					// color to use for the marker

	// defining the color;
	color.r = 1.0;
	color.g = 0.0;
	color.b = 0.0;
	color.a = 0.9;

	// defining the position
	tf_position = tf::Vector3(points_of_interest_[name][0], points_of_interest_[name][1], points_of_interest_[name][2]);

	// placing the interactive marker at its desired position, wrt the frame "base_tf_frameid_"
	marker.header.frame_id = base_tf_frameid_;
	tf::pointTFToMsg(tf_position, marker.pose.position);
	marker.scale = 0.25;
	marker.name = "poi_" + name;

	// define the marker description
	marker_text.pose.position.z = 0.25;
	marker_text.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
	marker_text.scale.z = marker.scale;
	marker_text.color = color;
	marker_text.text = "POI: " + name;
	text_control.always_visible = true;
	text_control.markers.push_back(marker_text);
	marker.controls.push_back(text_control);

	// define the marker object
	free_control.always_visible = true;
	marker_obj.type = visualization_msgs::Marker::SPHERE;
	marker_obj.scale.x = marker.scale * 0.45;
	marker_obj.scale.y = marker.scale * 0.45;
	marker_obj.scale.z = marker.scale * 0.45;
	marker_obj.color = color;
	free_control.markers.push_back( marker_obj );
	free_control.name = "move_three_dee";
	free_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_3D;
	free_control.orientation_mode = visualization_msgs::InteractiveMarkerControl::FIXED;
	marker.controls.push_back( free_control );

	// define individual axis controls
	arrow_control.orientation_mode = visualization_msgs::InteractiveMarkerControl::FIXED;
	orien = tf::Quaternion(1.0, 0.0, 0.0, 1.0);
	orien.normalize();
	tf::quaternionTFToMsg(orien, arrow_control.orientation);
	arrow_control.name = "move_x";
	arrow_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
	marker.controls.push_back( arrow_control );

	orien = tf::Quaternion(0.0, 1.0, 0.0, 1.0);
	orien.normalize();
	tf::quaternionTFToMsg(orien, arrow_control.orientation);
	arrow_control.name = "move_y";
	arrow_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
	marker.controls.push_back( arrow_control );

	orien = tf::Quaternion(0.0, 0.0, 1.0, 1.0);
	orien.normalize();
	tf::quaternionTFToMsg(orien, arrow_control.orientation);
	arrow_control.name = "move_z";
	arrow_control.interaction_mode = visualization_msgs::InteractiveMarkerControl::MOVE_AXIS;
	marker.controls.push_back( arrow_control );

	// appending the interactive marker to the server
	server_->insert(marker);
//	server_->setCallback(marker.name, &PointMGR::processFeedback);						// NOT THIS
	server_->setCallback(marker.name, boost::bind(&PointMGR::processPointOfInterestFeedback, this, _1));		// THIS INSTEAD. WHY??? --> https://answers.ros.org/question/331365/error-no-match-for-call-to-boost/
}

void PointMGR::addWayPoint(const std::string name, const std::array<float, 2> position)
{
	// This function is for adding a waypoint to the "dictionary" of waypoints to be managed: waypoints_
	// It also immediately renders that waypoint on RViz
	waypoints_[name] = position;
	makeWayPoint(name);
	server_->applyChanges();
}

void PointMGR::addPointOfInterest(const std::string name, const std::array<float, 3> position)
{
	// This function is for adding a point of interest to the "dictionary" of points of interest to be managed: points_of_interest_
	// It also immediately renders that point of interest on RViz
	points_of_interest_[name] = position;
	makePointOfInterest(name);
	server_->applyChanges();
}

void PointMGR::removeWayPoint(const std::string name)
{
	// This function is for removing a waypoint from the "dictionary" of waypoints to be managed: waypoints_
	// It also immediately refreshes RViz to no longer present the waypoint
	waypoints_.erase(name);
	refreshAllPoints();
}

void PointMGR::removePointOfInterest(const std::string name)
{
	// This function is for removing a point of interest from the "dictionary" of points of interest to be managed: points_of_interest_
	// It also immediately refreshes RViz to no longer present the point of interest
	points_of_interest_.erase(name);
	refreshAllPoints();
}

void PointMGR::refreshAllPoints()
{
	// This function refreshes the RViz render of all the points, using the currently available ones in waypoints_ and points_of_interest_

	server_->clear();
	for (auto const& item : waypoints_)
	{
		makeWayPoint(item.first);
	}

	for (auto const& item : points_of_interest_)
	{
		makePointOfInterest(item.first);
	}

	server_->applyChanges();
}

void PointMGR::savePoints()
{
	// This function can be called to save the points into a txt file.

	std::ofstream point_file;
	point_file.open(save_file_name_);
	
	for (auto const& item : waypoints_)
	{
		point_file << "WPT" << save_sep_ << item.first << save_sep_ << item.second[0] << save_sep_ << item.second[1] << "\n";
		ROS_INFO_STREAM(item.first << ": " << item.second[0] << ", " << item.second[1]);
	}

	for (auto const& item : points_of_interest_)
	{
		point_file << "POI" << save_sep_ << item.first << save_sep_ << item.second[0] << save_sep_ << item.second[1] << save_sep_ << item.second[2] << "\n";
		ROS_INFO_STREAM(item.first << ": " << item.second[0] << "," << item.second[1] << "," << item.second[2]);
	}

	point_file.close();
	ROS_INFO_STREAM("SAVED TO: " << save_file_name_);

}

void PointMGR::loadPoints()
{
	// This function is for reading the contents of the .txt file which holds the saved waypoints and points of interest.
	std::ifstream point_file;
	point_file.open(save_file_name_);

	std::string line;		// a line is built like this (custom separator can be chosen) : "POI/WPT", point name, coordinates
	while (getline(point_file, line))
	{
		std::vector<std::string> parsed_line;
		parsed_line = parseLine(line, save_sep_);

		if(parsed_line[0] == "WPT")
		{
			waypoints_[parsed_line[1]][0] = std::stof(parsed_line[2]);
			waypoints_[parsed_line[1]][1] = std::stof(parsed_line[3]);
		}

		if(parsed_line[0] == "POI")
		{
			points_of_interest_[parsed_line[1]][0] = std::stof(parsed_line[2]);
			points_of_interest_[parsed_line[1]][1] = std::stof(parsed_line[3]);
			points_of_interest_[parsed_line[1]][2] = std::stof(parsed_line[4]);
		}
	}

	refreshAllPoints();
	ROS_INFO_STREAM("POINTS LOADED");
	summarizePoints();

	point_file.close();
}

std::vector<std::string> PointMGR::parseLine(std::string line, std::string delimiter)
{
	// check this: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos)
	{
		token = line.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	
	res.push_back(line.substr(pos_start));
	return res;
}

void PointMGR::summarizePoints()
{
	ROS_INFO_STREAM("WAYPOINTS ARE:");
	for (auto const& item: waypoints_)
	{
		ROS_INFO_STREAM(item.first << " : " << item.second[0] << ", " << item.second[1]);
	}

	ROS_INFO_STREAM("");	
	ROS_INFO_STREAM("POINTS OF INTEREST ARE:");
	for (auto const& item: points_of_interest_)
	{
		ROS_INFO_STREAM(item.first << " : " << item.second[0] << ", " << item.second[1] << ", " << item.second[2]);
	}
}


void PointMGR::serverReset()
{
	// This is the server handling the RViz side
	server_.reset();
}

bool PointMGR::spawnWayPointService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res)
{
	addWayPoint(req.name, {0, -1});	// TODO: Maybe smarter position
	ROS_INFO_STREAM("request: spawn waypoint with name: " << req.name);
	return true;	
}

bool PointMGR::spawnPOIService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res)
{
	addPointOfInterest(req.name, {0, 0, 1});
	ROS_INFO_STREAM("request: spawn point of interest with name: " << req.name);
	return true;
}

bool PointMGR::killWayPointService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res)
{
	removeWayPoint(req.name);
	ROS_INFO_STREAM("request: remove waypoint with name: " << req.name);
	return true;
}

bool PointMGR::killPOIService(point_mgmt_msgs::SimpleMarker::Request &req, point_mgmt_msgs::SimpleMarker::Response &res)
{
	removePointOfInterest(req.name);
	ROS_INFO_STREAM("request: remove point of interest with name: " << req.name);
	return true;
}

bool PointMGR::savePointsService(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
	savePoints();
	return true;
}

bool PointMGR::loadPointsService(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
	loadPoints();
	return true;
}

bool PointMGR::getPointsSummary(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
	summarizePoints();
	return true;
}

bool PointMGR::WayPointLocService(point_mgmt_msgs::MarkerCoord::Request &req, point_mgmt_msgs::MarkerCoord::Response &res)
{
	std::string name;
	name = req.name;
	if (waypoints_.find(name) != waypoints_.end())	// check if the waypoint name exists
	{
		res.x = waypoints_[name][0];
		res.y = waypoints_[name][1];

		ROS_INFO_STREAM("Requesting location of WPT: " << req.name);
		ROS_INFO_STREAM("Response coordinates: " << res.x << ", " << res.y << ", " << res.z);

		return true;
	}
	return false;
}

bool PointMGR::POILocService(point_mgmt_msgs::MarkerCoord::Request &req, point_mgmt_msgs::MarkerCoord::Response &res)
{
	std::string name;
	name = req.name;
	if (points_of_interest_.find(name) != points_of_interest_.end())	// check if the point of interest name exists
	{
		res.x = points_of_interest_[name][0];
		res.y = points_of_interest_[name][1];
		res.z = points_of_interest_[name][2];

		ROS_INFO_STREAM("Requesting location of POI: " << req.name);
		ROS_INFO_STREAM("Response coordinates: " << res.x << ", " << res.y << ", " << res.z);

		return true;
	}
	return false;
}

bool PointMGR::WayPointNamesService(point_mgmt_msgs::MarkerNames::Request &req, point_mgmt_msgs::MarkerNames::Response &res)
{
	std::vector<std::string> waypoint_names;

	ROS_INFO_STREAM("Providing Waypoint Names:");
	for (auto const& item: waypoints_)
	{
		ROS_INFO_STREAM(item.first);
		waypoint_names.push_back(item.first);
	}
	
	res.names = waypoint_names;
	return true;

}

bool PointMGR::POINamesService(point_mgmt_msgs::MarkerNames::Request &req, point_mgmt_msgs::MarkerNames::Response &res)
{
	std::vector<std::string> point_of_interest_names;

	ROS_INFO_STREAM("Providing Point Of Interest Names:");
	for (auto const& item: points_of_interest_)
	{
		ROS_INFO_STREAM(item.first);
		point_of_interest_names.push_back(item.first);
	}
	
	res.names = point_of_interest_names;
	return true;

}


