#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <ratio>
#include <chrono>
#include <ctime>
#include <string>

#include "undistortion.h"
#include "linedetect.h"
#include "eval_vp.h"

int main()
{

    UNDISTORTION* undistort = new UNDISTORTION();
    LineDetect* ld = new LineDetect();
    Eval_VP* evp = new Eval_VP();
    /**
     **************************************
     * OPENING VIDEO
     **************************************
    **/
    cv::VideoCapture cap;
    cap.open("/home/haha/workspaces/test/data/fabuhui_final.mov");
    //cap.open("/home/haha/workspaces/test/data/trafficlight1080p.mov");
    //cap.open("/home/haha/workspaces/test/data/gaoxinxing_all.mov");
    if (!cap.isOpened()) {
      std::cout << "Failed to open camera." << std::endl;
      return -1;
    }

    cv::Mat img, rst_img;
    cv::String filename_save;
    //*******************************************************************
    int frame_id = 0;
    while(1){
        auto fps_t1 = std::chrono::high_resolution_clock::now();
        //Capture an image and resize to 720p;
        cap >> img;
        cv::Mat img_copy;;
        cv::resize(img, img_copy, cv::Size(1280, 720));
        std::cout << "-> input size : " << img_copy.cols << "x" << img_copy.rows << std::endl;
        cv::Mat undistortImg = undistort->undistort(img_copy);
        std::cout << "-> undistortImg size : " << undistortImg.cols << "x" << undistortImg.rows << std::endl;

        //std::vector<std::vector<double>> lines = ld->ld(undistortImg, 100, true);

        /**
         * ESTIMATE VANISHING POINT
         */
        evp->run(undistortImg);

        /**
         **************************************
         * SHOWING
         **************************************
        **/
        auto fps_showing_t1 = std::chrono::high_resolution_clock::now();
        undistortImg.copyTo(rst_img);


        auto fps_showing_t2 = std::chrono::high_resolution_clock::now();
        float fps_showing_time = std::chrono::duration<float, std::milli>(fps_showing_t2 - fps_showing_t1).count();
        auto fps_t2 = std::chrono::high_resolution_clock::now();
        float fps_time = std::chrono::duration<float, std::milli>(fps_t2 - fps_t1).count();

        /**
         **************************************
         * Time used
         **************************************
        **/
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        std::cout << ">>frame: " << frame_id << std::endl;
        std::cout << ">>SHOWING:       using " << fps_showing_time  << " ms." << std::endl;
        std::cout << ">>TOTALLY:       using " << fps_time  << " ms." << std::endl;
        cv::imshow("ADAS++", rst_img);
        cv::waitKey(1);

        //*************************
        //FRAME_ID
        //*************************
        frame_id++;
        if(cv::waitKey(10)==27) {
            cap.release();
        }
    }

    return 0;
}
