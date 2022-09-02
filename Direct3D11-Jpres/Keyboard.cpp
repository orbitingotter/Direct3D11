#include "Keyboard.h"
#pragma once

Keyboard::Keyboard()
{
	for (int i = 0; i < 256; i++)
		mKeyStates[i] = false;
}

bool Keyboard::KeyIsPressed(const unsigned char keyCode) const
{
	return mKeyStates[keyCode];
}

bool Keyboard::KeyBufferIsEmpty() const
{
	return mKeyBuffer.empty();
}

bool Keyboard::CharBufferIsEmpty() const
{
	return mCharBuffer.empty();
}

KeyboardEvent Keyboard::ReadKey()
{
	if (mKeyBuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent e = mKeyBuffer.front();
		mKeyBuffer.pop();
		return e;
	}
}

unsigned char Keyboard::ReadChar()
{
	if (mCharBuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = mCharBuffer.front();
		mCharBuffer.pop();
		return e;
	}
}

void Keyboard::OnKeyPressed(const unsigned char key)
{
	mKeyStates[key] = true;
	mKeyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void Keyboard::OnKeyReleased(const unsigned char key)
{
	mKeyStates[key] = false;
	mKeyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void Keyboard::OnChar(const unsigned char key)
{
	mCharBuffer.push(key);
}

void Keyboard::EnableAutoRepeatKeys()
{
	mAutoRepeatKeys = true;
}

void Keyboard::DisableAutoRepeatKeys()
{
	mAutoRepeatKeys = false;
}

void Keyboard::EnableAutoRepeatChars()
{
	mAutoRepeatChars = true;
}

void Keyboard::DisableAutoRepeatChars()
{
	mAutoRepeatChars = false;
}

bool Keyboard::isKeysAutoRepeat() const
{
	return mAutoRepeatKeys;
}

bool Keyboard::isCharsAutoRepeat() const
{
	return mAutoRepeatChars;
}
