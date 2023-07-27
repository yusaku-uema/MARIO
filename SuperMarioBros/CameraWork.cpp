#include "CameraWork.h"
#include"Define.h"

CameraWork::CameraWork()
{

	map_draw_point_x = 0;
	map_draw_point_y = 0;

	draw_map_chip_num_x = 0;
	draw_map_chip_num_y = 0;

	player_x = 0;
	player_y = 0;

}

CameraWork::~CameraWork()
{

}

void CameraWork::Scroll(int ScrollX, int ScrollY)
{
	// �`�悷��}�b�v�`�b�v�̐����Z�b�g
	draw_map_chip_num_x = 640 / SIZE_MAP_X;
	draw_map_chip_num_y = 480 / SIZE_MAP_Y;

	// ��ʍ���ɕ`�悷��}�b�v���W���Z�b�g
	map_draw_point_x = player_x - (draw_map_chip_num_x / 2 - 1);
	map_draw_point_y = player_y - (draw_map_chip_num_y / 2 - 1);
}
