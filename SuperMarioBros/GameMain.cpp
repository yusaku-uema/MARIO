#include "GameMain.h"
#include"Define.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>



GameMain::GameMain()
{

	FILE* fp;

	//	読み込みモードでファイルを開く
	fopen_s(&fp, "data/stage/test.txt", "r");

	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			fscanf_s(fp, "%d", &block[j][i]);
			
			if (block[j][i] > 0)
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

	player->Update();

	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			if (stage[j][i] != nullptr)
			{
				if (player->HitBox(stage[j][i]))
				{
					player->SetHitBlockFlg(true);
				}

			}
		}
	}

	return this;
}

void GameMain::Draw() const
{
	background_stage->Draw();

	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			if (stage[j][i] != nullptr)
			{
				stage[j][i]->Draw();
			}
		}
	}

	player->Draw();
}
