#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

Mat src, hsv, hue;
int bins = 12;//每根柱的宽度
void Hist_And_Backprojection(int, void*);

int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/安妮.jpg");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	const char* window_image = "input image";//定义常量变量
	namedWindow(window_image, 1);

	cvtColor(src, hsv, CV_BGR2HSV);//转色彩空间
	hue.create(hsv.size(), hsv.depth());//创建新的图片
	int nchannels[] = { 0,0 };//const int* fromTo
	mixChannels(&hsv, 1, &hue, 1, nchannels, 1);

	createTrackbar("Histogram Bins:", window_image, &bins, 180, Hist_And_Backprojection);
	Hist_And_Backprojection(0, 0);//0可以代表everything
	
	imshow(window_image, src);
	waitKey(0);
	return 0;
}
void Hist_And_Backprojection(int, void*)
{
	float range[] = { 0,180 };
	const float *histRanges = { range };
	Mat h_hist;
	calcHist(&hue, 1, 0, Mat(), h_hist, 1, &bins, &histRanges, true, false);
	normalize(h_hist, h_hist, 0, 255, NORM_MINMAX, -1, Mat());

	Mat backPrjImg;
	calcBackProject(&hue, 1, 0, h_hist, backPrjImg, &histRanges, 1, true);
	imshow("BackPrj", backPrjImg);

	int hist_h = 400;
	int hist_w = 400;
	Mat histImg(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	int bin_w = (hist_w / bins);
	for (int i = 1; i < bins; i++) {
		rectangle(
			histImg,
			Point((i - 1)*bin_w, (hist_h - cvRound(h_hist.at<float>(i - 1)*(400 / 255)))),
			//Point(i*bin_w, (hist_h - cvRound(h_hist.at<float>(i)*(400 / 255)))),
			Point(i*bin_w, hist_h),
			Scalar(0, 0, 255),-1);
	}
	imshow("Histgram", histImg);
	return;
}