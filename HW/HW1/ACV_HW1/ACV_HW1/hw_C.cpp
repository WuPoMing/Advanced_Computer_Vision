#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

void hw_C() {
	// initial variable
	unsigned char* image = bmp_read("input image/InputImage1.bmp");
	int width = 512;
	int height = 512;

	// Generate a color negative image
	unsigned char* img_neg = negative(image, width, height);

	// Split and reassemble into new image
	unsigned char* img_new = gen_hw_img(image, width, height);

	// write file
	bmp_write(img_neg, 512, 512, "output image/img_neg_C.bmp");
	printf("Save img_neg_C.bmp successfully...\n");
	bmp_write(img_new, 512, 512, "output image/img_new_C.bmp");
	printf("Save img_new_C.bmp successfully...\n\n");
}