#include "Header.h"

void style_transfer() {
	Mat left = imread("left.bmp");
	Mat right = imread("right.bmp");
	Mat styleimage = imread("styleimage.bmp");

	int width = left.cols;
	int height = left.rows;
	uchar* left0 = new uchar[width * height];
	uchar* left1 = new uchar[width * height];
	uchar* left2 = new uchar[width * height];

	uchar* right0 = new uchar[width * height];
	uchar* right1 = new uchar[width * height];
	uchar* right2 = new uchar[width * height];

	uchar* styleimage0 = new uchar[563 * 750];
	uchar* styleimage1 = new uchar[563 * 750];
	uchar* styleimage2 = new uchar[563 * 750];

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			left0[x + y * width] = left.at<Vec3b>(y, x)[0];
			left1[x + y * width] = left.at<Vec3b>(y, x)[1];
			left2[x + y * width] = left.at<Vec3b>(y, x)[2];

			right0[x + y * width] = right.at<Vec3b>(y, x)[0];
			right1[x + y * width] = right.at<Vec3b>(y, x)[1];
			right2[x + y * width] = right.at<Vec3b>(y, x)[2];
		}
	}

	for (int y = 0; y < 750; y++) {
		for (int x = 0; x < 563; x++) {
			styleimage0[x + y * 563] = styleimage.at<Vec3b>(y, x)[0];
			styleimage1[x + y * 563] = styleimage.at<Vec3b>(y, x)[1];
			styleimage2[x + y * 563] = styleimage.at<Vec3b>(y, x)[2];
		}
	}

	uchar* left0_histogram_matching = histogram_matching(styleimage0, 563, 750, left0, width, height);
	uchar* left1_histogram_matching = histogram_matching(styleimage1, 563, 750, left1, width, height);
	uchar* left2_histogram_matching = histogram_matching(styleimage2, 563, 750, left2, width, height);

	uchar* right0_histogram_matching = histogram_matching(styleimage0, 563, 750, right0, width, height);
	uchar* right1_histogram_matching = histogram_matching(styleimage1, 563, 750, right1, width, height);
	uchar* right2_histogram_matching = histogram_matching(styleimage2, 563, 750, right2, width, height);

	Mat left_histogram_matching(height, width, CV_8UC3);
	Mat right_histogram_matching(height, width, CV_8UC3);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			left_histogram_matching.at<Vec3b>(y, x)[0] = left0_histogram_matching[x + y * width];
			left_histogram_matching.at<Vec3b>(y, x)[1] = left1_histogram_matching[x + y * width];
			left_histogram_matching.at<Vec3b>(y, x)[2] = left2_histogram_matching[x + y * width];

			right_histogram_matching.at<Vec3b>(y, x)[0] = right0_histogram_matching[x + y * width];
			right_histogram_matching.at<Vec3b>(y, x)[1] = right1_histogram_matching[x + y * width];
			right_histogram_matching.at<Vec3b>(y, x)[2] = right2_histogram_matching[x + y * width];
		}
	}

	vector<Mat> img_vector;
	img_vector.push_back(left_histogram_matching.clone());
	img_vector.push_back(right_histogram_matching.clone());
	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::SCANS);
	Mat out;
	Stitcher::Status status = stitcher->stitch(img_vector, out);
	imwrite("04_transfer_stitching.bmp", out);
}