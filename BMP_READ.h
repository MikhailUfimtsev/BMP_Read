#pragma once
#include<Windows.h>
#include <fstream>
#include <iostream>

class BMP_READ
{
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER bmp_info_header;
	unsigned char* data;
	std::fstream bmp;
	void openBMP(const char* fname);
	void Create_bmp24(const char* fname);
	void Create_bmp32(const char* fname);
	void Read_bmp24(const char* fname);
	void Read_bmp32(const char* fname);
	void displayBMP();
	void closeBMP();
	
public:
	BMP_READ(const char* fname) {
		openBMP(fname);
		displayBMP();
		
		//Create_bmp24(fname);
		//Create_bmp32(fname);
		
		
	}
	~BMP_READ() {
		closeBMP();
		delete[]data;
	}
};

