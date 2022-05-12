cmake_minimum_required(VERSION 3.0.2)
project(lib_open_thermal_camera)

# find needed ros packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  camera_info_manager
)

# find OPENCV
#find_package(OpenCV 4.2 REQUIRED) 
# specify OpenCV 4.5.4 to link
set(OpenCV_DIR /usr/local/lib/cmake/opencv4)
find_package(OpenCV 4.5.4 REQUIRED)
#if (OpenCV_FOUND)
    message(STATUS "OpenCV is found")
    message(STATUS "${OpenCV_LIBRARIES}")
#endif (OpenCV_FOUND)




catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES publisher
   CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs camera_info_manager 
#  DEPENDS system_lib
)


# add all catkin package
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

include_directories(${OpenCV_INCLUDE_DIRS})

# define executable
add_executable(${PROJECT_NAME}_node src/open_camera.cpp)
#add_executable(${PROJECT_NAME}_node src/open_images.cpp)

# link executable to ros dependent packages and OPENCV
target_link_libraries(${PROJECT_NAME}_node ${OpenCV_LIBRARIES})

target_link_libraries(${PROJECT_NAME}_node
${catkin_LIBRARIES}
)