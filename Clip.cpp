#include "stdafx.h"
#include "Clip.h"


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
	length(0), playTime(0), bPlay(false), currentFrame(0)
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
	for (auto a : frames)
	{
		a->Image->Position(vec);
	}
}

void Clip::Scale(float x, float y)
{
	Scale(D3DXVECTOR2(x, y));
}

void Clip::Scale(D3DXVECTOR2 & vec)
{
	for (auto a : frames)
	{
		D3DXVECTOR2 scale = a->Image->Scale();
		a->Image->Scale(vec.x, vec.y);
	}
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

