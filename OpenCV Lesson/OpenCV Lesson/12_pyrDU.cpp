#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst;

int main(int argc, char** argv)
{
	src = imread("C:/Users/yefci/Desktop/lab/lines.png");
	if (!src.data) {
		printf("could not load image");
		return -1;
	}
	char inTitle[] = "input image";
	namedWindow(inTitle, 1);
	imshow(inTitle, src);
	//降采样、上采样
	pyrDown(src, dst, Size(src.cols / 2, src.rows / 2));
	imshow("降采样", dst);
	pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	imshow("上采样", dst);

	//DOG
	Mat grayImg, g1, g2;
	cvtColor(src, grayImg, CV_BGR2GRAY);//转灰度图
	GaussianBlur(src, g1, Size(3, 3), 0, 0);//第一层高斯
	GaussianBlur(g1, g2, Size(3, 3), 0, 0);//第二层高斯
	subtract(g1, g2, src, Mat());
	
	//归一化显示
	normalize(src, src, 255, 0, NORM_MINMAX);
	imshow("DOG Image", src);

	waitKey(0);
	return 0;
}