#include "linedetect.h"

LineDetect::LineDetect()
{

}

std::vector<std::vector<double>> LineDetect::ld(cv::Mat img, double threshold_length, bool showing) {
    std::vector<std::vector<double>> lines;

    cv::Mat img_gray;
    if(img.channels()==1) {
        img_gray = img;
    }
    else {
        cv::cvtColor(img, img_gray, CV_BGR2GRAY);
    }

    unsigned int _cols = unsigned(img_gray.cols);
    unsigned int _rows = unsigned(img_gray.rows);
    image_double img_lsd = new_image_double(_cols, _rows);
    unsigned char* img_src = (unsigned char *) img_gray.data;

    for(unsigned int r = 0; r < _rows; r++) {
        for(unsigned int c = 0; c < _cols; c++) {
            img_lsd->data[r * _cols + c] = img_src[r * _cols + c];
        }
    }

    ntuple_list lines_lsd = lsd(img_lsd);
    unsigned int num_lines = lines_lsd->size;
    unsigned int dim = lines_lsd->dim;
    std::vector<double> line_temp(4);
    for(unsigned int i = 0; i < num_lines; i++) {
        double x1 = lines_lsd->values[i * dim + 0];
        double y1 = lines_lsd->values[i * dim + 1];
        double x2 = lines_lsd->values[i * dim + 2];
        double y2 = lines_lsd->values[i * dim + 3];

        double l = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
        if(l < threshold_length) {
            line_temp[0] = x1;
            line_temp[1] = y1;
            line_temp[2] = x2;
            line_temp[3] = y2;

            lines.push_back(line_temp);
        }
    }
    free_ntuple_list(lines_lsd);

    if(showing) {
        cv::Mat img_show = img.clone();

        unsigned long num_lines = lines.size();
        for(unsigned int k = 0; k < num_lines; k++) {
            std::vector<double> _line = lines[k];
            cv::Point2d pt1(_line[0], _line[1]);
            cv::Point2d pt2(_line[2], _line[3]);
            cv::circle(img_show, pt1, 1, cv::Scalar(255, 0, 0), 1, 8, 0);
            cv::circle(img_show, pt2, 1, cv::Scalar(0, 255, 0), 1, 8, 0);
            cv::line(img_show, pt1, pt2, cv::Scalar(0, 0, 255), 1, 8, 0);
        }
        cv::imshow("LINEDETECT", img_show);
        cv::waitKey(1);
    }

    return lines;
}
