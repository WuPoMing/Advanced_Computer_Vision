#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\stitching\warpers.hpp>

using namespace std;
using namespace cv;

void rectify_image();
void image_stitching_C();
void image_stitching_CV();
void style_transfer();

Mat rectify(Mat img_omnidirectional, int Xc, int Yc, int out_width, int out_height);
uchar* histogram_matching(uchar* src_img, int src_width, int src_height, uchar* dst_img, int dst_width, int dst_height);