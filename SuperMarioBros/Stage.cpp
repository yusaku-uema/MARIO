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

	camerax = 0;

	image = LoadGraph("image/stage/floor.png");
}

Stage::~Stage()
{

}

void Stage::Update(int camerax)
{
	this->camerax = camerax;
}

void Stage::Draw() const
{
	//デバック
	/*DrawBox(location.x ,location.y,
		location.x + area.width, location.y+area.height,
		GetColor(255, 255, 0), false);

	DrawFormatString(location.x, location.y, 0xFFFFFF, "%f", location.x-32);
	*/
	DrawGraph(location.x - camerax, location.y, image, FALSE);
}



