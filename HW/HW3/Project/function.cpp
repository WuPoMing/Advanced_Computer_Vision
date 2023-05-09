#include "Header.h"
#define PI 3.1415926535

Mat rectify(Mat img_omnidirectional, int Xc, int Yc, int out_width, int out_height) {
	Mat out(out_height, out_width, CV_8UC3);

	for (int y = 0; y < out_height; y++) {
		for (int x = 0; x < out_width; x++) {
			int ix = y * cos(2 * PI * x / 720) + Xc;
			int iy = y * sin(2 * PI * x / 720) + Yc;
			out.at<Vec3b>(out_height - 1 - y, out_width - 1 - x)[2] = img_omnidirectional.at<Vec3b>(iy, ix)[2];
			out.at<Vec3b>(out_height - 1 - y, out_width - 1 - x)[1] = img_omnidirectional.at<Vec3b>(iy, ix)[1];
			out.at<Vec3b>(out_height - 1 - y, out_width - 1 - x)[0] = img_omnidirectional.at<Vec3b>(iy, ix)[0];
		}
	}

	return out;
}

uchar* histogram_matching(uchar* src_img, int src_width, int src_height, uchar* dst_img, int dst_width, int dst_height) {
	double* src_histogram_count = new double[256]{ 0 };
	double* dst_histogram_count = new double[256]{ 0 };
	double* src_cdf = new double[256]{ 0 };
	double* dst_cdf = new double[256]{ 0 };
	double* diff = new double[256]{ 0 };
	uchar* M = new uchar[256]{ 0 };
	uchar* new_img = new uchar[dst_width * dst_height];

	// src image
	for (int i = 0; i < src_width * src_height; i++)
		src_histogram_count[src_img[i]]++;		// 計算各像素累積值

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < i; j++) {
			src_cdf[i] += src_histogram_count[j] / (double)(src_width * src_height);		// 累加
		}
	}

	// dst image
	for (int i = 0; i < dst_width * dst_height; i++)
		dst_histogram_count[dst_img[i]]++;		// 計算各像素累積值

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < i; j++) {
			dst_cdf[i] += dst_histogram_count[j] / (double)(dst_width * dst_height);		// 累加
		}
	}

	// diff
	for (int i = 0; i < 256; i++) {

		for (int j = 0; j < 256; j++) {
			diff[j] = abs(dst_cdf[i] - src_cdf[j]);
		}

		int idx = 0;
		double val = diff[0];
		for (int k = 0; k < 256; k++) {
			if (diff[k] < val) {
				val = diff[k];
				idx = k;
			}
		}
		M[i] = idx;
	}

	for (int i = 0; i < dst_width * dst_height; i++) {
		new_img[i] = M[dst_img[i]];
	}

	return new_img;
}