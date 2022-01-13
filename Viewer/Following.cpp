#include "stdafx.h"
#include "Following.h"

Following::Following(IFollowing * focus)
	:focus(focus)
{

}

Following::~Following()
{

}

void Following::Change(IFollowing * focus)
{
	this->focus = focus;
}

void Following::Update()
{
	if (focus == NULL) return;

	D3DXVECTOR2 location, size;
	focus->Focus(&location, &size);

	D3DXVECTOR2 temp = location;

	temp.x -= (float)Width * 0.5f;
	temp.y -= (float)Height * 0.5f;

	if (temp.x < Rect.left + Focusoffset.x)
	{
		temp.x = Rect.left + Focusoffset.x;
	}
	if (temp.x > Rect.right - (float)Width + Focusoffset.x)
	{
		temp.x = Rect.right - (float)Width + Focusoffset.x;
	}


	if (temp.y < Rect.bottom + Focusoffset.y)
	{
		temp.y = Rect.bottom + Focusoffset.y;
	}
	if (temp.y > Rect.top - (float)Height  + Focusoffset.y)
	{
		temp.y = Rect.top - (float)Height  + Focusoffset.y;
	}
	position = temp;

	__super::Update();
}

void Following::SetLimit(RECT rect, D3DXVECTOR2 focusoffset)
{
	this->Rect = rect;
	this->Focusoffset = focusoffset;
}


