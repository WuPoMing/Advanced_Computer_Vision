#include "Header.h"

int main() {
	while (1) {
		printf("0:    Exit\n");
		printf("1:    rectify_image.cpp\n");
		printf("2:    image_stitching_C.cpp\n");
		printf("3:    image_stitching_CV.cpp\n");
		printf("4:    style_transfer.cpp\n");
		printf("Enter the question number to select output result: ");

		int num;
		int stop = 0;
		scanf("%d", &num);
		printf("-------------------------------result----------------------------------\n\n");

		switch (num) {
		case 0:
			stop = 1;
			printf("<<Exit>>!\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 1:
			rectify_image();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 2:
			image_stitching_C();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 3:
			image_stitching_CV();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 4:
			style_transfer();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		default:
			printf("<<Please enter number 0~4!!>>\n\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		}
		if (stop == 1) break;
	}
}