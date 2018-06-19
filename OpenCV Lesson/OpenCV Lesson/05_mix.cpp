#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat src1, src2, dst, dst_add , dst_mul;
	src1 = imread("C:/Users/yefci/Desktop/lab/qrcode.jpg");
	src2 = imread("C:/Users/yefci/Desktop/lab/qrcode2.jpg");

	if (!src1.data) {//检测图片是否为空
		printf("Could not load Logo image 1...");
		return -1;
	}
	if (!src1.data) {
		printf("Could not load Logo image 2...");
		return -1;
	}

	if (src1.rows == src2.rows&&src1.cols == src2.cols&& src1.type() == src2.type()) {//确保两张图片尺寸、类型相同，这是addWeighted的前提
		double alpha = 0.5;
		addWeighted(src1, alpha, src2, (1 - alpha), 0.0, dst);//addWeighted,gamma值默认为0
		add(src1, src2, dst_add, Mat());//add 直接相加，没有权重没有矫正
		multiply(src1, src2, dst_mul, 1.0);//multiply 直接相加，没有权重没有矫正
		imshow("s1", src1);
		imshow("s2", src2);
		namedWindow("line-blend", CV_WINDOW_AUTOSIZE);
		imshow("line-blend", dst);
		imshow("line add", dst_add);
		imshow("line mul", dst_mul);
		waitKey(0);
		return 0;
	}
	else
	{
		printf("image size is not same...\n");
		return -1;
	}
}