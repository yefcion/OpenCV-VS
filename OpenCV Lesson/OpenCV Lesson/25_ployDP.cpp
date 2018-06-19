#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, grayImg, dst;
int threshold_value = 170;
int threshold_max = 255;
const char* srcImg = "input image";
const char* dstImg = "rectangle image";
RNG rng(12345);
void Contours_Callback(int, void*);
int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/kernel.png");
	if (src.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	namedWindow(srcImg, 1);
	namedWindow(dstImg, 1);
	imshow(srcImg, src);

	cvtColor(src, grayImg, CV_BGR2GRAY);
	blur(grayImg, grayImg, Size(3, 3), Point(-1, -1));

	const char* tBar = "threshold value:";
	createTrackbar(tBar, dstImg, &threshold_value, threshold_max, Contours_Callback);
	Contours_Callback(0, 0);

	waitKey(0);
	return 0;
}

void Contours_Callback(int, void*)
{
	Mat binary_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	threshold(grayImg, binary_output, threshold_value, threshold_max, THRESH_BINARY);
	imshow("binary image", binary_output);
	findContours(binary_output, contours, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(-1, -1));

	vector<vector<Point>> contours_ploy(contours.size());//ÂÖÀª³õÊ¼»¯
	vector<Rect> ploy_rects(contours.size());//¾ØÐÎ
	vector<Point2f> ccs(contours.size());//Ô²ÐÄ
	vector<float> radius(contours.size());//°ë¾¶

	vector<RotatedRect> minRects(contours.size());
	vector<RotatedRect> myellipse(contours.size());

	for (size_t i = 0; i < contours.size(); i++) {
		approxPolyDP(Mat(contours[i]), contours_ploy[i], 3, true);
		ploy_rects[i] = boundingRect(contours_ploy[i]);
		minEnclosingCircle(contours_ploy[i], ccs[i], radius[i]);
		if (contours_ploy[i].size() > 5) {
			minRects[i] = minAreaRect(contours_ploy[i]);
			myellipse[i] = fitEllipse(contours_ploy[i]);
		}
	}

	//»æÍ¼
	//src.copyTo(dst);ÔÚ²ÊÍ¼
	dst = Mat::zeros(src.size(), src.type());
	Point2f pts[4];
	for (size_t t = 0; t < contours.size(); t++) {
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		//rectangle(dst, ploy_rects[t], color, 2, 8);
		//circle(dst, ccs[t], radius[t], color, 2, 8);
		if (contours_ploy[t].size() > 5) {
			ellipse(dst, myellipse[t], color, 1, 8);
			minRects[t].points(pts);
			for (int r = 0; r < 4; r++) {
				line(dst, pts[r], pts[(r + 1) % 4], color, 1, 8);
			}
		}
	}

	imshow(dstImg, dst);
	return;
}