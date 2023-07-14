#include "Stage.h"

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"DxLib.h"


Stage::Stage(float location_x, float location_y, float area_width, float area_height)
{
	//描画位置
	location.x = location_x * area_width;
	location.y = location_y * area_height;

	//サイズ
	area.width = area_width;
	area.height = area_height;

	image = LoadGraph("image/stage/floor.png");
}

Stage::~Stage()
{

}

void Stage::Update()
{

}

void Stage::Draw() const
{
	DrawBox(location.x - (area.width / 2), location.y - (area.height / 2),
		(location.x - (area.width / 2)) + area.width, (location.y - (area.height / 2)) + area.height,
		GetColor(255, 255, 0), false);
	DrawGraph(location.x, location.y, image, FALSE);
}



