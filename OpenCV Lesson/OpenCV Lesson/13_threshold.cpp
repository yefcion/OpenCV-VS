#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, grayImg, dst;
int threshold_value = 127;//阈值
int threshold_max = 255;//阈值的最大值
int type_value = 2;
int type_max = 4;
const char*output_title = "binary image";
void Threshold_Demo(int, void*);

int main(int argc, char** argv)
{
	src = imread("C:/Users/yefci/Desktop/lab/xiu.png");
	if (!src.data) {
		printf("could not load image");
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	createTrackbar("Threshold Value", output_title, &threshold_value, threshold_max, Threshold_Demo);
	createTrackbar("Type Value", output_title, &type_value, type_max, Threshold_Demo);
	Threshold_Demo(0, 0);

	waitKey(0);
	return 0;
}

void Threshold_Demo(int, void*)
{
	cvtColor(src, grayImg, CV_BGR2GRAY);
	//threshold(grayImg, dst, threshold_value, threshold_max, type_value);//此处type_value的值对应不同的阈值类型
	//上述操作是手动输入的阈值，下面方法可以由系统自动计算阈值
	threshold(grayImg, dst, 0, 255, THRESH_OTSU | type_value);//还有一个THRESH_TRIANGLE
	imshow(output_title, dst);
}