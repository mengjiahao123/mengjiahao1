#include "opencv2/core/core.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
using namespace cv;
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
	return ;
	
}
int main(){
	Mat image = imread("2.jpg");
	float cast1, da1, db1;
	double start = (double)cvGetTickCount();
	colorException(image, cast1, da1, db1);
	// do something ...  
	double all_end = (double)cvGetTickCount();
	double t2 = (all_end - start) / ((double)cvGetTickFrequency()*1000.);
	printf("time is %f", t2);
	system("pause");
	return 0;
	
}