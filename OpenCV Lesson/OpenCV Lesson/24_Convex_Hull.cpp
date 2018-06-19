#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, grayImg, dst;
int threshold_value = 100;
int threshold_max = 255;
const char* srcImg = "input image";
const char* dstImg = "convex hull image";
RNG rng(12345);
void Threshold_Callback(int, void*);
int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/lines.png");
	if (src.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	namedWindow(srcImg, 1);
	namedWindow(dstImg, 1);
	imshow(srcImg, src);

	cvtColor(src, grayImg, CV_BGR2GRAY);
	blur(grayImg, grayImg, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	imshow("gray image", grayImg);

	const char* tBar = "threshold value:";
	createTrackbar(tBar, dstImg, &threshold_value, threshold_max, Threshold_Callback);
	Threshold_Callback(0, 0);


	waitKey(0);
	return 0;
}

void Threshold_Callback(int, void*)
{
	Mat bin_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	threshold(grayImg, bin_output, threshold_value, threshold_max, THRESH_BINARY);
	findContours(bin_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point>> convexs(contours.size());
	for (size_t i = 0; i < contours.size(); i++) {
		convexHull(contours[i], convexs[i], false, true);
	}

	//»æÖÆ
	dst = Mat::zeros(src.size(), CV_8UC3);
	vector<Vec4i>empty(0);
	for (size_t k = 0; k < contours.size(); k++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(dst, contours, k, color, 2, LINE_8, hierarchy, 0, Point(0, 0));
		drawContours(dst, convexs, k, color, 2, LINE_8, empty, 0, Point(0, 0));
	}
	imshow(dstImg, dst);
	return;
}