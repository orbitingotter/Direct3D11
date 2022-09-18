#pragma once

#include "KeyboardEvent.h"
#include <queue>

class Keyboard
{
public:
	Keyboard();
	bool KeyIsPressed(const unsigned char keyCode) const;

	bool KeyBufferIsEmpty() const;
	bool CharBufferIsEmpty() const;

	KeyboardEvent ReadKey();
	unsigned char ReadChar();

	void OnKeyPressed(const unsigned char key);
	void OnKeyReleased(const unsigned char key);
	void OnChar(const unsigned char key);

	void EnableAutoRepeatKeys();
	void DisableAutoRepeatKeys();

	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();

	bool isKeysAutoRepeat() const;
	bool isCharsAutoRepeat() const;



private:
	bool mAutoRepeatKeys = false;
	bool mAutoRepeatChars = false;
	bool mKeyStates[256];
	std::queue<KeyboardEvent> mKeyBuffer;
	std::queue<unsigned char> mCharBuffer;

};