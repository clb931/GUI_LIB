#include "BitmapImage.h"
#include "Button.h"
#include "GUIBox.h"
#include "Menu.h"
#include "SoftwareWindow.h"
#include "GUI.h"


GUI::GUI() :
	m_pWindow(nullptr),
	m_targetPixels(nullptr),
	m_targetWidth(0), m_targetHeight(0), m_targetBPP(32)
{
	std::wcout << L"GUI::GUI()" << std::endl;
}

GUI::GUI(Window *pWindow)
{
	std::wcout << L"GUI::GUI()" << std::endl;

	m_pWindow = pWindow;
	m_targetPixels = m_pWindow->GetPixels();
	m_targetWidth = m_pWindow->GetWidth();
	m_targetHeight = m_pWindow->GetHeight();
	m_targetBPP = m_pWindow->GetBPP();
}

GUI::~GUI()
{
	std::wcout << L"GUI::~GUI()" << std::endl;
}

void GUI::LoadFont(const char *file_path)
{
	m_font.Open(file_path);
}

void GUI::Update()
{
	int x, y, flags;
	m_pWindow->GetMousePos(x, y, flags);

	for(auto button : m_Buttons)
		if(button->Update(x, y, flags))
			return;

	for(auto menu : m_Menus)
		if(menu->Update(x, y, flags))
			return;

	for(auto tb : m_TextBoxs)
		if(tb->Update(x, y, flags))
			return;

	for(auto box : m_GUIBoxes)
		if(box->Update(x, y, flags))
			return;
}

void GUI::Draw()
{
	m_targetWidth = m_pWindow->GetWidth();
	m_targetHeight = m_pWindow->GetHeight();

	for(auto box : m_GUIBoxes)
		box->Draw(m_targetPixels, m_targetWidth, m_targetHeight, m_targetBPP);

	for(auto tb : m_TextBoxs)
		tb->Draw(m_targetPixels, m_targetWidth, m_targetHeight, m_targetBPP, &m_font);

	for(auto button : m_Buttons)
		button->Draw(m_targetPixels, m_targetWidth, m_targetHeight, m_targetBPP, &m_font);

	for(auto menu : m_Menus)
		menu->Draw(m_targetPixels, m_targetWidth, m_targetHeight, m_targetBPP, &m_font);
}

void GUI::AddTextBox(TextBox *pTextBox)
{
	m_TextBoxs.push_back(pTextBox);
}

void GUI::AddMenu(Menu *pMenu)
{
	m_Menus.push_back(pMenu);
}

void GUI::AddButton(Button *pButton)
{
	m_Buttons.push_back(pButton);
}

void GUI::AddGUIBox(GUIBox *pBox)
{
	m_GUIBoxes.push_back(pBox);
}