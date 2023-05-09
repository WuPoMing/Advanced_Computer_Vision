#include "Header.h"

void Find_Mangogo()
{
	Mat img1 = imread("findmango1.jpg");
	Mat template1 = imread("mangogo1.jpg");
	Mat img2 = imread("findmango2.jpg");
	Mat template2 = imread("mangogo2.jpg");

	Mat result1, result2;

	Point min_loc1, max_loc1, min_loc2, max_loc2;
	double min_val1, max_val1, min_val2, max_val2;

	matchTemplate(img1, template1, result1, TM_CCOEFF_NORMED);
	minMaxLoc(result1, &min_val1, &max_val1, &min_loc1, &max_loc1);
	//rectangle(img1, max_loc1, Point(max_loc1.x + template1.cols, max_loc1.y + template1.rows), Scalar(255, 255, 0), 2);
	for (int y = 0; y < img1.rows; y++)
	{
		for (int x = 0; x < img1.cols; x++)
		{
			if (x < max_loc1.x || x > max_loc1.x + template1.cols || y < max_loc1.y || y > max_loc1.y + template1.rows)
			{
				img1.at<Vec3b>(y, x) = img1.at<Vec3b>(y, x) * 0.3;
			}
		}
	}
	imwrite("01_find1.jpg", img1);

	matchTemplate(img2, template2, result2, TM_CCOEFF_NORMED);
	minMaxLoc(result2, &min_val2, &max_val2, &min_loc2, &max_loc2);
	//rectangle(img2, max_loc2, Point(max_loc2.x + template2.cols, max_loc2.y + template2.rows), Scalar(255, 255, 0), 2);
	for (int y = 0; y < img2.rows; y++)
	{
		for (int x = 0; x < img2.cols; x++)
		{
			if (x < max_loc2.x || x > max_loc2.x + template2.cols || y < max_loc2.y || y > max_loc2.y + template2.rows)
			{
				img2.at<Vec3b>(y, x) = img2.at<Vec3b>(y, x) * 0.3;
			}
		}
	}
	imwrite("02_find2.jpg", img2);
}