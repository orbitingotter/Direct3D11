#pragma once

#include <string>
#include "RenderWindow.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Graphics/Graphics.h"


class WindowContainer
{
protected:
	RenderWindow renderWindow;
	Keyboard keyboard;
	Mouse mouse;
	Graphics graphics;

public:
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};