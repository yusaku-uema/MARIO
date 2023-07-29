#include "GameMain.h"
#include"Define.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>



GameMain::GameMain()
{

	FILE* fp;

	block = 0;

	rendering_coordinates_x = 0;

	camerawork = new CameraWork();

	//	読み込みモードでファイルを開く
	fopen_s(&fp, "data/stage/mario_test1.txt", "r");

	if (fp == nullptr)
	{
		int a = 0;
	}

	for (int j = 0; j < MAP_Y; j++)
	{
		for (int i = 0; i < MAP_MAX; i++)
		{
			
			fscanf_s(fp, "%d", &block);
			
			if (block> 0)
			{
				stage[j][i] = new Stage(i, j, 32, 32);
			}
			else
			{
				stage[j][i] = nullptr;
			}

		}
	}

	fclose(fp);

	player = new Player();
	background_stage = new BackgroundStage();
}

GameMain::~GameMain()
{
	delete player;
	delete background_stage;
	delete stage;
}

AbstractScene* GameMain::Update()
{

	camerawork->Update(player->GetLocation().x);

	Location oldlocatio = player->GetLocation();
	
	player->Update(camerawork->GetViewCharX());

	if (player->GetHitBlockFlg() == true)
	{
		player->SetHitBlockFlg(false);
	}

	if (player->GetLocation().x > oldlocatio.x)
	{
		rendering_coordinates_x++;
	}

	for (int j = 0; j < MAP_Y; j++)
	{
		for (int i = 0; i < MAP_MAX; i++)
		{
			if (stage[j][i] != nullptr)
			{
				stage[j][i]->Update(camerawork->GetCameraX());
				player->Hit(stage[j][i]);
			}
		}
	}



	return this;
}

void GameMain::Draw() const
{
	background_stage->Draw();

	for (int j = 0; j < MAP_Y; j++)
	{
		for (int i = 0; i < MAP_MAX; i++)
		{
			if (stage[j][i] != nullptr)
			{
				stage[j][i]->Draw();
			}
		}
	}

	player->Draw();
}
