#pragma once

class CameraWork
{
private:
		
	// �`�悷��}�b�v���W�l
	int map_draw_point_x; 
	int map_draw_point_y;	

	// �`�悷��}�b�v�`�b�v�̐�
	int draw_map_chip_num_x;	
	int	draw_map_chip_num_y;	

	// �v���C���[�̈ʒu
	float player_x;
	float player_y;

public:

	//�R���X�g���N�^
	CameraWork();

	//�f�X�g���N�^
	~CameraWork();

	//�X�N���[��
	void Scroll(int scroll_x, int scroll_y);

};

