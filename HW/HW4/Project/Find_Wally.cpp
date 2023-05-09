#include "Header.h"

void Find_Wally()
{
	// Read in the image with template to be searched
	Mat img = imread("findwally1.jpg");
	// Read in the templates
	Mat templ_hat = imread("hat.jpg");
	Mat templ_eye = imread("eye.jpg");
	Mat templ_shirt = imread("shirt.jpg");
	// Define the result matrix
	Mat result_hat, result_eye, result_shirt;
	// Define the matching method
	int match_method = TM_CCORR_NORMED;
	// Match the templates
	matchTemplate(img, templ_hat, result_hat, match_method);
	matchTemplate(img, templ_eye, result_eye, match_method);
	matchTemplate(img, templ_shirt, result_shirt, match_method);
	// threshold
	threshold(result_hat, result_hat, 0.91, 255, THRESH_BINARY);
	threshold(result_eye, result_eye, 0.99, 255, THRESH_BINARY);
	threshold(result_shirt, result_shirt, 0.95, 255, THRESH_BINARY);
	// convert float32 to CV_8UC1
	result_hat.convertTo(result_hat, CV_8UC1);
	result_eye.convertTo(result_eye, CV_8UC1);
	result_shirt.convertTo(result_shirt, CV_8UC1);
	// find contours
	vector<vector<Point>> contour_hat, contour_eye, contour_shirt;
	vector<Vec4i> hierarchy;
	findContours(result_hat, contour_hat, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	findContours(result_eye, contour_eye, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	findContours(result_shirt, contour_shirt, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	// find centers
	vector<vector<Point>> contours_poly_hat(contour_hat.size());
	vector<Rect> boundRect_hat(contour_hat.size());
	vector<Point2f>centers_hat(contour_hat.size());
	vector<float>radius_hat(contour_hat.size());
	Mat mat_center_hat = Mat::zeros(img.size(), CV_8UC1);
	for (size_t i = 0; i < contour_hat.size(); i++)
	{
		approxPolyDP(contour_hat[i], contours_poly_hat[i], 3, true);
		boundRect_hat[i] = boundingRect(contours_poly_hat[i]);
		minEnclosingCircle(contours_poly_hat[i], centers_hat[i], radius_hat[i]);
		mat_center_hat.at<uchar>(centers_hat[i]) = 255;
	}
	vector<vector<Point>> contours_poly_eye(contour_eye.size());
	vector<Rect> boundRect_eye(contour_eye.size());
	vector<Point2f>centers_eye(contour_eye.size());
	vector<float>radius_eye(contour_eye.size());
	Mat mat_center_eye = Mat::zeros(img.size(), CV_8UC1);
	for (size_t i = 0; i < contour_eye.size(); i++)
	{
		approxPolyDP(contour_eye[i], contours_poly_eye[i], 3, true);
		boundRect_eye[i] = boundingRect(contours_poly_eye[i]);
		minEnclosingCircle(contours_poly_eye[i], centers_eye[i], radius_eye[i]);
		mat_center_eye.at<uchar>(centers_eye[i]) = 255;
	}
	vector<vector<Point>> contours_poly_shirt(contour_shirt.size());
	vector<Rect> boundRect_shirt(contour_shirt.size());
	vector<Point2f>centers_shirt(contour_shirt.size());
	vector<float>radius_shirt(contour_shirt.size());
	Mat mat_center_shirt = Mat::zeros(img.size(), CV_8UC1);
	for (size_t i = 0; i < contour_shirt.size(); i++)
	{
		approxPolyDP(contour_shirt[i], contours_poly_shirt[i], 3, true);
		boundRect_shirt[i] = boundingRect(contours_poly_shirt[i]);
		minEnclosingCircle(contours_poly_shirt[i], centers_shirt[i], radius_shirt[i]);
		mat_center_shirt.at<uchar>(centers_shirt[i]) = 255;
	}
	// dilate
	Mat mat_center_hat_dilate, mat_center_eye_dilate, mat_center_shirt_dilate;
	dilate(mat_center_hat, mat_center_hat_dilate, getStructuringElement(MORPH_ELLIPSE, Size(39, 39)));
	dilate(mat_center_shirt, mat_center_shirt_dilate, getStructuringElement(MORPH_ELLIPSE, Size(59, 59)));
	Mat find_eyes = mat_center_eye & mat_center_hat_dilate & mat_center_shirt_dilate;
	vector<vector<Point> > contours;
	Mat tmp;
	dilate(result_eye, tmp, getStructuringElement(MORPH_ELLIPSE, Size(14, 14)));
	findContours(tmp, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	vector<int> valid_cnt;
	for (int i = 0; i < contours.size(); i++) {
		if (contourArea(contours[i]) >= 243 && contourArea(contours[i]) <= 401) {
			valid_cnt.push_back(i);
		}
	}
	//rectangle(img, Point(1147, 424), Point(1168, 474), Scalar(255, 255, 0), 2);
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			if (x < 1147 || x > 1168 || y < 424 || y > 474)
			{
				img.at<Vec3b>(y, x) = img.at<Vec3b>(y, x) * 0.3;
			}
		}
	}
	imwrite("03_findWally.jpg", img);
}