#pragma once
#include <string>

class StringConverter
{
public:
	static std::wstring StringToWide(const std::string& str)
	{
		std::wstring wideString(str.begin(), str.end());
		return wideString;
	}
};