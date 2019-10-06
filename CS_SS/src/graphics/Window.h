#pragma once
class Window
{
public:
	Window(unsigned int width, unsigned int height, const std::string& title);
	~Window();
public:
	bool Create(HINSTANCE hInstace);
private:
	unsigned int fWidth;
	unsigned int fHeight;
	std::string fTitle;
};

