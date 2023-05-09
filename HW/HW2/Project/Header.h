#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace std;
using namespace cv;

void C_Connected_components();
void OpenCV_Connected_components();

struct point {
	int x;
	int y;
};

Mat binarize_OSTU(Mat img);
Mat get_dilation(Mat img, int iterations);
Mat get_erosion(Mat img, int iterations);
int* get_connected_components_labels(Mat img);