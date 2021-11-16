#pragma once
#include "Camera.h"

class Freedom : public Camera
{

public:
	Freedom(float speed = 200.0f);
	virtual ~Freedom();

	virtual void Update() override;
	void SetPosition(float x, float y);
	void SetPosition(D3DXVECTOR2& vec);

private:
	void Move(D3DXVECTOR2& translation);
public:
private:
	float speed;
};