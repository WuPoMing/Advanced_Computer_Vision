#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <iostream>
#include "Header.h"

int main() {
	while (1) {
		printf("0:Exit\n");
		printf("1:hw_C.cpp\n");
		printf("2:hw_C_bonus.cpp\n");
		printf("3:hw_opencv.cpp\n");
		printf("4:hw_opencv_bonus.cpp\n");
		printf("Enter the question number to select output result:");

		int num;
		int stop = 0;
		scanf("%d", &num);

		switch (num) {
		case 0:
			stop = 1;
			printf("<<Exit>>!\n");
			break;
		case 1:
			hw_C();
			break;
		case 2:
			hw_C_bonus();
			break;
		case 3:
			hw_opencv();
			break;
		case 4:
			hw_opencv_bonus();
			break;
		default:
			printf("<<Please enter number 0~4!!>>\n\n");
			break;
		}
		if (stop == 1)break;
	}
}