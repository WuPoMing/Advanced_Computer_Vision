#include "Header.h"

void image_stitching_CV() {
	Mat left = imread("left.bmp");
	Mat right = imread("right.bmp");
	vector<Mat> img_vector;
	img_vector.push_back(left.clone());
	img_vector.push_back(right.clone());
	Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::SCANS);
	Mat out;
	Stitcher::Status status = stitcher->stitch(img_vector, out);
	imwrite("03_stitching_CV.bmp", out);
}