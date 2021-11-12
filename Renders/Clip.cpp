#include "stdafx.h"



//
//--------------------------------------
//------------Frame---------------------
//--------------------------------------
Frame::Frame(Sprite * sprite, float time)
{
	Image = sprite;
	Time = time;
}

Frame::~Frame()
{
	SAFE_DELETE(Image);
}

Clip::Clip(PlayMode playmode, float speed)
	:mode(playmode), speed(speed),
	length(0), playTime(0), bPlay(false), currentFrame(0),
	position(0, 0), scale(1, 1), rotation(0, 0, 0)
{

}

Clip::~Clip()
{
	for (auto a : frames)
	{
		SAFE_DELETE(a);
	}

}

void Clip::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void Clip::Position(D3DXVECTOR2 & vec)
{
	position = vec;
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;
}

void Clip::Rotation(float x, float y, float z)
{
	Rotation(D3DXVECTOR3(x, y, z));
}

void Clip::Rotation(D3DXVECTOR3 & vec)
{
	rotation = vec;
}

void Clip::RotationDegree(float x, float y, float z)
{
	RotationDegree(D3DXVECTOR3(x, y, z));
}

void Clip::RotationDegree(D3DXVECTOR3 & vec)
{
	Rotation(D3DXVECTOR3(
		Math::ToRadian(vec.x), Math::ToRadian(vec.y), Math::ToRadian(vec.z)
	));
}

D3DXVECTOR3 Clip::RotationDegree()
{
	return D3DXVECTOR3(
		Math::ToDegree(rotation.x), 
		Math::ToDegree(rotation.y), 
		Math::ToDegree(rotation.z));
}

D3DXVECTOR3 Clip::TextureSize()
{
	return frames[currentFrame]->Image->TextureSize();
}

void Clip::AddFrame(Sprite * sprite, float time)
{
	frames.push_back(new Frame(sprite, time));
}

void Clip::Play()
{
	playTime = 0.0f;
	currentFrame = 0;
	bPlay = true;
}

void Clip::Play(UINT startFrame)
{
	playTime = 0.0f;
	currentFrame = startFrame;

	bPlay = true;
}

void Clip::Stop()
{
	bPlay = false;
	currentFrame = 0;


}

void Clip::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	Frame* frame = frames[currentFrame];
	frame->Image->Update(V, P);

	if (bPlay == false)
		return;


	float time = frame->Time * speed;
	playTime += Timer->Elapsed();

	if (playTime < time)
		return;


	switch (mode)
	{
		case PlayMode::End:
		{
			currentFrame++;

			if (currentFrame >= frames.size())
				Stop();
		}
		break;

		case PlayMode::Loop:
		{
			currentFrame++;
			currentFrame %= frames.size();
		}
		break;

		case PlayMode::Reverse:
		{
			currentFrame--;
			currentFrame %= frames.size();
		}
	}

	playTime = 0.0f;
}

void Clip::Render()
{
	Frame* frame = frames[currentFrame];
	frame->Image->Render();
}

