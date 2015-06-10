#ifndef BUTTON_H


class BitmapImage;
class GUIBox;

class Button : public GUIBox
{
public:
	Button();
	Button(std::string text, void (*callback)(void), int x = 0, int y = 0, int width = 96, int height = 32);
	~Button();

	bool Update(int mouse_x, int mouse_y, int mouse_flags);
	void Draw(void *target_pixels, int target_width, int target_height, int target_bpp, BitmapImage *font);

private:
	std::string m_text;
	void (*m_callback)(void);
};


#define BUTTON_H
#endif