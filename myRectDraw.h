#pragma once
class myRectDraw
{
	ID3D11Buffer* vertexBuffer;
	Vertex vertices[6];
	D3DXMATRIX W, V, P;
	D3DXMATRIX S, R, T;
	Shader* shader;
	D3DXVECTOR2 position;
	D3DXVECTOR3 eye;// (0, 0, -1); // z : ����, ���� ī�޶� ������ �ʵ���. ȭ�鿡�� �Ⱥ��̴� ��ġ. ���� �����ϴ� ������ 2d
	D3DXVECTOR3 at;// (0, 0, 0); // at : ī�޶� �ٶ󺸴� ����. (0, 0, -1)���� (0, 0, 0)�� �ٶ�
	D3DXVECTOR3 up;// (0, 1, 0); // ��� ���� �˷���
	D3DXVECTOR4 WorldPosition[2];
	int xScale, yScale;
	void initialize();

	D3DXVECTOR3 GetRandomColor();
public:
	myRectDraw();
	myRectDraw(float left, float top, float right, float down);
	// position �Է¹޾Ƽ� ����.
	void setPosition(D3DXVECTOR2 Position);
	void setColor(D3DXVECTOR3 color);
	void setRandomColor();
	void Update();
	void Render();



	//Rect ����ü ��ȯ(World)
	RECT GetWorldRect();
	~myRectDraw();
};

