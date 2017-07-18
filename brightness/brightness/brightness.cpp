#include "opencv2/core/core.hpp"  
#include"opencv2/highgui/highgui.hpp"  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <omp.h>
using namespace cv;
void brightnessException(Mat InputImg, float& cast, float& da)
{

	Mat GRAYimg;
	cvtColor(InputImg, GRAYimg, CV_BGR2GRAY);
	float a = 0;
	int Hist[256];
#pragma omp parallel for
	for (int i = 0; i < 256; i++)
		Hist[i] = 0;
#pragma omp parallel for

	for (int i = 0; i < GRAYimg.rows; i++)
	{
#pragma omp parallel for
		for (int j = 0; j < GRAYimg.cols; j++)
		{

			a += float(GRAYimg.at<uchar>(i, j) - 128);//�ڼ�������У�����128Ϊ���Ⱦ�ֵ��  
			int x = GRAYimg.at<uchar>(i, j);
			Hist[x]++;
		}
	}
	da = a / float(GRAYimg.rows*InputImg.cols);
	float D = abs(da);
	float Ma = 0;
#pragma omp parallel for
	for (int i = 0; i < 256; i++)
	{
		Ma += abs(i - 128 - da)*Hist[i];
	}
	Ma /= float((GRAYimg.rows*GRAYimg.cols));
	float M = abs(Ma);
	float K = D / M;
	cast = K;
	if (cast>1)
	{
		printf("ͼƬ��������\n");
	}
	else{
		printf("ͼƬ�����쳣\n");
	}

	return;
}

void colorException(Mat InputImg, float& cast, float& da, float& db)
{

	Mat LABimg;
	cvtColor(InputImg, LABimg, CV_BGR2Lab);//�ο�http://blog.csdn.net/laviewpbt/article/details/9335767  
	//����OpenCV����ĸ�ʽ��uint8�����������LABimg�ӱ�׼��0��100��-127��127��-127��127����ӳ�䵽��0��255��0��255��0��255�ռ�  
	float a = 0, b = 0;
	int HistA[256], HistB[256];
#pragma omp parallel for
	for (int i = 0; i<256; i++)
	{
		HistA[i] = 0;
		HistB[i] = 0;
	}
#pragma omp parallel for
	for (int i = 0; i<LABimg.rows; i++)
	{
#pragma omp parallel for
		for (int j = 0; j<LABimg.cols; j++)
		{
			a += float(LABimg.at<cv::Vec3b>(i, j)[1] - 128);//�ڼ�������У�Ҫ���ǽ�CIE L*a*b*�ռ仹ԭ ��ͬ  
			b += float(LABimg.at<cv::Vec3b>(i, j)[2] - 128);
			int x = LABimg.at<cv::Vec3b>(i, j)[1];
			int y = LABimg.at<cv::Vec3b>(i, j)[2];
			HistA[x]++;
			HistB[y]++;
		}
	}
	da = a / float(LABimg.rows*LABimg.cols);
	db = b / float(LABimg.rows*LABimg.cols);

	float D = sqrt(da*da + db*db);
	float Ma = 0, Mb = 0;
#pragma omp parallel for
	for (int i = 0; i<256; i++)
	{
		Ma += abs(i - 128 - da)*HistA[i];//���㷶Χ-128��127  
		Mb += abs(i - 128 - db)*HistB[i];
	}
	Ma /= float((LABimg.rows*LABimg.cols));
	Mb /= float((LABimg.rows*LABimg.cols));
	float M = sqrt(Ma*Ma + Mb*Mb);
	float K = D / M;
	cast = K;
	if (cast>1)
	{
		printf("����ɫ��\n");
	}
	else{
		printf("�Ƚ�����\n");
	}
	if (da > 0)
	{
		printf("ƫ��\n");
	}
	else{
		printf("ƫ��\n");
	}
	if (db > 0)
	{
		printf("ƫ��\n");
	}
	else{
		printf("ƫ��\n");

	}
	return;

}
double DefRto(Mat frame)
{
	Mat gray;
	cvtColor(frame, gray, CV_BGR2GRAY);
	IplImage *img = &(IplImage(gray));
	double temp = 0;
	double DR = 0;
	int i, j;//ѭ������  
	int height = img->height;
	int width = img->width;
	int step = img->widthStep / sizeof(uchar);
	uchar *data = (uchar*)img->imageData;
	double num = width*height;

	for (i = 0; i<height; i++)
	{

		for (j = 0; j<width; j++)
		{
			temp += sqrt((pow((double)(data[(i + 1)*step + j] - data[i*step + j]), 2) + pow((double)(data[i*step + j + 1] - data[i*step + j]), 2)));
			temp += abs(data[(i + 1)*step + j] - data[i*step + j]) + abs(data[i*step + j + 1] - data[i*step + j]);
		}
	}
	DR = temp / num;
	if (DR > 14)
	{
		printf("ͼƬ����\n");
	}
	else if (DR < 10)
	{
		printf("ͼƬģ��\n");
	}
	else{
		printf("ͼƬ������һ��\n");
	}
	return DR;
}
int main(){
	Mat image = imread("1.jpg");
	float cast1, da1, db1;
	double start = (double)cvGetTickCount();
	colorException(image, cast1, da1, db1);
	brightnessException(image, cast1, da1);
	DefRto(image);
	// do something ...  
	double all_end = (double)cvGetTickCount();
	double t2 = (all_end - start) / ((double)cvGetTickFrequency()*1000.);
	printf("time is %f", t2);
	
	system("pause");
	return 0;
}