#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position(0, 0)
{
	D3DXMatrixIdentity(&view);
}

Camera::~Camera()
{

}

void Camera::Update()
{
	// 실제로 화면이 x축으로  + 이동시 보이는건 -로 보임 => -position 입력
	D3DXMatrixTranslation(&view, -position.x, -position.y, 0.0f);

}

void Camera::Render()
{
	ImGui::SliderFloat("position X", &position.x, -1500, 1500);
	ImGui::SliderFloat("position Y", &position.y, -400, 400);
}
