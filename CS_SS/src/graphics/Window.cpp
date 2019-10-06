#include "../prefix.h"

const wchar_t CLASS_NAME[] = L"CSSS Window Class";

Window::Window(unsigned int width, unsigned int height, const std::string& title)
	: fWidth(width), fHeight(height), fTitle(title)
{
	if (!Init())
	{
		printf("Could not Initialize the window!");
	}
}

Window::~Window()
{

}

bool Window::Init()
{
}