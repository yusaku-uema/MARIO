#pragma once
#include"BoxCollider.h"



//�w�i�ƈ���Ă������ɂ͓����蔻�肪����
class Stage : public  BoxCollider
{
private:
	
	//�u���b�N�̎��
	int image[20];

	int deta[];

public:

	//�R���X�g���N�^
	Stage();

	//�f�X�g���N�^
	~Stage();

	//�X�V
	void Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;
};

