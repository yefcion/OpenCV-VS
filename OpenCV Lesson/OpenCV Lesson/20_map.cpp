#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

using namespace std;
using namespace cv;

Mat src, dst, map_x, map_y;
const char* outWin = "remap Demo";
int index = 0;
void update_map(void);
int main(int agrc, char** agrv)
{
	src = imread("C:/Users/yefci/Desktop/lab/kernel.png");
	if (!src.data) {
		cout << "could not load image" << endl;
		return -1;
	}
	char inWin[] = "input iamge";
	namedWindow(inWin, 1);
	imshow(inWin, src);

	map_x.create(src.size(), CV_32FC1);//创建映射
	map_y.create(src.size(), CV_32FC1);//32位单通道

	int c = 0;
	while (true) {
		c = waitKey(500);
		if ((char)c == 27) {
			break;
		}
		index = c % 4;
		update_map();
		remap(src, dst, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 255));
		imshow(outWin, dst);
	}

	return 0;
}

void update_map(void) {
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			switch (index)//语句从index所指向的数字开始执行
			{
			case 0:
				if (col > (src.cols*0.25) && col <= (src.cols*0.75) && row > (src.rows*0.25) && row <= (src.rows*0.75))
				{//原图的一半
					map_x.at<float>(row, col) = 2 * (col - (src.cols*0.25));
					map_y.at<float>(row, col) = 2 * (row - (src.rows*0.25))-0.5;
				}
				else {//超出部分为0
					map_x.at<float>(row, col) = 0;
					map_y.at<float>(row, col) = 0;
				}
				break;
			case 1://水平翻转
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = row;
				break;
			case 2://竖直翻转
				map_x.at<float>(row, col) = col;
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			case 3://水平竖直都翻转
				map_x.at<float>(row, col) = (src.cols - col - 1);
				map_y.at<float>(row, col) = (src.rows - row - 1);
				break;
			default:
				break;
			}
		}
	}
}