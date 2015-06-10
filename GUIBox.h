#ifndef GUIBOX_H


class Window;
class Color4f;

class GUIBox
{
public:
	GUIBox();
	GUIBox(int x, int y, int width = 96, int height = 32);
	~GUIBox();

	bool Update(int mouse_x, int mouse_y, int mouse_flags);
	void Draw(void *pixels, int target_width, int target_height, int target_bpp);

	void SetVisible(bool bVisible);
	void SetHighlighted(bool bHighlighted);
	void SetEnabled(bool bEnabled);
	void SetColor(Color4f color);
	void SetHighlightColor(Color4f color);
	void SetPosition(int x, int y);
	void SetSize(int width, int height);

	bool IsVisible();
	bool IsHighlighted();
	bool IsEnabled();
	void GetPosition(int &x, int &y);
	void GetSize(int &width, int &height);

protected:
	Window 	*m_window;
	bool 	m_bVisible;
	bool 	m_bHighlighted;
	bool 	m_bEnabled;
	Color4f	*m_color, m_hColor, m_nColor;
	int 	m_x, m_y;
	int 	m_width, m_height;
};


#define GUIBOX_H
#endif