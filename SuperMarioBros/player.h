#pragma once
#include"BoxCollider.h"
#include"PadInput.h"

class Player :public BoxCollider
{
private:
	
	int stick_x; //�X�e�B�b�N�ړ�
	float jumping_power; //�W�����v(��Ɍ�������)
	float descent_speed; //�~���X�s�[�h
	float movement_speed; //�ړ����x
	float direction_move; //�ړ��������

	bool jump_flg; //�W�����v���Ă���̂�
	

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

};

