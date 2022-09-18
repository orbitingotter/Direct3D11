#pragma once
#include "StringConverter.h"
#include <Windows.h>
#include <source_location>

class ErrorLogger
{
public:
	static void Log(const std::string& message, const std::source_location& location = std::source_location::current());
	static void Log(HRESULT hr, const std::string& message, const std::source_location& location = std::source_location::current());

};
