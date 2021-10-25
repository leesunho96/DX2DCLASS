#pragma once
class myRectDraw
{
	ID3D11Buffer* vertexBuffer;
	Vertex vertices[6];
	D3DXMATRIX W, V, P;
	D3DXMATRIX S, R, T;
	Shader* shader;
	D3DXVECTOR2 position;
	D3DXVECTOR3 eye;// (0, 0, -1); // z : 깊이, 실제 카메라가 보이지 않도록. 화면에서 안보이는 위치. 현재 제작하는 게임은 2d
	D3DXVECTOR3 at;// (0, 0, 0); // at : 카메라가 바라보는 방향. (0, 0, -1)에서 (0, 0, 0)을 바라봄
	D3DXVECTOR3 up;// (0, 1, 0); // 상단 방향 알려줌
	D3DXVECTOR4 WorldPosition[2];
	int xScale, yScale;
	void initialize();

	D3DXVECTOR3 GetRandomColor();
public:
	myRectDraw();
	myRectDraw(float left, float top, float right, float down);
	// position 입력받아서 설정.
	void setPosition(D3DXVECTOR2 Position);
	void setColor(D3DXVECTOR3 color);
	void setRandomColor();
	void Update();
	void Render();



	//Rect 구조체 반환(World)
	RECT GetWorldRect();
	~myRectDraw();
};

