#include <stdio.h>
#include <string.h>
#include <math.h>
#define PI 3.1415926535897
#define HEIGHT_WIDTH 1000
typedef struct BMPSIN BMPSIN;
static unsigned char rgb[HEIGHT_WIDTH][HEIGHT_WIDTH][3];
void repeat(int count, int m, int n)
{
	if ((int)(400 / pow(2, count) )!= 0)
	{
	int x = 0, y = 400;
	while (y !=(int)(400 / pow(2, count+1)))
	{
		x += y;
		y /= 2;
	}
        if((int)(m / pow(2, count) +x)<HEIGHT_WIDTH && (int)(n / pow(2, count) +x)<HEIGHT_WIDTH){
	rgb[(int)(m / pow(2, count) +x)][(int)(n / pow(2, count) +x)][1] = (unsigned char)127;
        rgb[(int)(m / pow(2, count) +x)][(int)(n / pow(2, count) +x)][2] = (unsigned char)255;
	rgb[(int)(n / pow(2, count) +x)][(int)(m / pow(2, count) +x)][1] = (unsigned char)127;
        rgb[(int)(n / pow(2, count) +x)][(int)(m / pow(2, count) +x)][2] = (unsigned char)255;
}
}
}

int main(int argc, char **argv)
{
	int w = HEIGHT_WIDTH, h = HEIGHT_WIDTH;
	unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	int filesize = 54 + 3 * HEIGHT_WIDTH * HEIGHT_WIDTH;
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	FILE *f = fopen(argv[1], "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	float i;
	for (i = 0; i < 100; i += 0.0001)
	{
		int m = 400+ 200 * sin(i), n =400+ 400 * cos(i);
		int rep;
		for (rep = 1; rep < 10; rep++)
                {
			repeat(rep, m, n);
                        repeat(rep, m, (int)(400+200*cos(i)));
                        repeat(rep, n, (int)(400+400*sin(i)));
                }
	}
	fwrite(rgb, sizeof(rgb), 1, f);
	fclose(f);
	return 0;
}
