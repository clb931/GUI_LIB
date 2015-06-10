#include "Color4f.h"
#include "GUIBox.h"
#include "SoftwareWindow.h"


Window::Window() :
	BaseWindow<Window>()
{

}

Window::Window(LPWSTR title, int width, int height, int bpp) :
	BaseWindow<Window>()
{
	if(!Init())
		return;

	if(Create(title, width, height, bpp))
		return;

	m_hWnd = nullptr;
}

bool Window::Init()
{
	std::wcout << L"Window::Init()" << std::endl;

	WNDCLASSEXW wcex = {};
	wcex.cbSize = sizeof(WNDCLASSEXW);
	wcex.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = m_hInst;
	wcex.lpszClassName = ClassName();
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	if(!RegisterClassExW(&wcex)) {
		std::wcout << L"*** ERROR (" << GetLastError() << L") *** BaseWindow::BaseWindow() RegisterClassExW" << std::endl;
		return false;
	}

	return true;
}

LRESULT CALLBACK
Window::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch(msg) {
		case WM_CLOSE: {
			PostQuitMessage(0);
		} break;

		default: {
			result = DefWindowProcW(m_hWnd, msg, wParam, lParam);
		} break;
	}

	return result;
}

LPCWSTR Window::ClassName() const
{
	return L"SoftwareWindowClass";
}