

# qtros
<img src="https://img.shields.io/badge/ROS%20version-melodic-blue.svg"/>
<p align="justify">
Welcome to qtros package. This workspace is built with c++. You can see the table of content below where the gui panel is presented with its characteristics. The installation section gives you command you need to type in your command line in order to run this package. In the code section, the several files are explained in details.
</p>

##### Table of Contents  
[Overview](#Overview)  
[Installation](#Installation)  
[code](#code)  
- [src](#src)  
- [include](#include)  
- [ui](#ui)  



   


## Overview
This package contains a node that builds the graphical user interphace window. The user can communicate with the robots via this graphical interface. Below are the description of each tab that will appear in the user's screen when this last one launches the package.
<p align="center">
<img src="./resources/images/tab1.png" alt="tab 1" width="700"/>
</p>
<p align="justify">
 
The first tab shown above allows the user to connect to the master node or stop the connection. The user can enter the ROS Master Url and Ros IP address. The settings can be remembered the next time the gui is run. 
</p>
<p align="center">
<img src="./resources/images/tab2.png" alt="tab 2" width="700"/>
</p>
<p align="justify">

In the second tab camera, the user can visualize the camera output by pressing the button start. The user can stop the process at any time by pressing the button stop. By pressing the button snapshot, the user can take a snapshot  wich will saved in a relative path which must be declared in [here](https://gitlab.tudelft.nl/cor/ro47007/2022/team-15/cor_mdp_husky/-/blob/testing/qtros/src/main_window.cpp#L313). On the right, the user can perform teleoperation of the end effector either by moving it translational wise or rational wise.
</p>
<p align="center">
<img src="./resources/images/tab3.png" alt="tab 2" width="700"/>
</p>
<p align="justify"/>
Inside the move husky tab, the user can press the button `refresh all markers` to load all the markers saved in previous sessions. The user can then click on the waypoint of his choice in the list on the left and press the button `GO` to let Husky go to the desired location.  
Similarly, the user can click on a point to look at in the right list, and then press `look` to let kinova arm place its end effector such that the desire point of interest is in the camera's field of view. 
If the battery falls under a threshold, the user will be informed and can press the button `charging` to stop all activities and let Husky go back to its charging station.
</p>
<p align="center">
<img src="./resources/images/tab4.png" alt="tab 2"
width="700"/>
</p>

<p align="justify">
In the Place Waypoints tab shown below, the user can spawn the markers saved in previous sessions in rviz by pressing `load markers`. The user can interact with the markers on Rviz, see [point_mgmt/Readme](../point_mgmt). In addition, the user can create a new marker being a waypoint or a point of interest. 
He must choose a name by typing in the edit line and then decides either the marker is a 2D waypoint for Husky to reach or a 3D point of interest that Kinova could track. The user will need to switch to Rviz window to place the spawned marker in a location he sees fit. After that, the user can go back to the GUI window and press the `save markers` button.
The freshly saved marker will be now be remembered in future sessions. If the user wants to move husky to the new waypoint or make kinova look at the new waypoint, the user must go to the `move husky tab` and follow the directives stated above.
</p>

## Installation
<p align="justify">
To run this package, you first need to install qt5 software.

``` bash
sudo apt-get update
sudo apt-get install qt5-default
sudo apt-get install qtcreator
sudo apt-get install ros-melodic-qt-create
sudo apt-get install ros-melodic-qt-build
```
You then can run the node with the following:

``` bash
rosrun qtros qtros
```
The window with the tabs explained above will appear alongside a prontobot popup informing you that the node is running.
</p>

## Code

[//]: # (Symbols we can use for folder structure  │  ├  ─  └)
The package is organized in the following manner:
```
qtros
 │
 ├─── CMakeLists.txt
 │
 ├─── package.xml
 │
 ├─── README.md
 │
 │
 ├─── include
 │     └─── qtros
 │            │─── main_window.hpp
 │            │─── qnode.hpp
 │            └─── ui_main_window.h
 │
 ├─── src
 │     ├─── main.cpp 
 │     │─── main_window.hpp 
 │     └─── qnode.cpp
 │
 │
 ├─── launch
 │     └─── gui.launch
 │
 ├─── ui
 │     └─── main_window.ui
 └─── resources
       ├─── images.qrc
       └─── images
              │─── icon.hpp
              │─── tab1.hpp
              │───...
              └─── tab4.png
            

```
### src
Inside `src`, three cpp files are present to declare the various subsribed topics, the callback functions and the qt widgets implementations.  
Inside `qnode.cpp`, t

### include  

### ui
The `ui/` directory contains the ui file named [main_window.ui](ui/main_window.ui) that stores the different configurations for the graphical interface programm. This ui file is automatically generated after designing the different tabs of the gui in Qt5 designer software and saving it as an .ui file. Several widgets such as push buttons, labels, line edits, list widget,  are dragged and dropped onto the main window. The widgets are then given an appropriate name for easier differenciation between the several buttons when assigning them with a specific task during coding.



