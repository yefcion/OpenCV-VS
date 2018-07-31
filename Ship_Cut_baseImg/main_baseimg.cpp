#include<iostream>
#include<windows.h>
#include <list>
#include <fstream>
#include <sstream>
#include <io.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

/********************************************************************************************************************/
/*													*/
/*		函数名		:	统计白点数									英名 :bSums										*/
/*													*/
/*		概要		:	统计二值图中，白点个数																		*/
/*													*/
/*		入参		:	Mat src										数组中有几个1									*/
/*		出参		:	无																							*/
/*													*/
/*		返回值		:	counter						*/
/*													*/
/********************************************************************************************************************/
int bSums( Mat src )
{
	int counter = 0;
	//迭代器访问像素点
	Mat_<uchar>::iterator it = src.begin<uchar>( );
	Mat_<uchar>::iterator itend = src.end<uchar>( );
	for ( ; it != itend; ++it )
	{
		if ( (*it) > 0 ) counter += 1;//二值化后，像素点是0或者255
	}
	return counter;
}

int main( int argc, char* argv[] )
{
	Mat img, frame_gray, roi;
	Mat edge_x, bw_edge_x, edge_y, bw_edge_y;
	int counter_b_x, counter_b_y;
	string label;

	VideoCapture capture;
	Mat frame;
	frame = capture.open( "G:/杨庄船闸下游闸门/视频/ship_in_open.avi" );

	namedWindow( "output", CV_WINDOW_NORMAL );

	while ( capture.read( frame ) )
	{

		//读图，灰度化，取roi
		cvtColor( frame, frame_gray, CV_BGR2GRAY );
		roi = frame_gray( Rect( 1275, 560, 20, 90 ) );
		//中值滤波，方便后续边缘检测
		medianBlur( roi, roi, 9 );
		//检测垂直边缘，并将边缘图转成二值图，统计二值图的白点个数
		//该值可以理解成垂直边缘值
		Sobel( roi, edge_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
		convertScaleAbs( edge_x, edge_x );
		threshold( edge_x, bw_edge_x, 0, 255, CV_THRESH_OTSU );
		counter_b_x = bSums( bw_edge_x );
		//检测水平边缘，并将边缘图转成二值图，统计二值图的白点个数
		//该值可以理解成水平边缘值
		Sobel( roi, edge_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
		convertScaleAbs( edge_y, edge_y );
		threshold( edge_y, bw_edge_y, 0, 255, CV_THRESH_OTSU );
		counter_b_y = bSums( bw_edge_y );

		if ( counter_b_x > 185 && counter_b_y < 20 )
		{
			label = "CLOSE";
		}
		else
		{
			label = "OPEN";
		}

		//加边框
		Rect rect = Rect( 1275, 560, 20, 90 );//x,y,width,height
		Scalar color = Scalar( 240, 180, 110 );//Blue
		rectangle( frame, rect, color, 2, LINE_8 );

		//加文字
		putText( frame, label, Point( 1200, 550 ), CV_FONT_HERSHEY_COMPLEX, 2, Scalar( 0, 0, 255 ), 2, LINE_AA );

		imshow( "output", frame );
		waitKey( 10 );
	}

	return 0;
}
