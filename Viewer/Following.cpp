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
	if (temp.x < -3800.0f)
	{
		temp.x = -3800.0f;
	}
	if (temp.x > 3800.0f)
	{
		temp.x = 3800.0f;
	}
	temp.x -= (float)Width * 0.5f;
	temp.y = (float)0.0f;

	position = temp;

	__super::Update();
}
