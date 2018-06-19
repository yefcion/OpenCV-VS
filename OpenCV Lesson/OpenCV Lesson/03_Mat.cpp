#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src;
	src = imread("C:/Users/yefci/Pictures/girl.png");
	if (src.empty()) {
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	//创建一张空白图像
	/*Mat dst;
	dst = Mat(src.size(), src.type());
	dst = Scalar(127, 0, 255);
	namedWindow("1.空白", CV_WINDOW_AUTOSIZE);
	imshow("1.空白", dst);*/

	//克隆
	/*Mat dst = src.clone();
	namedWindow("2.克隆", CV_WINDOW_AUTOSIZE);
	imshow("2.克隆", dst);*/

	//拷贝
	/*Mat dst;
	src.copyTo(dst);
	namedWindow("3.拷贝", CV_WINDOW_AUTOSIZE);
	imshow("3.拷贝", dst);*/

	//查看参数
	Mat dst;
	namedWindow("4.参数", CV_WINDOW_AUTOSIZE);
	cvtColor(src, dst, CV_BGR2GRAY);
	printf("srcImg channels : %d\n", src.channels());
	printf("dstImg channels : %d\n", dst.channels());
	imshow("4.参数", dst);

	int cols = dst.cols;
	int rows = dst.rows;
	cout << cols << " " << rows << endl;
	const uchar* firstRow = dst.ptr<uchar>(0);//第一个像素值
	printf("first pixel value : %d\n", *firstRow);
	
	//创建新的图像
	Mat M(700, 700, CV_8UC3,Scalar(0, 0, 255));
	//cout << "M= :" << endl << M << endl;
	imshow("max",M);

	Mat G;
	G.create(4, 3, CV_8UC2);
	G = Scalar(127, 127);
	cout << "G = " << endl << " " << G << endl << endl;
	uchar* firsRow = G.ptr<uchar>(0);
	printf("%d\n", *firsRow);

	Mat H = Mat::zeros(5,5, CV_8UC3);//初始化为0
	Mat J = Mat::eye(5, 5, CV_8UC3);//对角线为1，其他为0
	cout << "H = " << endl << " " << H << endl << endl;
	cout << "J = " << endl << " " << J << endl << endl;

	waitKey(0);
	return 0;
}