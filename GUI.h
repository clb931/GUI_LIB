#ifndef GUI_H
#include <vector>


class BitmapImage;
class GUIBox;
class Menu;
class TextBox;
class Window;

class GUI
{
public:
	GUI();
	GUI(Window *window);
	~GUI();

	void LoadFont(const char *file_path);

	void Update();
	void Draw();

	void AddTextBox(TextBox *pTextBox);
	void AddMenu(Menu *pMenu);
	void AddButton(Button *pButton);
	void AddGUIBox(GUIBox *pBox);

private:
	Window 					*m_pWindow;
	void 					*m_targetPixels;
	int 					m_targetWidth, m_targetHeight;
	int						m_targetBPP;
	BitmapImage				m_font;

	std::vector<TextBox*>	m_TextBoxs;
	std::vector<Menu*>		m_Menus;
	std::vector<Button*>	m_Buttons;
	std::vector<GUIBox*>	m_GUIBoxes;
};


#define GUI_H
#endif