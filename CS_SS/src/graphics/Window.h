#pragma once
class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::string& title);
	~Window();
private:
	unsigned int fWidth;
	unsigned int fHeight;
	std::string fTitle;
};

