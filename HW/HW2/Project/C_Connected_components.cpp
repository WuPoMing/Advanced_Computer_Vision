#include "Header.h"
#define PI 3.14159265

void C_Connected_components() {
	Mat img = imread("lan_island_square.bmp");
	Mat img_gray = imread("lan_island_square.bmp", 0);
	TickMeter time;

	/*---------------------------------------------binarizing---------------------------------------------*/
	time.start();
	Mat img_binary = binarize_OSTU(img_gray);
	time.stop();
	cout << "binarizing time: " << time << endl;
	imwrite("01_lan_island_square_binary_C.bmp", img_binary);

	/*---------------------------------------------morphology---------------------------------------------*/
	time.reset();
	time.start();
	img_binary = get_dilation(img_binary, 8);
	img_binary = get_erosion(img_binary, 8);
	time.stop();
	cout << "morphology time: " << time << endl;
	imwrite("02_lan_island_square_morphology_C.bmp", img_binary);

	/*-----------------------------------------connected component-----------------------------------------*/
	time.reset(); 
	time.start();
	int * labels = get_connected_components_labels(~img_binary);
	time.stop();
	cout << "connected component time: " << time << endl;

	/*------------------------------------------property analysis------------------------------------------*/
	time.reset(); 
	time.start();
	for (int i = 1; i < 4; i++) {
		string region;
		if (i == 1) region = "GREEN";
		if (i == 2) region = "BLUE";
		if (i == 3) region = "RED";
		printf("==============================COMPONENT %s==============================\n", region.c_str());
		int x_count = 0;
		int y_count = 0;
		double centroid_x, centroid_y;
		int AREA = 0;
		int LEFT = 9999;
		int TOP = 9999;
		int RIGHT = -9999;
		int BOTTON = -9999;

		// find centroids and areas
		for (int y = 0; y < 800; y++) {
			for (int x = 0; x < 800; x++) {
				// find bounding box values
				if (labels[800 * y + x] == i) {
					if (x < LEFT)
						LEFT = x;
					if (x > RIGHT)
						RIGHT = x;
					if (y < TOP)
						TOP = y;
					if (y > BOTTON)
						BOTTON = y;
					x_count += x;
					y_count += y;
					AREA++;
				}
			}
		}

		centroid_x = (double)x_count / AREA;
		centroid_y = (double)y_count / AREA;
		printf("Centroid %s: [%.3f, %.3f]\n", region.c_str(), centroid_x, centroid_y);
		printf("Area %s: %d\n", region.c_str(), AREA);

		// 找八個極點
		point LT = { 9999, 9999 };
		point LB = { 9999, 9999 };
		point TL = { 9999, 9999 };
		point TR = { 9999, 9999 };
		point RT = { 9999, 9999 };
		point RB = { 9999, 9999 };
		point BL = { 9999, 9999 };
		point BR = { 9999, 9999 };

		for (int y = 0; y < BOTTON; y++) {
			if (LB.x == 9999 && LB.y == 9999 && labels[800 * y + LEFT] == i)
				LT = { LEFT, y };
			if (labels[800 * y + LEFT] == i)
				LB = { LEFT, y };
			if (RB.x == 9999 && RB.y == 9999 && labels[800 * y + RIGHT] == i)
				RT = { RIGHT, y };
			if (labels[800 * y + RIGHT] == i)
				RB = { RIGHT, y };
		}
		for (int x = 0; x < RIGHT; x++) {
			if (TR.x == 9999 && TR.y == 9999 && labels[800 * TOP + x] == i)
				TL = { x, TOP };
			if (labels[800 * TOP + x] == i)
				TR = { x, TOP };
			if (BR.x == 9999 && BR.y == 9999 && labels[800 * BOTTON + x] == i)
				BL = { x, BOTTON };
			if (labels[800 * BOTTON + x] == i)
				BR = { x, BOTTON };
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

		if (M1 > M2 && M1 > M3 && M1 > M4)
			printf("(length, orientation) of the longest axis M1: (%f, %f°)\n", M1, THETA1);
		else if (M2 > M1 && M2 > M3 && M2 > M4)
			printf("(length, orientation) of the longest axis M2: (%f, %f°)\n", M2, THETA2);
		else if (M3 > M1 && M3 > M2 && M3 > M4)
			printf("(length, orientation) of the longest axis M3: (%f, %f°)\n", M3, THETA3);
		else
			printf("(length, orientation) of the longest axis M4: (%f, %f°)\n", M4, THETA4);
	}
	time.stop();
	cout << "property analysis time: " << time << endl;

	/*-----------------------------------------------drawing-----------------------------------------------*/
	time.reset(); 
	time.start();
	for (int i = 1; i < 4; i++) {
		int LEFT = 9999;
		int TOP = 9999;
		int RIGHT = -9999;
		int BOTTON = -9999;

		// find centroids and areas
		for (int y = 0; y < 800; y++) {
			for (int x = 0; x < 800; x++) {
				// find bounding box values
				if (labels[800 * y + x] == i) {
					if (x < LEFT)
						LEFT = x;
					if (x > RIGHT)
						RIGHT = x;
					if (y < TOP)
						TOP = y;
					if (y > BOTTON)
						BOTTON = y;
				}
			}
		}

		// draw bounding box
		int b, g, r;
		if (i == 1) b = 0, g = 255, r = 0;
		if (i == 2) b = 255, g = 0, r = 0;
		if (i == 3) b = 0, g = 0, r = 255;

		for (int x = LEFT; x <= RIGHT; x++) {
			img.at<Vec3b>(TOP, x)[0] = b;
			img.at<Vec3b>(TOP, x)[1] = g;
			img.at<Vec3b>(TOP, x)[2] = r;

			img.at<Vec3b>(BOTTON, x)[0] = b;
			img.at<Vec3b>(BOTTON, x)[1] = g;
			img.at<Vec3b>(BOTTON, x)[2] = r;
		}

		for (int y = TOP; y <= BOTTON; y++) {
			img.at<Vec3b>(y, LEFT)[0] = b;
			img.at<Vec3b>(y, LEFT)[1] = g;
			img.at<Vec3b>(y, LEFT)[2] = r;

			img.at<Vec3b>(y, RIGHT)[0] = b;
			img.at<Vec3b>(y, RIGHT)[1] = g;
			img.at<Vec3b>(y, RIGHT)[2] = r;
		}
	}
	time.stop();
	cout << "drawing time: " << time << endl;
	imwrite("03_lan_island_square_boundingbox_C.bmp", img);


	//imshow("img", img);
	//waitKey(0);
	//destroyAllWindows();
}