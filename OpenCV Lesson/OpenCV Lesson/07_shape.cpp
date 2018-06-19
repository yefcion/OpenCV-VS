#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat bgImg;
const char* dravdemo_win = "draw shapes and text demo";//这句话干嘛的
void MyLines();
void MyRectangle();
void MyEllipse();
void MyCircle();
void MyPloygon();
void RandomLineDemo();
int main(int argc, char** argv) 
{
	bgImg = imread("C:/Users/yefci/Pictures/Camera Roll/长歌行.jpg");
	if (!bgImg.data) {
		printf("could not load image");
		return -1;
	}

	//程序调用部分
	/*MyLines();
	MyRectangle();//记得要在前面声明下函数，不然会出现找不到标识符报错
	MyEllipse();
	MyCircle();
	MyPloygon();
	
	putText(bgImg, "Hello OpenCV", Point(300, 200), CV_FONT_BLACK, 2.0, Scalar(50, 60, 255), 1, 8);

	namedWindow("lines", 1);
	imshow("lines", bgImg);*/

	RandomLineDemo();

	waitKey(0);
	return 0;
}

//程序定义部分
//画线
void MyLines()
{
	Point p1 = Point(20, 30);//一种定义方式
	Point p2;
	p2.x = 90;
	p2.y = 90;//另一种定义方式
	Scalar color = Scalar(0, 0, 255);//定义color向量，用于表示颜色
	line(bgImg, p1, p2, color, 9, LINE_8);//线宽为9
}
//画矩形
void MyRectangle()
{
	Rect rect = Rect(200, 100, 90, 90);//x,y,width,height
	Scalar color = Scalar(255, 0, 0);//Blue
	rectangle(bgImg, rect, color, 8, LINE_8);
}
//画椭圆
void MyEllipse()
{
	Point Epoint = Point(bgImg.cols / 2, bgImg.rows / 2);//圆心x,y
	Size Esize = Size(bgImg.cols / 4, bgImg.rows / 8);//x,y轴半径
	Scalar color = Scalar(0, 255, 0);
	int degree = 90;//圆整体呈现的角度
	int starD = 0;//圆的起始位置度数
	int endD = 360;//圆的终止位置度数
	int Lwidth = 2;//线宽
	ellipse(bgImg, Epoint, Esize, degree, starD, endD, color, Lwidth, LINE_8);
}
//画圆
void MyCircle()
{
	Point center = Point(bgImg.cols / 2, bgImg.rows / 2);//圆心x,y
	int radius = 150;//半径
	Scalar color = Scalar(0, 255, 255);
	circle(bgImg, center, radius, color, 2, 8);//注意这里的LINE_8可以直接写成8
}
//填充多边形
void MyPloygon()
{
	Point pts[1][6];
	pts[0][0] = Point(130, 122);
	pts[0][1] = Point(146, 122);
	pts[0][2] = Point(146, 145);
	pts[0][3] = Point(125, 146);
	pts[0][4] = Point(126, 139);
	pts[0][5] = Point(120, 131);

	const Point* ppts[1] = { pts[0] };//定义一个指针，指向二维数组的第0个位置
	int npt[] = { 6 };//声明共有6个点
	Scalar color = Scalar(99, 100, 255);

	fillPoly(bgImg, ppts, npt, 1, color, 8);//这里的1，是指轮廓的数量
}
//画随机线
void RandomLineDemo()
{
	RNG rng(12345);
	Point pt1;
	Point pt2;
	Mat bg = Mat::zeros(bgImg.size(), bgImg.type());
	namedWindow("random line", 1);
	for (int i = 0; i < 10000; i++) {
		pt1.x = rng.uniform(0, bgImg.cols);//随机函数
		pt1.y = rng.uniform(0, bgImg.cols);
		pt2.x = rng.uniform(0, bgImg.cols);
		pt2.y = rng.uniform(0, bgImg.cols);
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		if (waitKey(50) > 0) {//等待50s
			break;
		}
		line(bg, pt1, pt2, color, 1, 8);
		imshow("random line", bg);
	}
}
