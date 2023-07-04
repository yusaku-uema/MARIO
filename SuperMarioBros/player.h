#pragma once
#include"BoxCollider.h"
#include"PadInput.h"


enum class MARIO_STATE
{
	AMALL_MAIO,   //�`�r�}���I 
	SUPER_MARIO, //�X�[�p�}���I
	FIRE_MARIO, //�t�@�C�A�}���I
	STAR_MARIO, //�X�^�[�}���I
	CHANGE_SUPER_MARIO, //�X�[�p�}���I�ɕω���
	CHANGE_FIRE_MARIO, //�t�@�C�A�}���I�ɕω���
	DEATH //���S���
};


class Player :public BoxCollider
{
private:
	
	int tiny_mario[9]; //�`�r�}���I
	int power_up_image[3]; //�`�r�}���I����X�[�p�}���I 
	int super_mario_image[9]; //�X�[�p�}���I
	long long int animation_time; //�A�j���[�V��������
	int animation; //�摜�؂�ւ�
	int animation_count; //�摜�؂�ւ�
	int power_up_animation; //�`�r�}���I����X�[�p�}���I�ɕω��A�j���[�V����

	int stick_x; //�X�e�B�b�N�ړ�
	float jumping_power; //�W�����v(��Ɍ�������)
	float descent_speed; //�~���X�s�[�h
	float movement_speed; //�ړ����x
	float b_button_press_time; //B�{�^���������Ă��鎞��

	bool jump_flg; //�W�����v���Ă���̂�
	bool left_move; //���ɓ����Ă���̂�
	bool power_up_flg; //�}���I���p���[�A�b�v�A�j���[�V�������s���Ă���̂�


	MARIO_STATE mario_state; //�}���I�̏��
	

public:

	//�R���X�g���N�^
	Player();

	//�f�X�g���N�^
	~Player();
	

	//�X�V
	void Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;

	//�}���I�̑���
	void Operation();

	//�}���I�W�����v
	void MarioJump();

	//�}���I�p���[�A�b�v,�A�j���[�V����
	void PowerUpAnimation();

};

