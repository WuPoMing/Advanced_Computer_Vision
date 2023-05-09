#include "Header.h"

int main() {
	while (1) {
		printf("0:Exit\n");
		printf("1: C_Connected_components.cpp\n");
		printf("2: OpenCV_Connected_components.cpp\n");
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
			C_Connected_components();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		case 2:
			OpenCV_Connected_components();
			printf("-----------------------------------------------------------------------\n\n");
			break;
		default:
			printf("<<Please enter number 0~2!!>>\n\n");
			printf("-----------------------------------------------------------------------\n\n");
			break;
		}
		if (stop == 1) break;
	}
}