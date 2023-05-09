#include <stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "Header.h"
using namespace cv;

void hw_opencv() {
	// initial variables
	Mat img = imread("input image/InputImage1.bmp");
	Mat img_neg;
	Mat tmp, tmp1;
	Mat img_new(img.rows, img.cols, CV_8UC3);

	// process
	bitwise_not(img, img_neg);

	int x1 = 0, y1 = 0;
	int x2 = img.cols - 1, y2 = 0;
	int x3 = 0, y3 = img.rows - 1;
	int x4 = img.cols - 1, y4 = img.rows - 1;
	rotate(img, tmp, ROTATE_90_CLOCKWISE);
	rotate(img, tmp1, ROTATE_90_COUNTERCLOCKWISE);

	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) >= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) <= 0) {
				img_new.at<Vec3b>(Point(x, y)) = tmp1.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) >= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) >= 0) {
				
				img_new.at<Vec3b>(Point(x, y)) = tmp.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) <= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) >= 0) {
				img_new.at<Vec3b>(Point(x, y)) = tmp1.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) <= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) <= 0) {
				img_new.at<Vec3b>(Point(x, y)) = tmp.at<Vec3b>(Point(x, y));
			}
			if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) == 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) == 0) {
				img_new.at<Vec3b>(Point(x, y)) = img.at<Vec3b>(Point(x, y));
			}
		}
	}

	// show images
	imshow("lena_neg_opencv", img_neg);
	imshow("lena_new_opencv", img_new);
	waitKey(0);
	destroyAllWindows();

	// write file
	imwrite("output image/lena_neg_opencv.bmp", img_neg);
	printf("Save lena_neg_opencv.bmp successfully...\n");
	imwrite("output image/lena_new_opencv.bmp", img_new);
	printf("Save lena_new_opencv.bmp successfully...\n\n");
}