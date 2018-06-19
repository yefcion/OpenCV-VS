#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst;
int element_size = 3;//默认膨胀/腐蚀程度
int max_size = 21;
void CallBack_Demo(int, void*);//回调函数，是一个通过函数指针调用的函数。

int main(int argc, char** argv)
{
	src = imread("C:/Users/yefci/Pictures/2.jpg");
	if (!src.data) {
		printf("could not load image");
		return -1;
	}
	namedWindow("input image", 1);
	imshow("input image", src);

	namedWindow("output image", 1);
	createTrackbar("Element Size:", "output image", &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0, 0);

	waitKey(0);
	return 0;
}
void CallBack_Demo(int, void*)
{
	int s = element_size * 2 + 1;
	Mat strctureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	//dilate(src, dst, strctureElement, Point(-1, -1), 1);
	erode(src, dst, strctureElement);
	imshow("output image", dst);
}