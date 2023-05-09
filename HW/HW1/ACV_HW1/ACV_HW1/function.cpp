#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Header.h"

unsigned char* bmp_read(const char* filename) {
	char fname_bmp[128];
	FILE* fp;
	unsigned char* image;
	unsigned char header[54];

	sprintf(fname_bmp, "%s", filename);

	fp = fopen(fname_bmp, "rb");
	if (fp == NULL) {
		puts("Loading File Error!");
		system("PAUSE");
		exit(0);
	}

	fread(header, sizeof(unsigned char), 54, fp);

	int width = header[18] + header[19] * pow(2, 8) + header[20] * pow(2, 16) + header[21] * pow(2, 32);
	int height = header[22] + header[23] * pow(2, 8) + header[24] * pow(2, 16) + header[25] * pow(2, 32);

	image = new unsigned char[width * height * 3];
	fread(image, sizeof(unsigned char), (size_t)(long)width * height * 3, fp);

	fclose(fp);
	return image;
}

int bmp_write(unsigned char* image, int xsize, int ysize, const char* filename) {
	unsigned char header[54] = {
		0x42, 0x4d, 0, 0, 0, 0, 0, 0, 0, 0,
		54, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0
	};
	long file_size = (long)xsize * (long)ysize * 3 + 54;
	long width, height;
	char fname_bmp[128];
	FILE* fp;

	header[2] = (unsigned char)(file_size & 0x000000ff);
	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff;

	width = xsize;
	header[18] = width & 0x000000ff;
	header[19] = (width >> 8) & 0x000000ff;
	header[20] = (width >> 16) & 0x000000ff;
	header[21] = (width >> 24) & 0x000000ff;

	height = ysize;
	header[22] = height & 0x000000ff;
	header[23] = (height >> 8) & 0x000000ff;
	header[24] = (height >> 16) & 0x000000ff;
	header[25] = (height >> 24) & 0x000000ff;

	sprintf(fname_bmp, "%s", filename);

	if (!(fp = fopen(fname_bmp, "wb")))
		return -1;

	fwrite(header, sizeof(unsigned char), 54, fp);
	fwrite(image, sizeof(unsigned char), (size_t)(long)xsize * ysize * 3, fp);
	fclose(fp);
	return 0;
}

unsigned char* negative(unsigned char* image, int width, int height) {
	unsigned char* img_neg = new unsigned char[width * height * 3];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				*(img_neg + (width * y + x) * 3 + c) = 255 - *(image + (width * y + x) * 3 + c);
			}
		}
	}
	return img_neg;
}

unsigned char* rotate90(unsigned char* image, int width, int height) {
	unsigned char* tmp = new unsigned char[width * height * 3];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				*(tmp + (width * y + x) * 3 + c) = *(image + (width * x + (width - y)) * 3 + c);
			}
		}
	}
	return tmp;
}

unsigned char* rotate270(unsigned char* image, int width, int height) {
	unsigned char* tmp = new unsigned char[width * height * 3];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				*(tmp + (width * y + x) * 3 + c) = *(image + (width * (height - x) + y) * 3 + c);
			}
		}
	}
	return tmp;
}

unsigned char* gen_hw_img(unsigned char* image, int width, int height) {
	unsigned char* img_new = new unsigned char[width * height * 3];
	unsigned char* tmp = rotate90(image, width, height);
	unsigned char* tmp1 = rotate270(image, width, height);

	int x1 = 0, y1 = 0;
	int x2 = width - 1, y2 = 0;
	int x3 = 0, y3 = height - 1;
	int x4 = width - 1, y4 = height - 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			for (int c = 0; c < 3; c++) {
				if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) >= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) <= 0) {
					*(img_new + (width * y + x) * 3 + c) = *(tmp1 + (width * y + x) * 3 + c);
				}
				if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) >= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) >= 0) {
					*(img_new + (width * y + x) * 3 + c) = *(tmp + (width * y + x) * 3 + c);
				}
				if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) <= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) >= 0) {
					*(img_new + (width * y + x) * 3 + c) = *(tmp1 + (width * y + x) * 3 + c);
				}
				if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) <= 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) <= 0) {
					*(img_new + (width * y + x) * 3 + c) = *(tmp + (width * y + x) * 3 + c);
				}
				if ((y - y4) * (x1 - x4) - (x - x4) * (y1 - y4) == 0 && (y - y3) * (x2 - x3) - (x - x3) * (y2 - y3) == 0) {
					*(img_new + (width * y + x) * 3 + c) = *(image + (width * y + x) * 3 + c);
				}
			}
		}
	}

	return img_new;
}

unsigned char* nearest_neighbor(unsigned char* img, int src_width, int src_height, int dst_width, int dst_height) {
	unsigned char* new_img = new unsigned char[dst_width * dst_height * 3];

	for (int y = 0; y < dst_height; y++) {
		for (int x = 0; x < dst_width; x++) {
			for (int c = 0; c < 3; c++) {
				int srcX = round(x * src_width / dst_width);
				int srcY = round(y * src_height / dst_height);
				*(new_img + (y * dst_width + x) * 3 + c) = *(img + (src_width * srcY + srcX) * 3 + c);
			}
		}
	}
	return new_img;
}