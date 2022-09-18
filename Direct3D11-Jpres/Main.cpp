#include <Windows.h>
#include "Engine.h"
#include "Utilities/ErrorLogger.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")
#pragma comment(lib, "D3DCompiler.lib")



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	CoInitialize(NULL);
	Engine engine;
	engine.Initialize("Direct3D11 App", "Direct3D11 App", 800, 600);

	while (engine.ProcessMessages())
	{
		engine.Update();
	}

	return 0;
}