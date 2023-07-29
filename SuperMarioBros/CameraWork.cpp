#include "CameraWork.h"
#include"Define.h"

CameraWork::CameraWork()
{

	

}

CameraWork::~CameraWork()
{

}

void CameraWork::Update(float player_lcation)
{
	//自キャラの座標の代入
	charx = player_lcation;
	//カメラ位置を計算
	camerax = charx - SCREEN_WIDTH / 2;
	//左右の補正
	if (camerax < 0) camerax = 0;
	if (camerax > (MAP_PIXEL_WIDTH - SCREEN_WIDTH)) camerax = (MAP_PIXEL_WIDTH - SCREEN_WIDTH);
	//画面内の位置を求める。
	view_charx = charx - camerax;
}

int CameraWork::GetViewCharX()
{
	return view_charx;
}

int CameraWork::GetCameraX()
{
	return camerax;
}

