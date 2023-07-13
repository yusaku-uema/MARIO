#include "Stage.h"

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"Define.h"
#include"DxLib.h"


int deta1[15][20] =
{
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,

		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,

		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,  0, 0, 0, 0, 0,
		1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,
		1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,  1, 1, 1, 1, 1,
};


Stage::Stage()
{
	DataRead();
	image=LoadGraph("image/stage/floor.png");


	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			block[j][i].x = 0;
			block[j][i].y = 0;
			block[j][i].type = 0;
		}
	}
}

Stage::~Stage()
{

}

void Stage::Update()
{
	
}

void Stage::Draw() const
{

	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			if (deta1[j] [i] == 1)
			{
				DrawGraph(i * SIZE_MAP_X, j * SIZE_MAP_Y, image, FALSE);
			}
		}
	}
}


int Stage::DataRead()
{

	FILE* fp;

	//	読み込みモードでファイルを開く
	fopen_s(&fp, "data/stage/test.txt", "r");


	for (int j = 0; j < NUM_MAP_Y; j++)
	{
		for (int i = 0; i < NUM_MAP_X; i++)
		{
			fscanf_s(fp, "%d", &block[j][i].type);
			if (block[j][i].type == 1)
			{
				block[j][i].x = i * SIZE_MAP_X;
				block[j][i].y = j * SIZE_MAP_Y;
				location.x = 32;
				location.y = 32;
				area.height = 16;
				area.width = 16;
			}
		}
	}


	fclose(fp);

	return 0;
}

Block Stage::GetBlockDeta() const
{
	return block[0][0];
}

