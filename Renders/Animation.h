#pragma once


class Animation
{
public:
	Animation();
	~Animation();

	void AddClip(Clip* clip);
	void Play(UINT clipNumber);
	void Stop();

	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2& vec);
	D3DXVECTOR2 GetPosition() { return position; };

	void SetScale(float x, float y);
	void SetScale(D3DXVECTOR2 &vec);
	D3DXVECTOR2 GetScale() { return scale; };

	void SetRotation(float x, float y, float z);
	void SetRotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 GetRotation() { return rotation; };

	void SetRotationDegree(float x, float y, float z);
	void SetRotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 GetRotationDegree();

	D3DXVECTOR2 TextureSize();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	UINT currentClip;
	vector<Clip*> clips;
public:

private:

};