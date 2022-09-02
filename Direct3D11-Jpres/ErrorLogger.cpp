#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(const std::string& message, const std::source_location& location)
{
	std::string errorMessage = "File : " + std::string(location.file_name()) + "\nFunction : " +
		std::string(location.function_name()) + "()\nError : " + message;
	MessageBoxA(NULL, errorMessage.c_str(), "Error", MB_ICONERROR);
}


void ErrorLogger::Log(HRESULT hr, const std::string& message, const std::source_location& location)
{
	_com_error error(hr);
	std::wstring errorMessage = L"File : " + StringConverter::StringToWide(location.file_name()) + L"\nFunction : " +
		StringConverter::StringToWide(location.function_name()) +
		L"()\nError : " + StringConverter::StringToWide(message) +
		L"\nError Description : " + error.ErrorMessage();

	MessageBoxW(NULL, errorMessage.c_str(), L"Error", MB_ICONERROR);

}