#include "opencv2/core/core.hpp"  
#include"opencv2/highgui/highgui.hpp"  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <omp.h>

using namespace cv;


double DefRto(Mat frame)
{
	Mat gray;
	cvtColor(frame, gray, CV_BGR2GRAY);
	IplImage *img = &(IplImage(gray));
	double temp = 0;
	double DR = 0;
	int i, j;//Ñ­»·±äÁ¿  
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
	return DR;
}
int main(){
	Mat image = imread("pic.jpg");
	if (DefRto( image) > 14)
	{
		printf("this image is clear\n");
	}
	else if (DefRto(image) < 10)
	{
		printf("this image is fuzzy\n");
	}
	else{
		printf("this image is normal\n");
	}
	double t = (double)getTickCount();
	// do something ...  
	t = ((double)getTickCount() - t) / getTickFrequency();
	printf("time is %f", t);
	system("pause");
	return 0;
}