#include "BitmapImage.h"

unsigned int texture_count = 0;

BitmapImage::BitmapImage()
{
	std::cout << "BitmapImage::BitmapImage()" << std::endl;

	data = nullptr;
}

BitmapImage::BitmapImage(const char *file_path) : data(nullptr)
{
	std::cout << "BitmapImage::BitmapImage(" << m_Name << ")" << std::endl;

	Open(file_path);
}

BitmapImage::~BitmapImage()
{
	std::cout << "BitmapImage::~BitmapImage(" << m_Name << ")" << std::endl;

	if (data)
		free(data);
}

void BitmapImage::Open(const char *file_path)
{
	char str[256] = "";
	FILE *pFile;
	BMP colors;

	std::cout << "BitmapImage::Open(" << file_path << ")" << std::endl;
	fopen_s(&pFile, file_path, "rb");
	if (pFile) {
		fseek(pFile, sizeof(short) * 9, SEEK_SET);
		fread(&width, sizeof(int), 1, pFile);
		fread(&height, sizeof(int), 1, pFile);
		fseek(pFile, sizeof(short), SEEK_CUR);
		fread(&bpp, sizeof(short), 1, pFile);
		fseek(pFile, sizeof(int) * 6, SEEK_CUR);

		std::cout << "\tDimensions: " << width << " x " << height << std::endl;
		std::cout << "\tBPP: " << bpp << std::endl;

		if (bpp <= 8)
			for (unsigned int a = 0; a < bpp; a++)
				fseek(pFile, sizeof(int), SEEK_CUR);

		data = (unsigned char*)malloc(width * height * 4);
		memset(data, 0, width * height * 4);

		std::cout << "\tSize: " << ((width * height) / 1024.0f) << "KB" << std::endl;
		unsigned int j = 0;
		for (unsigned int i = 0; i < width * height; ++i) {
			fread(&colors, sizeof(BMP), 1, pFile);

			data[j + 0] = colors.r;
			data[j + 1] = colors.g;
			data[j + 2] = colors.b;
			data[j + 3] = 0;

			j += 4;
		}

		id = texture_count++;
		strcpy_s(m_Name, 64, file_path);

		fclose(pFile);
	}
	else {
		std::cout << "*** Error. File does not exist." << std::endl;
	}
}

void BitmapImage::SetName(const char *name)
{
	strcpy_s(m_Name, 64, name);
}

char *BitmapImage::GetName()
{
	return m_Name;
}