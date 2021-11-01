#pragma once

class Sprite
{
public:
	Sprite(wstring textureFile, wstring shaderFile);
	Sprite(wstring textureFile, wstring shaderFile, 
		float endX, float endY);
	Sprite(wstring textureFile, wstring shaderFile, 
		float startX, float startY, 
		float endX, float endY);
private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};

	wstring textureFile;
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	ID3D11ShaderResourceView* srv;
public:
private:
public:

};