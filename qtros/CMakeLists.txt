##############################################################################
# CMake
##############################################################################

cmake_minimum_required(VERSION 2.8.3)
project(qtros)

##############################################################################
# Catkin
##############################################################################

# qt_build provides the qt cmake glue, roscpp the comms for a default talker
find_package(catkin REQUIRED COMPONENTS 
qt_build 
roscpp 
sensor_msgs 
image_transport 
cv_bridge  
actionlib
move_base_msgs
std_msgs
point_mgmt_msgs
point_mgmt
moveit_core
moveit_ros_planning
moveit_ros_planning_interface
moveit_ros_perception
moveit_ros_move_group)
find_package(OpenCV REQUIRED)

include_directories(include ${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

# Use this to define what the package will export (e.g. libs, headers).
# Since the default here is to produce only a binary, we don’t worry about
# exporting anything.
catkin_package()

##############################################################################
# Qt Environment
##############################################################################
set(CMAKE_AUTOUIC ON)

# this comes from qt_build’s qt-ros.cmake which is automatically
# included via the dependency ca ll in package.xml
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)

##############################################################################
# Sections
##############################################################################
file(GLOB QT_FORMS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ui/*.ui)
file(GLOB QT_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} resources/*.qrc)
file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/qtros/*.hpp)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_UI(QT_FORMS_HPP ${QT_FORMS})
QT5_WRAP_CPP(QT_MOC_HPP ${QT_MOC})


##############################################################################
# Sources
##############################################################################

file(GLOB_RECURSE QT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS src/*.cpp)

##############################################################################
# Binaries
##############################################################################
add_executable( qtros ${QT_SOURCES} ${QT_RESOURCES_CPP} ${QT_FORMS_HPP} ${QT_MOC_HPP} )
qt5_use_modules(qtros Widgets Gui Core)
target_link_libraries(qtros ${QT_LIBRARIES} ${catkin_LIBRARIES} ${OpenCV_LIBS})
target_include_directories(qtros PUBLIC include)
