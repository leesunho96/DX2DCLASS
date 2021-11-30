#include "stdafx.h"
#include "NonBreakableBricks.h"
#include "Renders/Animation.h"
#include "Objects/Ball.h"

extern Ball* ball;

NonBreakableBricks::NonBreakableBricks(D3DXVECTOR2 position) : IBRICKSINTERFACE(), Position(position)
{
	animation = new Animation;
	Clip* clip;
	wstring TexturesName = Textures + L"/Alkanoid/Blocks.png";
	wstring ShaderName = Shaders + L"009_Sprite.fx";


	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(TexturesName, ShaderName, 124, 226, 242, 293), 1.0f);
	animation->AddClip(clip);

	animation->SetPosition(position);
	// 54 * 22 px
	animation->SetScale(D3DXVECTOR2(0.45, 0.45));
	animation->Play(0);

	animation->DrawBound(true);
}

NonBreakableBricks::~NonBreakableBricks()
{
	SAFE_DELETE(animation);
}

void NonBreakableBricks::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 position = animation->GetPosition();
	D3DXVECTOR2 ballPosition = ball->GetPosition();

	if ((ballPosition.y <= position.y + 30.0f && ballPosition.y >= position.y - 30.0f) && ballPosition.x <= position.x + 30.0f && ballPosition.x >= position.x - 30.0f)
	{
		if (Sprite::AABB(this->animation->GetSprite(), ball->GetSprite()))
		{
			ball->CollisionTestWithBall(animation->GetSprite());
		}
	}

	animation->Play(0);
	animation->Update(V, P);
}

void NonBreakableBricks::Render()
{
	animation->Render();
}
