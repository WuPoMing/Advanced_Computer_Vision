#include "Header.h"

Mat binarize_OSTU(Mat img) {
	// threshold 參數宣告
	int width = img.cols;
	int height = img.rows;
	double w0 = 0, w1 = 0;
	double m0 = 0, m1 = 0;
	double max_sb = 0, sb = 0;
	int threshold = 0;
	int val;

	// 計算 threshold
	for (int t = 0; t < 255; t++) {
		w0 = 0;
		w1 = 0;
		m0 = 0;
		m1 = 0;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				val = img.at<uchar>(y,x);
				if (val < t) {
					w0++;
					m0 += val;
				}
				else {
					w1++;
					m1 += val;
				}
			}
		}
		m0 /= w0;
		m1 /= w1;
		w0 /= (height * width);
		w1 /= (height * width);
		sb = w0 * w1 * pow((m0 - m1), 2);

		if (sb > max_sb) {
			max_sb = sb;
			threshold = t;
		}
	}

	// use threshold to binarize the image
	Mat new_img(height, width, CV_8UC1);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (img.at<uchar>(y, x) > threshold)
				new_img.at<uchar>(y, x) = 255;
			else
				new_img.at<uchar>(y, x) = 0;
		}
	}
	return new_img;
}

Mat get_dilation(Mat img, int iterations) {
	int width = img.cols;
	int height = img.rows;
	Mat new_img = img.clone();
	Mat tmp_img;

	for (int _ = 0; _ < iterations; _++) {
		tmp_img = new_img.clone();

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// check left pixel
				if ((x > 0) && (tmp_img.at<uchar>(y, x - 1) == 255)) {
					new_img.at<uchar>(y, x) = 255;
					continue;
				}
				// check up pixel
				if ((y > 0) && (tmp_img.at<uchar>(y - 1, x) == 255)) {
					new_img.at<uchar>(y, x) = 255;
					continue;
				}
				// check right pixel
				if ((x < width - 1) && (tmp_img.at<uchar>(y, x + 1) == 255)) {
					new_img.at<uchar>(y, x) = 255;
					continue;
				}
				// check left pixel
				if ((y < height - 1) && (tmp_img.at<uchar>(y + 1, x) == 255)) {
					new_img.at<uchar>(y, x) = 255;
					continue;
				}
			}
		}
	}
	return new_img;
}

Mat get_erosion(Mat img, int iterations) {
	int width = img.cols;
	int height = img.rows;
	Mat new_img = img.clone();
	Mat tmp_img;

	for (int _ = 0; _ < iterations; _++) {
		tmp_img = new_img.clone();

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// check left pixel
				if ((x > 0) && (tmp_img.at<uchar>(y, x - 1) == 0)) {
					new_img.at<uchar>(y, x) = 0;
					continue;
				}
				// check up pixel
				if ((y > 0) && (tmp_img.at<uchar>(y - 1, x) == 0)) {
					new_img.at<uchar>(y, x) = 0;
					continue;
				}
				// check right pixel
				if ((x < width - 1) && (tmp_img.at<uchar>(y, x + 1) == 0)) {
					new_img.at<uchar>(y, x) = 0;
					continue;
				}
				// check left pixel
				if ((y < height - 1) && (tmp_img.at<uchar>(y + 1, x) == 0)) {
					new_img.at<uchar>(y, x) = 0;
					continue;
				}
			}
		}
	}
	return new_img;
}

int* get_connected_components_labels(Mat img) {
	int width = img.cols;
	int height = img.rows;
	int* labels = new int[width * height];
	int label_count = 1;

	// 標記
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int val = img.at<uchar>(y,x);
			// if white
			if (val == 255) {
				// (0, 0)
				if (x == 0 && y == 0) {
					labels[width * y + x] = label_count;
					label_count++;
				}
				// top line
				else if (x != 0 && y == 0) {
					if (labels[width * y + x - 1] != 0) {
						labels[width * y + x] = labels[width * y + x - 1];
					}
					else {
						labels[width * y + x] = label_count;
						label_count++;
					}
				}
				// left line
				else if (x == 0 && y != 0) {
					if (labels[width * (y - 1) + x] != 0) {
						labels[width * y + x] = labels[width * (y - 1) + x];
					}
					else {
						labels[width * y + x] = label_count;
						label_count++;
					}
				}
				else {
					// top != 0
					if (labels[width * (y - 1) + x] != 0 && (labels[width * y + x - 1] == 0)) {
						labels[width * y + x] = labels[width * (y - 1) + x];
					}
					// left != 0
					else if (labels[width * (y - 1) + x] == 0 && (labels[width * y + x - 1] != 0)) {
						labels[width * y + x] = labels[width * y + x - 1];
					}
					// left != 0 & top != 0
					else if (labels[width * (y - 1) + x] != 0 && (labels[width * y + x - 1] != 0)) {
						labels[width * y + x] = labels[width * (y - 1) + x];
						int top_label = labels[width * (y - 1) + x];
						int left_label = labels[width * y + x - 1];

						if (top_label != left_label) {
							for (int i = 0; i < height; i++) {
								for (int j = 0; j < width; j++) {
									if (labels[width * i + j] == left_label) {
										labels[width * i + j] = top_label;
									}
								}
							}
						}
					}
					else {
						labels[width * y + x] = label_count;
						label_count++;
					}
				}
			}
			// if black
			else {
				labels[width * y + x] = 0;
			}
		}
	}

	// 轉換 labels 成 0 ~ 3
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (labels[width * y + x] != 0) {
				labels[width * y + x] = labels[width * y + x] % 255 + 1;
				if (labels[width * y + x] == 85) {
					labels[width * y + x] = 1;
				}
				else if (labels[width * y + x] == 3) {
					labels[width * y + x] = 2;
				}
				else {
					labels[width * y + x] = 3;
				}
			}
			else {
				labels[width * y + x] = 0;
			}
		}
	}
	return labels;
}