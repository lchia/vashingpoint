#ifndef EVAL_VP_H
#define EVAL_VP_H
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <time.h>
#include <ratio>
#include <chrono>
#include <ctime>
#include <string>
#include <math.h>
#include <armadillo>

class Eval_VP
{
public:
    Eval_VP();
    std::vector<cv::Point2f> run(cv::Mat img);
};

#endif // EVAL_VP_H
