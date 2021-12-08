#include "stdafx.h"
#include "Line.h"
#include "Marker.h"
#include "Viewer/Freedom.h"
#include "Scene/Scene.h"

Line::Line()
{
}

Line::~Line()
{
}

void Line::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	D3DXVECTOR2 mouseposition = ((Freedom*)(values->MainCamera))->GetPosition();

}

void Line::Render()
{
}
