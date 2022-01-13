#pragma once
#include "IFollowing.h"
#include "Camera.h"


class Following : public Camera
{

public:
	Following(IFollowing* focus = NULL);
	virtual ~Following();

	void Change(IFollowing* focus);
	void Update() override;

	void SetLimit(RECT rect, D3DXVECTOR2 focusoffset);

private:
	IFollowing* focus;
	//float left, right, height, bottom;
	RECT Rect;
	D3DXVECTOR2 Focusoffset;
};