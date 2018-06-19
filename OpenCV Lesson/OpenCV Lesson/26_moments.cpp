#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, grayImg, dst;
int threshold_value = 80;
int threshold_max = 255;
const char* srcImg = "input image";
const char* dstImg = "rectangle image";
RNG rng(12345);
void Demo_Moments(int, void*);
int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/sgali.jpg");
	if (src.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	namedWindow(srcImg, 1);
	namedWindow(dstImg, 1);
	imshow(srcImg, src);

	cvtColor(src, grayImg, CV_BGR2GRAY);
	GaussianBlur(grayImg, grayImg, Size(3, 3),0,0);

	const char* tBar = "threshold value:";
	createTrackbar(tBar, dstImg, &threshold_value, threshold_max, Demo_Moments);
	Demo_Moments(0, 0);

	waitKey(0);
	return 0;
}

void Demo_Moments(int, void*)
{
	Mat canny_output;
	vector<vector<Point>> contours;//定义轮廓点的数据集
	vector<Vec4i> hierarchy;//层数

	Canny(grayImg, canny_output, threshold_value, threshold_value*2, 3, false);
	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<Moments> contours_moments(contours.size());
	vector<Point2f> ccs(contours.size());//中心位置
	for (size_t i = 0; i < contours.size(); i++) {
		contours_moments[i] = moments(contours[i]);
		ccs[i] = Point(static_cast<float>(contours_moments[i].m10 / contours_moments[i].m00,
			static_cast<float>(contours_moments[i].m01 / contours_moments[i].m00)));

	}

	//绘制
	src.copyTo(dst);
	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		printf("center point x : %.2f  y : %.2f\n", ccs[i].x, ccs[i].y);
		printf("contours %d area : %.2f  arc lenth : %.2f \n", i, contourArea(contours[i]), arcLength(contours[i], true));
		drawContours(dst, contours, i, color, 2, 8, hierarchy, 0, Point(0, 0));
		circle(dst, ccs[i], 2, color, 2, 8);
	}

	imshow(dstImg, dst);
	return;
}