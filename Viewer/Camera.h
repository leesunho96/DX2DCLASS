#pragma once

class Camera
{

public:
	Camera();
	virtual ~Camera();

	D3DXMATRIX GetView() { return view; };
	D3DXVECTOR2 GetPosition() { return position; };
	virtual void Update();
	void Render();

protected:
	D3DXVECTOR2 position;
private:
	D3DXMATRIX view;

};