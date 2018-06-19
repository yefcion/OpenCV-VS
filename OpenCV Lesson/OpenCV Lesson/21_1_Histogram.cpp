#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main(int agrc, char** agrv)
{
	Mat src, dst;
	src = imread("C:/Users/yefci/Desktop/lab/sgali.jpg");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	char inWin[] = "input iamge";
	namedWindow(inWin, 1);
	imshow(inWin, src);
	
//对图像做直方图操作
	cvtColor(src, dst, CV_BGR2GRAY);
	equalizeHist(dst, dst);
	imshow("histogram", dst);


//计算图像的直方图
	//定义数组,用于分通道显示
	vector<Mat>bgr_planes;
	split(src, bgr_planes);//分成3个不同的通道
	imshow("single channel", bgr_planes[0]);
	
	int histSize = 255;//定义变量，作为直方图纵轴最大值
	float range[] = { 0,256 };//定义浮点数数组
	const float *histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRanges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRanges, true, false);
	//归一化
	int hist_h = 400;
	int hist_w = 512;
	int bin_w = hist_w / histSize;
	Mat histImg(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	//绘制直方图
	for (int i = 1; i < histSize; i++) {
		line(histImg, Point((i - 1)*bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))), 
			Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, LINE_AA);
		line(histImg, Point((i - 1)*bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, LINE_AA);
		line(histImg, Point((i - 1)*bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, LINE_AA);
	}
	imshow("hist image", histImg);

	waitKey(0);
	return 0;
}