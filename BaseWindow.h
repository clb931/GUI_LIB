#ifndef BASEWINDOW_H
#include <Windowsx.h>


void DefRenderFunc()
{

}

template <class T>
class BaseWindow
{
public:
	BaseWindow() :
		m_hInst(GetModuleHandle(NULL)), m_hWnd(nullptr), m_hDC(nullptr),
		m_ClearColor(Color4f::BLACK),
		m_width(0), m_height(0), m_bpp(0),
		m_pixels(nullptr),
		m_title(L"NULL")
	{
		std::wcout << L"BaseWindow::BaseWindow()" << std::endl;
	}
	~BaseWindow()
	{
		std::wcout << L"BaseWindow::~BaseWindow()" << std::endl;

		if (m_pixels)
			VirtualFree(m_pixels, NULL, MEM_RELEASE);
	}

	bool Create(LPWSTR title, int width, int height, int bpp = 32)
	{
		std::wcout << L"BaseWindow::Create()<" << ClassName() << L">" << std::endl;

		if (m_width < 0 || m_height < 0 || m_bpp < 0)
			return false;

		m_title = title;
		m_width = width;
		m_height = height;
		m_bpp = bpp;

		m_bmpInfo.bmiHeader.biSize = sizeof(m_bmpInfo.bmiHeader);
		m_bmpInfo.bmiHeader.biPlanes = 1;
		m_bmpInfo.bmiHeader.biBitCount = m_bpp;
		m_bmpInfo.bmiHeader.biCompression = BI_RGB;

		m_hWnd = CreateWindowExW(NULL,
			ClassName(), m_title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			width, height,
			NULL, NULL, m_hInst, this);

		if(!m_hWnd) {
			std::wcout << L"*** ERROR (" << GetLastError() << L") *** BaseWindow::BaseWindow() CreateWindowExW" << std::endl;
			return false;
		}

		UpdateWindow(m_hWnd);
		ShowWindow(m_hWnd, SW_SHOW);

		m_hDC = GetDC(m_hWnd);

		return Resize(width, height);
	}

	int Run()
	{
		std::wcout << L"BaseWindow::Run()" << std::endl;

		MSG msg = {};
		while (GetMessageW(&msg, NULL, 0, 0)) {
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessageW(&msg);

			m_RenderFunction();
		}

		return (int)msg.wParam;
	}

	bool Resize(int width, int height)
	{
		std::wcout << "Window::Resize(" << width << ", " << height << ")" << std::endl;

		if (width <= 0 || height <= 0)
			return false;

		m_width = m_bmpInfo.bmiHeader.biWidth = width;
		m_height = m_bmpInfo.bmiHeader.biHeight = height;

		if (m_pixels)
			VirtualFree(m_pixels, NULL, MEM_RELEASE);

		m_pixels = VirtualAlloc(NULL, m_width * m_height * m_bpp, MEM_COMMIT, PAGE_READWRITE);

		if(!m_pixels)
			return false;

		return true;
	}

	void Clear()
	{
		unsigned int *pixels32 = (unsigned int *)m_pixels;
		int end = (m_width * m_height * m_bpp) / 32;

		for(int i = 0; i < end; ++i)
			pixels32[i] = m_ClearColor.ToColor32();
	}

	void Flip()
	{
		if(!m_pixels)
			return;

		StretchDIBits(m_hDC,
			0, 0, m_width, m_height,
			0, 0, m_width, m_height,
			m_pixels, &m_bmpInfo,
			DIB_RGB_COLORS, SRCCOPY);
	}

	static LRESULT CALLBACK
	WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT result = 0;
		T *pThis = NULL;

		if(msg == WM_NCCREATE) {
			CREATESTRUCT *pCreate = (CREATESTRUCT*)lParam;
			pThis = (T*)pCreate->lpCreateParams;
			SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->m_hWnd = hWnd;
		} else {
			pThis = (T*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
		}

		if(pThis) {
			switch(msg) {
				case WM_SIZE: {
					pThis->Resize(LOWORD(lParam), HIWORD(lParam));
				} break;

				case WM_MOUSEMOVE: {
					pThis->m_mouseX = GET_X_LPARAM(lParam);
					pThis->m_mouseY = GET_Y_LPARAM(lParam);
					pThis->m_mouseFlags = 0;
				} break;

				case WM_LBUTTONDOWN:
				case WM_MBUTTONDOWN:
				case WM_RBUTTONDOWN: {
					pThis->m_mouseX = GET_X_LPARAM(lParam);
					pThis->m_mouseY = GET_Y_LPARAM(lParam);
					pThis->m_mouseFlags = wParam;
				} break;

				case WM_LBUTTONUP:
				case WM_MBUTTONUP:
				case WM_RBUTTONUP: {
					pThis->m_mouseX = GET_X_LPARAM(lParam);
					pThis->m_mouseY = GET_Y_LPARAM(lParam);
					pThis->m_mouseFlags = wParam;
				} break;
			}

			result = pThis->HandleMessage(msg, wParam, lParam);
		} else {
			result = DefWindowProcW(hWnd, msg, wParam, lParam);
		}

		return result;
	}

	void SetRenderFunction(void (*render)(void) = DefRenderFunc)
	{
		m_RenderFunction = render;
	}

	void SetClearColor(Color4f color)
	{
		m_ClearColor = color;
	}

	HWND GetHandle()
	{
		return m_hWnd;
	}

	void *GetPixels()
	{
		return m_pixels;
	}

	int GetWidth()
	{
		return m_width;
	}

	int GetHeight()
	{
		return m_height;
	}

	int GetBPP()
	{
		return m_bpp;
	}

	void GetMousePos(int &x, int &y, int &flags)
	{
		x = m_mouseX;
		y = m_mouseY;
		flags = m_mouseFlags;
	}

protected:
	virtual
	bool Init() = 0;
	virtual LRESULT CALLBACK
	HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	virtual LPCWSTR
	ClassName() const = 0;

	HINSTANCE		m_hInst;
	HWND			m_hWnd;
	HDC 			m_hDC;

	BITMAPINFO 		m_bmpInfo;
	Color4f			m_ClearColor;
	int 			m_width, m_height, m_bpp;
	void 			*m_pixels;
	void			(*m_RenderFunction)(void);

	LPWSTR			m_title;
	int 			m_mouseX, m_mouseY, m_mouseFlags;
};


#define BASEWINDOW_H
#endif