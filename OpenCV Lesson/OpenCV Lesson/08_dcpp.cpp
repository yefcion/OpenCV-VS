#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src, dst, dst2;
	src = imread("C:/Users/yefci/Pictures/Camera Roll/长歌行2.jpg");
	if (!src.data) {
		printf("could not load image");
		return -1;
	}
	char srcN[] = "input image";
	namedWindow(srcN, 1);
	imshow(srcN, src);

	medianBlur(src, dst, 3);//中值滤波去除椒盐噪声
	char dstN[] = "中值滤波";
	namedWindow(dstN, 1);
	imshow(dstN, dst);

	bilateralFilter(src, dst2, 15, 150, 3);//双边滤波保留边缘信息
	imshow("双边滤波", dst2);

	Mat gblur;
	GaussianBlur(src, gblur, Size(15, 15), 3, 3);
	imshow("高斯模糊", gblur);

	Mat F2D;
	Mat kernel = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(gblur, F2D, -1, kernel, Point(-1, -1), 0);
	imshow("对比度增强", F2D);

	waitKey(0);
	return 0;
}