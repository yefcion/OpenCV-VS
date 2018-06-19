#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, dst;
const char* srcImg = "input image";
const char* dstImg = "find contours image";
int threshold_value = 100;
int threshold_max = 255;
RNG rng;

void Demo_Contours(int, void*);
int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/°²ÄÝ.jpg");
	if (src.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	namedWindow(srcImg, 1);
	namedWindow(dstImg, 1);
	imshow(srcImg, src);

	cvtColor(src, src, CV_BGR2GRAY);

	const char* tBar = "threshold value:";
	createTrackbar(tBar, dstImg, &threshold_value, threshold_max, Demo_Contours);
	Demo_Contours(0, 0);


	waitKey(0);
	return 0;
}

void Demo_Contours(int, void*)
{
	Mat canny_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Canny(src, canny_output, threshold_value, threshold_value * 2, 3, false);
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	dst = Mat::zeros(src.size(), CV_8UC3);
	RNG rng(12345);
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, i, color, 2, 8, hierarchy, 0, Point(0, 0));
	}
	imshow(dstImg, dst);
}