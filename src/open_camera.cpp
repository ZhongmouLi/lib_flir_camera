#include <ros/ros.h>
#include <ros/console.h>
#include <iostream>
#include <cstdlib>  // exit
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp> // window
#include <opencv2/imgproc.hpp> // draw



static const std::string OPENCV_WINDOW = "Image window";


int main(int argc, char* argv[])
{

    ros::init(argc, argv, "display_themral_camera");

    // define ros handle
    ros::NodeHandle nh;

    //define ros node frequency
    ros::Rate loop_rate(10);

        // declear image
    cv::Mat image;

    // define display windows
    cv::namedWindow(OPENCV_WINDOW,cv::WINDOW_NORMAL);
    //cv::resizeWindow(OPENCV_WINDOW, 640, 480);
    // open camera
    // 0 is the index of the Webcam
         cv::VideoCapture cap(0,cv::CAP_V4L2);    // 4 gives a blue screen ,cv::CAP_V4L2
    //   cv::VideoCapture cap("/home/p00972zl/catkin_ws/src/lib_open_thermal_camera/src/test.avi"); 
    //cv::VideoCapture cap;
    //int deviceID = 0;             // 0 = open default camera
    //int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    // open selected camera using selected API
    //cap.open(deviceID, apiID);
    
    ROS_INFO_STREAM("point 1");
    // set size of dimention of camera image
    // output is 
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    
    ROS_INFO_STREAM("point 2");
    // check if camera is open or not
    if ((!cap.isOpened()) || (!cap.grab())) //|| (!cap.retrieve(image)) || image.empty()
    {
        ROS_INFO_STREAM("cannot open camera"); // error message if camera is not open
        exit(EXIT_SUCCESS);
        
    }
    ROS_INFO_STREAM("point 3");

    // keep showing images to screen
    while (ros::ok()) {

        // declear image
        cv::Mat image;

        // 1. pass the captured video to image
            ROS_INFO_STREAM("Before write images");
            //cap >> image;
            cap.read(image);
            ROS_INFO_STREAM("After write images");
                    // check if we succeeded
            if (image.empty()) {
                ROS_ERROR_STREAM("ERROR! blank frame grabbed");
                break;
            }

/*             cv::Mat ig_;
            cap.read(ig_);

                if (ig_.empty())
                {
                    ROS_INFO_STREAM("ERROR! blank frame grabbed");
                    break;
                } */
                

       // Debug: check size of image
            // cv::Size sz = image.size();
            //std::cout<< "height of image "<< sz.height<<std::endl;
            //std::cout<< "weight of image "<< sz.width<<std::endl;

        // 2. plot a rectangle in image
        // 2.1 define rectangle with left_top and right_bot
        // NOTE: size of frame is defined by cap.set()
                cv::Point pt_left_top(160,120);
                cv::Point pt_right_bom(480,360);

        // 2.2 plot rectagnle 
            // arguments:
            //1-2 rectangle is defined using one left_top and one right_botom 
            //3 color green defined as cv::Scalar(0,255,0)
            //4-6 thickness 1
        cv::rectangle(image,pt_left_top,pt_right_bom,cv::Scalar(0,255,0),1,1,0);

        // show images
        cv::imshow(OPENCV_WINDOW, image);
        // each image shows for 25 milliseconds
        cv::waitKey(25);  
 
   //        ROS_INFO_STREAM("Node is ON");

        ros::spinOnce();
  
        loop_rate.sleep();

    }


    return 0;
}