#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

int t1_value = 50;
int max_value = 255;
const char* outWin = "Canny image";
Mat src, grayImg, dst;
void Canny_Demo(int, void*);
int main(int agrc, char** agrv)
{

	src = imread("C:/Users/yefci/Desktop/lab/paste.png");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	char inWin[] = "input iamge";
	namedWindow(inWin, 1);
	namedWindow(outWin, 1);
	imshow(inWin, src);

	cvtColor(src, grayImg, CV_BGR2GRAY);
	createTrackbar("Threshold", outWin, &t1_value, max_value, Canny_Demo);
	Canny_Demo(0, 0);

	waitKey(0);
	return 0;
}

void Canny_Demo(int, void*)
{
	Mat edgeImg;
	blur(grayImg, grayImg, Size(3, 3), Point(-1, -1), BORDER_DEFAULT);
	Canny(grayImg, edgeImg, t1_value, t1_value * 2, 3, false);

	imshow("Canny-ºÚ°×", edgeImg);

	dst.create(src.size(), src.type());
	src.copyTo(dst, edgeImg);
	imshow(outWin, dst);
}