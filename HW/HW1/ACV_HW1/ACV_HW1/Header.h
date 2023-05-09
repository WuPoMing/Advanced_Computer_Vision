void hw_C();
void hw_C_bonus();
void hw_opencv();
void hw_opencv_bonus();

unsigned char* bmp_read(const char* filename);
int bmp_write(unsigned char* image, int xsize, int ysize, const char* filename);
unsigned char* negative(unsigned char* image, int width, int height);
unsigned char* rotate90(unsigned char* image, int width, int height);
unsigned char* rotate270(unsigned char* image, int width, int height);
unsigned char* gen_hw_img(unsigned char* image, int width, int height);
unsigned char* nearest_neighbor(unsigned char* img, int src_width, int src_height, int dst_width, int dst_height);