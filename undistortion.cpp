#include "undistortion.h"

UNDISTORTION::UNDISTORTION()
{
    //*********************************************
    /**
     * LingDu A305 parameters
     *       : 1.2M CMOS传感器，1/4 inch感光面积, 屏幕分辨率 1920×1080P
     *
     * 相机CCD尺寸的大小详细列表
     * 1英寸——靶面尺寸为宽12.7mm*高9.6mm，对角线16mm。
     * 2/3英寸——靶面尺寸为宽8.8mm*高6.6mm，对角线11mm。
     * 1/2英寸——靶面尺寸为宽6.4mm*高4.8mm，对角线8mm。
     * 1/3英寸——靶面尺寸为宽4.8mm*高3.6mm，对角线6mm。
     * 1/4英寸——靶面尺寸为宽3.2mm*高2.4mm，对角线4mm。
     *
     * dx = 3.2 / 1920
     * dy = 2.4 / 1080
     *
     * f = (f/dx) * dx = 991.83 * (3.2 / 1920) = 1.65305
     * f = (f/dy) * dy = 744.04 * (2.4 / 1080) = 1.65342
     *
     *  double f1 = 991.83 * (3.2 / 1920); // (f/dx) * dx = 1.65305
     *  double f2 = 744.04 * (2.4 / 1080); // (f/dy) * dy = 1.65342
     *  double f = (f1 + f2) / 2.0; //focal length;       = 1.65323
     *
     *
     *
     * camera matrix
     *      f/dx 0    u_0
     *       0   f/dy v_0
     *       0   0    1
     * 内参矩阵的参数含义：
     *       f：焦距，单位毫米，dx：像素x方向宽度，单位毫米，1/dx：x方向1毫米内有多少个像素
     *       f/dx：使用像素来描述x轴方向焦距的长度
     *       f/dy：使用像素来描述y轴方向焦距的长度
     *       u0,v0,主点的实际位置，单位也是像素。
     *
     * */
    //camera matrix
    cameraMatrix = cv::Mat::eye(3, 3, CV_64F);
    cameraMatrix.at<double>(0,0) = 991.83;     //  f/dx
    cameraMatrix.at<double>(0,1) = 0;
    cameraMatrix.at<double>(0,2) = 676.19;     //  u_0
    cameraMatrix.at<double>(1,0) = 0;
    cameraMatrix.at<double>(1,1) = 744.04;     //  f/dy
    cameraMatrix.at<double>(1,2) = 347.44;     //  v_0
    cameraMatrix.at<double>(2,0) = 0;
    cameraMatrix.at<double>(2,1) = 0;
    cameraMatrix.at<double>(2,2) = 1;

    //distortion coefficients
    distCoeffs = cv::Mat::zeros(4, 1, CV_64F);
    distCoeffs.at<double>(0,0) = -0.4123;
    distCoeffs.at<double>(1,0) =  0.1773;
    //********************************************
}

UNDISTORTION::~UNDISTORTION(){}

cv::Mat UNDISTORTION::undistort(cv::Mat img){
    cv::Mat img_undistort;
    cv::undistort(img, img_undistort, cameraMatrix, distCoeffs);
    //cv::resize(img_undistort, img_undistort, cv::Size(img.cols, img.rows));

    return img_undistort;
}
