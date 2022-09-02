#include "KeyboardEvent.h"
#pragma once

KeyboardEvent::KeyboardEvent()
	: mType(EventType::Invalid), mKey(0u)
{
}

KeyboardEvent::KeyboardEvent(EventType type, const unsigned char key)
	: mType(type), mKey(key)
{
}

bool KeyboardEvent::IsPress() const
{
	return mType == EventType::Press;
}

bool KeyboardEvent::IsRelease() const
{
	return mType == EventType::Release;

}

bool KeyboardEvent::IsInvalid() const
{
	return mType == EventType::Invalid;

}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return 0;
}
