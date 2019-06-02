#ifndef LINEDETECT_H
#define LINEDETECT_H

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

extern "C"
{
    #include "lsd.h"
};

class LineDetect
{
public:
    LineDetect();
    std::vector<std::vector<double>> ld(cv::Mat img, double threshold_length, bool showing);
};

#endif // LINEDETECT_H
