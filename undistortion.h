#ifndef UNDISTORTION_H
#define UNDISTORTION_H

#include <stdio.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

#include <chrono>


class UNDISTORTION
{
public:
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;

public:
    UNDISTORTION();
    ~UNDISTORTION();
    cv::Mat undistort(cv::Mat img);
};

#endif // UNDISTORTION_H
