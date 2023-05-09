#include "Header.h"

void image_stitching_C() {
	Mat left = imread("left.bmp");
	Mat right = imread("right.bmp");
	Mat img_stitching;
	Mat out(480, 900, CV_8UC3);

	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 900; x++) {
			if (x >= 0 && x <= 509 && y >= 80 && y <= 449) {
				out.at<Vec3b>(y, x) = left.at<Vec3b>(y - 80, x);
			}
		}
	}

	double x0 = 250, y0 = 130;
	double x1 = 770, y1 = 0;
	double x2 = 900, y2 = 475;
	double x3 = 310, y3 = 470;

	double sigma_x = x0 - x1 + x2 - x3;
	double sigma_y = y0 - y1 + y2 - y3;

	double dx1 = x1 - x2;
	double dx2 = x3 - x2;

	double dy1 = y1 - y2;
	double dy2 = y3 - y2;

	double g = (sigma_x * dy2 - sigma_y * dx2) / (dx1 * dy2 - dx2 * dy1);
	double h = (dx1 * sigma_y - sigma_x * dy1) / (dx1 * dy2 - dx2 * dy1);
	double i = 1;
	double a = x1 - x0 + g * x1;
	double b = x3 - x0 + h * x3;
	double c = x0;
	double d = y1 - y0 + g * y1;
	double e = y3 - y0 + h * y3;
	double f = y0;

	a = a / 510;
	b = b / 370;
	c = c;
	d = d / 510;
	e = e / 370;
	f = f;
	g = g / 510;
	h = h / 370;
	i = i;

	double A = e * i - f * h;
	double B = -(b * i - c * h);
	double C = b * f - c * e;
	double D = -(d * i - f * g);
	double E = a * i - c * g;
	double F = -(a * f - c * d);
	double G = d * h - e * g;
	double H = -(a * h - b * g);
	double I = a * e - b * d;

	for (int y = 0; y < out.rows; y++) {
		for (int x = 0; x < out.cols; x++) {
			double W = double(x) * G + double(y) * H + I;
			double X = (double(x) * A + double(y) * B + C) / W;
			double Y = (double(x) * D + double(y) * E + F) / W;
			if (X > 0 && X < 510 && Y > 0 && Y < 370) {
				out.at<Vec3b>(y, x) = right.at<Vec3b>(Y, X);
			}
		}
	}
	imwrite("02_stitching_C.bmp", out);
}