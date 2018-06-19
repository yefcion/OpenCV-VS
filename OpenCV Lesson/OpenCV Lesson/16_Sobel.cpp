#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat src, dst;
int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/paste.png");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	char inWin[] = "input image";
	namedWindow(inWin, 1);
	imshow(inWin, src);

	Mat grayImg;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	cvtColor(dst, grayImg, CV_BGR2GRAY);
	imshow("gray image", grayImg);

	Mat xgrad, ygrad;
	//Scharr(grayImg, xgrad, CV_16S, 1, 0, 3);
	//Scharr(grayImg, ygrad, CV_16S, 0, 1, 3);
	Sobel(grayImg, xgrad, CV_16S, 1, 0, 3);
	Sobel(grayImg, ygrad, CV_16S, 0, 1, 3);
	convertScaleAbs(xgrad, xgrad);//负值变正
	convertScaleAbs(ygrad, ygrad);
	imshow("xgrad", xgrad);
	imshow("ygrad", ygrad);

	Mat grad;
	addWeighted(xgrad, 0.5, ygrad, 0.5, 0, grad);
	imshow("addWeighted", grad);

	Mat Grad = Mat(xgrad.size(), xgrad.type());
	printf("type:%d", xgrad.type());
	int width = xgrad.cols;
	int height = ygrad.rows;
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int xg = xgrad.at<uchar>(row, col);
			int yg = ygrad.at<uchar>(row, col);
			int xy = xg + yg;
			Grad.at<uchar>(row, col) = saturate_cast<uchar>(xy);
		}
	}
	imshow("final show", Grad);

	waitKey(0);
	return 0;
}