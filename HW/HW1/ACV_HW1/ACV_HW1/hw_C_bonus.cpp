#include <stdio.h>
#include "Header.h"

void hw_C_bonus() {
	// initial variable
	unsigned char* image = bmp_read("input image/InputImage1.bmp");
	int width = 512;
	int height = 512;
	unsigned char* img_onehalf = nearest_neighbor(image, width, height, width * 0.5, height * 0.5);
	unsigned char* img_double = nearest_neighbor(image, width, height, width * 2, height * 2);

	// Generate a color negative image
	unsigned char* img_neg_onehalf = negative(img_onehalf, width * 0.5, height * 0.5);
	unsigned char* img_neg_double = negative(img_double, width * 2, height * 2);

	// Split and reassemble into new image
	unsigned char* img_new_onehalf = gen_hw_img(img_onehalf, width * 0.5, height * 0.5);
	unsigned char* img_new_double = gen_hw_img(img_double, width * 2, height * 2);

	// write file
	bmp_write(img_neg_onehalf, width * 0.5, height * 0.5, "output image/img_neg_onehalf_C.bmp");
	printf("Save img_neg_onehalf_C.bmp successfully...\n");
	bmp_write(img_neg_double, width * 2, height * 2, "output image/img_neg_double_C.bmp");
	printf("Save img_neg_double_C.bmp successfully...\n");
	bmp_write(img_new_onehalf, width * 0.5, height * 0.5, "output image/img_new_onehalf_C.bmp");
	printf("Save img_new_onehalf_C.bmp successfully...\n");
	bmp_write(img_new_double, width * 2, height * 2, "output image/img_new_double_C.bmp");
	printf("Save img_new_double_C.bmp successfully...\n\n");
}