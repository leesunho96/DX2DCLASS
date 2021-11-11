#pragma once

enum class PlayMode
{
	End = 0, Loop, Reverse
};

struct Frame
{
	float Time;
	Sprite* Image;

	Frame(Sprite* sprite, float time);
	~Frame();
};
class Clip
{
public:
	Clip(PlayMode playmode = PlayMode::End,
		float speed = 1.0f);
	~Clip();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 &vec);

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);

	void AddFrame(Sprite* sprite, float time);

	void Play();
	void Play(UINT startFrame);
	void Stop();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
private:
	float length; // 시간의 합
	float speed; // 플레이 될 속도

	bool bPlay; // 플레이중인지 아닌지
	UINT currentFrame; // 현재 프레임
	float playTime; // 전체적으로 플레이될 시간
	// != length

	PlayMode mode;

	vector<Frame*> frames; // 각 프레임 벡터

};