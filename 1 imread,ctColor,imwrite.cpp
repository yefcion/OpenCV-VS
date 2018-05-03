/*
	加载 cv::imread
	修改 cv::ctColor
	保存 cv::imwrite

1.1 加载图像(用cv::imread)
	imread功能是加载图像文件成为一个Mat对象,其中
	第一个参数表示图像文件名称
	第二个参数,表示加载的图像是什么类型,支持常见的三个参数值:
		IMREAD_UNCHANGED 或者 (<0) 表示加载原图,不做任何改变
		IMREAD_GRAYSCALE 或者 (0) 表示把原图作为灰度图像加载进来
		IMREAD_COLOR 或者 (>0) 表示把原图作为RGB图像加载进来
注意:OpenCV支持JPG、PNG、TIFF等常见格式图像文件加载
*/

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
/*
显示图像(cv::namedWindos 与 cv::imshow )
	namedwindos功能是创建一个OpenCV窗口,它是由OpenCV自动创建与释放,无需销毁。
		常见用法 namedWindow(“Window Title”,WINDOW_AUTOSIZE)
			WINDOW_AUTOSIZE 会自动根据图像大小,显示窗口大小,不能人为改变窗口大小
			WINDOW_NORMAL 跟QT集成的时候会使用,允许修改窗口大小。
	imshow根据窗口名称显示图像到指定的窗口上去,第一个参数是窗口名称,第二参数是Mat对象
*/

/*
--------------------------------------------------------------------------------------------

1.2 修改图像(cv::cvtColor)
	cvtColor的功能是把图像从一个彩色空间转换到另外一个色彩空间,有三个参数:
		第一个参数表示源图像
		第二参数表示色彩空间转换之后的图像
		第三个参数表示源和目标色彩空间如:COLOR_BGR2HLS、COLOR_BGR2GRAY等
	cvtColor(image,gray_image,COLOR_BGR2GRAY);
*/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImg = imread("C:/Users/yefci/Pictures/aditya-vyas-542857-unsplash.jpg");
	if (srcImg.empty()) {
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("test opencv setup", CV_WINDOW_AUTOSIZE);//创建一个可以自动销毁的窗口,窗口大小自动
	imshow("test opencv setup", srcImg);

	namedWindow("output windows", CV_WINDOW_AUTOSIZE);//创建另一个可以自动销毁的窗口,
	Mat dstImg;
	cvtColor(srcImg, dstImg, CV_BGR2GRAY);//CV_BGR2GRAY 从BGR转为灰度
	imshow("output windows", dstImg);

	waitKey(0);
	return 0;
}

/*
----------------------------------------------------------------------------------------------

1.3 保存图像(cv:imwrite)
	保存图像文件到指定目录路径
	只有8位、16位的PNG、JPG、Tiff文件格式而且是单通道或者三通道的BGR的图像才可以通过这种方式保存
	保存PNG格式的时候可以保存透明通道的图片
	可以指定压缩参数
*/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImg = imread("C:/Users/yefci/Pictures/aditya-vyas-542857-unsplash.jpg");
	if (srcImg.empty()) {
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("test opencv setup", CV_WINDOW_AUTOSIZE);//创建一个可以自动销毁的窗口,窗口大小自动
	imshow("test opencv setup", srcImg);

	namedWindow("output windows", CV_WINDOW_AUTOSIZE);
	Mat dstImg;
	cvtColor(srcImg, dstImg, CV_BGR2HLS);
	imshow("output windows", dstImg);

	imwrite("C:/Users/yefci/Desktop/lab/1.jpg", dstImg);
	waitKey(0);
	return 0;
}
