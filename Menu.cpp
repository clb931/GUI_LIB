#include "Button.h"
#include "BitmapImage.h"
#include "Menu.h"


Menu::Menu() :
	GUIBox(),
	m_text(""), m_bExpanded(false)
{
	std::cout << "Menu::Menu()" << std::endl;
}

Menu::Menu(std::string text, int x, int y, int width, int height) :
	GUIBox(x, y, text.length() * 16 + 16, height),
	m_text(text), m_bExpanded(false)
{
	std::cout << "Menu::Menu(" << m_text.c_str() << ")" << std::endl;
}

Menu::~Menu()
{
	std::cout << "Menu::~Menu()" << std::endl;
}

bool Menu::Update(int mouse_x, int mouse_y, int mouse_flags)
{
	if(!m_bEnabled)
		return false;

	GUIBox::Update(mouse_x, mouse_y, mouse_flags);

	if (m_bExpanded)
		for(auto button : m_Buttons)
			m_bHighlighted |= button->Update(mouse_x, mouse_y, mouse_flags);

	if((mouse_flags & MK_LBUTTON) && m_bHighlighted)
		m_bExpanded = true;
	else if (!m_bHighlighted)
		m_bExpanded = false;

	return m_bHighlighted;
}

void Menu::Draw(void *target_pixels, int target_width, int target_height, int target_bpp, BitmapImage *font)
{
	if (!m_bVisible)
		return;

	GUIBox::Draw(target_pixels, target_width, target_height, target_bpp);

	if(font)
		DrawString(m_text, font, m_x + 8, m_y + 8, m_width, m_height, target_pixels, target_width, target_height);

	if(m_bExpanded)
		for(auto button : m_Buttons)
			button->Draw(target_pixels, target_width,  target_height, target_bpp, font);
}

void Menu::AddButton(Button *pButton)
{
	m_Buttons.push_back(pButton);
	m_Buttons.back()->SetPosition(m_x, m_y + (m_Buttons.size() * 32));
}

void Menu::SetExpanded(bool bExpanded)
{
	m_bExpanded = bExpanded;
}