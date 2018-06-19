#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, dst;

int main(int agrc, char* agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/anni.jpg");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	//图像显示
	char srcImg[] = "input image";
	namedWindow(srcImg, 1);
	imshow(srcImg, src);
	
	//图像腐蚀
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3), Point(-1, -1));
	erode(src, dst, element);
	imshow("erode image", dst);

	//图像模糊
	blur(src, dst, Size(3, 3), Point(-1, -1), 4);
	imshow("blur image", dst);

	//canny边缘检测
	cvtColor(src, dst, CV_BGR2GRAY);//1 先转灰度
	blur(dst, dst, Size(3, 3));//2 再降噪（默认值可省略）
	Canny(dst, dst, 3, 9, 3);//3 边缘检测
	imshow("canny image", dst);
	/*
	//读取并播放视频
	VideoCapture capture("C:/Users/yefci/Desktop/lab/1.avi");//实例化一个VideoCapture类的对象，读取视频
	while (true)
	{
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;  //读取当前帧

		//若视频播放完成，退出循环
		if (frame.empty())
		{
			break;
		}

		imshow("读取视频", frame);  //显示当前帧
		waitKey(30);  //延时30ms
	}*/

	//调用摄像头采集图像
	VideoCapture capture2(0);//从摄像头读入视频
	//循环显示每一帧
	while (1)
	{
		Mat frame;  //定义一个Mat变量，用于存储每一帧的图像
		capture2 >> frame;  //读取当前帧
		imshow("摄像头视频", frame);  //显示当前帧
		waitKey(30);  //延时30ms
	}
	waitKey(0);
	return 0;
}