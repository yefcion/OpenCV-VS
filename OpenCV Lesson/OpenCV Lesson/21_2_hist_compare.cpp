#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace cv;

string cvt2string(double d);//自建函数 compare的结果是double类型，要把它转换为字符串
int main(int agrc, char** agrv)
{
	Mat src, test1, test2;
	src = imread("C:/Users/yefci/Desktop/lab/sgaliGray.png");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	test1 = imread("C:/Users/yefci/Desktop/lab/sgali.jpg");
	test2 = imread("C:/Users/yefci/Desktop/lab/sgaliNoise.jpg");
	
	//转换色彩空间
	cvtColor(src, src, CV_BGR2HSV);
	cvtColor(test1, test1, CV_BGR2HSV);
	cvtColor(test2, test2, CV_BGR2HSV);

	int h_bins = 50;
	int s_bins = 60;
	int histSize[] = { h_bins,s_bins };

	//Hue色度 varies from 0 to179, Saturation饱和度 from 0 to 255
	float h_ranges[] = { 0,180 };
	float s_ranges[] = { 0,256 };
	const float* ranges[] = { h_ranges,s_ranges };
	//use the o-th and l-st channels
	int channels[] = { 0,1 };
	MatND hist_src;//多维图像
	MatND hist_test1;
	MatND hist_test2;

	calcHist(&src, 1, channels, Mat(), hist_src, 2, histSize, ranges, true, false);
	normalize(hist_src, hist_src, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
	normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

	calcHist(&test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
	normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());

	//互相比较
	double src_src = compareHist(hist_src, hist_src, CV_COMP_BHATTACHARYYA);
	double src_test1 = compareHist(hist_src, hist_test1, CV_COMP_BHATTACHARYYA);
	double src_test2 = compareHist(hist_src, hist_test2, CV_COMP_BHATTACHARYYA);
	double test1_test2 = compareHist(hist_test1, hist_test2, CV_COMP_BHATTACHARYYA);
	printf("test1 compare with test2 correlation value :%f", test1_test2);

	//添加文字：照片之间的相似度
	putText(src, cvt2string(src_src), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test1, cvt2string(src_test1), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(test2, cvt2string(src_test2), Point(50, 50), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);

	namedWindow("src", 1);
	namedWindow("test1", 1);
	namedWindow("test2", 1);

	imshow("src", src);
	imshow("test1", test1);
	imshow("test2", test2);

	waitKey(0);
	return 0;
}

string cvt2string(double d) 
{
	ostringstream os;
	if (os << d)
		return os.str();
	return "invalid conversion";
}