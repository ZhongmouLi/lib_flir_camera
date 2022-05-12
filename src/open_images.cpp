#include <ros/ros.h>
#include <ros/console.h>
#include <iostream>
#include <cstdlib>  // exit
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp> // window
#include <opencv2/imgproc.hpp> // draw
#include <opencv2/imgcodecs.hpp> // module, which provides functions for reading and writing
#include <cv_bridge/cv_bridge.h> // cv_bridge for trans between ROS sensor_mgs and OpenCV images
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>

int main(int argc, char* argv[])
{

    ros::init(argc, argv, "display_themral_camera");

    // define ros handle
    ros::NodeHandle nh;

    //define ros node frequency
    ros::Rate loop_rate(20);

    
    cv::Mat img_cv = imread("/home/p00972zl/Desktop/Codes/Cpp_OpenCV_Tutorial_1/src/sss.png", cv::IMREAD_COLOR);

    cv_bridge::CvImage img_bridge;

    img_bridge.header.frame_id = "my_image";
    img_bridge.header.seq = 1;
    img_bridge.encoding = "bgr8";


    sensor_msgs::Image img_msg;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub_img = it.advertise("/my_camera/image", 1);

    // keep showing images to screen
    while (ros::ok()) {

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
        cv::rectangle(img_cv,pt_left_top,pt_right_bom,cv::Scalar(0,255,0),1,1,0);

        // show images
        //cv::imshow("Display window", image);
        // each image shows for 25 milliseconds
        //cv::waitKey(25);

        // test in rviz
        // sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();

        // test in rviz
        //img_bridge = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::RGB8, img_cv);
        //img_bridge.toImageMsg(img_msg);

        // test in rviz
        // update image time
        ros::Time time=ros::Time::now(); 
        img_bridge.header.stamp = time;
        // update image sequence
        img_bridge.header.seq++;
        // ass images in cv to images in cv_bridge
        img_bridge.image = img_cv;

        // cv_bridge transfer images in cv to images in sensor_msgs
        img_bridge.toImageMsg(img_msg);

        // publish sensor_msgs
        pub_img.publish(img_msg);

        ros::spinOnce();
  
        loop_rate.sleep();

    }


    return 0;
}