#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define BMP_HEADER_SIZE 54
#define DIB_HEADER_SIZE 40
typedef unsigned char uChar;

#pragma pack(push)  
#pragma pack(1)    

struct bmpHeader
{
	uint16_t		type;
	uint32_t		size;
	uint16_t		reserved1;
	uint16_t		reserved2;
	uint32_t		offset;
	uint32_t		dib_header_size;
	int32_t			width_px;
	int32_t			height_px;
	uint16_t		num_planes;
	uint16_t		bits_per_pixel;
	uint32_t		compression;
	uint32_t		image_size_bytes;
	unsigned long	x_resolution_ppm;
	unsigned long	y_resolution_ppm;
	uint32_t		num_colors;
	uint32_t		important_colors;
};
  
struct pixel
{
	unsigned char 	blue;
	unsigned char 	green;
	unsigned char 	red;
};
   
struct bmpImage
{
	bmpHeader		header;
	pixel*			data;
};

pixel* read_bmp(const char* filename);