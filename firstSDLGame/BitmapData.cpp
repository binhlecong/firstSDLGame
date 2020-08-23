#include "BitmapData.h"

pixel* read_bmp(const char* filename)
{
	if (filename == NULL) 
		return NULL;
	FILE* fp;
	errno_t err = fopen_s(&fp, filename, "rb");
	if (!fp || err)
	{
		std::cout << "!!! Khong tim thay file, vui long nhap lai" << std::endl;
		return NULL;
	}
	rewind(fp);

	bmpHeader header;
	pixel* data;
	int validate = 1;
	
	validate = fread(&header, sizeof(header), 1, fp);

	if (validate != 1)
	{
		std::cout << "!!! Loi khi doc duong dan file" << std::endl;
		return NULL;
	}

	fseek(fp, header.offset, SEEK_SET);

	data = (pixel*)malloc(header.width_px * header.height_px * header.bits_per_pixel / 8);

	validate = fread(data, header.width_px * header.height_px * header.bits_per_pixel / 8, 1, fp);
	if (validate != 1)
	{
		std::cout << "!!! Loi khi doc du lieu anh." << std::endl;
		return NULL;
	}

	fclose(fp);
	return data;
}