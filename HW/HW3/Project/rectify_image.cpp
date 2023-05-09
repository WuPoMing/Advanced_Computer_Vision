#include "Header.h"

void rectify_image() {
	Mat img_omnidirectional = imread("360degree.bmp");
	Mat img_panoramic = rectify(img_omnidirectional, 512, 384, 720, 384);
	imwrite("01_360degree_panoramic.bmp", img_panoramic);
}