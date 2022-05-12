# Trans thermal cameras to ROS
## Development
- Ubuntu 20.04
- ROS noetic
- OpenCV  4.2

## ROS package 
Two ros packages are needed:
- cv_bridge: Bridge between ROS messages and OpenCV;
- image_geometry: Collection of methods for dealing with image and pixel geometry 

## How to use this package
1. check device port.
    - webcam of a pc is usually indexed as 0 in
        - ```cv::VideoCapture cap(0)```,
        - or ```cv::VideoCapture cap("/dev/video0")```.

      Accessing a usb camera is suggested to get the absolute address instead of using ```cap(index)```.

      Therefore, a linux command ```ls /dev/``` can help find the needed address.
2. 