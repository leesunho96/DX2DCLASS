#include "stdafx.h"
#include "Objects/Shoulder.h"
#include "Systems/StopWatch.h"



Shoulder::Shoulder(ShoulderType shouldertype, D3DXVECTOR2 position, D3DXVECTOR2 scale) 
	: stopwatch(StopWatch()), position(position), shouldertype(shouldertype), scale(scale), rotation(D3DXVECTOR3(0, 0, 0))
{
	wstring texture = Textures + L"/TianSouls/gol_lath.png";
	wstring shader = Shaders + L"/009_Sprite.fx";
	switch (shouldertype)
	{
	case ShoulderType::Left:
		shoulder = new Sprite(texture, shader, 151, 102, 185, 141);
		direction = D3DXVECTOR2(-1, 0);
		break;
	case ShoulderType::Right:
		shoulder = new Sprite(texture, shader, 198, 102, 234, 141);
		direction = D3DXVECTOR2(1, 0);
		break;
	}
	stopwatch.RetAndSetTimer(1.0f);
}

Shoulder::~Shoulder()
{
	SAFE_DELETE(shoulder);
}

void Shoulder::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	if (bIsActivate)
	{
		if (!stopwatch.IsOver())
		{
			position += direction * Timer->Elapsed() * 10.0f;
		}
		else
		{
			direction = direction == D3DXVECTOR2(1, 0) ? D3DXVECTOR2(-1, 0) : D3DXVECTOR2(1, 0);
			stopwatch.RetAndSetTimer(1.0f);
		}

		stopwatch.Update();
	}
	shoulder->Position(position);
	shoulder->Scale(scale);
	shoulder->RotationDegree(rotation);
	shoulder->Update(V, P);

}

void Shoulder::Render()
{
	shoulder->Render();
}