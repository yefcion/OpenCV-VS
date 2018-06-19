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

	Mat grayImg;
	cvtColor(src, grayImg, CV_BGR2GRAY);
	imshow("gray", grayImg);

	Mat binImg;
	adaptiveThreshold(~grayImg, binImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -2);
	//注意此处 ~ 意为取反，既翻转颜色再做二值化操作，有好的效果
	imshow("binary", binImg);

	//水平线
	Mat xline = getStructuringElement(MORPH_RECT, Size(src.cols / 16, 1), Point(-1, -1));
	//垂直线
	Mat yline = getStructuringElement(MORPH_RECT, Size(1, src.rows / 16), Point(-1, -1));
	//矩形
	Mat rect = getStructuringElement(MORPH_RECT, Size(4,4));//调整size可以改善效果

	morphologyEx(binImg, dst, CV_MOP_OPEN, xline);
	bitwise_not(dst, dst);//反转背景颜色
	blur(dst, dst, Size(3, 3), Point(-1, -1));//模糊操作，使图像更圆润，从而遮掩瑕疵
	imshow("xline", dst);
	
	morphologyEx(binImg, dst, CV_MOP_OPEN, yline);
	bitwise_not(dst, dst);
	blur(dst, dst, Size(3, 3), Point(-1, -1));
	imshow("yline", dst);

	morphologyEx(binImg, dst, CV_MOP_OPEN, rect);
	bitwise_not(dst, dst);
	imshow("rectangle", dst);//最终达到了只保留字母的效果
	//可以实现复杂验证码中字母的提取


	waitKey(0);
	return 0;
}