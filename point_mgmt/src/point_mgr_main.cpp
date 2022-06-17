#include "point_mgmt/point_mgr.h"


int main ( int argc, char** argv)
{
	// Initialising server node
	ros::init(argc, argv, "point_mgr");

	PointMGR my_points = PointMGR();

//	// CAN ALSO BE CONSTRUCTED THIS WAY:
//	// creating the server
//	boost::shared_ptr<interactive_markers::InteractiveMarkerServer> server;
//	server.reset( new interactive_markers::InteractiveMarkerServer("basic_controls","",false) );
//	PointMGR my_points = PointMGR(server);
	
	ros::spin();

	my_points.serverReset();
}

