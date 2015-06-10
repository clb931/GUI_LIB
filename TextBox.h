#ifndef TEXTBOX_H


class BitmapImage;
class GUIBox;
class Menu;

class TextBox : public GUIBox
{
public:
	TextBox(int x, int y, int width, int height);
	TextBox(std::string text, int x, int y, int width, int height);
	~TextBox();

	bool Update(int mouse_x, int mouse_y, int mouse_flags);
	void Draw(void *target_pixels, int target_width, int target_height, int target_bpp, BitmapImage *font);

	void SetEditable(bool bEditable);
	void Append(std::string text);
	void Insert(int position, std::string text);
	void SetText(std::string text);

private:
	std::string m_text;

	bool m_bEditable;
	Menu m_ContextMenu;
};


#define TEXTBOX_H
#endif