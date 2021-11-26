#include "stdafx.h"
#include "Animation.h"

Animation::Animation() :
	currentClip(-1), position(0, 0), scale(1, 1), rotation(0, 0, 0)
{

}

Animation::~Animation()
{
	for (auto a : clips)
	{
		SAFE_DELETE(a);
	}
}

void Animation::AddClip(Clip * clip)
{
	clips.push_back(clip);
}

void Animation::Play(UINT clipNumber)
{
	if (clipNumber == currentClip)
		return;
	if (currentClip > -1)
		clips[currentClip]->Stop();

	currentClip = clipNumber;
	clips[currentClip]->Play();
}

void Animation::Stop()
{
	if (currentClip > -1)
		clips[currentClip]->Stop();
}

void Animation::SetPosition(float x, float y)
{
	SetPosition(D3DXVECTOR2(x, y));
}

void Animation::SetPosition(D3DXVECTOR2 & vec)
{
	for (auto a : clips )
	{
		a->Position(vec);
	}
	this->position = vec;
}

void Animation::SetScale(float x, float y)
{
	SetScale(D3DXVECTOR2(x, y));
}

void Animation::SetScale(D3DXVECTOR2 & vec)
{

	for (auto a : clips)
	{
		a->Scale(vec);
	}

	this->scale = vec;
}

void Animation::SetRotation(float x, float y, float z)
{
	SetRotation(D3DXVECTOR3(x, y, z));
}

void Animation::SetRotation(D3DXVECTOR3 & vec)
{
	this->rotation = vec;
}

void Animation::SetRotationDegree(float x, float y, float z)
{
	SetRotationDegree(D3DXVECTOR3(x, y, z));
}

void Animation::SetRotationDegree(D3DXVECTOR3 & vec)
{
	SetRotation(D3DXVECTOR3(
		Math::ToRadian(vec.x), Math::ToRadian(vec.y), Math::ToRadian(vec.z)
	));
}

D3DXVECTOR3 Animation::GetRotationDegree()
{
	return D3DXVECTOR3(Math::ToDegree(rotation.x),
		Math::ToDegree(rotation.y),
		Math::ToDegree(rotation.z));
}

D3DXVECTOR2 Animation::TextureSize()
{
	if (currentClip < 0)
		return D3DXVECTOR2(0, 0);
	return clips[currentClip]->TextureSize();
}

void Animation::Update(D3DXMATRIX &V, D3DXMATRIX &P)
{
	if (currentClip < 0)
		return;

	clips[currentClip]->Position(position);
	clips[currentClip]->Scale(scale);
	clips[currentClip]->Rotation(rotation);
	clips[currentClip]->Update(V, P);
}

void Animation::Render()
{
	if (currentClip < 0)
		return;
	clips[currentClip]->Render();
}

void Animation::DrawBound(bool val)
{
	for (auto clip : clips)
	{
		clip->DrawBound(val);
	}
}

Sprite * Animation::GetSprite()
{
	if (currentClip < 0)
		return NULL;

	return clips[currentClip]->GetSprite();
}

Clip * Animation::GetClip()
{
	if (currentClip < 0)
		return NULL;

	return clips[currentClip];
}
