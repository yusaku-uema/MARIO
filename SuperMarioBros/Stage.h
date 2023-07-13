#pragma once
#include"BoxCollider.h"

//�u���b�N�̎�ނ���W�̐ݒ�
struct Block
{
	int x;
	int y;
	int type;
};

//�w�i�ƈ���Ă������ɂ͓����蔻�肪����
class Stage : public  BoxCollider
{
private:
	
	//�u���b�N�̎��
	int image;

	int deta[15][20];

	Block block[15][20];

public:

	//�R���X�g���N�^
	Stage();

	//�f�X�g���N�^
	~Stage();

	//�X�V
	void Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;

	//�X�e�[�W�f�[�^�Ǎ���
	int DataRead();

	Block GetBlockDeta() const;

};

