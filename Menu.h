#ifndef MENU_H
#include <vector>


class Button;
class BitmapImage;
class GUIBox;

class Menu : public GUIBox
{
public:
	Menu();
	Menu(std::string text, int x, int y, int width = 96, int height = 32);
	~Menu();

	void AddButton(Button *pButton);

	bool Update(int mouse_x, int mouse_y, int mouse_flags);
	void Draw(void *target_pixels, int target_width, int target_height, int target_bpp, BitmapImage *font);

	void SetExpanded(bool bExpanded);

private:
	std::string				m_text;
	std::vector<Button*>	m_Buttons;

	bool					m_bExpanded;
};


#define MENU_H
#endif