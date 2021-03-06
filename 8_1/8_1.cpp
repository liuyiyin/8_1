// 8_1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat src = imread("D:\\rim.png", 0);
	cv::Mat dst;
	
	adaptiveThreshold(src, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV,35, 10);
	
	vector<vector<Point>> contours;
	findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {
       
		RotatedRect rbox = minAreaRect(contours[i]);
		float width = rbox.size.width;
		float height = rbox.size.height;
		float a = width / height;
		float b = width * height;
		
		if (a > 0.9&&a< 1.1&&b > 50) {
			drawContours(src, contours, i, Scalar(0, 255, 255), 1, 8);
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i) {
				cv::line(src, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	cv::imshow("src", src);
	waitKey(0);
    return 0;
}

