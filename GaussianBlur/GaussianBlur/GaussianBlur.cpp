/*
对图像而言，高频部分展现图像细节，所以低通滤波后图像模糊，称为高斯模糊；
相对，高通滤波滤掉低频，从而对图像进行锐化，图像更清晰，被称为高斯滤波。
高斯模糊是用高斯低通滤波器；
高斯滤波是指用高斯函数作为滤波函数的操作。
*/

#include<iostream>
#include<stdio.h>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

//定义全局变量
Mat src, dst;

//定义轨迹条最大值参量
const int g_nKwidthTrackBarMaxValue = 9;
const int g_nKheightTrackBarMaxValue = 9;
const int g_nsigmaXTrackBarMaxValue = 9;
const int g_nsigmaYTrackBarMaxValue = 9;

//定义轨迹条初始值
int g_nKwidthTrackBarValue = 1;
int g_nKheightTrackBarValue = 1;
int g_nsigmaXTrackBarValue = 1;
int g_nsigmaYTrackBarValue = 1;

int g_kernelWidthValue;
int g_kernelHeightValue;

void on_GaussianBlurTrackBar(int, void*);//定义回调函数

int main()
{
	src = imread("C:/Users/yefci/Desktop/lab/2.jpg");

	//判断图片是否加载成功
	if (!src.data)
	{
		cout << "图像加载失败！" << endl;
		return -1;
	}
	else
		cout << "图像加载成功!" << endl;

	namedWindow("原图", WINDOW_NORMAL);//可调节图像大小
	imshow("原图", src);

	namedWindow("高斯滤波图像", WINDOW_NORMAL);

	//定义每条轨迹名称
	char widthTrackBarName[20];
	printf(widthTrackBarName, "width %d", g_nKwidthTrackBarMaxValue);
	char heightTrackBarName[20];
	printf(heightTrackBarName, "height %d", g_nKheightTrackBarMaxValue);
	char sigmaXTrackBarName[20];
	printf(sigmaXTrackBarName, "sigX %d", g_nsigmaXTrackBarMaxValue);
	char sigmaYTrackBarName[20];
	printf(sigmaYTrackBarName, "sigY %d", g_nsigmaYTrackBarMaxValue);

	//创建轨迹条
	createTrackbar(widthTrackBarName, "高斯滤波图像", &g_nKwidthTrackBarValue, g_nKwidthTrackBarMaxValue, on_GaussianBlurTrackBar);
	createTrackbar(heightTrackBarName, "高斯滤波图像", &g_nKheightTrackBarValue, g_nKheightTrackBarMaxValue, on_GaussianBlurTrackBar);
	createTrackbar(sigmaXTrackBarName, "高斯滤波图像", &g_nsigmaXTrackBarValue, g_nsigmaXTrackBarMaxValue, on_GaussianBlurTrackBar);
	createTrackbar(sigmaYTrackBarName, "高斯滤波图像", &g_nsigmaYTrackBarValue, g_nsigmaYTrackBarMaxValue, on_GaussianBlurTrackBar);


	waitKey(0);
	return 0;
}

void on_GaussianBlurTrackBar(int, void*)
{
	//根据输入的width和height重新计算ksize.width和ksize.height
	g_kernelWidthValue = g_nKwidthTrackBarValue * 2 + 1;
	g_kernelHeightValue = g_nKheightTrackBarValue * 2 + 1;

	//高斯滤波
	GaussianBlur(src, dst, Size(g_kernelWidthValue, g_kernelHeightValue), g_nsigmaXTrackBarValue, g_nsigmaYTrackBarValue);

	imshow("高斯滤波图像", dst);
}