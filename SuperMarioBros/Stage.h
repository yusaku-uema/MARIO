#pragma once
#include"BoxCollider.h"
#include"Define.h"


//�w�i�ƈ���Ă������ɂ͓����蔻�肪����
class Stage : public  BoxCollider
{
private:
	
	//�u���b�N�̎��
	int image;

public:

	//�R���X�g���N�^
	Stage(float location_x,float location_y,float area_width,float area_height);

	//�f�X�g���N�^
	~Stage();

	//�X�V
	void Update();

	//�`��Ɋւ��邱�Ƃ�����
	void Draw() const;

};

