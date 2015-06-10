#include "BitmapImage.h"
#include "Button.h"


Button::Button() :
	GUIBox(),
	m_text(""), m_callback(nullptr)
{
	std::cout << "Button::Button()" << std::endl;
}

Button::Button(std::string text, void (*callback)(void), int x, int y, int width, int height) :
	GUIBox(x, y, text.length() * 16 + 16, height),
	m_text(text), m_callback(callback)
{
	std::cout << "Button::Button(" << m_text.c_str() << ")" << std::endl;
}

Button::~Button()
{
	std::cout << "Button::~Button()" << std::endl;
}

bool Button::Update(int mouse_x, int mouse_y, int mouse_flags)
{
	if(!m_bEnabled)
		return false;

	GUIBox::Update(mouse_x, mouse_y, mouse_flags);

	if((mouse_flags & MK_LBUTTON) && m_bHighlighted)
		m_callback();

	return m_bHighlighted;
}

void Button::Draw(void *target_pixels, int target_width, int target_height, int target_bpp, BitmapImage *font)
{
	if (!m_bVisible)
		return;

	GUIBox::Draw(target_pixels, target_width, target_height, target_bpp);

	if(font)
		DrawString(m_text, font, m_x + 8, m_y + 8, m_width, m_height, target_pixels, target_width, target_height);
}