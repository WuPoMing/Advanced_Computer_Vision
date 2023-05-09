#include "Header.h"
#define PI 3.14159265

void OpenCV_Connected_components() {
	Mat img = imread("lan_island_square.bmp");
	Mat img_gray = imread("lan_island_square.bmp", 0);
	Mat img_binary;
	Mat labels, stats, centroids;
	TickMeter time;

	/*---------------------------------------------binarizing---------------------------------------------*/
	time.start();
	threshold(img_gray, img_binary, 120, 255, THRESH_BINARY);
	time.stop();
	cout << "binarizing time: " << time << endl;
	imwrite("01_lan_island_square_binary_OpenCV.bmp", img_binary);

	/*---------------------------------------------morphology---------------------------------------------*/
	time.reset(); 
	time.start();
	Mat kernel = getStructuringElement(MORPH_CROSS, Size(5,5));
	dilate(img_binary, img_binary, kernel, Point(-1,-1), 4);
	kernel = getStructuringElement(MORPH_CROSS, Size(5, 5));
	erode(img_binary, img_binary, kernel, Point(-1, -1), 4);
	time.stop();
	cout << "morphology time: " << time << endl;
	imwrite("02_lan_island_square_morphology_OpenCV.bmp", img_binary);

	/*-----------------------------------------connected component-----------------------------------------*/
	time.reset(); 
	time.start();
	int nccomps = connectedComponentsWithStats(~img_binary, labels, stats, centroids, 4);
	time.stop();
	cout << "connected component time: " << time << endl;
	
	/*------------------------------------------property analysis------------------------------------------*/
	time.reset(); 
	time.start();
	for (int i = 1; i < nccomps; i++) {
		printf("==============================COMPONENT %d==============================\n", i);

		// find centroids and areas
		double x = centroids.at<double>(i, 0);
		double y = centroids.at<double>(i, 1);
		int AREA = stats.at<int>(i, CC_STAT_AREA);
		printf("Centroid %d: [%.3f, %.3f]\n", i, x, y);
		printf("Area %d: %d\n", i, AREA);

		// 找八個極點
		int LEFT = stats.at<int>(i, CC_STAT_LEFT);
		int TOP = stats.at<int>(i, CC_STAT_TOP);
		int WIDTH = stats.at<int>(i, CC_STAT_WIDTH);
		int HEIGHT = stats.at<int>(i, CC_STAT_HEIGHT);
		int RIGHT = LEFT + WIDTH - 1;
		int BOTTON = TOP + HEIGHT - 1;
		Point LT = Point(9999, 9999);
		Point LB = Point(9999, 9999);
		Point TL = Point(9999, 9999);
		Point TR = Point(9999, 9999);
		Point RT = Point(9999, 9999);
		Point RB = Point(9999, 9999);
		Point BL = Point(9999, 9999);
		Point BR = Point(9999, 9999);

		for (int y = 0; y < BOTTON; y++) {
			if (img_binary.at<uchar>(y, LEFT) == 0 && LB == Point(9999, 9999) && labels.at<int>(y, LEFT) == i)
				LT = Point(LEFT, y);
			if (img_binary.at<uchar>(y, LEFT) == 0 && labels.at<int>(y, LEFT) == i)
				LB = Point(LEFT, y);
			if (img_binary.at<uchar>(y, RIGHT) == 0 && RB == Point(9999, 9999) && labels.at<int>(y, RIGHT) == i)
				RT = Point(RIGHT, y);
			if (img_binary.at<uchar>(y, RIGHT) == 0 && labels.at<int>(y, RIGHT) == i)
				RB = Point(RIGHT, y);
		}
		for (int x = 0; x < RIGHT; x++) {
			if (img_binary.at<uchar>(TOP, x) == 0 && TR == Point(9999, 9999) && labels.at<int>(TOP, x) == i)
				TL = Point(x, TOP);
			if (img_binary.at<uchar>(TOP, x) == 0 && labels.at<int>(TOP, x) == i)
				TR = Point(x, TOP);
			if (img_binary.at<uchar>(BOTTON, x) == 0 && BR == Point(9999, 9999) && labels.at<int>(BOTTON, x) == i)
				BL = Point(x, BOTTON);
			if (img_binary.at<uchar>(BOTTON, x) == 0 && labels.at<int>(BOTTON, x) == i)
				BR = Point(x, BOTTON);
		}
		// 算軸長、角度
		double M1 = sqrt(pow(TL.x - BR.x, 2) + pow(TL.y - BR.y, 2));
		double M2 = sqrt(pow(TR.x - BL.x, 2) + pow(TR.y - BL.y, 2));
		double M3 = sqrt(pow(RT.x - LB.x, 2) + pow(RT.y - LB.y, 2));
		double M4 = sqrt(pow(RB.x - LT.x, 2) + pow(RB.y - LT.y, 2));
		double THETA1 = atan((double)(TL.y - BR.y) / -(TL.x - BR.x)) * 180 / PI;
		double THETA2 = atan((double)(TR.y - BL.y) / -(TR.x - BL.x)) * 180 / PI;
		double THETA3 = atan((double)(RT.y - LB.y) / -(RT.x - LB.x)) * 180 / PI;
		double THETA4 = atan((double)(RB.y - LT.y) / -(RB.x - LT.x)) * 180 / PI;
		double b, g, r;
		if (i == 1) b = 0, g = 255, r = 0;
		if (i == 2) b = 255, g = 0, r = 0;
		if (i == 3) b = 0, g = 0, r = 255;

		if (M1 > M2 && M1 > M3 && M1 > M4) {
			printf("(length, orientation) of the longest axis M1: (%f, %f°)\n", M1, THETA1);
			line(img, TL, BR, Scalar(b, g, r), 1);
		}
		else if (M2 > M1 && M2 > M3 && M2 > M4) {
			printf("(length, orientation) of the longest axis M2: (%f, %f°)\n", M2, THETA2);
			line(img, TR, BL, Scalar(b, g, r), 1);
		}
		else if (M3 > M1 && M3 > M2 && M3 > M4) {
			printf("(length, orientation) of the longest axis M3: (%f, %f°)\n", M3, THETA3);
			line(img, RT, LB, Scalar(b, g, r), 1);
		}
		else {
			printf("(length, orientation) of the longest axis M4: (%f, %f°)\n", M4, THETA4);
			line(img, RB, LT, Scalar(b, g, r), 1);
		}
	}
	time.stop();
	cout << "property analysis time: " << time << endl;

	/*-----------------------------------------------drawing-----------------------------------------------*/
	time.reset(); 
	time.start();
	for (int i = 1; i < nccomps; i++) {
		int LEFT = stats.at<int>(i, CC_STAT_LEFT);
		int TOP = stats.at<int>(i, CC_STAT_TOP);
		int WIDTH = stats.at<int>(i, CC_STAT_WIDTH);
		int HEIGHT = stats.at<int>(i, CC_STAT_HEIGHT);
		int RIGHT = LEFT + WIDTH - 1;
		int BOTTON = TOP + HEIGHT - 1;
		int x = (LEFT + RIGHT) / 2;
		int y = (TOP + BOTTON) / 2;
		double b, g, r;
		if (i == 1) b = 0, g = 255, r = 0;
		if (i == 2) b = 255, g = 0, r = 0;
		if (i == 3) b = 0, g = 0, r = 255;

		rectangle(img, Rect(LEFT, TOP, WIDTH, HEIGHT), Scalar(b, g, r), 1, 1, 0);
		putText(img, to_string(i), Point(x, y), FONT_HERSHEY_DUPLEX, 1, Scalar(b, g, r));
	}
	time.stop();
	cout << "drawing time: " << time << endl;
	imwrite("03_lan_island_square_boundingbox_OpenCV.bmp", img);

	/*--------------------------------------------show images--------------------------------------------*/
	//imshow("img", img);
	//waitKey(0);
	//destroyAllWindows();
}