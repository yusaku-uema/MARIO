#include "Stage.h"

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"DxLib.h"


#define SWITCHING_TIME 6

Stage::Stage(float location_x, float location_y, float area_width, float area_height ,int type)
{

	this->type = type;
	//描画位置
	location.x = location_x * area_width;
	location.y = location_y * area_height;

	//サイズ
	area.width = area_width;
	area.height = area_height;

	camerax = 0;

	animation = 0;
	animation_count = 0;

	switch (type)
	{
	case 1:
		image = LoadGraph("image/stage/floor.png");
		break;
		
	default:
		LoadDivGraph("image/stage/Background (1).png", 12, 12, 1, 32, 32, block);
		break;
	}
}

Stage::~Stage()
{

}

void Stage::Update(int camerax)
{
	this->camerax = camerax;

	if (type > 1)
	{
		++animation_count;
	}

	if (animation > 3)
	{
		animation = 0;
	}

	if (animation_count % SWITCHING_TIME == 0)
	{
		animation++;
	}
}

void Stage::Draw() const
{
	switch (type)
	{
	case 1:
		DrawGraph(location.x - camerax, location.y, image, FALSE);
		break;
	case 2:
		DrawGraph(location.x - camerax, location.y, block[animation], FALSE);
		break;
	case 3:
		DrawGraph(location.x - camerax, location.y, block[4], FALSE);
		break;
	case 4:
		DrawGraph(location.x - camerax, location.y, block[5], FALSE);
		break;
	case 6:
		DrawGraph(location.x - camerax, location.y, block[7], FALSE);
		break;
	case 7:
		DrawGraph(location.x - camerax, location.y, block[9], FALSE);
		break;
	case 8:
		DrawGraph(location.x - camerax, location.y, block[8], FALSE);
		break;
	case 9:
		DrawGraph(location.x - camerax, location.y, block[10], FALSE);
		break;
	case 10:
		DrawGraph(location.x - camerax, location.y, block[11], FALSE);
		break;
	default:
		break;
	}

	DrawBox(location.x - camerax, location.y,
		location.x - camerax + area.width, location.y + area.height,
		GetColor(255, 255, 0), false);


}



