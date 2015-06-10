#include <Windows.h>
#include <iostream>
#include "Color4f.cpp"
#include "BitmapImage.cpp"
#include "GUIBox.cpp"
#include "TextBox.cpp"
#include "Button.cpp"
#include "Menu.cpp"
#include "SoftwareWindow.cpp"
#include "GUI.cpp"
#include "Font.cpp"


Window 	window(L"GUI-Test", 960, 480);
GUI 	gui(&window);

void render()
{
	window.Clear();

	gui.Update();
	gui.Draw();

	window.Flip();
}

void New()
{
	std::cout << "New()" << std::endl;
}

void Open()
{
	std::cout << "Open()" << std::endl;
}

void Save()
{
	std::cout << "Save()" << std::endl;
}

void SaveAs()
{
	std::cout << "SaveAs()" << std::endl;
}

int WINAPI CALLBACK
wWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PWSTR pCmdLine, int nCmdShow)
{
	std::wcout << L"\n*** Starting Program!\n" << std::endl;

	if(!window.GetHandle())
		return -1;

	window.SetRenderFunction(render);
	window.SetClearColor(Color4f(0.3f, 0.3f, 0.3f));

	Font font_1("Resources\\Consolas.ttf");

	FILE *pFile = fopen("BitmapImage.cpp", "r");
	char test[1024] = { 0 };
	char c = fgetc(pFile);
	int i = 0;

	while(c != EOF && i < 1024)
	{
		test[i++] = c;
		c = fgetc(pFile);
	}

	TextBox tb(test, 0, 32, window.GetWidth(), window.GetHeight() - 64);

	Button b1("New       ", New);
	b1.SetColor(Color4f::BLACK);
	b1.SetHighlightColor(Color4f::DARK_GRAY);
	Button b2("Open      ", Open);
	b2.SetColor(Color4f::BLACK);
	b2.SetHighlightColor(Color4f::DARK_GRAY);
	Button b3("Save      ", Save);
	b3.SetColor(Color4f::BLACK);
	b3.SetHighlightColor(Color4f::DARK_GRAY);
	Button b4("Save As...", SaveAs);
	b4.SetColor(Color4f::BLACK);
	b4.SetHighlightColor(Color4f::DARK_GRAY);

	Menu file_menu("File", 0, 0);
	file_menu.SetColor(Color4f::BLACK);
	file_menu.SetHighlightColor(Color4f::DARK_GRAY);
	file_menu.AddButton(&b1);
	file_menu.AddButton(&b2);
	file_menu.AddButton(&b3);
	file_menu.AddButton(&b4);

	gui.LoadFont(".\\Resources\\Consolas.bmp");
	gui.AddMenu(&file_menu);
	gui.AddTextBox(&tb);

	int retval = window.Run();

	std::wcout << L"\n*** (" <<  retval << ") Exiting Program!\n" << std::endl;
	return retval;
}