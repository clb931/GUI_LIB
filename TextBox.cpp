#include "BitmapImage.h"
#include "Button.h"
#include "Menu.h"
#include "TextBox.h"

Button button("Context Menu", nullptr);

TextBox::TextBox(int x, int y, int width, int height) :
	GUIBox(x, y, width, height),
	m_text(""), m_bEditable(false)
{
	std::cout << "TextBox::TextBox()" << std::endl;
	m_nColor = Color4f(0.1f, 0.1f, 0.1f);
	m_hColor = Color4f(0.05f, 0.05f, 0.05f);

	button.SetColor(Color4f::BLACK);
	button.SetHighlightColor(Color4f::DARK_GRAY);
	m_ContextMenu.AddButton(&button);
}

TextBox::TextBox(std::string text, int x, int y, int width, int height) :
	GUIBox(x, y, width, height),
	m_text(text), m_bEditable(false)
{
	std::cout << "TextBox::TextBox()" << std::endl;
	m_nColor = Color4f(0.1f, 0.1f, 0.1f);
	m_hColor = Color4f(0.05f, 0.05f, 0.05f);
}

TextBox::~TextBox()
{
	std::cout << "TextBox::~TextBox()" << std::endl;
}

bool TextBox::Update(int mouse_x, int mouse_y, int mouse_flags)
{
	if(!m_bEnabled)
		return false;

	GUIBox::Update(mouse_x, mouse_y, mouse_flags);

	if((mouse_flags & MK_RBUTTON) && m_bHighlighted) {
		m_ContextMenu.SetPosition(mouse_x, mouse_y);
		m_ContextMenu.SetVisible(true);
		std::cout << "Context Menu" << std::endl;
	} else if(!m_ContextMenu.IsHighlighted()) {
		m_ContextMenu.SetVisible(false);
	}

	return m_bHighlighted;
}

void TextBox::Draw(void *target_pixels, int target_width, int target_height, int target_bpp, BitmapImage *font)
{
	if (!m_bVisible)
		return;

	GUIBox::Draw(target_pixels, target_width, target_height, target_bpp);

	if(font)
		DrawString(m_text, font, m_x + 8, m_y + 8, m_width, m_height, target_pixels, target_width, target_height);

	if(m_ContextMenu.IsVisible())
		m_ContextMenu.Draw(target_pixels, target_width, target_height, target_bpp, font);
}

void TextBox::SetEditable(bool bEditable)
{
	m_bEditable = bEditable;
}

void TextBox::Append(std::string text)
{
	m_text.append(text);
}

void TextBox::Insert(int position, std::string text)
{
	m_text.insert(position, text);
}

void TextBox::SetText(std::string text)
{
	m_text = text;
}