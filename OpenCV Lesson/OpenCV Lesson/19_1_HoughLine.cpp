#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int main(int agrc, char** agrv)
{
	Mat src, grayImg, dst;
	src = imread("C:/Users/yefci/Desktop/lab/lines.png");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	char inWin[] = "input iamge";
	namedWindow(inWin, 1);
	imshow(inWin, src);

	//extract edge
	Canny(src, grayImg, 100, 200);//Canny算法做边缘检测
	cvtColor(grayImg, dst, CV_GRAY2BGR);
	imshow("Canny", dst);

	vector<Vec4f> plines;//定义一条直线
	HoughLinesP(grayImg, plines, 1, CV_PI / 180.0, 10, 0, 5);//最后一个参数反锯齿
	Scalar color = Scalar(140, 60, 200);
	for (size_t i = 0; i < plines.size(); i++) {
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 3, LINE_AA);
	}
	imshow("Hough Lines P", dst);

	waitKey(0);
	return 0;
}