#pragma once
#include <Windows.h>
#include <string>

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer* pContainer, std::string windowTitle, std::string windowClass, int width, int height);
	bool ProcessMessages();
	RenderWindow();
	~RenderWindow();

	HWND GetHandle() const;
	HINSTANCE GetInstance() const;
	int GetWidth();
	int GetHeight();

private:
	void RegisterWindowClass();

	HWND mHandle;
	HINSTANCE mInstance;
	std::string mWindowTitle;
	std::wstring mWindowTitleWide;
	std::string mWindowClass;
	std::wstring mWindowClassWide;
	int mWidth;
	int mHeight;

};