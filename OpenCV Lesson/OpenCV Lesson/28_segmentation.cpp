#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

int main(int agrc, char** agrv)
{
	char srcImg[] = "input image";
	char watersheldWin[] = "watershed segmentation demo";

	//load image
	Mat src = imread("C:/Users/yefci/Desktop/lab/poke.png");
	if (src.empty()) {
		cout << "could not load image" << endl;
		return -1;
	}
	namedWindow(srcImg, 1);
	imshow(srcImg, src);

	//1. change background
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255)) {//如果坐标为(x,y)的点 颜色为白色
				//则将它的3个颜色值分别改为0
				src.at<Vec3b>(row, col)[0] = 0;
				src.at<Vec3b>(row, col)[1] = 0;
				src.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	imshow("black bakgroud", src);
	
	//2. sharpe
	Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	Mat imgLaplance;
	Mat sharpenImg = src;
	filter2D(src, imgLaplance, CV_32F, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
	src.convertTo(sharpenImg, CV_32F);
	Mat resultImg = sharpenImg - imgLaplance;

	resultImg.convertTo(resultImg, CV_8UC3);
	imgLaplance.convertTo(imgLaplance, CV_8UC3);
	imshow("sharp image", resultImg);

	//3. convert to binary iamge
	Mat binaryImg;
	cvtColor(src, binaryImg, CV_BGR2GRAY);
	threshold(binaryImg, binaryImg, 40, 255, THRESH_BINARY | THRESH_OTSU);
	imshow("binary image", binaryImg);

	//4. distance transform
	Mat distImg;
	distanceTransform(binaryImg, distImg, CV_DIST_L2, 3);
	//5. normalize
	normalize(distImg, distImg, 0, 1, NORM_MINMAX);
	imshow("distance image", distImg);

	//6.binary again with threshold 
	threshold(distImg, distImg, 0.4, 1, THRESH_BINARY);
	//7. erode to get peaks
	Mat kernel_1 = Mat::ones(13, 13, CV_8UC1);
	erode(distImg, distImg, kernel_1);
	imshow("peaks image", distImg);
	
	//8. try to get marker
	Mat dist_8u;
	distImg.convertTo(dist_8u, CV_8U);
	vector<vector<Point>> contours;
	findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));// findContours

	Mat markers = Mat::zeros(src.size(), CV_32SC1);//create makers
	for (size_t i = 0; i < contours.size(); i++) {
		drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1),-1);//drawContours
	}
	circle(markers, Point(5, 5), 3, Scalar(255, 255, 255), -1);
	imshow("markers image",markers*1000);//markers灰度级别很低，*1000
	
	//9. watershed
	watershed(src, markers);

	Mat mark = Mat::zeros(markers.size(), CV_8UC1);
	markers.convertTo(mark, CV_8UC1);
	bitwise_not(mark, mark);
	imshow("watershed marks", mark);

	//10. generate random color
	vector<Vec3b> colors;
	for (size_t i = 0; i < contours.size(); i++) {
		int r = theRNG().uniform(0, 255);
		int g = theRNG().uniform(0, 255);
		int b = theRNG().uniform(0, 255);
		colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
	}

	//fill with color and display final result
	Mat dst = Mat::zeros(markers.size(), CV_8UC3);
	for (int row = 0; row < markers.rows; row++) {
		for (int col = 0; col < markers.cols; col++) {
			int index = markers.at<int>(row, col);
			if (index > 0 && index <= static_cast<int>(contours.size())) {
				dst.at<Vec3b>(row, col) = colors[index - 1];
			}
			else {
				dst.at<Vec3b>(row, col) = Vec3b(0, 0, 0);
			}
		}
	}

	imshow("Final show", dst);
	waitKey(0);
	return 0;
}