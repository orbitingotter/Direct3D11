#include "RenderWindow.h"
#include "Utilities/ErrorLogger.h"
#include "WindowContainer.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"

RenderWindow::RenderWindow()
	: mHandle(NULL), mInstance(GetModuleHandle(nullptr)),
	mWindowTitle(""), mWindowTitleWide(L""),
	mWindowClass(""), mWindowClassWide(L""),
	mWidth(0), mHeight(0)
{

}

bool RenderWindow::Initialize(WindowContainer* pContainer, std::string windowTitle, std::string windowClass, int width, int height)
{
	mWindowTitle = windowTitle;
	mWindowTitleWide = StringConverter::StringToWide(windowTitle);
	mWindowClass = windowClass;
	mWindowClassWide = StringConverter::StringToWide(windowClass);
	mWidth = width;
	mHeight = height;

	RegisterWindowClass();

	RECT wr;
	wr.left = 0;
	wr.right = mWidth + wr.left;
	wr.top = 0;
	wr.bottom = mHeight + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	mHandle = CreateWindowEx(0, mWindowClassWide.c_str(), mWindowTitleWide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 0, 0,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, mInstance, pContainer);

	if (mHandle == nullptr)
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEx Failed for window : " + mWindowTitle);
		return false;
	}

	ShowWindow(mHandle, SW_SHOW);
	SetForegroundWindow(mHandle);
	SetFocus(mHandle);

	// Setup imgui

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(mHandle);
	ImGui::StyleColorsDark();

	return true;

}


LRESULT CALLBACK SetupWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowContainer* pContainer = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
		if (pContainer == nullptr)
		{
			ErrorLogger::Log("Pointer to Engine is null during WM_NCCREATE");
		}

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pContainer));

		return pContainer->WindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	WindowContainer* pContainer = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	return pContainer->WindowProc(hWnd, uMsg, wParam, lParam);

}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = SetupWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mInstance;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = mWindowClassWide.c_str();
	wc.cbSize = sizeof(wc);

	RegisterClassEx(&wc);
}

bool RenderWindow::ProcessMessages()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (PeekMessage(&msg, mHandle, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_NULL)
	{
		if (!IsWindow(mHandle))
		{
			mHandle = nullptr;
			UnregisterClass(mWindowClassWide.c_str(), mInstance);
			return false;
		}
	}

	return true;
}

RenderWindow::~RenderWindow()
{
	if (mHandle != nullptr)
	{
		UnregisterClass(mWindowClassWide.c_str(), mInstance);
		DestroyWindow(mHandle);
	}

	// Delete imgui

	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

HWND RenderWindow::GetHandle() const
{
	return mHandle;
}

HINSTANCE RenderWindow::GetInstance() const
{
	return mInstance;
}

int RenderWindow::GetWidth()
{
	return mWidth;
}

int RenderWindow::GetHeight()
{
	return mHeight;
}
