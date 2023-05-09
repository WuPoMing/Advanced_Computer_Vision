#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Header.h"
using namespace cv;

void hw_opencv_bonus() {
	// initial variables
	Mat img = imread("input image/InputImage1.bmp");
	Mat img_onehalf, img_double, img_neg_onehalf, img_neg_double, tmp_onehalf, tmp_double, tmp1_onehalf, tmp1_double;
	Mat img_new_onehalf(img.rows * 0.5, img.cols * 0.5, CV_8UC3);
	Mat img_new_double(img.rows * 2, img.cols * 2, CV_8UC3);
	resize(img, img_onehalf, Size(img.cols * 0.5, img.rows * 0.5), 0, 0, INTER_LINEAR);
	resize(img, img_double, Size(img.cols * 2, img.rows * 2), 0, 0, INTER_LINEAR);

	// negative image
	bitwise_not(img_onehalf, img_neg_onehalf);
	bitwise_not(img_double, img_neg_double);
	
	// Split and reassemble into new image (onehalf size)
	int x1 = 0, y1 = 0;
	int x2 = img_onehalf.cols - 1, y2 = 0;
	int x3 = 0, y3 = img_onehalf.rows - 1;
	int x4 = img_onehalf.cols - 1, y4 = img_onehalf.rows - 1;
	rotate(img_onehalf, tmp_onehalf, ROTATE_90_CLOCKWISE);
	rotate(img_onehalf, tmp1_onehalf, ROTATE_90_COUNTERCLOCKWISE);

	for (int y = 0; y < img_onehalf.rows; y++) {
		for (int x = 0; x < img_onehalf.cols; x++) {
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) >= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) <= 0) {
				img_new_onehalf.at<Vec3b>(Point(x, y)) = tmp1_onehalf.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) >= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) >= 0) {

				img_new_onehalf.at<Vec3b>(Point(x, y)) = tmp_onehalf.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) <= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) >= 0) {
				img_new_onehalf.at<Vec3b>(Point(x, y)) = tmp1_onehalf.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) <= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) <= 0) {
				img_new_onehalf.at<Vec3b>(Point(x, y)) = tmp_onehalf.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) == 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) == 0) {
				img_new_onehalf.at<Vec3b>(Point(x, y)) = img_onehalf.at<Vec3b>(Point(x, y));
			}
		}
	}
	
	// Split and reassemble into new image (double size)
	int x11 = 0, y11 = 0;
	int x22 = img_double.cols - 1, y22 = 0;
	int x33 = 0, y33 = img_double.rows - 1;
	int x44 = img_double.cols - 1, y44 = img_double.rows - 1;
	rotate(img_double, tmp_double, ROTATE_90_CLOCKWISE);
	rotate(img_double, tmp1_double, ROTATE_90_COUNTERCLOCKWISE);

	for (int y = 0; y < img_double.rows; y++) {
		for (int x = 0; x < img_double.cols; x++) {
			if ((y - y44) * (x11 - x44) - (x - x44) * (y11 - y44) >= 0 && (y - y33) * (x22 - x33) - (x - x33) * (y22 - y33) <= 0) {
				img_new_double.at<Vec3b>(Point(x, y)) = tmp1_double.at<Vec3b>(Point(x, y));
			}
			if ((y - y44) * (x11 - x44) - (x - x44) * (y11 - y44) >= 0 && (y - y33) * (x22 - x33) - (x - x33) * (y22 - y33) >= 0) {

				img_new_double.at<Vec3b>(Point(x, y)) = tmp_double.at<Vec3b>(Point(x, y));
			}
			if ((y - y44) * (x11 - x44) - (x - x44) * (y11 - y44) <= 0 && (y - y33) * (x22 - x33) - (x - x33) * (y22 - y33) >= 0) {
				img_new_double.at<Vec3b>(Point(x, y)) = tmp1_double.at<Vec3b>(Point(x, y));
			}
			if ((y - y44) * (x11 - x44) - (x - x44) * (y11 - y44) <= 0 && (y - y33) * (x22 - x33) - (x - x33) * (y22 - y33) <= 0) {
				img_new_double.at<Vec3b>(Point(x, y)) = tmp_double.at<Vec3b>(Point(x, y));
			}
			if ((y - y44) * (x11 - x44) - (x - x44) * (y11 - y44) == 0 && (y - y33) * (x22 - x33) - (x - x33) * (y22 - y33) == 0) {
				img_new_double.at<Vec3b>(Point(x, y)) = img_double.at<Vec3b>(Point(x, y));
			}
		}
	}

	// show images
	imshow("lena_neg_onehalf_opencv", img_neg_onehalf);
	imshow("lena_neg_double_opencv", img_neg_double);
	imshow("img_new_onehalf_opencv", img_new_onehalf);
	imshow("img_new_double_opencv", img_new_double);
	waitKey(0);
	destroyAllWindows();

	// write file
	imwrite("output image/lena_neg_onehalf_opencv.bmp", img_neg_onehalf);
	printf("Save lena_neg_onehalf_opencv.bmp successfully...\n");
	imwrite("output image/lena_neg_double_opencv.bmp", img_neg_double);
	printf("Save lena_neg_double_opencv.bmp successfully...\n");
	imwrite("output image/img_new_onehalf_opencv.bmp", img_new_onehalf);
	printf("Save img_new_onehalf_opencv.bmp successfully...\n");
	imwrite("output image/img_new_double_opencv.bmp", img_new_double);
	printf("Save img_new_double_opencv.bmp successfully...\n\n");
}