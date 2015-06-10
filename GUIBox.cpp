#include "Color4f.h"
#include "SoftwareWindow.h"
#include "GUIBox.h"


GUIBox::GUIBox() :
	m_bVisible(true), m_bHighlighted(false), m_bEnabled(true),
	m_color(&m_nColor), m_nColor(Color4f::WHITE), m_hColor(Color4f::LIGHT_GRAY),
	m_x(0), m_y(0), m_width(96), m_height(24)
{
	std::wcout << L"GUIBox::GUIBox()" << std::endl;
}

GUIBox::GUIBox(int x, int y, int width, int height) :
	m_bVisible(true), m_bHighlighted(false), m_bEnabled(true),
	m_color(&m_nColor), m_nColor(Color4f::WHITE), m_hColor(Color4f::LIGHT_GRAY),
	m_x(x), m_y(y), m_width(width), m_height(height)
{
	std::wcout << L"GUIBox::GUIBox()" << std::endl;
}

GUIBox::~GUIBox()
{
	std::wcout << L"GUIBox::~GUIBox()" << std::endl;
}

bool GUIBox::Update(int mouse_x, int mouse_y, int mouse_flags)
{
	if(!m_bEnabled)
		return false;

	if(mouse_x > m_x && mouse_x < m_x + m_width &&
		mouse_y > m_y && mouse_y < m_y + m_height + 1) {
		m_color = &m_hColor;
		m_bHighlighted = true;
	} else {
		m_color = &m_nColor;
		m_bHighlighted = false;
	}

	return m_bHighlighted;
}

void GUIBox::Draw(void *target_pixels, int target_width, int target_height, int target_bpp)
{
	if (!m_bVisible)
		return;

	unsigned int *pixels = (unsigned int *)target_pixels;
	int width = m_x + m_width;
	int height = target_height - m_y;

	for(int y = height - m_height; y < height; ++y)
		if(y >= 0 && y < target_height)
			for(int x = m_x; x < width; ++x)
				if(x >= 0 && x < target_width)
					pixels[y * target_width + x] = m_color->ToColor32();
}

void GUIBox::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

void GUIBox::SetHighlighted(bool bHighlighted)
{
	m_bHighlighted = bHighlighted;
}

void GUIBox::SetEnabled(bool bEnabled)
{
	m_bEnabled = bEnabled;
}

void GUIBox::SetColor(Color4f color)
{
	m_nColor = color;
}

void GUIBox::SetHighlightColor(Color4f color)
{
	m_hColor = color;
}

void GUIBox::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void GUIBox::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

bool GUIBox::IsVisible()
{
	return m_bVisible;
}

bool GUIBox::IsHighlighted()
{
	return m_bHighlighted;
}

bool GUIBox::IsEnabled()
{
	return m_bEnabled;
}

void GUIBox::GetPosition(int &x, int &y)
{
	x = m_x;
	y = m_y;
}

void GUIBox::GetSize(int &width, int &height)
{
	width = m_width;
	height = m_height;
}

void BitmapCopy(void *src, int src_x, int src_y, int src_w, int src_h, int src_width, int src_height, void *dst, int dst_x, int dst_y, int dst_width, int dst_height)
{
	if((unsigned)src_x > src_width || (unsigned)src_y > src_height ||
	   (unsigned)dst_x > dst_width || (unsigned)dst_y > dst_height)
		return;

	unsigned int *src_pixels = (unsigned int *)src;
	unsigned int *dst_pixels = (unsigned int *)dst;

	for(int y = 0; y < src_h; ++y) {
		if(y < dst_height) {
			for(int x = 0; x < src_w; ++x) {
				if(x < dst_width) {
					unsigned int sp = src_pixels[(y + src_y) * src_width + (x + src_x)];
						dst_pixels[(y + dst_y) * dst_width + (x + dst_x)] = sp;
				}
			}
		}
	}
}

void DrawChar(char c, BitmapImage *font, int x_pos, int y_pos, void *target_pixels, int target_width, int target_height)
{
	unsigned int char_width = font->width / 16;
	unsigned int char_height = font->height / 16;

	unsigned int char_x = c % 16;
	char_x *= char_width;
	unsigned int char_y = c / 16;
	char_y = font->height - (char_y + 1) * char_height;
	unsigned int char_size = char_width * char_height;

	BitmapCopy(font->data, char_x, char_y, char_width, char_height, font->width, font->height,
		target_pixels, x_pos, target_height - char_height - y_pos, target_width, target_height);
}

void DrawString(std::string text, BitmapImage *font, int x_pos, int y_pos, int width, int height, void *target_pixels, int target_width, int target_height)
{
	int x = x_pos, y = y_pos;
	unsigned int *pixels = (unsigned int *)target_pixels;
	for(int i = 0; i < text.length(); ++i) {
		char c = text.at(i);

		if(c == '\n' || c == '\r') {
			y += 16;
			x = x_pos;
			continue;
		} else if(c == '\t') {
			c = ' ';
			for(int i = 0; i < 4; ++i) {
				DrawChar(c, font, x, y, target_pixels, target_width, target_height);
				x += 16;
			}
			continue;
		}

		DrawChar(c, font, x, y, target_pixels, target_width, target_height);
		x += 16;
	}
}