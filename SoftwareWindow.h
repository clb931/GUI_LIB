#ifndef SOFTWAREWINDOW_H
#include "BaseWindow.h"


class Window : public BaseWindow<Window>
{
public:
	Window();
	Window(LPWSTR title, int width, int height, int bpp = 32);

	bool Init();

	LRESULT CALLBACK
	HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	LPCWSTR ClassName() const;
};


#define SOFTWAREWINDOW_H
#endif