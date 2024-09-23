#include "BMP_READ.h"

void BMP_READ::openBMP(const char* fname)
{
	bmp.open(fname, std::ios::in | std::ios::binary);
	if (!bmp) {
		std::cout << "No open file\n";
		exit(1);
	}else {
		bmp.read((char*)&file_header, sizeof(file_header));
		if (file_header.bfType != 0x4D42) {
			std::cout << "Error: Invalid file format1" << std::endl;
			exit(1);
		}
		bmp.read((char*)&bmp_info_header, sizeof(bmp_info_header));
		data = new unsigned char[bmp_info_header.biHeight * bmp_info_header.biWidth];
		if (bmp_info_header.biBitCount == 32) {
			Read_bmp32(fname);
		}
		else {
			Read_bmp24(fname);
		}
	}
	
}

void BMP_READ::Create_bmp24(const char* fname)
{
	bmp.open(fname, std::ios::out | std::ios::binary);
	if (!bmp) {
		std::cout << "No open file\n";
		exit(1);
	}
	else {
		unsigned char dt[] = { 0xFF,0x00,0xFF };
		file_header.bfType = 0x4D42;
		file_header.bfSize = sizeof(file_header) + sizeof(file_header) + sizeof(dt) * 400;
		file_header.bfReserved2 = 0;
		file_header.bfReserved1 = 0;
		file_header.bfOffBits = sizeof(file_header) + sizeof(file_header);

		bmp_info_header.biSize = sizeof(bmp_info_header);
		bmp_info_header.biWidth = 20;
		bmp_info_header.biHeight = 20;
		bmp_info_header.biBitCount = 24;
		bmp_info_header.biPlanes = 1;
		bmp_info_header.biCompression = 0;
		bmp_info_header.biSizeImage = sizeof(dt) * 400;
		bmp_info_header.biXPelsPerMeter = 0;
		bmp_info_header.biYPelsPerMeter = 0;
		bmp_info_header.biClrImportant = 0;
		bmp_info_header.biClrUsed = 0;

		bmp.write((const char*)&file_header, sizeof(file_header));
		bmp.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
		srand(time(0));
		for (int i = 0; i < bmp_info_header.biHeight; i++) {
			for (int j = 0; j < bmp_info_header.biWidth; j++) {
				if (rand() % 2) { 
					dt[0] = 255;
					dt[1] = 255;
					dt[2] = 255;
				}
				else { 
					dt[0] = 0;
					dt[1] = 0;
					dt[2] = 0;
				}
				bmp.write((const char*)&dt, sizeof(dt));
			}
		}
	}
	bmp.close();
}

void BMP_READ::Create_bmp32(const char* fname)
{
	bmp.open(fname, std::ios::out | std::ios::binary);
	if (!bmp) {
		std::cout << "No open file\n";
		exit(1);
	}
	else {
		unsigned char dt[] = {0xFF,0xFF,0xFF,0x00 };
		file_header.bfType = 0x4D42;
		file_header.bfSize = sizeof(file_header) + sizeof(file_header) + sizeof(dt) * 400;
		file_header.bfReserved2 = 0;
		file_header.bfReserved1 = 0;
		file_header.bfOffBits = sizeof(file_header) + sizeof(file_header);

		bmp_info_header.biSize = sizeof(bmp_info_header);
		bmp_info_header.biWidth = 20;
		bmp_info_header.biHeight = 20;
		bmp_info_header.biBitCount = 32;
		bmp_info_header.biPlanes = 1;
		bmp_info_header.biCompression = 0;
		bmp_info_header.biSizeImage = sizeof(dt) * 400;
		bmp_info_header.biXPelsPerMeter = 0;
		bmp_info_header.biYPelsPerMeter = 0;
		bmp_info_header.biClrImportant = 0;
		bmp_info_header.biClrUsed = 0;

		bmp.write((const char*)&file_header,sizeof(file_header));
		bmp.write((const char*)&bmp_info_header, sizeof(bmp_info_header));
		srand(time(0));
		for (int i = 0; i < bmp_info_header.biHeight; i++) {
			for (int j = 0; j < bmp_info_header.biWidth; j++) {
				if (rand() % 2) {
					dt[0] = 255;
					dt[1] = 255;
					dt[2] = 255;
					dt[3] = 0;
				}
				else {
					dt[0] = 0;
					dt[1] = 0;
					dt[2] = 0;
					dt[3] = 0;
				}
				bmp.write((const char*)&dt, sizeof(dt));
			}
		}
	}
	bmp.close();
}

void BMP_READ::Read_bmp24(const char* fname)
{
	bmp.seekg(sizeof(file_header) + bmp_info_header.biSize, std::ios::beg);
	
	char temp[4],res; int zeron = 0;
	if (bmp_info_header.biWidth % 4) zeron = bmp_info_header.biWidth % 4;
	for (int n = 0; n < bmp_info_header.biHeight; n++)
	{
		for (int m = 0; m < bmp_info_header.biWidth; m++)
		{
			bmp.read(temp, 3);
			if (m % bmp_info_header.biWidth == 0)
			{
				for (int j = 0; j < zeron; j++)
					bmp.read(&res, 1);
			}
			data[n * bmp_info_header.biHeight + m] = temp[0];
		}
	}
}

void BMP_READ::Read_bmp32(const char* fname)
{
	bmp.seekg(sizeof(file_header) + bmp_info_header.biSize, std::ios::beg);

	char temp[4], res; int zeron = 0;
	if (bmp_info_header.biWidth % 4) zeron = bmp_info_header.biWidth % 4;
	for (int n = 0; n < bmp_info_header.biHeight; n++)
	{
		for (int m = 0; m < bmp_info_header.biWidth; m++)
		{
			bmp.read(temp, 4);
			if (m % bmp_info_header.biWidth == 0)
			{
				for (int j = 0; j < zeron; j++)
					bmp.read(&res, 1);
			}
			data[n * bmp_info_header.biHeight + m] = temp[0];
		}
	}

	/*if (bmp_info_header.bmiHeader.biSize >= (sizeof(BITMAPINFO) + sizeof(BITMAPCOREINFO))) {
		bmp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
	}
	else {
		std::cerr << "Warning! The file \"" << fname << "\" does not seem to contain bit mask information\n";
		throw std::runtime_error("Error! Unrecognized file format.");
	}*/

}

void BMP_READ::displayBMP()
{
	for (int n = bmp_info_header.biHeight - 1; n >= 0; n--) {
		for (int m = 0; m < bmp_info_header.biWidth; m++) {
			if (data[n * bmp_info_header.biHeight + m] == 0) { std::cout << (char)219; }
			else {std::cout << (char)32;}
		}std::cout << "\n";
	}
	std::cout << "\n";
}

void BMP_READ::closeBMP()
{
	bmp.close();
}
