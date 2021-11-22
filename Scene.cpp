#include "stdafx.h"
#include "Systems/Device.h"

#include "Objects/Bullet.h"
#include "Objects/Player.h"
#include "Viewer/Freedom.h"
#include "Viewer/Following.h"
#include "Objects/Background.h"
#include "Objects/Goomba.h"

Player* player;
vector<Goomba*> enemylist;
Background* bg;

Following* following;
Freedom* freedom;

Camera* camera;

void InitScene()
{
	player = new Player(D3DXVECTOR2(-4000, 500), D3DXVECTOR2(1.0f, 1.0f));
	bg = new Background();
	freedom = new Freedom();
	following = new Following(player);

	/*Goomba* enemy = new Goomba(-3000, -2700);
	enemylist.push_back(enemy);
*/
	camera = following;
}

void DestroyScene()
{
	SAFE_DELETE(camera)
	SAFE_DELETE(bg);
	SAFE_DELETE(player);

}

D3DXMATRIX V, P;
void Update()
{
	//View
	camera->Update();
	V = camera->GetView();
	//Projection
	D3DXMatrixOrthoOffCenterLH(&P, 0, (float)Width, 0, (float)Height, -1, 1);
	player->Update(V, P);
	bg->Update(V, P);

	for (auto a : enemylist )
	{
		a->Update(V, P);
	}
}

void Render()
{
	D3DXCOLOR bgColor = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		if (ImGui::Button("ChangeCamera"))
		{
			if (camera == following)
			{
				camera = freedom;
			}
			else
			{
				camera = following;
			}
		}
		ImGui::LabelText("FPS", "%.0f", ImGui::GetIO().Framerate);
		camera->Render();
		bg->Render();
		for (auto a : enemylist )
		{
			a->Render();
		}
		player->Render();

	}
	ImGui::Render();
	SwapChain->Present(0, 0);
}
