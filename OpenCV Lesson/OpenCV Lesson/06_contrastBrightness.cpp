#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

double alpha; /** < Simple contrast control */
int beta;     /** < Simple brightness control */

int main(int argc, char** argv)
{
	Mat src, dst;
	// 加载图像
	src = imread("C:/Users/yefci/Desktop/lab/qrcode2.jpg");

	if (!src.data) {//检测图片是否为空
		printf("Could not load Logo image 1...");
		return -1;
	}

	// 目标图像空间预分配
	dst = Mat::zeros(src.size(), src.type());

	/// 输入初始化值
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << " *Enter the alpha value [1.0-3.0]: ";
	cin >> alpha;
	cout << " *Enter the beta value [0-100]: ";
	cin >> beta;

	//Mat m1;
	//src.convertTo(m1, CV_32F);//如果这里改了，先面就可以用Vec3f 了

	// 执行变换 dst(i,j) = alpha * src(i,j) + beta
	for (int row = 0; row < src.rows; row++) 
	{
		for (int col = 0; col < src.cols; col++) 
		{
			if (src.channels() == 3) 
			{
				for (int c = 0; c < 3; c++)
				{
					float v = src.at<Vec3b>(row, col)[c];//由于这张图片是8U，所以这里不能用Vec3f
					dst.at<Vec3b>(row, col)[c] = saturate_cast<uchar>(v*alpha + beta);
				}
			}
			else if (src.channels() == 1) 
			{
				float v = src.at<uchar>(row, col);//函数 at()来实现读取矩阵中的某个像素
				dst.at<uchar>(row, col) = saturate_cast<uchar>(v*alpha + beta);
			}
		}
	}
	// 创建显示窗口
	char srcName[] = "input image";
	char output[] = "contrast and brightness change demo";
	namedWindow(srcName, CV_WINDOW_AUTOSIZE);
	namedWindow(output, 1);
	// 显示图像
	imshow(srcName, src);
	imshow(output, dst);
	// 等待键盘事件
	waitKey(0);
	return 0;
}