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
	//���L�����̍��W�̑��
	charx = player_lcation;
	//�J�����ʒu���v�Z
	camerax = charx - SCREEN_WIDTH / 2;
	//���E�̕␳
	if (camerax < 0) camerax = 0;
	if (camerax > (MAP_PIXEL_WIDTH - SCREEN_WIDTH)) camerax = (MAP_PIXEL_WIDTH - SCREEN_WIDTH);
	//��ʓ��̈ʒu�����߂�B
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

