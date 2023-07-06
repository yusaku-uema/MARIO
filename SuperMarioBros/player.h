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
	int fire_mario[8]; //�t�@�C�A�}���I
	int star_mario_tiny[36]; //��������Ԃł̃X�^�[�}���I
	int star_mario[36]; //�X�[�p�}���Ior�t�@�C�A�}���I�̏�Ԃł̃X�^�[�}���I

	long long int animation_time; //�A�j���[�V��������
	int animation; //�摜�؂�ւ�
	int animation_count; //�摜�؂�ւ�
	int power_up_animation; //�p���[�A�b�v���鎞�Ɏg���A�j���[�V�����p�ϐ�
	int fire_power_up[4]; //�t�@�C�A�}���I�ɂȂ�Ƃ��̎g���v�f�������[����B
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

