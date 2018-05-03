#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("C:/Users/yefci/Pictures/aditya-vyas-542857-unsplash.jpg",0);
	if (src.empty()) {
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("test opencv setup", CV_WINDOW_AUTOSIZE);//窗口大小自动
	imshow("test opencv setup", src);

	waitKey(0);
	return 0;
}
