#include "Mouse.h"

void Mouse::OnLeftPressed(int x, int y)
{
	mLeftIsDown = true;
	MouseEvent me(MouseEvent::EventType::LPress, x, y);
	mEventBuffer.push(me);
}

void Mouse::OnLeftReleased(int x, int y)
{
	mLeftIsDown = false;
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::LRelease, x, y));
}

void Mouse::OnRightPressed(int x, int y)
{
	mRightIsDown = true;
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::RPress, x, y));
}

void Mouse::OnRightReleased(int x, int y)
{
	mRightIsDown = false;
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::RRelease, x, y));
}

void Mouse::OnMiddlePressed(int x, int y)
{
	mMButtonDown = true;
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::MPress, x, y));
}

void Mouse::OnMiddleReleased(int x, int y)
{
	mMButtonDown = false;
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::MRelease, x, y));
}

void Mouse::OnWheelUp(int x, int y)
{
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void Mouse::OnWheelDown(int x, int y)
{
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void Mouse::OnMouseMove(int x, int y)
{
	mX = x;
	mY = y;
	mEventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

bool Mouse::IsLeftDown()
{
	return mLeftIsDown;
}

bool Mouse::IsMiddleDown()
{
	return mMButtonDown;
}

bool Mouse::IsRightDown()
{
	return mRightIsDown;
}

int Mouse::GetPosX()
{
	return mX;
}

int Mouse::GetPosY()
{
	return mY;
}

MousePoint Mouse::GetPos()
{
	return{ mX, mY };
}

bool Mouse::EventBufferIsEmpty()
{
	return mEventBuffer.empty();
}

MouseEvent Mouse::ReadEvent()
{
	if (mEventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent e = mEventBuffer.front();
		mEventBuffer.pop();
		return e;
	}
}