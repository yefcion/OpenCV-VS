#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main(int agrc, char** agrv)
{
	Mat src, grayImg, dst;
	src = imread("C:/Users/yefci/Desktop/lab/mix.png");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	char inWin[] = "input iamge";
	namedWindow(inWin, 1);
	imshow(inWin, src);

	Mat mediaImg;
	medianBlur(src, mediaImg, 7);//中值滤波
	cvtColor(mediaImg, mediaImg, CV_BGR2GRAY);//转为灰度

	Canny(src, dst, 100, 200);
	imshow("Canny", dst);

	//霍夫圆检测
	vector<Vec3f>pcircles;//定义圆
	HoughCircles(mediaImg, pcircles, CV_HOUGH_GRADIENT, 1, 10, 100, 18, 5, 50);//用霍夫变换获得可能的圆心坐标(0,1,2)形式
	src.copyTo(dst);//把原图像拷贝给目标图像
	for (size_t i = 0; i < pcircles.size(); i++) {
		Vec3f cc = pcircles[i];//circlr center坐标
		circle(dst, Point(cc[0], cc[1]), cc[2], Scalar(1, 1, 255), 2, LINE_AA);//绘制圆
		circle(dst, Point(cc[0], cc[1]), 1, Scalar(1, 1, 255), 0.5, LINE_AA);//绘制圆心
	}
	imshow("Hough Circle", dst);

	waitKey(0);
	return 0;
}