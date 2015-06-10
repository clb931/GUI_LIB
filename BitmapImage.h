#ifndef BITMAP_IMAGE_H


class BitmapImage
{
public:
	BitmapImage();
	explicit BitmapImage(const char *file_path);
	~BitmapImage();

	void Open(const char *file_path);
	void SetName(const char *name);
	char *GetName();

	unsigned char *data;
	unsigned int width;
	unsigned int height;
	unsigned int bpp;
	unsigned int id;

private:
	struct BMP { unsigned char b, g, r; };

	char m_Name[64];
};


#define BITMAP_IMAGE_H
#endif