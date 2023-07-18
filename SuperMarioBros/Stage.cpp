#include "Stage.h"

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"DxLib.h"


Stage::Stage(float location_x, float location_y, float area_width, float area_height)
{
	//�`��ʒu
	location.x = location_x * area_width;
	location.y = location_y * area_height;

	//�T�C�Y
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
	//�f�o�b�N
	DrawBox(location.x ,location.y,
		location.x + area.width, location.y+area.height,
		GetColor(255, 255, 0), false);
	
	DrawGraph(location.x, location.y, image, FALSE);
}



